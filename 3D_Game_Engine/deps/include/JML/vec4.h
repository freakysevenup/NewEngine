// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 03-23-2016
// Created For      : Jade Math Library
// Last Modified By : Jesse Derochie
// Last Modified On : 03-23-2016
// ***********************************************************************
// <copyright file="vec4.h">
//     Copyright (c) Jesse Derochie. All rights reserved.
// </copyright>
// <summary>JML vec4 class header file</summary>
// ***********************************************************************
#pragma once
#include "Jade_Primitives.h"
#include "vec3.h"
#include "vec2.h"

namespace jml
{

	class vec4
	{
	public:
		/// <summary>
		/// Initializes a new instance of the <see cref="vec4"/> class.
		/// </summary>
		vec4() {}
		/// <summary>
		/// Initializes a new instance of the <see cref="vec4"/> class.
		/// </summary>
		/// <param name="param">The initializing parameter.</param>
		vec4(JFloat param)
			: x(param), y(param), z(param), w(param) {}
		/// <summary>
		/// Initializes a new instance of the <see cref="vec4"/> class.
		/// </summary>
		/// <param name="xVal">The x value.</param>
		/// <param name="yVal">The y value.</param>
		/// <param name="zVal">The z value.</param>
		/// <param name="wVal">The w value.</param>
		vec4(JFloat xVal, JFloat yVal, JFloat zVal, JFloat wVal)
			: x(xVal), y(yVal), z(zVal), w(wVal) {}
		/// <summary>
		/// Initializes a new instance of the <see cref="vec4"/> class.
		/// </summary>
		/// <param name="param">vec3 containing x, y, z values</param>
		/// <param name="wVal">The w value.</param>
		vec4(vec3 param, JFloat wVal)
			: x(param.x), y(param.y), z(param.z), w(wVal) {}
		/// <summary>
		/// Initializes a new instance of the <see cref="vec4"/> class.
		/// </summary>
		/// <param name="param1">vec2 containing x and y values</param>
		/// <param name="param2">vec2 containing z and w values</param>
		vec4(vec2 param1, vec2 param2)
			: x(param1.x), y(param1.y), z(param2.x), w(param2.y) {}
		/// <summary>
		/// Initializes a new instance of the <see cref="vec4"/> class.
		/// </summary>
		/// <param name="other">The other.</param>
		vec4(const vec4 & other)
			: x(other.x), y(other.y), z(other.z), w(other.w) {}
		/// <summary>
		/// Finalizes an instance of the <see cref="vec4"/> class.
		/// </summary>
		~vec4() {}

		JFloat & operator[](U_JInt i);
		void operator () (JFloat xVal, JFloat yVal, JFloat zVal, JFloat wVal);
		JBool operator == (vec4 &param);
		JBool operator != (vec4 &param);
		vec4 operator = (vec4 &param);
		vec4 operator - (void);
		vec4 operator + (vec4 &param);
		vec4 operator += (vec4 &param);
		vec4 operator - (vec4 &param);
		vec4 operator -= (vec4 &param);
		vec4 operator * (JFloat  param);
		JFloat operator * (vec4 &param);
		vec4 operator *= (JFloat  param);
		vec4 operator / (JFloat  param);
		vec4 operator /= (JFloat  param);

		friend vec4 operator * (JFloat param, vec4 vec);
		friend vec4 operator / (JFloat param, vec4 vec);
		friend vec4 operator - (JFloat param, vec4 vec);
		friend vec4 operator + (JFloat param, vec4 vec);
		friend vec4 operator *= (JFloat param, vec4 vec);
		friend vec4 operator /= (JFloat param, vec4 vec);
		friend vec4 operator -= (JFloat param, vec4 vec);
		friend vec4 operator += (JFloat param, vec4 vec);

		/// <summary>
		/// returns the Magnitude of this vec4
		/// </summary>
		/// <returns></returns>
		JFloat Magnitude();
		/// <summary>
		/// returns the Magnitude of this vec4 squared
		/// </summary>
		/// <returns></returns>
		JFloat MagnitudeSquared();
		/// <summary>
		/// Returns a unit vec4
		/// </summary>
		/// <returns></returns>
		vec4 GetUnitVector();
		/// <summary>
		/// Normalizes this vec4
		/// </summary>
		/// <returns></returns>
		void Normalize();
		/// <summary>
		/// returns a vec4 using the minimum values of these two vec4's
		/// </summary>
		/// <param name="param">The parameter.</param>
		/// <returns></returns>
		vec4 Minimum(vec4 &param);
		/// <summary>
		/// Returns a vec4 using the maximumm values of these two vec4's
		/// </summary>
		/// <param name="param">The parameter.</param>
		/// <returns></returns>
		vec4 Maximum(vec4 &param);
		/// <summary>
		/// Reflects the vec4
		/// </summary>
		/// <param name="param">The parameter.</param>
		void Reflect(vec4 &param);
		/// <summary>
		/// Projects the vec4
		/// </summary>
		/// <param name="param">The parameter.</param>
		void Project(vec4 &param);
		/// <summary>
		/// Returns the projected vec4
		/// </summary>
		/// <param name="param">The parameter.</param>
		/// <returns></returns>
		vec4 Projected(vec4 &param);
		/// <summary>
		/// Returns the x, y and z components as a vec3.
		/// </summary>
		/// <returns></returns>
		vec3 GetXYZ();

		/// <summary>
		/// The x value of this vec4
		/// </summary>
		JFloat x;
		/// <summary>
		/// The y value of this vec4
		/// </summary>
		JFloat y;
		/// <summary>
		/// The z value of this vec4
		/// </summary>
		JFloat z;
		/// <summary>
		/// The w value of this vec4
		/// </summary>
		JFloat w;
	};

}