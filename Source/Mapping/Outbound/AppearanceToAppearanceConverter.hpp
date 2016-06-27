#ifndef _OUTBOUND_APPEARANCE_TO_APPEARANCE_CONVERTER_HPP_
    #define _OUTBOUND_APPEARANCE_TO_APPEARANCE_CONVERTER_HPP__

#pragma once
#include "../TypeConverter.hpp"

#include "../../Components/Appearance.hpp"
#include "../../Components/Persistence/Appearance.hpp"

#include <vector>

using namespace Components;

template <>
Appearance TypeConverter::Convert<Persistence::Appearance, Appearance>(const Persistence::Appearance& source)
{
    auto dest = Appearance(source.cModelPath, source.nEntityId, source.cName);

    dest.nId = source.nComponentId;

    return dest;
}

template <>
std::vector<Appearance> TypeConverter::ConvertAll<Persistence::Appearance, Appearance>(const std::vector<Persistence::Appearance>& source)
{
    auto res = std::vector<Appearance>();

    auto iter = source.begin();
    while (iter != source.end())
    {
        auto current = TypeConverter::Convert<Persistence::Appearance, Appearance>((*iter));
        res.push_back(current);

        ++iter;
    }

    return res;
}

#endif _OUTBOUND_APPEARANCE_TO_APPEARANCE_CONVERTER_HPP__
