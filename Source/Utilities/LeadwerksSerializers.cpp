#pragma once
#include "Leadwerks.h"
#include "LeadwerksSerializers.hpp"

template <> Vec3 LuaTableNode::getDefault<Vec3>(const Vec3& defVal)
{
	Vec3 result = defVal;

	if (exists())
	{
		LuaTable table = stackQueryTable();
	
		result = Leadwerks::Vec3(table[1], table[2], table[3]);
	}

	// < Restore the stack.
	stackRestore();

	return result;
}

template <> void LuaTableNode::set<Vec3>(const Vec3& val)
{
	using namespace Leadwerks;
	LuaTable table = stackCreateLuaTable();

	// < Set fields.	
	table[1] = val.x;
	table[2] = val.y;
	table[3] = val.z;

	// < Restore the stack.
	stackRestore();
}