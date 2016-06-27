#ifndef _INBOUND_PLACEMENT_TO_PLACEMENT_CONVERTER_HPP_
    #define _INBOUND_PLACEMENT_TO_PLACEMENT_CONVERTER_HPP

#pragma once
#include "../TypeConverter.hpp"

#include "../../Components/Placement.hpp"
#include "../../Components/Persistence/Placement.hpp"

#include <vector>

using namespace Components;

template <>
Persistence::Placement TypeConverter::Convert<Placement, Persistence::Placement>(const Placement& source)
{
    auto dest = Persistence::Placement();

    dest.nId = source.nId;
    dest.nComponentId = source.nId;
    dest.nEntityId = source.nEntityId;
    dest.nComponentId = source.nId;
    dest.cName = source.cName;

    dest.vForward = source.vForward;
    dest.vRight = source.vRight;

    dest.mWorld = source.mWorld;
    dest.mView = source.mView;

    dest.vTranslation = source.vTranslation;
    dest.vRotation = source.vRotation;

    dest.vVelocity = source.vVelocity;
    dest.vSpin = source.vSpin;

    dest.mTranslation = source.mTranslation;
    dest.mRotation = source.mRotation;

    dest.nFriction = source.nFriction;
    dest.bVisible = source.bVisible;
    dest.bGhost = source.bGhost;
    dest.bIgnoreCollision = source.bIgnoreCollision;
    dest.bTouchingGround = source.bTouchingGround;

    return dest;
}

template <>
std::vector<Persistence::Placement> TypeConverter::ConvertAll<Placement, Persistence::Placement>(const std::vector<Placement>& source)
{
    auto res = std::vector<Persistence::Placement>();

    auto iter = source.begin();
    while (iter != source.end())
    {
        auto current = TypeConverter::Convert<Placement, Persistence::Placement>((*iter));
        res.push_back(current);

        ++iter;
    }

    return res;
}

#endif _INBOUND_PLACEMENT_TO_PLACEMENT_CONVERTER_HPP
