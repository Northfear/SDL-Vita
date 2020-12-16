/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2020 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#ifndef SDL_RENDER_VITA_GXM_SHADERS_H
#define SDL_RENDER_VITA_GXM_SHADERS_H

#include <psp2/gxm.h>

#define gxm_shader_texture_f_size 256
static const unsigned char gxm_shader_texture_f[gxm_shader_texture_f_size] = {
    0x47, 0x58, 0x50, 0x00, 0x01, 0x05, 0x50, 0x03, 
    0x00, 0x01, 0x00, 0x00, 0x2f, 0x18, 0xe0, 0x2b, 
    0x1f, 0x21, 0x47, 0x49, 0x01, 0x08, 0x18, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 
    0xa4, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 
    0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 
    0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x78, 0x00, 0x00, 0x00, 0x74, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x64, 0x00, 0x00, 0x00, 0xc0, 0x3d, 0x03, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 
    0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x04, 
    0x01, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 
    0x00, 0xf9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x40, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x07, 0x44, 0xfa, 0x30, 0x00, 0x00, 0x00, 
    0x02, 0x04, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x74, 0x65, 0x78, 0x00, 
};

#define gxm_shader_texture_v_size 344
static const unsigned char gxm_shader_texture_v[gxm_shader_texture_v_size] = {
    0x47, 0x58, 0x50, 0x00, 0x01, 0x05, 0x50, 0x03, 
    0x58, 0x01, 0x00, 0x00, 0xa3, 0x36, 0x7b, 0x62, 
    0x1b, 0x80, 0x1c, 0xb0, 0x00, 0x00, 0x19, 0x00, 
    0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 
    0xe8, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 
    0x08, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x01, 0x00, 0x09, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x74, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 
    0xa0, 0x00, 0x00, 0x00, 0xc0, 0x3d, 0x03, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x94, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x94, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x84, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 
    0x01, 0x00, 0x00, 0x00, 0x74, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x37, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x06, 
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x44, 0xfa, 
    0x80, 0x00, 0x08, 0x83, 0x21, 0x0d, 0x80, 0x38, 
    0x02, 0x80, 0x81, 0xaf, 0x9c, 0x0d, 0xc0, 0x40, 
    0x0e, 0x86, 0xb9, 0xff, 0xbc, 0x0d, 0xc0, 0x40, 
    0x04, 0x11, 0x49, 0xcf, 0x80, 0x8f, 0xb1, 0x18, 
    0x02, 0x11, 0x45, 0xcf, 0x80, 0x8f, 0xb1, 0x18, 
    0x00, 0x11, 0x01, 0xc0, 0x81, 0x81, 0xb1, 0x18, 
    0x01, 0xd1, 0x42, 0xc0, 0x81, 0x81, 0xb1, 0x18, 
    0x00, 0x00, 0x20, 0xa0, 0x00, 0x50, 0x27, 0xfb, 
    0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 
    0x30, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x2a, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 
    0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 
    0x24, 0x00, 0x00, 0x00, 0x01, 0xe4, 0x00, 0x00, 
    0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x61, 0x50, 0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, 
    0x6e, 0x00, 0x61, 0x54, 0x65, 0x78, 0x63, 0x6f, 
    0x6f, 0x72, 0x64, 0x00, 0x77, 0x76, 0x70, 0x00, 
};


static const SceGxmProgram *const textureVertexProgramGxp       = (const SceGxmProgram *)gxm_shader_texture_v;
static const SceGxmProgram *const textureFragmentProgramGxp     = (const SceGxmProgram *)gxm_shader_texture_f;

#endif // SDL_RENDER_VITA_GXM_SHADERS_H

/* vi: set ts=4 sw=4 expandtab: */