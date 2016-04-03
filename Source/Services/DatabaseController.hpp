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

typedef std::vector<std::tuple<std::string, std::string, std::string>> DataTable;
typedef std::tuple<std::string, std::string, std::string> WhereClause;
typedef std::vector<std::string> ColumnCollection;
typedef std::vector<std::string> ValueCollection;
typedef std::vector<std::pair<std::string, std::string>> KeyValCollection;

class IDatabaseController : virtual IDisposable
{
    CLASS_TYPE(IDatabaseController);

public:

    virtual void CreateTable(std::string tableName, const DataTable& table) = 0;
    virtual unsigned long InsertRecord(std::string tableName, const ColumnCollection& cols, const ValueCollection& values) = 0;
    virtual void UpdateRecord(std::string tableName, const KeyValCollection& values, const std::vector<WhereClause>& WhereClauses) = 0;
    virtual std::vector<std::vector<std::string>> SelectRecords(std::string tableName, const ColumnCollection& cols, const std::vector<WhereClause>& WhereClauses) = 0;
    virtual unsigned long DeleteRecords(std::string tableName, const std::vector<WhereClause>& WhereClauses) = 0;

    virtual void Update(unsigned long nMaxMillis = 20) = 0;

}; // < end class interface.

class DatabaseController : public IDatabaseController, public Disposable
{
    CLASS_TYPE(DatabaseController);

    enum eConstants { KINFINITE = 0xffffffff };

public :

    DatabaseController(IDbConnectionFactory* const dbConnectionFactory);
    ~DatabaseController(void);

    void CreateTable(std::string tableName, const DataTable& table);
    unsigned long InsertRecord(std::string tableName, const ColumnCollection& cols, const ValueCollection& values);
    void UpdateRecord(std::string tableName, const KeyValCollection& values, const std::vector<WhereClause>& WhereClauses);
	std::vector<std::vector<std::string>> SelectRecords(std::string tableName, const ColumnCollection& cols, const std::vector<WhereClause>& WhereClauses);
	unsigned long DeleteRecords(std::string tableName, const std::vector<WhereClause>& WhereClauses);

    void Update(unsigned long nMaxMillis = 20);

    void Dispose(void);

protected:

    std::vector<std::vector<std::string>> ExecuteCommand(const std::string& query, bool bCloseConnection = false);

    static std::string GenerateCreateTableStatement(std::string tableName, const DataTable& table);
    static std::string GenerateInsertStatement(std::string tabelName, const ColumnCollection& cols, const ValueCollection& values);
    static std::string GenerateUpdateStatement(std::string tableName, const KeyValCollection& values, const std::vector<WhereClause>& WhereClauses);
    static std::string GenerateSelectStatement(std::string tableName, const ColumnCollection& cols, const std::vector<WhereClause>& WhereClauses);
    static std::string GenerateDeleteStatement(std::string tableName, const std::vector<WhereClause>& WhereClauses);

    static std::string GenerateColumnCollection(const ColumnCollection& values);
    static std::string GenerateKeyValCollection(const KeyValCollection& keyValPair);
    static std::string GenerateWhereClause(const std::vector<WhereClause>& keyValPair);

    bool CleanupConnection(void);

    void CloseConnections(void);

private:

    IDbConnectionFactory* const m_pDbConnectionFactory;

    std::deque<IDbConnection* const> m_connections;

}; // < end class.

#endif _DATABASE_CONTROLLER_HPP_