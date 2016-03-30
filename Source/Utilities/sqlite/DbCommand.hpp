#ifndef _DBCOMMAND_HPP_
    #define _DBCOMMAND_HPP_

#pragma once

#include "sqlite3.h"

#include <cassert>
#include <string>
#include <vector>

class IDbCommand
{
public:

    virtual std::vector<std::vector<std::string>> Query(char* queryString) = 0;

}; // < end class interface.

class DbCommand : public IDbCommand
{
public:

    DbCommand(sqlite3* pDatabase)
        : m_pDatabase(pDatabase)
    {
        assert(m_pDatabase != nullptr);
    }

    ~DbCommand(void) { }

    std::vector<std::vector<std::string>> Query(char* queryString)
    {
        assert(m_pDatabase != nullptr);

        sqlite3_stmt* pStatement;
        vector<vector<string>> results;

        auto res = sqlite3_prepare_v2(m_pDatabase, queryString, -1, &pStatement, 0);
        assert(res == SQLITE_OK);

        auto cols = sqlite3_column_count(pStatement);
        auto result = 0;
        while (true)
        {
            result = sqlite3_step(pStatement);

            if (result == SQLITE_ROW)
            {
                std::vector<std::string> values;
                auto index = cols;
                while (index < cols)
                {
                    std::string val; // < Initialized to empty string.
                    auto ptr = (char*)sqlite3_column_text(pStatement, index);

                    if (ptr) { val = ptr; }

                    values.push_back(val);
                    ++index;
                }
                results.push_back(values);
            }
            else
            {
                break;
            }
        }

        auto err = sqlite3_errmsg(m_pDatabase);
        if (err != "not an error") std::cerr << queryString << " " << err << std::endl;

        return results;
    }

protected:

    sqlite3* const m_pDatabase;

}; // < end class.

#endif _DBCOMMAND_HPP_