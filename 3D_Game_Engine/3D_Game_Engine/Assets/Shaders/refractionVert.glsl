#version 400

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 ReflectDir;			// Reflected direction
out vec3 RefractDir;			// Transmitted direction

uniform vec3 camPosition;
uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
	mat4 MVP = projection * view * model;

	vec3 worldPos = vec3(model * vec4(position, 1.0));
	vec3 worldNorm = vec3(model * vec4(normal, 0.0));
	vec3 worldView = normalize(camPosition - worldPos);

	ReflectDir = reflect(-worldView, worldNorm);
	RefractDir = refract(-worldView, worldNorm, 0.85);

	gl_Position = MVP * vec4(position, 1.0);
}