/*

Some clarifications, as there have been much confusion about matrix formats etc in the past.

Matrix is column centric

   c   c   c
   o   o   o
   l   l   l
   u   u   u
   m   m   m
   n   n   n
   0   1   2
[ a.x b.x c.x ]
[ a.y b.y c.y ]
[ a.z b.z c.z ]

Vectors are treated as columns, so the vector v is

[ x ]
[ y ]
[ z ]

*/

#pragma once
#include "vec3.h"
#include "quat.h"

namespace jml
{

	class mat3
	{
	public:
		/// <summary>
		/// Initializes a new instance of the <see cref="mat3"/> class.
		/// </summary>
		mat3() {}
		/// <summary>
		/// Initializes a new instance of the <see cref="mat3"/> class.
		/// </summary>
		/// <param name="param1">The param1.</param>
		/// <param name="param2">The param2.</param>
		/// <param name="param3">The param3.</param>
		mat3(vec3 &param1, vec3 &param2, vec3 &param3)
			: column0(param1), column1(param2), column2(param3) {}
		/// <summary>
		/// Initializes a new instance of the <see cref="mat3"/> class.
		/// </summary>
		/// <param name="param">The parameter.</param>
		mat3(quat &param);
		/// <summary>
		/// Initializes a new instance of the <see cref="mat3"/> class.
		/// </summary>
		/// <param name="param">The parameter.</param>
		mat3(JFloat param)
			: column0(vec3(param)), column1(vec3(param)), column2(vec3(param)) {}
		/// <summary>
		/// Initializes a new instance of the <see cref="mat3"/> class.
		/// </summary>
		/// <param name="other">The other.</param>
		mat3(const mat3 &other)
			: column0(other.column0), column1(other.column1), column2(other.column2) {}
		/// <summary>
		/// Finalizes an instance of the <see cref="mat3"/> class.
		/// </summary>
		~mat3() {}

		mat3 operator + (mat3 &param);
		mat3 operator += (mat3 &param);
		mat3 operator - (mat3 &param);
		mat3 operator -= (mat3 &param);
		mat3 operator * (mat3 &param);
		mat3 operator *= (mat3 &param);
		mat3 operator * (JFloat &param);
		mat3 operator *= (JFloat &param);
		mat3 operator / (JFloat &param);
		mat3 operator /= (JFloat &param);
		JBool operator == (mat3 &param);
		JBool operator != (mat3 &param);

		/// <summary>
		/// Inverts the matrix.
		/// </summary>
		/// <returns></returns>
		mat3 InvertMatrix();
		/// <summary>
		/// Transposes the matrix.
		/// </summary>
		/// <returns></returns>
		mat3 TransposeMatrix();
		/// <summary>
		/// Gets the adjunct.
		/// </summary>
		/// <returns></returns>
		mat3 GetAdjunct();
		/// <summary>
		/// Rotates the matrix using this angle and axis
		/// </summary>
		/// <param name="angle">The angle.</param>
		/// <param name="axis">The axis.</param>
		/// <returns></returns>
		mat3 RotateMatrix(JFloat angle, JChar axis);
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
		mat3 CreateDiagonalMatrix(vec3 &param);
		/// <summary>
		/// Creates the identity.
		/// </summary>
		/// <returns></returns>
		mat3 CreateIdentity();

		/// <summary>
		/// The column0
		/// </summary>
		vec3 column0;
		/// <summary>
		/// The column1
		/// </summary>
		vec3 column1;
		/// <summary>
		/// The column2
		/// </summary>
		vec3 column2;
	};

}