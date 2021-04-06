# SDL 1.2 GXM port for PS Vita

### Features

- 1.2.16 version bump
- Up to 20% faster than vita2d version
- Lower memory usage
- Working 32 bpp
- Front touchpad support (Mouse emulation. Works with scaled/centered images)

## Build instructions

- ```make -f Makefile.vita```

- ```make install```

## Custom functions

Just like vita2d port, this one contains few custom functions that extend it's functionality and allow some fine-tuning

```void SDL_PSP2_SetVideoModeScaling(int x, int y, float w, float h);```

Sets position of rendering surface and it's dimension

```void SDL_PSP2_SetVideoModeBilinear(int enable_bilinear);```

Enables or disables bilinear filtering on scaled surfaces

```void SDL_PSP2_SetVideoModeSync(int enable_vsync);```

Enables or disables vsync

```void SDL_PSP2_SetFlipWaitRendering(int flip_wait);```

Enables or disables usage of ```sceGxmFinish``` during screen flip. In most of the cases it's safe to disable this. Doing so will improve performance a bit (but it might result in visual bugs in some games)

```void SDL_PSP2_SetTextureAllocMemblockType(SceKernelMemBlockType type);```

Sets type of memory block for all new hardware surface allocations. ```SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW``` is default one. Depending on a game ```SCE_KERNEL_MEMBLOCK_TYPE_USER_RW_UNCACHE``` or ```SCE_KERNEL_MEMBLOCK_TYPE_USER_RW``` might provide a bit better (or worse) performance. Set memblock type before display/surface creation.

## Performance tips

Mixed usage of ```SDL_SWSURFACE``` and ```SDL_HWSURFACE``` (for screen/surfaces) might result in decreased performance.

Set ```SDL_PSP2_SetFlipWaitRendering(0)``` unless you experience visual bugs (tearing, dissapearing elements).

Hardware surfaces with memblock type ```SCE_KERNEL_MEMBLOCK_TYPE_USER_RW``` or ```SCE_KERNEL_MEMBLOCK_TYPE_USER_RW_UNCACHE``` can provide better performance is case of big number of CPU read/writes of the surface.

Generally performance of ```SDL_SWSURFACE``` and ```SDL_HWSURFACE``` is roughtly the same (hardware blit is not implemented).

### Thanks to:
- isage for [SDL2 gxm port](https://github.com/isage/SDL-mirror)
- xerpi for [libvita2d](https://github.com/xerpi/libvita2d) and xerpi, Cpasjuste and rsn8887 for [original PS Vita SDL port](https://github.com/rsn8887/SDL-Vita/tree/SDL12)
