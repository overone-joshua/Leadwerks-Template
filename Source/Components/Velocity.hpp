/*-------------------------------------------------------
                    <copyright>
    
    File: Velocity.hpp
    Language: C++
    
    (C) Copyright Eden Softworks
    
    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net
    
    Description: Header file for Velocity component.

---------------------------------------------------------*/

#ifndef _VELOCITY_HPP_
	#define _VELOCITY_HPP_

#pragma once
#include "Leadwerks.h"
#include "../Utilities/Macros.hpp"

#include "Component.hpp"

namespace Components
{
	/** A Velocity component..
	*  The Velocity component provides access to a Leadwerks::Vec3
	*  objects representing a movement vector.
	*/
	typedef struct Velocity : public Component
	{		
		CLASS_TYPE(Velocity);

		Leadwerks::Vec3                   vVel;	/*!< A Leadwerks::Vec3 representing a movement vector in 3D space. */

		/* The Velocity component constructor. */
		Velocity(Leadwerks::Vec3 _vVel = Leadwerks::Vec3(0.0f, 0.0f, 0.0f), std::string cName = "") 
			: vVel(_vVel), Component(cName) { }

	} Velocity; // < end struct.

} // < end namespace.

#endif _VELOCITY_HPP_