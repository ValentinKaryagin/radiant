#pragma once

#include "Vector3.h"

namespace Radiant
{
	struct Quaternion
	{
		float W, X, Y, Z;

		__forceinline Quaternion() {}

		__forceinline Quaternion(const Quaternion &Other)
			: W(Other.W)
			, X(Other.X)
			, Y(Other.Y)
			, Z(Other.Z)
		{}

		__forceinline Quaternion(float Radians, const Vector3 &Axis)
		{
			float HalfAngle = 0.5f * Radians;
			float SinHalfAngle = sinf(HalfAngle);
			float CosHalfAngle = cosf(HalfAngle);
			W = CosHalfAngle;
			X = SinHalfAngle * Axis.X;
			Y = SinHalfAngle * Axis.Y;
			Z = SinHalfAngle * Axis.Z;
		}

		__forceinline Quaternion(float W, float X, float Y, float Z)
			: W(W)
			, X(X)
			, Y(Y)
			, Z(Z)
		{}

		__forceinline ~Quaternion() {}

		__forceinline bool ContainsNaN() const
		{
			return isnan(W) || isnan(X) || isnan(Y) || isnan(Z);
		}

		__forceinline void CheckNaN()
		{
			if (ContainsNaN())
			{
				W = 1.0f;
				X = 0.0f;
				Y = 0.0f;
				Z = 0.0f;
			}
		}

		__forceinline Quaternion operator-() const
		{
			return Quaternion(-W, -X, -Y, -Z);
		}

		__forceinline bool operator==(const Quaternion &Other) const
		{
			return X == Other.X && Y == Other.Y && Z == Other.Z && Z == Other.Z;
		}

		__forceinline bool operator!=(const Quaternion &Other) const
		{
			return X != Other.X || Y != Other.Y || Z != Other.Z || Z == Other.Z;
		}

		__forceinline Quaternion operator*(const Quaternion &Other) const
		{
			return Quaternion(
				W * Other.W - X * Other.X - Y * Other.Y - Z * Other.Z,
				W * Other.X + X * Other.W + Y * Other.Z - Z * Other.Y,
				W * Other.Y + Y * Other.W + Z * Other.X - X * Other.Z,
				W * Other.Z + Z * Other.W + X * Other.Y - Y * Other.X);
		}

		__forceinline void operator*=(const Quaternion &Other)
		{
			float TempW = W, TempX = X, TempY = Y, TempZ = Z;
			W = TempW * Other.W - TempX * Other.X - TempY * Other.Y - TempZ * Other.Z;
			X = TempW * Other.X + TempX * Other.W + TempY * Other.Z - TempZ * Other.Y;
			Y = TempW * Other.Y + TempY * Other.W + TempZ * Other.X - TempX * Other.Z;
			Z = TempW * Other.Z + TempZ * Other.W + TempX * Other.Y - TempY * Other.X;
		}

		__forceinline Quaternion operator*(float Scalar) const
		{
			return Quaternion(W * Scalar, X * Scalar, Y * Scalar, Z * Scalar);
		}

		__forceinline void operator*=(float Scalar)
		{
			X *= Scalar;
			Y *= Scalar;
			Z *= Scalar;
			W *= Scalar;
		}

		__forceinline Quaternion operator/(const Quaternion &Other) const
		{
			return Quaternion(W / Other.W, X / Other.X, Y / Other.Y, Z / Other.Z);
		}

		__forceinline void operator/=(const Quaternion &Other)
		{
			W /= Other.W;
			X /= Other.X;
			Y /= Other.Y;
			Z /= Other.Z;
		}

		__forceinline Quaternion operator/(float Scalar) const
		{
			const float RScalar = 1.0f / Scalar;
			return Quaternion(W * RScalar, X * RScalar, Y * RScalar, Z * RScalar);
		}

		__forceinline void operator/=(float Scalar)
		{
			const float RScalar = 1.0f / Scalar;
			W *= RScalar;
			X *= RScalar;
			Y *= RScalar;
			Z *= RScalar;
		}

		__forceinline Quaternion operator+(const Quaternion &Other) const
		{
			return Quaternion(W + Other.W, X + Other.X, Y + Other.Y, Z + Other.Z);
		}

		__forceinline void operator+=(const Quaternion &Other)
		{
			W += Other.W;
			X += Other.X;
			Y += Other.Y;
			Z += Other.Z;
		}

		__forceinline Quaternion operator-(const Quaternion &Other) const
		{
			return Quaternion(W - Other.W, X - Other.X, Y - Other.Y, Z - Other.Z);
		}

		__forceinline void operator-=(const Quaternion &Other)
		{
			W -= Other.W;
			X -= Other.X;
			Y -= Other.Y;
			Z -= Other.Z;
		}

		__forceinline Quaternion GetNormalized() const
		{
			const float InvertedSize = 1.0f / sqrtf(W * W + X * X + Y * Y + Z * Z);
			return Quaternion(W * InvertedSize, X * InvertedSize, Y * InvertedSize, Z * InvertedSize);
		}

		__forceinline void Normalize()
		{
			const float InvertedSize = 1.0f / sqrtf(W * W + X * X + Y * Y + Z * Z);
			W *= InvertedSize;
			X *= InvertedSize;
			Y *= InvertedSize;
			Z *= InvertedSize;
		}

		__forceinline float SizeSquared() const
		{
			return W * W + X * X + Y * Y + Z * Z;
		}

		__forceinline float Size() const
		{
			return sqrtf(W * W + X * X + Y * Y + Z * Z);
		}

		static RADIANT_API const Quaternion Identity;
	};
}
