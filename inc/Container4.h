/*
============================================================================
Name        : CContainer4 from Container4.h
Author      : Cleave Pokotea
Version     :
Copyright   : 2006 - 2007
Description : Declares container control for application.
============================================================================
*/

#ifndef Container4_H
#define Container4_H

// INCLUDES
#include <coecntrl.h>
#include <eikenv.h>
#include "CustomListBox.h"

// FORWARD DECLARATIONS
class MEikCommandObserver;	

// CLASS DECLARATION

/**
*  CContainer4  container control class.
*  
*/
class CContainer4 : public CCoeControl, MCoeControlObserver, MEikListBoxObserver
{
public: // Constructors and destructor

	/**
	* EPOC default constructor.
	* @param aRect Frame rectangle for container.
	*/
	void ConstructL(const TRect& aRect);

	/**
	* Destructor.
	*/
	~CContainer4();

public: // New functions
	void CreateDir();

	void SetColours(const TRgb& aTextForeground, 
		const TRgb& aTextBackground,
		const TRgb& aHighlightForeground, 
		const TRgb& aHighlightBackground);

	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);

public: // Functions from base classes

private: // Functions from base classes

	/**
	* From CoeControl,SizeChanged.
	*/
	void SizeChanged();

	/**
	* From CoeControl,CountComponentControls.
	*/
	TInt CountComponentControls() const;

	/**
	* From CCoeControl,ComponentControl.
	*/
	CCoeControl* ComponentControl(TInt aIndex) const;

	/**
	* From CCoeControl,Draw.
	*/
	void Draw(const TRect& aRect) const;

	/**
	* From MCoeControlObserver
	* Acts upon changes in the hosted control's state. 
	*
	* @param	aControl	The control changing its state
	* @param	aEventType	The type of control event 
	*/
	void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);

	virtual void HandleListBoxEventL(CEikListBox* aListBox, TListBoxEvent aEventType);
	void InitListItemsL();

private: //data

	CCustomListBox* iListBox;
	CEikScrollBarFrame* iScrollBarFrame;
	CDesC16ArrayFlat* iListItems;

	TRgb iTextForegroundColour;
	TRgb iTextBackgroundColour;
	TRgb iHighlightForegroundColour;
	TRgb iHighlightBackgroundColour;
};

#endif


