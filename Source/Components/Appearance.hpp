#ifndef _APPEARANCE_HPP_
	#define _APPEARANCE_HPP_

#pragma once
#include "Leadwerks.h"
#include "../Utilities/Macros.hpp"

#include "Component.hpp"

#include <string>

namespace Components 
{
	typedef struct Appearance : public Component
	{
		CLASS_TYPE(Appearance);

		Leadwerks::Model* pModel;

		Appearance(Leadwerks::Model* _pModel = nullptr, std::string cName = "")
			: pModel(_pModel), Component(cName) { }

	} Appearance; // < end struct.

} // < end namespace.

#endif _APPEARANCE_HPP_