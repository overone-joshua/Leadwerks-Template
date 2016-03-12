#ifndef _LEADWERKS_SERIALIZERS_HPP_
	#define _LEADWERKS_SERIALIZERS_HPP_

#pragma once
#include "Leadwerks.h"

#include "luatables/luatables.h"

using namespace Leadwerks;

template <> Vec3 LuaTableNode::getDefault<Vec3>(const Vec3& defVal);
template <> void LuaTableNode::set<Vec3>(const Vec3& val);

#endif _LEADWERKS_SERIALIZERS_HPP_
