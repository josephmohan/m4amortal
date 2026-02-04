# m4amortal

A small C++ library for converting `.m4a` audio files to `.wav` by invoking `ffmpeg`.

## CLI usage

After install, users run:

```bash
m4amortal path/to/file.m4a
```

The command writes `path/to/file.wav` right next to the source file and prints the output path.

## Build

```bash
make
```

This builds:
- `lib/libm4amortal.a` (static library)
- `bin/m4amortal` (CLI)

Requirement: `ffmpeg` must be installed and available on `PATH`.

## Homebrew

The included formula at `Formula/m4amortal.rb` declares:
- `depends_on "ffmpeg"`

So when users install via your tap, Homebrew installs `ffmpeg` automatically before `m4amortal`.

## Local run

```bash
make
./bin/m4amortal "Westfield Century City.m4a"
```

## Library usage

```cpp
#include "m4a_to_wav.h"

std::string error;
m4amortal::ConvertOptions options;
options.sample_rate = 44100; // optional; 0 keeps input sample rate
options.channels = 2;        // optional; 0 keeps input channel count

bool ok = m4amortal::convert_m4a_to_wav("input.m4a", "output.wav", options, &error);
```
library is key