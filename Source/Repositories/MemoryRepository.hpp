#ifndef _MEMORY_REPOSITORY_HPP_
    #define _MEMORY_REPOSITORY_HPP_

#pragma once
#include "../Common.hpp"
#include "../Utilities/CacheCollection.hpp"
#include "../Utilities/CacheObject.hpp"

#include <cassert>
#include <functional>

template <typename T>
class MemoryRepository
{
public:

    MemoryRepository(int _size = -1);
    ~MemoryRepository(void);

    T& Add(T& _obj);

    void Clear(void);

    const bool Exists(const uint64_t& _id);

    std::vector<T> GetWhere(std::function<bool(T&)> _expression);

    T& Get(const uint64_t& _id);

    T& Set(const uint64_t& _id, T& _obj);

    void Remove(const uint64_t& _id);

protected:

    uint64_t GetNextIndex(void);

private:

    CacheCollection<T> m_cache;

    uint64_t m_nRunningIndex;

}; // < end class.

template <typename T>
MemoryRepository<T>::MemoryRepository(int _size)
    : m_cache(CacheCollection<T>(_size)), m_nRunningIndex(0)
{

}

template <typename T>
MemoryRepository<T>::~MemoryRepository(void)
{
    this->Clear();
}

template <typename T>
T& MemoryRepository<T>::Add(T& _obj)
{
    uint64_t index = this->GetNextIndex();
    _obj.nId = index;

    return this->m_cache.Add(index, _obj);
}

template <typename T>
void MemoryRepository<T>::Clear(void)
{
    this->m_cache.Clear();
}


template <typename T>
const bool MemoryRepository<T>::Exists(const uint64_t& _id)
{
    return this->m_cache.Exists();
}

template <typename T>
uint64_t MemoryRepository<T>::GetNextIndex(void)
{
    return ++this->m_nRunningIndex;
}

template <typename T>
std::vector<T> MemoryRepository<T>::GetWhere(std::function<bool(T&)> _expression)
{
    return this->m_cache.GetWhere(_expression);
}

template <typename T>
T& MemoryRepository<T>::Get(const uint64_t& _id)
{
    return this->m_cache.Get(_id);
}

template <typename T>
T& MemoryRepository<T>::Set(const uint64_t& _id, T& _obj)
{
    return this->m_cache.Set(_id, _obj);
}

template <typename T>
void MemoryRepository<T>::Remove(const uint64_t& _id)
{
    return this->m_cache.Remove(_id);
}

#endif _MEMORY_REPOSITORY_HPP_