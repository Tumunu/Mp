/*
============================================================================
Name        : PngLoader.cpp
Author      : 
Version     :
Copyright   : 
Description : PngLoader.cpp - source file
============================================================================
*/
#include "commondata.h"
#include "PngLoader.h"


// Read the image file with maximum color depth and then convert them
// down to something lower if the user wants it that way.
// If we'd read directly in the low color depth, the system would dither
// the image. This results in ugly images most of the times. The conversion 
// we do later doesn't dither.
static const TDisplayMode KSourceColourDepth = EColor16M;

CPngLoader::CPngLoader(const TDesC *aFilename):iErrorCode(KErrNone)
{
	// make a local copy of the filename
	iFilename = aFilename->Alloc();
	iBitmap = NULL;
}

CPngLoader::~CPngLoader()
{
	// deallocate all data
	DELETE_AND_NULL(iBitmap);
	//delete iBitmap;
	delete iFilename;
	delete iConverter;
}

void CPngLoader::LoadAndSplitImageL(const TDesC& aFilename, CFbsBitmap** aTargetBmps, TInt aNumPics, TDisplayMode aDisplayMode)
{
	CFbsBitmap* bigBmp = LoadImageL(aFilename, aDisplayMode);
	CleanupStack::PushL(bigBmp);

	TInt bmpWidth = (bigBmp->SizeInPixels()).iWidth / aNumPics;
	TSize newBmpSize(bmpWidth, (bigBmp->SizeInPixels()).iHeight);

	// Split the bitmap up into the individual frames
	for (TInt i = 0; i < aNumPics; i++)
	{
		aTargetBmps[i] = NBitmapMethods::CreateBitmapL(newBmpSize, aDisplayMode);

		CFbsBitmapDevice*		bitmapDevice	= NBitmapMethods::CreateBitmapDeviceLC(*aTargetBmps[i]);
		CFbsBitGc*				bitmapGc		= NULL;
		User::LeaveIfError( bitmapDevice->CreateContext(bitmapGc) );
		CleanupStack::PushL(bitmapGc);
		bitmapGc->BitBlt( TPoint(0, 0), bigBmp, TRect(TPoint(i * bmpWidth, 0), newBmpSize) );
		CleanupStack::PopAndDestroy(2); // device and gc
	}
	CleanupStack::PopAndDestroy(bigBmp);
}

CFbsBitmap* CPngLoader::LoadImageL(const TDesC& aFilename, const TDisplayMode aDisplayMode)
{
	TFileName fullName(aFilename);
	CompleteWithAppPath(fullName);
#ifdef __WINS__
	fullName[0] = 'C';
#endif

	// construct new loader instance
	CPngLoader *loader = new (ELeave) CPngLoader(&fullName);
	CleanupStack::PushL(loader);

	// perform operations for reading and converting the image
	loader->ReadImageL();

	// Convert the color depth of the image to something more memory-saving
	// Get the size of the original bitmap
	const TSize bitmapSize = loader->iBitmap->SizeInPixels();
	CFbsBitmap* newBitmap = NBitmapMethods::CreateBitmapLC(bitmapSize, aDisplayMode);

	CFbsBitmapDevice* newBitmapDevice = NBitmapMethods::CreateBitmapDeviceLC(*newBitmap);
	CFbsBitGc* newBitmapGc;
	User::LeaveIfError( newBitmapDevice->CreateContext(newBitmapGc) );
	newBitmapGc->BitBlt(TPoint(0,0), loader->iBitmap);
	delete newBitmapGc;
	CleanupStack::PopAndDestroy(newBitmapDevice); // Bitmap device

	// deallocate the instance
	CleanupStack::Pop(newBitmap);
	CleanupStack::PopAndDestroy(loader);

	// return the created texture
	return newBitmap;
}


// performs the actual reading and conversion of the image
void CPngLoader::ReadImageL()
{   
	iConverter = CMdaImageFileToBitmapUtility::NewL(*this);
	iConverter->OpenL(*iFilename);

	// Continue here when the opening process is finished
	CActiveScheduler::Start();

	if (iErrorCode)
		User::Leave(iErrorCode);

	TFrameInfo info;
	iConverter->FrameInfo(0, info);

	// create a bitmap to write into
	iBitmap = new (ELeave) CFbsBitmap();
	User::LeaveIfError(iBitmap->Create(info.iOverallSizeInPixels, KSourceColourDepth));

	// convert the gif into a bitmap
	iConverter->ConvertL(*iBitmap);

	// Continue when converting is finished
	CActiveScheduler::Start();

	if (iErrorCode)
		User::Leave(iErrorCode);
}



//This function is called when the gif file has been opened or an error has occured in the process
void CPngLoader::MiuoOpenComplete(TInt aError)
{
	iErrorCode = aError;
	CActiveScheduler::Stop();

}

// called when ConvertL() finishes
void CPngLoader::MiuoConvertComplete(TInt aError)
{
	iErrorCode = aError;
	CActiveScheduler::Stop();
}

void CPngLoader::MiuoCreateComplete(TInt /*aError*/)
{
	// Unused
}
