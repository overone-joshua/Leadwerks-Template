#ifndef _SCENE_OBJECT_SYSTEM_HPP_
	#define _SCENE_OBJECT_SYSTEM_HPP_

#pragma once
#include "Leadwerks.h"
#include "../Utilities/Math/Math.hpp"
#include "../Components/InputDictionary.hpp"
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

        static Placement* Create(uint64_t _nEntityId, const std::string& _cName)
        {
            return new Placement(_nEntityId, _cName);
        }

        static void Destroy(Placement* _pPlacement)
        {
            if (_pPlacement != nullptr)
            {
                delete _pPlacement;
                _pPlacement = nullptr;
            }
        }

		static Placement& Update(Placement& comp, float dt, bool bAddVelocity)
		{
            float nFriction = 1.0f - comp.nFriction * dt;

            // < Spin the object.
            auto vSpin = comp.vSpin.Multiply(nFriction).Multiply(dt);
            comp = AddRotation(comp, vSpin);

            if (comp.vRotation.z <= -360.0f)
            {
                comp.vRotation.z = 360.0f;
            }

            if (bAddVelocity)
            {
                // < Check input mask to propagate movement.
                float localMove, localStrafe;
                localMove = localStrafe = 0.0f;

                localMove = (comp.nInputMask.HasStatus(INPUT_MOVE_BACKWARD) - comp.nInputMask.HasStatus(INPUT_MOVE_FORWARD)) * 0.025;
                localStrafe = (comp.nInputMask.HasStatus(INPUT_MOVE_LEFT) - comp.nInputMask.HasStatus(INPUT_MOVE_RIGHT)) * 0.025;

                float localVertMove = (comp.nInputMask.HasStatus(INPUT_MOVE_DOWN) - comp.nInputMask.HasStatus(INPUT_MOVE_UP)) * 0.025;

                if (localVertMove != 0.0f)
                {
                    comp = AddTranslation(comp, Leadwerks::Vec3(0.0f, localVertMove, 0.0f));
                }

                if (localMove != 0.0f)
                {
                    comp = SetDrive(comp, localMove);

                    auto vVelocity = comp.vVelocity.Multiply(nFriction).Multiply(dt);
                    comp = AddTranslation(comp, vVelocity);
                }

                if (localStrafe != 0.0f)
                {
                    comp = SetStrafe(comp, localStrafe);

                    auto vVelocity = comp.vVelocity.Multiply(nFriction).Multiply(dt);
                    comp = AddTranslation(comp, vVelocity);
                }
            }

            //comp.vForward = Math::CalculateForwardVector(comp.vRotation.x, comp.vRotation.y);
            //comp.vRight = Math::CalculateRightVector(comp.vRotation.x, comp.vRotation.y);

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

            // < Update the world matrix.
            comp.mWorld = comp.mRotation.Multiply(comp.mTranslation);

            // < Create the view matrix.
            comp.mView = comp.mWorld.Inverse();

            return comp;
		}

		static Placement& Drive(Placement& comp, float nForce, bool bLockYAxis = true)
		{
			auto force = comp.vForward * nForce;
			comp.vVelocity.x += force.x;
			comp.vVelocity.z += force.z;

			if (!bLockYAxis) { comp.vVelocity.y += force.y; }

            return comp;
		}

        static Placement& SetDrive(Placement& comp, float nForce)
        {
            comp.vVelocity = comp.vForward.Multiply(nForce);

            return comp;
        }

		static Placement& Strafe(Placement& comp, float nForce, bool bLockYAxis = true)
		{
			auto force = comp.vRight * nForce;

            comp.vVelocity += force.x;
            comp.vVelocity += force.z;

            if (!bLockYAxis) { comp.vVelocity.y += force.y; }

            return comp;
		}

        static Placement& SetStrafe(Placement& comp, float nForce)
        {
            comp.vVelocity = comp.vRight.Multiply(nForce);

            return comp;
        }

		static Placement& Stop(Placement& comp)
		{
            comp.vVelocity = Leadwerks::Vec3(0.0f, 0.0f, 0.0f);
            comp.vVelocity = Leadwerks::Vec3(0.0f, 0.0f, 0.0f);

            return comp;
		}

		static Placement& SetTranslation(Placement& comp, float x, float y, float z)
		{
			comp.vTranslation.x = x;
			comp.vTranslation.y = y;
			comp.vTranslation.z = z;

			comp.mTranslation = Leadwerks::Mat4(comp.vTranslation.x, comp.vTranslation.y, comp.vTranslation.z);
			
            return comp;
		}

		static Placement& SetTranslation(Placement& comp, Leadwerks::Vec3 vTranslation)
		{
            comp.vTranslation = vTranslation;

            Math::MatrixTranslation(&comp.mTranslation, comp.vTranslation.x, comp.vTranslation.y, comp.vTranslation.z);

            return comp;
		}

		static Placement& AddTranslation(Placement& comp, float x, float y, float z)
		{
            comp.vTranslation.x += x;
            comp.vTranslation.y += y;
            comp.vTranslation.z += z;

            comp.mTranslation = Leadwerks::Mat4(comp.vTranslation.x, comp.vTranslation.y, comp.vTranslation.z, 1.0f);

            return comp;
		}

		static Placement& AddTranslation(Placement& comp, Leadwerks::Vec3 vTranslation)
		{
            comp.vTranslation.x += vTranslation.x;
            comp.vTranslation.y += vTranslation.y;
            comp.vTranslation.z += vTranslation.z;

            Math::MatrixTranslation(&comp.mTranslation, comp.vTranslation.x, comp.vTranslation.y, comp.vTranslation.z);

            return comp;
		}

		static Placement& SetRotation(Placement& comp, float x, float y, float z)
		{
            comp.vRotation.x = x;
            comp.vRotation.y = y;
            comp.vRotation.z = z;

            Leadwerks::Mat4 rotX, rotY;
            Math::MatrixRotationX(&rotX, comp.vRotation.x);
            Math::MatrixRotationY(&rotY, comp.vRotation.y);
            Math::MatrixRotationZ(&comp.mRotation, comp.vRotation.z);
            comp.mRotation *= rotX;
            comp.mRotation *= rotY;

            return comp;
		}

		static Placement& SetRotation(Placement& comp, Leadwerks::Vec3 vRotation)
		{
			comp.vRotation.x = vRotation.x;
			comp.vRotation.y = vRotation.y;
			comp.vRotation.z = vRotation.z;

			Leadwerks::Mat4 rotX, rotY;
			Math::MatrixRotationX(&rotX, comp.vRotation.x);
			Math::MatrixRotationY(&rotY, comp.vRotation.y);
			Math::MatrixRotationZ(&comp.mRotation, comp.vRotation.z);
			comp.mRotation *= rotX;
			comp.mRotation *= rotY;

            return comp;
		}

		static Placement& AddRotation(Placement& comp, float x, float y, float z)
		{
			comp.vRotation.x += x;
			comp.vRotation.y += y;
			comp.vRotation.z += z;

			Leadwerks::Mat4 rotX, rotY;
			Math::MatrixRotationX(&rotX, comp.vRotation.x);
			Math::MatrixRotationY(&rotY, comp.vRotation.y);
			Math::MatrixRotationZ(&comp.mRotation, comp.vRotation.z);
			comp.mRotation *= rotX;
			comp.mRotation *= rotY;

            return comp;
		}

		static Placement& AddRotation(Placement& comp, Leadwerks::Vec3 vRotation)
		{
			comp.vRotation.x += vRotation.x;
			comp.vRotation.y += vRotation.y;
			comp.vRotation.z += vRotation.z;

			Leadwerks::Mat4 rotX, rotY;
			Math::MatrixRotationX(&rotX, comp.vRotation.x);
			Math::MatrixRotationY(&rotY, comp.vRotation.y);
			Math::MatrixRotationZ(&comp.mRotation, comp.vRotation.z);
			comp.mRotation *= rotX;
			comp.mRotation *= rotY;

            return comp;
		}

		static Placement& SetVelocity(Placement& comp, float x, float y, float z)
		{
			comp.vVelocity.x = x;
			comp.vVelocity.y = y;
			comp.vVelocity.z = z;

            return comp;
		}

		static Placement& SetVelocity(Placement& comp, Leadwerks::Vec3 vVelocity)
		{
			comp.vVelocity = vVelocity;

            return comp;
		}


		static Placement& AddVelocity(Placement& comp, float x, float y, float z)
		{
			comp.vVelocity.x += x;
			comp.vVelocity.y += y;
			comp.vVelocity.z += z;

            return comp;
		}

		static Placement& AddVelocity(Placement& comp, Leadwerks::Vec3 vVelocity)
		{
			comp.vVelocity.x += vVelocity.x;
			comp.vVelocity.y += vVelocity.y;
			comp.vVelocity.z += vVelocity.z;

            return comp;
		}

		static Placement& SetSpin(Placement& comp, float x, float y, float z)
		{
			comp.vSpin.x = x;
			comp.vSpin.y = y;
			comp.vSpin.z = z;

            return comp;
		}

		static Placement& SetSpin(Placement& comp, Leadwerks::Vec3 vSpin)
		{
			comp.vSpin = vSpin;

            return comp;
		}


		static Placement& AddSpin(Placement& comp, float x, float y, float z)
		{
			comp.vSpin.x += x;
			comp.vSpin.y += y;
			comp.vSpin.z += z;

            return comp;
		}

		static Placement& AddSpin(Placement& comp, Leadwerks::Vec3 vSpin)
		{
			comp.vSpin.x += vSpin.x;
			comp.vSpin.y += vSpin.y;
			comp.vSpin.z += vSpin.z;

            return comp;
		}

        static Placement& Save(uint64_t entity, Placement& _comp)
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