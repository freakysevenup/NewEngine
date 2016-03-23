// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 03-23-2016
// Created For      : Jade Math Library
// Last Modified By : Jesse Derochie
// Last Modified On : 03-23-2016
// ***********************************************************************
// <copyright file="JadeMath.h">
//     Copyright (c) Jesse Derochie. All rights reserved.
// </copyright>
// <summary>JML JadeMath class header file</summary>
// ***********************************************************************
#pragma once
#include <math.h>
#include "Jade_Primitives.h"

namespace jml
{
	static const float J_PI	= JFloat(3.141592653589793);
	static const int J_NIL = JInt(0);

	JFloat j_Abs(JFloat param);
	JFloat j_Max(JFloat param1, JFloat param2);
	JFloat j_Min(JFloat param1, JFloat param2);
	JFloat j_Sqrt(JFloat param);
	JFloat j_RecipricalSqrt(JFloat param);
	JFloat j_Sin(JFloat param);
	JFloat j_Cos(JFloat param);
	JFloat j_Tan(JFloat param);
	JFloat j_ASin(JFloat param);
	JFloat j_ACos(JFloat param);
	JFloat j_ATan(JFloat param);
	JFloat j_ATan2(JFloat param1, JFloat param2);
	JFloat j_Floor(JFloat param);
	JFloat j_Ceil(JFloat param);
	JFloat j_Pow(JFloat param1, JFloat param2);
	JFloat j_Exp(JFloat param);
	JBool j_IsFinite(JFloat param);
		
	template <class T>
	T j_Max(T param1, T param2);
	template <class T>
	T j_Min(T param1, T param2);
	template <class T>
	T j_Clamp(T param, T lowParam, T highParam);

}