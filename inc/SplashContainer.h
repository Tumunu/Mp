/*
============================================================================
 Name        : SplashContainer.h
 Author      : Cleave Pokotea
 Version     :
 Copyright   : 2006 - 2007
 Description : SplashContainer.h - header file
============================================================================
*/

#ifndef SPLASHCONTAINER_H
#define SPLASHCONTAINER_H

// INCLUDES
#include <coecntrl.h>

// FORWARD DECLARATIONS
class CFbsBitmap;

// CLASS DECLARATION

/**
*  CSplashContainer  container control class.
*  
*/
class CSplashContainer : public CCoeControl, MCoeControlObserver
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
	 ~CSplashContainer();

public: // New functions
	/**
	* Draw Function
	*/
	 void DrawSplash(const TRect& aRect) const;

	/**
	* Timer management function
	*/
	 TBool Tick();
	 static TInt Period(TAny* aPtr);
	 void DoPeriod();

	 void StartTimer();
	 void StopTimer();

	 void SetTimerTick(TTimeIntervalMicroSeconds32  aTick);

	enum TState 
	{
		ESplash,
		EMain,
	};
	 void SetState(CSplashContainer::TState aState);
	 CSplashContainer::TState State();

public: // Functions from base classes

private: // New Functions

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

	 void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);


private: //data

	TState iState;
	CPeriodic* iPeriodicTimer;
	TTimeIntervalMicroSeconds32  iTick;

private: //data
	TInt iColorCount;
	TInt iPreCount;
	TInt iPostCount;
	CFbsBitmap*			iSplashBitmap;
};

#endif

// End of File
