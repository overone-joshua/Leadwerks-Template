/*-------------------------------------------------------
                    <copyright>
    
    File: Component.hpp
    Language: C++
    
    (C) Copyright Eden Softworks
    
    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net
    
    Description: Header file for base Component class.

---------------------------------------------------------*/

#ifndef _COMPONENT_HPP_
	#define _COMPONENT_HPP_
	
#pragma once
#include "HasId.hpp"
#include "HasName.hpp"

#include <string>

namespace Components
{
	/** An base Component.
	*  The Component provides a base for all other component objects.
	*/
	typedef struct Component : public HasId, public HasName
	{
		using HasId::HasId;
		using HasName::HasName;

		/** The Components constructor. */
		explicit Component(std::string cName = "") : HasName(cName) { }

	} Component; // < end struct.

} // < end namespace.

#endif _COMPONENT_HPP_