/*-------------------------------------------------------
                    <copyright>

    File: Component.hpp
    Language: C++

    (C) Copyright Eden Softworks

    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net

    Description: Header file for base Component class.

---------------------------------------------------------*/

#ifndef _COMPONENT_HPP_
	#define _COMPONENT_HPP_

#pragma once
#include "../Common.hpp"
#include "../Utilities/Macros.hpp"
#include "HasId.hpp"
#include "HasName.hpp"

#include <string>

namespace Components
{
	/** An base Component.
	*  The Component provides a base for all other component objects.
	*/
	typedef struct Component : public HasId, public HasName
	{
		CLASS_TYPE(Component);

        uint64_t nEntityId;

		/** The Components constructor. */
		explicit Component(uint64_t _entityId, std::string _name = "")
            : nEntityId(_entityId), HasName(_name) { }

        Component& operator = (Component _other)
        {
            this->nId = _other.nId;
            this->cName = _other.cName;
            return *this;
        }

	} Component; // < end struct.

} // < end namespace.

#endif _COMPONENT_HPP_