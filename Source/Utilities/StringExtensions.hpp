#ifndef _STRING_EXTENSIONS_HPP_
    #define _STRING_EXTENSIONS_HPP_

#pragma once

#include <string>
#include <utility>

static inline void Replace(const std::string& _key, const std::string& _val, std::string& _orig)
{
    size_t pos = 0;
    while ((pos = _orig.find(_key, pos)) != std::string::npos)
    {
        _orig.replace(pos, _key.length(), _val);
        pos += _val.length();
    }

    if (pos == 0)
    {
        throw "Key not found!";
    }
}

static inline void ReplaceWithLiteral(const std::string& _key, const std::string& _val, std::string& _orig)
{
    return Replace(_key, "'" + _val + "'", _orig);
}

#endif _STRING_EXTENSIONS_HPP_