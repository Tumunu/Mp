/*
============================================================================
Name        : SkinEngine.cpp
Author      : Cleave Pokotea
Version     :
Copyright   : 2006 - 2007
Description : SkinEngine.cpp - source file
============================================================================
*/

// INCLUDE FILES
// Class include
#include "SkinEngine.h"
// System includes
//#include <e32base.h>  // For CBase, link against euser.lib
#include <Mp.rsg>

// User includes
#include "MpAppUi.h"

// ================= MEMBER FUNCTIONS =======================

CSkinEngine::CSkinEngine(CMpAppUi* aAppUi, TMpSkin& aSkin) : iAppUi(aAppUi), iSkin(aSkin)
{
}

CSkinEngine* CSkinEngine::NewL(CMpAppUi* aAppUi, TMpSkin& aSkin)
{
	CSkinEngine* self = new (ELeave) CSkinEngine(aAppUi, aSkin);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();

	return self;
}

void CSkinEngine::ConstructL()
{
	// Create a bitmap suitable for holding a 24-bit skin image.
	iSkin.iBitmap = new (ELeave) CFbsBitmap;
	User::LeaveIfError(iSkin.iBitmap->Create(TSize(KMaxSkinBitmapWidth, KMaxSkinBitmapHeight), EColor16M));

	iSkinLoader = CMdaImageFileToBitmapUtility::NewL(*this);
	iSkinScaler = CMdaBitmapScaler::NewL();

	CEikonEnv::Static()->FsSession().MkDirAll(KCDriveSkinTextPath);
	CEikonEnv::Static()->FsSession().MkDirAll(KCDriveSkinImagePath);
	CEikonEnv::Static()->FsSession().MkDirAll(KDDriveSkinTextPath);
	CEikonEnv::Static()->FsSession().MkDirAll(KDDriveSkinImagePath);

	// Try to load the skin. The operation is asynchronous; this is only the first stage.
	TRAPD(err, LoadSkinL());
	if (err != KErrNone)
	{
		TBuf<256> resourceBuf;
		iAppUi->CoeEnv()->ReadResource(resourceBuf, R_LOAD_SKIN_ERROR);
		CEikonEnv::Static()->InfoWinL(resourceBuf, KNullDesC);
	}
}

CSkinEngine::~CSkinEngine()
{
	iSkinLoader->Close();
	delete iSkinLoader;
	delete iSkinScaler;
	delete iSkin.iBitmap;
}

void CSkinEngine::MiuoConvertComplete(TInt aError)
{
	if (!iScaling)
	{
		iSkinLoader->Close();

#ifdef BEMUSED_SERIES_60

		if (aError != KErrNone)
		{
			TBuf<256> resourceBuf;
			iAppUi->CoeEnv()->ReadResource(resourceBuf, R_LOAD_SKIN_ERROR);
			TRAPD(err, CEikonEnv::Static()->InfoWinL(KNullDesC, resourceBuf));
		}
		else
		{
			iSkin.iValid = ETrue;
		}

		if (iAppUi->ControlView()->ControlContainer())
			iAppUi->ControlView()->ControlContainer()->DrawNow();
#else
		TSize currentSize = iSkin.iBitmap->SizeInPixels();
		TReal width = currentSize.iWidth;
		TReal height = currentSize.iHeight;
		width *= KSkinScalingFactor;
		height *= KSkinScalingFactor;

		TSize newSize(width, height);

		iSkinScaler->ScaleL(*this, *iSkin.iBitmap, newSize, EFalse);

		iScaling = ETrue;
#endif
	}
	else
	{
		if (aError != KErrNone)
		{
			TBuf<256> resourceBuf;
			iAppUi->CoeEnv()->ReadResource(resourceBuf, R_LOAD_SKIN_ERROR);
			TRAPD(err, CEikonEnv::Static()->InfoWinL(KNullDesC, resourceBuf));
		}
		else
		{
			iSkin.iValid = ETrue;
		}

		iAppUi->DrawControlView(KBemusedDrawEverything);
		iScaling = EFalse;
	}
}

void CSkinEngine::MiuoCreateComplete(TInt /*aError*/)
{
}

void CSkinEngine::MiuoOpenComplete(TInt aError)
{
	if (aError == KErrNone)
	{
		TRAP(aError, iSkinLoader->ConvertL(*iSkin.iBitmap));
		if (aError != KErrNone)
		{
			TBuf<256> resourceBuf;
			iAppUi->CoeEnv()->ReadResource(resourceBuf, R_LOAD_SKIN_ERROR);
			TRAP(aError, CEikonEnv::Static()->InfoWinL(resourceBuf, KNullDesC));
		}
	}
}

void CSkinEngine::LoadSkinL()
{
	iSkin.iValid = EFalse;

	CDir* entryList;
	TBuf<256> formatBuf;
	TFileName skinPath;
	TInt ret;

	TInt skinIndex = iAppUi->Settings().iSkinFileIndex;
	skinPath.Format(_L("%S\\*.png"), &iAppUi->SkinPathL());

	ret = CEikonEnv::Static()->FsSession().GetDir(skinPath, KEntryAttNormal,
		ESortByName, entryList);

	if (ret != KErrNone)
	{
		delete entryList;

		TBuf<256> resourceBuf;
		iAppUi->CoeEnv()->ReadResource(resourceBuf, R_SKIN_LIST_ERROR);
		formatBuf.Format(resourceBuf, ret);
		CEikonEnv::Static()->InfoWinL(formatBuf, KNullDesC);
		return;
	}

	CleanupStack::PushL(entryList);
	CleanupStack::PopAndDestroy(entryList);
}

void CSkinEngine::SetupSkinL(const TDesC& aFileName)
{
	iSkin.iButtonsRect.SetRect(0, 105, 175, 140);
	iSkin.iAppFontColour = KRgbBlack;
	iSkin.iAppFont = EMpTitleFont;
}


const CFont* CSkinEngine::FontToFont(TMpFont aFont)
{
	CEikonEnv* eikonEnv = CEikonEnv::Static();

	switch (aFont)
	{
	case EMpTitleFont:
		return eikonEnv->TitleFont();
	case EMpDenseFont:
		return eikonEnv->DenseFont();
	case EMpLegendFont:
		return eikonEnv->LegendFont();
	case EMpAnnotationFont:
		return eikonEnv->AnnotationFont();
	case EMpSymbolFont:
		return eikonEnv->SymbolFont();
	case EMpNormalFont:
		return eikonEnv->NormalFont();
	default:
		break;
	}
	return NULL;
}

// End of File
