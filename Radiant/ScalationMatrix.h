#pragma once

#include "Matrix.h"

namespace Radiant
{
	struct ScalationMatrix : public Matrix
	{
		__forceinline ScalationMatrix(const Vector3 &Scalation)
		{
			M[0][0] = Scalation.X;	M[0][1] = 0.0f;			M[0][2] = 0.0f;			M[0][3] = 0.0f;
			M[1][0] = 0.0f;			M[1][1] = Scalation.Y;	M[1][2] = 0.0f;			M[1][3] = 0.0f;
			M[2][0] = 0.0f;			M[2][1] = 0.0f;			M[2][2] = Scalation.Z;	M[2][3] = 0.0f;
			M[3][0] = 0.0f;			M[3][1] = 0.0f;			M[3][2] = 0.0f;			M[3][3] = 1.0f;
		}

		__forceinline ScalationMatrix(float Scalation)
		{
			M[0][0] = Scalation;	M[0][1] = 0.0f;			M[0][2] = 0.0f;			M[0][3] = 0.0f;
			M[1][0] = 0.0f;			M[1][1] = Scalation;	M[1][2] = 0.0f;			M[1][3] = 0.0f;
			M[2][0] = 0.0f;			M[2][1] = 0.0f;			M[2][2] = Scalation;	M[2][3] = 0.0f;
			M[3][0] = 0.0f;			M[3][1] = 0.0f;			M[3][2] = 0.0f;			M[3][3] = 1.0f;
		}
	};
}
