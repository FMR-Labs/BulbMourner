
#include "BulbMourner.h"

#include "IPlug_include_in_plug_src.h"
#include "IControls.h"

#include "BulbMournerGUI.h"
#include "../FMR_Library/FMR_NeuralDrive/FMR_BulbMourner.h"
#include "../FMR_Library/FMR_Lib/FMR_ConvPot.h"

#include <algorithm>

// utiliser struct Parameters et BulbMournerDSP::SetParam pour ne pas dupliquer les infos ?
BulbMourner::BulbMourner(const InstanceInfo& info) : iplug::Plugin(info, MakeConfig(BbMr_kNumParams, kNumPresets))
{
  GetParam(BbMr_kGain)->InitDouble("Gain", 0.3, 0.1, 0.999, 0.001);
  GetParam(BbMr_kTone)->InitInt("Tone", 2730, 0, 4095);
  GetParam(BbMr_kVolume)->InitInt("Volume", 2048, 0, 4095);

  GetParam(BbMr_kFilter)->InitInt("Filter", 1, 0, 2);
  GetParam(BbMr_kType)->InitInt("Type", 0, 0, 1);
  GetParam(BbMr_kBoost)->InitDouble("Boost", 0.5f, 0.001f, 0.999f, 0.499f);
  
  GetParam(BbMr_kFootSw)->InitInt("Foot Switch", 1, 0, 1);
  
#if IPLUG_EDITOR
  mMakeGraphicsFunc = [&]()
  {
    return MakeGraphics(*this, PLUG_WIDTH, PLUG_HEIGHT, PLUG_FPS, GetScaleForScreen(PLUG_WIDTH, PLUG_HEIGHT));
  };

  mLayoutFunc = [&](IGraphics* pGraphics)
  {
    pGraphics->AttachCornerResizer(EUIResizerMode::Scale, false);
    pGraphics->AttachPanelBackground(COLOR_GRAY);
    BulbMournerGUI::Build(pGraphics, 0.f, 0.f, 0, true);
	mDSP.setDisplayedLed(true);
  };
#endif
}

void BulbMourner::OnIdle()
{
#if IPLUG_EDITOR
  if (!GetUI()) return;
  
  for(int l = 0; l < BbMr_kNumLeds ; l++ )
  {
    if ( auto* led = dynamic_cast<ILEDControl*>( GetUI()->GetControlWithTag( kNumStartLED + l) ) )
	{
      float value = GetBypassed() ? 0.0f : mDSP.GetLedValue(l);
      led->SetValue(value);
      if (value != 0.0f)
      {
          led->TriggerWithDecay(mDSP.GetLedDecay(l));
      }
      led->SetHue(mDSP.GetLedColor(l));
      led->SetDirty(true);
    }
  }

#endif
}

#if IPLUG_DSP

void BulbMourner::OnReset()
{
  mDSP.Reset(GetSampleRate(), std::max(GetBlockSize(), 64));
  SetLatency(mDSP.GetLatency());
}

void BulbMourner::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{
  const int nChans = std::min(NOutChansConnected(),ND_BULB_MOURNER_NB_CHANNELS);

  // Conversion unique : BulbMournerDSP::SetParam (partagée avec le board).
  // lecture de tous les knobs et conversion (mise à l'échelle)
  for (int k = 0; k < mDSP.NumParams(); k++)
    mDSP.SetParam(k, static_cast<float>(GetParam(k)->GetNormalized()));

  mDSP.ProcessBlock(inputs, outputs, nFrames, nChans);  
}

#endif
