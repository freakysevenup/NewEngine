//#version 120
//
//
//varying vec3 worldVertexPosition;
//
//varying vec3 worldNormalDirection;
//
//
//uniform samplerCube cubeMap;
//
//uniform vec3 camPosition;
//
//
//
//void main()
//
//{
//	
//	vec3 incident = normalize(worldVertexPosition - camPosition);
//	
//	vec3 normal = normalize(worldNormalDirection);
//	
//	vec3 reflected = reflect(incident, normal);
//	
//	gl_FragColor = textureCube(cubeMap, reflected);
//
//}

#version 400

in vec3 pos_eye;
in vec3 n_eye;
uniform samplerCube cube_texture;
uniform mat4 view; // view matrix
out vec4 frag_colour;

void main () {
  /* reflect ray around normal from eye to surface */
  vec3 incident_eye = normalize (pos_eye);
  vec3 normal = normalize (n_eye);

  vec3 reflected = reflect (incident_eye, normal);
  // convert from eye to world space
  reflected = vec3 (inverse (view) * vec4 (reflected, 0.0));

  frag_colour = texture (cube_texture, reflected);
}