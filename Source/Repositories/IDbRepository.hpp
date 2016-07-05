#ifndef _IDBREPOSITORY_HPP_
    #define _IDBREPOSITORY_HPP_

#pragma once
#include "../Common.hpp"
#include "../Utilities/Disposable.hpp"
#include "../Utilities/Macros.hpp"

#include <string>
#include <vector>

template <typename T>
class IDbRepository : virtual IDisposable
{

    CLASS_TYPE(IDbRepository);

public:

    virtual ~IDbRepository(void) { }

    virtual void DeleteById(uint64_t _id) = 0;

    virtual std::vector<T> FindByEntityId(uint64_t _entityId) = 0;

    virtual T FindById(uint64_t _id) = 0;

    virtual std::vector<T> FindByName(const std::string& _name) = 0;

    virtual T Save(const T& _comp) = 0;

    virtual T SaveDeferred(const T& _comp) = 0;

    virtual void Update(void) = 0;

}; // < end class.

#endif _IDBREPOSITORY_HPP