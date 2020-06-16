#pragma once

#include "Platform.h"
#include "Std.h"

namespace Radiant
{
	enum EInputState
	{
		IS_None,
		IS_Pressed,
		IS_Repeated,
		IS_Released,
		IS_DoubleClicked
	};
}

namespace Radiant
{
	class Key
	{
	protected:
		const int32_t	Code;
		const tchar		*Name;

	public:
		__forceinline Key(int32_t Code = 0, const tchar *Name = TXT("Unnamed"))
			: Code(Code)
			, Name(Name)
		{}

		__forceinline ~Key() {}

	public:
		__forceinline int32_t GetCode() const
		{
			return Code;
		}

		__forceinline const tchar * GetName() const
		{
			return Name;
		}
	};
}
