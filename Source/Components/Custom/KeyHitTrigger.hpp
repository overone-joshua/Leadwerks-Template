#ifndef _KEY_HIT_TRIGGER_COMPONENT_HPP_
	#define _KEY_HIT_TRIGGER_COMPONENT_HPP_

#pragma once
#include "../../Common.hpp"
#include "../../Utilities/Event.hpp"
#include "../../Utilities/Macros.hpp"

#include "../World.hpp"
#include "../Trigger.hpp"

namespace Components
{
	template <typename T>
	struct KeyHitTrigger : public Trigger<Components::World&, T, Event_KeyHit*>
	{
        typedef Delegate<Components::World&, T, Event_KeyHit*> KeyHitEvent;

		CLASS_TYPE(KeyHitTrigger);

		KeyHitTrigger(KeyHitEvent _callback, std::string _cName = "")
			: Trigger(_callback, _cName) { }

	}; // < end class.

} // < end namespace.

#endif _KEY_HIT_TRIGGER_COMPONENT_HPP_