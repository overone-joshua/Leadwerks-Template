/*-------------------------------------------------------
                    <copyright>
    
    File: DefaultState.hpp
    Language: C++
    
    (C) Copyright Eden Softworks
    
    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net
    
    Description: Header file for DefaultState class.
                 The DefaultState class exists to provide
                 a concrete example of how other
                 application states can implement to
                 base state class to provide state
                 gameplay-based logic.

---------------------------------------------------------*/

#ifndef _DEFAULT_STATE_HPP_
	#define _DEFAULT_STATE_HPP_

#pragma once
#include "State.hpp"
#include "../Managers/InputManager.hpp"

#include "../Utilities/CameraHandle.hpp"
#include "../Utilities/Container.hpp"
#include "../Utilities/Delegate.hpp"
#include "../Utilities/Event.hpp"

#include "../Components/World.hpp"

#include "../Entities/Entity.hpp"
#include "../Entities/Actor.hpp"
#include "../Entities/Camera.hpp"
#include "../Entities/Input.hpp"

#include "../Entities/Custom/SpectatorCamera.hpp"

class DefaultState : public State {

	CLASS_TYPE(DefaultState);

public:		

	                       DefaultState(void);

	void                   Configure(Container* pContainer);
	void                   Load(void);
	void                   Close(void);

	bool                   Update(float deltaTime);

    void                    OnMouseMove(Event_MouseMove* pEvent);

	void                   OnKeyDown(Event_KeyDown* pEvent);
	void                   OnKeyUp(Event_KeyUp* pEvent);

private:

    InputManager*          m_pInputMgr;
    CameraHandle*          m_pCameraHndl;

	Leadwerks::Light*	  m_pSceneLight;		

	Components::World*     m_pWorld;

    uint64_t                m_player;
    uint64_t                m_camera;	    

}; // < end class.

#endif _DEFAULT_STATE_HPP_