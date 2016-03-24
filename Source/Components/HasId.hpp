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
#include "../Common.hpp"

#include <algorithm>

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

        HasId& operator = (HasId other)
        {
            this->nId = other.nId;
            return *this;
        }

	} HasId; // < and struct.

} // < end namespace.

#endif _HAS_ID_