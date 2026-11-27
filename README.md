# Bulb Mourner

**Two Classics. Your Own Flavor.**

Sometimes you need the smooth, focused midrange of a classic Tube Screamer. Sometimes you want the sharper bite and extra edge of an SD-1. Bulb Mourner brings both together in one versatile overdrive.

Six dedicated neural models capture the distinct character of each circuit, thanks to two 3-position switches open up a world of tonal possibilities: from Normal to Fat and Fatter input filtering, combined with a neural-modeled boost stage: Bass, flat or Treble.

Seven neural models, countless ways to make them your own.

**Explore. Craft. Find. Enjoy your own sound!**

This plugin models a real analog pedal that we developed.

Distributed as a free **Windows VST3** plugin by [FMR Labs](https://github.com/FMR-Labs). Built with **iPlug2**.

<p align="center">
  <img alt="Bulb Mourner" title="Bulb Mourner" src="docs/BulbMourner.png">
</p>

> **Note:** FMR Labs is an independent personal project and is not affiliated with FMR Audio.

---

## Features

* 2 colors, 3 input filter and 3 boost, selectable with lever siwtchs
* Controls: **Gain**, **tone**, **Volume**, **Filter**, **Color**, **Boost**, **Bypass**
* Mono or stereo (`1-1`, `2-2`), independent processing per channel
* Input level LED around bypass foot switch (green / orange / red)
* Star-shaped activation LED
* Click-free channel switching (short mute fade)
* Runs at any host sample rate: the engine works at 48 kHz, with automatic resampling when the host runs at another rate. The resampler latency is reported to the host.
* Lightweight: small recurrent neural network per model, no allocation or lock on the audio thread

## Signal chain

```
Host (any fs, 1-2 ch)
 → [fs ≠ 48 kHz] resampling → 48 kHz
 → neural model (driven by Gain)
 → Bass / Middle / Treble
 → Volume
 → [fs ≠ 48 kHz] resampling → host fs
```

## Level indicators

| Indicator | Measured | Green | Orange | Red |
|---|---|---|---|---|
| Input LED | Level after PreGain | below -9 dB | below -3 dB | above |

Input LED thresholds are relative to a 4.5 full scale.

---

## Installation (Windows)

> Binaries will be published on the **[Releases](../../releases)** page. Until then, there is nothing to download.

1. Download the latest `.zip` from the **[Releases](../../releases)** page. It contains the plugin, a `README_FMR_BulbMourner.txt` (installation, license, third-party notices) and the font license file.
2. Extract the `.vst3` file.
3. Copy it into your VST3 folder (usually `C:\Program Files\Common Files\VST3`).
4. Rescan plugins in your DAW.

---

## About this repository (source code notice)

This repository contains the **iPlug2 wrapper and UI** of Neural Preamp: plugin class, parameters, UI layout, resources and CMake project.

* **The DSP engine is closed source and not included.** `CMakeLists.txt`, `BulbMourner.cpp`, `BulbMournerDSP.cpp` and `BulbMournerGUI.cpp` reference it through `../FMR_Library/` (neural network inference, weights, EQ, resampler, pot curves, filters, and a custom UI control). **The project cannot be compiled from this repository alone.**
* **Images are not included** (the knob and background bitmaps). See [THIRD_PARTY.md](THIRD_PARTY.md) for their origin and licenses.
* It is published to share iPlug2 UI and parameter patterns, track issues and host documentation. Pre-compiled binaries will be distributed through GitHub Releases.

### Layout

| File | Role |
|---|---|
| `BulbMourner.h / .cpp` | Plugin class, parameters |
| `BulbMournerDSP.h / .cpp` | Plugin audio callback |
| `BulbMournerGUI.h / .cpp` | Plugin UI |
| `config.h` | iPlug2 plugin configuration (IDs, channels, UI size, resources) |
| `CMakeLists.txt` | iPlug2 CMake project (VST3 target) |
| `resources/` | Windows resources (`main.rc`, `resource.h`); images are not included |

### Building the wrapper structure (reference only)

Requires [iPlug2](https://github.com/iPlug2/iPlug2), CMake ≥ 3.14, a C++20 compiler, and the engine sources placed in `../FMR_Library/`:

```
cmake -B build -DIPLUG2_DIR=<path to iPlug2>
cmake --build build --config Release
```

---

## License

* **Source code in this repository** (iPlug2 UI and wrapper): [MIT License](LICENSE). The MIT license covers the code only. Fonts and images are not part of this repository and keep their own terms, see [THIRD_PARTY.md](THIRD_PARTY.md).
* **Compiled binaries (`.vst3`)**: **Freeware**. Free to use in both personal and commercial music productions. You may redistribute the original, unmodified archive, free of charge. Reverse engineering, decompiling, reselling, or redistributing modified binaries is prohibited.

*VST is a trademark of Steinberg Media Technologies GmbH.*
