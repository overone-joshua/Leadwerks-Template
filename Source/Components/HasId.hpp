#ifndef _HAS_ID_
	#define _HAS_ID_

#pragma once

namespace Components
{
	/** A HasId component.
	*   The HasId component provides access to a uint64_t identifier.
	*/
	typedef struct HasId
	{
		uint64_t nId;	/*!< A uint64_t identifier. */

		/** The HasId component constructor. */
		HasId(void) : nId(0) { }

	} HasId; // < and struct.

} // < end namespace.

#endif _HAS_ID_