// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 03-23-2016
// Created For      : Jade Math Library
// Last Modified By : Jesse Derochie
// Last Modified On : 03-23-2016
// ***********************************************************************
// <copyright file="vec2.cpp">
//     Copyright (c) Jesse Derochie. All rights reserved.
// </copyright>
// <summary>JML vec2 class cpp file</summary>
// ***********************************************************************
#include "vec2.h"
#include "JadeMath.h"

namespace jml
{
	vec2 vec2::operator () (JFloat xVal, JFloat yVal)
	{
		return vec2(x = xVal, y = yVal);
	}

	vec2 vec2::operator + (vec2 &param)
	{
		return vec2(x + param.x, y + param.y);
	}

	vec2 vec2::operator += (vec2 &param)
	{
		return vec2(x += param.x, y += param.y);
	}

	vec2 vec2::operator + (JFloat param)
	{
		return vec2(x + param, y + param);
	}

	vec2 vec2::operator += (JFloat param)
	{
		return vec2(x += param, y += param);
	}

	vec2 vec2::operator - (void)
	{
		return vec2(-x, -y);
	}

	vec2 vec2::operator - (vec2 &param)
	{
		return vec2(x - param.x, y - param.y);
	}

	vec2 vec2::operator -= (vec2 &param)
	{
		return vec2(x -= param.x, y -= param.y);
	}

	vec2 vec2::operator * (vec2 &param)
	{
		return vec2(x * param.x, y * param.y);
	}

	vec2 vec2::operator *= (vec2 &param)
	{
		return vec2(x *= param.x, y *= param.y);
	}

	vec2 vec2::operator * (JFloat param)
	{
		return vec2(x * param, y * param);
	}

	vec2 vec2::operator *= (JFloat param)
	{
		return vec2(x *= param, y *= param);
	}

	vec2 vec2::operator / (JFloat param)
	{
		return vec2(x / param, y / param);
	}

	vec2 vec2::operator /= (JFloat param)
	{
		return vec2(x /= param, y /= param);
	}

	bool vec2::operator == (vec2 &param)
	{
		return (x == param.x && y == param.y) ? true : false;
	}

	bool vec2::operator != (vec2 &param)
	{
		return (x == param.x && y == param.y) ? false : true;
	}

	bool vec2::operator < (vec2 &param)
	{
		return (j_Abs(x) < j_Abs(param.x) && j_Abs(y) < j_Abs(param.y)) ? true : false;
	}

	bool vec2::operator > (vec2 &param)
	{
		return (j_Abs(x) > j_Abs(param.x) && j_Abs(y) > j_Abs(param.y)) ? true : false;
	}

	vec2 vec2::GetUnitVector()
	{
		JFloat temp = MagnitudeSquared();
		return temp > JFloat(0.0) ? *this * j_RecipricalSqrt(temp) : vec2(JFloat(0.0));
	}

	void vec2::Normalize()
	{
		if (Magnitude() > JFloat(0.0))
		{
			*this /= Magnitude();
		}
	}

	JFloat vec2::Magnitude()
	{
		return j_Sqrt(MagnitudeSquared());
	}

	JFloat vec2::MagnitudeSquared()
	{
		return (x * x) + (y * y);
	}

	void vec2::RotateVector(JFloat _angle)
	{
		JFloat tempX = x;
		JFloat tempY = y;
		x = tempX * j_Cos(_angle) - tempY * j_Sin(_angle);
		y = tempX * j_Sin(_angle) + tempY * j_Cos(_angle);
	}

	JFloat vec2::Dot(vec2 & _passed)
	{
		return ((_passed.x * x) + (_passed.y * y));
	}

}