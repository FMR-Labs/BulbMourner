#pragma once

#include "IPlug_include_in_plug_hdr.h"
#include "BulbMournerDSP.h"

using namespace iplug;
using namespace igraphics;

const int kNumPresets = 1;

class BulbMourner final : public Plugin
{
public:
  BulbMourner(const InstanceInfo& info);
  ~BulbMourner() override = default;

  void OnIdle() override;

#if IPLUG_DSP
  void ProcessBlock(sample** inputs, sample** outputs, int nFrames) override;
  void OnReset() override;

private:
  BulbMournerDSP mDSP;
#endif
};
