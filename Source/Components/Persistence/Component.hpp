#ifndef _PERSISTENCE_COMPONENT_HPP_
    #define _PERSISTENCE_COMPONENT_HPP_

#pragma once
#include "../../Common.hpp"
#include "../../Utilities/Macros.hpp"

#include <string>

namespace Components
{
    namespace Persistence
    {
        class Component
        {
            CLASS_TYPE(Component);

        public:

            uint64_t    nId;
            uint64_t    nEntityId;
            std::string cName;

            std::string cCreatedDate;
            std::string cModifiedDate;

            Component Merge(const Component& other)
            {
                auto self = *this;

                self.nId = other.nId;
                self.nEntityId = other.nEntityId;
                self.cCreatedDate = other.cCreatedDate;

                return self;
            }
        };

    } // < end namespace.
} // < end namespace.

#endif _PERSISTENCE_COMPONENT_HPP_