/*-------------------------------------------------------
                    <copyright>
    
    File: Health.hpp
    Language: C++
    
    (C) Copyright Eden Softworks
    
    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net
    
    Description: Header file for Health component.

---------------------------------------------------------*/

#ifndef _HEALTH_COMPONENT_HPP_
    #define _HEALTH_COMPONENT_HPP_
    
#pragma once
#include "../Utilities/Macros.hpp"

#include "Component.hpp"

#include <string>

namespace components
{
    // < A health component.
    // * The health component provides access to health-related properties.
    template <typename T>
    typedef struct Health : public Component
    {
        CLASS_TYPE(Health);
        
        T               nCur;       /*!< The current health value of type T. >/      
        
        /** The Health component constructor. */
        Health(T _nHealth = 0, std::string cName = "") 
            : nCur(_nHealth), Component(cName) { }
        
    } Health; // < end struct.
    
} // < end namespace.

#endif _HEALTH_COMPONENT_HPP_