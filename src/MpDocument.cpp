/*
============================================================================
Name        : CMpDocument from MpDocument.h
Author      : Cleave Pokotea
Version     :
Copyright   : 2006 - 2007
Description : CMpDocument implementation
============================================================================
*/

// INCLUDE FILES
#include "MpDocument.h"
#include "MpAppui.h"

// ================= MEMBER FUNCTIONS =======================

// constructor
CMpDocument::CMpDocument(CEikApplication& aApp)
: CAknDocument(aApp)    
{
}

// destructor
CMpDocument::~CMpDocument()
{
}

// EPOC default constructor can leave.
void CMpDocument::ConstructL()
{
}

// Two-phased constructor.
CMpDocument* CMpDocument::NewL(
							   CEikApplication& aApp)     // CMpApp reference
{
	CMpDocument* self = new (ELeave) CMpDocument( aApp );
	CleanupStack::PushL( self );
	self->ConstructL();
	CleanupStack::Pop();

	return self;
}

// ----------------------------------------------------
// CMpDocument::CreateAppUiL()
// constructs CMpAppUi
// ----------------------------------------------------
//
CEikAppUi* CMpDocument::CreateAppUiL()
{
	return new (ELeave) CMpAppUi;
}


