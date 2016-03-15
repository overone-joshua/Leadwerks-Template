/*-------------------------------------------------------
                    <copyright>
    
    File: Appearance.hpp
    Language: C++
    
    (C) Copyright Eden Softworks
    
    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net
    
    Description: Header file for Appearance component.

---------------------------------------------------------*/

#ifndef _APPEARANCE_HPP_
	#define _APPEARANCE_HPP_

#pragma once
#include "Leadwerks.h"
#include "../Utilities/Macros.hpp"
#include "../Utilities/ModelHandle.hpp"

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
		
        std::string                   cModelPath;    /* The relative filepath to this components model. */

        /** The Appearance component constructor. */
        Appearance(std::string modelPath = "", std::string cName = "") 
			: cModelPath(modelPath), Component(cName) { }     

	} Appearance; // < end struct.

} // < end namespace.

#endif _APPEARANCE_HPP_