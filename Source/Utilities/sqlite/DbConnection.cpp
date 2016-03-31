#pragma once
#include "DbConnection.hpp"
#include "Leadwerks.h"

#include "../Macros.hpp"
#include "ConnectionState.hpp"
#include "DbCommand.hpp"

DbConnection::DbConnection(const std::string& connectionString, const DbConnectionOptions options)
    : m_pDatabase(nullptr), m_connectionString(connectionString), m_connectionState(CONNECTION_CLOSED)
    , m_connectionOptions(options)
{
    m_nBeganExecution = Leadwerks::Time::GetCurrent();
}

DbConnection::~DbConnection(void)
{
    Dispose();
}

void DbConnection::Dispose(void)
{
    Close(true);
}

unsigned DbConnection::GetConnectionState(void) { return m_connectionState; }

void DbConnection::SetConnectionState(unsigned connectionStateMask) { this->m_connectionState = connectionStateMask; }

const void DbConnection::Open(void)
{
    if (m_pDatabase != nullptr && HasConnectionState(this, CONNECTION_CLOSED))
    {
        return;
    }

    AddConnectionState(this, CONNECTION_CONNECTING);

    auto res = sqlite3_open(m_connectionString.c_str(), &m_pDatabase);
    assert(res == SQLITE_OK);

    this->SetConnectionState(CONNECTION_OPEN);
}

const void DbConnection::Close(bool bForce)
{
    // < We do not want to close a connection preemptively
    // * unless explicitly told to force-close the connection.
    if (m_pDatabase == nullptr || !bForce || !HasConnectionState(this, CONNECTION_OPEN))
    {
        return;
    }

    AddConnectionState(this, CONNECTION_CLOSING);

    // < Clean up all commands associated with this connection.
    auto iter = m_commands.begin();
    while (iter != m_commands.end())
    {
        auto command = (*iter);
        if (command != nullptr)
        {
            SAFE_DELETE(command);
            assert(command == nullptr);
        }

        iter = m_commands.erase(iter);

        if (iter != m_commands.end())
        {
            ++iter;
        }
    }
    m_commands.clear();

    auto res = sqlite3_close(m_pDatabase);
    assert(res == SQLITE_OK);

    this->SetConnectionState(CONNECTION_CLOSED);
}

IDbCommand* const DbConnection::CreateCommand(void)
{
    assert(m_pDatabase != nullptr);
    assert(HasConnectionState(this, CONNECTION_OPEN) == true);

    auto command = new DbCommand(m_pDatabase, this);
    m_commands.push_back(command);

    return command;
}

std::vector<std::vector<std::string>> DbConnection::ExecuteCommand(IDbCommand* const command, const char* query)
{
    assert(HasConnectionState(this, CONNECTION_OPEN));

    AddConnectionState(this, CONNECTION_EXECUTING);
    auto result = command->Query(query);

    DestroyCommand(command);

    if (m_commands.empty() && HasAnyConnectionState(this, CONNECTION_EXECUTING))
    {
        RemoveConnectionState(this, CONNECTION_EXECUTING);
    }

    return result;
}

void DbConnection::DestroyCommand(IDbCommand* command)
{
    if (command != nullptr)
    {
        SAFE_DELETE(command);
        assert(command == nullptr);
    }
}

void DbConnection::Update(void)
{
    // < If the connection has been around for longer than its lifespan,
    // * close it so it may be cleaned up appropriately.
    auto timespan = m_connectionOptions.nTimeout;
    if (timespan > 0 && m_nBeganExecution + timespan <= Leadwerks::Time::GetCurrent())
    {
        this->Close(true);
    }
}

const void DbConnection::AddConnectionState(DbConnection* const connection, unsigned connectionStateMask)
{
    auto& mask = connection->m_connectionState;
    mask |= connectionStateMask;

    connection->SetConnectionState(mask);
}

const void DbConnection::RemoveConnectionState(DbConnection* const connection, unsigned connectionStateMask)
{
    auto& mask = connection->m_connectionState;
    mask &= ~connectionStateMask;

    connection->SetConnectionState(mask);
}