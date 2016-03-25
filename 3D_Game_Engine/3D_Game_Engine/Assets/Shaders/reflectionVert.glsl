#version 400
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textureCoord;

out vec3 ReflectDir; // The direction of the reflected ray

uniform bool DrawSkyBox; // Are we drawing the sky box?

uniform vec3 camPosition;

uniform mat4 model;

uniform mat4 view;

uniform mat4 projection;

void main()
{
	mat4 MVP = projection * view * model;

	if( DrawSkyBox )
	{
		ReflectDir = position;
	}
	else
	{
	// Compute the reflected direction in world coords.

	vec3 worldPos = vec3( model * vec4(position, 1.0));
	vec3 worldNorm = vec3( model * view * vec4(normal, 0.0));
	vec3 worldView = normalize( camPosition - worldPos );
	ReflectDir = reflect(-worldView, worldNorm);

	}
	gl_Position = MVP * vec4(position, 1.0);
}
