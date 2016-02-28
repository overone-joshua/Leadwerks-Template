#ifndef _PLACEMENT_HPP_
	#define _PLACEMENT_HPP_

#pragma once
#include "Leadwerks.h"
#include "../Utilities/Macros.hpp"

#include "Component.hpp"

#include <string>

namespace Components
{
	typedef struct Placement : public Component
	{
		CLASS_TYPE(Placement);

		Leadwerks::Vec3 vPos;	//!<Position>//
		Leadwerks::Vec3 vRot;	//!<Rotation>//
		Leadwerks::Vec3 vSca;	//!<Scale>//

		Placement(Leadwerks::Vec3 _vPos = Leadwerks::Vec3(0.0f, 0.0f, 0.0f), Leadwerks::Vec3 _vRot = Leadwerks::Vec3(0.0f, 0.0f, 0.0f), Leadwerks::Vec3 _vSca = Leadwerks::Vec3(1.0f, 1.0f, 1.0f), std::string cName = "")
			: vPos(_vPos), vRot(_vRot), vSca(_vSca), Component(cName) { }

	} Placement; // < end struct.

} // < end namespace.

#endif _PLACEMENT_HPP_