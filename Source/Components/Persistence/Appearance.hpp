#ifndef _PERSISTENCE_APPEARANCE_HPP_
    #define _PERSISTENCE_APPEARANCE_HPP_

#pragma once
#include "../../Common.hpp"
#include "../../Utilities/Macros.hpp"

#include <string>

namespace Components
{
    namespace Persistence
    {
        class Appearance
        {
            CLASS_TYPE(Appearance);

        public:

            uint64_t nId;
            uint64_t nEntityId;
            std::string cModelPath;
            std::string cName;
            uint64_t nComponentId;

            std::string cCreatedDate;
            std::string cModifiedDate;

            Appearance Merge(const Appearance& other)
            {
                auto self = *this;

                self.nId = other.nId;
                self.nComponentId = other.nComponentId;
                self.cCreatedDate = other.cCreatedDate;

                return self;
            }
        };

    } // < end namespace.
} // < end namespace.

#endif _PERSISTENCE_APPEARANCE_HPP_