/*
============================================================================
Name        : CMpApp from MpApp.h
Author      : Cleave Pokotea
Version     :
Copyright   : 2006 - 2007
Description : Declares main application class.
============================================================================
*/

#ifndef MPAPP_H
#define MPAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
// UID of the application
const TUid KUidMp = { 0x0165a237 };

// CLASS DECLARATION

/**
* CMpApp application class.
* Provides factory to create concrete document object.
* 
*/
class CMpApp : public CAknApplication
{

public: // Functions from base classes
private:

	/**
	* From CApaApplication, creates CMpDocument document object.
	* @return A pointer to the created document object.
	*/
	CApaDocument* CreateDocumentL();

	/**
	* From CApaApplication, returns application's UID (KUidMp).
	* @return The value of KUidMp.
	*/
	TUid AppDllUid() const;
};

#endif



