/*-------------------------------------------------------
                    <copyright>
    
    File: Appearance.hpp
    Language: C++
    
    (C) Copyright Eden Softworks
    
    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net
    
    Description: Header file for Appearance component.

---------------------------------------------------------*/

#ifndef _APPEARANCE_HPP_
	#define _APPEARANCE_HPP_

#pragma once
#include "Leadwerks.h"
#include "../Utilities/Macros.hpp"
#include "../Utilities/ModelHandle.hpp"

#include "Component.hpp"

#include "../Utilities/luatables/luatables.h"

#include <string>

using namespace std;

namespace Components 
{
	/** An Appearance component.
	 *  The Appearance component provides access to a Leadwerks::Model object.
	 */
	typedef struct Appearance : public Component
	{
		CLASS_TYPE(Appearance);
		
        std::string                   cModelPath;    /* The relative filepath to this components model. */

        /** The Appearance component constructor. */
        Appearance(std::string modelPath = "", std::string cName = "") 
			: cModelPath(modelPath), Component(cName) { }     

	} Appearance; // < end struct.

} // < end namespace.

// < LUA-TABLES BINDING
template <>
Components::Appearance LuaTableNode::getDefault<Components::Appearance>(const Components::Appearance& defVal)
{
    using namespace Leadwerks;
    using namespace Components;
    Appearance result = defVal;

    if (exists())
    {
        LuaTable custom_table = stackQueryTable();

        result.cName = custom_table["name"].get<std::string>();
        result.nId = 0;
        result.cModelPath = custom_table["modelPath"].get<std::string>();
    }
    
    // < Restore the stack.
    stackRestore();

    return result;
}

template <>
void LuaTableNode::set<Components::Appearance>(const Components::Appearance& val)
{
    using namespace Leadwerks;
    using namespace Components;    
    LuaTable custom_table = stackCreateLuaTable();

    // < Set fields.
    custom_table["name"] = val.cName;
    custom_table["id"] = val.nId;
    custom_table["modelPath"] = val.cModelPath;

    // < Restore the stack.
    stackRestore();

}

#endif _APPEARANCE_HPP_