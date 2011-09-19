/*
============================================================================
 Name        : SpriteHandler.h
 Author      : Cleave Pokotea
 Version     :
 Copyright   : 2006 - 2007
 Description : SpriteHandler.h - header file
============================================================================
*/

#ifndef SPRITEHANDLER_H
#define SPRITEHANDLER_H

#include <e32std.h>
#include "commondata.h"
#include "PngLoader.h"

/**
* Stores the sprite bitmaps and handles their references.
*/
class CSpriteHandler {
public:
	static CSpriteHandler* NewL();

	void ConstructL();

	CSpriteHandler();
	~CSpriteHandler();

	/**
	* Returns a reference to the specified sprite bitmap.
	*/
	inline CFbsBitmap* GetSprite(MpowerShared::TSpriteIds aSpriteId);

private:
	/**
	* Stores all sprite bitmaps.
	*/
	TFixedArray<CFbsBitmap*, MpowerShared::ENumSprites> iSprites;

};

inline CFbsBitmap* CSpriteHandler::GetSprite(MpowerShared::TSpriteIds aSpriteId)
{
	return iSprites[aSpriteId];
}

#endif
