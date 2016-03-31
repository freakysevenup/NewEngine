#version 400
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;			// Switch normal and textureCoord positions for cloaking effect
layout (location = 2) in vec2 textureCoord;

out vec3 ReflectDir; // The direction of the reflected ray
out vec3 RefractDir;
out vec3 normalInterp;
out vec3 vertPos;

uniform float counter;

uniform bool DrawSkyBox; // Are we drawing the sky box?

uniform vec3 camPosition;

uniform mat4 model;

uniform mat4 view;

uniform mat4 projection;

void main()
{
	mat4 MVP = projection * view * model;
	vertPos = position;
	vec3 positionOfVertex = position;

	if( DrawSkyBox )
	{
		ReflectDir = position;
		gl_Position = MVP * vec4( positionOfVertex, 1.0 );
	}
	else
	{
		mat4 normalMat = transpose( inverse( view * model ) );
		normalInterp = vec3(normalMat * vec4(normal, 0.0));

		// Compute the reflected direction in world coords.

		vec3 worldPos = vec3( model * vec4( position, 1.0 ) );
		vec3 worldNorm = vec3( model * view * vec4(normal, 0.0 ) );
		vec3 worldView = normalize( camPosition - worldPos );

		ReflectDir = reflect( -worldView, worldNorm );
		RefractDir = refract( -worldView, worldNorm, 0.44 );
		gl_Position = MVP * vec4((vec3(
		(positionOfVertex.x) + abs(cos(positionOfVertex.x + counter)), 
		(positionOfVertex.y) + abs(cos(positionOfVertex.y + counter)), 
		(positionOfVertex.z) + abs(cos(positionOfVertex.z + counter)) * (ReflectDir/RefractDir))
		), 1.0 );
	}

}
