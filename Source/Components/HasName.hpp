#ifndef _HAS_NAME_
	#define _HAS_NAME_

#pragma once
#include <string>

namespace Components
{
	typedef struct HasName
	{
		std::string cName;

		HasName(std::string _cName = "") : cName(_cName) { }

	} HasName; // < and struct.

} // < end namespace.

#endif _HAS_NAME_