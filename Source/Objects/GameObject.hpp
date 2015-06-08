#ifndef _GAMEOBJECT_H_
	#define _GAMEOBJECT_H_

#pragma once
#include "Leadwerks.h"

class GameObject {
public:
												GameObject();															// Game object's constructor
												~GameObject();															// Game object's destructor

	void										Update(float deltaTime);												// Game object's update.
	void										Render();																// Game object's render.
	void										Draw();																	// Game object's draw.

	void										Move(float deltaTime);													// Moves the game object, according to its current velocity.

	void										SetCamera(Leadwerks::Camera* pCamera);									// Sets the game object's camera.
	void										SetModel(Leadwerks::Model* pModel);										// Sets the game object's model.

	void										SetRotation(float x, float y, float z, bool bGlobal = false);			// Sets the rotation of the game object's model.
	void										SetRotation(Leadwerks::Vec3 vRotation, bool bGlobal = false);			// Sets the rotation of the game object's model.
	void										SetPosition(float x, float y, float z, bool bGlobal = false);			// Sets the position of the game object's model.
	void										SetPosition(Leadwerks::Vec3 vPosition, bool bGlobal = false);			// Sets the position of the game objects model.

	void										SetCameraRotation(float x, float y, float z, bool bGlobal = false);		// Sets the rotation of the game object's camera.
	void										SetCameraRotation(Leadwerks::Vec3 vRotation, bool bGlobal = false);		// Sets the rotation of the game object's camera.
	void										SetCameraPosition(float x, float y, float z, bool bGlobal = false);		// Sets the position of the game object's camera.
	void										SetCameraPosition(Leadwerks::Vec3 vPosition, bool bGlobal = false);		// Sets the position of the game object's camera.

	void										SetCameraPitch(float nPitch, bool bGlobal = false);						// Sets the pitch of the game object's camera.
	void										SetCameraYaw(float nYaw, bool bGlobal = false);							// Sets the yaw of the game object's camera.
	void										SetCameraRoll(float nRoll, bool bGlobal = false);						// Sets the roll of the game object's camera.

	void										SetModelPitch(float nPitch, bool bGlobal = false);						// Sets the pitch of the game object's model.
	void										SetModelYaw(float nYaw, bool bGlobal = false);							// Sets the yaw of the game object's model.
	void										SetModelRoll(float nRoll, bool bGlobal = false);						// ets the roll of the game object's model.

	void										SetMoveSpeed(float nSpeed);												// Sets the game object's move speed.
	void										SetStrafeSpeed(float nSpeed);											// Sets the game object's strafe speed.
	void										SetVertSpeed(float nSpeed);												// Sets the game object's vert-move speed.

	Leadwerks::Vec3								Forward();																// Gets the game object's current forward vector.
	Leadwerks::Vec3								Right();																// Gets the game object's current right vector.
	Leadwerks::Vec3								Up();																	// Gets the game object's current up vector.
	Leadwerks::Vec3								Velocity();																// Gets the game objects current velocity.

	Leadwerks::Vec3								CameraForward();														// Gets the camera's forward vector.
	Leadwerks::Vec3								CameraRight();															// Gets the camera's right vector.
	Leadwerks::Vec3								CameraUp();																// Gets the camera's up vector.
	Leadwerks::Vec3								CameraVelocity();														// Gets the camera's velocity.

	float										MoveSpeed();															// Gets the forward and backward, movement speed.
	float										StrafeSpeed();															// Gets the side to side, movement speed.
	float										VertSpeed();															// Gets the up and down, movement speed.

	Leadwerks::Vec3								Position();																// Gets the current position of the game object.
	Leadwerks::Vec3								Rotation();																// Gets the current rotation of the game object.
	Leadwerks::Vec3								Scale();																// Gets the current scale of the game object.
	
	Leadwerks::Vec3								CameraPosition();														// Gets the current position of the camera.
	Leadwerks::Vec3								CameraRotation();														// Gets the current rotation of the camera.

	float										Pitch();																// Gets the pitch of the game object.
	float										Yaw();																	// Gets the yaw of the game object.
	float										Roll();																	// Gets the roll of the game object.

	float										CameraPitch();															// Gets the pitch of the camera.
	float										CameraYaw();															// Gets the yaw of the camera.
	float										CameraRoll();															// Gets the roll of the camera.

	Leadwerks::Camera*							Camera();																// Gets the camera of the game object.
	Leadwerks::Model*							Model();																// Gets the model of the game object.

protected:
	Leadwerks::Vec3								CalcForwardVector(float pitch, float yaw);								// Calculates the forward vector, from the model.
	Leadwerks::Vec3								CalcRightVector(float pitch, float yaw);								// Calculates the right vector, from the model.
	Leadwerks::Vec3								CalcUpVector(float pitch, float yaw);									// Calculates the up vector, from the model.
	void										CalcVelocity();															// Calculates the velocity, for the model.

private:
	Leadwerks::Camera*							m_pCamera;																// The Leadwerks::camera handle.
	Leadwerks::Model*							m_pModel;																// The Leadwerks model handle.

	float										m_nMoveSpeed;															// The front and back speed of the game object.
	float										m_nStrafeMoveSpeed;														// The side to side speed of the game object.
	float										m_nVertMoveSpeed;														// The up and down speed of the game object..

	Leadwerks::Vec3								m_vForward;																// The game object's current forward vector.
	Leadwerks::Vec3								m_vRight;																// The game object's current right vector.
	Leadwerks::Vec3								m_vUp;																	// The game objects current up vector.
	Leadwerks::Vec3								m_vVelocity;															// The game object's current velocity.

	Leadwerks::Vec3								m_vCameraForward;														// The camera's current forward vector.
	Leadwerks::Vec3								m_vCameraRight;															// The camera's current right vector.
	Leadwerks::Vec3								m_vCameraUp;															// The camera's current up vector.

}; // end class GameObject.

#endif // _GAMEOBJECT_H_