# Eremit 64

Port of Eremit for the Nintendo 64 with minimal modifications.

Used as a test for the N64 port of SDL1 using [sdl_n64_libdragon](https://github.com/stefanmielke/sdl_n64_libdragon).

Original source found here: http://www.segaxtreme.net/content/satdev/srcToPort/eremit-1.1.tar.gz

## Changes from the original

- Ported assets using [ngine](https://github.com/stefanmielke/ngine) from tga to the sprite format supported by libdragon
- Made it draw every frame (since it was calling `SDL_Flip` every frame I had to make at least one change either way)
- Used `debugf` to get the `printf` used (also changed `fprintf` calls to `printf`)

## Building

Use [libdragon-cli](https://github.com/anacierdem/libdragon-docker) on the root directory to build.
