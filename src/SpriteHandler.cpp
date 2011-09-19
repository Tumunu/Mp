/*
============================================================================
 Name        : SpriteHandler.cpp
 Author      : Cleave Pokotea
 Version     :
 Copyright   : 2006 - 2007
 Description : SpriteHandler.cpp - source file
============================================================================
*/

#include "commondata.h"
#include "SpriteHandler.h"

using namespace MpowerShared;

CSpriteHandler::CSpriteHandler()
{
}

CSpriteHandler::~CSpriteHandler()
{
	// Delete ALL bitmaps
	iSprites.DeleteAll();
}

CSpriteHandler* CSpriteHandler::NewL()
{
	CSpriteHandler* self = new (ELeave) CSpriteHandler;
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
}

void CSpriteHandler::ConstructL()
{
	_LIT(KBmpHeaders, "headers.png");
	CPngLoader::LoadAndSplitImageL(KBmpHeaders, &iSprites[ESpriteHeaderSplash], BANNER_NUM, EColor4K);

	_LIT(KBmpBackgrounds, "bkgnds.png");
	CPngLoader::LoadAndSplitImageL(KBmpBackgrounds, &iSprites[ESpriteBkgndDefault], BKGND_NUM, EColor16M);

	_LIT(KBmpSoftkeys, "softkeys.png");
	CPngLoader::LoadAndSplitImageL(KBmpSoftkeys, &iSprites[ESpriteSoftkeyInteract], SOFTKEY_NUM, EColor4K);

	// ?
	_LIT(KBmpSend, "send.png");
	iSprites[ESpriteButtonSend] = CPngLoader::LoadImageL(KBmpSend, EColor16M);

	_LIT(KBmpInvite, "invite.png");
	iSprites[ESpriteButtonInvite] = CPngLoader::LoadImageL(KBmpInvite, EColor16M);
}
