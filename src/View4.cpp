/*
============================================================================
Name        : View4 from View4.h
Author      : Cleave Pokotea
Version     :
Copyright   : 2006 - 2007
Description : View4 implementation
============================================================================
*/

// INCLUDE FILES
#include  <aknviewappui.h>
#include  <avkon.hrh>
#include  <Mp.rsg>
#include  <Mp.hrh>
#include  "View4.h"
#include  "Container4.h" 


// ================= MEMBER FUNCTIONS =======================

void CView4::ConstructL()
{
	BaseConstructL( R_MP_VIEW4 );

	iTextForegroundColour = TRgb(41,61,85); //KRgbBlack;
	iTextBackgroundColour = TRgb(179,204,230);
	iHighlightForegroundColour = TRgb(22,28,50); //KRgbBlack;
	iHighlightBackgroundColour = TRgb(233,235,255); //TRgb(0x80, 0x80, 0xFF);
}


CView4::~CView4()
{
	if ( iContainer )
	{
		AppUi()->RemoveFromViewStack( *this, iContainer );
		delete iContainer;
	}


}


TUid CView4::Id() const
{
	return KView4Id;
}


void CView4::HandleCommandL(TInt aCommand)
{   
	switch ( aCommand )
	{
	case EAknSoftkeyOk:
		{
			break;
		}
	case EAknSoftkeyBack:
		{
			TUid vId;
			vId.iUid = EMpViewMain;
			AppUi()->ActivateLocalViewL(vId);
			break;
		}
	default:
		{
			AppUi()->HandleCommandL( aCommand );
			break;
		}
	}
}


void CView4::HandleClientRectChange()
{
	if ( iContainer )
	{
		iContainer->SetRect( ClientRect() );
	}
}


void CView4::DoActivateL(const TVwsViewId& /*aPrevViewId*/,
						 TUid /*aCustomMessageId*/,
						 const TDesC8& /*aCustomMessage*/)
{
	if (!iContainer)
	{
		iContainer = new (ELeave) CContainer4;
		iContainer->SetMopParent(this);

		iContainer->SetColours(iTextForegroundColour, 
			iTextBackgroundColour,
			iHighlightForegroundColour,
			iHighlightBackgroundColour);

		iContainer->ConstructL( ClientRect() );
		AppUi()->AddToStackL( *this, iContainer );
	}
}


void CView4::DoDeactivate()
{
	if ( iContainer )
	{
		AppUi()->RemoveFromViewStack( *this, iContainer );
		delete iContainer;
		iContainer = NULL;
	}
}
