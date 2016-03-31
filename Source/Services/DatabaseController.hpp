#ifndef _DATABASE_CONTROLLER_HPP_
    #define _DATABASE_CONTROLLER_HPP_

#pragma once
#include "DbConnectionFactory.hpp"

#include "../Utilities/sqlite/ConnectionState.hpp"
#include "../Utilities/sqlite/DbConnectionOptions.hpp"
#include "../Utilities/sqlite/DbConnection.hpp"
#include "../Utilities/sqlite/DbCommand.hpp"

#include <cassert>
#include <string>
#include <sstream>
#include <vector>
#include <tuple>

class DatabaseController
{

    enum eConstants { KINFINITE = 0xffffffff };

public :

    DatabaseController(DbConnectionFactory* const dbConnectionFactory);
    ~DatabaseController(void);

    template <class C>
    void CreateTable(const std::vector<std::tuple<std::string, std::string, std::string>>& table);

    void Update(unsigned long nMaxMillis = 20);

protected:

    std::vector<std::vector<std::string>> ExecuteCommand(const std::string& query, bool bCloseConnection = false);

    template <class C>
    static std::string GenerateCreateStatement(const std::vector<std::tuple<std::string, std::string, std::string>>& table);

    bool CleanupConnection(void);

private:

    DbConnectionFactory* const m_pDbConnectionFactory;

    std::vector<IDbConnection* const> m_connections;

}; // < end class.

template <class C>
void DatabaseController::CreateTable(const std::vector<std::tuple<std::string, std::string, std::string>>& table)
{
    auto sql = GenerateCreateStatement<C>(table);

    ExecuteCommand(sql);
}

template <class C>
std::string DatabaseController::GenerateCreateStatement(const std::vector<std::tuple<std::string, std::string, std::string>>& table)
{
    std::string tableName = C::ClassType();

    auto sqlStatement = "CREATE TABLE " + tableName + " (";
    auto endStatement = ");";

    auto iter = table.begin();
    while (iter != table.end())
    {
        auto row = (*iter);
        auto colName = row.first;
        auto colType = row->second;
        auto colNullable = row->third;

        auto rowStatement = colName + ", " + colType + ", " + colNullable;
        sqlStatement.append(rowStatement);

        ++iter;

        if (iter != table.end())
        {
            sqlStatement.append(", ");
        }
    }

    sqlStatement.append(endStatement);

    return sqlStatement;
}

#endif _DATABASE_CONTROLLER_HPP_