#pragma once
#include "Math\vec3.h"

class quat;

namespace jml
{

	class mat3
	{
	public:
		mat3() {}
		mat3(vec3 &param1, vec3 &param2, vec3 &param3)
			: column0(param1), column1(param2), column2(param3) {}
		mat3(quat &param);
		mat3(const mat3 &other)
			: column0(other.column0), column1(other.column1), column2(other.column2) {}


		~mat3();



		vec3 column0;
		vec3 column1;
		vec3 column2;
	};

}