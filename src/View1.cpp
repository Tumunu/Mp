/*
============================================================================
Name        : View1 from MpView.h
Author      : Cleave Pokotea
Version     :
Copyright   : 2006 - 2007
Description : View1 implementation
============================================================================
*/

// INCLUDE FILES
#include  "MpAppUi.h"
#include  "View1.h"
#include  "Container1.h" 
#include "commondata.h"

#include  <aknviewappui.h>
#include  <avkon.hrh>
#include  <Mp.rsg>
#include  <Mp.hrh>

// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CView1::ConstructL(const TRect& aRect)
// EPOC two-phased constructor
// ---------------------------------------------------------
//
void CView1::ConstructL()
{
	BaseConstructL( R_MP_VIEW1 );
}

// ---------------------------------------------------------
// CView1::~View1()
// destructor
// ---------------------------------------------------------
//
CView1::~CView1()
{
	if ( iContainer )
	{
		AppUi()->RemoveFromViewStack( *this, iContainer );
		delete iContainer;
		iContainer = NULL;             
	}
}

// ---------------------------------------------------------
// TUid CView1::Id()
//
// ---------------------------------------------------------
//
TUid CView1::Id() const
{
	return KViewId;
}

// ---------------------------------------------------------
// CView1::HandleCommandL(TInt aCommand)
// takes care of view command handling
// ---------------------------------------------------------
//
void CView1::HandleCommandL(TInt aCommand)
{   
	switch ( aCommand )
	{
	case EAknSoftkeyOk:
		{
			TUid vId;
			vId.iUid = EMpViewMain;
			AppUi()->ActivateLocalViewL(vId);
			break;
		}
	case EAknSoftkeyBack:
		{
			_LIT(KUpdateUrl,"http://www.google.com/");
			iContainer->LaunchUpdate(KUpdateUrl);
			break;
		}
	default:
		{
			AppUi()->HandleCommandL( aCommand );
			break;
		}
	}
}

// ---------------------------------------------------------
// CView1::HandleClientRectChange()
// ---------------------------------------------------------
//
void CView1::HandleClientRectChange()
{
	if ( iContainer )
	{
		iContainer->SetRect( ClientRect() );
	}
}

// ---------------------------------------------------------
// CView1::DoActivateL(...)
// 
// ---------------------------------------------------------
//
void CView1::DoActivateL(
						  const TVwsViewId& /*aPrevViewId*/,TUid /*aCustomMessageId*/,
						  const TDesC8& /*aCustomMessage*/)
{
	if (!iContainer)
	{
		iContainer = new (ELeave) CContainer1;
		iContainer->SetMopParent(this);
		iContainer->ConstructL( ClientRect() );
		AppUi()->AddToStackL( *this, iContainer );
	} 
}

// ---------------------------------------------------------
// CView1::DoDeactivate()
// 
// ---------------------------------------------------------
//
void CView1::DoDeactivate()
{
	if ( iContainer )
	{
		AppUi()->RemoveFromViewStack( *this, iContainer );
	}

	delete iContainer;
	iContainer = NULL;
}



