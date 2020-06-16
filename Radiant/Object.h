/*
	Filename:		Object.h
	Description:	Base class for all engine classes
	Author:			Valentin Karyagin
*/

#pragma once

#include "Platform.h"

#define DECLARE_BASECLASS(ThisClass)	\
public:	\
	typedef ThisClass This;	\
public:	\
	__forceinline static ThisClass * GetInstance()	\
	{	\
		static ThisClass ThisClass ## Instance;	\
		return &ThisClass ## Instance;	\
	}	\
private:

#define DECLARE_CLASS(ThisClass, SuperClass)	\
public:	\
	typedef ThisClass	This;	\
	typedef SuperClass	Super;	\
public:	\
	__forceinline static ThisClass * GetInstance()	\
	{	\
		static ThisClass ThisClass ## Instance;	\
		return &ThisClass ## Instance;	\
	}	\
private:

namespace Radiant
{
	/** Base class for all objects */
	class RADIANT_API Object
	{
		DECLARE_BASECLASS(Object)

	public:
		Object();
		virtual ~Object();
	};
}
