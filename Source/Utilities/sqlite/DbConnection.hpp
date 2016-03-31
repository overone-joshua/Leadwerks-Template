#ifndef _DBCONNECTION_HPP_
    #define _DBCONNECTION_HPP_

#pragma once
#include "../Disposable.hpp"

#include "sqlite3.h"

#include "DbConnectionOptions.hpp"

#include <cassert>
#include <string>
#include <map>
#include <vector>

class IDbCommand;
class DbCommand;

class IDbConnection : virtual IDisposable
{
public:

    virtual const void Open(void) = 0;
    virtual const void Close(bool bForce = true) = 0;

    virtual IDbCommand* const CreateCommand(void) = 0;
    virtual std::vector<std::vector<std::string>> ExecuteCommand(IDbCommand* const command, const char* query) = 0;

    virtual void Update(void) = 0;

}; // < end class interface.

class DbConnection : public IDbConnection, public Disposable
{
protected:

public:

    DbConnection(const std::string& connectionString, const DbConnectionOptions options);

    ~DbConnection(void);

    const void Open(void);

    const void Close(bool bForce = false);

    IDbCommand* const CreateCommand(void);
    std::vector<std::vector<std::string>> ExecuteCommand(IDbCommand* const command, const char* query);

    static inline bool HasConnectionState(const DbConnection* connection, unsigned connectionStateMask);
    static inline bool HasAnyConnectionState(const DbConnection* connection, unsigned connectionStateMask);

    void Update(void);

    void Dispose(void);

protected:

    static inline const void AddConnectionState(DbConnection* const connection, unsigned connectionStateMask);

    static inline const void RemoveConnectionState(DbConnection* const connection, unsigned connectionStateMask);

    unsigned GetConnectionState(void);
    void SetConnectionState(unsigned connectionStateMask);

    void DestroyCommand(IDbCommand* command);

private:

    sqlite3* m_pDatabase;

    DbConnectionOptions m_connectionOptions;
    std::string m_connectionString;

    unsigned long m_nBeganExecution;
    unsigned m_connectionState;

    std::vector<IDbCommand* const> m_commands;

}; // < end class.

bool DbConnection::HasConnectionState(const DbConnection* connection, unsigned connectionStateMask)
{
    auto mask = connection->m_connectionState;

    return ((mask & connectionStateMask) == connectionStateMask);
}

bool DbConnection::HasAnyConnectionState(const DbConnection* connection, unsigned connectionStateMask)
{
    auto mask = connection->m_connectionState;

    return (bool(mask & connectionStateMask));
}

#endif _DBCONNECTION_HPP_
