#include "Vector2.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix.h"
#include "Transformation.h"

namespace Radiant
{
	const Vector2 Vector2::Zero						= Vector2(0.0f, 0.0f);
	const Vector2 Vector2::Identity					= Vector2(1.0f, 1.0f);

	const Vector3 Vector3::Zero						= Vector3(0.0f, 0.0f, 0.0f);
	const Vector3 Vector3::Forward					= Vector3(1.0f, 0.0f, 0.0f);
	const Vector3 Vector3::Right					= Vector3(0.0f, 1.0f, 0.0f);
	const Vector3 Vector3::Up						= Vector3(0.0f, 0.0f, 1.0f);
	const Vector3 Vector3::Identity					= Vector3(1.0f, 1.0f, 1.0f);

	const Quaternion Quaternion::Identity			= Quaternion(1.0f, 0.0f, 0.0f, 0.0f);

	const Matrix Matrix::Zero						= Matrix(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	const Matrix Matrix::Identity					= Matrix(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	const Transformation Transformation::Identity	= Transformation(Vector3::Zero, Quaternion::Identity, Vector3::Identity);
}
