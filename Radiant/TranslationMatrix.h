#pragma once

#include "Matrix.h"

namespace Radiant
{
	struct TranslationMatrix : public Matrix
	{
		__forceinline TranslationMatrix(const Vector3 &Translation)
		{
			M[0][0] = 1.0f;				M[0][1] = 0.0f;				M[0][2] = 0.0f;				M[0][3] = 0.0f;
			M[1][0] = 0.0f;				M[1][1] = 1.0f;				M[1][2] = 0.0f;				M[1][3] = 0.0f;
			M[2][0] = 0.0f;				M[2][1] = 0.0f;				M[2][2] = 1.0f;				M[2][3] = 0.0f;
			M[3][0] = Translation.X;	M[3][1] = Translation.Y;	M[3][2] = Translation.Z;	M[3][3] = 1.0f;
		}
	};
}
