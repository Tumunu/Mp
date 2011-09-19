/*
============================================================================
Name        : CMpApp from MpApp.cpp
Author      : Cleave Pokotea
Version     :
Copyright   : 2006 - 2007
Description : Main application class
============================================================================
*/

// INCLUDE FILES
#include    "MpApp.h"
#include    "MpDocument.h"

// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CMpApp::AppDllUid()
// Returns application UID
// ---------------------------------------------------------
//
TUid CMpApp::AppDllUid() const
{
	return KUidMp;
}


// ---------------------------------------------------------
// CMpApp::CreateDocumentL()
// Creates CMpDocument object
// ---------------------------------------------------------
//
CApaDocument* CMpApp::CreateDocumentL()
{
	return CMpDocument::NewL( *this );
}

// ================= OTHER EXPORTED FUNCTIONS ==============
//
// ---------------------------------------------------------
// NewApplication() 
// Constructs CMpApp
// Returns: created application object
// ---------------------------------------------------------
//
EXPORT_C CApaApplication* NewApplication()
{
	return new CMpApp;
}

// ---------------------------------------------------------
// E32Dll(TDllReason) 
// Entry point function for EPOC Apps
// Returns: KErrNone: No error
// ---------------------------------------------------------
//
GLDEF_C TInt E32Dll( TDllReason )
{
	return KErrNone;
}



