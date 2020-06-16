#pragma once

#include "Matrix.h"

namespace Radiant
{
	struct Transformation
	{
	protected:
		Vector3		Translation;
		Quaternion	Rotation;
		Vector3		Scalation;		

	public:
		__forceinline Transformation() {}

		__forceinline Transformation(const Vector3 &Translation, const Quaternion &Rotation = Quaternion::Identity, const Vector3 &Scalation = Vector3::Identity)
			: Translation(Translation)
			, Rotation(Rotation)
			, Scalation(Scalation)
		{}

		__forceinline ~Transformation() {}

		__forceinline bool ContainsNaN() const
		{
			return Translation.ContainsNaN() || Rotation.ContainsNaN() || Scalation.ContainsNaN();
		}

		__forceinline void CheckNaN()
		{
			if (ContainsNaN())
			{
				*this = Transformation::Identity;
			}
		}

		static RADIANT_API const Transformation Identity;
	};
}
