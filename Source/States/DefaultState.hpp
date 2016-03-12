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
#include "../Utilities/Event.hpp"
#include "../Utilities/IsoSurface.hpp"
#include "../Utilities/Modeler.hpp"
#include "../Utilities/VoxelBuffer.hpp"

#include "../Components/World.hpp"
#include "../Entities/CameraDynamic.hpp"
#include "../Entities/Prop.hpp"

#include "../Utilities/luatables/luatables.h"

#define ISOLEVEL				0.0f
#define VOXELS_PER_CELL			9
#define DATACELL_SIZE			7.0f
#define VOXEL_SIZE				1.0f
#define RENDERCELL_SIZE			64.0f
#define CELLS_PER_ISOSURFACE	8
#define NUM_VOXELS				9

class DefaultState : public State {

	CLASS_TYPE(DefaultState);

public:		

	                       DefaultState(void);

	void                   Configure(Container* pContainer);
	void                   Load(void);
	void                   Close(void);

	bool                   Update(float deltaTime);

	void                   OnKeyDown(Event_KeyDown* pEvent);
	void                   OnKeyUp(Event_KeyUp* pEvent);

private:

	IsoSurface<float>*     m_pIsosurface;
	Leadwerks::Model*      m_pModel;
	VoxelBuffer<float>*    m_pBuffer;

    InputManager*          m_pInputMgr;
	CameraHandle*          m_pCameraHndl;

	Components::World*     m_pWorld;

	uint64_t               m_cameraDynamic;	
    uint64_t               m_crawlerModel;

}; // < end class.

DefaultState::DefaultState(void) { }

void DefaultState::Configure(Container* pContainer)
{
	m_pCameraHndl = pContainer->Resolve<CameraHandle>();
    m_pInputMgr = pContainer->Resolve<InputManager>();
}

void DefaultState::Load(void) 
{ 	
	m_pWorld = new Components::World();
	m_cameraDynamic = Entities::CameraDynamic::Create(m_pWorld, m_pCameraHndl, "./Scripts/Camera.lua");

    // < Create a sample Appearance component using a lua script.    
    m_crawlerModel = Entities::Prop::Create(m_pWorld, "./Scripts/Crawler.lua");

	m_pCameraHndl->getInst()->SetDrawMode(DRAW_WIREFRAME);
    m_pInputMgr->ToggleMouseCenter();

	m_pModel = Leadwerks::Model::Create();
	m_pBuffer = new VoxelBuffer<float>(NUM_VOXELS, NUM_VOXELS, NUM_VOXELS);
	m_pIsosurface = new IsoSurface<float>();

	ModelerInput<float> input;
	Modeler<float> modeler;
	modeler.Assign(*m_pBuffer);

	for (unsigned z = 0; z <= 8; z += 1)
		for (unsigned y = 0; y <= 8; y += 1)
			for (unsigned x = 0; x <= 8; x += 1) {
				input.pt[0] = x; input.pt[1] = y; input.pt[2] = z;
				
				// < Formula for a circle.
				if (sqrt((x - 4) * (x - 4) + (y - 4) * (y - 4) + (z - 4) * (z - 4)) < 4)
					input.val = -1.0f;
				else
					input.val = 1.0f;

				modeler.AddInput(input);
			} // end for
	
	modeler.Execute();

	unsigned nTriangles = m_pIsosurface->GenerateSurface(*m_pModel,
		*m_pBuffer,
		0.0,
		CELLS_PER_ISOSURFACE,
		CELLS_PER_ISOSURFACE,
		CELLS_PER_ISOSURFACE,
		VOXEL_SIZE,
		VOXEL_SIZE,
		VOXEL_SIZE);

}

void DefaultState::Close(void) 
{ 		
    m_pInputMgr->ToggleMouseCenter();

	SAFE_DELETE(m_pWorld);

	m_pCameraHndl = nullptr;
    m_pInputMgr = nullptr;

	SAFE_DELETE(m_pIsosurface);
	SAFE_DELETE(m_pBuffer);

	SAFE_RELEASE(m_pModel);
	SAFE_DELETE(m_pModel);

}

bool DefaultState::Update(float dt) { 

    Components::Input& inputComponent = m_pWorld->GetComponents<Components::Input>(m_pWorld, m_cameraDynamic)
        ->front();

    if (m_pInputMgr->DeltaX() < 0) { inputComponent.nMask |= INPUT_ROTATE_LEFT; }
    if (m_pInputMgr->DeltaX() > 0) { inputComponent.nMask |= INPUT_ROTATE_RIGHT; }

    if (m_pInputMgr->DeltaY() < 0) { inputComponent.nMask |= INPUT_ROTATE_DOWN; }
    if (m_pInputMgr->DeltaY() > 0) { inputComponent.nMask |= INPUT_ROTATE_UP; }

	Entities::CameraDynamic::Update(m_pInputMgr, m_pWorld, dt);	

	return true;

}

void DefaultState::OnKeyDown(Event_KeyDown* pEvent)
{
	Components::Input& inputComponent = m_pWorld->GetComponents<Components::Input>(m_pWorld, m_cameraDynamic)
		->front();    

	if (pEvent->Key() == Leadwerks::Key::W) { inputComponent.nMask |= INPUT_MOVE_FORWARD; }
	if (pEvent->Key() == Leadwerks::Key::A) { inputComponent.nMask |= INPUT_MOVE_LEFT; }
	if (pEvent->Key() == Leadwerks::Key::S) { inputComponent.nMask |= INPUT_MOVE_BACKWARD; }
	if (pEvent->Key() == Leadwerks::Key::D) { inputComponent.nMask |= INPUT_MOVE_RIGHT; }

	if (pEvent->Key() == Leadwerks::Key::E) { inputComponent.nMask |= INPUT_MOVE_UP; }
	if (pEvent->Key() == Leadwerks::Key::Q) { inputComponent.nMask |= INPUT_MOVE_DOWN; }

}

void DefaultState::OnKeyUp(Event_KeyUp* pEvent)
{
	Components::Input& inputComponent = m_pWorld->GetComponents<Components::Input>(m_pWorld, m_cameraDynamic)
		->front();

	if (pEvent->Key() == Leadwerks::Key::W) { inputComponent.nMask &= ~INPUT_MOVE_FORWARD; }
	if (pEvent->Key() == Leadwerks::Key::A) { inputComponent.nMask &= ~INPUT_MOVE_LEFT; }
	if (pEvent->Key() == Leadwerks::Key::S) { inputComponent.nMask &= ~INPUT_MOVE_BACKWARD; }
	if (pEvent->Key() == Leadwerks::Key::D) { inputComponent.nMask &= ~INPUT_MOVE_RIGHT; }

	if (pEvent->Key() == Leadwerks::Key::E) { inputComponent.nMask &= ~INPUT_MOVE_UP; }
	if (pEvent->Key() == Leadwerks::Key::Q) { inputComponent.nMask &= ~INPUT_MOVE_DOWN; }

}

#endif _DEFAULT_STATE_HPP_