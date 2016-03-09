/*-------------------------------------------------------
                    <copyright>
    
    File: Camera.hpp
    Language: C++
    
    (C) Copyright Eden Softworks
    
    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net
    
    Description: Header file for Camera component.

---------------------------------------------------------*/

#ifndef _CAMERA_COMPONENT_HPP_
	#define _CAMERA_COMPONENT_HPP_

#pragma once
#include "../Utilities/CameraHandle.hpp"
#include "../Utilities/Macros.hpp"

#include "../Services/ScriptController.hpp"

#include "Component.hpp"

#include <Sqrat.h>
#include <Sqrat/sqext.h>

#include <string>

namespace Components
{
	/** A Camera component.
	 *  The Camera component provides access to a CameraHandle
	 *  object which wraps the Leadwerks::Camera object.
	 */
	typedef struct Camera : public Component
	{
		CLASS_TYPE(Camera);

		CameraHandle*                 pCamHndl;		/*!< A CameraHandle object. */

		/** The Camera component constructor. */
		Camera(CameraHandle* _pCamHndl = nullptr, std::string cName = "") 
			: pCamHndl(_pCamHndl), Component(cName) { }

		static void Bind(void)
		{
			using namespace Sqrat;

			auto ComponentsTable = ScriptController::GetTable("Components");

			ComponentsTable->Bind("Camera", Class<Camera, sqext::ConstAlloc<Camera, CameraHandle*, std::string>>()
				.Var("pCamHndl", &Camera::pCamHndl)
			);

		}

	} Camera; // < end struct.

} // < end namespace.

#endif _CAMERA_COMPONENT_HPP_