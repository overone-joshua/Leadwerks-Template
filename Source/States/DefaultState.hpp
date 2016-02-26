#ifndef _DEFAULT_STATE_HPP_
	#define _DEFAULT_STATE_HPP_

#pragma once
#include "State.hpp"
#include "../Utilities/IsoSurface.hpp"
#include "../Utilities/Modeler.hpp"
#include "../Utilities/VoxelBuffer.hpp"

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

	void Load(void);
	void Close(void);

	bool Update(float deltaTime);

private:

	IsoSurface<float>* m_pIsosurface;
	Leadwerks::Model* m_pModel;
	VoxelBuffer<float>* m_pBuffer;

}; // < end class.

DefaultState::DefaultState(void) { }

void DefaultState::Load(void) 
{ 
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
				if (y <= 4)
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
	SAFE_DELETE(m_pIsosurface);
	SAFE_DELETE(m_pBuffer);

	SAFE_RELEASE(m_pModel);
	SAFE_DELETE(m_pModel);

}

bool DefaultState::Update(float dt) { 

	return true;

}

#endif _DEFAULT_STATE_HPP_