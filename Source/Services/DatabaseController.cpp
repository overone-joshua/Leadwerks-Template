#pragma once
#include "DatabaseController.hpp"
#include "Leadwerks.h"
#include <crossguid/guid.h>

DatabaseController::DatabaseController(DbConnectionFactory* const dbConnectionFactory)
    : m_pDbConnectionFactory(dbConnectionFactory)
{
    assert(m_pDbConnectionFactory != nullptr);
}

DatabaseController::~DatabaseController(void)
{

}

std::vector<std::vector<std::string>> DatabaseController::ExecuteCommand(const std::string& query, bool bCloseConnection)
{
    GuidGenerator generator;

    auto guid = generator.newGuid();
    std::stringstream key;
    key << guid;

    auto connection = m_pDbConnectionFactory->CreateConnection(key.str());
    assert(connection != nullptr);

    m_connections.push_back(connection);

    auto command = connection->CreateCommand();
    assert(command != nullptr);

    auto result = command->Query(query.c_str());
    if (bCloseConnection)
    {
        SAFE_DELETE(command);
        assert(command == nullptr);
    }

    return result;
}

void DatabaseController::Update(unsigned long nMaxMillis)
{
    unsigned numConnectionsClosed = 0;
    unsigned long currMs = 0, maxMs = 0;

    currMs = Leadwerks::Time::GetCurrent();
    maxMs = ((nMaxMillis == DatabaseController::KINFINITE) ? (DatabaseController::KINFINITE) : (currMs + maxMs));

    while (!m_connections.empty())
    {
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
    auto connection = static_cast<DbConnection*>(m_connections.front());

    if (!DbConnection::HasConnectionState(connection, CONNECTION_CLOSED))
    {
        // < Connection is still busy
        return false;
    }

    SAFE_DELETE(connection);
    assert(connection == nullptr);

    return true;
}