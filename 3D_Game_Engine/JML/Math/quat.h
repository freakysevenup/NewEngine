// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 03-23-2016
// Created For      : Jade Math Library
// Last Modified By : Jesse Derochie
// Last Modified On : 03-23-2016
// ***********************************************************************
// <copyright file="quat.h">
//     Copyright (c) Jesse Derochie. All rights reserved.
// </copyright>
// <summary>JML quat class header file</summary>
// ***********************************************************************
#pragma once
#include "Jade_Primitives.h"
#include "vec3.h"
#include "vec4.h"

namespace jml
{
	class quat
	{
	public:
		/// <summary>
		/// Initializes a new instance of the <see cref="quat"/> class.
		/// </summary>
		quat() {}
		/// <summary>
		/// Initializes a new instance of the <see cref="quat"/> class.
		/// </summary>
		/// <param name="angle">The angle.</param>
		/// <param name="axis">The axis.</param>
		quat(JFloat angle, vec3 axis)
			: w(angle), v(axis) {}
		/// <summary>
		/// Initializes a new instance of the <see cref="quat"/> class.
		/// </summary>
		/// <param name="param">The parameter.</param>
		quat(vec4 param)
			: w(param.w), v(vec3(param.x, param.y, param.z)) {}
		/// <summary>
		/// Initializes a new instance of the <see cref="quat"/> class.
		/// </summary>
		/// <param name="wVal">The w value.</param>
		/// <param name="xVal">The x value.</param>
		/// <param name="yVal">The y value.</param>
		/// <param name="zVal">The z value.</param>
		quat(JFloat wVal, JFloat xVal, JFloat yVal, JFloat zVal)
			: w(wVal), v(vec3(xVal, yVal, zVal)) {}
		/// <summary>
		/// Initializes a new instance of the <see cref="quat"/> class.
		/// </summary>
		/// <param name="other">The other.</param>
		quat(const quat & other)
			: w(other.w), v(other.v) {}
		/// <summary>
		/// Finalizes an instance of the <see cref="quat"/> class.
		/// </summary>
		~quat() {}

		quat operator = (quat &param);
		JBool operator == (quat &param);
		JBool operator != (quat &param);
		quat operator + (quat &param);
		quat operator - (quat &param);
		quat operator * (quat &param);
		quat operator / (quat &param);
		quat operator * (JFloat param);
		quat operator / (JFloat param);
		quat operator - (void);
		quat operator += (quat &param);
		quat operator -= (quat &param);
		quat operator *= (quat &param);
		quat operator *= (JFloat param);
		quat operator /= (JFloat param);

		/// <summary>
		/// Return a Quaternion from euler angles.
		/// </summary>
		/// <param name="theta_z">The theta_z.</param>
		/// <param name="theta_y">The theta_y.</param>
		/// <param name="theta_x">The theta_x.</param>
		/// <returns></returns>
		quat QuaternionFromEulerAngles(JFloat theta_z, JFloat theta_y, JFloat theta_x);
		/// <summary>
		/// Return a Quaternion from euler angles.
		/// </summary>
		/// <param name="angles">The angles.</param>
		/// <returns></returns>
		quat QuaternionFromEulerAngles(const vec3 &angles);
		/// <summary>
		/// Returns the magnitude of the quaternion
		/// </summary>
		/// <returns></returns>
		JFloat Magnitude();
		/// <summary>
		/// Returns the quaternion squared
		/// </summary>
		/// <returns></returns>
		JFloat MagnitudeSquared();
		/// <summary>
		/// Normalizes this quaternion
		/// </summary>
		void Normalize();
		/// <summary>
		/// returns the normalized quaternion
		/// </summary>
		/// <returns></returns>
		quat GetNormalized();
		/// <summary>
		/// Conjugates the quaternion
		/// </summary>
		void Conjugate();
		/// <summary>
		/// Inverts this quaternion
		/// </summary>
		void Invert();
		/// <summary>
		/// returns the dot product between quaternions
		/// </summary>
		/// <param name="q">The q.</param>
		/// <returns></returns>
		JFloat Dot(quat &q);
		/// <summary>
		/// Lerps the quaternion
		/// </summary>
		/// <param name="q1">The q1.</param>
		/// <param name="q2">The q2.</param>
		/// <param name="t">The timestep.</param>
		/// <returns></returns>
		static quat Lerp(quat &q1, quat &q2, JFloat t);
		/// <summary>
		/// Slerps the quaternion
		/// </summary>
		/// <param name="q1">The q1.</param>
		/// <param name="q2">The q2.</param>
		/// <param name="t">The timestep.</param>
		/// <returns></returns>
		static quat Slerp(quat &q1, quat &q2, JFloat t);
		/// <summary>
		/// Slerps the quaternion without inverting it
		/// </summary>
		/// <param name="q1">The q1.</param>
		/// <param name="q2">The q2.</param>
		/// <param name="t">The timestep.</param>
		/// <returns></returns>
		static quat SlerpNoInvert(quat &q1, quat &q2, JFloat t);
		/// <summary>
		/// Squads the quaternion
		/// </summary>
		/// <param name="q1">The q1.</param>
		/// <param name="q2">The q2.</param>
		/// <param name="a">a.</param>
		/// <param name="b">The b.</param>
		/// <param name="t">The timestep.</param>
		/// <returns></returns>
		static quat Squad(quat &q1, quat &q2, quat &a, quat &b, JFloat t);
		/// <summary>
		/// Beziers the quaternion
		/// </summary>
		/// <param name="q1">The q1.</param>
		/// <param name="q2">The q2.</param>
		/// <param name="a">a.</param>
		/// <param name="b">The b.</param>
		/// <param name="t">The timestep.</param>
		/// <returns></returns>
		static quat Bezier(quat &q1, quat &q2, quat &a, quat &b, JFloat t);
		/// <summary>
		/// Returns a quaternion using axis and angle
		/// </summary>
		/// <param name="axis">The axis.</param>
		/// <param name="angle">The angle.</param>
		/// <returns></returns>
		static inline quat From_Axis_Angle(vec3 &axis, JFloat angle);
		/// <summary>
		/// creates a quaternion using axis and angle
		/// </summary>
		/// <param name="axis">The axis.</param>
		/// <param name="angle">The angle.</param>
		void To_Axis_Angle(vec3 &axis, JFloat angle);
		/// <summary>
		/// Rotates the vector
		/// </summary>
		/// <param name="v">The v.</param>
		/// <returns></returns>
		vec3 Rotate(vec3 &v);
		/// <summary>
		/// Return the Euler angles
		/// </summary>
		/// <param name="homogenous">The homogenous.</param>
		/// <returns></returns>
		vec3 Euler_Angles(JBool homogenous = true);

		/// <summary>
		/// The x, y and z (ijk) values of the quaternion
		/// the imaginary numbers 
		/// </summary>
		vec3 v;
		/// <summary>
		/// the w value of the quaternion
		/// the real number
		/// </summary>
		JFloat w;
	};

}