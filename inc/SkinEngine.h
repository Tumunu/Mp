/*
============================================================================
 Name        : SkinEngine.h
 Author      : Cleave Pokotea
 Version     :
 Copyright   : 2006 - 2007
 Description : SkinEngine.h - header file
============================================================================
*/

#ifndef SKINENGINE_H
#define SKINENGINE_H

// INCLUDES
// System Includes
#include <MdaImageConverter.h>

// FORWARD DECLARATIONS
class CMpAppUi;

// CLASS DECLARATION

enum TMpFont
{
	EMpNoFont = 0,
	EMpTitleFont = 1,
	EMpDenseFont = 2,
	EMpLegendFont = 3,
	EMpAnnotationFont = 4,
	EMpSymbolFont = 5,
	EMpNormalFont = 6
};

class TMpSkin
{
public:
	TRect iButtonsRect;

	TRgb iAppFontColour;
	TMpFont iAppFont;

	CFbsBitmap* iBitmap;

	TBool iValid;
};


const TInt KMaxSkinBitmapWidth = 176;
const TInt KMaxSkinBitmapHeight = 300;


class CSkinEngine : public CBase, public MMdaImageUtilObserver
{
public: // Constructors and destructor
	CSkinEngine(CMpAppUi* aAppUi, TMpSkin& aSkin);
	static CSkinEngine* NewL(CMpAppUi* aAppUi, TMpSkin& aSkin);

	~CSkinEngine();

public: // From MMdaImageUtilObserver.
	virtual void MiuoConvertComplete(TInt aError);
	virtual void MiuoCreateComplete(TInt aError);
	virtual void MiuoOpenComplete(TInt aError);

public: // New functions.
	void LoadSkinL();
	static const CFont* FontToFont(TMpFont aFont);

protected:
	void ConstructL();

private:
	void SetupSkinL(); //ReadSkinDescriptionL(const TDesC& aFileName);

private: // Data
	CMdaImageFileToBitmapUtility* iSkinLoader;
	CMdaBitmapScaler* iSkinScaler;

	CMpAppUi* iAppUi;
	TMpSkin& iSkin;

	TBool iScaling;
};

#endif // SKINENGINE_H

// End of File
