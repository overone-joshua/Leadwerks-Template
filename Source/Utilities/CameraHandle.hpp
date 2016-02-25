#ifndef _CAMERA_HANDLE_HPP_
	#define _CAMERA_HANDLE_HPP_

#pragma once
#include "Leadwerks.h"
#include "Macros.hpp"

class CameraHandle {

	CLASS_TYPE(Camera);

public:

	CameraHandle(Leadwerks::Camera* pCamera) 
		:m_pCamera(pCamera){

	}

	~CameraHandle(void) {

		SAFE_RELEASE(m_pCamera);
		SAFE_DELETE(m_pCamera);

	}

	Leadwerks::Camera* getInst(void) { return m_pCamera; }

private:

	Leadwerks::Camera* m_pCamera;

}; // < end class.

#endif _CAMERA_HANDLE_HPP_