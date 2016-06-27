#ifndef _DBQUERY_HPP_
	#define _DBQUERY_HPP_

#pragma once
#include "IDbQuery.hpp"

#include "ClassType.hpp"

#include <string>

#include "sqlite/sqlite3.h"

class DbQuery : public IDbQuery
{
    CLASS_TYPE(DbQuery);

public:

	explicit DbQuery(std::string _sqlQuery);
    ~DbQuery(void);

	const std::string Text(void);

    void Set(const std::string& _query);

    bool operator == (const IDbQuery& other) const
    {
        const DbQuery* obj = dynamic_cast<const DbQuery*>(&other);

        if (obj == nullptr) { return false; }

        return (obj->m_query.compare(this->m_query) == 1);
    }

private:

	std::string m_query;

}; // < end class.

#endif _DBQUERY_HPP_