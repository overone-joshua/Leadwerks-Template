/*-------------------------------------------------------
                    <copyright>
    
    File: AI.hpp
    Language: C++
    
    (C) Copyright Eden Softworks
    
    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net
    
    Description: Header file for AI component.

---------------------------------------------------------*/

#ifndef _AI_COMPONENT_HPP_
    #define _AI_COMPONENT_HPP_
    
#pragma once
#include "../Common.hpp"
#include "../Utilities/Macros.hpp"

#include "Component.hpp"

namespace Components
{
    typedef struct AI : public Component
    {
        CLASS_TYPE(AI);
                    
        uint64_t nBehaviorMask;     /* A uint64_t bitmask to define behavior. */
            
        /** The AI component constructor. */
        AI(uint64_t _nBehaviorMask, std::string _cName = "")
            : nBehaviorMask(_nBehaviorMask), Component(_cName) { }
            
    } AI;
    
} // < end namespace.

#endif _AI_COMPONENT_HPP_