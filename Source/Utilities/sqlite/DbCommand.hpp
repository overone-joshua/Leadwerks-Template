#ifndef _DBCOMMAND_HPP_
    #define _DBCOMMAND_HPP_

#pragma once
#include "DbConnection.hpp"
#include "../Disposable.hpp"

#include "sqlite3.h"

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

class IDbCommand : virtual IDisposable
{
public:

    virtual std::vector<std::vector<std::string>> Query(const char* queryString) = 0;

}; // < end class interface.

class DbCommand : public IDbCommand, public Disposable
{
public:

    DbCommand(sqlite3* pDatabase, IDbConnection* const connection)
        : m_pDatabase(pDatabase), m_pDbConnection(connection)
    {
        assert(m_pDatabase != nullptr);
        assert(m_pDbConnection != nullptr);
    }

    ~DbCommand(void) { Dispose(); }

    void Dispose(void)
    {

    }

    std::vector<std::vector<std::string>> Query(const char* queryString)
    {
        assert(m_pDatabase != nullptr);

        sqlite3_stmt* pStatement;
        std::vector<std::vector<std::string>> results;

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
                auto index = 0;
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
                // < The query executed must not have returned any records so
                // * push back one record with the number of affected rows.
                if (results.empty())
                {
                    // < Fetch the number of affected rows.
                    auto numAffected = sqlite3_changes(m_pDatabase);
                    results.push_back(std::vector<std::string>(1, std::to_string(numAffected)));
                }
                break;
            }
        }

        auto err = sqlite3_errmsg(m_pDatabase);
        if (err != "not an error") std::cerr << queryString << " " << err << std::endl;

        return results;
    }

protected:

private:

    sqlite3* const m_pDatabase;

    IDbConnection* const m_pDbConnection;

}; // < end class.

#endif _DBCOMMAND_HPP_