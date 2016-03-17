/*-------------------------------------------------------
                    <copyright>
    
    File: ComponentDictionary.hpp
    Language: C++
    
    (C) Copyright Eden Softworks
    
    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net
    
    Description: Header file for ComponentDictionary.

---------------------------------------------------------*/

#ifndef _COMPONENT_DICTIONARY_HPP_
	#define _COMPONENT_DICTIONARY_HPP_

#pragma once

/** A Component dictionary.
 *  An enumeration containing all bitmasks representing the finite
 *  number of components that can be combined together to form
 *  entities.
 */
typedef enum
{
	COMPONENT_NONE = 0,
	COMPONENT_PLACEMENT = 1 << 0,
	COMPONENT_VELOCITY = 1 << 1,
	COMPONENT_APPEARANCE = 1 << 2,
	COMPONENT_CAMERA = 1 << 3,
	COMPONENT_HASID = 1 << 4,
	COMPONENT_HASNAME = 1 << 5,
	COMPONENT_WORLD = 1 << 6,
	COMPONENT_INPUT = 1 << 7,
    COMPONENT_HEALTH = 1 << 8,
    COMPONENT_TRIGGER = 1 << 9,
    COMPONENT_AI = 1 << 10,
    COMPONENT_RELATIONSHIP = 1 << 11,
    COMPONENT_COLLIDER = 1 << 12    

} ComponentDictionary;

#endif _COMPONENT_DICTIONARY_HPP_