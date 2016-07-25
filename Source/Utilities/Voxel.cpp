
#pragma once
#include "Voxel.hpp"

#include <cassert>

Voxel::Voxel(Leadwerks::Material* _pDefMaterial, float _width, float _height , float _depth)
    : m_pDefaultMaterial(_pDefMaterial), m_nWidth(_width), m_nHeight(_height), m_nDepth(_depth)
{
    unsigned index = 0;
    while (index < 6)
    {
        m_materials[index] = nullptr;
        m_sides[index] = nullptr;

        index += 1;
    }
}

Voxel::~Voxel(void)
{
    unsigned index = 0;
    while (index < 6)
    {
        SafeDeleteSurface(m_sides[index]);
        SafeDeleteMaterial(m_materials[index]);

        index += 1;
    }

    SafeDeleteMaterial(m_pDefaultMaterial);
}

Leadwerks::Material* Voxel::SafeDeleteMaterial(Leadwerks::Material* _pMaterial)
{
    if (_pMaterial != nullptr)
    {
        _pMaterial->Release();
        delete _pMaterial;
        _pMaterial = nullptr;
    }

    if (_pMaterial != nullptr)
    {
        std::cerr << "Failed to safely delete given material!\n";
    }

    return _pMaterial;
}

Leadwerks::Model* Voxel::SafeDeleteModel(Leadwerks::Model* _pModel)
{
    if (_pModel != nullptr)
    {
        _pModel->Release();
        delete _pModel;
        _pModel = nullptr;
    }

    if (_pModel != nullptr)
    {
        std::cerr << "Failed to safely delete given model!\n";
    }

    return _pModel;
}

Leadwerks::Surface* Voxel::SafeDeleteSurface(Leadwerks::Surface* _pSurface)
{
    if (_pSurface != nullptr)
    {
        _pSurface->Release();
        delete _pSurface;
        _pSurface = nullptr;
    }

    if (_pSurface != nullptr)
    {
        std::cerr << "Failed to safely delete given surface! \n";
    }

    return _pSurface;
}

void Voxel::ApplyDefaultMaterialToSide(VoxelSide _side)
{
    if (_side == VOXEL_ALL_SIDES)
    {
        unsigned index = 0;
        while (index < 6)
        {
            m_sides[index]->SetMaterial(m_pDefaultMaterial);

            index += 1;
        }
    }
    else
    {
        m_sides[_side]->SetMaterial(m_pDefaultMaterial);
    }
}

void Voxel::ApplySideMaterialToSide(VoxelSide _sourceSide, VoxelSide _destSide)
{
    // < Apply each material to its associated side.
    if (_sourceSide == VOXEL_ALL_SIDES)
    {
        unsigned index = 0;
        while (index < 6)
        {
            if (m_materials[index] == nullptr)
            {
                m_sides[index]->SetMaterial(m_pDefaultMaterial);
            }
            else
            {
                m_sides[index]->SetMaterial(m_materials[index]);
            }

            index += 1;
        }
    }
    // < Apply the material of the given side to all sides.
    else if (_destSide == VOXEL_ALL_SIDES)
    {
        unsigned index = 0;
        while (index < 6)
        {
            if (m_materials[_sourceSide] == nullptr)
            {
                m_sides[index]->SetMaterial(m_pDefaultMaterial);
            }
            else
            {
                m_sides[index]->SetMaterial(m_materials[_sourceSide]);
            }
            
            index += 1;
        }
    }
    // < Apply the material of the source side to the dest side.
    else
    {
        if (m_materials[_sourceSide] == nullptr)
        {
            m_sides[_destSide]->SetMaterial(m_pDefaultMaterial);
        }
        else
        {
            m_sides[_destSide]->SetMaterial(m_materials[_sourceSide]);
        }
    }
}

Leadwerks::Material* Voxel::GetMaterialForSide(VoxelSide _side)
{
    assert(_side != VOXEL_ALL_SIDES);

    return m_materials[_side];
}

Leadwerks::Surface* Voxel::GetSurfaceForSide(VoxelSide _side)
{
    assert(_side != VOXEL_ALL_SIDES);

    return m_sides[_side];
}

void Voxel::SetDefaultMaterial(Leadwerks::Material* _pMaterial)
{
    if (m_pDefaultMaterial != nullptr)
    {
        SafeDeleteMaterial(m_pDefaultMaterial);
        m_pDefaultMaterial = _pMaterial;
    }
}

void Voxel::SetMaterial(Leadwerks::Material* _pMaterial, VoxelSide _side)
{
    if (_side == VOXEL_ALL_SIDES)
    {
        unsigned index = 0;
        while (index < 6)
        {
            SafeDeleteMaterial(m_materials[index]);
            m_materials[index] = _pMaterial;

            index += 1;
        }
    }
    else
    {
        SafeDeleteMaterial(m_materials[_side]);
        m_materials[_side] = _pMaterial;
    }
}

void Voxel::ClearMaterial(VoxelSide _side)
{
    if (_side == VOXEL_ALL_SIDES)
    {
        unsigned index = 0;
        while (index < 6)
        {
            SafeDeleteMaterial(m_materials[index]);

            index += 1;
        }
    }
    else
    {
        SafeDeleteMaterial(m_materials[_side]);
    }
}