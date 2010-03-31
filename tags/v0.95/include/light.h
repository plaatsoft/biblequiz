/**  
 *  @file
 *  @brief Wii Light include file
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

#ifndef __LIGHT_H__
#define __LIGHT_H__

/**
 * Init Wii Light 
 */
void WIILIGHT_Init();

/**
 * Get current Wii light intensity level
 *
 * @return Intensity [0..255]
 */
int WIILIGHT_GetLevel();

/**
 * Set Wii Light intensity
 * @param level	THe intensity level
 * @return return set level.
 */
int WIILIGHT_SetLevel(int i);

/**
 * Set Wii Light on and start the looping thread
 */
void WIILIGHT_TurnOn();

/**
 * Set Wii Light Off (looping thread terminate)
 */
void WIILIGHT_TurnOff();

/**
 * Toggl Wii Light
 * Switch the light on or off!
 */
 void WIILIGHT_Toggle();

/**
 * Close Wii Light (stop loop thread)
 */
void WIILIGHT_close();

#endif
