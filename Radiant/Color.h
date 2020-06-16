/*
	Filename:		Color.h
	Description:	Color structure
	Author:			Valentin Karyagin
*/

#include "Object.h"

namespace Radiant
{
	struct Color
	{
	public:
		uint8_t R, G, B, A;

	public:
		__forceinline Color(uint8_t R = 255, uint8_t G = 255, uint8_t B = 255, uint8_t A = 255)
			: R(R)
			, G(G)
			, B(B)
			, A(A)
		{}

		__forceinline ~Color() {}

	public:
		static const RADIANT_API Color White;
		static const RADIANT_API Color Red;
		static const RADIANT_API Color Green;
		static const RADIANT_API Color Blue;
		static const RADIANT_API Color Cyan;
		static const RADIANT_API Color Magenta;
		static const RADIANT_API Color Yellow;
		static const RADIANT_API Color Black;
	};	
}
