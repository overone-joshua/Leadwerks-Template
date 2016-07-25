/*-------------------------------------------------------
                    <copyright>
    
    File: VoxelBuffer.hpp
    Language: C++
    
    (C) Copyright Eden Softworks
    
    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net
    
    Description: Header file for VoxelBuffer utility.
                 The VoxelBuffer class provides a 
                 three-dimensional array in which to 
                 easily get or set identity values.
                 
    
    Functions: 1. T Get(int i, int j, int k);
    
               2. T Get(int index);
               
               3. void Set(int i, int j, int k, T val);
               
               4. void Set(int index, T val);
               
               5. void Load(const char* filename);
               
               6. void Save(const char* filename);

---------------------------------------------------------*/

#ifndef _VOXEL_BUFFER_H
    #define _VOXEL_BUFFER_H_

#pragma once
#include <vector>

template <typename T>
struct VoxelBuffer {
public:
	VoxelBuffer(int nSizeX, int nSizeY, int nSizeZ)
		: m_nSizeX(nSizeX), m_nSizeY(nSizeY), m_nSizeZ(nSizeZ)
    {

		m_data.resize(nSizeX * nSizeY * nSizeZ);
	}

	~VoxelBuffer() { m_data.clear(); }

	T Get(int i, int j, int k)
    {
		return m_data[Index(i, j, k)];
	}

	T Get(int index)
    {
		return m_data[index];
	}

	void Set(int i, int j, int k, T val)
    {
		m_data[Index(i, j, k)] = val;
	}

	void Set(int index, T val)
    {
		m_data[index] = val;
	}

	void Load(const char* filename)
    {
		std::ifstream in(filename);
		in >> m_nSizeX >> m_nSizeY >> m_nSizeZ;
		std::copy(std::istream_iterator<T>(in),
			std::istream_iterator<T>(),
			std::back_inserter(m_data));
	}

	void Save(const char* filename)
    {
		std::ofstream out(filename);
		out << m_nSizeX << " " << m_nSizeY << " " << m_nSizeZ << std::endl;
		std::copy(m_data.begin(), m_data.end(), std::ostream_iterator<T>(out, "\n"));

	}

    int size(void) { return this->m_data.size(); }

    int width(void) { return this->m_nSizeX; }

    int height(void) { return this->m_nSizeY; }

    int depth(void) { return this->m_nSizeZ; }

	operator T*()
    {
		return &m_data[0];
	}

protected:

private:
	int Index(int i, int j, int k)
    {
		return i + j * m_nSizeX + k * m_nSizeX * m_nSizeY;
	}

	int m_nSizeX;
	int m_nSizeY;
	int m_nSizeZ;
	std::vector<T> m_data;

}; // end struct VoxelBuffer<T>

#endif // _VOXEL_BUFFER_H_