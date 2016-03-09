/*-------------------------------------------------------
                    <copyright>
    
    File: HasName.hpp
    Language: C++
    
    (C) Copyright Eden Softworks
    
    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net
    
    Description: Header file for HasName component.

---------------------------------------------------------*/

#ifndef _HAS_NAME_
	#define _HAS_NAME_

#pragma once
#include "../Services/ScriptController.hpp"

#include <Sqrat.h>
#include <Sqrat/sqext.h>

#include <string>

namespace Components
{
	/** An HasName component.
	*  The HasName component provides access to a std::string name identifier.
	*/
	typedef struct HasName
	{
		std::string               cName;	/*!< std::string identifier. */

		/** The HasName component constructor. */
		HasName(std::string _cName = "") : cName(_cName) { }

		static void Bind(void)
		{
			using namespace Sqrat;

			auto ComponentsTable = ScriptController::GetTable("Components");

			ComponentsTable->Bind("HasName", Class<HasName, sqext::ConstAlloc<HasName, std::string>>()
				.Var("cName", &HasName::cName)
			);

		}

	} HasName; // < and struct.

} // < end namespace.

#endif _HAS_NAME_