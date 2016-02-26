#ifndef _MODELER_H_
	#define _MODELER_H_

#pragma once
#include "Leadwerks.h"

#include "VoxelBuffer.hpp"

#include <queue>

template <typename T>
struct ModelerInput{
public:
	int pt[3];
	T val;
	Leadwerks::Material* mat;
};

template <typename T>
class Modeler {
public:
	Modeler();
	~Modeler();

	void Assign(VoxelBuffer<T>& pBuffer);

	void AddInput(ModelerInput<T> input);
	void Execute();

	void ClearInputs();

protected:

private:
	std::queue<ModelerInput<T>> m_inputs;
	VoxelBuffer<T>* m_pBuffer;

};

template <typename T>
Modeler<T>::Modeler()
	: m_pBuffer(nullptr) {

	ClearInputs();

}

template <typename T>
Modeler<T>::~Modeler() {
	ClearInputs();
	m_pBuffer = nullptr;
}

template <typename T>
void Modeler<T>::AddInput(ModelerInput<T> input) {
	m_inputs.push(input);
}

template <typename T>
void Modeler<T>::Assign(VoxelBuffer<T>& pBuffer) {
	m_pBuffer = &pBuffer;
}

template <typename T>
void Modeler<T>::Execute() {
	while (!m_inputs.empty()) {
		Leadwerks::Vec3 pos = Leadwerks::Vec3(m_inputs.front().pt[0], m_inputs.front().pt[1], m_inputs.front().pt[2]);
		T val = m_inputs.front().val;
		Leadwerks::Material* pMat = m_inputs.front().mat;

		m_pBuffer->Set(pos.x, pos.y, pos.z, val);
		m_inputs.pop();
	}

}

template <typename T>
void Modeler<T>::ClearInputs() {
	std::queue<ModelerInput<T>> empty;
	std::swap(m_inputs, empty);

}

#endif // _MODELER_H_