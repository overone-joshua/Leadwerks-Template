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
#include "../Utilities/Macros.hpp"
#include "Component.hpp"

#include <string>

namespace Components
{
    template <typename T>
    typedef struct Collider : public Component
    {
        CLASS_TYPE(Collider);
        
        T           collider;       /* The collider of type T.*/
        
        /** The Collider component constructor. */
        Collider(T _collider, std::string cName = "")
            : collider(_collider), Component(cName) { }
            
    }; // < end struct.
    
} // < end namespace.

#endif _COLLIDER_COMPONENT_HPP_