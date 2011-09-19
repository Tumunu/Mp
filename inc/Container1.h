/*
============================================================================
Name        : CContainer1 from MpContainer.h
Author      : Cleave Pokotea
Version     :
Copyright   : 2006 - 2007
Description : Declares container control for application.
============================================================================
*/

#ifndef MPCONTAINER_H
#define MPCONTAINER_H

// INCLUDES
#include <coecntrl.h>

// FORWARD DECLARATIONS
class CEikLabel;        // for example labels

// CLASS DECLARATION

/**
*  CContainer1  container control class.
*  
*/
class CContainer1 : public CCoeControl, MCoeControlObserver
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
	~CContainer1();

public: // New functions
	void LaunchUpdate(const TDesC& aUrl) const;

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

private: //data
	RPointerArray<CCoeControl> iCtrlArray;

	CEikLabel* iTopLabel;
	CEikLabel* iBottomLabel;


};

#endif


