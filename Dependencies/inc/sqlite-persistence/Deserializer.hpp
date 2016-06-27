#ifndef _DESERIALIZER_HPP_
    #define _DESERIALIZER_HPP_

#pragma once

#include <string>
#include <vector>

template <typename T>
class Deserializer
{
public:

    static T Deserialize(const std::vector<std::string>& obj);

    static std::vector<T> DeserializeAll(const std::vector<std::vector<std::string>>& obj);

}; // < end class.

#endif _DESERIALIZER_HPP_