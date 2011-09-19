/*
============================================================================
 Name        : View3.h
 Author      : Cleave Pokotea
 Version     :
 Copyright   : 2006 - 2007
 Description : View3.h - header file
============================================================================
*/

#ifndef VIEW3_H
#define VIEW3_H

// INCLUDES
#include <aknview.h>

// CONSTANTS
// UID of view
const TUid KView3Id = {3};

// FORWARD DECLARATIONS
class CContainer3;

// CLASS DECLARATION

/**
*  CView3 view class.
* 
*/
class CView3 : public CAknView
{
public: // Constructors and destructor

	/**
	* EPOC default constructor.
	*/
	void ConstructL();

	/**
	* Destructor.
	*/
	~CView3();

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
	CContainer3* iContainer;
};

#endif // VIEW3_H

// End of File
