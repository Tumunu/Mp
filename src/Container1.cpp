/*
============================================================================
Name        : Container1 from MpContainer.h
Author      : Cleave Pokotea
Version     :
Copyright   : 2006 - 2007
Description : Container control implementation
============================================================================
*/

// INCLUDE FILES
#include "MpAppUi.h"
#include "MpDocument.h"
#include "Container1.h"
#include  <Mp.rsg>
#include "Mp.hrh"

#include <apgcli.h>
#include <eiklabel.h>  // label control
#include <StringLoader.h>	// StringLoader


// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CContainer1::ConstructL(const TRect& aRect)
// EPOC two phased constructor
// ---------------------------------------------------------
//
void CContainer1::ConstructL(const TRect& aRect)
{
	CreateWindowL();

	iTopLabel = new (ELeave) CEikLabel;
	iTopLabel->SetContainerWindowL( *this );
	iTopLabel->SetTextL( _L("M-Power") );

	iBottomLabel = new (ELeave) CEikLabel;
	iBottomLabel->SetContainerWindowL( *this );
	iBottomLabel->SetTextL( _L("You to your World!") );

	iEikonEnv->AppUiFactory()->StatusPane()->MakeVisible( EFalse );
	SetRect( TRect( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT ) );
	ActivateL();
}

// Destructor
CContainer1::~CContainer1()
{
	if(iTopLabel)
		delete iTopLabel;

	if(iBottomLabel)
		delete iBottomLabel;
}

// ---------------------------------------------------------
// CContainer1::SizeChanged()
// Called by framework when the view size is changed
// ---------------------------------------------------------
//
void CContainer1::SizeChanged()
{
	iTopLabel->SetExtent( TPoint(0,0), TSize(Rect().Width(), Rect().Height()/2));
	iBottomLabel->SetExtent( TPoint(0,Rect().Height()/2), TSize(Rect().Width(),Rect().Height()/2));

}

// ---------------------------------------------------------
// CContainer1::CountComponentControls() const
// ---------------------------------------------------------
//
TInt CContainer1::CountComponentControls() const
{
	return iCtrlArray.Count();
}

// ---------------------------------------------------------
// CContainer1::ComponentControl(TInt aIndex) const
// ---------------------------------------------------------
//
CCoeControl* CContainer1::ComponentControl(TInt aIndex) const
{
	return (CCoeControl*)iCtrlArray[aIndex];
}

// ---------------------------------------------------------
// CContainer1::Draw(const TRect& aRect) const
// ---------------------------------------------------------
//
void CContainer1::Draw(const TRect& aRect) const
{
	CWindowGc& gc = SystemGc();

	TInt mainHeight = aRect.Height();
	TInt mainWidth = aRect.Width();
	TInt bkgndStartPoint = mainHeight - (mainHeight - BANNER_HEIGHT);
	TInt softkeyX = mainWidth - SOFTKEY_WIDTH;
	TInt softkeyY = mainHeight - SOFTKEY_HEIGHT + 2;

	gc.BitBlt(TPoint(0,0), ((CMpAppUi*)(CCoeEnv::Static()->AppUi()))->iSpriteHandler->GetSprite(MpowerShared::ESpriteHeaderSplash));
	gc.BitBlt(TPoint(0,bkgndStartPoint), ((CMpAppUi*)(CCoeEnv::Static()->AppUi()))->iSpriteHandler->GetSprite(MpowerShared::ESpriteBkgndSplash));

	gc.BitBlt(TPoint(0,softkeyY), ((CMpAppUi*)(CCoeEnv::Static()->AppUi()))->iSpriteHandler->GetSprite(MpowerShared::ESpriteSoftkeyInteract));
	gc.BitBlt(TPoint(softkeyX,softkeyY), ((CMpAppUi*)(CCoeEnv::Static()->AppUi()))->iSpriteHandler->GetSprite(MpowerShared::ESpriteSoftkeyUpdate));

	//// catch cry
	//gc.SetPenStyle(CGraphicsContext::ENullPen);
	//gc.SetBrushColor(TRgb(206,206,182)); // #CECEB6
	//gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	//TRect banner (TSize(168, 34));
	//TSize corner (12, 12);
	//gc.DrawRoundRect(banner, corner);
	//TPoint textPoint (aRect.Width()/KHorizOffset, 10);
	//TBuf<KTextMaxLength> text;
	//StringLoader::Load(text, R_BANNER_TEXT);
	//const CFont* font = iEikonEnv->LegendFont();
	//gc.UseFont(font);
	//gc.DrawText(text, textPoint);
	//gc.DiscardFont();
}

// ---------------------------------------------------------
// CContainer1::HandleControlEventL(
//     CCoeControl* aControl,TCoeEvent aEventType)
// ---------------------------------------------------------
//
void CContainer1::HandleControlEventL(CCoeControl* /*aControl*/,TCoeEvent /*aEventType*/)
{

}

void CContainer1::LaunchUpdate(const TDesC& aUrl) const
{
	HBufC* param = HBufC::NewL( 1024 );

	TInt browserUid;
		browserUid = KWmlBrowserUid;

	param->Des().Format( _L( "4 %S" ),&aUrl );
	TUid id( TUid::Uid( browserUid ) );
	TApaTaskList taskList( CEikonEnv::Static()->WsSession() );
	TApaTask task = taskList.FindApp( id );
	if ( task.Exists() ) {
		HBufC8* param8 = HBufC8::NewL( param->Length() );
		param8->Des().Append( *param );
		task.SendMessage( TUid::Uid( 0 ), *param8 ); 
	}
	else {
		RApaLsSession appArcSession;
		User::LeaveIfError( appArcSession.Connect() ); // connect to AppArc server
		TThreadId id;
		appArcSession.StartDocument( *param, TUid::Uid(browserUid), id );
		appArcSession.Close();
	}
}
