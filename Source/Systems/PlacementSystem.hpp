#ifndef _SCENE_OBJECT_SYSTEM_HPP_
	#define _SCENE_OBJECT_SYSTEM_HPP_

#pragma once
#include "Leadwerks.h"
#include "../Utilities/Math/Math.hpp"
#include "../Components/Placement.hpp"
#include "../Components/World.hpp"
#include "../Repositories/MemoryRepository.hpp"

#include <cassert>
#include <functional>

using namespace Components;

namespace Systems
{
	class PlacementSystem
	{
	private:

		static MemoryRepository<Placement>* _pPlacementRepository;

		static bool bInitialized;

	protected:

		PlacementSystem(void) { bInitialized = false; }

	public:

		static inline int Init(void)
		{
			assert(!bInitialized);

			_pPlacementRepository = new MemoryRepository<Placement>(-1);
			if (_pPlacementRepository == nullptr) { return 1; }

			bInitialized = true;
			return 0;
		}

		static inline void Shutdown(void)
		{
			assert(bInitialized);

			delete _pPlacementRepository;

			_pPlacementRepository = nullptr;

			bInitialized = false;
		}

		static Placement Update(uint64_t entity, float dt, bool bAddVelocity)
		{
            auto comp = _pPlacementRepository->GetWhere([entity](Placement& comp) { return comp.nEntityId == entity; }).front();

			float nFriction = 1.0f - comp.nFriction * dt;

			// < Move the object.
			comp.vVelocity *= nFriction;
			if (bAddVelocity)
			{
				auto vVelocity = comp.vVelocity * dt;
				comp.vTranslation += vVelocity;

				// < Set translation matrix.
				comp.mTranslation = Leadwerks::Mat4(comp.vTranslation.x, comp.vTranslation.y, comp.vTranslation.z);
			}

			// < Spin the object.
			comp.vSpin *= nFriction;
			auto vSpin = comp.vSpin * dt;
			comp.vRotation += vSpin;
			comp.mRotation = Leadwerks::Mat4(comp.vRotation.x, comp.vRotation.y, comp.vRotation.z);

			// < Update the world matrix.
			comp.mWorld = comp.mRotation * comp.mTranslation;

			// < Create the view matrix.
			comp.mView = comp.mWorld.Inverse();

			// < Update the forward vector.
			comp.vForward = Leadwerks::Vec3(
				Leadwerks::Math::Sin(comp.vRotation.y)
				, -Leadwerks::Math::Tan(comp.vRotation.x)
				, Leadwerks::Math::Cos(comp.vRotation.y))
				.Normalize();

			// < Update the right vector.
			comp.vRight = Leadwerks::Vec3(
				Leadwerks::Math::Cos(comp.vRotation.y)
				, Leadwerks::Math::Tan(comp.vRotation.z)
				, -Leadwerks::Math::Sin(comp.vRotation.y))
				.Normalize();

			return _pPlacementRepository->Set(comp.nId, comp);
		}

		static Placement Drive(uint64_t entity, float nForce, bool bLockYAxis = true)
		{
            auto comp = _pPlacementRepository->GetWhere([entity](Placement& comp) { return comp.nEntityId == entity; }).front();

			auto force = comp.vForward * nForce;
			comp.vVelocity.x += force.x;
			comp.vVelocity.z += force.z;

			if (!bLockYAxis) { comp.vVelocity.y += force.y; }

			return _pPlacementRepository->Set(comp.nId, comp);
		}

		static Placement Strafe(uint64_t entity, float nForce, bool bLockYAxis = true)
		{
            auto comp = _pPlacementRepository->GetWhere([entity](Placement& comp) { return comp.nEntityId == entity; }).front();

			auto force = comp.vRight * nForce;

            comp.vVelocity += force.x;
            comp.vVelocity += force.z;

            if (!bLockYAxis) { comp.vVelocity.y += force.y; }

            return _pPlacementRepository->Set(comp.nId, comp);
		}

		static Placement Stop(uint64_t entity)
		{
            auto comp = _pPlacementRepository->GetWhere([entity](Placement& comp) { return comp.nEntityId == entity; }).front();

            comp.vVelocity = Leadwerks::Vec3(0.0f, 0.0f, 0.0f);
            comp.vVelocity = Leadwerks::Vec3(0.0f, 0.0f, 0.0f);

            return _pPlacementRepository->Set(comp.nId, comp);
		}

		static Placement SetTranslation(uint64_t entity, float x, float y, float z)
		{
            auto comp = _pPlacementRepository->GetWhere([entity](Placement& comp) { return comp.nEntityId == entity; }).front();

			comp.vTranslation.x = x;
			comp.vTranslation.y = y;
			comp.vTranslation.z = z;

			comp.mTranslation = Leadwerks::Mat4(comp.vTranslation.x, comp.vTranslation.y, comp.vTranslation.z);
			
            return _pPlacementRepository->Set(comp.nId, comp);
		}

		static Placement SetTranslation(uint64_t entity, Leadwerks::Vec3 vTranslation)
		{
            auto comp = _pPlacementRepository->GetWhere([entity](Placement& comp) { return comp.nEntityId == entity; }).front();

            comp.vTranslation = vTranslation;

            comp.mTranslation = Leadwerks::Mat4(comp.vTranslation.x, comp.vTranslation.y, comp.vTranslation.z);

            return _pPlacementRepository->Set(comp.nId, comp);
		}

		static Placement AddTranslation(uint64_t entity, float x, float y, float z)
		{
            auto comp = _pPlacementRepository->GetWhere([entity](Placement& comp) { return comp.nEntityId == entity; }).front();

            comp.vTranslation.x += x;
            comp.vTranslation.y += y;
            comp.vTranslation.z += z;

            comp.mTranslation = Leadwerks::Mat4(comp.vTranslation.x, comp.vTranslation.y, comp.vTranslation.z);

            return _pPlacementRepository->Set(comp.nId, comp);
		}

		static Placement AddTranslation(uint64_t entity, Leadwerks::Vec3 vTranslation)
		{
            auto comp = _pPlacementRepository->GetWhere([entity](Placement& comp) { return comp.nEntityId == entity; }).front();

            comp.vTranslation.x += vTranslation.x;
            comp.vTranslation.y += vTranslation.y;
            comp.vTranslation.z += vTranslation.z;

            comp.mTranslation = Leadwerks::Mat4(comp.vTranslation.x, comp.vTranslation.y, comp.vTranslation.z);

            return _pPlacementRepository->Set(comp.nId, comp);
		}

		static Placement SetRotation(uint64_t entity, float x, float y, float z)
		{
            auto comp = _pPlacementRepository->GetWhere([entity](Placement& comp) { return comp.nEntityId == entity; }).front();

            comp.vRotation.x = x;
            comp.vRotation.y = y;
            comp.vRotation.z = z;

            Leadwerks::Mat4 rotX, rotY;
            Math::MatrixRotationX(&rotX, comp.vRotation.x);
            Math::MatrixRotationY(&rotY, comp.vRotation.y);
            Math::MatrixRotationZ(&comp.mRotation, comp.vRotation.z);
            comp.mRotation *= rotX;
            comp.mRotation *= rotY;

            return _pPlacementRepository->Set(comp.nId, comp);
		}

		static Placement SetRotation(uint64_t entity, Leadwerks::Vec3 vRotation)
		{
            auto comp = _pPlacementRepository->GetWhere([entity](Placement& comp) { return comp.nEntityId == entity; }).front();

			comp.vRotation.x = vRotation.x;
			comp.vRotation.y = vRotation.y;
			comp.vRotation.z = vRotation.z;

			Leadwerks::Mat4 rotX, rotY;
			Math::MatrixRotationX(&rotX, comp.vRotation.x);
			Math::MatrixRotationY(&rotY, comp.vRotation.y);
			Math::MatrixRotationZ(&comp.mRotation, comp.vRotation.z);
			comp.mRotation *= rotX;
			comp.mRotation *= rotY;

            return _pPlacementRepository->Set(comp.nId, comp);
		}

		static Placement AddRotation(uint64_t entity, float x, float y, float z)
		{
            auto comp = _pPlacementRepository->GetWhere([entity](Placement& comp) { return comp.nEntityId == entity; }).front();

			comp.vRotation.x += x;
			comp.vRotation.y += y;
			comp.vRotation.z += z;

			Leadwerks::Mat4 rotX, rotY;
			Math::MatrixRotationX(&rotX, comp.vRotation.x);
			Math::MatrixRotationY(&rotY, comp.vRotation.y);
			Math::MatrixRotationZ(&comp.mRotation, comp.vRotation.z);
			comp.mRotation *= rotX;
			comp.mRotation *= rotY;

            return _pPlacementRepository->Set(comp.nId, comp);
		}

		static Placement AddRotation(uint64_t entity, Leadwerks::Vec3 vRotation)
		{
            auto comp = _pPlacementRepository->GetWhere([entity](Placement& comp) { return comp.nEntityId == entity; }).front();

			comp.vRotation.x += vRotation.x;
			comp.vRotation.y += vRotation.y;
			comp.vRotation.z += vRotation.z;

			Leadwerks::Mat4 rotX, rotY;
			Math::MatrixRotationX(&rotX, comp.vRotation.x);
			Math::MatrixRotationY(&rotY, comp.vRotation.y);
			Math::MatrixRotationZ(&comp.mRotation, comp.vRotation.z);
			comp.mRotation *= rotX;
			comp.mRotation *= rotY;

            return _pPlacementRepository->Set(comp.nId, comp);
		}

		static Placement SetVelocity(uint64_t entity, float x, float y, float z)
		{
            auto comp = _pPlacementRepository->GetWhere([entity](Placement& comp) { return comp.nEntityId == entity; }).front();

			comp.vVelocity.x = x;
			comp.vVelocity.y = y;
			comp.vVelocity.z = z;

            return _pPlacementRepository->Set(comp.nId, comp);
		}

		static Placement SetVelocity(uint64_t entity, Leadwerks::Vec3 vVelocity)
		{
            auto comp = _pPlacementRepository->GetWhere([entity](Placement& comp) { return comp.nEntityId == entity; }).front();

			comp.vVelocity = vVelocity;

            return _pPlacementRepository->Set(comp.nId, comp);
		}


		static Placement AddVelocity(uint64_t entity, float x, float y, float z)
		{
            auto comp = _pPlacementRepository->GetWhere([entity](Placement& comp) { return comp.nEntityId == entity; }).front();

			comp.vVelocity.x += x;
			comp.vVelocity.y += y;
			comp.vVelocity.z += z;

            return _pPlacementRepository->Set(comp.nId, comp);
		}

		static Placement AddVelocity(uint64_t entity, Leadwerks::Vec3 vVelocity)
		{
            auto comp = _pPlacementRepository->GetWhere([entity](Placement& comp) { return comp.nEntityId == entity; }).front();

			comp.vVelocity.x += vVelocity.x;
			comp.vVelocity.y += vVelocity.y;
			comp.vVelocity.z += vVelocity.z;

            return _pPlacementRepository->Set(comp.nId, comp);
		}

		static Placement SetSpin(uint64_t entity, float x, float y, float z)
		{
            auto comp = _pPlacementRepository->GetWhere([entity](Placement& comp) { return comp.nEntityId == entity; }).front();

			comp.vSpin.x = x;
			comp.vSpin.y = y;
			comp.vSpin.z = z;

            return _pPlacementRepository->Set(comp.nId, comp);
		}

		static Placement SetSpin(uint64_t entity, Leadwerks::Vec3 vSpin)
		{
            auto comp = _pPlacementRepository->GetWhere([entity](Placement& comp) { return comp.nEntityId == entity; }).front();

			comp.vSpin = vSpin;

            return _pPlacementRepository->Set(comp.nId, comp);
		}


		static Placement AddSpin(uint64_t entity, float x, float y, float z)
		{
            auto comp = _pPlacementRepository->GetWhere([entity](Placement& comp) { return comp.nEntityId == entity; }).front();

			comp.vSpin.x += x;
			comp.vSpin.y += y;
			comp.vSpin.z += z;

            return _pPlacementRepository->Set(comp.nId, comp);
		}

		static Placement AddSpin(uint64_t entity, Leadwerks::Vec3 vSpin)
		{
            auto comp = _pPlacementRepository->GetWhere([entity](Placement& comp) { return comp.nEntityId == entity; }).front();

			comp.vSpin.x += vSpin.x;
			comp.vSpin.y += vSpin.y;
			comp.vSpin.z += vSpin.z;

            return _pPlacementRepository->Set(comp.nId, comp);
		}

        static Placement Save(uint64_t entity, Placement& _comp)
        {
            auto components = _pPlacementRepository->GetWhere([entity](Placement& comp) { return comp.nEntityId == entity; });

            if (!components.empty())
            {
                return _pPlacementRepository->Set(_comp.nId, _comp);
            }
            
            return _pPlacementRepository->Add(_comp);
        }
	}; // < end class.
} // < end system.

#endif _SCENE_OBJECT_SYSTEM_HPP_