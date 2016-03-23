
/*

Some clarifications, as there have been much confusion about matrix formats etc in the past.

Short:
- Matrix have base vectors in columns (vectors are column matrices, 3x1 matrices).
- Matrix is physically stored in column major format
- Matrices are concaternated from left

Long:
Given three base vectors a, b and c the matrix is stored as

|a.x b.x c.x|
|a.y b.y c.y|
|a.z b.z c.z|

Vectors are treated as columns, so the vector v is

|x|
|y|
|z|

And matrices are applied _before_ the vector (pre-multiplication)
v' = M*v

|x'|   |a.x b.x c.x|   |x|   |a.x*x + b.x*y + c.x*z|
|y'| = |a.y b.y c.y| * |y| = |a.y*x + b.y*y + c.y*z|
|z'|   |a.z b.z c.z|   |z|   |a.z*x + b.z*y + c.z*z|


Physical storage and indexing:
To be compatible with popular 3d rendering APIs (read D3d and OpenGL)
the physical indexing is

|0 3 6|
|1 4 7|
|2 5 8|

index = column*3 + row

which in C++ translates to M[column][row]

The mathematical indexing is M_row,column and this is what is used for _-notation
so _12 is 1st row, second column and operator(row, column)

*/
#pragma once
#include "Math\vec3.h"

	class Matrix3x3
	{
	public:
		Matrix3x3(void);

		// A1 A2 A3
		// B1 B2 B3
		// C1 C2 C3
		Matrix3x3(float a_One, float a_Two, float a_Three, float b_One, float b_Two, float b_Three, float c_One, float c_Two, float c_Three);
		Matrix3x3(Vector3 _row1, Vector3 _row2, Vector3 _row3);
		~Matrix3x3(void);

		Matrix3x3 operator + (Matrix3x3 &param);
		Matrix3x3 operator += (Matrix3x3 &param);
		Matrix3x3 operator - (Matrix3x3 &param);
		Matrix3x3 operator -= (Matrix3x3 &param);
		Matrix3x3 operator * (Matrix3x3 &param);
		Matrix3x3 operator *= (Matrix3x3 &param);
		Matrix3x3 operator * (float &param);
		Matrix3x3 operator *= (float &param);
		Matrix3x3 operator / (float &param);
		Matrix3x3 operator /= (float &param);

		bool operator == (Matrix3x3 &param);
		bool operator != (Matrix3x3 &param);

		Matrix3x3 InvertMatrix();
		Matrix3x3 TransposeMatrix();
		Matrix3x3 GetAdjunct();
		Matrix3x3 RotateMatrix(float angle, char axis);
		float Get3x3Determinant(float _I11, float _D11, float _I12, float _D12, float _I13, float _D13);


	};