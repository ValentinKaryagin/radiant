#pragma once

#include "Matrix.h"

namespace Radiant
{
	struct LookAtMatrix : public Matrix
	{
		__forceinline LookAtMatrix(const Vector3 &From, const Vector3 &At, const Vector3 &UpDirection = Vector3::Up)
		{
			const Vector3 ZAxis = (At - From).GetNormalized();
			const Vector3 XAxis = (UpDirection ^ ZAxis).GetNormalized();
			const Vector3 YAxis = ZAxis ^ XAxis;

			M[0][0] = XAxis.X;			M[0][1] = YAxis.X;			M[0][2] = ZAxis.X;			M[0][3] = 0.0f;
			M[1][0] = XAxis.Y;			M[1][1] = YAxis.Y;			M[1][2] = ZAxis.Y;			M[1][3] = 0.0f;
			M[2][0] = XAxis.Z;			M[2][1] = YAxis.Z;			M[2][2] = ZAxis.Z;			M[2][3] = 0.0f;
			M[3][0] = -(XAxis | From);	M[3][1] = -(YAxis | From);	M[3][2] = -(ZAxis | From);	M[3][3] = 1.0f;
		}
	};
}
