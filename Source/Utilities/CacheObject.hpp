#ifndef _CACHE_OBJECT_HPP
    #define _CACHE_OBJECT_HPP_

#pragma once
#include "../Common.hpp"

#include <memory>

template <typename T>
class CacheObject
{
public:

    CacheObject() { }

    CacheObject(uint64_t _id, const T& _obj, unsigned _scalar = 6000 /* 6 seconds*/)
        : _pObj(_obj), _nLifespan(_scalar), _nScalar(_scalar)
    {
        this->_nId = _id;
        this->_nLifeTime = 0;
    }

    ~CacheObject(void) { }

    int _nLifespan;    // < The amount of time this object can remain in memory.
    int _nLifeTime;    // < The amount of time this object has been in memory.
    unsigned _nScalar;      // < The amount of time to increase the Lifespan by when accessed.

    T& GetInst(void)
    {
        return this->_pObj;
    }

    // < TODO:
    CacheObject<T> Merge(const CacheObject<T> _other)
    {
        auto self = *this;

        std::swap(self._pObj, _other._pObj);

        self._nLifespan = other._nLifespan;
        self._nLifeTime = other._nLifeTime;
        self._nScalar = other._nScalar;

        return self;
    }

    void Set(T& _pObj)
    {
        std::swap(this->_pObj, _pObj);
        //this->_pObj = _pObj;
    }

    void IncrementLifespan(void)
    {
        if (this->_nLifespan != -1)
        {
            this->_nLifespan += this->_nScalar;
        }
    }

private:

    uint64_t _nId;  // < The unique identifier for this cache object.
    T _pObj;        // < Pointer to the object stored in memory.

}; // < end class.

#endif _CACHE_OBJECT_HPP_