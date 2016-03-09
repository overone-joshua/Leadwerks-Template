/*-------------------------------------------------------
                    <copyright>
    
    File: HasId.hpp
    Language: C++
    
    (C) Copyright Eden Softworks
    
    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net
    
    Description: Header file for HasId component.

---------------------------------------------------------*/

#ifndef _HAS_ID_
	#define _HAS_ID_

#pragma once
#include "../Services/ScriptController.hpp"

#include <Sqrat.h>
#include <Sqrat/sqext.h>

namespace Components
{
	/** A HasId component.
	*   The HasId component provides access to a uint64_t identifier.
	*/
	typedef struct HasId
	{
		uint64_t              nId;	/*!< A uint64_t identifier. */

		/** The HasId component constructor. */
		HasId(void) : nId(0) { }

		static void Bind(void)
		{
			using namespace Sqrat;

			auto ComponentsTable = ScriptController::GetTable("Components");

			ComponentsTable->Bind("HasId", Class<HasId>()
				.Var("nId", &HasId::nId)
			);

		}

	} HasId; // < and struct.

} // < end namespace.

#endif _HAS_ID_