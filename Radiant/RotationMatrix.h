#pragma once

#include "Matrix.h"

namespace Radiant
{
	struct RotationMatrix : public Matrix
	{
		__forceinline RotationMatrix(const Quaternion &Rotation, const Vector3 &Origin = Vector3::Zero)
		{
			const float X2 = Rotation.X + Rotation.X;	const float Y2 = Rotation.Y + Rotation.Y;	const float Z2 = Rotation.Z + Rotation.Z;
			const float XX = Rotation.X * X2;			const float XY = Rotation.X * Y2;			const float XZ = Rotation.X * Z2;
			const float YY = Rotation.Y * Y2;			const float YZ = Rotation.Y * Z2;			const float ZZ = Rotation.Z * Z2;
			const float WX = Rotation.W * X2;			const float WY = Rotation.W * Y2;			const float WZ = Rotation.W * Z2;

			M[0][0] = 1.0f - (YY + ZZ);	M[0][1] = XY + WZ;			M[0][2] = XZ - WY;			M[0][3] = 0.0f;
			M[1][0] = XY - WZ;			M[1][1] = 1.0f - (XX + ZZ);	M[1][2] = YZ + WX;			M[1][3] = 0.0f;
			M[2][0] = XZ + WY;			M[2][1] = YZ - WX;			M[2][2] = 1.0f - (XX + YY);	M[2][3] = 0.0f;
			M[3][0] = Origin.X;			M[3][1] = Origin.Y;			M[3][2] = Origin.Z;			M[3][3] = 1.0f;
		}
	};
}
