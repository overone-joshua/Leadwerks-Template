/*-------------------------------------------------------
                    <copyright>
    
    File: Trigger.hpp
    Language: C++
    
    (C) Copyright Eden Softworks
    
    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net
    
    Description: Header file for Trigger component.

---------------------------------------------------------*/

#ifndef _TRIGGER_COMPONENT_HPP_
    #define _TRIGGER_COMPONENT_HPP_
    
#pragma once
#include "../Utilities/Macros.hpp"
#include "../Utilities/Delegate.hpp"

#include "Component.hpp"

#include <string>

namespace Components
{
    template <typename... ARGS>
    typedef struct Trigger : public Component
    {
        CLASS_TYPE(Trigger);
        
        Delegate<ARGS...>           callback;
        
        Trigger(Delegate<ARGS...> _callback, std::string cName = "")
            : callback(_callback), Component(cName) { }

    } Trigger;
    
} // < end namespace.

#endif _TRIGGER_COMPONENT_HPP_