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

void DatabaseController::CreateTable(std::string tableName, const std::vector<std::tuple<std::string, std::string, std::string>>& table)
{
    auto sql = GenerateCreateStatement(tableName, table);

    ExecuteCommand(sql);
}

unsigned long DatabaseController::InsertRecord(std::string tableName, const std::vector<std::string>& cols, const std::vector<std::string>& values)
{
    auto sql = GenerateInsertStatement(tableName, cols, values);

    // < A sqlite Delete will not return the deleted rows so
    // * the DbCommand is written to return one record
    // * containing the number of affected rows.
    auto rowsAffected = std::stoi(ExecuteCommand(sql).front().front());
    return rowsAffected;
}

void DatabaseController::UpdateRecord(std::string tableName, const std::vector<std::pair<std::string, std::string>>& values, const std::vector<std::pair<std::string, std::string>>& WhereClauses)
{
    auto sql = GenerateUpdateStatement(tableName, values, WhereClauses);

    ExecuteCommand(sql);
}

std::vector<std::vector<std::string>> DatabaseController::SelectRecords(std::string tableName, const std::vector<std::string>& cols, const std::vector<std::pair<std::string, std::string>>& WhereClauses)
{
	auto sql = GenerateSelectStatement(tableName, cols, WhereClauses);

	return ExecuteCommand(sql);
}

unsigned long DatabaseController::DeleteRecords(std::string tableName, const std::vector<std::pair<std::string, std::string>>& WhereClauses)
{
	auto sql = GenerateDeleteStatement(tableName, WhereClauses);

    auto rowsAffected = std::stoi(ExecuteCommand(sql).front().front());
	return rowsAffected;
}

std::string DatabaseController::GenerateCreateStatement(std::string tableName, const std::vector<std::tuple<std::string, std::string, std::string>>& table)
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

std::string DatabaseController::GenerateInsertStatement(std::string tabelName, const std::vector<std::string>& cols, const std::vector<std::string>& values)
{
    std::string sqlStatement = "INSERT INTO " + tabelName + " (";
    auto endStatement = ");";

    auto iter = cols.begin();
    while (iter != cols.end())
    {
        sqlStatement.append((*iter));

        ++iter;

        if (iter != cols.end())
        {
            sqlStatement.append(", ");
        }
    }

    sqlStatement.append(") VALUES (");

    auto iter2 = values.begin();
    while (iter2 != values.end())
    {
        auto val = (*iter2);
        sqlStatement.append(val);

        ++iter2;

        if (iter2 != values.end())
        {
            sqlStatement.append(", ");
        }
    }

    sqlStatement.append(endStatement);
    return sqlStatement;
}

std::string DatabaseController::GenerateUpdateStatement(std::string tableName, const std::vector<std::pair<std::string, std::string>>& values, const std::vector<std::pair<std::string, std::string>>& WhereClauses)
{
    std::string sqlStatement = "UPDATE " + tableName + " SET ";
    auto endStatement = ";";

    auto iter = values.begin();
    while (iter != values.end())
    {
        auto key = (*iter).first;
        auto val = (*iter).second;

        auto rowStatement = key + " = " + val;
		sqlStatement.append(rowStatement);

        ++iter;

        if (iter != values.end())
        {
            sqlStatement.append(", ");
        }
    }

    // < Add where clauses.
    sqlStatement.append(" WHERE ");

    auto iter2 = WhereClauses.begin();
    while (iter2 != WhereClauses.end())
    {
        auto key = std::get<0>((*iter2));
        auto val = std::get<1>((*iter2));

        auto rowStatement = key + " = " + val;
        sqlStatement.append(rowStatement);

        ++iter2;

        if (iter2 != WhereClauses.end())
        {
            sqlStatement.append(", ");
        }
    }

    sqlStatement.append(endStatement);
    return sqlStatement;
}

std::string DatabaseController::GenerateSelectStatement(std::string tableName, const std::vector<std::string>& cols, const std::vector<std::pair<std::string, std::string>>& WhereClauses)
{
	std::string sqlStatement = "SELECT ";
    auto endStatement = ";";

    // < Add columns.
    auto iter = cols.begin();
    while (iter != cols.end())
    {
        auto& val = (*iter);

        sqlStatement.append(val);

        ++iter;

        if (iter != cols.end())
        {
            sqlStatement.append(", ");
        }
    }

    // < Add where clauses.
    sqlStatement.append(" FROM " + tableName + " WHERE ");

    auto iter2 = WhereClauses.begin();
    while (iter2 != WhereClauses.end())
    {
        auto key = std::get<0>((*iter2));
        auto val = std::get<1>((*iter2));

        auto rowStatement = key + " = " + val;
        sqlStatement.append(rowStatement);

        ++iter2;

        if (iter2 != WhereClauses.end())
        {
            sqlStatement.append(", ");
        }
    }

    sqlStatement.append(endStatement);
	return sqlStatement;
}

std::string DatabaseController::GenerateDeleteStatement(std::string tableName, const std::vector<std::pair<std::string, std::string>>& WhereClauses)
{
	std::string sqlStatement = "DELETE FROM " + tableName + " WHERE ";
    auto endStatement = ";";

    auto iter = WhereClauses.begin();
    while (iter != WhereClauses.end())
    {
        auto key = std::get<0>((*iter));
        auto val = std::get<1>((*iter));

        sqlStatement.append(key + " = " + val);

        ++iter;

        if (iter != WhereClauses.end())
        {
            sqlStatement.append(", ");
        }
    }

	return sqlStatement;
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