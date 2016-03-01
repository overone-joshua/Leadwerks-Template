#ifndef _APPEARANCE_HPP_
	#define _APPEARANCE_HPP_

#pragma once
#include "Leadwerks.h"
#include "../Utilities/Macros.hpp"

#include "Component.hpp"

#include <string>

namespace Components 
{
	/** An Appearance component.
	 *  The Appearance component provides access to a Leadwerks::Model object.
	 */
	typedef struct Appearance : public Component
	{
		CLASS_TYPE(Appearance);

		Leadwerks::Model* pModel;	/*!< A Leadwerks 3DModel. */

		/** The Appearance component constructor. */
		Appearance(Leadwerks::Model* _pModel = nullptr, std::string cName = "")
			: pModel(_pModel), Component(cName) { }

	} Appearance; // < end struct.

} // < end namespace.

#endif _APPEARANCE_HPP_