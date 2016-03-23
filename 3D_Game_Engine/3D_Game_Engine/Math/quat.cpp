// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 03-23-2016
// Created For      : Jade Math Library
// Last Modified By : Jesse Derochie
// Last Modified On : 03-23-2016
// ***********************************************************************
// <copyright file="quat.cpp">
//     Copyright (c) Jesse Derochie. All rights reserved.
// </copyright>
// <summary>JML quaternion class cpp file</summary>
// ***********************************************************************
#include "quat.h"
#include "Math\JadeMath.h"

namespace jml
{

	quat quat::operator = (quat &param)
	{
		return quat(param);
	}

	JBool quat::operator == (quat &param)
	{
		return (w == param.w && v == param.v) ? true : false;
	}

	JBool quat::operator != (quat &param)
	{
		return (w != param.w && v != param.v) ? true : false;
	}

	quat quat::operator + (quat &param)
	{
		return quat(w + param.w, v + param.v);
	}

	quat quat::operator - (quat &param)
	{
		return quat(w - param.w, v - param.v);
	}

	quat quat::operator * (quat &param)
	{
		return quat(
			w * param.w - v.x * param.v.x + v.y * param.v.y + v.z * param.v.z,		// w
			v.y * param.v.z - v.z * param.v.y + w * param.v.x + v.x * param.w,		// x
			v.z * param.v.x - v.x * param.v.z + w * param.v.y + v.y * param.w,		// y
			v.x * param.v.y - v.y * param.v.x + w * param.v.z + v.z * param.w);		// z
	}

	quat quat::operator / (quat &param)
	{
		quat p(param);
		p.Invert();
		return *this * p;
	}

	quat quat::operator * (JFloat param)
	{
		return quat(w * param, v * param);
	}

	quat quat::operator / (JFloat param)
	{
		return quat(w / param, v / param);
	}

	quat quat::operator - (void)
	{
		return quat(-w, -v);
	}

	quat quat::operator += (quat &param)
	{
		return quat(w += param.w, v += param.v);
	}

	quat quat::operator -= (quat &param)
	{
		return quat(w -= param.w, v -= param.v);
	}

	quat quat::operator *= (quat &param)
	{
		return quat(w *= param.w, v *= param.v);
	}

	quat quat::operator *= (JFloat param)
	{
		return quat(w *= param, v *= param);
	}

	quat quat::operator /= (JFloat param)
	{
		return quat(w /= param, v /= param);
	}

	quat quat::QuaternionFromEulerAngles(JFloat theta_z, JFloat theta_y, JFloat theta_x)
	{
		JFloat cos_z_2 = j_Cos(0.5f * theta_z);
		JFloat cos_y_2 = j_Cos(0.5f * theta_y);
		JFloat cos_x_2 = j_Cos(0.5f * theta_x);

		JFloat sin_z_2 = j_Sin(0.5f * theta_z);
		JFloat sin_y_2 = j_Sin(0.5f * theta_y);
		JFloat sin_x_2 = j_Sin(0.5f * theta_x);

		// and now compute quaternion
		return quat(
			cos_z_2 * cos_y_2 * cos_x_2 + sin_z_2 * sin_y_2 * sin_x_2,  //w
			cos_z_2 * cos_y_2 * sin_x_2 - sin_z_2 * sin_y_2 * cos_x_2,  //x
			cos_z_2 * sin_y_2 * cos_x_2 + sin_z_2 * cos_y_2 * sin_x_2,  //y
			sin_z_2 * cos_y_2 * cos_x_2 - cos_z_2 * sin_y_2 * sin_x_2); //z
	}

	quat quat::QuaternionFromEulerAngles(const vec3 &angles)
	{
		return QuaternionFromEulerAngles(angles.z, angles.y, angles.x);
	}

	JFloat quat::Magnitude()
	{
		return j_Sqrt(MagnitudeSquared());
	}

	JFloat quat::MagnitudeSquared()
	{
		return w * w + v.x * v.x + v.y * v.y + v.z * v.z;
	}

	void quat::Normalize()
	{
		if (Magnitude() > JFloat(0.0))
		{
			w *= Magnitude();
			v.x *= Magnitude();
			v.y *= Magnitude();
			v.z *= Magnitude();
		}
	}

	quat quat::GetNormalized()
	{
		const JFloat s = 1.0f / Magnitude();
		return quat(w * s, v.x * s, v.y * s, v.z * s);
	}

	void quat::Conjugate()
	{
		v = v * -1.0f;
	}

	void quat::Invert()
	{
		Conjugate();
		*this /= MagnitudeSquared();
	}

	JFloat quat::Dot(quat &q)
	{
		return (v.Dot(q.v)) + (w * q.w);
	}

	quat quat::Lerp(quat &q1, quat &q2, JFloat t)
	{
		return (q1 * (1 - t) + q2 * t).GetNormalized();
	}

	quat quat::Slerp(quat &q1, quat &q2, JFloat t)
	{
		quat q3;
		float dot = q1.Dot(q2);

		/*	dot = cos(theta)
		if (dot < 0), q1 and q2 are more than 90 degrees apart,
		so we can invert one to reduce spinning	*/
		if (dot < 0)
		{
			dot = -dot;
			q3 = -q2;
		}
		else q3 = q2;

		if (dot < 0.95f)
		{
			float angle = j_ACos(dot);
			return (q1 * j_Sin(angle * (1 - t)) + q3 * j_Sin(angle * t)) / j_Sin(angle);
		}
		else // if the angle is small, use linear interpolation								
			return Lerp(q1, q3, t);
	}

	quat quat::SlerpNoInvert(quat &q1, quat &q2, JFloat t)
	{
		float dot = q1.Dot(q2);
		if (dot > -0.95f && dot < 0.95f)
		{
			float angle = j_ACos(dot);
			return (q1 * j_Sin(angle * (1 - t)) + q2 * j_Sin(angle * t)) / j_Sin(angle);
		}
		else  // if the angle is small, use linear interpolation								
			return Lerp(q1, q2, t);
	}

	quat quat::Squad(quat &q1, quat &q2, quat &a, quat &b, JFloat t)
	{
		quat c = SlerpNoInvert(q1, q2, t), d = SlerpNoInvert(a, b, t);
		return SlerpNoInvert(c, d, 2 * t * (1 - t));
	}

	quat quat::Bezier(quat &q1, quat &q2, quat &a, quat &b, JFloat t)
	{
		quat q11 = SlerpNoInvert(q1, a, t), q12 = SlerpNoInvert(a, b, t), q13 = SlerpNoInvert(b, q2, t);
		return SlerpNoInvert(SlerpNoInvert(q11, q12, t), SlerpNoInvert(q12, q13, t), t);
	}

	inline quat quat::From_Axis_Angle(vec3 &axis, JFloat angle)
	{
		return quat(j_Cos(angle / 2.0f), axis * j_Sin(angle / 2.0f));
	}

	void quat::To_Axis_Angle(vec3 &axis, JFloat angle)
	{
		angle = j_ACos(w);

		// pre-compute to save time
		float sinf_theta_inv = 1.0f / j_Sin(angle);

		// now the vector
		axis.x = v.x * sinf_theta_inv;
		axis.y = v.y * sinf_theta_inv;
		axis.z = v.z * sinf_theta_inv;

		// multiply by 2
		angle *= 2.0f;
	}

	vec3 quat::Rotate(vec3 &v)
	{
		quat V(0.0f, v);
		quat conjugate(*this);
		conjugate.Conjugate();
		return (*this * V * conjugate).v;
	}

	vec3 quat::Euler_Angles(JBool homogenous = true)
	{
		float sqw = w * w;
		float sqx = v.x * v.x;
		float sqy = v.y * v.y;
		float sqz = v.z * v.z;

		vec3 euler;
		if (homogenous) {
			euler.x = j_ATan2(2.f * (v.x * v.y + v.z * w), sqx - sqy - sqz + sqw);
			euler.y = j_ASin(-2.f * (v.x * v.z - v.y * w));
			euler.z = j_ATan2(2.f * (v.y * v.z + v.x * w), -sqx - sqy + sqz + sqw);
		}
		else {
			euler.x = j_ATan2(2.f * (v.z * v.y + v.x * w), 1 - 2 * (sqx + sqy));
			euler.y = j_ASin(-2.f * (v.x * v.z - v.y * w));
			euler.z = j_ATan2(2.f * (v.x * v.y + v.z * w), 1 - 2 * (sqy + sqz));
		}
		return euler;
	}


}
