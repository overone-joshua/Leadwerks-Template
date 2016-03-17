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
#include "../Utilities/Macros.hpp"

#include "Component.hpp"

namespace Components
{
    template <typename T>
    typedef struct Relationship : public Component
    {
        CLASS_TYPE(Relationship);
        
        T               related;
        
        Relationship(T related, std::string cName = "")
            : Component(cName) { }
        
    }; // < end struct.
    
} // < end namespace.

#endif _RELATIONSHIP_COMPONENT_HPP_