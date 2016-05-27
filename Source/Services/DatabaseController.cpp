#pragma once
#include "DatabaseController.hpp"
#include "Leadwerks.h"
#include <crossguid/guid.h>

DatabaseController::DatabaseController(IDbConnectionFactory* const dbConnectionFactory)
    : m_pDbConnectionFactory(dbConnectionFactory)
{
    assert(m_pDbConnectionFactory != nullptr);
}

DatabaseController::~DatabaseController(void)
{
    Dispose();
}

void DatabaseController::Dispose(void)
{
    CloseConnections();
}

void DatabaseController::CloseConnections(void)
{
    auto iter = m_connections.begin();
    while (iter != m_connections.end())
    {
        auto connection = static_cast<DbConnection*>((*iter));

        if (!DbConnection::HasConnectionState(connection, CONNECTION_CLOSED))
        {
            connection->Close(true);
        }

        SAFE_DELETE(connection);
        assert(connection != nullptr);

        iter = m_connections.erase(iter);

        if (iter != m_connections.end())
        {
            ++iter;
        }
    }
    m_connections.clear();
}

std::vector<std::vector<std::string>> DatabaseController::ExecuteCommand(const std::string& query, bool bCloseConnection)
{
    GuidGenerator generator;

    auto guid = generator.newGuid();
    std::stringstream key;
    key << guid;

    auto connection = m_pDbConnectionFactory->CreateConnection(key.str());
    assert(connection != nullptr);

    // < open the connection.
    connection->Open(); // < This will create the database if it does not exist.
    assert(DbConnection::HasConnectionState(static_cast<DbConnection*>(connection), CONNECTION_OPEN));

    auto it = m_connections.insert(m_connections.end(), connection);

    auto command = connection->CreateCommand();
    assert(command != nullptr);

    auto results = connection->ExecuteCommand(command, query.c_str());

    // < Force the connection closed.
    if (bCloseConnection)
    {
        connection->Close(true);
        m_connections.erase(it);
    }

    return results;
}

void DatabaseController::CreateTable(std::string tableName, const DataTable& table)
{
    assert(!tableName.empty());
    assert(!table.empty());

    auto sql = GenerateCreateTableStatement(tableName, table);

    ExecuteCommand(sql);
}

unsigned long DatabaseController::GetLastInsertId(void)
{
    // < Will return ZERO should there be no successful inserts
    // * into rowId tables.
    return m_pDbConnectionFactory->LastInsertRowId();
}

unsigned long DatabaseController::InsertRecord(std::string tableName, const ColumnCollection& cols, const ValueCollection& values)
{
    assert(!tableName.empty());
    assert(!cols.empty());
    assert(!values.empty());

    auto sql = GenerateInsertStatement(tableName, cols, values);

    auto rowsAffected = std::stoi(ExecuteCommand(sql).front().front());
    return GetLastInsertId();
}

void DatabaseController::UpdateRecord(std::string tableName, const KeyValCollection& values, const std::vector<WhereClause>& WhereClauses)
{
    assert(!tableName.empty());
    assert(!values.empty());
    assert(!WhereClauses.empty());

    auto sql = GenerateUpdateStatement(tableName, values, WhereClauses);

    ExecuteCommand(sql);
}

std::vector<std::vector<std::string>> DatabaseController::SelectRecords(std::string tableName, const ColumnCollection& cols, const std::vector<WhereClause>& WhereClauses)
{
    assert(!tableName.empty());
    assert(!cols.empty());

	auto sql = GenerateSelectStatement(tableName, cols, WhereClauses);

	return ExecuteCommand(sql);
}

unsigned long DatabaseController::DeleteRecords(std::string tableName, const std::vector<WhereClause>& WhereClauses)
{
    assert(!tableName.empty());
    assert(!WhereClauses.empty());

	auto sql = GenerateDeleteStatement(tableName, WhereClauses);

    // < A sqlite Delete will not return the deleted rows so
    // * the DbCommand is written to return one record
    // * containing the number of affected rows.
    auto rowsAffected = std::stoi(ExecuteCommand(sql).front().front());
	return rowsAffected;
}

void DatabaseController::CreateFKConstraint(const std::string& colName, const std::string& fkTableName, const std::string& fkColumn)
{
	assert(!colName.empty());
	assert(!fkTableName.empty());
	assert(!fkColumn.empty());

	auto sql = GenerateFKConstraint(colName, fkTableName, fkColumn);

	ExecuteCommand(sql);
}

std::vector<std::vector<std::string>> DatabaseController::ExecuteQuery(std::string query)
{
    assert(!query.empty());

    return ExecuteCommand(query);
}

unsigned long DatabaseController::ExecuteNoQuery(std::string query)
{
    assert(!query.empty());

    auto rowsAffected = std::stoi(ExecuteCommand(query).front().front());
    return rowsAffected;
}

std::string DatabaseController::GenerateCreateTableStatement(std::string tableName, const DataTable& table)
{
    std::string sqlStatement = "CREATE TABLE " + tableName + " (";
    auto endStatement = ");";

    auto iter = table.begin();
    while (iter != table.end())
    {
        auto& row= (*iter);
        auto colName = std::get<0>(row);
        auto colType = std::get<1>(row);
        auto colNullable = std::get<2>(row);

        auto rowStatement = colName + " " + colType + " " + colNullable;
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

std::string DatabaseController::GenerateInsertStatement(std::string tableName, const ColumnCollection& cols, const ValueCollection& values)
{
    std::string sqlStatement = "INSERT INTO " + tableName + " (";
    auto endStatement = ");";

    sqlStatement.append(GenerateColumnCollection(cols));

    sqlStatement.append(") VALUES (");

    sqlStatement.append(GenerateColumnCollection(values));

    sqlStatement.append(endStatement);
    return sqlStatement;
}

std::string DatabaseController::GenerateUpdateStatement(std::string tableName, const KeyValCollection& values, const std::vector<WhereClause>& WhereClauses)
{
    std::string sqlStatement = "UPDATE " + tableName + " SET ";
    auto endStatement = ";";

    sqlStatement.append(GenerateKeyValCollection(values));

    sqlStatement.append(GenerateWhereClause(WhereClauses));
    sqlStatement.append(endStatement);

    return sqlStatement;
}

std::string DatabaseController::GenerateSelectStatement(std::string tableName, const ColumnCollection& cols, const std::vector<WhereClause>& WhereClauses)
{
	std::string sqlStatement = "SELECT ";
    auto endStatement = ";";

    sqlStatement.append(GenerateColumnCollection(cols));

    // < Add where clauses.
    sqlStatement.append(" FROM " + tableName);
    sqlStatement.append(GenerateWhereClause(WhereClauses));

    sqlStatement.append(endStatement);
	return sqlStatement;
}

std::string DatabaseController::GenerateDeleteStatement(std::string tableName, const std::vector<WhereClause>& WhereClauses)
{
	std::string sqlStatement = "DELETE FROM " + tableName;
    auto endStatement = ";";

    sqlStatement.append(GenerateWhereClause(WhereClauses));
    sqlStatement.append(endStatement);

	return sqlStatement;
}

std::string DatabaseController::GenerateFKConstraint(const std::string& colName, const std::string& fkTableName, const std::string& fkColumn)
{
	std::string sqlStatement = "FOREIGN KEY (" + colName + ") REFERENCES " + fkTableName + "(" + fkColumn + ");";

	return sqlStatement;
}

std::string DatabaseController::GenerateColumnCollection(const ColumnCollection& values)
{
    std::string cols = " ";

    // < Add columns.
    auto iter = values.begin();
    while (iter != values.end())
    {
        auto& val = (*iter);

        cols.append(val);

        ++iter;

        if (iter != values.end())
        {
            cols.append(", ");
        }
        else
        {
            cols.append(" ");
        }
    }

    return cols;
}

std::string DatabaseController::GenerateKeyValCollection(const KeyValCollection& keyValPair)
{
    std::string keyVals = " ";

    auto iter = keyValPair.begin();
    while (iter != keyValPair.end())
    {
        auto key = (*iter).first;
        auto val = (*iter).second;

        auto rowStatement = key + " = " + val;
        keyVals.append(rowStatement);

        ++iter;

        if (iter != keyValPair.end())
        {
            keyVals.append(", ");
        }
        else
        {
            keyVals.append(" ");
        }
    }

    return keyVals;
}

std::string DatabaseController::GenerateWhereClause(const std::vector<WhereClause>& keyValPair)
{
    if (keyValPair.empty()) { return ""; }

    std::string whereStatement = " WHERE ";

    auto iter = keyValPair.begin();
    while (iter != keyValPair.end())
    {
        auto key = std::get<0>((*iter));
        auto sign = std::get<1>((*iter));
        auto val = std::get<2>((*iter));

        whereStatement.append(key + " " + sign + " " + val);

        ++iter;

        if (iter != keyValPair.end())
        {
            whereStatement.append(" ");
        }
    }

    return whereStatement;
}

void DatabaseController::Update(unsigned long nMaxMillis)
{
    unsigned numConnectionsClosed = 0;
    unsigned long currMs = 0, maxMs = 0;

    currMs = Leadwerks::Time::GetCurrent();
    maxMs = ((nMaxMillis == DatabaseController::KINFINITE) ? (DatabaseController::KINFINITE) : (currMs + maxMs));

    while (!m_connections.empty())
    {
        auto iter = m_connections.begin();
        while (iter != m_connections.end())
        {
            (*iter)->Update();
            ++iter;
        }

        numConnectionsClosed += CleanupConnection();

        /* Check to see if processing time ran out */
        currMs = Leadwerks::Time::GetCurrent();
        if (nMaxMillis != DatabaseController::KINFINITE && currMs >= maxMs) {
            break;
        }
    }

}

bool DatabaseController::CleanupConnection(void)
{
    auto connection = m_connections.front();
    m_connections.pop_front();

    auto dbConnection = static_cast<DbConnection*>(connection);
    if (!DbConnection::HasConnectionState(dbConnection, CONNECTION_CLOSED))
    {
        // < Connection is still busy
        m_connections.push_back(connection);
        return false;
    }

    SAFE_DELETE(connection);
    assert(connection == nullptr);

    return true;
}