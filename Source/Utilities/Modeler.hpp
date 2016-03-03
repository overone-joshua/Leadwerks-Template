/*-------------------------------------------------------
                    <copyright>
    
    File: Modeler.hpp
    Language: C++
    
    (C) Copyright Eden Softworks
    
    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net
    
    Description: Header file for Modeler utility.
                 The Modeler class provides a class
                 interface to easily inject density val
                 into a VoxelBuffer.
    
    Functions: 1. void Assign(VocelBuffer<T>& pBuffer);
    
               2. void AssInput(ModelerInput<T> input);
               
               3. void Execute(void);
               
               4. void ClearInputs(void);

---------------------------------------------------------*/

#ifndef _MODELER_H_
	#define _MODELER_H_

#pragma once
#include "Leadwerks.h"

#include "VoxelBuffer.hpp"

#include <queue>

template <typename T>
struct ModelerInput
{
public:
	int pt[3];
	T val;
	Leadwerks::Material* mat;
};

template <typename T>
class Modeler
{
public:
	Modeler(void) : m_pBuffer(nullptr) { ClearInputs(); }
	~Modeler(void) { ClearInputs(); m_pBuffer = nullptr; }

	void Assign(VoxelBuffer<T>& pBuffer);

	void AddInput(ModelerInput<T> input);
	void Execute(void);

	void ClearInputs(void);

protected:

private:
	std::queue<ModelerInput<T>> m_inputs;
	VoxelBuffer<T>* m_pBuffer;

};

/* Adds the given modeler input object to the internal collection of inputs. */ 
template <typename T>
void Modeler<T>::AddInput(ModelerInput<T> input)
{
	m_inputs.push(input);
}

/* Attaches the given buffer to the modeler. */
template <typename T>
void Modeler<T>::Assign(VoxelBuffer<T>& pBuffer)
{
	m_pBuffer = &pBuffer;
}

/* Injects the values of each added modeler input into the attached buffer. */
template <typename T>
void Modeler<T>::Execute()
{
	while (!m_inputs.empty()) {
		Leadwerks::Vec3 pos = Leadwerks::Vec3(m_inputs.front().pt[0], m_inputs.front().pt[1], m_inputs.front().pt[2]);
		T val = m_inputs.front().val;
		Leadwerks::Material* pMat = m_inputs.front().mat;

		m_pBuffer->Set(pos.x, pos.y, pos.z, val);
		m_inputs.pop();
	}

}

/* Clears any existing modeler input from the input collection*/
template <typename T>
void Modeler<T>::ClearInputs()
{
	std::queue<ModelerInput<T>> empty;
	std::swap(m_inputs, empty);

}

#endif // _MODELER_H_