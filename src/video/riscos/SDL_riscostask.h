/*
    SDL - Simple DirectMedia Layer
    Copyright (C) 1997-2012 Sam Lantinga

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Sam Lantinga
    slouken@libsdl.org
*/
#include "SDL_config.h"

/*
    This file added by Alan Buckley (alan_baa@hotmail.com) to support RISC OS 
	26 March 2003
*/

extern int riscos_backbuffer; /* Create a back buffer in system memory for full screen mode */
extern int riscos_closeaction; /* Close icon action */

/* Task initialisation/Clean up */

extern int RISCOS_InitTask();
extern void RISCOS_ExitTask();
extern int RISCOS_GetWimpVersion();
extern int RISCOS_GetTaskHandle();


/* Wimp mode saveing/restoring */
extern void RISCOS_StoreWimpMode();
extern void RISCOS_RestoreWimpMode();
