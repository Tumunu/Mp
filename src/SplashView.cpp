/*
============================================================================
Name        : CSplashView from SplashView.h
Author      : Cleave Pokotea
Version     :
Copyright   : 2006 - 2007
Description : Declares view for application.
============================================================================
*/

// INCLUDE FILES
#include "MpAppUi.h"
#include "MpDocument.h"
#include  "SplashView.h"
#include  "SplashContainer.h" 

#include  <aknviewappui.h>
#include  <Mp.rsg>

// ================= MEMBER FUNCTIONS =======================

void CSplashView::ConstructL()
{
	BaseConstructL( R_SPLASH_VIEW );
}


CSplashView::~CSplashView()
{
	if ( iContainer )
	{
		AppUi()->RemoveFromViewStack( *this, iContainer );
	}

	delete iContainer;
}


TUid CSplashView::Id() const
{
	return KSplashId;
}

void CSplashView::DynInitMenuPaneL(TInt /* aResourceId */,CEikMenuPane* /* aMenuPane */)
{}

void CSplashView::HandleCommandL(TInt aCommand)
{
	switch ( aCommand )
	{
	case EAknSoftkeyOk:
	case EAknSoftkeyBack:
	default:
		{
			break;
		}
	}
}


void CSplashView::HandleClientRectChange()
{
	if ( iContainer )
	{
		iContainer->SetRect( ClientRect() );
	}
}


void CSplashView::DoActivateL(
						 const TVwsViewId& /*aPrevViewId*/,TUid /*aCustomMessageId*/,
						 const TDesC8& /*aCustomMessage*/)
{
	if (!iContainer)
	{
		iContainer = new (ELeave) CSplashContainer;
		iContainer->SetMopParent(this);
		iContainer->ConstructL( ClientRect() );
		AppUi()->AddToStackL( *this, iContainer );
	} 
}


void CSplashView::DoDeactivate()
{
	if ( iContainer )
	{
		AppUi()->RemoveFromViewStack( *this, iContainer );
	}

	delete iContainer;
	iContainer = NULL;
}
