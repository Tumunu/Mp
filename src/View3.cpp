/*
============================================================================
 Name        : View3.cpp
 Author      : Cleave Pokotea
 Version     :
 Copyright   : 2006 - 2007
 Description : View3.cpp - source file
============================================================================
*/

// INCLUDE FILES
#include  <aknviewappui.h>
#include  <avkon.hrh>
#include  <Mp.rsg>
#include  <Mp.hrh>
#include  "View3.h"
#include  "Container3.h" 

// ================= MEMBER FUNCTIONS =======================

void CView3::ConstructL()
{
	BaseConstructL( R_MP_VIEW2 );
}


CView3::~CView3()
{
	if ( iContainer )
	{
		AppUi()->RemoveFromViewStack( *this, iContainer );
	}

	delete iContainer;
}


TUid CView3::Id() const
{
	return KView3Id;
}


void CView3::HandleCommandL(TInt aCommand)
{   
	switch ( aCommand )
	{
	case EAknSoftkeyOk:
		{
			iEikonEnv->InfoMsg( _L("view2 ok") );
			break;
		}
	case EAknSoftkeyBack:
		{
			TUid vId;
			vId.iUid = EMpViewMain;
			AppUi()->ActivateLocalViewL(vId);
		}
	default:
		{
			AppUi()->HandleCommandL( aCommand );
			break;
		}
	}
}


void CView3::HandleClientRectChange()
{
	if ( iContainer )
	{
		iContainer->SetRect( ClientRect() );
	}
}


void CView3::DoActivateL(const TVwsViewId& /*aPrevViewId*/,
						 TUid /*aCustomMessageId*/,
						 const TDesC8& /*aCustomMessage*/)
{
	if (!iContainer)
	{
		iContainer = new (ELeave) CContainer3;
		iContainer->SetMopParent(this);
		iContainer->ConstructL( ClientRect() );
		AppUi()->AddToStackL( *this, iContainer );
	}
}


void CView3::DoDeactivate()
{
	if ( iContainer )
	{
		AppUi()->RemoveFromViewStack( *this, iContainer );
		delete iContainer;
		iContainer = NULL;
	}
}
