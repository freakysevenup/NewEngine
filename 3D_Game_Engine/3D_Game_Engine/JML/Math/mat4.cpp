// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 03-23-2016
// Created For      : Jade Math Library
// Last Modified By : Jesse Derochie
// Last Modified On : 03-23-2016
// ***********************************************************************
// <copyright file="mat4.cpp">
//     Copyright (c) Jesse Derochie. All rights reserved.
// </copyright>
// <summary>JML mat4 class cpp file</summary>
// ***********************************************************************

#include "mat4.h"
#include "JadeMath.h"

namespace jml
{

	mat4::mat4(quat &param)
	{
		const JFloat x = param.v.x;
		const JFloat y = param.v.y;
		const JFloat z = param.v.z;
		const JFloat w = param.w;

		const JFloat x2 = x + x;
		const JFloat y2 = y + y;
		const JFloat z2 = z + z;

		const JFloat xx = x2*x;
		const JFloat yy = y2*y;
		const JFloat zz = z2*z;

		const JFloat xy = x2*y;
		const JFloat xz = x2*z;
		const JFloat xw = x2*w;

		const JFloat yz = y2*z;
		const JFloat yw = y2*w;
		const JFloat zw = z2*w;

		column0 = vec4(1.0f - yy - zz, xy + zw, xz - yw, 0.0f);
		column1 = vec4(xy - zw, 1.0f - xx - zz, yz + xw, 0.0f);
		column2 = vec4(xz + yw, yz - xw, 1.0f - xx - yy, 0.0f);
		column3 = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}

	mat4 mat4::operator - (void)
	{
		return mat4(-column0, -column1, -column2, -column3);
	}

	vec4 mat4::operator [] (U_JInt num) 
	{ 
		return (&column0)[num]; 
	}

	JFloat mat4::operator () (U_JInt row, U_JInt column)
	{
		return (*this)[column][row];
	}

	mat4 mat4::operator + (mat4 &param)
	{
		return mat4(column0 + param.column0, column1 + param.column1, column2 + param.column2, column3 + param.column3);
	}
	mat4 mat4::operator += (mat4 &param)
	{
		return mat4(column0 += param.column0, column1 += param.column1, column2 += param.column2, column3 += param.column3);
	}

	mat4 mat4::operator - (mat4 &param)
	{
		return mat4(column0 - param.column0, column1 - param.column1, column2 - param.column2, column3 - param.column3);
	}

	mat4 mat4::operator -= (mat4 &param)
	{
		return mat4(column0 -= param.column0, column1 -= param.column1, column2 -= param.column2, column3 -= param.column3);
	}

	mat4 mat4::operator * (mat4 &param)
	{
		return mat4(Transform(param.column0), Transform(param.column1), Transform(param.column2), Transform(param.column3));
	}

	mat4 mat4::operator *= (mat4 &param)
	{
		return (*this * param);
	}

	mat4 mat4::operator * (JFloat &param)
	{
		return mat4(column0 * param, column1 * param, column2 * param, column3 * param);
	}

	mat4 mat4::operator *= (JFloat &param)
	{
		return mat4(column0 *= param, column1 *= param, column2 *= param, column3 *= param);
	}

	mat4 mat4::operator / (JFloat &param)
	{
		return mat4(column0 / param, column1 / param, column2 / param, column3 / param);
	}

	mat4 mat4::operator /= (JFloat &param)
	{
		return mat4(column0 /= param, column1 /= param, column2 /= param, column3 /= param);
	}

	JBool mat4::operator == (mat4 &param)
	{
		return (column0 == param.column0, column1 == param.column1, column2 == param.column2, column3 == param.column3);
	}

	JBool mat4::operator != (mat4 &param)
	{
		return (column0 != param.column0, column1 != param.column1, column2 != param.column2, column3 != param.column3);
	}

	mat4 mat4::InvertMatrix()
	{
		return (1.0 / GetDeterminant()) * GetAdjunct();
	}

	mat4 mat4::TransposeMatrix()
	{
		return mat4(
			vec4(column0.x, column1.x, column2.x, column3.x),
			vec4(column0.y, column1.y, column2.y, column3.y),
			vec4(column0.z, column1.z, column2.z, column3.z),
			vec4(column0.w, column1.w, column2.w, column3.w));
	}

	mat4 mat4::GetAdjunct()
	{
		mat4 temp(column0, column1, column2, column3);

		temp.column0.y != 0.0f ? temp.column0.y *= -1 : temp.column0.y;
		temp.column0.w != 0.0f ? temp.column0.w *= -1 : temp.column0.w;
		temp.column1.x != 0.0f ? temp.column1.x *= -1 : temp.column1.x;
		temp.column1.z != 0.0f ? temp.column1.z *= -1 : temp.column1.z;
		temp.column2.y != 0.0f ? temp.column2.y *= -1 : temp.column2.y;
		temp.column2.w != 0.0f ? temp.column2.w *= -1 : temp.column2.w;
		temp.column3.x != 0.0f ? temp.column3.x *= -1 : temp.column3.x;
		temp.column3.z != 0.0f ? temp.column3.z *= -1 : temp.column3.z;

		return temp;
	}

	mat4 mat4::RotateMatrix(JFloat angle, JChar axis)
	{
		mat4 temp;

		if (axis == 'x' || axis == 'X')
		{
			//Rotate about the X axis when axis is equal to 1
			mat4 rotateByFloat(
				vec4(1.0f, 0.0f, 0.0f, 0.0f),
				vec4(0.0f, j_Cos((angle * 3.141592653589793f) / 180.0f), j_Sin((angle * 3.141592653589793f) / 180.0f), 0.0f),
				vec4(0.0f, -j_Sin((angle * 3.141592653589793f) / 180.0f), j_Cos((angle * 3.141592653589793f) / 180.0f), 0.0f),
				vec4(0.0f, 0.0f, 0.0f, 1.0f));

			temp = rotateByFloat;
			return temp;
		}

		if (axis == 'y' || axis == 'Y')
		{
			//Rotate about the Y axis when axis is equal to 2
			mat4 rotateByFloat(
				vec4(j_Cos((angle * 3.141592653589793f) / 180.0f), 0.0f, j_Sin((angle * 3.141592653589793f) / 180.0f), 0.0f),
				vec4(0.0f, 1.0f, 0.0f, 0.0f),
				vec4(-j_Sin((angle * 3.141592653589793f) / 180.0f), 0.0f, j_Cos((angle * 3.141592653589793f) / 180.0f), 0.0f),
				vec4(0.0f, 0.0f, 0.0f, 1.0f));

			temp = rotateByFloat;
			return temp;
		}

		if (axis == 'z' || axis == 'Z')
		{
			//Rotate about the Z axis when axis is equal to 3
			mat4 rotateByFloat(
				vec4(j_Cos((angle * 3.141592653589793f) / 180.0f), -j_Sin((angle * 3.141592653589793f) / 180.0f), 0.0f, 0.0f),
				vec4(j_Sin((angle * 3.141592653589793f) / 180.0f), j_Cos((angle * 3.141592653589793f) / 180.0f), 0.0f, 0.0f),
				vec4(0.0f, 0.0f, 1.0f, 0.0f),
				vec4(0.0f, 0.0f, 0.0f, 1.0f));

			temp = rotateByFloat;
			return temp;
		}

		return ((axis == 'x' || axis == 'X') || (axis == 'y' || axis == 'Y') || (axis == 'z' || axis == 'Z')) ? temp : CreateIdentity();
	}

	JFloat mat4::Get3x3Determinant(vec3 &basisVec, JFloat d1, JFloat d2, JFloat d3)
	{
		return ((basisVec.x * d1) - (basisVec.y * d2) + (basisVec.z * d3));
	}

	mat3 mat4::GetMinorMatrix(U_JInt param)
	{
		switch (param)
		{
		case 1:
			return mat3(
				vec3(column1.y, column1.z, column1.w), 
				vec3(column2.y, column2.z, column2.w), 
				vec3(column3.y, column3.z, column3.w));
		case 2:
			return mat3(
				vec3(column1.x, column1.z, column1.w), 
				vec3(column2.x, column2.z, column2.w), 
				vec3(column3.x, column3.z, column3.w));
		case 3:
			return mat3(
				vec3(column1.x, column1.y, column1.w), 
				vec3(column2.x, column2.y, column2.w), 
				vec3(column3.x, column3.y, column3.w));
		case 4:
			return mat3(
				vec3(column1.GetXYZ()), 
				vec3(column2.GetXYZ()), 
				vec3(column3.GetXYZ()));
		case 5:
			return mat3(
				vec3(column0.y, column0.z, column0.w), 
				vec3(column2.y, column2.z, column2.w), 
				vec3(column3.y, column3.z, column3.w));
		case 6:
			return mat3(
				vec3(column0.x, column0.z, column0.w), 
				vec3(column2.x, column2.z, column2.w), 
				vec3(column3.x, column3.z, column3.w));
		case 7:
			return mat3(
				vec3(column0.x, column0.y, column0.w), 
				vec3(column2.x, column2.y, column2.w), 
				vec3(column3.x, column3.y, column3.w));
		case 8:
			return mat3(
				vec3(column0.GetXYZ()), 
				vec3(column2.GetXYZ()), 
				vec3(column3.GetXYZ()));
		case 9:
			return mat3(
				vec3(column0.y, column0.z, column0.w), 
				vec3(column1.y, column1.z, column1.w), 
				vec3(column3.y, column3.z, column3.w));
		case 10:
			return mat3(
				vec3(column0.x, column0.z, column0.w), 
				vec3(column1.x, column1.z, column1.w), 
				vec3(column3.x, column3.z, column3.w));
		case 11:
			return mat3(
				vec3(column0.x, column0.y, column0.w), 
				vec3(column1.x, column1.y, column1.w), 
				vec3(column3.x, column3.y, column3.w));
		case 12:
			return mat3(
				vec3(column0.GetXYZ()), 
				vec3(column1.GetXYZ()), 
				vec3(column3.GetXYZ()));
		case 13:
			return mat3(
				vec3(column0.y, column0.z, column0.w), 
				vec3(column1.y, column1.z, column1.w), 
				vec3(column2.y, column2.z, column2.w));
		case 14:
			return mat3(
				vec3(column0.x, column0.z, column0.w), 
				vec3(column1.x, column1.z, column1.w), 
				vec3(column2.x, column2.z, column2.w));
		case 15:
			return mat3(
				vec3(column0.x, column0.y, column0.w), 
				vec3(column1.x, column1.y, column1.w), 
				vec3(column2.x, column2.y, column2.w));
		case 16:
			return mat3(
				vec3(column0.GetXYZ()), 
				vec3(column1.GetXYZ()), 
				vec3(column2.GetXYZ()));
		}
	}

	JFloat mat4::GetDeterminant()
	{
		JFloat Determinant = 0.0f;
		U_JInt counter = 0;

		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 4; j++)
			{
				counter++;
				mat3 temp = GetMinorMatrix(counter);

				JFloat d1 = (column1.y * column2.z) - (column2.y * column1.z);
				JFloat d2 = (column1.x * column2.z) - (column2.x * column1.z);
				JFloat d3 = (column1.x * column2.y) - (column2.x * column1.y);
				Determinant += Get3x3Determinant(temp.column0, d1, d2, d3);
			}
		}

		return Determinant;
	}

	mat4 mat4::CreateDiagonalMatrix(JFloat param)
	{
		return mat4(
			vec4(param, 0.0, 0.0, 0.0), 
			vec4(0.0, param, 0.0, 0.0), 
			vec4(0.0, 0.0, param, 0.0), 
			vec4(0.0, 0.0, 0.0, param));
	}

	mat4 mat4::CreateIdentity()
	{
		return mat4(CreateDiagonalMatrix(1.0));
	}

	vec4 mat4::Transform(vec4 &param)
	{
		return column0 * param.x + column1 * param.y + column2 * param.z + column3 * param.w;
	}

	vec3 mat4::Transform(vec3 &param)
	{
		return Transform(vec4(param, 1.0f)).GetXYZ();
	}

}