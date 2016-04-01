#ifndef _DATABASE_CONTROLLER_HPP_
    #define _DATABASE_CONTROLLER_HPP_

#pragma once
#include "../Utilities/Disposable.hpp"
#include "../Utilities/Macros.hpp"
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

class IDatabaseController : virtual IDisposable
{
    CLASS_TYPE(IDatabaseController);

public:

    virtual void CreateTable(std::string tableName, const std::vector<std::tuple<std::string, std::string, std::string>>& table) = 0;
    virtual void InsertRecord(std::string tableName, const std::vector<std::string>& row) = 0;
    virtual void UpdateRecord(std::string tabelName, const std::pair<std::string, std::string>& MatchKey, const std::vector<std::pair<std::string, std::string>>& values) = 0;

    virtual void Update(unsigned long nMaxMillis = 20) = 0;

}; // < end class interface.

class DatabaseController : public IDatabaseController, public Disposable
{
    CLASS_TYPE(DatabaseController);

    enum eConstants { KINFINITE = 0xffffffff };

public :

    DatabaseController(IDbConnectionFactory* const dbConnectionFactory);
    ~DatabaseController(void);

    void CreateTable(std::string tableName, const std::vector<std::tuple<std::string, std::string, std::string>>& table);
    void InsertRecord(std::string tableName, const std::vector<std::string>& row);
    void UpdateRecord(std::string tabelName, const std::pair<std::string, std::string>& MatchKey, const std::vector<std::pair<std::string, std::string>>& values);

    void Update(unsigned long nMaxMillis = 20);

    void Dispose(void);

protected:

    std::vector<std::vector<std::string>> ExecuteCommand(const std::string& query, bool bCloseConnection = false);

    static std::string GenerateCreateStatement(std::string tableName, const std::vector<std::tuple<std::string, std::string, std::string>>& table);
    static std::string GenerateInsertStatement(std::string tabelName, const std::vector<std::string>& row);
    std::string GenerateUpdateStatement(std::string tableName, const std::pair<std::string, std::string>& MatchKey, const std::vector<std::pair<std::string, std::string>>& values);

    bool CleanupConnection(void);

    void CloseConnections(void);

private:

    IDbConnectionFactory* const m_pDbConnectionFactory;

    std::deque<IDbConnection* const> m_connections;

}; // < end class.

#endif _DATABASE_CONTROLLER_HPP_