/*
============================================================================
Name        : CMpAppUi from MpAppui.h
Author      : Cleave Pokotea
Version     :
Copyright   : 2006 - 2007
Description : Declares UI class for application.
============================================================================
*/

#ifndef MPAPPUI_H
#define MPAPPUI_H

// INCLUDES
#include <aknviewappui.h>
#include <akntabgrp.h>
#include <aknnavide.h>

#include <akntabobserver.h>
#include "SpriteHandler.h"
//#include "HeapDump.h"

// FORWARD DECLARATIONS
class CMpContainer;
class CContainer2;
class CContainer4;


const TInt KFullScreenWidth = 176;
const TInt KFullScreenHeight = 188; // 208?

// CLASS DECLARATION

/**
* Application UI class.
* Provides support for the following features:
* - EIKON control architecture
* - view architecture
* - status pane
* 
*/
class CMpAppUi : public CAknViewAppUi//, MAknTabObserver
{
public: // // Constructors and destructor

	/**
	* EPOC default constructor.
	*/      
	void ConstructL();

	/**
	* Destructor.
	*/      
	~CMpAppUi();

public: // New functions

public: // Functions from base classes

	/**
	* Class that stores and manages the sprite bitmaps.
	*/
	CSpriteHandler* iSpriteHandler;

private:
	// From MEikMenuObserver
	void DynInitMenuPaneL(TInt aResourceId,CEikMenuPane* aMenuPane);

private:
	/**
	* From CEikAppUi, takes care of command handling.
	* @param aCommand command to be handled
	*/
	void HandleCommandL(TInt aCommand);

	/**
	* From CEikAppUi, handles key events.
	* @param aKeyEvent Event to handled.
	* @param aType Type of the key event. 
	* @return Response code (EKeyWasConsumed, EKeyWasNotConsumed). 
	*/
	virtual TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

private: //Data

};

#endif


