#pragma once
#include "Jade_Primitives.h"
#include "vec3.h"
#include "vec4.h"
//#include "mat3.h"
//#include "mat4.h"

class vec3;
class vec4;
class mat3;
class mat4;

namespace jml
{
	vec3 operator * (mat3 &param);
	vec4 operator * (mat4 &param);
}