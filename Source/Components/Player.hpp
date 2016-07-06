#ifndef _PLAYER_COMPONENT_HPP_
    #define _PLAYER_COMPONENT_HPP_

#pragma once
#include "Leadwerks.h"
#include "../Utilities/Macros.hpp"

#include "Component.hpp"

#include <string>

namespace Components
{
    typedef struct Component_Player : public Component
    {
        CLASS_TYPE(Player);

        bool bViewingPlayer;

        Leadwerks::Vec3 vViewPoint;
        float nViewTilt;

        float nViewSmoothing;
        float nViewSensitivity;

        float nHealth;
        bool bDying;

        float nDrive;
        float nStrafe;

        bool bFire;
        unsigned long nFrags;
        unsigned long nDeaths;

        explicit Component_Player(uint64_t _nEntityId = 0, const std::string& _cName = "")
            : Component(_nEntityId, _cName)
        {
            bViewingPlayer = false;

            vViewPoint = Leadwerks::Vec3(0.0f, 0.0f, 0.0f);
            nViewTilt = 0.0f;

            nViewSmoothing = 0.5f;
            nViewSensitivity = 0.5f;

            nHealth = 100.0f;
            bDying = false;

            bFire = false;

            nFrags = 0;
            nDeaths = 0;
        }

    } Player; // < end struct.
} // < end namespace.

#endif _PLAYER_COMPONENT_HPP_