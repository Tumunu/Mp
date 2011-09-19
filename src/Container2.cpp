/*
============================================================================
Name        : CContainer2 from Container2.cpp
Author      : Cleave Pokotea
Version     :
Copyright   : 2006 - 2007
Description : Container control implementation
============================================================================
*/

// INCLUDE FILES
#include <eiktxlbm.h>
#include <eiklbv.h>
#include <aknutils.h> 
#include "commondata.h"
#include "Container2.h"
#include "MpApp.h"
#include "MpAppUi.h"
#include <gdi.h>

// ================= MEMBER FUNCTIONS =======================

void CContainer2::ConstructL(const TRect& aRect)
{
//__UHEAP_MARK;
	CreateWindowL();

	const CFont* font;
	font = CEikonEnv::Static()->NormalFont();

	// listbox instance
	iListBox = new (ELeave) CCustomListBox(font);
	iListBox->ConstructL(this, CEikListBox::EPaintedSelection);

	// Create the scrolling indicators at the bottom of the screen.
	iScrollBarFrame = iListBox->CreateScrollBarFrameL(ETrue);
	iListBox->ScrollBarFrame()->SetScrollBarVisibilityL(CEikScrollBarFrame::EAuto, CEikScrollBarFrame::EAuto);

	// set container class as an observer of the listbox
	iListBox->SetListBoxObserver(this);
	iListBox->SetObserver(this);

	CCustomListItemDrawer* iDwr = (CCustomListItemDrawer*) iListBox->View()->ItemDrawer();

	iDwr->SetColours(iTextForegroundColour, 
		iTextBackgroundColour, 
		iHighlightForegroundColour,
		iHighlightBackgroundColour);

	// Set the colour to be used in areas where there aren't any items in the list.
	iListBox->View()->SetBackColor(iTextBackgroundColour);
	iListBox->View()->ItemDrawer()->SetBackColor(iTextBackgroundColour);

	// Set the item height to a sensible value that can be used for all fonts.
	iListBox->SetItemHeightL(KItemHeight);

	// sets full screen
	SetRect( TRect( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT ) );
	SetBlank();

	// Set the list items
	InitListItemsL();

	ActivateL();
//__UHEAP_MARKEND;
}


CContainer2::~CContainer2()
{
	DELETE_AND_NULL(iListBox);
	//delete iListItems;
}


void CContainer2::SizeChanged()
{
	// This is important
	if (iListBox)
	{
		// Set rectangle of listbox.
		//iListBox->SetRect(Rect()); // sets listbox to full screen
		// leave space for blt
		iListBox->SetRect( TRect( 0, SCREEN_HEIGHT - (SCREEN_HEIGHT - BANNER_HEIGHT), SCREEN_WIDTH, SCREEN_HEIGHT - SOFTKEY_HEIGHT ) );
	}
}


void CContainer2::InitListItemsL()
{
	((CCustomListItemDrawer*) iListBox->View()->ItemDrawer())->ResetScrolling();

	iListItems = new (ELeave) CDesC16ArrayFlat(3);
	CleanupStack::PushL(iListItems);

	// NOTE: _L() is depreciated
	iListItems->AppendL (_L("Tumunu SMS"));
	iListItems->AppendL (_L("Activate | Play"));
	iListItems->AppendL (_L("Download SPEC"));

	// **
	iListBox->Model()->SetOwnershipType(ELbmOwnsItemArray);
	iListBox->Model()->SetItemTextArray(iListItems);
	iListBox->HandleItemAdditionL(); // Update listbox
	iListBox->SetCurrentItemIndex(0);
	iListBox->SetFocus(ETrue);

	CleanupStack::Pop(iListItems);
}


TInt CContainer2::CountComponentControls() const
{
	//return iCtrlArray.Count();
	if (iListBox)
		return 1;
	else
		return 0;
}


CCoeControl* CContainer2::ComponentControl(TInt aIndex) const
{
	//return (CCoeControl*)iCtrlArray[aIndex];
	switch ( aIndex )
	{
	case 0:
		return iListBox;
	default:
		return NULL;
	}
}


void CContainer2::Draw(const TRect& aRect) const
{
	CWindowGc& gc = SystemGc();

	TInt mainHeight = aRect.Height();
	TInt mainWidth = aRect.Width();
	TInt bkgndStartPoint = mainHeight - (mainHeight - BANNER_HEIGHT);
	TInt softkeyX = mainWidth - SOFTKEY_WIDTH;
	TInt softkeyY = mainHeight - SOFTKEY_HEIGHT + 2;

	gc.BitBlt(TPoint(0,0), ((CMpAppUi*)(CCoeEnv::Static()->AppUi()))->iSpriteHandler->GetSprite(MpowerShared::ESpriteHeaderIndex));
	gc.BitBlt(TPoint(0,bkgndStartPoint), ((CMpAppUi*)(CCoeEnv::Static()->AppUi()))->iSpriteHandler->GetSprite(MpowerShared::ESpriteBkgndDefault));

	gc.BitBlt(TPoint(0,softkeyY), ((CMpAppUi*)(CCoeEnv::Static()->AppUi()))->iSpriteHandler->GetSprite(MpowerShared::ESpriteSoftkeySelect));
	gc.BitBlt(TPoint(softkeyX,softkeyY), ((CMpAppUi*)(CCoeEnv::Static()->AppUi()))->iSpriteHandler->GetSprite(MpowerShared::ESpriteSoftkeyExit));
}

// ---------------------------------------------------------
// CContainer2::HandleControlEventL(
//     CCoeControl* aControl,TCoeEvent aEventType)
// ---------------------------------------------------------
//
void CContainer2::HandleControlEventL(CCoeControl* /*aControl*/,
									  TCoeEvent /*aEventType*/)
{

}

void CContainer2::SetColours(const TRgb& aTextForeground, 
							 const TRgb& aTextBackground,
							 const TRgb& aHighlightForeground, 
							 const TRgb& aHighlightBackground)
{
	iTextForegroundColour			= aTextForeground;
	iTextBackgroundColour			= aTextBackground;
	iHighlightForegroundColour		= aHighlightForeground;
	iHighlightBackgroundColour		= aHighlightBackground;

	if (iListBox)
	{
		CCustomListItemDrawer* iDwr = (CCustomListItemDrawer*) iListBox->View()->ItemDrawer();

		iDwr->SetColours(iTextForegroundColour,
			iTextBackgroundColour,
			iHighlightForegroundColour, 
			iHighlightBackgroundColour);

		iListBox->View()->SetBackColor(iTextBackgroundColour);
	}
}

/** 
* Override of the HandleListBoxEventL virtual function
*/
void CContainer2::HandleListBoxEventL(CEikListBox* aListBox, 
									  TListBoxEvent aListBoxEvent)
{
	if ((aListBoxEvent == MEikListBoxObserver::EEventEnterKeyPressed) ||
		(aListBoxEvent == MEikListBoxObserver::EEventItemClicked))
	{
		TUid vId;
		vId.iUid = iListBox->CurrentItemIndex()+ 3;
		((CMpAppUi*)(CCoeEnv::Static()->AppUi()))->ActivateLocalViewL(vId);
	};
}

TKeyResponse CContainer2::OfferKeyEventL(const TKeyEvent& aKeyEvent,
										 TEventCode aType)
{
	if ((aKeyEvent.iCode == EKeyUpArrow) || (aKeyEvent.iCode == EKeyDownArrow) || (aKeyEvent.iScanCode == 167) || (aKeyEvent.iScanCode == 164))
	{
		((CCustomListItemDrawer*) iListBox->View()->ItemDrawer())->ResetScrolling();
		return iListBox->OfferKeyEventL(aKeyEvent, aType);
	}

	return EKeyWasNotConsumed;
}
