// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 03-23-2016
// Created For      : Jade Math Library
// Last Modified By : Jesse Derochie
// Last Modified On : 03-24-2016
// ***********************************************************************
// <copyright file="mat4.h">
//     Copyright (c) Jesse Derochie. All rights reserved.
// </copyright>
// <summary>JML mat4 class header file</summary>
// ***********************************************************************

/*
Matrix is column centric

   c   c   c   c
   o   o   o   o
   l   l   l   l
   u   u   u   u
   m   m   m   m
   n   n   n   n
   0   1   2   3
[ a.x b.x c.x d.x ]
[ a.y b.y c.y d.y ]
[ a.z b.z c.z d.z ]
[ a.w b.w c.w d.w ]

Vectors are treated as columns

[ x ]
[ y ]
[ z ]
[ w ]

*/
#pragma once
#include "Jade_Primitives.h"
#include "vec4.h"
#include "quat.h"
#include "mat3.h"

namespace jml
{
	class mat4
	{
	public:
		/// <summary>
		/// Initializes a new instance of the <see cref="mat4"/> class.
		/// </summary>
		mat4() {}
		/// <summary>
		/// Initializes a new instance of the <see cref="mat4"/> class.
		/// </summary>
		/// <param name="param1">The param1.</param>
		/// <param name="param2">The param2.</param>
		/// <param name="param3">The param3.</param>
		mat4(vec4 &param1, vec4 &param2, vec4 &param3, vec4 &param4)
			: column0(param1), column1(param2), column2(param3), column3(param4) {}
		/// <summary>
		/// Initializes a new instance of the <see cref="mat4"/> class.
		/// </summary>
		/// <param name="param">The parameter.</param>
		mat4(quat &param);
		/// <summary>
		/// Initializes a new instance of the <see cref="mat4"/> class.
		/// </summary>
		/// <param name="param">The parameter.</param>
		mat4(JFloat param)
			: column0(vec4(param)), column1(vec4(param)), column2(vec4(param)), column3(vec4(param)) {}
		/// <summary>
		/// Initializes a new instance of the <see cref="mat4"/> class.
		/// </summary>
		/// <param name="other">The other.</param>
		mat4(const mat4 &other)
			: column0(other.column0), column1(other.column1), column2(other.column2), column3(other.column3) {}
		/// <summary>
		/// Finalizes an instance of the <see cref="mat4"/> class.
		/// </summary>
		~mat4() {}

		mat4 operator - (void);
		vec4 operator [] (U_JInt num);
		JFloat operator () (U_JInt column, U_JInt row);
		mat4 operator + (mat4 &param);
		mat4 operator += (mat4 &param);
		mat4 operator - (mat4 &param);
		mat4 operator -= (mat4 &param);
		mat4 operator * (mat4 &param);
		mat4 operator *= (mat4 &param);
		mat4 operator * (JFloat &param);
		mat4 operator *= (JFloat &param);
		mat4 operator / (JFloat &param);
		mat4 operator /= (JFloat &param);
		JBool operator == (mat4 &param);
		JBool operator != (mat4 &param);

		/// <summary>
		/// Inverts the matrix.
		/// </summary>
		/// <returns></returns>
		mat4 InvertMatrix();
		/// <summary>
		/// Transposes the matrix.
		/// </summary>
		/// <returns></returns>
		mat4 TransposeMatrix();
		/// <summary>
		/// Gets the adjunct.
		/// </summary>
		/// <returns></returns>
		mat4 GetAdjunct();
		/// <summary>
		/// Rotates the matrix using this angle and axis
		/// </summary>
		/// <param name="angle">The angle.</param>
		/// <param name="axis">The axis.</param>
		/// <returns></returns>
		mat4 RotateMatrix(JFloat angle, JChar axis);
		/// <summary>
		/// Gets the determinant.
		/// </summary>
		/// <returns></returns>
		JFloat GetDeterminant();
		/// <summary>
		/// Creates the diagonal matrix.
		/// </summary>
		/// <param name="param">The parameter.</param>
		/// <returns></returns>
		mat4 CreateDiagonalMatrix(JFloat param);
		/// <summary>
		/// Creates the identity.
		/// </summary>
		/// <returns></returns>
		mat4 CreateIdentity();
		/// <summary>
		/// Transform vec4 by matrix
		/// </summary>
		/// <param name="param">The parameter.</param>
		/// <returns></returns>
		vec4 Transform(vec4 &param);
		/// <summary>
		/// Transform vec3 by matrix
		/// </summary>
		/// <param name="param">The parameter.</param>
		/// <returns></returns>
		vec3 Transform(vec3 &param);
		/// <summary>
		/// Get3x3s the determinant.
		/// </summary>
		/// <param name="basisVec"> The basis vector.</param>
		/// <param name="d1">The first 2x2 determinant.</param>
		/// <param name="d2">The second 2x2 determinant.</param>
		/// <param name="d3">The third 2x2 determinant.</param>
		/// <returns></returns>
		JFloat Get3x3Determinant(vec3 &basisVec, JFloat d1, JFloat d2, JFloat d3);
		/// <summary>
		/// Returns a minor matrix.
		/// Used for Getting 4x4 Determinant
		/// </summary>
		/// <param name="param">The parameter.</param>
		/// <returns></returns>
		mat3 GetMinorMatrix(U_JInt param);

		/// <summary>
		/// The first column
		/// </summary>
		vec4 column0;
		/// <summary>
		/// The second column
		/// </summary>
		vec4 column1;
		/// <summary>
		/// The third column
		/// </summary>
		vec4 column2;
		/// <summary>
		/// The fourth column
		/// </summary>
		vec4 column3;
	};

	namespace
	{
		mat4 operator * (JFloat param, mat4 vec)
		{
			return param * vec;
		}
		mat4 operator / (JFloat param, mat4 vec)
		{
			return param / vec;
		}
		mat4 operator *= (JFloat param, mat4 vec)
		{
			return param *= vec;
		}
		mat4 operator /= (JFloat param, mat4 vec)
		{
			return param /= vec;
		}
		vec4 operator * (vec4 &param1, mat4 &param2)
		{
			return vec4(
				param1.x * param2.column0.x + param1.x * param2.column0.y + param1.x * param2.column0.z + param1.x * param2.column0.w,
				param1.y * param2.column1.x + param1.y * param2.column1.y + param1.y * param2.column1.z + param1.y * param2.column1.w,
				param1.z * param2.column2.x + param1.z * param2.column2.y + param1.z * param2.column2.z + param1.z * param2.column2.w,
				param1.w * param2.column3.x + param1.w * param2.column3.y + param1.w * param2.column3.z + param1.w * param2.column3.w);
		}
	}
}