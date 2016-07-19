#ifndef _BITMASK_HPP_
    #define _BITMASK_HPP

#pragma once
#include "../Common.hpp"

class Bitmask
{
private:

    uint64_t m_mask;

public:

    explicit Bitmask(void) : m_mask(0) { }

    Bitmask(const Bitmask& other)
    {
        this->m_mask = other.m_mask;
    }

    ~Bitmask(void) { m_mask = 0; }

    bool HasAnyStatus(uint64_t flags)
    {
        return HasAnyStatus(this->m_mask, flags);
    }

    static bool HasAnyStatus(uint64_t existingFlags, uint64_t flagsToCheck)
    {
        return (existingFlags & flagsToCheck) != 0;
    }

    bool HasStatus(uint64_t flags)
    {
        return HasStatus(this->m_mask, flags);
    }

    static bool HasStatus(uint64_t existingFlags, uint64_t flagsToCheck)
    {
        return (existingFlags & flagsToCheck) == flagsToCheck;
    }

    void AddStatus(uint64_t status)
    {
        this->m_mask |= status;
    }

    void RemoveStatus(uint64_t status)
    {
        this->m_mask &= ~status;
    }

    uint64_t Status(void)
    {
        return this->m_mask;
    }

    void SetStatus(uint64_t status)
    {
        this->m_mask = status;
    }

    void SetStatus(const Bitmask& other)
    {
        this->m_mask = other.m_mask;
    }

    static void SetStatus(Bitmask& original, const Bitmask& other)
    {
        original.m_mask = other.m_mask;
    }

    /*Bitmask operator = (const Bitmask& other)
    {
        auto self = *this;

        self.m_mask = other.m_mask;

        return self;
    
    }*/

}; // < end class.

#endif _BITMASK_HPP_