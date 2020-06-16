#pragma once

#include "Vector3.h"
#include "Quaternion.h"

namespace Radiant
{
	struct Matrix
	{
		float M[4][4];

		__forceinline Matrix() {}

		__forceinline Matrix(const Matrix &Other)
		{
			M[0][0] = Other.M[0][0]; M[0][1] = Other.M[0][1]; M[0][2] = Other.M[0][2]; M[0][3] = Other.M[0][3];
			M[1][0] = Other.M[1][0]; M[1][1] = Other.M[1][1]; M[1][2] = Other.M[1][2]; M[1][3] = Other.M[1][3];
			M[2][0] = Other.M[2][0]; M[2][1] = Other.M[2][1]; M[2][2] = Other.M[2][2]; M[2][3] = Other.M[2][3];
			M[3][0] = Other.M[3][0]; M[3][1] = Other.M[3][1]; M[3][2] = Other.M[3][2]; M[3][3] = Other.M[3][3];
		}

		__forceinline Matrix(
			float _00, float _01, float _02, float _03,
			float _10, float _11, float _12, float _13,
			float _20, float _21, float _22, float _23,
			float _30, float _31, float _32, float _33
			)
		{
			M[0][0] = _00; M[0][1] = _01; M[0][2] = _02; M[0][3] = _03;
			M[1][0] = _10; M[1][1] = _11; M[1][2] = _12; M[1][3] = _13;
			M[2][0] = _20; M[2][1] = _21; M[2][2] = _22; M[2][3] = _23;
			M[3][0] = _30; M[3][1] = _31; M[3][2] = _32; M[3][3] = _33;
		}

		__forceinline ~Matrix() {}

		__forceinline bool ContainsNaN() const
		{
			return
				isnan(M[0][0]) || isnan(M[0][1]) || isnan(M[0][2]) || isnan(M[0][3]) ||
				isnan(M[1][0]) || isnan(M[1][1]) || isnan(M[1][2]) || isnan(M[1][3]) ||
				isnan(M[2][0]) || isnan(M[2][1]) || isnan(M[2][2]) || isnan(M[2][3]) ||
				isnan(M[3][0]) || isnan(M[3][1]) || isnan(M[3][2]) || isnan(M[3][3]);
		}

		__forceinline void CheckNaN()
		{
			if (ContainsNaN())
			{
				M[0][0] = 1.0f; M[0][1] = 0.0f; M[0][2] = 0.0f; M[0][3] = 0.0f;
				M[1][0] = 0.0f; M[1][1] = 1.0f; M[1][2] = 0.0f; M[1][3] = 0.0f;
				M[2][0] = 0.0f; M[2][1] = 0.0f; M[2][2] = 1.0f; M[2][3] = 0.0f;
				M[3][0] = 0.0f; M[3][1] = 0.0f; M[3][2] = 0.0f; M[3][3] = 1.0f;
			}
		}

		__forceinline void SetIdentity()
		{
			M[0][0] = 1.0f; M[0][1] = 0.0f; M[0][2] = 0.0f; M[0][3] = 0.0f;
			M[1][0] = 0.0f; M[1][1] = 1.0f; M[1][2] = 0.0f; M[1][3] = 0.0f;
			M[2][0] = 0.0f; M[2][1] = 0.0f; M[2][2] = 1.0f; M[2][3] = 0.0f;
			M[3][0] = 0.0f; M[3][1] = 0.0f; M[3][2] = 0.0f; M[3][3] = 1.0f;
		}

		__forceinline Matrix GetInverted() const
		{
			Matrix Result;
			Matrix Temp;

			float Det[4];			

			Temp.M[0][0] = M[2][2] * M[3][3] - M[2][3] * M[3][2];
			Temp.M[0][1] = M[1][2] * M[3][3] - M[1][3] * M[3][2];
			Temp.M[0][2] = M[1][2] * M[2][3] - M[1][3] * M[2][2];

			Temp.M[1][0] = M[2][2] * M[3][3] - M[2][3] * M[3][2];
			Temp.M[1][1] = M[0][2] * M[3][3] - M[0][3] * M[3][2];
			Temp.M[1][2] = M[0][2] * M[2][3] - M[0][3] * M[2][2];

			Temp.M[2][0] = M[1][2] * M[3][3] - M[1][3] * M[3][2];
			Temp.M[2][1] = M[0][2] * M[3][3] - M[0][3] * M[3][2];
			Temp.M[2][2] = M[0][2] * M[1][3] - M[0][3] * M[1][2];

			Temp.M[3][0] = M[1][2] * M[2][3] - M[1][3] * M[2][2];
			Temp.M[3][1] = M[0][2] * M[2][3] - M[0][3] * M[2][2];
			Temp.M[3][2] = M[0][2] * M[1][3] - M[0][3] * M[1][2];

			Det[0] = M[1][1] * Temp.M[0][0] - M[2][1] * Temp.M[0][1] + M[3][1] * Temp.M[0][2];
			Det[1] = M[0][1] * Temp.M[1][0] - M[2][1] * Temp.M[1][1] + M[3][1] * Temp.M[1][2];
			Det[2] = M[0][1] * Temp.M[2][0] - M[1][1] * Temp.M[2][1] + M[3][1] * Temp.M[2][2];
			Det[3] = M[0][1] * Temp.M[3][0] - M[1][1] * Temp.M[3][1] + M[2][1] * Temp.M[3][2];

			float Determinant = M[0][0] * Det[0] - M[1][0] * Det[1] + M[2][0] * Det[2] - M[3][0] * Det[3];
			const float	RDet = 1.0f / Determinant;

			Result.M[0][0] = RDet * Det[0];
			Result.M[0][1] = -RDet * Det[1];
			Result.M[0][2] = RDet * Det[2];
			Result.M[0][3] = -RDet * Det[3];
			Result.M[1][0] = -RDet * (M[1][0] * Temp.M[0][0] - M[2][0] * Temp.M[0][1] + M[3][0] * Temp.M[0][2]);
			Result.M[1][1] = RDet * (M[0][0] * Temp.M[1][0] - M[2][0] * Temp.M[1][1] + M[3][0] * Temp.M[1][2]);
			Result.M[1][2] = -RDet * (M[0][0] * Temp.M[2][0] - M[1][0] * Temp.M[2][1] + M[3][0] * Temp.M[2][2]);
			Result.M[1][3] = RDet * (M[0][0] * Temp.M[3][0] - M[1][0] * Temp.M[3][1] + M[2][0] * Temp.M[3][2]);
			Result.M[2][0] = RDet * (
				M[1][0] * (M[2][1] * M[3][3] - M[2][3] * M[3][1]) -
				M[2][0] * (M[1][1] * M[3][3] - M[1][3] * M[3][1]) +
				M[3][0] * (M[1][1] * M[2][3] - M[1][3] * M[2][1])
				);
			Result.M[2][1] = -RDet * (
				M[0][0] * (M[2][1] * M[3][3] - M[2][3] * M[3][1]) -
				M[2][0] * (M[0][1] * M[3][3] - M[0][3] * M[3][1]) +
				M[3][0] * (M[0][1] * M[2][3] - M[0][3] * M[2][1])
				);
			Result.M[2][2] = RDet * (
				M[0][0] * (M[1][1] * M[3][3] - M[1][3] * M[3][1]) -
				M[1][0] * (M[0][1] * M[3][3] - M[0][3] * M[3][1]) +
				M[3][0] * (M[0][1] * M[1][3] - M[0][3] * M[1][1])
				);
			Result.M[2][3] = -RDet * (
				M[0][0] * (M[1][1] * M[2][3] - M[1][3] * M[2][1]) -
				M[1][0] * (M[0][1] * M[2][3] - M[0][3] * M[2][1]) +
				M[2][0] * (M[0][1] * M[1][3] - M[0][3] * M[1][1])
				);
			Result.M[3][0] = -RDet * (
				M[1][0] * (M[2][1] * M[3][2] - M[2][2] * M[3][1]) -
				M[2][0] * (M[1][1] * M[3][2] - M[1][2] * M[3][1]) +
				M[3][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1])
				);
			Result.M[3][1] = RDet * (
				M[0][0] * (M[2][1] * M[3][2] - M[2][2] * M[3][1]) -
				M[2][0] * (M[0][1] * M[3][2] - M[0][2] * M[3][1]) +
				M[3][0] * (M[0][1] * M[2][2] - M[0][2] * M[2][1])
				);
			Result.M[3][2] = -RDet * (
				M[0][0] * (M[1][1] * M[3][2] - M[1][2] * M[3][1]) -
				M[1][0] * (M[0][1] * M[3][2] - M[0][2] * M[3][1]) +
				M[3][0] * (M[0][1] * M[1][2] - M[0][2] * M[1][1])
				);
			Result.M[3][3] = RDet * (
				M[0][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1]) -
				M[1][0] * (M[0][1] * M[2][2] - M[0][2] * M[2][1]) +
				M[2][0] * (M[0][1] * M[1][2] - M[0][2] * M[1][1])
				);

			return Result;
		}

		__forceinline void Invert()
		{
			Matrix Result;
			Matrix Temp;

			float Det[4];

			Temp.M[0][0] = M[2][2] * M[3][3] - M[2][3] * M[3][2];
			Temp.M[0][1] = M[1][2] * M[3][3] - M[1][3] * M[3][2];
			Temp.M[0][2] = M[1][2] * M[2][3] - M[1][3] * M[2][2];

			Temp.M[1][0] = M[2][2] * M[3][3] - M[2][3] * M[3][2];
			Temp.M[1][1] = M[0][2] * M[3][3] - M[0][3] * M[3][2];
			Temp.M[1][2] = M[0][2] * M[2][3] - M[0][3] * M[2][2];

			Temp.M[2][0] = M[1][2] * M[3][3] - M[1][3] * M[3][2];
			Temp.M[2][1] = M[0][2] * M[3][3] - M[0][3] * M[3][2];
			Temp.M[2][2] = M[0][2] * M[1][3] - M[0][3] * M[1][2];

			Temp.M[3][0] = M[1][2] * M[2][3] - M[1][3] * M[2][2];
			Temp.M[3][1] = M[0][2] * M[2][3] - M[0][3] * M[2][2];
			Temp.M[3][2] = M[0][2] * M[1][3] - M[0][3] * M[1][2];

			Det[0] = M[1][1] * Temp.M[0][0] - M[2][1] * Temp.M[0][1] + M[3][1] * Temp.M[0][2];
			Det[1] = M[0][1] * Temp.M[1][0] - M[2][1] * Temp.M[1][1] + M[3][1] * Temp.M[1][2];
			Det[2] = M[0][1] * Temp.M[2][0] - M[1][1] * Temp.M[2][1] + M[3][1] * Temp.M[2][2];
			Det[3] = M[0][1] * Temp.M[3][0] - M[1][1] * Temp.M[3][1] + M[2][1] * Temp.M[3][2];

			float Determinant = M[0][0] * Det[0] - M[1][0] * Det[1] + M[2][0] * Det[2] - M[3][0] * Det[3];
			const float	RDet = 1.0f / Determinant;

			Result.M[0][0] = RDet * Det[0];
			Result.M[0][1] = -RDet * Det[1];
			Result.M[0][2] = RDet * Det[2];
			Result.M[0][3] = -RDet * Det[3];
			Result.M[1][0] = -RDet * (M[1][0] * Temp.M[0][0] - M[2][0] * Temp.M[0][1] + M[3][0] * Temp.M[0][2]);
			Result.M[1][1] = RDet * (M[0][0] * Temp.M[1][0] - M[2][0] * Temp.M[1][1] + M[3][0] * Temp.M[1][2]);
			Result.M[1][2] = -RDet * (M[0][0] * Temp.M[2][0] - M[1][0] * Temp.M[2][1] + M[3][0] * Temp.M[2][2]);
			Result.M[1][3] = RDet * (M[0][0] * Temp.M[3][0] - M[1][0] * Temp.M[3][1] + M[2][0] * Temp.M[3][2]);
			Result.M[2][0] = RDet * (
				M[1][0] * (M[2][1] * M[3][3] - M[2][3] * M[3][1]) -
				M[2][0] * (M[1][1] * M[3][3] - M[1][3] * M[3][1]) +
				M[3][0] * (M[1][1] * M[2][3] - M[1][3] * M[2][1])
				);
			Result.M[2][1] = -RDet * (
				M[0][0] * (M[2][1] * M[3][3] - M[2][3] * M[3][1]) -
				M[2][0] * (M[0][1] * M[3][3] - M[0][3] * M[3][1]) +
				M[3][0] * (M[0][1] * M[2][3] - M[0][3] * M[2][1])
				);
			Result.M[2][2] = RDet * (
				M[0][0] * (M[1][1] * M[3][3] - M[1][3] * M[3][1]) -
				M[1][0] * (M[0][1] * M[3][3] - M[0][3] * M[3][1]) +
				M[3][0] * (M[0][1] * M[1][3] - M[0][3] * M[1][1])
				);
			Result.M[2][3] = -RDet * (
				M[0][0] * (M[1][1] * M[2][3] - M[1][3] * M[2][1]) -
				M[1][0] * (M[0][1] * M[2][3] - M[0][3] * M[2][1]) +
				M[2][0] * (M[0][1] * M[1][3] - M[0][3] * M[1][1])
				);
			Result.M[3][0] = -RDet * (
				M[1][0] * (M[2][1] * M[3][2] - M[2][2] * M[3][1]) -
				M[2][0] * (M[1][1] * M[3][2] - M[1][2] * M[3][1]) +
				M[3][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1])
				);
			Result.M[3][1] = RDet * (
				M[0][0] * (M[2][1] * M[3][2] - M[2][2] * M[3][1]) -
				M[2][0] * (M[0][1] * M[3][2] - M[0][2] * M[3][1]) +
				M[3][0] * (M[0][1] * M[2][2] - M[0][2] * M[2][1])
				);
			Result.M[3][2] = -RDet * (
				M[0][0] * (M[1][1] * M[3][2] - M[1][2] * M[3][1]) -
				M[1][0] * (M[0][1] * M[3][2] - M[0][2] * M[3][1]) +
				M[3][0] * (M[0][1] * M[1][2] - M[0][2] * M[1][1])
				);
			Result.M[3][3] = RDet * (
				M[0][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1]) -
				M[1][0] * (M[0][1] * M[2][2] - M[0][2] * M[2][1]) +
				M[2][0] * (M[0][1] * M[1][2] - M[0][2] * M[1][1])
				);

			*this = Result;
		}

		__forceinline Matrix GetTransposed() const
		{
			Matrix Result;
			Result.M[0][0] = M[0][0]; Result.M[0][1] = M[1][0]; Result.M[0][2] = M[2][0]; Result.M[0][3] = M[3][0];
			Result.M[1][0] = M[0][1]; Result.M[1][1] = M[1][1]; Result.M[1][2] = M[2][1]; Result.M[1][3] = M[3][1];
			Result.M[2][0] = M[0][2]; Result.M[2][1] = M[1][2]; Result.M[2][2] = M[2][2]; Result.M[2][3] = M[3][2];
			Result.M[3][0] = M[0][3]; Result.M[3][1] = M[1][3]; Result.M[3][2] = M[2][3]; Result.M[3][3] = M[3][3];
			return Result;
		}

		__forceinline void Transpose()
		{
			Matrix Result;
			Result.M[0][0] = M[0][0]; Result.M[0][1] = M[1][0]; Result.M[0][2] = M[2][0]; Result.M[0][3] = M[3][0];
			Result.M[1][0] = M[0][1]; Result.M[1][1] = M[1][1]; Result.M[1][2] = M[2][1]; Result.M[1][3] = M[3][1];
			Result.M[2][0] = M[0][2]; Result.M[2][1] = M[1][2]; Result.M[2][2] = M[2][2]; Result.M[2][3] = M[3][2];
			Result.M[3][0] = M[0][3]; Result.M[3][1] = M[1][3]; Result.M[3][2] = M[2][3]; Result.M[3][3] = M[3][3];
			*this = Result;
		}

		__forceinline Matrix operator-() const
		{
			return Matrix(
				M[0][0], M[1][0], M[2][0], M[3][0],
				M[0][1], M[1][1], M[2][1], M[3][1],
				M[0][2], M[1][2], M[2][2], M[3][2],
				M[0][3], M[1][3], M[2][3], M[3][3]);
		}

		__forceinline Matrix& operator=(const Matrix &Other)
		{
			if (this != &Other)
			{
				M[0][0] = Other.M[0][0]; M[0][1] = Other.M[0][1]; M[0][2] = Other.M[0][2]; M[0][3] = Other.M[0][3];
				M[1][0] = Other.M[1][0]; M[1][1] = Other.M[1][1]; M[1][2] = Other.M[1][2]; M[1][3] = Other.M[1][3];
				M[2][0] = Other.M[2][0]; M[2][1] = Other.M[2][1]; M[2][2] = Other.M[2][2]; M[2][3] = Other.M[2][3];
				M[3][0] = Other.M[3][0]; M[3][1] = Other.M[3][1]; M[3][2] = Other.M[3][2]; M[3][3] = Other.M[3][3];
			}
			return *this;
		}

		__forceinline bool operator==(const Matrix &Other) const
		{
			return
				M[0][0] == Other.M[0][0] && M[0][1] == Other.M[0][1] && M[0][2] == Other.M[0][2] && M[0][3] == Other.M[0][3] &&
				M[1][0] == Other.M[1][0] && M[1][1] == Other.M[1][1] && M[1][2] == Other.M[1][2] && M[1][3] == Other.M[1][3] &&
				M[2][0] == Other.M[2][0] && M[2][1] == Other.M[2][1] && M[2][2] == Other.M[2][2] && M[2][3] == Other.M[2][3] &&
				M[3][0] == Other.M[3][0] && M[3][1] == Other.M[3][1] && M[3][2] == Other.M[3][2] && M[3][3] == Other.M[3][3];
		}

		__forceinline bool operator!=(const Matrix &Other) const
		{
			return
				M[0][0] != Other.M[0][0] || M[0][1] != Other.M[0][1] || M[0][2] != Other.M[0][2] || M[0][3] != Other.M[0][3] ||
				M[1][0] != Other.M[1][0] || M[1][1] != Other.M[1][1] || M[1][2] != Other.M[1][2] || M[1][3] != Other.M[1][3] ||
				M[2][0] != Other.M[2][0] || M[2][1] != Other.M[2][1] || M[2][2] != Other.M[2][2] || M[2][3] != Other.M[2][3] ||
				M[3][0] != Other.M[3][0] || M[3][1] != Other.M[3][1] || M[3][2] != Other.M[3][2] || M[3][3] != Other.M[3][3];
		}

		__forceinline Matrix operator*(const Matrix &Other) const
		{
			Matrix Result;

			Result.M[0][0] = M[0][0] * Other.M[0][0] + M[0][1] * Other.M[1][0] + M[0][2] * Other.M[2][0] + M[0][3] * Other.M[3][0];
			Result.M[0][1] = M[0][0] * Other.M[0][1] + M[0][1] * Other.M[1][1] + M[0][2] * Other.M[2][1] + M[0][3] * Other.M[3][1];
			Result.M[0][2] = M[0][0] * Other.M[0][2] + M[0][1] * Other.M[1][2] + M[0][2] * Other.M[2][2] + M[0][3] * Other.M[3][2];
			Result.M[0][3] = M[0][0] * Other.M[0][3] + M[0][1] * Other.M[1][3] + M[0][2] * Other.M[2][3] + M[0][3] * Other.M[3][3];

			Result.M[1][0] = M[1][0] * Other.M[0][0] + M[1][1] * Other.M[1][0] + M[1][2] * Other.M[2][0] + M[1][3] * Other.M[3][0];
			Result.M[1][1] = M[1][0] * Other.M[0][1] + M[1][1] * Other.M[1][1] + M[1][2] * Other.M[2][1] + M[1][3] * Other.M[3][1];
			Result.M[1][2] = M[1][0] * Other.M[0][2] + M[1][1] * Other.M[1][2] + M[1][2] * Other.M[2][2] + M[1][3] * Other.M[3][2];
			Result.M[1][3] = M[1][0] * Other.M[0][3] + M[1][1] * Other.M[1][3] + M[1][2] * Other.M[2][3] + M[1][3] * Other.M[3][3];

			Result.M[2][0] = M[2][0] * Other.M[0][0] + M[2][1] * Other.M[1][0] + M[2][2] * Other.M[2][0] + M[2][3] * Other.M[3][0];
			Result.M[2][1] = M[2][0] * Other.M[0][1] + M[2][1] * Other.M[1][1] + M[2][2] * Other.M[2][1] + M[2][3] * Other.M[3][1];
			Result.M[2][2] = M[2][0] * Other.M[0][2] + M[2][1] * Other.M[1][2] + M[2][2] * Other.M[2][2] + M[2][3] * Other.M[3][2];
			Result.M[2][3] = M[2][0] * Other.M[0][3] + M[2][1] * Other.M[1][3] + M[2][2] * Other.M[2][3] + M[2][3] * Other.M[3][3];

			Result.M[3][0] = M[3][0] * Other.M[0][0] + M[3][1] * Other.M[1][0] + M[3][2] * Other.M[2][0] + M[3][3] * Other.M[3][0];
			Result.M[3][1] = M[3][0] * Other.M[0][1] + M[3][1] * Other.M[1][1] + M[3][2] * Other.M[2][1] + M[3][3] * Other.M[3][1];
			Result.M[3][2] = M[3][0] * Other.M[0][2] + M[3][1] * Other.M[1][2] + M[3][2] * Other.M[2][2] + M[3][3] * Other.M[3][2];
			Result.M[3][3] = M[3][0] * Other.M[0][3] + M[3][1] * Other.M[1][3] + M[3][2] * Other.M[2][3] + M[3][3] * Other.M[3][3];

			return Result;
		}

		__forceinline void operator*=(const Matrix &Other)
		{
			Matrix Result;

			Result.M[0][0] = M[0][0] * Other.M[0][0] + M[0][1] * Other.M[1][0] + M[0][2] * Other.M[2][0] + M[0][3] * Other.M[3][0];
			Result.M[0][1] = M[0][0] * Other.M[0][1] + M[0][1] * Other.M[1][1] + M[0][2] * Other.M[2][1] + M[0][3] * Other.M[3][1];
			Result.M[0][2] = M[0][0] * Other.M[0][2] + M[0][1] * Other.M[1][2] + M[0][2] * Other.M[2][2] + M[0][3] * Other.M[3][2];
			Result.M[0][3] = M[0][0] * Other.M[0][3] + M[0][1] * Other.M[1][3] + M[0][2] * Other.M[2][3] + M[0][3] * Other.M[3][3];

			Result.M[1][0] = M[1][0] * Other.M[0][0] + M[1][1] * Other.M[1][0] + M[1][2] * Other.M[2][0] + M[1][3] * Other.M[3][0];
			Result.M[1][1] = M[1][0] * Other.M[0][1] + M[1][1] * Other.M[1][1] + M[1][2] * Other.M[2][1] + M[1][3] * Other.M[3][1];
			Result.M[1][2] = M[1][0] * Other.M[0][2] + M[1][1] * Other.M[1][2] + M[1][2] * Other.M[2][2] + M[1][3] * Other.M[3][2];
			Result.M[1][3] = M[1][0] * Other.M[0][3] + M[1][1] * Other.M[1][3] + M[1][2] * Other.M[2][3] + M[1][3] * Other.M[3][3];

			Result.M[2][0] = M[2][0] * Other.M[0][0] + M[2][1] * Other.M[1][0] + M[2][2] * Other.M[2][0] + M[2][3] * Other.M[3][0];
			Result.M[2][1] = M[2][0] * Other.M[0][1] + M[2][1] * Other.M[1][1] + M[2][2] * Other.M[2][1] + M[2][3] * Other.M[3][1];
			Result.M[2][2] = M[2][0] * Other.M[0][2] + M[2][1] * Other.M[1][2] + M[2][2] * Other.M[2][2] + M[2][3] * Other.M[3][2];
			Result.M[2][3] = M[2][0] * Other.M[0][3] + M[2][1] * Other.M[1][3] + M[2][2] * Other.M[2][3] + M[2][3] * Other.M[3][3];

			Result.M[3][0] = M[3][0] * Other.M[0][0] + M[3][1] * Other.M[1][0] + M[3][2] * Other.M[2][0] + M[3][3] * Other.M[3][0];
			Result.M[3][1] = M[3][0] * Other.M[0][1] + M[3][1] * Other.M[1][1] + M[3][2] * Other.M[2][1] + M[3][3] * Other.M[3][1];
			Result.M[3][2] = M[3][0] * Other.M[0][2] + M[3][1] * Other.M[1][2] + M[3][2] * Other.M[2][2] + M[3][3] * Other.M[3][2];
			Result.M[3][3] = M[3][0] * Other.M[0][3] + M[3][1] * Other.M[1][3] + M[3][2] * Other.M[2][3] + M[3][3] * Other.M[3][3];

			*this = Result;
		}

		__forceinline Matrix operator*(float Scalar) const
		{
			Matrix Result;

			Result.M[0][0] = M[0][0] * Scalar; Result.M[0][1] = M[0][1] * Scalar; Result.M[0][2] = M[0][2] * Scalar; Result.M[0][3] = M[0][3] * Scalar;
			Result.M[1][0] = M[1][0] * Scalar; Result.M[1][1] = M[1][1] * Scalar; Result.M[1][2] = M[1][2] * Scalar; Result.M[1][3] = M[1][3] * Scalar;
			Result.M[2][0] = M[2][0] * Scalar; Result.M[2][1] = M[2][1] * Scalar; Result.M[2][2] = M[2][2] * Scalar; Result.M[2][3] = M[2][3] * Scalar;
			Result.M[3][0] = M[3][0] * Scalar; Result.M[3][1] = M[3][1] * Scalar; Result.M[3][2] = M[3][2] * Scalar; Result.M[3][3] = M[3][3] * Scalar;

			return Result;
		}

		__forceinline void operator*=(float Scalar)
		{
			M[0][0] *= Scalar; M[0][1] *= Scalar; M[0][2] *= Scalar; M[0][3] *= Scalar;
			M[1][0] *= Scalar; M[1][1] *= Scalar; M[1][2] *= Scalar; M[1][3] *= Scalar;
			M[2][0] *= Scalar; M[2][1] *= Scalar; M[2][2] *= Scalar; M[2][3] *= Scalar;
			M[3][0] *= Scalar; M[3][1] *= Scalar; M[3][2] *= Scalar; M[3][3] *= Scalar;
		}

		__forceinline Matrix operator+(const Matrix &Other) const
		{
			Matrix Result;
			Result.M[0][0] = M[0][0] + Other.M[0][0]; Result.M[0][1] = M[0][1] + Other.M[0][1]; Result.M[0][2] = M[0][2] + Other.M[0][2]; Result.M[0][3] = M[0][3] + Other.M[0][3];
			Result.M[1][0] = M[1][0] + Other.M[1][0]; Result.M[1][1] = M[1][1] + Other.M[1][1]; Result.M[1][2] = M[1][2] + Other.M[1][2]; Result.M[1][3] = M[1][3] + Other.M[1][3];
			Result.M[2][0] = M[2][0] + Other.M[2][0]; Result.M[2][1] = M[2][1] + Other.M[2][1]; Result.M[2][2] = M[2][2] + Other.M[2][2]; Result.M[2][3] = M[2][3] + Other.M[2][3];
			Result.M[3][0] = M[3][0] + Other.M[3][0]; Result.M[3][1] = M[3][1] + Other.M[3][1]; Result.M[3][2] = M[3][2] + Other.M[3][2]; Result.M[3][3] = M[3][3] + Other.M[3][3];
			return Result;
		}

		__forceinline void operator+=(const Matrix &Other)
		{
			M[0][0] += Other.M[0][0]; M[0][1] += Other.M[0][1]; M[0][2] += Other.M[0][2]; M[0][3] += Other.M[0][3];
			M[1][0] += Other.M[1][0]; M[1][1] += Other.M[1][1]; M[1][2] += Other.M[1][2]; M[1][3] += Other.M[1][3];
			M[2][0] += Other.M[2][0]; M[2][1] += Other.M[2][1]; M[2][2] += Other.M[2][2]; M[2][3] += Other.M[2][3];
			M[3][0] += Other.M[3][0]; M[3][1] += Other.M[3][1]; M[3][2] += Other.M[3][2]; M[3][3] += Other.M[3][3];
		}

		__forceinline Matrix operator+(float Scalar) const
		{
			Matrix Result;
			Result.M[0][0] = M[0][0] + Scalar; Result.M[0][1] = M[0][1] + Scalar; Result.M[0][2] = M[0][2] + Scalar; Result.M[0][3] = M[0][3] + Scalar;
			Result.M[1][0] = M[1][0] + Scalar; Result.M[1][1] = M[1][1] + Scalar; Result.M[1][2] = M[1][2] + Scalar; Result.M[1][3] = M[1][3] + Scalar;
			Result.M[2][0] = M[2][0] + Scalar; Result.M[2][1] = M[2][1] + Scalar; Result.M[2][2] = M[2][2] + Scalar; Result.M[2][3] = M[2][3] + Scalar;
			Result.M[3][0] = M[3][0] + Scalar; Result.M[3][1] = M[3][1] + Scalar; Result.M[3][2] = M[3][2] + Scalar; Result.M[3][3] = M[3][3] + Scalar;
			return Result;
		}

		__forceinline void operator+=(float Scalar)
		{
			M[0][0] += Scalar; M[0][1] += Scalar; M[0][2] += Scalar; M[0][3] += Scalar;
			M[1][0] += Scalar; M[1][1] += Scalar; M[1][2] += Scalar; M[1][3] += Scalar;
			M[2][0] += Scalar; M[2][1] += Scalar; M[2][2] += Scalar; M[2][3] += Scalar;
			M[3][0] += Scalar; M[3][1] += Scalar; M[3][2] += Scalar; M[3][3] += Scalar;
		}

		__forceinline Matrix operator-(const Matrix &Other) const
		{
			Matrix Result;
			Result.M[0][0] = M[0][0] - Other.M[0][0]; Result.M[0][1] = M[0][1] - Other.M[0][1]; Result.M[0][2] = M[0][2] - Other.M[0][2]; Result.M[0][3] = M[0][3] - Other.M[0][3];
			Result.M[1][0] = M[1][0] - Other.M[1][0]; Result.M[1][1] = M[1][1] - Other.M[1][1]; Result.M[1][2] = M[1][2] - Other.M[1][2]; Result.M[1][3] = M[1][3] - Other.M[1][3];
			Result.M[2][0] = M[2][0] - Other.M[2][0]; Result.M[2][1] = M[2][1] - Other.M[2][1]; Result.M[2][2] = M[2][2] - Other.M[2][2]; Result.M[2][3] = M[2][3] - Other.M[2][3];
			Result.M[3][0] = M[3][0] - Other.M[3][0]; Result.M[3][1] = M[3][1] - Other.M[3][1]; Result.M[3][2] = M[3][2] - Other.M[3][2]; Result.M[3][3] = M[3][3] - Other.M[3][3];
			return Result;
		}

		__forceinline void operator-=(const Matrix &Other)
		{
			M[0][0] -= Other.M[0][0]; M[0][1] -= Other.M[0][1]; M[0][2] -= Other.M[0][2]; M[0][3] -= Other.M[0][3];
			M[1][0] -= Other.M[1][0]; M[1][1] -= Other.M[1][1]; M[1][2] -= Other.M[1][2]; M[1][3] -= Other.M[1][3];
			M[2][0] -= Other.M[2][0]; M[2][1] -= Other.M[2][1]; M[2][2] -= Other.M[2][2]; M[2][3] -= Other.M[2][3];
			M[3][0] -= Other.M[3][0]; M[3][1] -= Other.M[3][1]; M[3][2] -= Other.M[3][2]; M[3][3] -= Other.M[3][3];
		}

		__forceinline Matrix operator-(float Scalar) const
		{
			Matrix Result;
			Result.M[0][0] = M[0][0] - Scalar; Result.M[0][1] = M[0][1] - Scalar; Result.M[0][2] = M[0][2] - Scalar; Result.M[0][3] = M[0][3] - Scalar;
			Result.M[1][0] = M[1][0] - Scalar; Result.M[1][1] = M[1][1] - Scalar; Result.M[1][2] = M[1][2] - Scalar; Result.M[1][3] = M[1][3] - Scalar;
			Result.M[2][0] = M[2][0] - Scalar; Result.M[2][1] = M[2][1] - Scalar; Result.M[2][2] = M[2][2] - Scalar; Result.M[2][3] = M[2][3] - Scalar;
			Result.M[3][0] = M[3][0] - Scalar; Result.M[3][1] = M[3][1] - Scalar; Result.M[3][2] = M[3][2] - Scalar; Result.M[3][3] = M[3][3] - Scalar;
			return Result;
		}

		__forceinline void operator-=(float Scalar)
		{
			M[0][0] -= Scalar; M[0][1] -= Scalar; M[0][2] -= Scalar; M[0][3] -= Scalar;
			M[1][0] -= Scalar; M[1][1] -= Scalar; M[1][2] -= Scalar; M[1][3] -= Scalar;
			M[2][0] -= Scalar; M[2][1] -= Scalar; M[2][2] -= Scalar; M[2][3] -= Scalar;
			M[3][0] -= Scalar; M[3][1] -= Scalar; M[3][2] -= Scalar; M[3][3] -= Scalar;
		}

		static RADIANT_API const Matrix Zero;
		static RADIANT_API const Matrix Identity;
	};
}
