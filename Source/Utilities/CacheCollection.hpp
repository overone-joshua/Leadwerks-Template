#ifndef _CACHE_COLLECTION_HPP_
    #define _CACHE_COLLECTION_HPP_

#pragma once
#include "CacheObject.hpp"
#include "../Common.hpp"

#include <cassert>
#include <functional>
#include <memory>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

template <typename T>
class CacheCollection
{
public:

    CacheCollection(int _size);
    ~CacheCollection(void);

    T& Add(const uint64_t& _id, T& _obj);

    void Clear(void);

    const bool Exists(const uint64_t& _id);

    std::vector<T> GetWhere(std::function<bool(T&)> _expression);

    T& Get(const uint64_t& _id);

    T& Set(const uint64_t& _id, T& _obj);

    void Remove(const uint64_t& _id);

    void Update(void);

protected:

private:

    int _cacheSize;    // < The total # of objects that can be within the cache
                       // * collection at any given time.

    std::queue<uint64_t> m_deletionQueue;
    std::unordered_map<uint64_t, CacheObject<T>> m_cache;

}; // < end class.

template <typename T>
CacheCollection<T>::CacheCollection(int _size)
    : m_cache(std::unordered_map<uint64_t, CacheObject<T>>())
    , _cacheSize(_size) { }

template <typename T>
CacheCollection<T>::~CacheCollection(void)
{
    Clear();
}

template <typename T>
void CacheCollection<T>::Clear(void)
{
    this->m_cache.clear();
}

template <typename T>
T& CacheCollection<T>::Add(const uint64_t& _id, T& _pObj)
{
    assert(this->_cacheSize > 0 || this->_cacheSize == -1);

    auto it = this->m_cache.find(_id);
    if (it != this->m_cache.end())
    {
        // < Already exists.
        return this->Set(_id, _pObj);
    }

    // < Have we reached our cache limit?
    if (this->m_cache.size() != -1 && this->m_cache.size() >= this->_cacheSize)
    {
        // < Find the least-accessed object within the cache
        // * and replace it.
        auto it = this->m_cache.begin();
        auto iter = this->m_cache.begin();
        while (iter != this->m_cache.end())
        {
            CacheObject<T> current = (*it).second;
            CacheObject<T> next = (*iter).second;

            if (next._nLifeTime < current._nLifeTime)
            {
                it = iter;
            }

            ++iter;
        }

        this->m_cache.erase(it);
    }

    // < Returns a pair consisting of an iterator to the inserted
    // * element (or to the element that prevented the insertion)
    // * and a bool denoting whether the insertion took place.
    return (*(this->m_cache.insert({ _id, CacheObject<T>(_id, _pObj) }).first)).second.GetInst();
}

template <typename T>
const bool CacheCollection<T>::Exists(const uint64_t& _id)
{
    return this->m_cache.find(_id) != this->m_cache.end();
}

template <typename T>
std::vector<T> CacheCollection<T>::GetWhere(std::function<bool(T&)> _expression)
{
    std::vector<T> res;

    auto iter = this->m_cache.begin();
    while (iter != this->m_cache.end())
    {
        T& it = (*iter).second.GetInst();

        if (_expression(it)) { res.push_back(it); }
        ++iter;
    }

    return res;
}

template <typename T>
T& CacheCollection<T>::Get(const uint64_t& _id)
{
    assert(this->_cacheSize > 0 || this->_cacheSize == -1);

    auto iter = this->m_cache.find(_id);
    if (iter == this->m_cache.end())
    {
        throw "Object with given id does not exist in cache!";
    }

    CacheObject<T> it = (*iter).second;

    return it.GetInst();
}

template <typename T>
T& CacheCollection<T>::Set(const uint64_t& _id, T& _pObj)
{
    assert(this->_cacheSize > 0 || this->_cacheSize == -1);

    std::unordered_map<uint64_t, CacheObject<T>>::iterator it = this->m_cache.find(_id);
    if (it == this->m_cache.end())
    {
        throw "Object with given id does not exist in cache!";
    }

    // < Object found.
    uint64_t id = (*it).first;
    CacheObject<T> obj = (*it).second;

    obj.IncrementLifespan();
    (*it).second.Set(_pObj);

    return (*it).second.GetInst();
}

template <typename T>
void CacheCollection<T>::Remove(const uint64_t& _id)
{
    assert(this->_cacheSize > 0 || this->_cacheSize == -1);

    auto it = this->m_cache.find(_id);
    if (it == this->m_cache.end())
    {
        // < Does not exist.
        return;
    }

    this->m_cache.erase(it);
}

template <typename T>
void CacheCollection<T>::Update(void)
{
    assert(this->_cacheSize > 0 || this->_cacheSize == -1);

    auto iter = this->m_cache.begin();
    while (iter != this->m_cache.end())
    {
        auto current = (*iter);

        uint64_t id = current.first;
        CacheObject<T> obj = current.second;

        if (obj._nLifeTime >= obj._nLifespan)
        {
            // < Object has been inactive, queue
            // * for deletion.
            this->m_deletionQueue.push(id);

            continue;
        }

        // < A lifetime less-than 0, will allow the object
        // * to remain in memory until manually removed.
        if (obj._nLifeTime >= 0)
        {
            // < Increment lifetime counter.
            obj._nLifeTime += 1;
        }

        ++iter;
    }

    auto index = 0;
    while (!this->m_deletionQueue.empty() && index < 8)
    {
        uint64_t id = this->m_deletionQueue.front();
        auto it = this->m_cache.find(id);
        this->m_cache.erase(it);

        this->m_deletionQueue.pop();
        ++index;
    }
}

#endif _CACHE_COLLECTION_HPP_
