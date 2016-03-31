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
    auto connection = static_cast<DbConnection*>(m_connections.front());
    m_connections.pop_front();

    if (!DbConnection::HasConnectionState(connection, CONNECTION_CLOSED))
    {
        // < Connection is still busy
        m_connections.push_back(connection);
        return false;
    }

    SAFE_DELETE(connection);
    assert(connection == nullptr);

    return true;
}