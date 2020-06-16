#pragma once

#include "Object.h"

namespace Radiant
{
	struct Vector2
	{
		float X, Y;

		inline Vector2(const Vector2 &Other)
			: X(Other.X)
			, Y(Other.Y)
		{}

		__forceinline Vector2(float X, float Y)
			: X(X)
			, Y(Y)
		{}

		__forceinline ~Vector2() {}

		__forceinline bool ContainsNaN() const
		{
			return isnan(X) || isnan(Y);
		}

		__forceinline void CheckNaN()
		{
			if (ContainsNaN())
			{
				X = 0.0f;
				Y = 0.0f;
			}
		}

		__forceinline Vector2 operator-() const
		{
			return Vector2(-X, -Y);
		}

		__forceinline Vector2 & operator=(const Vector2 &Other)
		{
			if (this != &Other)
			{
				X = Other.X;
				Y = Other.Y;
			}
			return *this;
		}

		__forceinline bool operator==(const Vector2 &Other) const
		{
			return X == Other.X && Y == Other.Y;
		}

		__forceinline bool operator!=(const Vector2 &Other) const
		{
			return X != Other.X || Y != Other.Y;
		}

		__forceinline Vector2 operator*(const Vector2 &Other) const
		{
			return Vector2(X * Other.X, Y * Other.Y);
		}

		__forceinline void operator*=(const Vector2 &Other)
		{
			X *= Other.X;
			Y *= Other.Y;
		}

		__forceinline Vector2 operator*(float Scalar) const
		{
			return Vector2(X * Scalar, Y * Scalar);
		}

		__forceinline void operator*=(float Scalar)
		{
			X *= Scalar;
			Y *= Scalar;
		}

		__forceinline Vector2 operator/(const Vector2 &Other) const
		{
			return Vector2(X / Other.X, Y / Other.Y);
		}

		__forceinline void operator/=(const Vector2 &Other)
		{
			X /= Other.X;
			Y /= Other.Y;
		}

		__forceinline Vector2 operator/(float Scalar) const
		{
			const float RScalar = 1.0f / Scalar;
			return Vector2(X * RScalar, Y * RScalar);
		}

		__forceinline void operator/=(float Scalar)
		{
			const float RScalar = 1.0f / Scalar;
			X *= RScalar;
			Y *= RScalar;
		}

		__forceinline Vector2 operator+(const Vector2 &Other) const
		{
			return Vector2(X + Other.X, Y + Other.Y);
		}

		__forceinline void operator+=(const Vector2 &Other)
		{
			X += Other.X;
			Y += Other.Y;
		}

		__forceinline Vector2 operator+(float Scalar) const
		{
			return Vector2(X + Scalar, Y + Scalar);
		}

		__forceinline void operator+=(float Scalar)
		{
			X += Scalar;
			Y += Scalar;
		}

		__forceinline Vector2 operator-(const Vector2 &Other) const
		{
			return Vector2(X - Other.X, Y - Other.Y);
		}

		__forceinline void operator-=(const Vector2 &Other)
		{
			X -= Other.X;
			Y -= Other.Y;
		}

		__forceinline Vector2 operator-(float Scalar) const
		{
			return Vector2(X - Scalar, Y - Scalar);
		}

		__forceinline void operator-=(float Scalar)
		{
			X -= Scalar;
			Y -= Scalar;
		}

		__forceinline float operator^(const Vector2 &Other) const
		{
			return X * Other.Y - Y * Other.X;
		}

		__forceinline float operator|(const Vector2 &Other) const
		{
			return X * Other.X + Y * Other.Y;
		}

		__forceinline Vector2 GetNormalized() const
		{
			const float InvertedSize = 1.0f / sqrtf(X * X + Y * Y);
			return Vector2(X * InvertedSize, Y * InvertedSize);
		}

		__forceinline void Normalize()
		{
			const float InvertedSize = 1.0f / sqrtf(X * X + Y * Y);
			X *= InvertedSize;
			Y *= InvertedSize;
		}

		__forceinline float SizeSquared() const
		{
			return X * X + Y * Y;
		}

		__forceinline float Size() const
		{
			return sqrtf(X * X + Y * Y);
		}

		__forceinline static float CrossProduct(const Vector2 &V1, const Vector2 &V2)
		{
			return V1 ^ V2;
		}

		__forceinline static float DotProduct(const Vector2 &V1, const Vector2 &V2)
		{
			return V1 | V2;
		}

		__forceinline static float DistanceSquared(const Vector2 &V1, const Vector2 &V2)
		{
			const float VX = V2.X - V1.X;
			const float VY = V2.Y - V1.Y;
			return VX * VX + VY * VY;
		}

		__forceinline static float Distance(const Vector2 &V1, const Vector2 &V2)
		{
			const float VX = V2.X - V1.X;
			const float VY = V2.Y - V1.Y;
			return sqrtf(VX * VX + VY * VY);
		}

		static RADIANT_API const Vector2 Zero;
		static RADIANT_API const Vector2 Identity;
	};
}
