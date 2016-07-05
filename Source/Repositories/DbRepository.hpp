#ifndef _DBREPOSITORY_HPP_
    #define _DBREPOSITORY_HPP_

#pragma once
#include "IDbRepository.hpp"

#include "../Common.hpp"
#include "../Utilities/CacheCollection.hpp"
#include "../Utilities/Disposable.hpp"
#include "../Utilities/Macros.hpp"

#include <sqlite-persistence/DbCommand.hpp>
#include <sqlite-persistence/DbConnection.hpp>

#include <string>
#include <vector>

// < TODO: Repositories should be able to save a collection of components.
template <typename T>
class DbRepository : public IDbRepository<T>, public Disposable
{
    CLASS_TYPE(DbRepository);

public:

    explicit DbRepository(IDbConnection* _pConnection);

    virtual ~DbRepository(void);

    virtual void Dispose(void);

    virtual void DeleteById(uint64_t _id) = 0;

    virtual std::vector<T> FindByEntityId(uint64_t _entityId) = 0;

    virtual T FindById(uint64_t _id) = 0;

    virtual std::vector<T> FindByName(const std::string& _name) = 0;

    virtual T Save(const T& _comp) = 0;

    virtual void Update(void) = 0;

protected:

    void ExecuteNonQuery(const std::string& _query);

    IDbConnection* m_pConnection;

    DbCommand* m_pCurrentCommand;

    CacheCollection<T> m_cache;

private:

}; // < end class.


template <typename T>
DbRepository<T>::DbRepository(IDbConnection* _pConnection)
    : m_pConnection(_pConnection), m_pCurrentCommand(nullptr)
    , m_cache(CacheCollection<T>(10)) { }

template <typename T>
DbRepository<T>::~DbRepository(void) { }

template <typename T>
void DbRepository<T>::Dispose(void)
{
    this->m_pConnection = nullptr;
}

template <typename T>
void DbRepository<T>::ExecuteNonQuery(const std::string& _query)
{
    this->m_pCurrentCommand = this->m_pConnection->CreateCommand(new DbQuery(_query));
    this->m_pCurrentCommand->ExecuteNonQuery();
}

#endif _DBREPOSITORY_HPP_