#ifndef _MATH_HPP_
	#define _MATH_HPP_

#pragma once
#include "Leadwerks.h"

namespace Math
{

	static Leadwerks::Mat4* MatrixRotationX(Leadwerks::Mat4* pOut, float angle)
	{
		pOut->MakeIdentity();

		pOut[1][1] = Leadwerks::Math::Cos(angle);
		pOut[2][2] = Leadwerks::Math::Cos(angle);
		pOut[1][2] = Leadwerks::Math::Sin(angle);
		pOut[2][1] = -Leadwerks::Math::Sin(angle);

		return pOut;
	}

	static Leadwerks::Mat4* MatrixRotationY(Leadwerks::Mat4* pOut, float angle)
	{
		pOut->MakeIdentity();

		pOut[0][0] = Leadwerks::Math::Cos(angle);
		pOut[2][2] = Leadwerks::Math::Cos(angle);
		pOut[0][2] = -Leadwerks::Math::Sin(angle);
		pOut[2][0] = Leadwerks::Math::Sin(angle);

		return pOut;
	}

	static Leadwerks::Mat4* MatrixRotationZ(Leadwerks::Mat4* pOut, float angle)
	{
		pOut->MakeIdentity();

		pOut[0][0] = Leadwerks::Math::Cos(angle);
		pOut[1][1] = Leadwerks::Math::Cos(angle);
		pOut[0][1] = Leadwerks::Math::Sin(angle);
		pOut[1][0] = -Leadwerks::Math::Sin(angle);

		return pOut;
	}

    static Leadwerks::Mat4* MatrixTranslation(Leadwerks::Mat4* pOut, float x, float y, float z)
    {
        pOut->MakeIdentity();

        pOut[3][0] = x;
        pOut[3][1] = y;
        pOut[3][2] = z;

        return pOut;
    }

} // < end namespace.

#endif _MATH_HPP_