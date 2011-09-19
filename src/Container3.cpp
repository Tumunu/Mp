/*
============================================================================
 Name        : Container3.cpp
 Author      : Cleave Pokotea
 Version     :
 Copyright   : 2006 - 2007
 Description : Container3.cpp - source file
============================================================================
*/

// INCLUDE FILES
#include <eiktxlbm.h>
#include <eiklbv.h>
#include <aknutils.h> 
#include "commondata.h"
#include <SendNorm.rsg>         // R_SENDUI_MENU
#include <aknapp.h>             // CAknApplication
#include <sendui.h>             // CSendAppUi
#include <smut.h>               // KUidMsgTypeSMS
#include <stringloader.h>       // StringLoader
#include <txtrich.h>            // CRichText
#include "Container3.h"
#include "MpApp.h"
#include "MpAppUi.h"
#include <Mp.rsg>
#include "Mp.hrh"
#include <gdi.h>

const TInt KDefaultGranularity = 4;

// ================= MEMBER FUNCTIONS =======================

void CContainer3::ConstructL(const TRect& /* aRect */)
{
	CreateWindowL();

	// Construct the CSendAppUi object
	iSendAppUi = CSendAppUi::NewL(ECmdBaseId);
	iSendAppUiCapabilities.iFlags = TSendingCapabilities::ESupportsBodyText;

	// Construct the CRichText object
	iRichText = CRichText::NewL(iEikonEnv->SystemParaFormatLayerL(),
		iEikonEnv->SystemCharFormatLayerL()); 

	iFocus = 0;

	// sets full screen
	SetRect( TRect( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT ) );
	ActivateL();
	InitiateDraw();
}


CContainer3::~CContainer3()
{
	delete iSendAppUi;
	delete iRichText;
}


void CContainer3::SizeChanged()
{
}


TInt CContainer3::CountComponentControls() const
{
	return iCtrlArray.Count();
}


CCoeControl* CContainer3::ComponentControl(TInt aIndex) const
{
	return (CCoeControl*)iCtrlArray[aIndex];
}

void CContainer3::Draw(const TRect& aRect) const
{
}

void CContainer3::InitiateDraw() const
{
	Window().Invalidate();
	ActivateGc();
	Window().BeginRedraw();

	DrawRequiredControls();

	Window().EndRedraw();
	DeactivateGc();
}

void CContainer3::DrawRequiredControls() const
{
	DrawMain(Rect());
	DrawButton();
}

void CContainer3::DrawMain(const TRect& aRect) const
{
	CWindowGc& gc = SystemGc();

	TInt mainHeight = aRect.Height();
	TInt mainWidth = aRect.Width();
	TInt bkgndStartPoint = mainHeight - (mainHeight - BANNER_HEIGHT);
	TInt softkeyX = mainWidth - SOFTKEY_WIDTH;
	TInt softkeyY = mainHeight - SOFTKEY_HEIGHT + 2;

	gc.BitBlt(TPoint(0,0), ((CMpAppUi*)(CCoeEnv::Static()->AppUi()))->iSpriteHandler->GetSprite(MpowerShared::ESpriteHeaderSms));
	gc.BitBlt(TPoint(0,bkgndStartPoint), ((CMpAppUi*)(CCoeEnv::Static()->AppUi()))->iSpriteHandler->GetSprite(MpowerShared::ESpriteBkgndSms));
	gc.BitBlt(TPoint(0,softkeyY), ((CMpAppUi*)(CCoeEnv::Static()->AppUi()))->iSpriteHandler->GetSprite(MpowerShared::ESpriteSoftkeySelect));
	gc.BitBlt(TPoint(softkeyX,softkeyY), ((CMpAppUi*)(CCoeEnv::Static()->AppUi()))->iSpriteHandler->GetSprite(MpowerShared::ESpriteSoftkeyBack));
}

void CContainer3::DrawButton()const
{
	CWindowGc& gc = SystemGc();
	if(iFocus == 0)
	{
		gc.BitBlt(TPoint((SCREEN_WIDTH - SMS_BUTTON_WIDTH) / 2,BANNER_HEIGHT + 8), ((CMpAppUi*)(CCoeEnv::Static()->AppUi()))->iSpriteHandler->GetSprite(MpowerShared::ESpriteButtonSend));
	}
	else
	{
		gc.BitBlt(TPoint((SCREEN_WIDTH - SMS_BUTTON_WIDTH) / 2,(BANNER_HEIGHT + 8) + (SMS_BUTTON_HEIGHT + 5)), ((CMpAppUi*)(CCoeEnv::Static()->AppUi()))->iSpriteHandler->GetSprite(MpowerShared::ESpriteButtonInvite));
	}
}

void CContainer3::CreatePlainSmsL()
{
	iSendAppUi->CreateAndSendMessageL(KUidMsgTypeSMS, NULL, NULL,
		KNullUid, NULL, NULL, EFalse);
}

void CContainer3::CreateInviteSmsL()
{
	__ASSERT_DEBUG(iRichText && iRichText->DocumentLength() == 0,
		Panic(ERichTextNotReady));

	// insert text into the message body
	HBufC* string = StringLoader::LoadLC(R_SMS_BODY_TEXT);
	iRichText->InsertL(0, *string);
	CleanupStack::PopAndDestroy(string);
	string = NULL;

	// display the SMS editor with some text and addresses already inserted
	iSendAppUi->CreateAndSendMessageL(KUidMsgTypeSMS, iRichText, NULL,
		KNullUid, NULL, NULL, EFalse);
	iRichText->Reset();
}

void CContainer3::HandleControlEventL(CCoeControl* /*aControl*/,TCoeEvent /*aEventType*/)
{

}

TKeyResponse CContainer3::OfferKeyEventL(const TKeyEvent& aKeyEvent,
										 TEventCode aType)
{
	if(aType!=EEventKey)
	{
		InitiateDraw();
		return EKeyWasNotConsumed;
	}

	switch (aKeyEvent.iCode)
	{
	case EKeyUpArrow:
		if (iFocus > 0)
		{
			iFocus--;
			InitiateDraw();
			return EKeyWasConsumed;
		}
		break;

	case EKeyDownArrow:
		if (iFocus < 1)
		{
			iFocus++;
			InitiateDraw();
			return EKeyWasConsumed;
		}
		break;

	case EKeyOK:
		if(iFocus == 0)
		{
			CreatePlainSmsL();
			return EKeyWasConsumed;
		}
		else
		{
			CreateInviteSmsL();
			return EKeyWasConsumed;
		}
		break;

	default:
		break;
	}
	return EKeyWasNotConsumed;
}
