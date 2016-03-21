#ifndef _MOUSE_UP_TRIGGER_COMPONENT_HPP_
	#define _MOUSE_UP_TRIGGER_COMPONENT_HPP_

#pragma once
#include "../../Common.hpp"
#include "../../Utilities/Event.hpp"
#include "../../Utilities/Macros.hpp"

#include "../World.hpp"
#include "../Trigger.hpp"

namespace Components
{
	template <typename T>
	struct MouseUpTrigger : public Trigger<Components::World&, T, Event_MouseUp*>
	{
        typedef Delegate<Components::World&, T, Event_MouseUp*> MouseUpEvent;

		CLASS_TYPE(MouseUpTrigger);

		MouseUpTrigger(MouseUpEvent _callback, std::string _cName = "") 
			: Trigger(_callback, _cName) { }

	}; // < end class.

} // < end namespace.

#endif _MOUSE_UP_TRIGGER_COMPONENT_HPP_