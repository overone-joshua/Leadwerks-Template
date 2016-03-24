/*-------------------------------------------------------
                    <copyright>

    File: Relationship.hpp
    Language: C++

    (C) Copyright Eden Softworks

    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net

    Description: Header file for Relationship component.

---------------------------------------------------------*/

#ifndef _RELATIONSHIP_COMPONENT_HPP_
    #define _RELATIONSHIP_COMPONENT_HPP_

#pragma once
#include "../Common.hpp"
#include "../Utilities/Macros.hpp"

#include "Component.hpp"

namespace Components
{
    typedef struct Relationship : public Component
    {
        CLASS_TYPE(Relationship);

        uint64_t               related;

        Relationship(uint64_t _related = 0, std::string cName = "")
            : related(related), Component(cName) { }

    }; // < end struct.

} // < end namespace.

#endif _RELATIONSHIP_COMPONENT_HPP_