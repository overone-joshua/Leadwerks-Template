/*-------------------------------------------------------
                    <copyright>

    File: Appearance.hpp
    Language: C++

    (C) Copyright Eden Softworks

    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net

    Description: Header file for Appearance component.

---------------------------------------------------------*/

#ifndef _APPEARANCE_COMPONENT_HPP
    #define _APPEARANCE_COMPONENT_HPP

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
	typedef struct Component_Appearance : public Component
	{
		CLASS_TYPE(Appearance);

		std::string cModelPath;
		Leadwerks::Model* pModel;

		explicit Component_Appearance(const std::string& modelPath, uint64_t _nEntityId, const std::string& cName = "")
			: cModelPath(modelPath), pModel(nullptr), Component(_nEntityId, cName) { }

        ~Component_Appearance(void)
        {
            if (pModel != nullptr)
            {
                pModel->Release();
                delete pModel;
                pModel = nullptr;
            }
        }

	} Appearance;
} // < end namespace.

#endif _APPEARANCE_COMPONENT_HPP