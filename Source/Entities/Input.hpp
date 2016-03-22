#ifndef _INPUT_ENTITY_HPP_
	#define _INPUT_ENTITY_HPP_

#pragma once
#include "../Common.hpp"
#include "../Utilities/Event.hpp"
#include "../Utilities/Macros.hpp"
#include "../Utilities/luatables/luatables.h"

#include "../Components/Component.hpp"
#include "../Components/ComponentDictionary.hpp"
#include "../Components/Trigger.hpp"
#include "../Components/World.hpp"

#include "../Components/Custom/MouseMoveTrigger.hpp"
#include "../Components/Custom/MouseHitTrigger.hpp"
#include "../Components/Custom/MouseDownTrigger.hpp"
#include "../Components/Custom/MouseUpTrigger.hpp"
#include "../Components/Custom/KeyHitTrigger.hpp"
#include "../Components/Custom/KeyDownTrigger.hpp"
#include "../Components/Custom/KeyUpTrigger.hpp"

#include <string>
#include <vector>

namespace Entities
{
	const uint64_t MASK_INPUT = COMPONENT_TRIGGER;

	template <typename T>
	class Input
	{
		CLASS_TYPE(Input);

	public:
		Input(void) 
		{
			mouseMoveTriggers = nullptr;
			mouseHitTriggers = nullptr;
			mouseDownTriggers = nullptr;
			mouseUpTriggers = nullptr;

			keyHitTriggers = nullptr;
			keyDownTriggers = nullptr;
			keyUpTriggers = nullptr;
		}		

		Components::Component component;
		
		std::vector<Components::MouseMoveTrigger<T>>* mouseMoveTriggers;
		std::vector<Components::MouseHitTrigger<T>>* mouseHitTriggers;			
		std::vector<Components::MouseDownTrigger<T>>* mouseDownTriggers;		
		std::vector<Components::MouseUpTrigger<T>>* mouseUpTriggers;		
		std::vector<Components::KeyHitTrigger<T>>* keyHitTriggers;		
		std::vector<Components::KeyDownTrigger<T>>* keyDownTriggers;		
		std::vector<Components::KeyUpTrigger<T>>* keyUpTriggers;	

	public:

		template <void(*Function)(Components::World&, T, Event_MouseMove*)>
		static void BindMouseMove(Components::World& world, uint64_t entity, std::string name);

		template <class C, void(C::*Function)(Components::World&, T, Event_MouseMove*)>
		static void BindMouseMove(Components::World& world, C* pInst, uint64_t entity, std::string name);

		template <void(*Function)(Components::World&, T, Event_MouseHit*)>
		static void BindMouseHit(Components::World& world, uint64_t entity, std::string name);

		template <class C, void(C::*Function)(Components::World&, T, Event_MouseHit*)>
		static void BindMouseHit(Components::World& world, C* pInst, uint64_t entity, std::string name);

		template <void(*Function)(Components::World&, T, Event_MouseDown*)>
		static void BindMouseDown(Components::World& world, uint64_t entity, std::string name);

		template <class C, void(C::*Function)(Components::World&, T, Event_MouseDown*)>
		static void BindMouseDown(Components::World& world, C* pInst, uint64_t entity, std::string name);

		template <void(*Function)(Components::World&, T, Event_MouseUp*)>
		static void BindMouseUp(Components::World& world, uint64_t entity, std::string name);

		template <class C, void(C::*Function)(Components::World&, T, Event_MouseUp*)>
		static void BindMouseUp(Components::World& world, C* pInst, uint64_t entity, std::string name);		

		template <void(*Function)(Components::World&, T, Event_KeyHit*)>
		static void BindKeyHit(Components::World& world, uint64_t entity, std::string name);

		template <class C, void(C::*Function)(Components::World&, T, Event_KeyHit*)>
		static void BindKeyHit(Components::World& world, C* pInst, uint64_t entity, std::string name);

		template <void(*Function)(Components::World&, T, Event_KeyDown*)>
		static void BindKeyDown(Components::World& world, uint64_t entity, std::string name);

		template <class C, void(C::*Function)(Components::World&, T, Event_KeyDown*)>
		static void BindKeyDown(Components::World& world, C* pInst, uint64_t entity, std::string name);

		template <void(*Function)(Components::World&, T, Event_KeyUp*)>
		static void BindKeyUp(Components::World& world, uint64_t entity, std::string name);

		template <class C, void(C::*Function)(Components::World&, T, Event_KeyUp*)>
		static void BindKeyUp(Components::World& world, C* pInst, uint64_t entity, std::string name);

		static void TriggerMouseMove(Components::World& world, uint64_t entity, Event_MouseMove* pEvent);

		static void TriggerMouseHit(Components::World& world, uint64_t entity, Event_MouseHit* pEvent);

		static void TriggerMouseDown(Components::World& world, uint64_t entity, Event_MouseDown* pEvent);

		static void TriggerMouseUp(Components::World& world, uint64_t entity, Event_MouseUp* pEvent);

		static void TriggerKeyHit(Components::World& world, uint64_t entity, Event_KeyHit* pEvent);

		static void TriggerKeyDown(Components::World& world, uint64_t entity, Event_KeyDown* pEvent);

		static void TriggerKeyUp(Components::World& world, uint64_t entity, Event_KeyUp* pEvent);	

	protected:

		static void BindMouseMoveInternal(Components::World& world, uint64_t entity, std::string name, Delegate<Components::World&, T, Event_MouseMove*> eventDelegate);

		static void BindMouseHitInternal(Components::World& world, uint64_t entity, std::string name, Delegate<Components::World&, T, Event_MouseHit*> eventDelegate);

		static void BindMouseDownInternal(Components::World& world, uint64_t entity, std::string name, Delegate<Components::World&, T, Event_MouseDown*> eventDelegate);

		static void BindMouseUpInternal(Components::World& world, uint64_t entity, std::string name, Delegate<Components::World&, T, Event_MouseUp*> eventDelegate);

		static void BindKeyHitInternal(Components::World& world, uint64_t entity, std::string name, Delegate<Components::World&, T, Event_KeyHit*> eventDelegate);

		static void BindKeyDownInternal(Components::World& world, uint64_t entity, std::string name, Delegate<Components::World&, T, Event_KeyDown*> eventDelegate);

		static void BindKeyUpInternal(Components::World& world, uint64_t entity, std::string name, Delegate<Components::World&, T, Event_KeyUp*> eventDelegate);

	}; // < end class.

	template <typename T>
	template <void(*Function)(Components::World&, T, Event_MouseMove*)>
	void Input<T>::BindMouseMove(Components::World& world, uint64_t entity, std::string name)
	{
		auto trigger = Components::MouseMoveTrigger<T>::MouseMoveEvent();
		trigger.Bind<Function>();

		BindMouseMoveInternal(world, entity, name, trigger);
	}

	template <typename T>
	template <class C, void(C::*Function)(Components::World&, T, Event_MouseMove*)>
	void Input<T>::BindMouseMove(Components::World& world, C* pInst, uint64_t entity, std::string name)
	{
		auto trigger = Components::MouseMoveTrigger<T>::MouseMoveEvent();
		trigger.Bind<C, Function>(pInst);

		BindMouseMoveInternal(world, entity, name, trigger);
	}

	template <typename T>
	template <void(*Function)(Components::World&, T, Event_MouseHit*)>
	void Input<T>::BindMouseHit(Components::World& world, uint64_t entity, std::string name)
	{
		auto trigger = Components::MouseHitTrigger<T>::MouseHitEvent();
		trigger.Bind<Function>();

		BindMouseHitInternal(world, entity, name, trigger);
	}

	template <typename T>
	template <class C, void(C::*Function)(Components::World&, T, Event_MouseHit*)>
	void Input<T>::BindMouseHit(Components::World& world, C* pInst, uint64_t entity, std::string name)
	{
		auto trigger = Components::MouseHitTrigger<T>::MouseHitEvent();
		trigger.Bind<C, Function>(pInst);

		BindMouseHitInternal(world, entity, name, trigger);
	}

	template <typename T>
	template <void(*Function)(Components::World&, T, Event_MouseDown*)>
	void Input<T>::BindMouseDown(Components::World& world, uint64_t entity, std::string name)
	{
		auto trigger = Components::MouseDownTrigger<T>::MouseDownEvent();
		trigger.Bind<Function>();

		BindMouseDownInternal(world, entity, name, trigger);
	}

	template <typename T>
	template <class C, void(C::*Function)(Components::World&, T, Event_MouseDown*)>
	void Input<T>::BindMouseDown(Components::World& world, C* pInst, uint64_t entity, std::string name)
	{
		auto trigger = Components::MouseDownTrigger<T>::MouseDownEvent();
		trigger.Bind<C, Function>(pInst);

		BindMouseDownInternal(world, entity, name, trigger);
	}

	template <typename T>
	template <void(*Function)(Components::World&, T, Event_MouseUp*)>
	void Input<T>::BindMouseUp(Components::World& world, uint64_t entity, std::string name)
	{
		auto trigger = Components::MouseUpTrigger<T>::MouseUpEvent();
		trigger.Bind<Function>();

		BindMouseUpInternal(world, entity, name, trigger);
	}

	template <typename T>
	template <class C, void(C::*Function)(Components::World&, T, Event_MouseUp*)>
	void Input<T>::BindMouseUp(Components::World& world, C* pInst, uint64_t entity, std::string name)
	{
		auto trigger = Components::MouseUpTrigger<T>::MouseUpEvent();
		trigger.Bind<C, Function>(pInst);

		BindMouseUpInternal(world, entity, name, trigger);
	}

	template <typename T>
	template <void(*Function)(Components::World&, T, Event_KeyHit*)>
	void Input<T>::BindKeyHit(Components::World& world, uint64_t entity, std::string name)
	{
		auto trigger = Components::KeyHitTrigger<T>::KeyHitEvent();
		trigger.Bind<Function>();

		BindKeyHitInternal(world, entity, name, trigger);
	}

	template <typename T>
	template <class C, void(C::*Function)(Components::World&, T, Event_KeyHit*)>
	void Input<T>::BindKeyHit(Components::World& world, C* pInst, uint64_t entity, std::string name)
	{
		auto trigger = Components::KeyHitTrigger<T>::KeyHitEvent();
		trigger.Bind<C, Function>(pInst);

		BindKeyHitInternal(world, entity, name, trigger);
	}

	template <typename T>
	template <void(*Function)(Components::World&, T, Event_KeyDown*)>
	void Input<T>::BindKeyDown(Components::World& world, uint64_t entity, std::string name)
	{
		auto trigger = Components::KeyDownTrigger<T>::KeyDownEvent();
		trigger.Bind<Function>();

		BindKeyDownInternal(world, entity, name, trigger);
	}

	template <typename T>
	template <class C, void(C::*Function)(Components::World&, T, Event_KeyDown*)>
	void Input<T>::BindKeyDown(Components::World& world, C* pInst, uint64_t entity, std::string name)
	{
		auto trigger = Components::KeyDownTrigger<T>::KeyDownEvent();
		trigger.Bind<C, Function>(pInst);

		BindKeyDownInternal(world, entity, name, trigger);
	}

	template <typename T>
	template <void(*Function)(Components::World&, T, Event_KeyUp*)>
	void Input<T>::BindKeyUp(Components::World& world, uint64_t entity, std::string name)
	{
		auto trigger = Components::KeyUpTrigger<T>::KeyUpEvent();
		trigger.Bind<Function>();

		BindKeyUpInternal(world, entity, name, trigger);
	}

	template <typename T>
	template <class C, void(C::*Function)(Components::World&, T, Event_KeyUp*)>
	void Input<T>::BindKeyUp(Components::World& world, C* pInst, uint64_t entity, std::string name)
	{
		auto trigger = Components::KeyUpTrigger<T>::KeyUpEvent();
		trigger.Bind<C, Function>(pInst);

		BindKeyUpInternal(world, entity, name, trigger);
	}

	template <typename T>
	void Input<T>::BindMouseMoveInternal(Components::World& world, uint64_t entity, std::string name, Delegate<Components::World&, T, Event_MouseMove*> eventDelegate)
	{
		world.AddComponent(&world, entity, Components::MouseMoveTrigger<T>(eventDelegate, name));
	}

	template <typename T>
	void Input<T>::BindMouseHitInternal(Components::World& world, uint64_t entity, std::string name, Delegate<Components::World&, T, Event_MouseHit*> eventDelegate)
	{
		world.AddComponent(&world, entity, Components::MouseHitTrigger<T>(eventDelegate, name));
	}

	template <typename T>
	void Input<T>::BindMouseDownInternal(Components::World& world, uint64_t entity, std::string name, Delegate<Components::World&, T, Event_MouseDown*> eventDelegate)
	{
		world.AddComponent(&world, entity, Components::MouseDownTrigger<T>(eventDelegate, name));
	}

	template <typename T>
	void Input<T>::BindMouseUpInternal(Components::World& world, uint64_t entity, std::string name, Delegate<Components::World&, T, Event_MouseUp*> eventDelegate)
	{
		world.AddComponent(&world, entity, Components::MouseUpTrigger<T>(eventDelegate, name));
	}

	template <typename T>
	void Input<T>::BindKeyHitInternal(Components::World& world, uint64_t entity, std::string name, Delegate<Components::World&, T, Event_KeyHit*> eventDelegate)
	{
		world.AddComponent(&world, entity, Components::KeyHitTrigger<T>(eventDelegate, name));
	}

	template <typename T>
	void Input<T>::BindKeyDownInternal(Components::World& world, uint64_t entity, std::string name, Delegate<Components::World&, T, Event_KeyDown*> eventDelegate)
	{
		world.AddComponent(&world, entity, Components::KeyDownTrigger<T>(eventDelegate, name));
	}

	template <typename T>
	void Input<T>::BindKeyUpInternal(Components::World& world, uint64_t entity, std::string name, Delegate<Components::World&, T, Event_KeyUp*> eventDelegate)
	{
		world.AddComponent(&world, entity, Components::KeyUpTrigger<T>(eventDelegate, name));
	}

	template <typename T>
	void Input<T>::TriggerMouseMove(Components::World& world, uint64_t entity, Event_MouseMove* pEvent)
	{
		auto res = Components::World::Get<T>(world, entity);
		if (res.mouseMoveTriggers == nullptr) { return; }

		auto iter = res.mouseMoveTriggers->begin();
		while (iter != res.mouseMoveTriggers->end())
		{
			auto trigger = (*iter);

			trigger.callback.Invoke(world, res, pEvent);

			++iter;
		}
	}

	template <typename T>
	void Input<T>::TriggerMouseHit(Components::World& world, uint64_t entity, Event_MouseHit* pEvent)
	{
		auto res = Components::World::Get<T>(world, entity);
		if (res.mouseHitTriggers == nullptr) { return; }

		auto iter = res.mouseHitTriggers->begin();
		while (iter != res.mouseHitTriggers->end())
		{
			auto trigger = (*iter);

			trigger.callback.Invoke(world, res, pEvent);

			++iter;
		}
	}

	template <typename T>
	void Input<T>::TriggerMouseDown(Components::World& world, uint64_t entity, Event_MouseDown* pEvent)
	{
		auto res = Components::World::Get<T>(world, entity);
		if (res.mouseDownTriggers == nullptr) { return; }

		auto iter = res.mouseDownTriggers->begin();
		while (iter != res.mouseDownTriggers->end())
		{
			auto trigger = (*iter);

			trigger.callback.Invoke(world, res, pEvent);

			++iter;
		}
	}

	template <typename T>
	void Input<T>::TriggerMouseUp(Components::World& world, uint64_t entity, Event_MouseUp* pEvent)
	{
		auto res = Components::World::Get<T>(world, entity);
		if (res.mouseUpTriggers == nullptr) { return; }

		auto iter = res.mouseUpTriggers->begin();
		while (iter != res.mouseUpTriggers->end())
		{
			auto trigger = (*iter);

			trigger.callback.Invoke(world, res, pEvent);

			++iter;
		}
	}

	template <typename T>
	void Input<T>::TriggerKeyHit(Components::World& world, uint64_t entity, Event_KeyHit* pEvent)
	{
		auto res = Components::World::Get<T>(world, entity);
		if (res.keyHitTriggers == nullptr) { return; }

		auto iter = res.keyHitTriggers->begin();
		while (iter != res.keyHitTriggers->end())
		{
			auto trigger = (*iter);

			trigger.callback.Invoke(world, res, pEvent);

			++iter;
		}
	}

	template <typename T>
	void Input<T>::TriggerKeyDown(Components::World& world, uint64_t entity, Event_KeyDown* pEvent)
	{
		auto res = Components::World::Get<T>(world, entity);
		if (res.keyDownTriggers == nullptr) { return; }

		auto iter = res.keyDownTriggers->begin();
		while (iter != res.keyDownTriggers->end())
		{
			auto trigger = (*iter);

			trigger.callback.Invoke(world, res, pEvent);

			++iter;
		}
	}

	template <typename T>
	void Input<T>::TriggerKeyUp(Components::World& world, uint64_t entity, Event_KeyUp* pEvent)
	{
		auto res = Components::World::Get<T>(world, entity);
		if (res.keyUpTriggers == nullptr) { return; }

		auto iter = res.keyUpTriggers->begin();
		while (iter != res.keyUpTriggers->end())
		{
			auto trigger = (*iter);

			trigger.callback.Invoke(world, res, pEvent);

			++iter;
		}
	}

} // < end namespace.

#endif _INPUT_ENTITY_HPP_