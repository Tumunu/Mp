/*
============================================================================
 Name        : commondata.h
 Author      : Cleave Pokotea
 Version     :
 Copyright   : 2006 - 2007
 Description : commondata.h - header file
============================================================================
*/

#ifndef COMMONDATA_H
#define COMMONDATA_H

#include <eikenv.h>

/* Constants */
#define DELETE_AND_NULL(p)		{delete p; p = NULL;}

// visuals 
#define SCREEN_WIDTH        176
#define SCREEN_HEIGHT       208

// skin specific
#define BANNER_NUM			5
#define BANNER_HEIGHT		43
#define BKGND_NUM			3
#define BKGND_HEIGHT		165
#define	SOFTKEY_NUM			7
#define SOFTKEY_HEIGHT		17
#define SOFTKEY_WIDTH		87

// sms buttons
#define SMS_NUM				2
#define SMS_BUTTON_WIDTH	134
#define SMS_BUTTON_HEIGHT	41

const TInt KHorizOffset = 5;
const TInt KVertOffset = 2;
const TInt KTextMaxLength = 50;

// web browser
// UIDs of Browser applications
const TInt KWmlBrowserUid = 0x10008D39;
//const TInt KOperaBrowserUid = 0x101F4DED;
//const TInt KDorisBrowserUid = 0x101f81a8;


namespace MpowerShared
{
	enum TSpriteIds {
		ESpriteHeaderSplash,
		ESpriteHeaderIndex,
		ESpriteHeaderSms,
		ESpriteHeaderPlay,
		ESpriteHeaderDownload,
		ESpriteBkgndDefault,
		ESpriteBkgndSplash,
		ESpriteBkgndSms,
		ESpriteSoftkeyInteract,
		ESpriteSoftkeyUpdate,
		ESpriteSoftkeySelect,
		ESpriteSoftkeyExit,
		ESpriteSoftkeyBack,
		ESpriteSoftkeyYes,
		ESpriteSoftkeyNo,
		ESpriteButtonSend,
		ESpriteButtonInvite,
		ENumSprites
	};
}

#endif
