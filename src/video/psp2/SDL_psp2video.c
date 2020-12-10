/*
    SDL - Simple DirectMedia Layer
    Copyright (C) 1997-2012 Sam Lantinga

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

    Sam Lantinga
    slouken@libsdl.org
*/
#include "SDL_config.h"

/* PSP2 SDL video driver implementation; this is just enough to make an
 *  SDL-based application THINK it's got a working video driver, for
 *  applications that call SDL_Init(SDL_INIT_VIDEO) when they don't need it,
 *  and also for use as a collection of stubs when porting SDL to a new
 *  platform for which you haven't yet written a valid video driver.
 *
 * This is also a great way to determine bottlenecks: if you think that SDL
 *  is a performance problem for a given platform, enable this driver, and
 *  then see if your application runs faster without video overhead.
 *
 * Initial work by Ryan C. Gordon (icculus@icculus.org). A good portion
 *  of this was cut-and-pasted from Stephane Peter's work in the AAlib
 *  SDL video driver.  Renamed to "DUMMY" by Sam Lantinga.
 */

#include "SDL_video.h"
#include "SDL_mouse.h"
#include "../SDL_sysvideo.h"
#include "../SDL_pixels_c.h"
#include "../../events/SDL_events_c.h"

#include "SDL_psp2video.h"
#include "SDL_psp2events_c.h"
#include "SDL_psp2mouse_c.h"
#include "SDL_psp2keyboard_c.h"
#include "SDL_vitatouch.h"

#include "SDL_render_vita_gxm_tools.h"
#include "SDL_render_vita_gxm_types.h"

#define PSP2VID_DRIVER_NAME "psp2"

typedef struct private_hwdata {
	gxm_texture *texture;
	SDL_Rect dst;
} private_hwdata;

static int vsync = 1;

/* Initialization/Query functions */
static int PSP2_VideoInit(_THIS, SDL_PixelFormat *vformat);
static SDL_Rect **PSP2_ListModes(_THIS, SDL_PixelFormat *format, Uint32 flags);
static SDL_Surface *PSP2_SetVideoMode(_THIS, SDL_Surface *current, int width, int height, int bpp, Uint32 flags);
static int PSP2_SetColors(_THIS, int firstcolor, int ncolors, SDL_Color *colors);
static void PSP2_VideoQuit(_THIS);

/* Hardware surface functions */
static int PSP2_FlipHWSurface(_THIS, SDL_Surface *surface);
static int PSP2_AllocHWSurface(_THIS, SDL_Surface *surface);
static int PSP2_LockHWSurface(_THIS, SDL_Surface *surface);
static void PSP2_UnlockHWSurface(_THIS, SDL_Surface *surface);
static void PSP2_FreeHWSurface(_THIS, SDL_Surface *surface);

/* etc. */
static void PSP2_UpdateRects(_THIS, int numrects, SDL_Rect *rects);

/* PSP2 driver bootstrap functions */
static int PSP2_Available(void)
{
	return 1;
}

static void PSP2_DeleteDevice(SDL_VideoDevice *device)
{
	SDL_free(device->hidden);
	SDL_free(device);
}

static SDL_VideoDevice *PSP2_CreateDevice(int devindex)
{
	SDL_VideoDevice *device;

	/* Initialize all variables that we clean on shutdown */
	device = (SDL_VideoDevice *)SDL_malloc(sizeof(SDL_VideoDevice));
	if ( device ) {
		SDL_memset(device, 0, (sizeof *device));
		device->hidden = (struct SDL_PrivateVideoData *)
				SDL_malloc((sizeof *device->hidden));
	}
	if ( (device == NULL) || (device->hidden == NULL) ) {
		SDL_OutOfMemory();
		if ( device ) {
			SDL_free(device);
		}
		return(0);
	}
	SDL_memset(device->hidden, 0, (sizeof *device->hidden));

	/* Set the function pointers */
	device->VideoInit = PSP2_VideoInit;
	device->ListModes = PSP2_ListModes;
	device->SetVideoMode = PSP2_SetVideoMode;
	device->CreateYUVOverlay = NULL;
	device->SetColors = PSP2_SetColors;
	device->UpdateRects = PSP2_UpdateRects;
	device->VideoQuit = PSP2_VideoQuit;
	device->AllocHWSurface = PSP2_AllocHWSurface;
	device->CheckHWBlit = NULL;
	device->FillHWRect = NULL;
	device->SetHWColorKey = NULL;
	device->SetHWAlpha = NULL;
	device->LockHWSurface = PSP2_LockHWSurface;
	device->UnlockHWSurface = PSP2_UnlockHWSurface;
	device->FlipHWSurface = PSP2_FlipHWSurface;
	device->FreeHWSurface = PSP2_FreeHWSurface;
	device->SetCaption = NULL;
	device->SetIcon = NULL;
	device->IconifyWindow = NULL;
	device->GrabInput = NULL;
	device->GetWMInfo = NULL;
	device->InitOSKeymap = PSP2_InitOSKeymap;
	device->PumpEvents = PSP2_PumpEvents;

	device->free = PSP2_DeleteDevice;

	return device;
}

int PSP2_VideoInit(_THIS, SDL_PixelFormat *vformat)
{
	if (gxm_init() != 0)
    {
        return -1;
    }
	gxm_set_vblank_wait(vsync);

	vformat->BitsPerPixel = 16;
	vformat->BytesPerPixel = 2;
	vformat->Rmask = 0xF800;
	vformat->Gmask = 0x07E0;
	vformat->Bmask = 0x001F;
	vformat->Amask = 0x0000;

	PSP2_InitKeyboard();
	PSP2_InitMouse();
	VITA_InitTouch();

	return(0);
}

SDL_Surface *PSP2_SetVideoMode(_THIS, SDL_Surface *current,
				int width, int height, int bpp, Uint32 flags)
{
	// support only 16/24 bits for now
	switch(bpp)
	{
		case 16:
		break;

		case 24:
			if (!SDL_ReallocFormat(current, 24, 0x00FF0000, 0x0000FF00, 0x000000FF, 0x00000000))
			{
				SDL_SetError("Couldn't allocate new pixel format for requested mode");
				return(NULL);
			}
		break;

		case 32:
			if (!SDL_ReallocFormat(current, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000))
			{
				SDL_SetError("Couldn't allocate new pixel format for requested mode");
				return(NULL);
			}
		break;

		default:
			if (!SDL_ReallocFormat(current, 16, 0xF800, 0x07E0, 0x001F, 0x0000))
			{
				SDL_SetError("Couldn't allocate new pixel format for requested mode");
				return(NULL);
			}
		break;
	}

	current->flags = flags | SDL_FULLSCREEN | SDL_DOUBLEBUF;
	current->w = width;
	current->h = height;
	if(current->hwdata == NULL)
	{
		PSP2_AllocHWSurface(this, current);
	}

	return(current);
}

SDL_Rect **PSP2_ListModes(_THIS, SDL_PixelFormat *format, Uint32 flags)
{
	static SDL_Rect PSP2_Rects[] = {
		{0, 0, 960, 544},
	};
	static SDL_Rect *PSP2_modes[] = {
		&PSP2_Rects[0],
		NULL
	};
	SDL_Rect **modes = PSP2_modes;

	switch(format->BitsPerPixel)
	{
		case 16:
		case 24:
		case 32:
		return modes;

		default:
		return (SDL_Rect **) -1;
	}
}

static int PSP2_AllocHWSurface(_THIS, SDL_Surface *surface)
{
	surface->hwdata = (private_hwdata*) SDL_malloc (sizeof (private_hwdata));
	if (surface->hwdata == NULL)
	{
		SDL_OutOfMemory();
		return -1;
	}
	SDL_memset (surface->hwdata, 0, sizeof(private_hwdata));

	// set initial texture destination
	surface->hwdata->dst.x = 0;
	surface->hwdata->dst.y = 0;
	surface->hwdata->dst.w = surface->w;
	surface->hwdata->dst.h = surface->h;

	switch(surface->format->BitsPerPixel)
	{
		case 16:
			surface->hwdata->texture =
				create_gxm_texture(surface->w, surface->h, SCE_GXM_TEXTURE_FORMAT_R5G6B5);
		break;

		case 24:
			surface->hwdata->texture =
				create_gxm_texture(surface->w, surface->h, SCE_GXM_TEXTURE_FORMAT_U8U8U8_RGB);
		break;

		case 32:
			surface->hwdata->texture =
				create_gxm_texture(surface->w, surface->h, SCE_GXM_COLOR_FORMAT_A8B8G8R8);
		break;

		default:
			SDL_SetError("unsupported BitsPerPixel: %i\n", surface->format->BitsPerPixel);
		return -1;
	}

	surface->pixels = gxm_texture_get_datap(surface->hwdata->texture);
	surface->pitch = gxm_texture_get_stride(surface->hwdata->texture);
	surface->flags |= SDL_HWSURFACE;

	gxm_init_texture_scale(
		surface->hwdata->texture,
		surface->hwdata->dst.x, surface->hwdata->dst.y,
		(float)surface->hwdata->dst.w/(float)surface->w,
		(float)surface->hwdata->dst.h/(float)surface->h);

	return(0);
}

static void PSP2_FreeHWSurface(_THIS, SDL_Surface *surface)
{
	if (surface->hwdata != NULL)
	{
		gxm_wait_rendering_done();
		free_gxm_texture(surface->hwdata->texture);
		SDL_free(surface->hwdata);
		surface->hwdata = NULL;
		surface->pixels = NULL;
	}
}

static int PSP2_FlipHWSurface(_THIS, SDL_Surface *surface)
{
	gxm_start_drawing();
	gxm_draw_texture(surface->hwdata->texture);
	gxm_end_drawing();
/*
	if(vsync == 1)
	{
		gxm_wait_rendering_done();
	}
*/
	gxm_swap_buffers();
}

// custom psp2 function for centering/scaling main screen surface (texture)
void SDL_SetVideoModeScaling(int x, int y, float w, float h)
{
	SDL_Surface *surface = SDL_VideoSurface;

	if (surface != NULL && surface->hwdata != NULL)
	{
		surface->hwdata->dst.x = x;
		surface->hwdata->dst.y = y;
		surface->hwdata->dst.w = w;
		surface->hwdata->dst.h = h;
	}

	gxm_init_texture_scale(
		surface->hwdata->texture,
		surface->hwdata->dst.x, surface->hwdata->dst.y,
		(float)surface->hwdata->dst.w/(float)surface->w,
		(float)surface->hwdata->dst.h/(float)surface->h);
}

// custom psp2 function for setting the texture filter to nearest or bilinear
void SDL_SetVideoModeBilinear(int enable_bilinear)
{
	SDL_Surface *surface = SDL_VideoSurface;
	
	if (surface != NULL && surface->hwdata != NULL)
	{
		if (enable_bilinear)
		{
			//reduce pixelation by setting bilinear filtering
			//for magnification
			//(first one is minimization filter,
			//second one is magnification filter)
			gxm_texture_set_filters(surface->hwdata->texture,
				SCE_GXM_TEXTURE_FILTER_POINT,
				SCE_GXM_TEXTURE_FILTER_LINEAR);
		}
		else
		{
			gxm_texture_set_filters(surface->hwdata->texture,
				SCE_GXM_TEXTURE_FILTER_POINT,
				SCE_GXM_TEXTURE_FILTER_POINT);
		}
	}
}	

// custom psp2 function for vsync
void SDL_SetVideoModeSync(int enable_vsync)
{
	vsync = enable_vsync;
	gxm_set_vblank_wait(vsync);
}


static int PSP2_LockHWSurface(_THIS, SDL_Surface *surface)
{
	return(0);
}

static void PSP2_UnlockHWSurface(_THIS, SDL_Surface *surface)
{
	return;
}

static void PSP2_UpdateRects(_THIS, int numrects, SDL_Rect *rects)
{

}

int PSP2_SetColors(_THIS, int firstcolor, int ncolors, SDL_Color *colors)
{
	return(1);
}

void PSP2_VideoQuit(_THIS)
{
	if (this->screen->hwdata != NULL)
	{
		PSP2_FreeHWSurface(this, this->screen);
	}
	gxm_finish();
}

VideoBootStrap PSP2_bootstrap = {
	PSP2VID_DRIVER_NAME, "SDL psp2 video driver",
	PSP2_Available, PSP2_CreateDevice
};

void PSP2_GetSurfaceRect(SDL_Rect *surfaceRect, SDL_Rect *scaledRect)
{
	SDL_Surface *surface = SDL_VideoSurface;

	if (surface != NULL && surface->hwdata != NULL)
	{
		surfaceRect->x = 0;
		surfaceRect->y = 0;
		surfaceRect->w = surface->w;
		surfaceRect->h = surface->h;
		*scaledRect = surface->hwdata->dst;
	}
}