/*-------------------------------------------------------
                    <copyright>

    File: Manager.hpp
    Language: C++

    (C) Copyright Eden Softworks

    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net

    Description: Header file for Manager base-class utility.
                 The Manager class provides a base for a
                 classes that meet the definition of a
                 Manager.

    Functions: 1. virtual void Update(float deltaTime) = 0;

               2. virtual void Render(void);

               3. virtual void Draw(void);

---------------------------------------------------------*/

#ifndef _MANAGER_HPP_
	#define _MANAGER_HPP_

#pragma once
#include "Disposable.hpp"

#include <cassert>

class Manager : public Disposable
{
public:

	Manager(void);
	virtual ~Manager(void);

	virtual void Update(float deltaTime) = 0;
	virtual void Render(void);
	virtual void Draw(void);

    void Dispose(void);

private:

	Manager* s_instance;

}; // end class.

#endif _MANAGER_HPP_