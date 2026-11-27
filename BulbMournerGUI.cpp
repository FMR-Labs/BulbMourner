
#include "BulbMournerGUI.h"
#include "IControls.h"
#include "../FMR_Library/FMR_Pedal/PedalFactory.h"

// Levier 2 positions sur bitmap à 3 frames : ne s'arrête jamais au milieu.
class IBSnapLeverControl : public iplug::igraphics::IBKnobControl
{
public:
  using IBKnobControl::IBKnobControl;

  void OnMouseDrag(float x, float y, float dX, float dY, const iplug::igraphics::IMouseMod& mod) override
  {
    IBKnobControl::OnMouseDrag(x, y, dX, dY, mod);
    SetValue(GetValue() < 0.5 ? 0.0 : 1.0);
    SetDirty(true);                      // renvoie la valeur snappée au paramètre
  }

  void OnMouseUp(float x, float y, const iplug::igraphics::IMouseMod& mod) override
  {
    SetValue(GetValue() < 0.5 ? 0.0 : 1.0);
    SetDirty(true);
	
	IBKnobControl::OnMouseUp(x, y, mod);
  }
};

void BulbMournerGUI::Build(iplug::igraphics::IGraphics* pGraphics, float x, float y, int slot, bool displayLed)
{
	using namespace iplug::igraphics;

	const IBitmap knobBitmap = pGraphics->LoadBitmap(KNOB_FN, 101);
	const IBitmap switchBitmap = pGraphics->LoadBitmap(SWITCH_FN, 3);
	const IBitmap footswBitmap = pGraphics->LoadBitmap(FOOTSW_FN, 2);
	const IBitmap boitierBitmap = pGraphics->LoadBitmap(BOITIER_FN, 1);

	const IBitmap fondBitmap = pGraphics->LoadBitmap(BULBMOURNER_FN, 1);

	auto at = [&](const IRECT& r) { return r.GetTranslated(x, y); };

	//  x /  y     
	// 42 / 81		126 / 81	210 / 81
	// 42 / 200		126 / 200	210 / 200
	//				126 / 337
	//				126 / 415

	// 49 / 129		133 / 129	217 / 129
	// 49 / 248		133 / 248	217 / 248
	//				133 / 385
	//				133 / 463

	const IRECT boitier = at(IRECT(0, 0, 266, 535));
	const IRECT ledCtrl = at(IRECT(84, 337, 182, 435));
	const IRECT faceAvant = at(IRECT(7, 48, 259, 528));

	const IRECT gainKnob = at(IRECT(0, 80, 98, 178));
	const IRECT toneKnob = at(IRECT(84, 80, 182, 178));
	const IRECT volumeKnob = at(IRECT(165, 80, 263, 178));
	const IRECT volumeLed =  at(IRECT(145, 60, 283, 198));

	const IRECT filterSwitch = at(IRECT(0, 199, 98, 297));
	const IRECT typeSwitch = at(IRECT(84, 199, 182, 297));
	const IRECT boostSwitch = at(IRECT(165, 199, 263, 297));

	const IRECT footSwitch = at(IRECT(84, 414, 182, 512));
	const IRECT inputLed = at(IRECT(64, 394, 202, 532));
	
	pGraphics->AttachControl(new IBitmapControl(boitier, boitierBitmap));
	pGraphics->AttachControl(new ILEDControl(ledCtrl, LedRouge), slot + BbMr_kCtrlLED + kNumStartLED);
	pGraphics->AttachControl(new IBitmapControl(faceAvant, fondBitmap));

	pGraphics->AttachControl(new IBKnobControl(gainKnob, knobBitmap, slot + BbMr_kGain));
	pGraphics->AttachControl(new IBKnobControl(toneKnob, knobBitmap, slot + BbMr_kTone));
//	if( displayLed )	pGraphics->AttachControl(new ILEDControl(volumeLed, LedVerte), slot + BbMr_kCtrlOutputLED + kNumStartLED);
	pGraphics->AttachControl(new IBKnobControl(volumeKnob, knobBitmap, slot + BbMr_kVolume));

	pGraphics->AttachControl(new IBKnobControl(filterSwitch, switchBitmap, slot + BbMr_kFilter));
	pGraphics->AttachControl(new IBSnapLeverControl(typeSwitch, switchBitmap, slot + BbMr_kType));
	pGraphics->AttachControl(new IBKnobControl(boostSwitch, switchBitmap, slot + BbMr_kBoost));

	if( displayLed )	pGraphics->AttachControl(new ILEDControl(inputLed, LedVerte), slot + BbMr_kCtrlInputLED + kNumStartLED);
	pGraphics->AttachControl(new IBSwitchControl(footSwitch, footswBitmap, slot + BbMr_kFootSw));
}

PEDAL_FACTORY(BulbMourner, BulbMournerDSP, BulbMournerGUI)