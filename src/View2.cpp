/*
============================================================================
Name        : View2 from View2.h
Author      : Cleave Pokotea
Version     :
Copyright   : 2006 - 2007
Description : View2 implementation
============================================================================
*/

// INCLUDE FILES
#include  <aknviewappui.h>
#include  <avkon.hrh>
#include  <Mp.rsg>
#include  "Mp.hrh"
#include  "View2.h"
#include  "Container2.h" 

// ================= MEMBER FUNCTIONS =======================

void CView2::ConstructL()
{
	BaseConstructL( R_MP_VIEW2 );

	iTextForegroundColour = TRgb(41,61,85);
	iTextBackgroundColour = TRgb(179,204,230); //TRgb(159,177,233);
	iHighlightForegroundColour = TRgb(22,28,50);
	iHighlightBackgroundColour = TRgb(233,235,255);
}


CView2::~CView2()
{
	if ( iContainer )
	{
		AppUi()->RemoveFromViewStack( *this, iContainer );
	}

	delete iContainer;
}


TUid CView2::Id() const
{
	return KView2Id;
}


void CView2::HandleCommandL(TInt aCommand)
{   
	switch ( aCommand )
	{
	//case EAknSoftkeyOk:
	//	{
	//		break;
	//	}
	case EAknSoftkeyBack:
		{
			AppUi()->HandleCommandL(EEikCmdExit);
			break;
		}
	case ECmdSendSMS:
		{
			TUid vId;
			vId.iUid = EMpViewSms;
			AppUi()->ActivateLocalViewL(vId);
			break;
		}
	case ECmdPlay:
		{
			TUid vId;
			vId.iUid = EMpViewSpecs;
			AppUi()->ActivateLocalViewL(vId);
			break;
		}
	case ECmdDownload:
		{
			//Note
			break;
		}
	default:
		{
			AppUi()->HandleCommandL( aCommand );
			break;
		}
	}
}


void CView2::HandleClientRectChange()
{
	if ( iContainer )
	{
		iContainer->SetRect( ClientRect() );
	}
}


void CView2::DoActivateL(const TVwsViewId& /*aPrevViewId*/,
						 TUid /*aCustomMessageId*/,
						 const TDesC8& /*aCustomMessage*/)
{
	if (!iContainer)
	{
		iContainer = new (ELeave) CContainer2;
		iContainer->SetMopParent(this);

		iContainer->SetColours(iTextForegroundColour, 
			iTextBackgroundColour,
			iHighlightForegroundColour,
			iHighlightBackgroundColour);

		iContainer->ConstructL( ClientRect() );
		//iContainer->ConstructL(CEikAppUi::ClientRect());
		AppUi()->AddToStackL( *this, iContainer );
		//iContainer->DrawNow();
	}
}


void CView2::DoDeactivate()
{
	if ( iContainer )
	{
		AppUi()->RemoveFromViewStack( *this, iContainer );
		delete iContainer;
		iContainer = NULL;
	}
}
