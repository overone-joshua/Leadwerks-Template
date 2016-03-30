#ifndef _DBCONNECTION_HPP_
    #define _DBCONNECTION_HPP_

#pragma once
#include "ConnectionState.hpp"
#include "DbCommand.hpp"

#include <sqlite/sqlite3.h>

#include <string>

class IDbConnection
{
public:

    virtual const void Open(void) = 0;
    virtual const void Close(bool bForce = true) = 0;

    virtual IDbCommand* const CreateCommand(void) = 0;

}; // < end class interface.

class DbConnection : public IDbConnection
{
protected:

public:

    DbConnection(const std::string& connectionString)
        : m_pDatabase(nullptr), m_connectionString(connectionString), m_connectionState(CONNECTION_CLOSED)
    {

    }

    ~DbConnection(void)
    {
        Dispose();
    }

    const void Open(void)
    {
        if (m_pDatabase != nullptr && HasConnectionState(this, CONNECTION_CLOSED))
        {
            return;
        }

        AddConnectionState(this, CONNECTION_CONNECTING);

        auto res = sqlite3_open(m_connectionString.c_str(), m_pDatabase);
        assert(res == SQLITE_OK);

        this->SetConnectionState(CONNECTION_OPEN);
    }

    const void Close(bool bForce = false)
    {
        // < We do not want to close a connection preemptively.
        if (m_pDatabase == nullptr || bForce || !HasConnectionState(this, CONNECTION_OPEN))
        {
            return;
        }

        AddConnectionState(this, CONNECTION_CLOSING);

        auto res = sqlite3_close(*m_pDatabase);
        assert(res == SQLITE_OK);

        this->SetConnectionState(CONNECTION_CLOSED);
    }

    IDbCommand* const CreateCommand(void)
    {
        assert(m_pDatabase != nullptr);
        assert(HasConnectionState(this, CONNECTION_OPEN) == true);

        auto command = new DbCommand(*m_pDatabase);

        return command;
    }

    static inline bool HasConnectionState(const DbConnection* connection, unsigned connectionStateMask)
    {
        auto mask = connection->m_connectionState;

        return ((mask & connectionStateMask) == connectionStateMask);
    }

    static inline bool HasAnyConnectionState(const DbConnection* connection, unsigned connectionStateMask)
    {
        auto mask = connection->m_connectionState;

        return (bool(mask & connectionStateMask));
    }

    void Dispose(void)
    {
        Close(true);
    }

protected:

    static inline const void AddConnectionState(DbConnection* const connection,  unsigned connectionStateMask)
    {
        auto& mask = connection->m_connectionState;
        mask |= connectionStateMask;

        connection->SetConnectionState(mask);
    }

    static inline const void RemoveConnectionState(DbConnection* const connection, unsigned connectionStateMask)
    {
        auto& mask = connection->m_connectionState;
        mask &= ~connectionStateMask;

        connection->SetConnectionState(mask);
    }

    unsigned GetConnectionState(void) { return m_connectionState; }
    void SetConnectionState(unsigned connectionStateMask) { this->m_connectionState = connectionStateMask; }

private:

    sqlite3** m_pDatabase;

    int m_connectionTimout;
    std::string m_connectionString;

    unsigned m_connectionState;

}; // < end class.

#endif _DBCONNECTION_HPP_
