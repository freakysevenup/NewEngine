#pragma once
#include <string>
#include <GLM/glm.hpp>

#include "../Rendering/Transform.h"
#include "../Rendering/Material.h"
#include "Camera3D.h"

using namespace glm;

class Shader
{
public:
	Shader(const std::string & name);
	virtual ~Shader();

	virtual void updateUniforms(const Transform& transform, const Material& material, const Camera3D& camera);

	// Uniform Setters
	void setUniformBool(const std::string& uniformName, bool value);
	void setUniformi(const std::string& uniformName, int value);
	void setUniformf(const std::string& uniformName, float value);
	void setUniformMat4(const std::string& uniformName, mat4 value);
	void setUniformMat3(const std::string& uniformName, mat3 value);
	void setUniformVec3(const std::string& uniformName, vec3 value);
	void setUniformVec4(const std::string& uniformName, vec4 value);

private:
	std::string m_name;
};

