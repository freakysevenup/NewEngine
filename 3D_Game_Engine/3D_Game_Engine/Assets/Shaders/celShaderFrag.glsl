#version 330

in vec3 Position0;
in vec2 TexCoord;
in vec3 EyespaceNormal;
in vec3 Diffuse;

uniform vec3 lightPos;
uniform vec3 material_ambient;
uniform vec3 material_specular;
uniform float shininess;
uniform sampler2D tex;

layout( location = 0 ) out vec4 FragColor;

float stepmix( float edge0, float edge1, float E, float x )
{
    float T = clamp( 0.5 * ( x - edge0 ) / E, 0.0, 1.0 );
    return mix( edge0, edge1, T );
}

void main()
{
    vec3 N = normalize( EyespaceNormal );
    vec3 L = normalize( lightPos );
    vec3 Eye = vec3( 0, 0, 1 );
    vec3 H = normalize( L + Eye );
    
    float df = max( 0.0, dot( N, L ) );
    float sf = max( 0.0, dot( N, H ) );
    sf = pow( sf, shininess );

    const float A = 0.1;
    const float B = 0.3;
    const float C = 0.6;
    const float D = 1.0;
    float E = fwidth( df );

    if      ( df > A - E && df < A + E ) df = stepmix( A, B, E, df );
    else if ( df > B - E && df < B + E ) df = stepmix( B, C, E, df );
    else if ( df > C - E && df < C + E ) df = stepmix( C, D, E, df );
    else if ( df < A ) df = 0.0;
    else if ( df < B ) df = B;
    else if ( df < C ) df = C;
    else df = D;

    E = fwidth( sf );
    if ( sf > 0.5 - E && sf < 0.5 + E )
    {
        sf = smoothstep( 0.5 * ( sf - 0.5 + E ) / E, 0.0, 1.0 );
    }
    else
    {
        sf = step( 0.5, sf );
    }

    vec3 color = material_ambient + df * Diffuse + sf * material_specular;
    FragColor = vec4( color, 1.0 ) + texture(tex, TexCoord);
}




//#version 330
//
//in vec3 Position;
//in vec3 Normal; 
//in vec2 TexCoord;
//
//uniform vec3 camPosition;
//uniform vec3 lightPos;
//uniform sampler2D tex;
//
//
//layout( location = 0 ) out vec4 FragColor;
//
//void main (void)
//{
//
//	vec3 lightDir = lightPos - Position;
//
//	float intensity;
//	vec4 color;
//	vec3 n = normalize( Normal );
//
//	intensity = dot( lightPos, n );
//
//	if ( intensity > 0.95 )
//		color = vec4( 1.0, 0.5, 0.5, 1.0 );
//	else if ( intensity > 0.5 )
//		color = vec4( 0.6, 0.3, 0.3, 1.0 );
//	else if ( intensity > 0.25 )
//		color = vec4( 0.4, 0.2, 0.2, 1.0 );
//	else
//		color = vec4( 0.2, 0.1, 0.1, 1.0 );
//
//	FragColor = color;// + texture(tex, TexCoord);
//
//}