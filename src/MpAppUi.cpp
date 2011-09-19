/*
============================================================================
Name        : CMpAppUi from MpAppui.cpp
Author      : Cleave Pokotea
Version     :
Copyright   : 2006 - 2007
Description : CMpAppUi implementation
============================================================================
*/

// INCLUDE FILES
#include <eikbtgpc.h>
#include <avkon.rsg>
#include <avkon.hrh>
#include "commondata.h"
#include "SpriteHandler.h"
#include "MpAppui.h"
#include "SplashView.h"
#include "View1.h"
#include "View2.h"
#include "View3.h"
#include "View4.h"
#include <Mp.rsg>
#include "Mp.hrh"


_LIT(KNewDir,"\\Mp\\Cache\\");

// ================= MEMBER FUNCTIONS =======================

void CMpAppUi::ConstructL()
{
	BaseConstructL();

	//// Initialize graphics
	//iSpriteHandler = CSpriteHandler::NewL();

	CView1* view1 = new (ELeave) CView1;

	CleanupStack::PushL( view1 );
	view1->ConstructL();
	AddViewL( view1 );      // transfer ownership to CAknViewAppUi
	CleanupStack::Pop();    // view1

	CView2* view2 = new (ELeave) CView2;

	CleanupStack::PushL( view2 );
	view2->ConstructL();
	AddViewL( view2 );
	CleanupStack::Pop(); 

	CView3* view3 = new (ELeave) CView3;

	CleanupStack::PushL( view3 );
	view3->ConstructL();
	AddViewL( view3 );
	CleanupStack::Pop(); 

	CView4* view4 = new (ELeave) CView4;

	CleanupStack::PushL( view4 );
	view4->ConstructL();
	AddViewL( view4 );
	CleanupStack::Pop(); 

	CSplashView* splash = new (ELeave) CSplashView;

	CleanupStack::PushL( splash );
	splash->ConstructL();
	AddViewL( splash );     
	CleanupStack::Pop();  

	//SetDefaultViewL(*view1);
	SetDefaultViewL(*splash);

	// Initialize graphics
	iSpriteHandler = CSpriteHandler::NewL();
}


CMpAppUi::~CMpAppUi()
{
	if (iSpriteHandler)
	{
		delete iSpriteHandler;
		iSpriteHandler = NULL;
	}
}


void CMpAppUi::DynInitMenuPaneL(TInt /*aResourceId*/,CEikMenuPane* /*aMenuPane*/)
{
}


TKeyResponse CMpAppUi::HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
{
	TKeyResponse keyResponse = EKeyWasNotConsumed;

	if(aType != EEventKey)
	{
		return keyResponse;
	}

	switch (aKeyEvent.iCode)
	{
	case EKeyOK:
		{
			ActivateLocalViewL(KView2Id);
			keyResponse = EKeyWasConsumed;
			break;
		}
	default:
		{
			keyResponse = EKeyWasNotConsumed;
			break;
		}
	}
	return keyResponse;
}


void CMpAppUi::HandleCommandL(TInt aCommand)
{
	switch ( aCommand )
	{
	case EEikCmdExit:
		{
			Exit();
			break;
		}
	default:
		break;      
	}
}