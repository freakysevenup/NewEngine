#version 120


varying vec3 worldVertexPosition;

varying vec3 worldNormalDirection;


uniform samplerCube cubeMap;

uniform vec3 camPosition;



void main()

{
	
	vec3 incident = normalize(worldVertexPosition - camPosition);
	
	vec3 normal = normalize(worldNormalDirection);
	
	vec3 reflected = reflect(incident, normal);
	
	gl_FragColor = textureCube(cubeMap, reflected);

}