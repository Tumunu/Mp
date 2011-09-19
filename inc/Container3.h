/*
============================================================================
 Name        : Container3.h
 Author      : Cleave Pokotea
 Version     :
 Copyright   : 2006 - 2007
 Description : Container3.h - header file
============================================================================
*/

#ifndef CONTAINER3_H
#define CONTAINER3_H

// INCLUDES
#include <coecntrl.h>
#include <eikenv.h>
#include <e32base.h>
#include <sendui.h>   // TSendingCapabilities, CSendAppUi

// FORWARD DECLARATIONS

/**
*  CContainer3  container control class.
*  
*/
class CContainer3 : public CCoeControl, MCoeControlObserver
{
public: // Constructors and destructor

	/**
	* EPOC default constructor.
	* @param aRect Frame rectangle for container.
	*/
	void ConstructL(const TRect& aRect);

	/**
	* Destructor.
	*/
	~CContainer3();

public: // New functions
	/**
	Adds a cascaded menu, listing the appropriate message types
	@param aMenuPane Menu to add to
	@param aRequiredCapabilities Required capabilities of the types
	*/
	void SenderCascadeMenuL(CEikMenuPane& aMenuPane, const TSendingCapabilities& aRequiredCapabilities);


	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);

public: // Functions from base classes

private: // Functions from base classes

	/**
	* From CoeControl
	*/
	void SizeChanged();
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;
	void Draw(const TRect& aRect) const;
	void InitiateDraw() const;
	void DrawRequiredControls() const;
	void DrawMain(const TRect& aRect) const;
	void DrawButton() const;

	/**
	* From MCoeControlObserver
	* Acts upon changes in the hosted control's state. 
	*
	* @param	aControl	The control changing its state
	* @param	aEventType	The type of control event 
	*/
	void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);

private:
	void CreatePlainSmsL();
	void CreateInviteSmsL();

private: // Data
	RPointerArray<CCoeControl> iCtrlArray;

	TInt				 iFocus;
	CSendAppUi*          iSendAppUi;
	TSendingCapabilities iSendAppUiCapabilities;
	CRichText*           iRichText;

private: // Panic code
	enum TPanicCode
	{
		EBadCommandId,
		ERichTextNotReady
	};
	inline void Panic(TPanicCode aCode);
};

_LIT(KContainer3PanicString, "CContainer3");
inline void CContainer3::Panic(TPanicCode aCode)
{
	User::Panic(KContainer3PanicString, aCode);
}

#endif
