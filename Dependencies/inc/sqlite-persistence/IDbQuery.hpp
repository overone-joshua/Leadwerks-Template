#ifndef _IDBQUERY_HPP_
    #define _IDBQUERY_HPP_

#pragma once
#include "ClassType.hpp"

#include <string>

class IDbQuery
{
    CLASS_TYPE(IDbQuery);

public:

    virtual ~IDbQuery(void) { }

    virtual void Set(const std::string& _query) = 0;

	virtual const std::string Text(void) = 0;

    virtual bool operator == (const IDbQuery& other) const = 0;

}; // < end interface.

#endif _IDBQUERY_HPP_