/*
============================================================================
 Name        : XmlHandler.h
 Author      : Cleave Pokotea
 Version     :
 Copyright   : 2006 - 2007
 Description : XmlHandler.h - header file
============================================================================
*/

#ifndef XMLHANDLER_H
#define XMLHANDLER_H

#include <coeccntx.h>
#include <eikon.hrh>
#include <e32std.h>
#include <coeccntx.h>
#include <eikenv.h>
#include <eikmenup.h>
#include "XmlQueryParser.h"
#include <http.h>
#include "ResponseError.h"
#include "ResponseItem.h"
#include "ResponseResult.h"

enum TLatherState 
{ 
	eStateStarting,
	eStateConnecting, 
	eStateFoundServer,
	eStateSentData,
	eStateReceivedResponse, 
	eStateComplete
};

struct TLatherQuery
{
	HBufC*		iGetSpecByCode;
	HBufC*		iBrowseSpecsByName;
	TInt		iBrowseSpecsByCategory;
};

/*
* CSpecQueryModel
* 
* Spec Model derived from CBase. Used to store SOAP related conditions
*/

class CSpecQueryModel : public CBase
{
public:
	CSpecQueryModel();
	~CSpecQueryModel();

	void	Reset();

	TInt						iHttpError;
	TLatherState				iState;
	TLatherQuery				iQuery;

	// Lather::ExecuteL()
	TLatherError				iError;	
	TLatherResult				iResult;
	TLatherItems 				iItems;		
};

/*
* MLatherObserver
* 
* This is the link between the application user interface and the engine.
* Whenever an event happens in the engine, the application user interface
* is notified via this callback interface function. This then updates the
* current view with the new information from the engine. Typically this new
* information will be obtained from the model [ CSpecQueryModel ].
*/
class MLatherObserver
{
public:
	virtual void	LatherEStateChanged(const TLatherState aNewState) = 0;
};

/*
* Main SOAP class
*/
class CLather : public CBase, private MHTTPTransactionCallback, private MHTTPDataSupplier
{
public:
	static CLather* NewL(CSpecQueryModel& aModel, MLatherObserver& aObserver);
	static CLather* NewLC(CSpecQueryModel& aModel, MLatherObserver& aObserver);

	virtual ~CLather();

	void ExecuteL(); // the data needed is in the model

private:
	// MHTTPSessionEventCallback interface functions
	virtual void MHFRunL(RHTTPTransaction aTransaction, const THTTPEvent& aEvent);
	virtual TInt MHFRunError(TInt aError, RHTTPTransaction aTransaction, const THTTPEvent& aEvent);

	// MHTTPDataSupplier interface function
	virtual void  ReleaseData();		
	virtual TBool GetNextDataPart(TPtrC8& aDataPart);
	virtual TInt  Reset();
	virtual TInt  OverallDataSize();


	void  CleanupQueryText();

	CLather(CSpecQueryModel& aModel, MLatherObserver& aObserver);
	void 	ConstructL();

	void 	AddRequestHeaderL(TInt aHdrField, const TDesC8& aHdrValue);

	// Functions to generate and release the text query data
	TPtr8 	GetSoapXml();
	void	CleanupSoapXml();

private:
	RFs					iFs;
	MLatherObserver&	iObserver;
	CSpecQueryModel&  	iModel;
	RHTTPSession	 	iSession;
	RHTTPTransaction 	iTransaction;
	HBufC8*			 	iQueryText;
	HBufC8*			 	iQueryResponse;
	CResponse*			iResponse;
};

#endif
