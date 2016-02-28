#ifndef _CAMERA_COMPONENT_HPP_
	#define _CAMERA_COMPONENT_HPP_

#pragma once
#include "../Utilities/CameraHandle.hpp"
#include "../Utilities/Macros.hpp"

#include "Component.hpp"

#include <string>

namespace Components
{
	typedef struct Camera : public Component
	{
		CLASS_TYPE(Camera);

		CameraHandle* pCamHndl; //!<Camera Handle>//

		Camera(CameraHandle* _pCamHndl = nullptr, std::string cName = "")
			: pCamHndl(_pCamHndl), Component(cName) { }

	} Camera; // < end struct.

} // < end namespace.

#endif _CAMERA_COMPONENT_HPP_