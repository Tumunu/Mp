/*
============================================================================
 Name        : Spec.h
 Author      : Cleave Pokotea
 Version     :
 Copyright   : 2006 - 2007
 Description : Spec.h - header file
============================================================================
*/

#ifndef SPEC_H
#define SPEC_H

// INCLUDES
// System Includes
#include <e32base.h>  // CBase, link against euser.lib
#include <gdi.h>

// FORWARD DECLARATIONS


// CLASS DECLARATION
/*
TButton
*/
class TButton
{
public:
	TButton(const TDesC& aButtonId, const TDesC& aText, TInt aX, TInt aY, const TDesC& aAction, TInt aWidth, TInt aHeight);

private:
	HBufC* iButtonId;
	HBufC* iText;
	TInt iX;
	TInt iY;
	HBufC* iAction;

	TInt iWidth; 
	TInt iHeight;
};


/*
TImg
*/
class TImg
{
public:
	TImg(const TDesC& aImgsId, const TDesC& aUrl, TInt aX, TInt aY, TInt aWidth, TInt aHeight);

private:
	HBufC* iImgsId;
	HBufC* iUrl;
	TInt iX;
	TInt iY;

	TInt iWidth; 
	TInt iHeight;
};


/*
TLabel
*/
class TLabel
{
public:
	TLabel(const TDesC& aLabelId, const TDesC& aText, TInt aX, TInt aY, TInt aWidth, TInt aHeight);
	
private:
	HBufC* iLabelId; 
	HBufC* iText; 
	TInt iX; 
	TInt iY;

	TInt iWidth; 
	TInt iHeight;
};


/*
TDefaultMenu
*/
class TDefaultMenu
{
public:
	TDefaultMenu(const TDesC& aDefaultMenuId, const TDesC& aText, const TDesC& aAction);

private:
	HBufC* iDefaultMenuId;
	HBufC* iText;
	HBufC* iAction;
};


/*
TOptionMenu
*/
class TOptionMenu
{
public:
	TOptionMenu(const TDesC& aOptionMenuId, const TDesC& aText, const TDesC& aAction);

private:
	HBufC* iOptionMenuId;
	HBufC* iText;
	HBufC* iAction;
};


/*
CSpecPage
*/
class CSpecPage : CBase
{
public:
	static CSpecPage* NewLC(const TDesC& aPageId, const TRgb aBkgndColour, TInt aMinTime, TInt aMaxTime, TBool aBackNavigation = EFalse);
	CSpecPage();
	virtual ~CSpecPage();

	/*
	Default layout getter functions
	*/
	const TDesC& PageId() const;
	TRgb BackgroundColour() const;
	TInt MinTime() const;
	TInt MaxTime() const;
	TBool BackNavigation() const;

	/*
	Access stored arrays to render layout
	*/
	RArray<TButton> Buttons() const;
	RArray<TImg> Images() const;
	RArray<TLabel> Labels() const;
	RArray<TDefaultMenu> DefaultMenu() const;
	RArray<TOptionMenu> OptionMenu() const;

	/*
	AddToButtons(TButton aButton);
	AddToImgs(TImg aImg);
	AddToLabel(TLabel aLabel);
	AddToDefaultMenu(TDefaultMenu aDf);
	AddToOptionMenu(TOptionMenu aOm);
	*/

public:
	void ExternalizeL(RWriteStream& aStream) const;
	void InternalizeL(RReadStream& aStream);

private:
	void ConstructL(const TDesC& aPageId, const TRgb aBkgndColour, TInt aMinTime, TInt aMaxTime, TBool aBackNavigation);

private:
	HBufC* iPageId;
	TRgb iBkgndColour; // if not defined default is 'white'
	TInt iMinTime;
	TInt iMaxTime;
	TBool iBackNavigation;

	RArray<TButton> iButtons;
	RArray<TImg> iImages;
	RArray<TLabel> iLabels;
	RArray<TDefaultMenu> iDefaultMenu;
	RArray<TOptionMenu> iOptionMenu;
};

#endif // SPEC_H

// End of File
