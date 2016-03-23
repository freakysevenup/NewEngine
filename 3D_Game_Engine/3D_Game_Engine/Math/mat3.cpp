#include "mat3.h"
#include "JadeMath.h"

namespace jml
{
	mat3::mat3(quat &param)
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

		column0 = vec3(1.0f - yy - zz, xy + zw, xz - yw);
		column1 = vec3(xy - zw, 1.0f - xx - zz, yz + xw);
		column2 = vec3(xz + yw, yz - xw, 1.0f - xx - yy);
	}

	mat3 mat3::operator + (mat3 &param)
	{
		return mat3(column0 + param.column0, column1 + param.column1, column2 + param.column2);
	}

	mat3 mat3::operator += (mat3 &param)
	{
		return mat3(column0 += param.column0, column1 += param.column1, column2 += param.column2);
	}

	mat3 mat3::operator - (mat3 &param)
	{
		return mat3(column0 - param.column0, column1 - param.column1, column2 - param.column2);
	}

	mat3 mat3::operator -= (mat3 &param)
	{
		return mat3(column0 -= param.column0, column1 -= param.column1, column2 -= param.column2);
	}

	mat3 mat3::operator * (mat3 &param)
	{
		return mat3(column0 * param.column0, column1 * param.column1, column2 * param.column2);
	}

	mat3 mat3::operator *= (mat3 &param)
	{
		return mat3(column0 *= param.column0, column1 *= param.column1, column2 *= param.column2);
	}

	mat3 mat3::operator * (JFloat &param)
	{
		return mat3(column0 * param, column1 * param, column2 * param);
	}

	mat3 mat3::operator *= (JFloat &param)
	{
		return mat3(column0 *= param, column1 *= param, column2 *= param);
	}

	mat3 mat3::operator / (JFloat &param)
	{
		return mat3(column0 / param, column1 / param, column2 / param);
	}

	mat3 mat3::operator /= (JFloat &param)
	{
		return mat3(column0 /= param, column1 /= param, column2 /= param);
	}

	JBool mat3::operator == (mat3 &param)
	{
		return (column0 == param.column0 && column1 == param.column1 && column2 == param.column2) ? true : false;
	}

	JBool mat3::operator != (mat3 &param)
	{
		return (column0 != param.column0 && column1 != param.column1 && column2 != param.column2) ? true : false;
	}

	JFloat mat3::GetDeterminant()
	{
		return column0.Dot(column1.Cross(column2));
	}

	mat3 mat3::InvertMatrix()
	{
		const JFloat determinant = GetDeterminant();
		mat3 inverse;
		if (determinant != JFloat(0.0))
		{
			const JFloat inverseDeterminant = 1.0f / determinant;

			inverse.column0.x = inverseDeterminant * (column1.y * column2.z - column2.y * column1.z);
			inverse.column0.y = inverseDeterminant *-(column0.y * column2.z - column2.y * column0.z);
			inverse.column0.z = inverseDeterminant * (column0.y * column1.z - column0.z * column1.y);
								 
			inverse.column1.x = inverseDeterminant *-(column1.x * column2.z - column1.z * column2.x);
			inverse.column1.y = inverseDeterminant * (column0.x * column2.z - column0.z * column2.x);
			inverse.column1.z = inverseDeterminant *-(column0.x * column1.z - column0.z * column1.x);
								
			inverse.column2.x = inverseDeterminant * (column1.x * column2.y - column1.y * column2.x);
			inverse.column2.y = inverseDeterminant *-(column0.x * column2.y - column0.y * column2.x);
			inverse.column2.z = inverseDeterminant * (column0.x * column1.y - column1.x * column0.y);

			return inverse;
		}
		else
		{
			return CreateIdentity();
		}
	}

	mat3 mat3::TransposeMatrix()
	{
		return mat3(
			vec3(column0.x, column1.x, column2.x), 
			vec3(column0.y, column1.y, column2.y), 
			vec3(column0.z, column1.z, column2.z));
	}

	mat3 mat3::GetAdjunct()
	{
		mat3 temp(column0, column1, column2);

		temp.column1.x != 0.0f ? temp.column1.x *= -1 : temp.column1.x;		temp.column0.x != 0.0f ? temp.column0.x *= -1 : temp.column0.x;
		temp.column2.y != 0.0f ? temp.column2.y *= -1 : temp.column2.y;		temp.column1.z != 0.0f ? temp.column1.z *= -1 : temp.column1.z;

		return temp;
	}

	mat3 mat3::RotateMatrix(JFloat angle, JChar axis)
	{
		mat3 temp;

		if (axis == 'x' || axis == 'X')
		{
			//Rotate about the X axis when axis is equal to 1
			mat3 rotateByFloat(
				vec3(1.0f, 0.0f, 0.0f), 
				vec3(0.0f, j_Cos((angle * 3.141592653589793f) / 180.0f), j_Sin((angle * 3.141592653589793f) / 180.0f)),
				vec3(0.0f, -j_Sin((angle * 3.141592653589793f) / 180.0f), j_Cos((angle * 3.141592653589793f) / 180.0f)));

			temp = rotateByFloat;
			return temp;
		}

		if (axis == 'y' || axis == 'Y')
		{
			//Rotate about the Y axis when axis is equal to 2
			mat3 rotateByFloat(
				vec3(j_Cos((angle * 3.141592653589793f) / 180.0f), j_Sin((angle * 3.141592653589793f) / 180.0f), 0.0f), 
				vec3(-j_Sin((angle * 3.141592653589793f) / 180.0f), j_Cos((angle * 3.141592653589793f) / 180.0f), 0.0f), 
				vec3(0.0f, 0.0f, 1.0f));

			temp = rotateByFloat;
			return temp;
		}

		if (axis == 'z' || axis == 'Z')
		{
			//Rotate about the Z axis when axis is equal to 3
			mat3 rotateByFloat(
				vec3(j_Cos((angle * 3.141592653589793f) / 180.0f), 0.0f, -j_Sin((angle * 3.141592653589793f) / 180.0f)),
				vec3(0.0f, 1.0f, 0.0f),
				vec3(j_Sin((angle * 3.141592653589793f) / 180.0f), 0.0f, j_Cos((angle * 3.141592653589793f) / 180.0f)));
				
			temp = rotateByFloat;
			return temp;
		}

		return ((axis == 'x' || axis == 'X') || (axis == 'y' || axis == 'Y') || (axis == 'z' || axis == 'Z')) ? temp : CreateIdentity();
	}

	mat3 mat3::CreateDiagonalMatrix(vec3 &param)
	{
		return mat3(vec3(param.x, 0.0f, 0.0f), vec3(0.0f, param.y, 0.0f), vec3(0.0f, 0.0f, param.z));
	}

	mat3 mat3::CreateIdentity()
	{
		return mat3(JFloat(0.0));
	}
}