/*
============================================================================
 Name        : PngLoader.h
 Author      : 
 Version     :
 Copyright   : 
 Description : PngLoader.h - header file
============================================================================
*/

#ifndef PNGLOADER_H
#define PNGLOADER_H

#include <e32base.h>
#include <eikenv.h>
#include <MdaImageConverter.h>
#include "bitmapmethods.h"
#include <aknutils.h>

/*!
@class CPngLoader

@discussion Converts pngs to bitmaps
*/
class CPngLoader : public CBase, public MMdaImageUtilObserver
{

public:
	/*!
	@function ~CPngLoader

	@discussion Destroy the object and release all memory objects
	*/
	virtual ~CPngLoader();

public:	 //from MMdaImageUtilObserver
	/*!
	@function MiuoOpenComplete

	@discussion Called when the gif file has been opened
	@param aError an error code or KErrNone if process was successful
	*/
	void MiuoOpenComplete(TInt aError);

	/*!
	@function MiuoConvertComplete

	@discussion Called when any conversion process performed on the bitmap is complete
	@param aError an error code or KErrNone if process was successful
	*/
	void MiuoConvertComplete(TInt aError);

	/*!
	@function MiuoCreateComplete

	@discussion Called when the file in which the bitmap is to be saved has been created 
	@param aError an error code or KErrNone if process was successful
	*/
	void MiuoCreateComplete(TInt aError);

public:
	static void LoadAndSplitImageL(const TDesC& aFilename, CFbsBitmap** aTargetBmps, TInt aNumPics, TDisplayMode aDisplayMode);
	/*!
	@function LoadImageL

	@discussion Loads a image file and converts it into a CFbsBitmap* object
	@param aFilename filename of the image file
	*/
	static CFbsBitmap* LoadImageL(const TDesC &aFilename, const TDisplayMode aDisplayMode);

private:
	/*!
	@function CPngLoader

	@discussion Perform the first phase of two phase construction 
	*/
	CPngLoader(const TDesC *aFilename);

private:  // Own functions
	void ReadImageL();

private:
	CMdaImageFileToBitmapUtility*		iConverter;
	CFbsBitmap*							iBitmap;
	TDesC* iFilename;
	TInt iErrorCode;
};

#endif

// End of File
