#version 120

varying vec2 textureCoords0;
varying vec3 normal0;

uniform sampler2D mySampler;

void main(void)
{
	gl_FragColor = texture2D(mySampler, -textureCoords0);
}