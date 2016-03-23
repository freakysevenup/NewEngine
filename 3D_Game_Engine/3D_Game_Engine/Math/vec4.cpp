// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 03-23-2016
// Created For      : Jade Math Library
// Last Modified By : Jesse Derochie
// Last Modified On : 03-23-2016
// ***********************************************************************
// <copyright file="vec4.cpp">
//     Copyright (c) Jesse Derochie. All rights reserved.
// </copyright>
// <summary>JML vec4 class cpp file</summary>
// ***********************************************************************
#include "vec4.h"
#include "JadeMath.h"

namespace jml
{
	JFloat & vec4::operator[](U_JInt i)
	{
		JFloat temp;
		if (i < 3)
		{
			temp = reinterpret_cast<JFloat*>(this)[i];
		}
		else
		{
			temp = JFloat(J_NIL);
		}
		return temp;
	}

	void vec4::operator () (float xVal, float yVal, float zVal, float wVal)
	{
		x = xVal; y = yVal; z = zVal; w = wVal;
	}

	bool vec4::operator == (vec4 &param)
	{
		return (x == param.x && y == param.y && z == param.z && w == param.w);
	}

	bool vec4::operator != (vec4 &param)
	{
		return (x != param.x || y != param.y || z != param.z || w != param.w);
	}

	vec4 vec4::operator = (vec4 &param)
	{
		return vec4(param);
	}

	vec4 vec4::operator - (void)
	{
		return vec4(-x, -y, -z, -w);
	}

	vec4 vec4::operator + (vec4 &param)
	{
		return vec4(x + param.x, y + param.y, z + param.z, w + param.w);
	}

	vec4 vec4::operator += (vec4 &param)
	{
		return vec4(x += param.x, y += param.y, z += param.z, w += param.w);
	}

	vec4 vec4::operator - (vec4 &param)
	{
		return vec4(x - param.x, y - param.y, z - param.z, w - param.w);
	}

	vec4 vec4::operator -= (vec4 &param)
	{
		return vec4(x -= param.x, y -= param.y, z -= param.z, w -= param.w);
	}

	float vec4::operator * (vec4 &param)
	{
		return x * param.x + y * param.y + z * param.z + w * param.w;
	}

	vec4 vec4::operator * (float param)
	{
		vec4 temp(*this);
		return temp *= param;
	}

	vec4 vec4::operator *= (float  param)
	{
		return vec4(x *= param, y *= param, z *= param, w *= param);
	}

	vec4 vec4::operator / (float param)
	{
		vec4 temp(*this);
		return temp /= param;
	}

	vec4 vec4::operator /= (float  param)
	{
		return vec4(x /= param, y /= param, z /= param, w /= param);
	}

	float vec4::MagnitudeSquared()
	{
		return (x * x) + (y * y) + (z * z) + (w * w);
	}

	float vec4::Magnitude()
	{
		return j_Sqrt(MagnitudeSquared());
	}

	vec4 vec4::GetUnitVector()
	{
		JFloat temp = MagnitudeSquared();
		return temp > JFloat(0.0) ? *this * j_RecipricalSqrt(temp) : vec4(JFloat(0.0));
	}

	vec4 vec4::Normalize()
	{
		JFloat temp = Magnitude();
		if (temp > JFloat(0.0))
		{
			*this /= temp;
		}
		return temp;
	}

	vec4 vec4::Minimum(vec4 &param)
	{
		return vec4(j_Min(x, param.x), j_Min(y, param.y), j_Min(z, param.z), j_Min(w, param.w));
	}

	vec4 vec4::Maximum(vec4 &param)
	{
		return vec4(j_Max(x, param.x), j_Max(y, param.y), j_Max(z, param.z), j_Max(w, param.w));
	}

	void vec4::Reflect(vec4 &param)
	{
		vec4 original(*this);
		Project(param);
		*this = *this * 2 - original;
	}

	void vec4::Project(vec4 &param)
	{
		*this = param * (*this * param) / (param * param);
	}

	vec4 vec4::Projected(vec4 &param)
	{
		return param * (*this * param) / (param * param);
	}

}