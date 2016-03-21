#ifndef _KEY_DOWN_TRIGGER_COMPONENT_HPP_
	#define _KEY_DOWN_TRIGGER_COMPONENT_HPP_

#pragma once
#include "../../Common.hpp"
#include "../../Utilities/Event.hpp"
#include "../../Utilities/Macros.hpp"

#include "../World.hpp"
#include "../Trigger.hpp"

namespace Components
{
	template <typename T>
	struct KeyDownTrigger : public Trigger<Components::World&, T, Event_KeyDown*>
	{
        typedef Delegate<Components::World&, T, Event_KeyDown*> KeyDownEvent;

		CLASS_TYPE(KeyDownTrigger);

		KeyDownTrigger(KeyDownEvent _callback, std::string _cName = "")
			: Trigger(_callback, _cName) { }

	}; // < end class.

} // < end namespace.

#endif _KEY_DOWN_TRIGGER_COMPONENT_HPP_