#ifndef _INBOUND_COMPONENT_TO_COMPONENT_CONVERTER_HPP_
    #define _INBOUND_COMPONENT_TO_COMPONENT_CONVERTER_HPP_

#pragma once
#include "../TypeConverter.hpp"

#include "../../Components/Component.hpp"
#include "../../Components/Persistence/Component.hpp"

#include <vector>

using namespace Components;

template <>
Persistence::Component TypeConverter::Convert<Component, Persistence::Component>(const Component& source)
{
    auto dest = Persistence::Component();

    dest.nId = source.nId;
    dest.cName = source.cName;
    dest.nEntityId = source.nEntityId;

    return dest;
}

template <>
std::vector<Persistence::Component> TypeConverter::ConvertAll<Component, Persistence::Component>(const std::vector<Component>& source)
{
    auto res = std::vector<Persistence::Component>();

    auto iter = source.begin();
    while (iter != source.end())
    {
        auto current = TypeConverter::Convert<Component, Persistence::Component>((*iter));
        res.push_back(current);

        ++iter;
    }

    return res;
}

#endif _INBOUND_COMPONENT_TO_COMPONENT_CONVERTER_HPP_
