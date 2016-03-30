#ifndef _DBCONNECTION_FACTORY_HPP_
    #define _DBCONNECTION_FACTORY_HPP_

#pragma once
#include "../Utilities/Macros.hpp"

#include "../Utilities/sqlite/ConnectionState.hpp"
#include "../Utilities/sqlite/DbConnection.hpp"
#include "../Utilities/sqlite/DbCommand.hpp"

#include <cassert>
#include <map>
#include <string>

class IDbConnectionFactory
{
    CLASS_TYPE(IDbConnectionFactory);

public:

    virtual IDbConnection* const OpenConnection(void) { return nullptr; }
    virtual IDbConnection* const CreateConnection(void) { return nullptr; }

}; // < end class interface.

class DbConnectionFactory : public IDbConnectionFactory
{
    CLASS_TYPE(DbConnectionFactory);

    typedef std::map<const std::string, DbConnection* const> ConnectionPool;

public:
    DbConnectionFactory(const std::string& connectionString)
        : m_connectionString(connectionString)
    {
        assert(connectionString.compare("") != 0);
    }

    ~DbConnectionFactory(void)
    {
        Dispose();
    }

    IDbConnection* const OpenConnection(const std::string& key)
    {
        auto connection = CreateConnection(key);

        assert(connection != nullptr);

        if (!DbConnection::HasConnectionState(static_cast<DbConnection*>(connection), CONNECTION_OPEN))
        {
            connection->Open();
        }

        return connection;
    }

    IDbConnection* const CreateConnection(const std::string& key)
    {
        auto iter = m_connectionPool.insert(std::make_pair(key, new DbConnection(m_connectionString)));
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

    void Dispose(void)
    {
        m_connectionString = "";
        auto iter = m_connectionPool.begin();
        while (iter != m_connectionPool.end())
        {
            auto& connection = (*iter).second;

            if (DbConnection::HasConnectionState(connection, CONNECTION_OPEN))
            {
                connection->Close();
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

    ConnectionPool::iterator FetchConnectionInternal(const std::string& key)
    {
        return m_connectionPool.find(key);
    }

private:

    std::string m_connectionString;

    ConnectionPool m_connectionPool;

}; // < end class.

#endif _DBCONNECTION_FACTORY_HPP_