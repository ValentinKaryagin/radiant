#pragma once

#include "Vector2.h"

namespace Radiant
{
	struct Vector3
	{
		float X, Y, Z;

		__forceinline Vector3() {}

		inline Vector3(const Vector3 &Other)
			: X(Other.X)
			, Y(Other.Y)
			, Z(Other.Z)
		{}

		__forceinline Vector3(const Vector2 &V, float Z = 0.0f)
			: X(V.X)
			, Y(V.Y)
			, Z(Z)
		{}

		__forceinline Vector3(float X, float Y, float Z)
			: X(X)
			, Y(Y)
			, Z(Z)
		{}

		__forceinline ~Vector3() {}

		__forceinline bool ContainsNaN() const
		{
			return isnan(X) || isnan(Y) || isnan(Z);
		}

		__forceinline void CheckNaN()
		{
			if (ContainsNaN())
			{
				X = 0.0f;
				Y = 0.0f;
				Z = 0.0f;
			}
		}

		__forceinline Vector3 operator-() const
		{
			return Vector3(-X, -Y, -Z);
		}

		__forceinline Vector3 & operator=(const Vector3 &Other)
		{
			if (this != &Other)
			{
				X = Other.X;
				Y = Other.Y;
				Z = Other.Z;
			}
			return *this;
		}

		__forceinline bool operator==(const Vector3 &Other) const
		{
			return X == Other.X && Y == Other.Y && Z == Other.Z;
		}

		__forceinline bool operator!=(const Vector3 &Other) const
		{
			return X != Other.X || Y != Other.Y || Z != Other.Z;
		}

		__forceinline Vector3 operator*(const Vector3 &Other) const
		{
			return Vector3(X * Other.X, Y * Other.Y, Z * Other.Z);
		}

		__forceinline void operator*=(const Vector3 &Other)
		{
			X *= Other.X;
			Y *= Other.Y;
			Z *= Other.Z;
		}

		__forceinline Vector3 operator*(float Scalar) const
		{
			return Vector3(X * Scalar, Y * Scalar, Z * Scalar);
		}

		__forceinline void operator*=(float Scalar)
		{
			X *= Scalar;
			Y *= Scalar;
			Z *= Scalar;
		}

		__forceinline Vector3 operator/(const Vector3 &Other) const
		{
			return Vector3(X / Other.X, Y / Other.Y, Z / Other.Z);
		}

		__forceinline void operator/=(const Vector3 &Other)
		{
			X /= Other.X;
			Y /= Other.Y;
			Z /= Other.Z;
		}

		__forceinline Vector3 operator/(float Scalar) const
		{
			const float RScalar = 1.0f / Scalar;
			return Vector3(X * RScalar, Y * RScalar, Z * RScalar);
		}

		__forceinline void operator/=(float Scalar)
		{
			const float RScalar = 1.0f / Scalar;
			X *= RScalar;
			Y *= RScalar;
			Z *= RScalar;
		}

		__forceinline Vector3 operator+(const Vector3 &Other) const
		{
			return Vector3(X + Other.X, Y + Other.Y, Z + Other.Z);
		}

		__forceinline void operator+=(const Vector3 &Other)
		{
			X += Other.X;
			Y += Other.Y;
			Z += Other.Z;
		}

		__forceinline Vector3 operator+(float Scalar) const
		{
			return Vector3(X + Scalar, Y + Scalar, Z + Scalar);
		}

		__forceinline void operator+=(float Scalar)
		{
			X += Scalar;
			Y += Scalar;
			Z += Scalar;
		}

		__forceinline Vector3 operator-(const Vector3 &Other) const
		{
			return Vector3(X - Other.X, Y - Other.Y, Z - Other.Z);
		}

		__forceinline void operator-=(const Vector3 &Other)
		{
			X -= Other.X;
			Y -= Other.Y;
			Z -= Other.Z;
		}

		__forceinline Vector3 operator-(float Scalar) const
		{
			return Vector3(X - Scalar, Y - Scalar, Z - Scalar);
		}

		__forceinline void operator-=(float Scalar)
		{
			X -= Scalar;
			Y -= Scalar;
			Z -= Scalar;
		}

		__forceinline Vector3 operator^(const Vector3 &Other) const
		{
			return Vector3(Y * Other.Z - Z * Other.Y, Z * Other.X - X * Other.Z, X * Other.Y - Y * Other.X);
		}

		__forceinline float operator|(const Vector3 &Other) const
		{
			return X * Other.X + Y * Other.Y + Z * Other.Z;
		}

		__forceinline Vector3 GetNormalized() const
		{
			const float InvertedSize = 1.0f / sqrtf(X * X + Y * Y + Z * Z);
			return Vector3(X * InvertedSize, Y * InvertedSize, Z * InvertedSize);
		}

		__forceinline void Normalize()
		{
			const float InvertedSize = 1.0f / sqrtf(X * X + Y * Y + Z * Z);
			X *= InvertedSize;
			Y *= InvertedSize;
			Z *= InvertedSize;
		}

		__forceinline float SizeSquared() const
		{
			return X * X + Y * Y + Z * Z;
		}

		__forceinline float Size() const
		{
			return sqrtf(X * X + Y * Y + Z * Z);
		}

		__forceinline static Vector3 CrossProduct(const Vector3 &V1, const Vector3 &V2)
		{
			return V1 ^ V2;
		}	

		__forceinline static float DotProduct(const Vector3 &V1, const Vector3 &V2)
		{
			return V1 | V2;
		}

		__forceinline static float DistanceSquared(const Vector3 &V1, const Vector3 &V2)
		{
			const float VX = V2.X - V1.X;
			const float VY = V2.Y - V1.Y;
			const float VZ = V2.Z - V1.Z;
			return VX * VX + VY * VY + VZ * VZ;
		}

		__forceinline static float Distance(const Vector3 &V1, const Vector3 &V2)
		{
			const float VX = V2.X - V1.X;
			const float VY = V2.Y - V1.Y;
			const float VZ = V2.Z - V1.Z;
			return sqrtf(VX * VX + VY * VY + VZ * VZ);
		}

		static RADIANT_API const Vector3 Zero;
		static RADIANT_API const Vector3 Forward;
		static RADIANT_API const Vector3 Right;
		static RADIANT_API const Vector3 Up;
		static RADIANT_API const Vector3 Identity;
	};
}
