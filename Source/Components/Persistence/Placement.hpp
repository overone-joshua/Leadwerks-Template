#ifndef _PERSISTENCE_PLACEMENT_HPP_
    #define _PERSISTENCE_PLACEMENT_HPP_

#pragma once

#include "../../Common.hpp"
#include "../../Utilities/Macros.hpp"

#include <string>

namespace Components
{
    namespace Persistence
    {
        class Placement
        {
            CLASS_TYPE(Placement);

        public:

            uint64_t nId;
            uint64_t nEntityId;
            std::string cName;
            uint64_t nComponentId;

            Leadwerks::Vec3 vForward;
            Leadwerks::Vec3 vRight;

            Leadwerks::Mat4 mWorld;
            Leadwerks::Mat4 mView;

            Leadwerks::Vec3 vTranslation;
            Leadwerks::Vec3 vRotation;

            Leadwerks::Vec3 vVelocity;
            Leadwerks::Vec3 vSpin;

            Leadwerks::Mat4 mTranslation;
            Leadwerks::Mat4 mRotation;

            float nFriction;
            bool bVisible;
            bool bGhost;
            bool bIgnoreCollision;
            bool bTouchingGround;

            std::string cCreatedDate;
            std::string cModifiedDate;

            Placement Merge(const Placement& other)
            {
                auto self = *this;

                self.nId = other.nId;
                self.nComponentId = other.nComponentId;
                self.cCreatedDate = other.cCreatedDate;

                return self;
            }

        }; // < end class.
    } // < end namespace.
} // < end namespace.

#endif _PLACEMENT_PLACEMENT_HPP_