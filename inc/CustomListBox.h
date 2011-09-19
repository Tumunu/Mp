/*
============================================================================
Name        : CustomListBox.h
Author      : Cleave Pokotea
Version     :
Copyright   : 2006 - 2007
Description : CustomListBox.h - header file
============================================================================
*/

#ifndef CUSTOMLISTBOX_H
#define CUSTOMLISTBOX_H

// INCLUDES
#include <coecntrl.h>
#include <eikenv.h>
#include <eiktxlbx.h> // CEikTextListBox
#include <eiklbi.h> //CListItemDrawer

// CLASS DECLARATION


class CmpowerAppUi;
class CDirTree;

const TInt KItemHeight = 20;

class CCustomListBoxView : public CListBoxView
{
public:
	CCustomListBoxView();

	virtual void DrawEmptyList(const TRect &aClientRect) const;
	virtual void Draw(const TRect* aClipRect) const;
};

/*
The class which is responsible for drawing the items. It needs to exist because 
CTextListItemDrawer doesn't give us enough control over the appearance of the 
text that's drawn
*/
class CCustomListItemDrawer : public CTextListItemDrawer
{
public:
	CCustomListItemDrawer(MTextListBoxModel* aTextListBoxModel, const CFont* aFont);

	virtual void DrawActualItem(TInt aItemIndex, const TRect& aActualItemRect, TBool aItemIsCurrent,
		TBool aViewIsEmphasized, TBool, TBool aItemIsSelected) const;

	void SetColours(const TRgb& aTextForeground, const TRgb& aTextBackground,
		const TRgb& aHighlightForeground, const TRgb& aHighlightBackground);

	TBool ScrollSpec(TInt aItemIndex);
	void ResetScrolling();

private:
	TRgb iTextForegroundColour;
	TRgb iTextBackgroundColour;
	TRgb iHighlightForegroundColour;
	TRgb iHighlightBackgroundColour;

	const CFont* iPersistentFont;

	TInt iScrollOffset;
};

/*
only responsibility is to look after CCustomListItemDrawer
*/
class CCustomListBox : public CEikTextListBox
{
public:
	CCustomListBox(const CFont* aFont);

protected:
	virtual void CreateItemDrawerL();
	virtual CListBoxView* MakeViewClassInstanceL();

private:
	const CFont* iFont;
};

#endif // CUSTOMLISTBOX_H

// End of File
