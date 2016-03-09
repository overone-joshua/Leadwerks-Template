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
#include "../Utilities/Macros.hpp"
#include "../Services/ScriptController.hpp"

#include "Component.hpp"

#include "InputDictionary.hpp"

#include <Sqrat.h>
#include <Sqrat/sqext.h>

namespace Components
{
	/** An Input component.
	 *  The Input component provides access to a uint64_t bitmask which 
	 *  can be populated with values from the InputDictionary.
	*/
	typedef struct Input : public Component
	{
		CLASS_TYPE(Input);

		uint64_t                      nMask;	/*!< A uint64_t bitmask. */

		/** The Input component constructor.*/
		Input(std::string cName = "") : nMask(INPUT_NONE) { }

		static void Bind(void)
		{
			using namespace Sqrat;

			auto ComponentsTable = ScriptController::GetTable("Components");

			ComponentsTable->Bind("Input", Class<Input, sqext::ConstAlloc<Input, std::string>>()
				.Var("nMask", &Input::nMask)
			);

		}

	} Input; // < end struct.

} // < end namespace.

#endif _INPUT_COMPONENT_HPP_