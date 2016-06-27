#ifndef _INBOUND_APPEARANCE_TO_APPEARANCE_CONVERTER_HPP_
    #define _INBOUND_APPEARANCE_TO_APPEARANCE_CONVERTER_HPP

#pragma once
#include "../TypeConverter.hpp"

#include "../../Components/Appearance.hpp"
#include "../../Components/Persistence/Appearance.hpp"

#include <vector>

using namespace Components;

template <>
Persistence::Appearance TypeConverter::Convert<Appearance, Persistence::Appearance>(const Appearance& source)
{
    auto dest = Persistence::Appearance();

    dest.nId = source.nId;
    dest.nComponentId = source.nId;
    dest.nEntityId = source.nEntityId;
    dest.nComponentId = source.nId;
    dest.cModelPath = source.cModelPath;
    dest.cName = source.cName;

    return dest;
}

template <>
std::vector<Persistence::Appearance> TypeConverter::ConvertAll<Appearance, Persistence::Appearance>(const std::vector<Appearance>& source)
{
    auto res = std::vector<Persistence::Appearance>();

    auto iter = source.begin();
    while (iter != source.end())
    {
        auto current = TypeConverter::Convert<Appearance, Persistence::Appearance>((*iter));
        res.push_back(current);

        ++iter;
    }

    return res;
}

#endif _INBOUND_APPEARANCE_TO_APPEARANCE_CONVERTER_HPP
