/*-------------------------------------------------------
                    <copyright>

    File: Converter.hpp
    Language: C++

    (C) Copyright Eden Softworks

    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net

    Description: Header file for type Converter.

    Functions:
---------------------------------------------------------*/

#ifndef _TYPE_CONVERTER_HPP_
    #define _TYPE_CONVERTER_HPP_

#pragma once
#include <vector>

struct TypeConverter
{
    TypeConverter() { }

    template <typename Inbound, typename Outbound>
    static Outbound Convert(const Inbound& source);

    template <typename Inbound, typename Outbound>
    static std::vector<Outbound> ConvertAll(const std::vector<Inbound>& source);

}; // end class.

#endif _TYPE_CONVERTER_HPP_