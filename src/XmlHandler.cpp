/*
============================================================================
Name        : XmlHandler.cpp
Author      : Cleave Pokotea
Version     :
Copyright   : 2006 - 2007
Description : XmlHandler.cpp - source file
============================================================================
*/

#include "XmlHandler.h"
#include <uri8.h>
#include <XmlGen.h>
#include <TumunuExpat.h>
//#include "errors.pan"

#include "XmlQueryBuilder.h"
#include "XmlQueryParser.h"

/*
Some constants. These will be overridden for all SOAP 
'query' and 'response' messages
*/
_LIT(KQueryFilename,"XmlQuery.xml");
_LIT(KResponseFilename, "XmlResponse.xml");


CXmlHandler* CXmlHandler::NewL(CGoogleItModel& aModel, MGoogleItEngineObserver& aObserver)
{
	CXmlHandler* self = NewLC(aModel, aObserver);
	CleanupStack::Pop();

	return self;
}

CXmlHandler* CXmlHandler::NewLC(CGoogleItModel& aModel, MGoogleItEngineObserver& aObserver)
{
	CXmlHandler* self = new (ELeave)CXmlHandler(aModel, aObserver);
	CleanupStack::PushL(self);

	self->ConstructL();

	return self;
}

CXmlHandler::CXmlHandler(CGoogleItModel& aModel, MGoogleItEngineObserver& aObserver) : iModel(aModel),
iObserver(aObserver),
iQueryText(NULL),
iQueryResponse(NULL)
{

}

CXmlHandler::~CXmlHandler()
{
	iTransaction.Close();
	iSession.Close();
	iFs.Close();
}

void CXmlHandler::ConstructL()
{
	User::LeaveIfError(iFs.Connect());

	iSession.OpenL();
}

void CXmlHandler::AddRequestHeaderL(TInt aHdrField, const TDesC8& aHdrValue)
{
	RHTTPHeaders headers = iTransaction.Request().GetHeaderCollection();

	RStringF valStr = iSession.StringPool().OpenFStringL(aHdrValue);
	CleanupClosePushL(valStr);

	THTTPHdrVal val(valStr);
	headers.SetFieldL(iSession.StringPool().StringF(aHdrField, RHTTPSession::GetTable()), val);
	CleanupStack::PopAndDestroy(); // valStr
}

TPtr8 CXmlHandler::GetQueryText()
{
	/*
	Generate query here and create a cached copy of the data. 
	Basically static after it has been generated once.
	*/
	if (iQueryText == NULL)
	{
		CGoogleQueryBuilder queryBuilder;
		iQueryText = queryBuilder.CreateQueryL(iModel.iQuery);

#ifdef LOG_REQUEST		
		LogMessage(iFs, KQueryFilename, *iQueryText);
#endif
	}

	return iQueryText->Des();
}

void CXmlHandler::CleanupQueryText()
{
	delete iQueryText;
	iQueryText = NULL;

	delete iQueryResponse;
	iQueryResponse = NULL;
}

_LIT8(KUserAgent, "Tumunu. You to your World");
_LIT8(KAccept, "*/*");
_LIT8(KPlainText, "text/xml");
_LIT8(KMpowerUrl, "http://mpower.url");

void CXmlHandler::ExecuteL()
{
	__ASSERT_ALWAYS(iModel.iState == eStateComplete, User::Panic(KModuleName, EAlreadyRunning));
	__ASSERT_ALWAYS(iModel.iQuery.iSearch != NULL, User::Panic(KModuleName, ENoQueryTerm));

	iModel.iState = eStateStarting;
	// next create a http transaction	
	TUriParser8  uri;
	uri.Parse(KMpowerUrl);

	// Set the transaction method to post as we will be submitting an xml soap request
	RStringF method = iSession.StringPool().StringF(HTTP::EPOST, RHTTPSession::GetTable());

	iTransaction.Close();	
	iTransaction = iSession.OpenTransactionL(uri, *this, method);

	// Set headers for request; user agent, accepted content type and body's content type.
	AddRequestHeaderL(HTTP::EUserAgent, KUserAgent);
	AddRequestHeaderL(HTTP::EAccept, KAccept);
	AddRequestHeaderL(HTTP::EContentType, KPlainText);

	// set the body text handler
	iTransaction.Request().SetBody(*this);

	// and start it
	iTransaction.SubmitL();

	iModel.iState = eStateConnecting;
}

// MHTTPTransactionCallback interface functions
void CXmlHandler::MHFRunL(RHTTPTransaction aTransaction, const THTTPEvent& aEvent)
{
	switch (aEvent.iStatus) 
	{ 
	case THTTPEvent::EGotResponseHeaders: 
		{
			iObserver.GIEStateChanged(eStateFoundServer);				
			iModel.iState = eStateFoundServer;

			/*
			Not interested in the received header 
			*/
		}
		break; 
	case THTTPEvent::EGotResponseBodyData: 
		{

#ifdef _INCREMENTAL_H

#else
			/*
			The non incremental version of the parser will just build 
			up a string of the data until the EReponseComplete code is
			received. Then the string is sent to parser in one go
			*/
			RHTTPResponse response = aTransaction.Response();
			MHTTPDataSupplier* bodyPtr = response.Body();

			/*
			Received data is appended to the existing block (if there is a block),
			otherwise a new block is created
			*/
			TPtrC8 bodypart;
			bodyPtr->GetNextDataPart(bodypart);
			if (iQueryResponse == NULL)
			{
				iQueryResponse = HBufC8::NewL( bodypart.Length() );
			}
			else
			{
				const TInt newSize = iQueryResponse->Length() + bodypart.Length();
				iQueryResponse = iQueryResponse->ReAllocL( newSize );
			}
			TPtr8 tmp = iQueryResponse->Des();
			tmp.Append(bodypart);
			bodyPtr->ReleaseData();
#endif
		}
		break; 
	case THTTPEvent::EResponseComplete: 
		{
			iObserver.GIEStateChanged(eStateReceivedResponse);				
			iModel.iState = eStateReceivedResponse;

#ifdef _INCREMENTAL_H

#else
#ifdef LOG_RESONSE
			LogMessage(iFs, KResponseFilename, *iQueryResponse);
#endif
			/*
			Data block ready. Parse and fill data model
			*/
			OneTripParse(iQueryResponse->Des(), iModel.iError, iModel.iResult, iModel.iItems);
#endif				

			CleanupQueryText();
			iObserver.GIEStateChanged(eStateComplete);				
			iModel.iState = eStateComplete;

		}
		break; 
	case THTTPEvent::ESucceeded: 
		{
			// transaction successful
			// we do not do this in the response complete phase or error
			// phase as it is nicer to break it up because if the parser
			// is working non incrementally we have potientionally done
			// a lot of work in the ReponseComplete phase
			iObserver.GIEStateChanged(eStateComplete);				
			iModel.iState = eStateComplete;
		}
		break; 
	case THTTPEvent::EFailed: 
		{
			// Transaction failed
			MHFRunError(aEvent.iStatus, aTransaction, aEvent);
		}
		break;
	default: 
		{
			/* 
			All errors will fall through to the generic event handler
			The only exceptional error handling is done when the soap 
			request itself fails and it reports an error
			*/
			MHFRunError(aEvent.iStatus, aTransaction, aEvent);
		}
		break;
	}
}

TInt CXmlHandler::MHFRunError(TInt aError, RHTTPTransaction /*aTransaction*/, const THTTPEvent& /*aEvent*/)
{
	iModel.iHttpError = aError;

	iModel.iState = eStateComplete;
	iObserver.GIEStateChanged(eStateComplete);				

	return KErrNone;
}


// MHTTPDataSupplier interface function
void  CXmlHandler::ReleaseData()
{
	iObserver.GIEStateChanged(eStateSentQuery);				
	iModel.iState = eStateSentQuery;

}

TBool CXmlHandler::GetNextDataPart(TPtrC8& aDataPart)
{
	const TPtr8 queryTextPtr = GetQueryText();

	aDataPart.Set(queryTextPtr);


	return ETrue;
}

TInt CXmlHandler::Reset()
{
	return KErrNone;
}

TInt CXmlHandler::OverallDataSize()
{
	const TPtr8 queryTextPtr = GetQueryText();

	const TInt size = queryTextPtr.Size();

	return size;
}
