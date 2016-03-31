#ifndef _DATABASE_CONTROLLER_HPP_
    #define _DATABASE_CONTROLLER_HPP_

#pragma once
#include "DbConnectionFactory.hpp"

#include "../Utilities/sqlite/ConnectionState.hpp"
#include "../Utilities/sqlite/DbConnectionOptions.hpp"
#include "../Utilities/sqlite/DbConnection.hpp"
#include "../Utilities/sqlite/DbCommand.hpp"

#include <cassert>
#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <tuple>

class IDatabaseController
{
public:

    virtual void CreateTable(std::string tableName, const std::vector<std::tuple<std::string, std::string, std::string>>& table) = 0;

    virtual void Update(unsigned long nMaxMillis = 20) = 0;

}; // < end class interface.

class DatabaseController
{

    enum eConstants { KINFINITE = 0xffffffff };

public :

    DatabaseController(DbConnectionFactory* const dbConnectionFactory);
    ~DatabaseController(void);

    void CreateTable(std::string tableName, const std::vector<std::tuple<std::string, std::string, std::string>>& table);

    void Update(unsigned long nMaxMillis = 20);

protected:

    std::vector<std::vector<std::string>> ExecuteCommand(const std::string& query, bool bCloseConnection = false);

    static std::string GenerateCreateStatement(std::string tableName, const std::vector<std::tuple<std::string, std::string, std::string>>& table);

    bool CleanupConnection(void);

private:

    DbConnectionFactory* const m_pDbConnectionFactory;

    std::deque<IDbConnection* const> m_connections;

}; // < end class.

#endif _DATABASE_CONTROLLER_HPP_