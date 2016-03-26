#version 400

in vec3 ReflectDir;
in vec3 RefractDir;

uniform samplerCube CubeMapTex;

layout( location = 0 ) out vec4 FragColor;

void main() 
{
	// Access the cube map texture
	vec4 reflectColor = texture(CubeMapTex, ReflectDir);
	vec4 refractColor = texture(CubeMapTex, RefractDir);

	FragColor = mix(refractColor, reflectColor, 0.85);
}