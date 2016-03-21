#ifndef _MOUSE_DOWN_TRIGGER_COMPONENT_HPP_
	#define _MOUSE_DOWN_TRIGGER_COMPONENT_HPP_

#pragma once
#include "../../Common.hpp"
#include "../../Utilities/Event.hpp"
#include "../../Utilities/Macros.hpp"

#include "../World.hpp"
#include "../Trigger.hpp"

namespace Components
{
	template <typename T>
	struct MouseDownTrigger : public Trigger<Components::World&, T, Event_MouseDown*>
	{
        typedef Delegate<Components::World&, T, Event_MouseDown*> MouseDownEvent;

		CLASS_TYPE(MouseDownTrigger);

		MouseDownTrigger(MouseDownEvent _callback, std::string _cName = "")
			: Trigger(_callback, _cName) { }

	}; // < end class.

} // < end namespace.

#endif _MOUSE_DOWN_TRIGGER_COMPONENT_HPP_