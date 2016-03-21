/*-------------------------------------------------------
                    <copyright>
    
    File: Input.hpp
    Language: C++
    
    (C) Copyright Eden Softworks
    
    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net
    
    Description: Header file for Input component.

---------------------------------------------------------*/

#ifndef _INPUT_COMPONENT_HPP_
	#define _INPUT_COMPONENT_HPP_

#pragma once
#include "../Utilities/Delegate.hpp"
#include "../Utilities/Event.hpp"
#include "../Utilities/Macros.hpp"

#include "Component.hpp"
#include "../Components/World.hpp"

#include "InputDictionary.hpp"

namespace Components
{
	/** An Input component.
	 *  The Input component provides access to a uint64_t bitmask which 
	 *  can be populated with values from the InputDictionary.
	*/    
    template <typename T>
	struct Input : public Component
	{
		CLASS_TYPE(Input);

		uint64_t                    nMask;	/*!< A uint64_t bitmask. */
        Leadwerks::Vec3             vDelta;
        Leadwerks::Vec3             vMovSpeed;
        Leadwerks::Vec3             vRotSpeed;        	

		/** The Input component constructor.*/
		explicit Input(Leadwerks::Vec3 _vMovSpeed = Leadwerks::Vec3(0.0f, 0.0f, 0.0f), Leadwerks::Vec3 _vRotSpeed = Leadwerks::Vec3(0.0f, 0.0f, 0.0f), std::string cName = "") 
            : nMask(INPUT_NONE),  vDelta(0.0f, 0.0f, 0.0f), vMovSpeed(_vMovSpeed)
            , vRotSpeed(_vRotSpeed), Component(cName) { }

	}; // < end struct.

} // < end namespace.

#endif _INPUT_COMPONENT_HPP_