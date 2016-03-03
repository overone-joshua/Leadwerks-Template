/*-------------------------------------------------------
                    <copyright>
    
    File: InputDictionary.hpp
    Language: C++
    
    (C) Copyright Eden Softworks
    
    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net
    
    Description: Header file for InputDictionary.

---------------------------------------------------------*/

#ifndef _INPUT_DICTIONARY_HPP_
	#define _INPUT_DICTIONARY_HPP_

#pragma once

/** An Input dictionary.
*  An enumeration containing all bitmasks representing the finite
*  number of inputs that can be combined together.
*/
typedef enum
{
	INPUT_NONE		= 0,
	SYSTEM_INPUT	= 1,
	USER_INPUT		= 2,

	INPUT_MOVE_FORWARD	= SYSTEM_INPUT << 0,
	INPUT_MOVE_BACKWARD = SYSTEM_INPUT << 1,
	INPUT_MOVE_LEFT		= SYSTEM_INPUT << 2,
	INPUT_MOVE_RIGHT	= SYSTEM_INPUT << 3,
	INPUT_MOVE_UP		= SYSTEM_INPUT << 4,
	INPUT_MOVE_DOWN		= SYSTEM_INPUT << 5,
	INPUT_ROTATE_LEFT	= SYSTEM_INPUT << 6,
	INPUT_ROTATE_RIGHT	= SYSTEM_INPUT << 7,
	INPUT_ROTATE_UP		= SYSTEM_INPUT << 8,
	INPUT_ROTATE_DOWN	= SYSTEM_INPUT << 9,
	INPUT_ROLL_LEFT		= SYSTEM_INPUT << 10,
	INPUT_ROLL_RIGHT	= SYSTEM_INPUT << 11,

	INPUT_ACTION_CROUCH		= USER_INPUT << 0,
	INPUT_ACTION_JUMP		= USER_INPUT << 1,
	INPUT_ACTION_INTERACT	= USER_INPUT << 2,
	INPUT_ACTION_PRIMARY	= USER_INPUT << 3,
	INPUT_ACTION_SECONDARY	= USER_INPUT << 4

} InputDictionary;

#endif _INPUT_DICTIONARY_HPP_