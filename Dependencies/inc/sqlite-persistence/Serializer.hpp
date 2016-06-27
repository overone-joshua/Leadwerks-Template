#ifndef _SERIALIZER_HPP_
    #define _SERIALIZER_HPP_

#pragma once

#include <string>
#include <vector>

template <typename T>
class serializer
{
public:

    static std::vector<std::string> Serialize(const T& obj);

    static std::vector<std::vector<std::string>> SerializeAll(const std::vector<T>& objs);

}; // < end class.

#endif _SERIALIZER_HPP_