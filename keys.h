/*
Copyright (C) 1996-2001 Id Software, Inc.
Copyright (C) 2002-2009 John Fitzgibbons and others
Copyright (C) 2010-2014 QuakeSpasm developers

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#ifndef _QUAKE_KEYS_H
#define _QUAKE_KEYS_H

//Keycodes no longer "converge", but rather use semaphores between different USB endpoints and devices
//to "Overlap" input. For example, if two mice were to be plugged in, and both were to have their MOUSE1
//held down, and then only 1 released, the program would still believe MOUSE1 to be held down.

//Keyboards work slightly differently, they will share the common toggles (Caps lock, Scroll lock, Num lock),
//and will have overlap with the special function keys (e.g. Left Ctrl, Right Alt, etc.), but pressing any
//other key will function as if you have pressed more than one key on a single keyboard, only the most recently
//pressed key will continue to be held, and once released, no more key presses will be registered.

//More direct integration with the USB interface will also take place, allowing me to drop these mountains of
//macros and allow the HID specification to do the talking. This may expand the flexibility and possibilities
//for binding inputs, however this is not guarenteed.

//This does raise the potential issue, for example, "universal adapters" may define more buttons than are available
//on the physical model of mouse, and this framework would allow the player to bind to these buttons which
//have no physical means to be activated.

//'Char_Event' will still work, but 'Key_Event' will no longer service this model.

//MOUSE names will have to be calculated, for example, MOUSE1 will be bit 0, MOUSE2 will be bit1, achieved with a
//bitshift, this is limited to MOUSE255 in the HID spec, but realistically this shouldn't be a problem for most 
//people.

//
// mouse buttons generate virtual keys
//

//
// joystick buttons
//

// aux keys are for multi-buttoned joysticks to generate so they can use
// the normal binding process
// aux29-32: reserved for the HAT (POV) switch motion

// JACK: Intellimouse(c) Mouse Wheel Support
// thumb buttons

// SDL2 game controller keys

#define	MAX_KEYS	97      //picoQuake -- could be 220 for full support of extended HID keyboard range
                                        // but due to memory considerations, it only covers the basic keys

#define	MAXCMDLINE	256

//typedef enum {key_game, key_console, key_message, key_menu} keydest_t;
//              0         1            2            3

//#define KEY_GAME    0
//#define KEY_CONSOLE 1
//#define KEY_MESSAGE 2
//#define KEY_MENU    3

// Instead of predefined 'key_dest's, have some seperation between church and state and employ callbacks
// such that this base code is more "serviceable" and operates much as an OS would, which allows for
// addons, mods, etc (which is ambitious for a project which I may never finish (or be impossible))

//key_dest now a cvar so that, on update, a callback is called which will handle the appropriate function
//for the selected destination, which allows for the user program to decide on the behavior
extern cvar_t	    key_dest;
extern void         (*key_press_cbs[MAX_KEY_DESTS])(void*, uint8_t);
extern void         (*key_upres_cbs[MAX_KEY_DESTS])(void*, uint8_t);
extern bool         (*key_texte_cbs[MAX_KEY_DESTS])(void);

extern char	        *keybindings[MAX_KEYS];

#define	CMDLINES    16      //picoQuake -- was 64

extern	char	    key_lines[CMDLINES][MAXCMDLINE];
extern	int		    edit_line;
extern	int		    key_linepos;
extern	int		    key_insert;
extern	double		key_blinktime;

void Key_Init (void);
void Key_ClearStates (void);
void Key_UpdateForDest (void);

void Key_BeginInputGrab (void);
void Key_EndInputGrab (void);
void Key_GetGrabbedInput (int *lastkey);

typedef struct {
    uint8_t*    array;
    uint8_t     bit_field;
    uint8_t     length;
} keys_t;

void Key_Event (keys_t *next);
bool Key_TextEntry (void);

void Key_SetBinding (int keynum, const char *binding);
const char *Key_KeynumToString (int16_t keynum);
void Key_WriteBindings (FILE *f);

/* move out to the 'client.c' or 'host.c' files
void Key_EndChat (void);
const char *Key_GetChatBuffer (void);
int Key_GetChatMsgLen (void);
*/

#endif	/* _QUAKE_KEYS_H */

