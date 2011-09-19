/*
============================================================================
Name        : CustomListBox.cpp
Author      : Cleave Pokotea
Version     :
Copyright   : 2006 - 2007
Description : CustomListBox.cpp - source file
============================================================================
*/

// INCLUDE FILES
#include <gdi.h>
#include <eiktxlbm.h>
#include <AknUtils.h>
#include "CustomListBox.h"
#include "MpAppUi.h"

/*
CustomListBoxView
*/
CCustomListBoxView::CCustomListBoxView()
{
}

void CCustomListBoxView::DrawEmptyList(const TRect &aClientRect) const
{
	AknDraw::DrawEmptyList(aClientRect, *iGc, iListEmptyText->Des());
}

void CCustomListBoxView::Draw(const TRect* aClipRect) const
{
	if (iModel->NumberOfItems() > 0)
		CListBoxView::Draw(aClipRect);
	else
		DrawEmptyList(iViewRect);
}

/*
CustomListItemDrawer
*/
CCustomListItemDrawer::CCustomListItemDrawer(MTextListBoxModel* aTextListBoxModel, const CFont* aFont): CTextListItemDrawer(aTextListBoxModel, aFont),
iPersistentFont(aFont)
{
}

void CCustomListItemDrawer::DrawActualItem(TInt aItemIndex, 
										   const TRect& aActualItemRect,
										   TBool aItemIsCurrent, 
										   TBool /*aViewIsEmphasized*/,
										   TBool,
										   TBool /*aItemIsSelected*/) const
{
	TRgb textColour;
	TRgb bgColour;

	/*
	We need to set the font every time, because AknDraw::DrawEmptyList() resets 
	it to the standard size
	*/
	Gc()->UseFont(iPersistentFont);

	if (aItemIsCurrent)
	{
		textColour = iHighlightForegroundColour;
		bgColour = iHighlightBackgroundColour;

		// Outer edges of item
		Gc()->SetBrushStyle(CGraphicsContext::ESolidBrush);
		//Gc()->SetBrushColor(iTextBackgroundColour);
		//Gc()->DrawRect(aActualItemRect);

		// Rounded corners
		TSize roundedEdge(12,12);
		Gc()->SetBrushColor(bgColour);
		Gc()->DrawRoundRect(aActualItemRect, roundedEdge);
	}
	else
	{
		textColour = iTextForegroundColour;
		bgColour = iTextBackgroundColour;

		// Set the item's background.
		Gc()->SetBrushStyle(CGraphicsContext::ESolidBrush);
		Gc()->SetBrushColor(bgColour);
		Gc()->SetPenColor(bgColour);
	}

	// Draw the item's text.
	Gc()->SetPenColor(textColour);

	/*
	If this item is currently being scrolled, then select some of it. Otherwise, 
	use the entire string. Some spaces are always prepended as well
	*/
	TBuf<256> displayBuf;
	if (aItemIsCurrent)
		displayBuf = iModel->ItemText(aItemIndex).Mid(iScrollOffset);
	else
		displayBuf = iModel->ItemText(aItemIndex);
	displayBuf.Insert(0, _L("  "));

	TInt margin = 0;
	Gc()->DrawText(displayBuf, 
		aActualItemRect, 
		(aActualItemRect.Height() / 2) + (iFont->AscentInPixels() / 2), 
		CGraphicsContext::ECenter,
		margin);

	// Set the pen to the colour of the background, so there isn't a visible frame around the item.
	Gc()->SetPenColor(bgColour);
}

void CCustomListItemDrawer::SetColours(const TRgb& aTextForeground, const TRgb& aTextBackground,
									   const TRgb& aHighlightForeground, const TRgb& aHighlightBackground)
{
	iTextForegroundColour = aTextForeground;
	iTextBackgroundColour = aTextBackground;
	iHighlightForegroundColour = aHighlightForeground;
	iHighlightBackgroundColour = aHighlightBackground;

	iBackColor = iTextBackgroundColour;
}

TBool CCustomListItemDrawer::ScrollSpec(TInt aItemIndex)
{
	TBuf<256> displayBuf;

	displayBuf = iModel->ItemText(aItemIndex);
	displayBuf.Insert(0, _L("  "));

	/*
	Check that the name fits into the space available. If not, we scroll it. There's
	a small delay at the beginning and end of scrolling
	*/
	TInt trackNameChars = iPersistentFont->TextCount(displayBuf, KFullScreenWidth);
	if (trackNameChars < displayBuf.Length())
	{
		iScrollOffset += 2;

		if (iScrollOffset > (displayBuf.Length() - (trackNameChars + 1)))
			iScrollOffset = 0;

		return ETrue;
	}

	return EFalse;
}

void CCustomListItemDrawer::ResetScrolling()
{
	iScrollOffset = 0;
}

/*
CCustomListBox
*/
CCustomListBox::CCustomListBox(const CFont* aFont)
{
	iFont = aFont;
}

void CCustomListBox::CreateItemDrawerL()
{
	iItemDrawer = new (ELeave) CCustomListItemDrawer(Model(), iFont);
}

CListBoxView* CCustomListBox::MakeViewClassInstanceL()
{
	return new (ELeave) CCustomListBoxView();
}

// End of File
