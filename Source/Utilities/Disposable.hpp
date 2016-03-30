#ifndef _DISPOSABLE_HPP_
    #define _DISPOSABLE_HPP_

#pragma once

class IDisposable
{
public:

    virtual void Dispose(void) = 0;

}; // < end class interface.

class Disposable : IDisposable
{
public:

    void Dispose(void) { }

}; // < end class.

#endif _DISPOSABLE_HPP_