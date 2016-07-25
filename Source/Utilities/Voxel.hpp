#ifndef _VOXEL_HPP_
    #define _VOXEL_HPP_

#pragma once
#include "Leadwerks.h"

typedef enum
{
    VOXEL_SIDE_TOP = 0,
    VOXEL_SIDE_BOTTOM = 1,
    VOXEL_SIDE_FRONT = 2,
    VOXEL_SIDE_BACK = 3,
    VOXEL_SIDE_LEFT = 4,
    VOXEL_SIDE_RIGHT = 5,

    VOXEL_ALL_SIDES = 6

} VoxelSide;

class Voxel
{
public:

    Voxel(Leadwerks::Material* _pDefMaterial, float _width = 1.0f, float _height = 1.0f, float _depth = 1.0f);
    ~Voxel(void);

    void SetDefaultMaterial(Leadwerks::Material* _pMaterial);
    void SetMaterial(Leadwerks::Material* _pMaterial, VoxelSide _side = VOXEL_ALL_SIDES);
    void ClearMaterial(VoxelSide _side = VOXEL_ALL_SIDES);

    Leadwerks::Material* GetMaterialForSide(VoxelSide _side);
    Leadwerks::Surface* GetSurfaceForSide(VoxelSide _side);

    Voxel(const Voxel* _other)
    {
        this->m_nWidth = _other->m_nWidth;
        this->m_nHeight = _other->m_nHeight;
        this->m_nDepth = _other->m_nDepth;

        this->m_pDefaultMaterial = _other->m_pDefaultMaterial;

        unsigned index = 0;
        while (index < 6)
        {
            this->m_sides[index] = _other->m_sides[index];
            this->m_materials[index] = _other->m_materials[index];

            index += 1;
        }
    }

protected:

    void ApplyDefaultMaterialToSide(VoxelSide _side = VOXEL_ALL_SIDES);
    void ApplySideMaterialToSide(VoxelSide _sourceSide, VoxelSide _destSide = VOXEL_ALL_SIDES);

private:

    Leadwerks::Material* SafeDeleteMaterial(Leadwerks::Material* _pMaterial);
    Leadwerks::Model* SafeDeleteModel(Leadwerks::Model* _pModel);
    Leadwerks::Surface* SafeDeleteSurface(Leadwerks::Surface* _pSurface);

    float m_nWidth;
    float m_nHeight;
    float m_nDepth;

    Leadwerks::Surface* m_sides[6];

    Leadwerks::Material* m_pDefaultMaterial;
    Leadwerks::Material* m_materials[6];

}; // < end class.

#endif _VOXEL_HPP_
