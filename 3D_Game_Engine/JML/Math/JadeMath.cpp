// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 03-23-2016
// Created For      : Jade Math Library
// Last Modified By : Jesse Derochie
// Last Modified On : 03-23-2016
// ***********************************************************************
// <copyright file="JadeMath.cpp">
//     Copyright (c) Jesse Derochie. All rights reserved.
// </copyright>
// <summary>JML JadeMath class cpp file</summary>
// ***********************************************************************
#include "JadeMath.h"

namespace jml
{

	JFloat j_Abs(JFloat param)
	{
		return abs(param);
	}

	JFloat j_Max(JFloat param1, JFloat param2)
	{
		return param1 > param2 ? param1 : param2;
	}

	JFloat j_Min(JFloat param1, JFloat param2)
	{
		return param1 < param2 ? param1 : param2;
	}

	JFloat j_Sqrt(JFloat param)
	{
		return sqrtf(param);
	}

	JFloat j_RecipricalSqrt(JFloat param)
	{
		return 1.0f / sqrtf(param);
	}

	JFloat j_Sin(JFloat param)
	{
		return sinf(param);
	}

	JFloat j_Cos(JFloat param)
	{
		return cosf(param);
	}

	JFloat j_Tan(JFloat param)
	{
		return tanf(param);
	}

	JFloat j_ASin(JFloat param)
	{
		return asinf(param);
	}

	JFloat j_ACos(JFloat param)
	{
		return acosf(param);
	}

	JFloat j_ATan(JFloat param)
	{
		return atanf(param);
	}

	JFloat j_ATan2(JFloat param1, JFloat param2)
	{
		return atan2f(param1, param2);
	}

	JFloat j_Floor(JFloat param)
	{
		return floorf(param);
	}

	JFloat j_Ceil(JFloat param)
	{
		return ceilf(param);
	}

	JFloat j_Pow(JFloat param1, JFloat param2)
	{
		return powf(param1, param2);
	}

	JFloat j_Exp(JFloat param)
	{
		return expf(param);
	}

	JBool j_IsFinite(JFloat param)
	{
		return isfinite(param);
	}

	template <class T>
	T j_Max(T param1, T param2)
	{
		return param1 > param2 ? param1 : param2;
	}

	template <class T>
	T j_Min(T param1, T param2)
	{
		return param1 < param2 ? param1 : param2;
	}

	template <class T>
	T j_Clamp(T param, T lowParam, T highParam)
	{
		return highParam > lowParam ? (j_Min(highParam, j_Max(lowParam, param))) : J_NIL;
	}

}