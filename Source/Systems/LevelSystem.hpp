#ifndef _LEVEL_SYSTEM_HPP_
    #define _LEVEL_SYSTEM_HPP_

#pragma once
#include "Leadwerks.h"
#include "../Components/InputDictionary.hpp"
#include "../Components/Level.hpp"
#include "../Repositories/MemoryRepository.hpp"
#include "../Utilities/Voxel.hpp"
#include "../Utilities/VoxelBuffer.hpp"

#include <cassert>
#include <list>

using namespace Components;

namespace Systems
{
    typedef struct PickResult
    {
        int x;
        int y;
        int z;
        bool bHit;
        Voxel* pRef;

        PickResult(Leadwerks::Vec3 _vPos = Leadwerks::Vec3(-1.0f, -1.0f, -1.0f), Voxel* pRef = nullptr)
            : pRef(pRef), bHit(false)
        {
            x = _vPos.x;
            y = _vPos.y;
            z = _vPos.z;
        }

    } PickResult;

    class LevelSystem
    {
    private:
        
        static MemoryRepository<Level>* _pLevelRepository;

        static Leadwerks::Model* _pFloor;
        static Leadwerks::Material* _pFloorMaterial;

        static bool _bInitialized;

    protected:

        LevelSystem(void) { }

    public:

        ~LevelSystem(void) { }

        static inline int Init(void)
        {
            assert(!_bInitialized);

            _pLevelRepository = new MemoryRepository<Level>(-1);
            if (_pLevelRepository == nullptr) { return 1; }

            _bInitialized = true;
            return 0;
        }

        static inline void Shutdown(void)
        {
            assert(_bInitialized);

            if (_pFloor != nullptr)
            {
                _pFloor->Release();
                delete _pFloor;
                _pFloor = nullptr;
            }

            if (_pFloorMaterial != nullptr)
            {
                _pFloorMaterial->Release();
                delete _pFloorMaterial;
                _pFloorMaterial = nullptr;
            }

            delete _pLevelRepository;
            _pLevelRepository = nullptr;

            _bInitialized = false;
        }

        static Level* Create(uint64_t _nEntityId, const std::string& _cName, unsigned _nWidth = 1, unsigned _nHeight = 1, unsigned _nDepth = 1, float _nSize = 1.0f) 
        {
            auto pMat = Leadwerks::Material::Create();
            pMat->SetColor(40.0f, 40.0f, 255.0f, 1.0f);

            if (_pFloor == nullptr)
            {
                _pFloor = Leadwerks::Model::Box(_nWidth + 2.0f, 1.0f, _nDepth + 2.0f);
                _pFloor->SetPosition(_nWidth * 0.5f, -0.5f, _nDepth * 0.5f);

                _pFloorMaterial = Leadwerks::Material::Create();
                _pFloorMaterial->SetColor(40.0f, 255.0f, 40.0f, 1.0f);

                _pFloor->SetMaterial(_pFloorMaterial);
            }

            auto lvl = new Level(_nEntityId, pMat, _nWidth, _nHeight, _nDepth, _nSize, _cName);

            return lvl;
        }

        static void Destroy(Level* _pLevel) 
        {
            if (_pLevel != nullptr)
            {
                delete _pLevel;
                _pLevel = nullptr;
            }
        }

        static void Update(Level* const _pLevel, float dt)
        {
            CheckInput(_pLevel, dt);

            if (_pLevel->bDirty)
            {
                GenerateMesh(_pLevel);
            }
            
        }

        static PickResult GetVoxel(Leadwerks::World* const _pWorld, Level* const _pLevel, const Leadwerks::Vec3 _vStart, const Leadwerks::Vec3 _vEnd, const float _nRadius = 0.0f, const bool _bClosest = false, const int _nCollisionType = 0)
        {
            Leadwerks::PickInfo pickInfo;
            PickResult pickResult;

            pickResult.bHit = _pWorld->Pick(_vStart, _vEnd, pickInfo, _nRadius, _bClosest, _nCollisionType);

            // < Did we hit anything?
            if (pickResult.bHit)
            {
                // < yes
                auto vPos = ConvertWorldToVoxel(_pLevel, pickInfo.position);
                vPos.x = Leadwerks::Math::Clamp(vPos.x, 0.0f, _pLevel->pBuffer.width() - 1);
                vPos.y = Leadwerks::Math::Clamp(vPos.y, 0.0f, _pLevel->pBuffer.height() - 1);
                vPos.z = Leadwerks::Math::Clamp(vPos.z, 0.0f, _pLevel->pBuffer.depth() - 1);

                auto ref = _pLevel->pBuffer.Get(vPos.x, vPos.y, vPos.z);

                pickResult.x = vPos.x;
                pickResult.y = vPos.y;
                pickResult.z = vPos.z;
                pickResult.pRef = ref;
            }

            return pickResult;
        }

        static Leadwerks::Vec3 ConvertWorldToVoxel(Level* const _pLevel, Leadwerks::Vec3 _vPosition)
        {
            return ConvertWorldToVoxel(_pLevel, _vPosition.x, _vPosition.y, _vPosition.z);
        }

        static Leadwerks::Vec3 ConvertWorldToVoxel(Level* const _pLevel, float _x, float _y, float _z)
        {
            auto nSize = _pLevel->nSize;

            // < Find our voxel coordinate(s).
            auto x = std::floor(_x / nSize);
            auto y = std::floor(_y / nSize);
            auto z = std::floor(_z / nSize);
            
            return Leadwerks::Vec3(x, y, z);
        }

    protected:

        static void CreateCube(Level* _pLevel, int x, int y, int z) {
            auto pVoxel = _pLevel->pBuffer.Get(x, y, z);

            if (pVoxel == nullptr) { return; }

            auto nSize = _pLevel->nSize;

            Leadwerks::Vec3 vZero(0.0f, 0.0f, 0.0f);
            Leadwerks::Vec3 vSize(nSize, nSize, nSize);

            Leadwerks::Vec3 p0 = Leadwerks::Vec3(x, y, z).Multiply(vSize).Add(Leadwerks::Vec3(0.0f, 0.0f, -nSize));					// Back-Bottom-Left
            Leadwerks::Vec3 p1 = Leadwerks::Vec3(x, y, z).Multiply(vSize).Add(Leadwerks::Vec3(nSize, 0.0f, -nSize));			// Back-Bottom-Right
            Leadwerks::Vec3 p2 = Leadwerks::Vec3(x, y, z).Multiply(vSize).Add(Leadwerks::Vec3(nSize, nSize, -nSize));	// Back-Top-Right
            Leadwerks::Vec3 p3 = Leadwerks::Vec3(x, y, z).Multiply(vSize).Add(Leadwerks::Vec3(0.0f, nSize, -nSize));			// Back-Top-Left

            Leadwerks::Vec3 p4 = Leadwerks::Vec3(x, y, z).Multiply(vSize).Add(Leadwerks::Vec3(nSize, 0, 0));					// Front-Bottom-Right
            Leadwerks::Vec3 p5 = Leadwerks::Vec3(x, y, z).Multiply(vSize);															// Front-Bottom-Left
            Leadwerks::Vec3 p6 = Leadwerks::Vec3(x, y, z).Multiply(vSize).Add(Leadwerks::Vec3(0.0f, nSize, 0.0f));					// Front-Top-Left
            Leadwerks::Vec3 p7 = Leadwerks::Vec3(x, y, z).Multiply(vSize).Add(Leadwerks::Vec3(nSize, nSize, 0.0f));			// Front-Top-Right

            Leadwerks::Model* pModel = _pLevel->pModel;
            Leadwerks::Vec3 vNormal;
            Leadwerks::Vec4 vWhite(255.0f, 255.0f, 255.0f, 1.0f);
            Leadwerks::Vec2 vTexCoord0(0.0f, 0.0f);
            Leadwerks::Vec2 vTexCoord1(1.0f, 1.0f);

            unsigned v0, v1, v2, v3, v4, v5, v6, v7;
            v0 = v1 = v2 = v3 = v4 = v5 = v6 = v7 = 0;

            if (pModel == nullptr)
            {
                pModel = Leadwerks::Model::Create();
            }

            /* BACK */
            auto pSurface = pVoxel->GetSurfaceForSide(VOXEL_SIDE_BACK);
            if (pSurface == nullptr) { pSurface = pModel->AddSurface(); }

            vNormal = Leadwerks::Vec3(0.0f, 0.0f, -1.0f);
            v0 = pSurface->AddVertex(p0, vNormal, vTexCoord0, vTexCoord1, vWhite);
            v1 = pSurface->AddVertex(p1, vNormal, vTexCoord0, vTexCoord1, vWhite);
            v2 = pSurface->AddVertex(p2, vNormal, vTexCoord0, vTexCoord1, vWhite);
            v3 = pSurface->AddVertex(p3, vNormal, vTexCoord0, vTexCoord1, vWhite);
            /* Outside */
            //pSurface->AddTriangle(v0, v1, v2);
            //pSurface->AddTriangle(v0, v2, v3);
            /* Inside */
            pSurface->AddTriangle(v2, v1, v0);
            pSurface->AddTriangle(v3, v2, v0);

            pSurface->Update();

            // < ---

            /* FRONT */
            pSurface = pVoxel->GetSurfaceForSide(VOXEL_SIDE_FRONT);
            if (pSurface == nullptr) { pSurface = pModel->AddSurface(); }

            vNormal = Leadwerks::Vec3(0.0f, 0.0f, 1.0f);
            v4 = pSurface->AddVertex(p4, vNormal, vTexCoord0, vTexCoord1, vWhite);
            v5 = pSurface->AddVertex(p5, vNormal, vTexCoord0, vTexCoord1, vWhite);
            v6 = pSurface->AddVertex(p6, vNormal, vTexCoord0, vTexCoord1, vWhite);
            v7 = pSurface->AddVertex(p7, vNormal, vTexCoord0, vTexCoord1, vWhite);
            /* Outside */
            //pSurface->AddTriangle(v4, v5, v6);
            //pSurface->AddTriangle(v4, v6, v7);
            /* Inside */
            pSurface->AddTriangle(v6, v5, v4);
            pSurface->AddTriangle(v7, v6, v4);

            pSurface->Update();

            // < ---

            /* RIGHT */
            pSurface = pVoxel->GetSurfaceForSide(VOXEL_SIDE_RIGHT);
            if (pSurface == nullptr) { pSurface = pModel->AddSurface(); }

            vNormal = Leadwerks::Vec3(1.0f, 0.0f, 0.0f);

            v1 = pSurface->AddVertex(p1, vNormal, vTexCoord0, vTexCoord1, vWhite);
            v4 = pSurface->AddVertex(p4, vNormal, vTexCoord0, vTexCoord1, vWhite);
            v7 = pSurface->AddVertex(p7, vNormal, vTexCoord0, vTexCoord1, vWhite);
            v2 = pSurface->AddVertex(p2, vNormal, vTexCoord0, vTexCoord1, vWhite);
            /* Outside */
            //pSurface->AddTriangle(v1, v4, v7);
            //pSurface->AddTriangle(v1, v7, v2);
            /* Inside */
            pSurface->AddTriangle(v7, v4, v1);
            pSurface->AddTriangle(v2, v7, v1);

            pSurface->Update();

            /* LEFT */
            pSurface = pVoxel->GetSurfaceForSide(VOXEL_SIDE_LEFT);
            if (pSurface == nullptr) { pSurface = pModel->AddSurface(); }

            vNormal = Leadwerks::Vec3(-1.0f, 0.0f, 0.0f);

            v5 = pSurface->AddVertex(p5, vNormal, vTexCoord0, vTexCoord1, vWhite);
            v0 = pSurface->AddVertex(p0, vNormal, vTexCoord0, vTexCoord1, vWhite);
            v3 = pSurface->AddVertex(p3, vNormal, vTexCoord0, vTexCoord1, vWhite);
            v6 = pSurface->AddVertex(p6, vNormal, vTexCoord0, vTexCoord1, vWhite);
            /* Outside */
            //pSurface->AddTriangle(v5, v0, v3);
            //pSurface->AddTriangle(v5, v3, v6);
            /* Inside */
            pSurface->AddTriangle(v3, v0, v5);
            pSurface->AddTriangle(v6, v3, v5);

            pSurface->Update();

            /* TOP */
            pSurface = pVoxel->GetSurfaceForSide(VOXEL_SIDE_TOP);
            if (pSurface == nullptr) { pSurface = pModel->AddSurface(); }

            vNormal = Leadwerks::Vec3(0.0f, 1.0f, 0.0f);

            v3 = pSurface->AddVertex(p3, vNormal, vTexCoord0, vTexCoord1, vWhite);
            v2 = pSurface->AddVertex(p2, vNormal, vTexCoord0, vTexCoord1, vWhite);
            v7 = pSurface->AddVertex(p7, vNormal, vTexCoord0, vTexCoord1, vWhite);
            v6 = pSurface->AddVertex(p6, vNormal, vTexCoord0, vTexCoord1, vWhite);
            /* Outside */
            //pSurface->AddTriangle(v3, v2, v7);
            //pSurface->AddTriangle(v3, v7, v6);
            /* Inside */
            pSurface->AddTriangle(v7, v2, v3);
            pSurface->AddTriangle(v6, v7, v3);

            pSurface->Update();

            /* BOTTOM */
            pSurface = pVoxel->GetSurfaceForSide(VOXEL_SIDE_BOTTOM);
            if (pSurface == nullptr) { pSurface = pModel->AddSurface(); }

            vNormal = Leadwerks::Vec3(0.0f, -1.0f, 0.0f);

            v5 = pSurface->AddVertex(p5, vNormal, vTexCoord0, vTexCoord1, vWhite);
            v4 = pSurface->AddVertex(p4, vNormal, vTexCoord0, vTexCoord1, vWhite);
            v1 = pSurface->AddVertex(p1, vNormal, vTexCoord0, vTexCoord1, vWhite);
            v0 = pSurface->AddVertex(p0, vNormal, vTexCoord0, vTexCoord1, vWhite);
            /* Outside */
            pSurface->AddTriangle(v5, v4, v1);
            pSurface->AddTriangle(v5, v1, v0);
            /* Inside */
            //pSurface->AddTriangle(v1, v4, v5);
            //pSurface->AddTriangle(v0, v1, v5);

            pSurface->Update();
        }

        static void GenerateMesh(Level* _pLevel) {
            if (_pLevel->pModel == nullptr) { _pLevel->pModel = Leadwerks::Model::Create(nullptr); }

            unsigned index = 0;
            for (int z = 0; z < _pLevel->pBuffer.depth(); z += 1)
                for (int y = 0; y < _pLevel->pBuffer.height(); y += 1)
                    for (int x = 0; x < _pLevel->pBuffer.width(); x += 1) {
                        CreateCube(_pLevel, x, y, z);
                        index += 1;
                    }

            _pLevel->pModel->BuildShape(Leadwerks::SHAPE_POLYMESH);
            _pLevel->pModel->UpdateAABB(Leadwerks::Entity::LocalAABB | Leadwerks::Entity::GlobalAABB);

            _pLevel->bDirty = false;
        }

    private:

        static void CheckInput(Level* const _pLevel, float dt)
        {
            auto& mask = _pLevel->inputMask;

        }

    }; // < end class.

} // < end namespace.

#endif _LEVEL_SYSTEM_HPP_
