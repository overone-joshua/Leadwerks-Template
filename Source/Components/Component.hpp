#ifndef _COMPONENT_HPP_
	#define _COMPONENT_HPP_
	
#pragma once
#include "HasId.hpp"
#include "HasName.hpp"

#include <string>

namespace Components
{
	typedef struct Component : public HasId, public HasName
	{
		using HasId::HasId;
		using HasName::HasName;

		Component(std::string cName = "") : HasName(cName) { }

	} Component; // < end struct.

} // < end namespace.

#endif _COMPONENT_HPP_