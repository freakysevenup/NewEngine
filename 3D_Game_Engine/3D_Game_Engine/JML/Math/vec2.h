// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 03-23-2016
// Created For      : Jade Math Library
// Last Modified By : Jesse Derochie
// Last Modified On : 03-23-2016
// ***********************************************************************
// <copyright file="vec2.h">
//     Copyright (c) Jesse Derochie. All rights reserved.
// </copyright>
// <summary>JML vec2 class header file</summary>
// ***********************************************************************
#pragma once
#include "Jade_Primitives.h"

namespace jml
{
	class vec2
	{
	public:
		/// <summary>
		/// Initializes a new instance of the <see cref="vec2"/> class.
		/// </summary>
		vec2() {}
		/// <summary>
		/// Initializes a new instance of the <see cref="vec2"/> class.
		/// </summary>
		/// <param name="param">The initializing parameter.</param>
		vec2(JFloat param)
			: x(param), y(param) {}
		/// <summary>
		/// Initializes a new instance of the <see cref="vec2"/> class.
		/// </summary>
		/// <param name="xVal">The x value.</param>
		/// <param name="yVal">The y value.</param>
		vec2(JFloat xVal, JFloat yVal)
			: x(xVal), y(yVal) {}
		/// <summary>
		/// Copy Constructor
		/// </summary>
		/// <param name="other">The other.</param>
		vec2(const vec2 & other)
			: x(other.x), y(other.y) {}
		/// <summary>
		/// Finalizes an instance of the <see cref="vec2"/> class.
		/// </summary>
		~vec2() {}

		vec2 operator () (JFloat xVal, JFloat yVal);
		vec2 operator + (vec2 &param);
		vec2 operator += (vec2 &param);
		vec2 operator + (JFloat param);
		vec2 operator += (JFloat param);
		vec2 operator - (vec2 &param);
		vec2 operator - (void);
		vec2 operator -= (vec2 &param);
		vec2 operator * (vec2 &param);
		vec2 operator *= (vec2 &param);
		vec2 operator * (JFloat param);
		vec2 operator *= (JFloat param);
		vec2 operator / (JFloat param);
		vec2 operator /= (JFloat param);
		JBool operator == (vec2 &param);
		JBool operator != (vec2 &param);
		JBool operator < (vec2 &param);
		JBool operator > (vec2 &param);

		/// <summary>
		/// Returns a unit vector
		/// </summary>
		/// <returns></returns>
		vec2 GetUnitVector();
		/// <summary>
		/// Normalizes this vec2.
		/// </summary>
		/// <returns></returns>
		void Normalize();
		/// <summary>
		/// gets the dot product of this vec2 and the passed parameter
		/// </summary>
		/// <param name="_passed">The _passed.</param>
		/// <returns></returns>
		JFloat Dot(vec2 &param);
		/// <summary>
		/// gets the Magnitude of this vec2.
		/// </summary>
		/// <returns></returns>
		JFloat Magnitude();
		/// <summary>
		/// gets the squared Magnitude of this vec2.
		/// </summary>
		/// <returns></returns>
		JFloat MagnitudeSquared();
		/// <summary>
		/// Rotates this vec2
		/// </summary>
		/// <param name="_angle">The _angle.</param>
		/// <returns></returns>
		void RotateVector(JFloat param);

		/// <summary>
		/// The x value of this vec2
		/// </summary>
		JFloat x;
		/// <summary>
		/// The y value of this vec2
		/// </summary>
		JFloat y;
	};

	vec2 operator * (JFloat param, vec2 vec)
	{
		return param * vec;
	}
	vec2 operator / (JFloat param, vec2 vec)
	{
		return param / vec;
	}
	vec2 operator - (JFloat param, vec2 vec)
	{
		return param - vec;
	}
	vec2 operator + (JFloat param, vec2 vec)
	{
		return param + vec;
	}
	vec2 operator *= (JFloat param, vec2 vec)
	{
		return param *= vec;
	}
	vec2 operator /= (JFloat param, vec2 vec)
	{
		return param /= vec;
	}
	vec2 operator -= (JFloat param, vec2 vec)
	{
		return param -= vec;
	}
	vec2 operator += (JFloat param, vec2 vec)
	{
		return param += vec;
	}
}

