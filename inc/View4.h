/*
============================================================================
Name        : View4 from MpView4.h
Author      : Cleave Pokotea
Version     :
Copyright   : 2006 - 2007
Description : Declares view for application.
============================================================================
*/

#ifndef MPView4_H
#define MPView4_H

// INCLUDES
#include <aknview.h>

// CONSTANTS
// UID of view
const TUid KView4Id = {4};

// FORWARD DECLARATIONS
class CContainer4;

// CLASS DECLARATION

/**
*  CView4 view class.
* 
*/
class CView4 : public CAknView
{
public: // Constructors and destructor

	/**
	* EPOC default constructor.
	*/
	void ConstructL();

	/**
	* Destructor.
	*/
	~CView4();

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
	CContainer4* iContainer;

	TRgb iTextForegroundColour;
	TRgb iTextBackgroundColour;
	TRgb iHighlightForegroundColour;
	TRgb iHighlightBackgroundColour;
};

#endif


