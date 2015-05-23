#ifndef _CAMERAMANAGER_H_
	#define _CAMERAMANAGER_H_

#pragma once
#include "Leadwerks.h"

enum class CamBehavior { FIRST_PERSON, THIRD_PERSON, FLIGHT, CAMERA_NOT_INITIALIZED };
class GameObject;

class CameraManager {
public:
													CameraManager(Leadwerks::Window* pWindow, Leadwerks::Context* pContext,					// CameraManager constructor.
																  Leadwerks::World* pWorld, Leadwerks::Camera* pCamera);
													~CameraManager();																		// CameraManager destructor.

	void											Update(float deltaTime);																// CameraManager Update.
	void											Render();																				// CameraManager 3D-renderer.
	void											Draw();																					// CameraManager 2D-renderer.

	CamBehavior										CameraBehavior();																		// Gets the camera's current behavior.
	Leadwerks::Camera*								GetCamera();																			// Gets the CameraManager's camera handle.
	GameObject&										Target();																				// Gets the CameraManager's target handle.

	void											SetBehavior(CamBehavior behavior);														// Sets the camera's behavior.
	void											SetTarget(GameObject* pObject);															// Sets the CameraManager's target.
	void											SetWindow(Leadwerks::Window* pWindow);													// Sets the CameraManager's window handle.
	void											SetContext(Leadwerks::Context* pContext);												// Sets the CameraManager's context handle.
	void											SetWorld(Leadwerks::World* pWorld);														// Sets the CameraManager's world handle.
	void											SetCamera(Leadwerks::Camera* pCamera);													// Sets the CameraManager's camera handle.

	Leadwerks::Vec3									MinOffset();																			// Gets the minimum offset distance.
	Leadwerks::Vec3									MaxOffset();																			// Gets the maximum offset distance.

	float											MinAngle();																				// Gets the minimum angle clamp.
	float											MaxAngle();																				// Gets the maximum angle clamp.

	float											MoveSpeed();																			// Gets the forward and backward, movement speed.
	float											StrafeSpeed();																			// Gets the side to side, movement speed.
	float											VertSpeed();																			// Gets the up and down, movement speed.

	void											SetMoveSpeed(float nSpeed);																// Sets the camera's move speed.
	void											SetStrafeSpeed(float nSpeed);															// Sets the camera's strafe speed.
	void											SetVertSpeed(float nSpeed);																// Sets the camera's vert-move speed.

	void											SetMinOffset(Leadwerks::Vec3 vMin);														// Sets the camera's minimum offset, from the target.
	void											SetMaxOffset(Leadwerks::Vec3 vMax);														// Sets the camera's maximum offset, from the target.

	void											SetMinAngle(float nAngle);																// Sets the camera's minimum clamping angle.
	void											SetMaxAngle(float nAngle);																// Sets the camera's maximum clamping angle.

	Leadwerks::Vec3									Forward();																				// Gets the camera's current forward vector.
	Leadwerks::Vec3									Right();																				// Gets the camera's current right vector.
	Leadwerks::Vec3									Up();																					// Gets the camera's current up vector.
	Leadwerks::Vec3									Velocity();																				// Gets the camera's current velocity.

	float											Pitch();																				// Gets the camera's current pitch.
	float											Yaw();																					// Gets the camera's current yaw.
	float											Roll();																					// Gets the camera's current roll.
protected:
	void											Shutdown();																				// Performs any shutdown logic required by the camera manager.

	Leadwerks::Window&								GetWindow();																			// Gets the window handle.
	Leadwerks::Context&								GetContext();																			// Gets the context handle.
	Leadwerks::World&								GetWorld();																				// Gets the world handle.

private:
	void											CalcForwardVector(float pitch, float yaw);												// Calculates the forward vector, from the camera.
	void											CalcRightVector(float pitch, float yaw);												// Calculates the right vector, from the camera.
	void											CalcUpVector(float pitch, float yaw);													// Calculates the up vector, from the camera.
	void											CalcVelocity();																			// Calculates the velocity, for the camera.

	Leadwerks::Window*								m_pWindow;																				// CameraManager's window handle.
	Leadwerks::Context*								m_pContext;																				// CameraManager's context handle.
	Leadwerks::World*								m_pWorld;																				// CameraManager's world handle.

	GameObject*										m_pCamera;
	GameObject*										m_pTarget;																				// CameraManager's target handle.
	CamBehavior										m_behavior;																				// Indicates the current behavior the camera is following.

	Leadwerks::Vec3									m_vOffset;																				// The default, max-offset for the camera.
	Leadwerks::Vec3									m_vMinOffset;																			// The default, min-offset to the camera, before switching to a first-person view.
	
	bool											m_bClampViewingAngles;																	// Indicates whether the yaw viewing-angles should be clamped.
	float											m_nMinAngleClamp;																		// Min-angle clamp.
	float											m_nMaxAngleClamp;																		// Max-angle clamp.

}; // end class CameraManager.

#endif	// _CAMERAMANAGER_H_