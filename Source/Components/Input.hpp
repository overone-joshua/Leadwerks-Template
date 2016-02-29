#ifndef _INPUT_COMPONENT_HPP_
	#define _INPUT_COMPONENT_HPP_

#pragma once
#include "Component.hpp"
#include "InputDictionary.hpp"

#include "../Utilities/Macros.hpp"

namespace Components
{
	typedef struct Input : public Component
	{
		CLASS_TYPE(Input);

		uint64_t nMask;

		Input(std::string cName = "") : nMask(INPUT_NONE) { }

	} Input; // < end struct.

} // < end namespace.

#endif _INPUT_COMPONENT_HPP_