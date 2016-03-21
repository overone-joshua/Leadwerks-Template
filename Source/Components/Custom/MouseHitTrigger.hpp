#ifndef _MOUSE_HIT_TRIGGER_COMPONENT_HPP_
	#define _MOUSE_HIT_TRIGGER_COMPONENT_HPP_

#pragma once
#include "../../Common.hpp"
#include "../../Utilities/Event.hpp"
#include "../../Utilities/Macros.hpp"

#include "../World.hpp"
#include "../Trigger.hpp"

namespace Components
{
	template <typename T>
	struct MouseHitTrigger : public Trigger<Components::World&, T, Event_MouseHit*>
	{
        typedef Delegate<Components::World&, T, Event_MouseHit*> MouseHitEvent;

		CLASS_TYPE(MouseHitTrigger);

		MouseHitTrigger(MouseHitEvent _callback, std::string _cName = "") 
			: Trigger(_callback, _cName) { }

	}; // < end class.

} // < end namespace.

#endif _MOUSE_HIT_TRIGGER_COMPONENT_HPP_