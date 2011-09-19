/*
============================================================================
Name        : CSplashContainer from SplashContainer.h
Author      : Cleave Pokotea
Version     :
Copyright   : 2006 - 2007
Description : Declares container for application.
============================================================================
*/

// INCLUDE FILES
// Class include
#include "SplashContainer.h"
#include "MpDocument.h"
#include "MpAppUi.h"
#include <bautils.h>
#include <Mp.hrh>
#include "Mpower.mbg"

_LIT(KDrawBitmapPath, "\\system\\apps\\Mp\\Mpower.mbm");
const TInt KTopLeftX = 0;
const TInt KTopLeftY = 0;
const TInt KSizeWidth = 176;
const TInt KSizeHeight = 208;

// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CSplashContainer::ConstructL(const TRect& aRect)
// EPOC two phased constructor
// ---------------------------------------------------------
//
void CSplashContainer::ConstructL(const TRect& aRect)
{

	// Initialise mode to Splash.
	iState=CSplashContainer::ESplash;
	//iTick = 3000000;

	// Create a periodic timer but don't start it yet
	iPeriodicTimer = CPeriodic::NewL(CActive::EPriorityStandard);

	SetTimerTick(100000);
	iPreCount  =10;
	iColorCount=255;
	iPostCount =28;

	StartTimer();
	CreateWindowL();
	SetRect(aRect);
	SetExtentToWholeScreen();

	TFileName bitmapFile (KDrawBitmapPath);
	User::LeaveIfError (CompleteWithAppPath (bitmapFile));

	iSplashBitmap = new (ELeave) CFbsBitmap();
	User::LeaveIfError(iSplashBitmap->Load(bitmapFile, EMbmMpowerSplash));

	ActivateL();
}

// Destructor
CSplashContainer::~CSplashContainer()
{
	StopTimer();
	delete iPeriodicTimer;
	iPeriodicTimer = NULL;
	delete iSplashBitmap;
}

// ---------------------------------------------------------
// CSplashContainer::SizeChanged()
// Called by framework when the view size is changed
// ---------------------------------------------------------
//
void CSplashContainer::SizeChanged()
{
}

// ---------------------------------------------------------
// CSplashContainer::CountComponentControls() const
// ---------------------------------------------------------
//
TInt CSplashContainer::CountComponentControls() const
{
	return 0;
}

// ---------------------------------------------------------
// CSplashContainer::ComponentControl(TInt aIndex) const
// ---------------------------------------------------------
//
CCoeControl* CSplashContainer::ComponentControl(TInt /*aIndex*/) const
{
	return NULL;
}

// ---------------------------------------------------------
// CSplashContainer::Draw(const TRect& aRect) const
// ---------------------------------------------------------
//
void CSplashContainer::Draw(const TRect& aRect) const
{
	switch(iState)
	{
	case CSplashContainer::ESplash:
		DrawSplash(aRect);
		break;
	/* debug */
	case CSplashContainer::EMain:
		break;
	default:
		// shouldn't reach here
		break;
	}
}

void CSplashContainer::DrawSplash(const TRect& /*aRect*/) const
{
	CWindowGc& gc = SystemGc();
	TRect    rect = Rect();

	TPoint topLeft(KTopLeftX, KTopLeftY);
	TSize bitmapSize(KSizeWidth, KSizeHeight);
	gc.DrawBitmap(TRect(topLeft, bitmapSize), iSplashBitmap);	
}

// ---------------------------------------------------------
// CSplashContainer::SetState(CSplashContainer::TState aState) 
// Change the mode of the container (possible values are
// ESplash, EMain, EExiting)
// ---------------------------------------------------------
//
void CSplashContainer::SetState(CSplashContainer::TState aState)
{
	iState=aState;
}

// ---------------------------------------------------------
// CSplashContainer::State() 
// Get the current mode. 
// ---------------------------------------------------------
//
CSplashContainer::TState CSplashContainer::State()
{
	return iState;
}

// ---------------------------------------------------------
// CSplashContainer::SetTimerTick(TTimeIntervalMicroSeconds32  aTick) 
// Set the Tick value (duration between two screen redraw)
// ---------------------------------------------------------
//
void CSplashContainer::SetTimerTick(TTimeIntervalMicroSeconds32  aTick)
{
	iTick=aTick;
}


// ---------------------------------------------------------
// CSplashContainer::DoPeriod() 
// Function that is called periodically by the timer.
// Call the child Tick() treatment and request a screen 
// redraw if needed.
// ---------------------------------------------------------
//
void CSplashContainer::DoPeriod()
{
	if (Tick())
	{
		CWindowGc& gc = SystemGc();
		gc.Activate(*DrawableWindow());
		Draw(Rect());
		gc.Deactivate();
	}
	else
	{
		TUid viewId;
		//viewId.iUid = EMpViewSplash;
		viewId.iUid = EMpViewIndex;
		((CMpAppUi*)(CCoeEnv::Static()->AppUi()))->ActivateLocalViewL(viewId);
	}
}

// This function is called by the periodic timer
TInt CSplashContainer::Period(TAny * aPtr)
{
	((CSplashContainer*)aPtr)->DoPeriod();
	return TRUE;
}

// ---------------------------------------------------------
// CSplashContainer::StartTimer() 
// Start the timer (required for animated SplashScreen)
// Optional but useful for static ones.
// ---------------------------------------------------------
//
void CSplashContainer::StartTimer()
{
	//If the timer is not already running, start it
	if (!iPeriodicTimer->IsActive())
	{
		iPeriodicTimer->Start(iTick,iTick,TCallBack(CSplashContainer::Period,this));
	}
}

// ---------------------------------------------------------
// CSplashContainer::StopTimer() 
// 
// ---------------------------------------------------------
//
void CSplashContainer::StopTimer()
{
	//Stop the timer if it is active
	if (iPeriodicTimer->IsActive())
	{
		iPeriodicTimer->Cancel();
	}
}

TBool CSplashContainer::Tick()
{
	//
	// Start by precount
	// (during precount iColorCount is zero, so splash text will be displayed
	// in black and then not visible)
	if(iPreCount>0)
	{
		iPreCount--;
	}
	//
	// After PreCount, fade the text to white with a 15 increment.
	//
	//else if(iColorCount<255) 
	else if(iColorCount>0) 
	{
		iColorCount-=15;
	}
	//
	// When the text is white, wait for iPostCount Tick before switching
	// to main state
	//
	else if(iPostCount>0)
	{
		iPostCount--;
	}
	else
	{
		//SetState(CSplashContainer::EMain);
		StopTimer();
		return EFalse;
	}
	return ETrue;
}


void CSplashContainer::HandleControlEventL(CCoeControl* /*aControl*/,TCoeEvent /*aEventType*/)
{
	// TODO: Add your control event handler code here
}


// End of File  
