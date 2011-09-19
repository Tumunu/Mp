/*
============================================================================
 Name        : SplashView.h
 Author      : Cleave Pokotea
 Version     :
 Copyright   : 2006 - 2007
 Description : SplashView.h - header file
============================================================================
*/

#ifndef SPLASHVIEW_H
#define SPLASHVIEW_H

// INCLUDES
#include <aknview.h>


// CONSTANTS
// UID of view
const TUid KSplashId = {6};

// FORWARD DECLARATIONS
class CSplashContainer;

// CLASS DECLARATION
class CSplashView : public CAknView
{
public: 
	void ConstructL();
	~CSplashView();

public: // Functions from base classes

	/**
	* From CAknView returns Uid of View
	* @return TUid uid of the view
	*/
	TUid Id() const;

	/**
	* From MEikMenuObserver delegate commands from the menu
	* @param aCommand a command emitted by the menu 
	* @return void
	*/
	void HandleCommandL(TInt aCommand);

	/**
	* From CAknView reaction if size change
	* @return void
	*/
	void HandleClientRectChange();

private:
	// From MEikMenuObserver
	void DynInitMenuPaneL(TInt /* aResourceId */, CEikMenuPane* /* aMenuPane */);

	/**
	* From CAknView activate the view
	* @param aPrevViewId 
	* @param aCustomMessageId 
	* @param aCustomMessage 
	* @return void
	*/
	void DoActivateL(const TVwsViewId& aPrevViewId,TUid aCustomMessageId,
		const TDesC8& aCustomMessage);

	/**
	* From CAknView deactivate the view (free resources)
	* @return void
	*/
	void DoDeactivate();

private: // Data
	CSplashContainer* iContainer;
};

#endif