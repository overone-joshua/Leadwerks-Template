/*-------------------------------------------------------
                    <copyright>

    File: Placement.hpp
    Language: C++

    (C) Copyright Eden Softworks

    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net

    Description: Header file for Placement component.

---------------------------------------------------------*/

#ifndef _PLACEMENT_HPP_
	#define _PLACEMENT_HPP_

#pragma once
#include "Leadwerks.h"
#include "../Utilities/Macros.hpp"

#include "Component.hpp"

#include <string>

namespace Components
{
	/** A Placement component..
	 *  The Placement component provides access to three Leadwerks::Vec3
	 *  objects; position, rotation and scale.
	 */
	typedef struct Placement : public Component
	{
		CLASS_TYPE(Placement);

		Leadwerks::Vec3                   vPos;	/*!< A Leadwerks::Vec3 representing a position in 3D space. */
		Leadwerks::Vec3                   vRot;	/*!< A Leadwerks::Vec3 representing a rotation in 3D space. */
		Leadwerks::Vec3                   vSca;	/*!< A Leadwerks::Vec3 representing a scaling factor in 3D space.*/

		/** The Placement component constructor. */
		Placement(Leadwerks::Vec3 _vPos = Leadwerks::Vec3(0.0f, 0.0f, 0.0f)
				, Leadwerks::Vec3 _vRot = Leadwerks::Vec3(0.0f, 0.0f, 0.0f)
				, Leadwerks::Vec3 _vSca = Leadwerks::Vec3(1.0f, 1.0f, 1.0f)
				, std::string cName = "")
		: vPos(_vPos), vRot(_vRot), vSca(_vSca), Component(cName) { }

	} Placement; // < end struct.

} // < end namespace.

#endif _PLACEMENT_HPP_