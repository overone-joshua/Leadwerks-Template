/*-------------------------------------------------------
                    <copyright>

    File: Collider.hpp
    Language: C++

    (C) Copyright Eden Softworks

    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net

    Description: Header file for Collider component.

---------------------------------------------------------*/

#ifndef _COLLIDER_COMPONENT_HPP_
    #define _COLLIDER_COMPONENT_HPP_

#pragma once
#include "Leadwerks.h"
#include "../Utilities/Macros.hpp"
#include "Component.hpp"

#include <string>

namespace Components
{
    typedef struct Collider : public Component
    {
        CLASS_TYPE(Collider);

        Leadwerks::AABB           collider;       /* The collider of type T.*/

        /** The Collider component constructor. */
        Collider(Leadwerks::AABB _collider = Leadwerks::AABB(Leadwerks::Vec3(0.0f, 0.0f, 0.0f), Leadwerks::Vec3(0.0f, 0.0f, 0.0f)), std::string cName = "")
            : collider(_collider), Component(cName) { }

    }; // < end struct.

} // < end namespace.

#endif _COLLIDER_COMPONENT_HPP_