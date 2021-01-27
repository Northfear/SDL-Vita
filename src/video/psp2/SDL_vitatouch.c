/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2017 Sam Lantinga <slouken@libsdl.org>

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

#include <psp2/kernel/processmgr.h>
#include <psp2/touch.h>

#include "SDL_mouse.h"
#include "../../events/SDL_events_c.h"
#include "../../events/SDL_sysevents.h"

#include "SDL_vitatouch.h"


SceTouchData touch_old;
SceTouchData touch;
SceTouchPanelInfo panelinfo;
float aAWidth;
float aAHeight;
float dispWidth;
float dispHeight;
float forcerange;
Uint8 firstTouchId;


void VITA_InitTouch(void)
{
	sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, SCE_TOUCH_SAMPLING_STATE_START);
	sceTouchGetPanelInfo(SCE_TOUCH_PORT_FRONT, &panelinfo);
	aAWidth = (float)(panelinfo.maxAaX - panelinfo.minAaX);
	aAHeight = (float)(panelinfo.maxAaY - panelinfo.minAaY);
	dispWidth = (float)(panelinfo.maxDispX - panelinfo.minDispX);
	dispHeight = (float)(panelinfo.maxDispY - panelinfo.minDispY);
	forcerange = (float)(panelinfo.maxForce - panelinfo.minForce);
}

void VITA_QuitTouch(void)
{
}

void VITA_PollTouch(void)
{
	Uint16 x;
	Uint16 y;
	touch_old = touch;

	sceTouchPeek(SCE_TOUCH_PORT_FRONT, &touch, 1);
	if (touch.reportNum > 0)
	{
		// emulate mouse events only for 1st touch
		if (touch_old.reportNum == 0)
			firstTouchId = touch.report[0].id;

		for (int i = 0; i < touch.reportNum; i++)
		{
			if (touch.report[i].id != firstTouchId)
				continue;

			VITA_ConvertTouchXYToSDLXY(&x, &y, touch.report[i].x, touch.report[i].y);
			SDL_PrivateMouseMotion(0, 0, x, y);

			// LMB SDL_PRESSED if it's initial touch down
			if (touch_old.reportNum == 0)
			{
				SDL_PrivateMouseButton(SDL_PRESSED, SDL_BUTTON_LEFT, x, y);
			}
		}
	}

	// check for touch up
	if (touch_old.reportNum > 0)
	{
		for (int i = 0; i < touch_old.reportNum; i++)
		{
			if (touch_old.report[i].id != firstTouchId)
				continue;

			int touch_up = 1;

			if (touch.reportNum > 0)
			{
				for (int j = 0; j < touch.reportNum; j++)
				{
					if (touch.report[j].id == touch_old.report[i].id )
					{
						touch_up = 0;
					}
				}
			}

			if (touch_up)
			{
				VITA_ConvertTouchXYToSDLXY(&x, &y, touch_old.report[i].x, touch_old.report[i].y);
				SDL_PrivateMouseButton(SDL_RELEASED, SDL_BUTTON_LEFT, x, y);
			}

			break;
		}
	}
}

void VITA_ConvertTouchXYToSDLXY(Uint16 *sdl_x, Uint16 *sdl_y, Uint16 vita_x, Uint16 vita_y) 
{
	float x = 0;
	float y = 0;

	x = (vita_x - panelinfo.minDispX) / dispWidth;
	y = (vita_y - panelinfo.minDispY) / dispHeight;

	x = SDL_max(x, 0.0);
	x = SDL_min(x, 1.0);
	y = SDL_max(y, 0.0);
	y = SDL_min(y, 1.0);

	SDL_Rect surfaceRect;
	SDL_Rect scaledRect;
	PSP2_GetSurfaceRect(&surfaceRect, &scaledRect);

	// translate to game coordinates
	x = ((SCREEN_W * x) - scaledRect.x) * ((float)surfaceRect.w / scaledRect.w);
	y = ((SCREEN_H * y) - scaledRect.y) * ((float)surfaceRect.h / scaledRect.h);

	*sdl_x = x;
	*sdl_y = y;
}

/* vi: set ts=4 sw=4 expandtab: */
