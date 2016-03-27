// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 03-23-2016
// Created For      : Jade Math Library
// Last Modified By : Jesse Derochie
// Last Modified On : 03-23-2016
// ***********************************************************************
// <copyright file="vec3.h">
//     Copyright (c) Jesse Derochie. All rights reserved.
// </copyright>
// <summary>JML vec3 class header file</summary>
// ***********************************************************************
#pragma once
#include "Jade_Primitives.h"
#include "vec2.h"

namespace jml
{
	class vec3
	{
	public:
		/// <summary>
		/// Initializes a new instance of the <see cref="vec3"/> class.
		/// </summary>
		vec3() {}
		/// <summary>
		/// Initializes a new instance of the <see cref="vec3"/> class.
		/// </summary>
		/// <param name="param">The parameter.</param>
		vec3(JFloat param)
			: x(param), y(param), z(param) {}
		/// <summary>
		/// Initializes a new instance of the <see cref="vec3"/> class.
		/// </summary>
		/// <param name="xVal">The x value.</param>
		/// <param name="yVal">The y value.</param>
		/// <param name="zVal">The z value.</param>
		vec3(JFloat xVal, JFloat yVal, JFloat zVal)
			: x(xVal), y(yVal), z(zVal) {}
		/// <summary>
		/// Initializes a new instance of the <see cref="vec3"/> class.
		/// </summary>
		/// <param name="param">vec2 containing the x and y values</param>
		/// <param name="zVal">The z value.</param>
		vec3(vec2 param, JFloat zVal)
			: x(param.x), y(param.y), z(zVal) {}
		/// <summary>
		/// Copy Constructor
		/// </summary>
		/// <param name="other">The other.</param>
		vec3(const vec3 & other)
			: x(other.x), y(other.y), z(other.z) {}
		/// <summary>
		/// Finalizes an instance of the <see cref="vec3"/> class.
		/// </summary>
		~vec3() {}

		vec3 operator () (JFloat xVal, JFloat yVal, JFloat zVal);
		vec3 operator + (vec3 &param);
		vec3 operator += (vec3 &param);
		vec3 operator + (JFloat param);
		vec3 operator += (JFloat param);
		vec3 operator - (void);
		vec3 operator - (vec3 &param);
		vec3 operator -= (vec3 &param);
		vec3 operator * (vec3 &param);
		vec3 operator *= (vec3 &param);
		vec3 operator * (JFloat param);
		vec3 operator *= (JFloat param);
		vec3 operator / (JFloat param);
		vec3 operator /= (JFloat param);
		JBool operator == (vec3 &param);
		JBool operator != (vec3 &param);
		JBool operator < (vec3 &param);
		JBool operator > (vec3 &param);

		/// <summary>
		/// Returns a unit vector
		/// </summary>
		/// <returns></returns>
		vec3 GetUnitVector();
		/// <summary>
		/// Normalizes this vec3.
		/// </summary>
		/// <returns></returns>
		void Normalize();
		/// <summary>
		/// gets the Magnitude of this vec3.
		/// </summary>
		/// <returns></returns>
		JFloat Dot(vec3 &param);
		/// <summary>
		/// gets the Magnitude of this vec3.
		/// </summary>
		/// <returns></returns>
		JFloat Magnitude();
		/// <summary>
		/// gets the squared Magnitude of this vec3.
		/// </summary>
		/// <returns></returns>
		JFloat MagnitudeSquared();
		/// <summary>
		/// Returns the cross Product between this vec3 and the passed parameter
		/// </summary>
		/// <param name="param">The parameter.</param>
		/// <returns></returns>
		vec3 Cross(vec3 &param);
		/// <summary>
		/// Returns a vec3 using the smallest values of these vec3's
		/// </summary>
		/// <param name="param">The parameter.</param>
		/// <returns></returns>
		vec3 Minimum(vec3 &param);
		/// <summary>
		/// returns a vec3 using the maximum values of these vec3's
		/// </summary>
		/// <param name="param">The parameter.</param>
		/// <returns></returns>
		vec3 Maximum(vec3 &param);
		/// <summary>
		/// Returns the smallest element in this vec3
		/// </summary>
		/// <returns></returns>
		JFloat MinElement() const;
		/// <summary>
		/// returns the largest element in this vec3
		/// </summary>
		/// <returns></returns>
		JFloat MaxElement() const;

		/// <summary>
		/// The x value of this vec3
		/// </summary>
		JFloat x;
		/// <summary>
		/// The y value of this vec3
		/// </summary>
		JFloat y;
		/// <summary>
		/// The z value of this vec3
		/// </summary>
		JFloat z;
	};

	namespace
	{
		vec3 operator * (JFloat param, vec3 vec)
		{
			return param * vec;
		}
		vec3 operator / (JFloat param, vec3 vec)
		{
			return param / vec;
		}
		vec3 operator - (JFloat param, vec3 vec)
		{
			return param - vec;
		}
		vec3 operator + (JFloat param, vec3 vec)
		{
			return param + vec;
		}
		vec3 operator *= (JFloat param, vec3 vec)
		{
			return param *= vec;
		}
		vec3 operator /= (JFloat param, vec3 vec)
		{
			return param /= vec;
		}
		vec3 operator -= (JFloat param, vec3 vec)
		{
			return param -= vec;
		}
		vec3 operator += (JFloat param, vec3 vec)
		{
			return param += vec;
		}
	}
}