#ifndef _INPUT_COMPONENT_HPP_
	#define _INPUT_COMPONENT_HPP_

#pragma once
#include "Component.hpp"
#include "InputDictionary.hpp"

#include "../Utilities/Macros.hpp"

namespace Components
{
	/** An Input component.
	 *  The Input component provides access to a uint64_t bitmask which 
	 *  can be populated with values from the InputDictionary.
	*/
	typedef struct Input : public Component
	{
		CLASS_TYPE(Input);

		uint64_t nMask;	/*!< A uint64_t bitmask. */

		/** The Input component constructor.*/
		Input(std::string cName = "") : nMask(INPUT_NONE) { }

	} Input; // < end struct.

} // < end namespace.

#endif _INPUT_COMPONENT_HPP_