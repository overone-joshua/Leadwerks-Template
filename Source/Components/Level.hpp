#ifndef _LEVEL_HPP_
    #define _LEVEL_HPP_

#pragma once
#include "Component.hpp"

#include "../Common.hpp"
#include "../Utilities/Bitmask.hpp"
#include "../Utilities/Macros.hpp"
#include "../Utilities/Voxel.hpp"
#include "../Utilities/VoxelBuffer.hpp"

#include <cassert>
#include <list>
#include <string>

namespace Components
{
    typedef struct Component_Level : public Component
    {
        CLASS_TYPE(Level);

        VoxelBuffer<Voxel*> pBuffer;
        Leadwerks::Model* pModel;

        float nSize;
        Bitmask inputMask;

        bool bDirty;

        explicit Component_Level(uint64_t _nEntityId, Leadwerks::Material* _pDefMaterial = nullptr, unsigned _nWidth = 1, unsigned _nHeight = 1, unsigned _nDepth = 1, float _nSize = 1.0f, const std::string& _cName = "")
            : pBuffer(_nWidth, _nHeight, _nDepth), bDirty(false), nSize(_nSize), Component(_nEntityId, _cName)
        {
            assert(_pDefMaterial != nullptr);
            assert(_nWidth >= 1);
            assert(_nHeight >= 1);
            assert(_nDepth >= 1);
            assert(_nSize >= 0.25f);

            pModel = nullptr;
            inputMask = Bitmask();
        }

        ~Component_Level(void)
        {
            if (pModel != nullptr)
            {
                pModel->Release();
                delete pModel;
                pModel = nullptr;
            }

            int index = 0;
            while (index < pBuffer.size())
            {
                auto curr = pBuffer.Get(index);

                if (curr != nullptr)
                {
                    delete curr;
                    curr = nullptr;
                }

                index += 1;
            }
        }

    } Level;
} // < end namespace.

#endif _LEVEL_HPP_
