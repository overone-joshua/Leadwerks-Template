#ifndef _OUTBOUND_PLACEMENT_TO_PLACEMENT_CONVERTER_HPP_
    #define _OUTBOUND_PLACEMENT_TO_PLACEMENT_CONVERTER_HPP__

#pragma once
#include "../TypeConverter.hpp"

#include "../../Components/Placement.hpp"
#include "../../Components/Persistence/Placement.hpp"

#include <vector>

using namespace Components;

template <>
Placement TypeConverter::Convert<Persistence::Placement, Placement>(const Persistence::Placement& source)
{
    auto dest = Placement(source.nEntityId, source.cName);

    dest.nId = source.nComponentId;

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
std::vector<Placement> TypeConverter::ConvertAll<Persistence::Placement, Placement>(const std::vector<Persistence::Placement>& source)
{
    auto res = std::vector<Placement>();

    auto iter = source.begin();
    while (iter != source.end())
    {
        auto current = TypeConverter::Convert<Persistence::Placement, Placement>((*iter));
        res.push_back(current);

        ++iter;
    }

    return res;
}

#endif _OUTBOUND_PLACEMENT_TO_PLACEMENT_CONVERTER_HPP__
