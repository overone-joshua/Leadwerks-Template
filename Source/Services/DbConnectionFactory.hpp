#ifndef _DBCONNECTION_FACTORY_HPP_
    #define _DBCONNECTION_FACTORY_HPP_

#pragma once
#include "../Utilities/Macros.hpp"
#include "../Utilities/Disposable.hpp"

#include "../Utilities/sqlite/ConnectionState.hpp"
#include "../Utilities/sqlite/DbConnection.hpp"
#include "../Utilities/sqlite/DbConnectionOptions.hpp"
#include "../Utilities/sqlite/DbCommand.hpp"

#include <cassert>
#include <map>
#include <string>

class IDbConnectionFactory : virtual IDisposable
{
    CLASS_TYPE(IDbConnectionFactory);

public:

    virtual IDbConnection* const OpenConnection(const std::string& key) = 0;
    virtual IDbConnection* const CreateConnection(const std::string& key) = 0;

    virtual IDbConnection* const GetLastConnection(void) = 0;
    virtual unsigned long LastInsertRowId(void) = 0;

}; // < end class interface.

class DbConnectionFactory : public IDbConnectionFactory, public Disposable
{
    CLASS_TYPE(DbConnectionFactory);

    typedef std::map<const std::string, DbConnection* const> ConnectionPool;

public:
    DbConnectionFactory(const std::string& connectionString)
    {
        DbConnectionOptions options;

        Initialize(connectionString, options);
    }

    DbConnectionFactory(const std::string& connectionString, const DbConnectionOptions options)
    {
        Initialize(connectionString, options);
    }

    ~DbConnectionFactory(void)
    {
        Dispose();
    }

    IDbConnection* const OpenConnection(const std::string& key)
    {
        auto connection = CreateConnection(key);

        assert(connection != nullptr);

        if (DbConnection::HasConnectionState(static_cast<DbConnection*>(connection), CONNECTION_CLOSED))
        {
            connection->Open();
        }

        // < Set the last used connection.
        m_pLastConnection = connection;

        return connection;
    }

    IDbConnection* const CreateConnection(const std::string& key)
    {
        auto iter = m_connectionPool.insert(std::make_pair(key, new DbConnection(this, m_connectionString, m_connectionOptions)));
        if (!iter.second)
        {
            // < Already exists .
        }
        else
        {
            // < Created .
        }

        return (*iter.first).second;
    }

    const DbConnection* FetchConnection(const std::string& key)
    {
        auto iter = FetchConnectionInternal(key);
        if (iter != m_connectionPool.end()) { return (*iter).second; }

        return nullptr;
    }

    IDbConnection* const GetLastConnection(void)
    {
        return m_pLastConnection;
    }

    unsigned long LastInsertRowId(void)
    {
        return m_nLastInsertRowId;
    }

    void Dispose(void)
    {
        m_connectionString = "";
        auto iter = m_connectionPool.begin();
        while (iter != m_connectionPool.end())
        {
            auto& connection = (*iter).second;

            if (DbConnection::HasAnyConnectionState(connection, CONNECTION_OPEN))
            {
                connection->Close(true);
            }

            connection->Dispose();
            if (connection != nullptr) { delete connection; }

            iter = m_connectionPool.erase(iter);

            if (iter != m_connectionPool.end())
            {
                ++iter;
            }
        }
        m_connectionPool.clear();
    }

protected:

    bool Initialize(const std::string& connectionString, const DbConnectionOptions& options)
    {
        assert(connectionString.compare("") != 0);

        m_connectionString = connectionString;

        return true;
    }

    ConnectionPool::iterator FetchConnectionInternal(const std::string& key)
    {
        return m_connectionPool.find(key);
    }

private:

    std::string m_connectionString;
    unsigned long m_nLastInsertRowId;

    ConnectionPool m_connectionPool;
    DbConnectionOptions m_connectionOptions;

    IDbConnection* m_pLastConnection;

    friend DbConnection;

}; // < end class.

#endif _DBCONNECTION_FACTORY_HPP_