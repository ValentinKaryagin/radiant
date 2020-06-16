#pragma once

#include "Matrix.h"

namespace Radiant
{
	struct PerspectiveMatrix : public Matrix
	{
		__forceinline PerspectiveMatrix(float FoV, float AspectRatio, float Near, float Far)
		{
			const float YScale = 1.0f / tanf(FoV * 0.5f);
			const float XScale = YScale / AspectRatio;

			M[0][0] = XScale;	M[0][1] = 0.0f;		M[0][2] = 0.0f;								M[0][3] = 0.0f;
			M[1][0] = 0.0f;		M[1][1] = YScale;	M[1][2] = 0.0f;								M[1][3] = 0.0f;
			M[2][0] = 0.0f;		M[2][1] = 0.0f;		M[2][2] = (Far + Near) / (Far - Near);		M[2][3] = 1.0f;
			M[3][0] = 0.0f;		M[3][1] = 0.0f;		M[3][2] = -(2 * Far * Near) / (Far - Near);	M[3][3] = 0.0f;
		}
	};

	struct OrthogonalMatrix : public Matrix
	{
		__forceinline OrthogonalMatrix(float Width,	float Height, float Near, float Far)
		{
			M[0][0] = 2.0f / Width;	M[0][1] = 0.0f;				M[0][2] = 0.0f;					M[0][3] = 0.0f;
			M[1][0] = 0.0f;			M[1][1] = 2.0f / Height;	M[1][2] = 0.0f;					M[1][3] = 0.0f;
			M[2][0] = 0.0f;			M[2][1] = 0.0f;				M[2][2] = 1.0f / (Far - Near);	M[2][3] = 0.0f;
			M[3][0] = 0.0f;			M[3][1] = 0.0f;				M[3][2] = Near / (Near - Far);	M[3][3] = 1.0f;
		}

		__forceinline OrthogonalMatrix(float Left, float Right, float Bottom, float Top, float Near, float Far)
		{
			M[0][0] = 2.0f / (Right - Left);			M[0][1] = 0.0f;								M[0][2] = 0.0f;					M[0][3] = 0.0f;
			M[1][0] = 0.0f;								M[1][1] = 2.0f / (Top - Bottom);			M[1][2] = 0.0f;					M[1][3] = 0.0f;
			M[2][0] = 0.0f;								M[2][1] = 0.0f;								M[2][2] = 1.0f / (Far - Near);	M[2][3] = 0.0f;
			M[3][0] = (Left + Right) / (Left - Right);	M[3][1] = (Top + Bottom) / (Bottom - Top);	M[3][2] = -Near / (Far - Near);	M[3][3] = 1.0f;
		}
	};
}
