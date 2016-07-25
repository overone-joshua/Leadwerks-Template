#ifndef _PLAYER_SYSTEM_HPP_
    #define _PLAYER_SYSTEM_HPP_

#pragma once
#include "Leadwerks.h"
#include "PlacementSystem.hpp"
#include "../Utilities/Math/Math.hpp"
#include "../Components/Placement.hpp"
#include "../Components/Player.hpp"
#include "../Repositories/MemoryRepository.hpp"

#include <cassert>
#include <functional>

using namespace Components;

namespace Systems
{
    class PlayerSystem
    {
    private:

        // < Using a -1 for size disables inactive memory clearing.
        static MemoryRepository<Placement>* _pPlacementRepository;
        static MemoryRepository<Player>* _pPlayerRepository;

        static bool bInitialized;

    protected:

        PlayerSystem(void) { bInitialized = false; }

    public:

        static inline int Init(void)
        {
            assert(!bInitialized);

            _pPlacementRepository = new MemoryRepository<Placement>(-1);
            if (_pPlacementRepository == nullptr) { return 1; }

            _pPlayerRepository = new MemoryRepository<Player>(-1);
            if (_pPlayerRepository == nullptr) { return 1; }

            bInitialized = true;
            return 0;
        }

        static inline void Shutdown(void)
        {
            assert(bInitialized);

            delete _pPlacementRepository;
            delete _pPlayerRepository;

            _pPlacementRepository = nullptr;
            _pPlayerRepository = nullptr;

            bInitialized = false;
        }

        static Player* Create(uint64_t _nEntityId, const std::string& _cName)
        {
            return new Player(_nEntityId, _cName);
        }

        static void Destroy(Player* _pPlayer)
        {
            if (_pPlayer != nullptr)
            {
                delete _pPlayer;
                _pPlayer = nullptr;
            }
        }

        static Player& Update(Player& playerComp, Placement& placementComp, float dt, bool bAddVelocity = true)
        {
            // < Override the object's forward vector to take the view tilt into account.
            // * This will allow the forward vector to move up and down as well instead
            // * of just remaining horizontal. This is not important for movement since
            // * the player can not fly, but for things like shooting it is.
            playerComp.vForward = Math::CalculateForwardVector(playerComp.nViewTilt, placementComp.vRotation.x);

			playerComp.vViewPoint.y += 0.75f; // < hard-coded for now.

			if (playerComp.bViewingPlayer)
			{
				Leadwerks::Mat4 rotX, rotY, viewPointTransMat;

				// Create the x-axis rotation matrix.
				Math::MatrixRotationX(&rotX, playerComp.nViewTilt);
				rotY = rotX.Multiply(placementComp.mRotation);

				Leadwerks::Vec3 vFinalViewPointTrans;
				vFinalViewPointTrans = placementComp.vTranslation.Add(playerComp.vViewPoint);

				Math::MatrixTranslation(&viewPointTransMat, vFinalViewPointTrans.x, vFinalViewPointTrans.y, vFinalViewPointTrans.z);

				placementComp.mView = rotY.Multiply(viewPointTransMat);
				placementComp.mView = placementComp.mView.Inverse();
			}

			if (playerComp.bDying) { return playerComp; }

			 // < Drive and strafe the player.
			if (playerComp.nDrive != 0.0f)
			{
				placementComp = PlacementSystem::Drive(placementComp, playerComp.nDrive * 8000.0f * dt);
			}

			if (playerComp.nStrafe != 0.0f)
			{
				placementComp = PlacementSystem::Strafe(placementComp, playerComp.nStrafe * 8000.0f * dt);
			}

            return playerComp;
        }

        static void Render(uint64_t _entity, Leadwerks::Mat4* _pWorldMtx = nullptr)
        {

        }

        static Player& MouseLook(Player& playerComp, Placement& placementComp, float _x, float _y, bool _bReset = false)
        {
            static float lastX = 0.0f;
            static float lastY = 0.0f;

            // < Check if the player's view needs to be reset.
            if (_bReset)
            {
                placementComp = PlacementSystem::SetRotation(placementComp, 0.0f, 0.0f, 0.0f);

                lastX = lastY = 0.0f;
                playerComp.nViewTilt = 0.0f;
                return playerComp;
            }

            // Calculate the real x and y values by accounting for smoothing.
            lastX = lastX * playerComp.nViewSmoothing + _x * (1.0f - playerComp.nViewSmoothing);
            lastY = lastY * playerComp.nViewSmoothing + _y * (1.0f - playerComp.nViewSmoothing);

            // Adjust the values for sensitivity.
            lastX *= playerComp.nViewSensitivity;
            lastY *= playerComp.nViewSensitivity;

            // Rotate the scene object around the y axis only. This will prevent the
            // player's mesh from rotating when the player looks up and down.
            placementComp = PlacementSystem::AddRotation(placementComp, 0.0f, lastY, 0.0f);
            placementComp = PlacementSystem::Save(placementComp.nEntityId, placementComp);

            // Ensure the view will not rotate to far up or down.
            if ((playerComp.nViewTilt > 0.8f && lastX > 0.0f) || (playerComp.nViewTilt < -0.8f && lastX < 0.0f))
                lastX = 0.0f;

            // Maintain a separate view rotation around the x axis to allow the player
            // to look up and down.
            playerComp.nViewTilt += lastX;

            return playerComp;
        }

        static Player Hurt(uint64_t _entity, float _damage, uint64_t _attacker)
        {
            auto playerComp = _pPlayerRepository->GetWhere([_entity](Player& comp) { return comp.nEntityId == _entity; }).front();

            playerComp.nHealth -= _damage;

            if (playerComp.nHealth <= 0.0f)
            {
                playerComp.nHealth = 0.0f;
                playerComp.bDying = true;
            }

            return _pPlayerRepository->Set(playerComp.nId, playerComp);
        }

        static Player Kill(uint64_t _entity)
        {
            auto playerComp = _pPlayerRepository->GetWhere([_entity](Player& comp) { return comp.nEntityId == _entity; }).front();

            playerComp.nHealth = 0.0f;
            playerComp.bDying = true;

            return _pPlayerRepository->Set(playerComp.nId, playerComp);
        }

        static Player SetHealth(uint64_t _entity, float _nHealth)
        {
			auto playerComp = _pPlayerRepository->GetWhere([_entity](Player& comp) { return comp.nEntityId == _entity; }).front();

			playerComp.nHealth = _nHealth;

			return _pPlayerRepository->Set(playerComp.nId, playerComp);
        }

        static float GetHealth(uint64_t _entity)
        {
			auto playerComp = _pPlayerRepository->GetWhere([_entity](Player& comp) { return comp.nEntityId == _entity; }).front();

			return playerComp.nHealth;
        }

        static Player SetDying(uint64_t _entity, bool _bDying)
        {
			auto playerComp = _pPlayerRepository->GetWhere([_entity](Player& comp) { return comp.nEntityId == _entity; }).front();

			playerComp.bDying = _bDying;

			return _pPlayerRepository->Set(playerComp.nId, playerComp);
        }

        static bool GetDying(uint64_t _entity)
        {
			auto playerComp = _pPlayerRepository->GetWhere([_entity](Player& comp) { return comp.nEntityId == _entity; }).front();

			return playerComp.bDying;
        }

        static Player SetIsViewing(uint64_t _entity, bool _bIsViewing)
        {
			auto playerComp = _pPlayerRepository->GetWhere([_entity](Player& comp) { return comp.nEntityId == _entity; }).front();

			playerComp.bViewingPlayer = _bIsViewing;

			return _pPlayerRepository->Set(playerComp.nId, playerComp);
        }

		static bool IsViewing(uint64_t _entity)
		{
			auto playerComp = _pPlayerRepository->GetWhere([_entity](Player& comp) { return comp.nEntityId == _entity; }).front();

			return playerComp.bViewingPlayer;
		}

        static Player SetFrags(uint64_t _entity, unsigned long _nFrags)
        {
			auto playerComp = _pPlayerRepository->GetWhere([_entity](Player& comp) { return comp.nEntityId == _entity; }).front();

			playerComp.nFrags = _nFrags;

			return _pPlayerRepository->Set(playerComp.nId, playerComp);
        }

        static unsigned long GetFrags(uint64_t _entity)
        {
			auto playerComp = _pPlayerRepository->GetWhere([_entity](Player& comp) { return comp.nEntityId == _entity; }).front();

			return playerComp.nFrags;
        }

        static Player SetDeaths(uint64_t _entity, unsigned long _nDeaths)
        {
			auto playerComp = _pPlayerRepository->GetWhere([_entity](Player& comp) { return comp.nEntityId == _entity; }).front();

			playerComp.nDeaths = _nDeaths;

			return _pPlayerRepository->Set(playerComp.nId, playerComp);
        }

        static unsigned long GetDeaths(uint64_t _entity)
        {
			auto playerComp = _pPlayerRepository->GetWhere([_entity](Player& comp) { return comp.nEntityId == _entity; }).front();

			return playerComp.nDeaths;
        }

        static Player SetDrive(uint64_t _entity, float _nDrive)
        {
			auto playerComp = _pPlayerRepository->GetWhere([_entity](Player& comp) { return comp.nEntityId == _entity; }).front();

			playerComp.nDrive = _nDrive;

			return _pPlayerRepository->Set(playerComp.nId, playerComp);
        }

        static float GetDrive(uint64_t _entity)
        {
			auto playerComp = _pPlayerRepository->GetWhere([_entity](Player& comp) { return comp.nEntityId == _entity; }).front();

			return playerComp.nDrive;
        }

        static Player SetStrafe(uint64_t _entity, float _nStrafe)
        {
			auto playerComp = _pPlayerRepository->GetWhere([_entity](Player& comp) { return comp.nEntityId == _entity; }).front();

			playerComp.nStrafe = _nStrafe;

			return _pPlayerRepository->Set(playerComp.nId, playerComp);
        }

        static float GetStrafe(uint64_t _entity)
        {
			auto playerComp = _pPlayerRepository->GetWhere([_entity](Player& comp) { return comp.nEntityId == _entity; }).front();

			return playerComp.nStrafe;
        }

        static Player SetFire(uint64_t _entity, bool _bFire)
        {
			auto playerComp = _pPlayerRepository->GetWhere([_entity](Player& comp) { return comp.nEntityId == _entity; }).front();

			playerComp.bFire = _bFire;

			return _pPlayerRepository->Set(playerComp.nId, playerComp);
        }

        static bool GetFire(uint64_t _entity)
        {
			auto playerComp = _pPlayerRepository->GetWhere([_entity](Player& comp) { return comp.nEntityId == _entity; }).front();

			return playerComp.bFire;
        }

        static Player SetViewTilt(uint64_t _entity, float nTilt)
        {
			auto playerComp = _pPlayerRepository->GetWhere([_entity](Player& comp) { return comp.nEntityId == _entity; }).front();

			playerComp.nViewTilt = nTilt;

			return _pPlayerRepository->Set(playerComp.nId, playerComp);
        }

        static float ViewTilt(uint64_t _entity)
        {
			auto playerComp = _pPlayerRepository->GetWhere([_entity](Player& comp) { return comp.nEntityId == _entity; }).front();

			return playerComp.nViewTilt;
        }

        static Leadwerks::Vec3 GetEyePoint(uint64_t _entity)
        {
			auto playerComp = _pPlayerRepository->GetWhere([_entity](Player& comp) { return comp.nEntityId == _entity; }).front();

			return playerComp.vViewPoint;
        }
    };
} // < end namespace.

#endif _PLAYER_SYSTEM_HPP_
