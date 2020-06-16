/*
	Filename:		Timer.h
	Description:	In engine timer class
	Author:			Valentin Karyagin
*/

#pragma once

#include "Platform.h"

namespace Radiant
{
	/** Timer */
	class Timer
	{
	private:
		clock_t Started, DeltaWhenStarted, Before, Delta;

	public:
		/** Default constructor */
		__forceinline Timer()
			: Started(clock())
			, DeltaWhenStarted(0)
			, Before(0)
			, Delta(0)

		{}

		/** Destructor */
		__forceinline ~Timer() {}

	public:
		/** Recalculating ticks */
		__forceinline void Update()
		{
			const clock_t CurrentTick = clock();
			DeltaWhenStarted = CurrentTick - Started;
			Delta = CurrentTick - Before;
			Before = CurrentTick;
		}

	public:
		/** Returns ticks when engine started */
		__forceinline uint32_t GetDeltaTicksWhenStarted() const
		{
			return DeltaWhenStarted;
		}

		/** Returns ticks when last recalculating (Update() method) */
		__forceinline uint32_t GetDeltaTicks() const
		{
			return Delta;
		}
		
	public:
		/** Returns seconds when engine started */
		__forceinline float CalcDeltaTimeWhenStarted() const
		{
			return static_cast<float>(DeltaWhenStarted) * 0.001f;
		}

		/** Returns seconds when last recalculating (Update() method) */
		__forceinline float CalcDeltaTime() const
		{
			return static_cast<float>(Delta) * 0.001f;
		}
	};
}
