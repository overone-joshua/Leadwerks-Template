/*-------------------------------------------------------
                    <copyright>
    
    File: Entity.hpp
    Language: C++
    
    (C) Copyright Eden Softworks
    
    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net
    
    Description: Header file for Base Entity.

    Functions: 
---------------------------------------------------------*/

#ifndef _ENTITY_HPP_
    #define _ENTITY_HPP_
    
#pragma once
#include "Leadwerks.h"
#include "../Common.hpp"
#include "../Utilities/Delegate.hpp"
#include "../Utilities/Event.hpp"

#include "../Mapping/TypeConverter.hpp"

#include "../Components/Component.hpp"
#include "../Components/World.hpp"

namespace Entities
{
    template <typename T>
    class Entity : public Leadwerks::Object
    {            
    public:		

        template <typename... ARGS> 
        static void Create(Components::World& world, ARGS... args);

        template <typename... ARGS>
        static void Load(Components::World& world, uint64_t entity, ARGS... args);
        
        static void LoadAll(Components::World& world);
        
        template <typename... ARGS>
        static void Close(Components::World& world, uint64_t entity, ARGS... args);
        
        static void CloseAll(Components::World& world);                                        

    }; // < end class.
    
} // < end namespace.

#endif _ENTITY_HPP_