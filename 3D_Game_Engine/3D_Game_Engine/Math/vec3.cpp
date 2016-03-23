// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 03-23-2016
// Created For      : Jade Math Library
// Last Modified By : Jesse Derochie
// Last Modified On : 03-23-2016
// ***********************************************************************
// <copyright file="vec3.cpp">
//     Copyright (c) Jesse Derochie. All rights reserved.
// </copyright>
// <summary>JML vec3 class cpp file</summary>
// ***********************************************************************
#include "vec3.h"
#include "JadeMath.h"

namespace jml
{

	vec3 vec3::operator () (JFloat xVal, JFloat yVal, JFloat zVal)
	{
		x = xVal; y = yVal; z = zVal;
	}

	vec3 vec3::operator + (vec3 &param)
	{
		return vec3(x + param.x, y + param.y, z + param.z);
	}

	vec3 vec3::operator += (vec3 &param)
	{
		return vec3(x += param.x, y += param.y, z += param.z);
	}

	vec3 vec3::operator + (JFloat param)
	{
		return vec3(x + param, y + param, z + param);
	}

	vec3 vec3::operator += (JFloat param)
	{
		return vec3(x += param, y += param, z += param);
	}

	vec3 vec3::operator - (void)
	{
		return vec3(-x, -y, -z);
	}

	vec3 vec3::operator - (vec3 &param)
	{
		return vec3(x - param.x, y - param.y, z - param.z);
	}

	vec3 vec3::operator -= (vec3 &param)
	{
		return vec3(x -= param.x, y -= param.y, z -= param.z);
	}

	vec3 vec3::operator * (vec3 &param)
	{
		return vec3(x * param.x, y * param.y, z * param.z);
	}

	vec3 vec3::operator *= (vec3 &param)
	{
		return vec3(x *= param.x, y *= param.y, z *= param.z);
	}

	vec3 vec3::operator * (JFloat param)
	{
		return vec3(x * param, y * param, z * param);
	}

	vec3 vec3::operator *= (JFloat param)
	{
		return vec3(x *= param, y *= param, z *= param);
	}

	vec3 vec3::operator / (JFloat param)
	{
		return vec3(x / param, y / param, z / param);
	}

	vec3 vec3::operator /= (JFloat param)
	{
		return vec3(x /= param, y /= param, z /= param);
	}

	JBool vec3::operator == (vec3 &param)
	{
		return (x == param.x && y == param.y && z == param.z) ? true : false;
	}

	JBool vec3::operator != (vec3 &param)
	{
		return (x == param.x && y == param.y && z == param.z) ? false : true;
	}

	JBool vec3::operator < (vec3 &param)
	{
		return (j_Abs(x) < j_Abs(param.x) && j_Abs(y) < j_Abs(param.y) && j_Abs(z) < j_Abs(param.z)) ? true : false;
	}

	JBool vec3::operator > (vec3 &param)
	{
		return (j_Abs(x) > j_Abs(param.x) && j_Abs(y) > j_Abs(param.y) && j_Abs(z) > j_Abs(param.z)) ? true : false;
	}

	vec3 vec3::GetUnitVector()
	{
		JFloat temp = MagnitudeSquared();
		return temp > JFloat(0.0) ? *this * j_RecipricalSqrt(temp) : vec3(JFloat(0.0));
	}

	void vec3::Normalize()
	{
		if (Magnitude() > JFloat(0.0))
		{
			*this /= Magnitude();
		}
	}

	JFloat vec3::Dot(vec3 &param)
	{
		return (x * param.x) + (y * param.y) + (z * param.z);
	}

	JFloat vec3::Magnitude()
	{
		return j_Sqrt(MagnitudeSquared());
	}

	JFloat vec3::MagnitudeSquared()
	{
		return (x * x) + (y * y) + (z + z);
	}

	vec3 vec3::Cross(vec3 &param)
	{
		return vec3(y * param.z - z * param.y, z * param.x - x * param.z, x * param.y - y * param.x);
	}

	vec3 vec3::Minimum(vec3 &param)
	{
		return vec3(j_Min(x, param.x), j_Min(y, param.y), j_Min(z, param.z));
	}

	vec3 vec3::Maximum(vec3 &param)
	{
		return vec3(j_Max(x, param.x), j_Max(y, param.y), j_Max(z, param.z));
	}

	JFloat vec3::MinElement() const
	{
		return j_Min(x, j_Min(y, z));
	}

	JFloat vec3::MaxElement() const
	{
		return j_Max(x, j_Max(y, z));
	}

}