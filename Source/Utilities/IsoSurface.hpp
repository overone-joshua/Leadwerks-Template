#ifndef _ISOSURFACE_H_
	#define _ISOSURFACE_H_

#pragma once
#include "Leadwerks.h"
#include <vector>
#include <map>

struct TRIANGLE {
	unsigned int vertID[3];
};

typedef std::map<unsigned, Leadwerks::Vec3> ID2VEC3;
typedef std::vector<TRIANGLE> TRIANGLEVECTOR;

template <typename T>
class IsoSurface {
public:
	IsoSurface();
	~IsoSurface();

	int GenerateSurface(Leadwerks::Model& pModel, const T* pScalarField, T nIsoLevel, int nCellsX, int nCellsY, int nCellsZ, float nCellWidth, float nCellHeight, float nCellDepth);	

	void DeleteSurface();

	bool IsSurfaceValid() { return m_bIsValidSurface; }

protected:

private:
	unsigned GetEdgeID(unsigned int nX, unsigned int nY, unsigned int nZ, unsigned int nEdgeNo);
	unsigned GetVertexID(unsigned int nX, unsigned int nY, unsigned int nZ);
	Leadwerks::Vec3 CalculateIntersection(unsigned int nX, unsigned int nY, unsigned int nZ, unsigned int nEdgeNo);
	Leadwerks::Vec3 Interpolate(float fX1, float fY1, float fZ1, float fX2, float fY2, float fZ2, T tVal1, T tVal2);
	void GenerateLeadwerksSurface(Leadwerks::Model& pModel);

	float m_nCellWidth;
	float m_nCellDepth;
	float m_nCellHeight;

	float m_nCellsX;
	float m_nCellsY;
	float m_nCellsZ;

	ID2VEC3 m_vertexIDs;
	TRIANGLEVECTOR m_triangles;

	T m_nIsoLevel;
	const T* m_pScalarField;

	bool m_bIsValidSurface;

	static const unsigned int EdgeTable[256];
	static const unsigned int TriTable[256][16];
};

#endif // _ISOSURFACE_H_