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

void DatabaseController::InsertRecord(std::string tableName, const std::vector<std::string>& row)
{
    auto sql = GenerateInsertStatement(tableName, row);

    ExecuteCommand(sql);
}

void DatabaseController::UpdateRecord(std::string tableName, const std::pair<std::string, std::string>& MatchKey, const std::vector<std::pair<std::string, std::string>>& values)
{
    auto sql = GenerateUpdateStatement(tableName, MatchKey, values);

    ExecuteCommand(sql);
}

std::string DatabaseController::GenerateCreateStatement(std::string tableName, const std::vector<std::tuple<std::string, std::string, std::string>>& table)
{
    auto sqlStatement = "CREATE TABLE " + tableName + " (";
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

std::string DatabaseController::GenerateInsertStatement(std::string tabelName, const std::vector<std::string>& row)
{
    auto sqlStatement = "INSERT INTO " + tabelName + " VALUES (";
    auto endStatement = ");";

    auto iter = row.begin();
    while (iter != row.end())
    {
        auto val = (*iter);
        sqlStatement.append(val);

        ++iter;

        if (iter != row.end())
        {
            sqlStatement.append(", ");
        }
    }

    sqlStatement.append(endStatement);
    return sqlStatement;
}

std::string DatabaseController::GenerateUpdateStatement(std::string tableName, const std::pair<std::string, std::string>& MatchKey, const std::vector<std::pair<std::string, std::string>>& values)
{
    auto sqlStatement = "UPDATE " + tableName + " SET ";
    auto endStatement = " WHERE " + MatchKey.first + " = " + MatchKey.second;

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

    sqlStatement.append(endStatement);
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