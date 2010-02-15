/**  
 *  @file
 *  @brief The file contain the Wii lights methodes
 *  @author wplaat
 *
 *  Copyright (C) 2008-2010 PlaatSoft
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 2.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <stdio.h>
#include <stdlib.h>
#include <ogcsys.h>

#include <wiiuse/wpad.h>

#include "light.h"

struct timespec _wiilight_timeOn;
struct timespec _wiilight_timeOff;

bool WIILIGHT_IsOn;
int WIILIGHT_Level;

// **************************************
// Variables
// **************************************

static vu32 *_wiilight_reg = (u32*)0xCD0000C0;
lwp_t _wiilight_thread;

// **************************************
// Internal methods
// **************************************

/**
 * just turn one bit
 */
void _wiilight_turn(int enable){
	u32 val = (*_wiilight_reg&~0x20);
	if(enable) val |= 0x20;
	*_wiilight_reg=val;
}

/**
 * This is the looping thread.. it just loops
 * turning on and off the light depending on the timing
 * specified by SetLevel()
 */
static void * _wiilight_loop(void *arg){
	
	struct timespec timeOn;
	struct timespec timeOff;
	while(WIILIGHT_IsOn){
		timeOn=_wiilight_timeOn;
		timeOff=_wiilight_timeOff;
		_wiilight_turn(1);
		nanosleep(&timeOn);
		if(timeOff.tv_nsec>0) _wiilight_turn(0);
		nanosleep(&timeOff);
	}
	
	return NULL;
}

// **************************************
// External methods
// **************************************

/**
 * Init Wii Light 
 */
void WIILIGHT_Init()
{
	_wiilight_timeOn.tv_sec=(time_t)0;
	_wiilight_timeOff.tv_sec=(time_t)0;
	WIILIGHT_IsOn=false;
	WIILIGHT_SetLevel(0);
}

/**
 * Get current Wii light intensity level
 *
 * @return Intensity [0..255]
 */
int WIILIGHT_GetLevel()
{
	return WIILIGHT_Level;
}

/**
 * Set Wii Light intensity
 * @param level	THe intensity level
 * @return return set level.
 *
 * Here is where we set the light intensity it turns on the light and 
 * waits level*40000 nanoseconds 
 * (so, if it is 255 it will wait for 10200000 nanoseconds) 
 * (that means ~ 1/100secs)
 * 
 * for the time turned off it is 10200000-level_on
 * (so, if level is 255, it will wait for 0 seconds)
 * (that means full light intensity)
 */
int WIILIGHT_SetLevel(int level)
{
	long level_on;
	long level_off;
	if(level>255) level=255;
	if(level<0) level=0;
	level_on=level*40000;
	level_off=10200000-level_on;
	_wiilight_timeOn.tv_nsec=level_on;
	_wiilight_timeOff.tv_nsec=level_off;
	WIILIGHT_Level=level;
	return level;
}

/**
 * Set Wii Light Off (looping thread terminate)
 */
void WIILIGHT_TurnOff()
{	
	WIILIGHT_IsOn=false;
}

/**
 * Set Wii Light on and start the looping thread
 */
void WIILIGHT_TurnOn()
{	
	if (!WIILIGHT_IsOn)
	{
		WIILIGHT_IsOn=true;
		LWP_CreateThread(&_wiilight_thread, _wiilight_loop,NULL,NULL,0,80);
	}
}

/**
 * Toggle Wii Light
 * Switch the light on or off!
 */
void WIILIGHT_Toggle()
{
	if(WIILIGHT_IsOn)
	{
		WIILIGHT_TurnOff();
	} 
	else 
	{
		WIILIGHT_TurnOn();
	}
}

/**
 * Close Wii Light (stop loop thread)
 */
void WIILIGHT_close() 
{
	WIILIGHT_IsOn=false;
}

// **************************************
// The End
// **************************************