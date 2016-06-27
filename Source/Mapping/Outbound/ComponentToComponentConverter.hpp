#ifndef _OUTBOUND_COMPONENT_TO_COMPONENT_CONVERTER_HPP_
    #define _OUTBOUND_COMPONENT_TO_COMPONENT_CONVERTER_HPP_

#pragma once
#include "../TypeConverter.hpp"

#include "../../Components/Component.hpp"
#include "../../Components/Persistence/Component.hpp"

#include <vector>

using namespace Components;

template <>
Component TypeConverter::Convert<Persistence::Component, Component>(const Persistence::Component& source)
{
    auto dest = Component(source.nEntityId);

    dest.nId = source.nId;
    dest.cName = source.cName;

    return dest;
}

template <>
std::vector<Component> TypeConverter::ConvertAll<Persistence::Component, Component>(const std::vector<Persistence::Component>& source)
{
    auto res = std::vector<Component>();

    auto iter = source.begin();
    while (iter != source.end())
    {
        auto current = TypeConverter::Convert<Persistence::Component, Component>((*iter));
        res.push_back(current);

        ++iter;
    }

    return res;
}

#endif _OUTBOUND_COMPONENT_TO_COMPONENT_CONVERTER_HPP_
