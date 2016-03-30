/*-------------------------------------------------------
                    <copyright>

    File: ModelHandle.hpp
    Language: C++

    (C) Copyright Eden Softworks

    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net

    Description: Header file for ModelHandle utility.
                 The ModelHandle is a wrapper around
                 the Leadwerks::Model object.

    Functions: 1. Leadwerks::Model* getInst(void);

---------------------------------------------------------*/

#ifndef _MODEL_HANDLE_HPP_
    #define _MODEL_HANDLE_HPP_

#pragma once
#include "Leadwerks.h"
#include "Disposable.hpp"
#include "Macros.hpp"

class ModelHandle : public Disposable
{
    CLASS_TYPE(ModelHandle);

public:

    explicit ModelHandle(Leadwerks::Model* pModel)
        :m_pModel(pModel) { }

    ~ModelHandle(void)
    {
        Dispose();
    }

    void Dispose(void)
    {
        SAFE_RELEASE(m_pModel);
        SAFE_DELETE(m_pModel);
    }

    Leadwerks::Model* getInst(void) { return m_pModel; }

    static inline Leadwerks::Model* Load(std::string cModelPath) { return Leadwerks::Model::Load(cModelPath); }

private:

    Leadwerks::Model* m_pModel;

}; // < end class.

#endif _MODEL_HANDLE_HPP_