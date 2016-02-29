#ifndef _HAS_ID_
	#define _HAS_ID_

#pragma once

namespace Components
{
	typedef struct HasId
	{
		uint64_t nId;

		HasId(void) : nId(0) { }

	} HasId; // < and struct.

} // < end namespace.

#endif _HAS_ID_