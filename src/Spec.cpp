/*
============================================================================
Name        : Spec.cpp
Author      : Cleave Pokotea
Version     :
Copyright   : 2006 - 2007
Description : Spec.cpp - source file
============================================================================
*/

// INCLUDE FILES
// Class include
#include "Spec.h"

// System includes
#include <gdi.h>

// User includes

// ================= MEMBER FUNCTIONS =======================
CSpecPage* CSpecPage::NewLC(const TDesC& aPageId, const TRgb aBkgndColour, TInt aMinTime, TInt aMaxTime, TBool aBackNavigation)
{
	CSpecPage* self = new (ELeave) CSpecPage;
	CleanupStack::PushL(self);
	self->ConstructL(aPageId, aBkgndColour, aMinTime, aMaxTime, aBackNavigation);
	return self;
}

CSpecPage::CSpecPage()
{

}

void CSpecPage::ConstructL(const TDesC& aPageId, const TRgb aBkgndColour, TInt aMinTime, TInt aMaxTime, TBool aBackNavigation)
{
	iPageId = aPageId.AllocL();
	iBkgndColour = aBkgndColour;
	iMinTime = aMinTime;
	iMaxTime = aMaxTime;
	iBackNavigation = aBackNavigation;
}

CSpecPage::~CSpecPage()
{
	if(iPageId)
		delete iPageId;
}

// End of File
