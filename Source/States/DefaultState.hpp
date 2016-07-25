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
#include "../Utilities/ContextHandle.hpp"
#include "../Utilities/WorldHandle.hpp"
#include "../Utilities/Container.hpp"
#include "../Utilities/Delegate.hpp"
#include "../Utilities/Event.hpp"

#include "../Components/Component.hpp"
#include "../Components/Level.hpp"
#include "../Components/LevelEditor.hpp"
#include "../Components/Placement.hpp"
#include "../Components/Player.hpp"
#include "../Components/World.hpp"

#include <sqlite-persistence/DbConnection.hpp>

class DefaultState : public State {

	CLASS_TYPE(DefaultState);

public:

	                       DefaultState(void);

	void                   Configure(Container* pContainer);
	void                   Load(void);
	void                   Close(void);

    void                   Draw(void);

	bool                   Update(float deltaTime);

    void                    OnMouseHit(Event_MouseHit* pEvent);
    void                    OnMouseMove(Event_MouseMove* pEvent);
    void                    OnMouseUp(Event_MouseUp* pEvent);

	void                   OnKeyDown(Event_KeyDown* pEvent);
	void                   OnKeyUp(Event_KeyUp* pEvent);

protected:

    // < Test objects.
    Leadwerks::Model* pModel;

private:

    IDbConnection*          m_pConnection;
    InputManager*           m_pInputMgr;
    CameraHandle*           m_pCameraHndl;
    ContextHandle*          m_pContextHndl;
    WorldHandle*            m_pWorldHndl;

	Leadwerks::Light*	    m_pSceneLight;

	Components::World*      m_pWorld;
    Components::Level*      m_pLevel;
    Components::LevelEditor* m_pLevelEditor;
    Components::Placement*  m_pCamera;
    Components::Player*     m_pPlayerEditor;

    uint64_t                m_level;
    uint64_t                m_levelEditor;
    uint64_t                m_camera;

}; // < end class.

#endif _DEFAULT_STATE_HPP_