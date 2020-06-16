#pragma once

#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix.h"
#include "ScalationMatrix.h"
#include "RotationMatrix.h"
#include "TranslationMatrix.h"
#include "ProjectionMatrix.h"
#include "ViewMatrix.h"
#include "Transformation.h"

namespace Radiant
{
	class Math
	{
	public:
		__forceinline static float DegsToRads(float Degrees)
		{
			return Degrees * 3.14159265f / 180.0f;
		}
	};
}
