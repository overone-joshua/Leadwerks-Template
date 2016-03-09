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

#include "../Services/ScriptController.hpp"

#include "Component.hpp"

#include <Sqrat.h>
#include <Sqrat/sqext.h>

#include <string>

namespace Components 
{
	/** An Appearance component.
	 *  The Appearance component provides access to a Leadwerks::Model object.
	 */
	typedef struct Appearance : public Component
	{
		CLASS_TYPE(Appearance);

		Leadwerks::Model*             pModel;	/*!< A Leadwerks 3DModel. */

        /** The Appearance component constructor. */
        Appearance(Leadwerks::Model* _pModel = nullptr, std::string cName = "") 
			: pModel(_pModel), Component(cName) { }

		static void Bind(void)
		{
			using namespace Sqrat;

			// < Get access to the ComponentsTable.
			// * NOTE: This implementation requires that the Sqrat defaultVm has been set.
			auto ComponentsTable = ScriptController::GetTable("Components");

			// < Bind Appearance component to squirrel, specifying constAlloc 
			// * in order to define available constructor in squirrel. 
			ComponentsTable->Bind("Appearance", Class<Appearance, sqext::ConstAlloc<Appearance, Leadwerks::Model*>>()
				.Var("pModel", &Appearance::pModel)
			);

		}

	} Appearance; // < end struct.

} // < end namespace.

#endif _APPEARANCE_HPP_