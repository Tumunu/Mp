/*
============================================================================
Name        : CMpDocument from MpDocument.h
Author      : Cleave Pokotea
Version     :
Copyright   : 2006 - 2007
Description : Declares document for application.
============================================================================
*/

#ifndef MPDOCUMENT_H
#define MPDOCUMENT_H

// INCLUDES
#include <akndoc.h>

// CONSTANTS

// FORWARD DECLARATIONS
class  CEikAppUi;

// CLASS DECLARATION

/**
*  CMpDocument application class.
*/
class CMpDocument : public CAknDocument
{
public: // Constructors and destructor
	/**
	* Two-phased constructor.
	*/
	static CMpDocument* NewL(CEikApplication& aApp);

	/**
	* Destructor.
	*/
	virtual ~CMpDocument();

public: // New functions

public: // Functions from base classes
protected:  // New functions

protected:  // Functions from base classes

private:

	/**
	* EPOC default constructor.
	*/
	CMpDocument(CEikApplication& aApp);
	void ConstructL();

private:

	/**
	* From CEikDocument, create CMpAppUi "App UI" object.
	*/
	CEikAppUi* CreateAppUiL();
};

#endif
