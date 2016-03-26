#version 400

in vec3 vertPos;

in vec3 ReflectDir; // The direction of the reflected ray
in vec3 RefractDir;
in vec3 normalInterp;

uniform samplerCube CubeMapTex; // The cube map

uniform bool DrawSkyBox; // Are we drawing the sky box?

uniform float ReflectFactor; // Amount of reflection

uniform vec3 lightPos;
const vec3 ambientColor = vec3(0.1, 0.1, 0.1); //Ambient Colour in the environment
const vec3 diffuseColor = vec3(1.0, 0.5, 0.5);
const vec3 specColor = vec3(1.0, 0.5, 0.0);
const float shininess = 4.0;
const float screenGamma = 1.2; // Assume the monitor is calibrated to the sRGB color space

layout( location = 0 ) out vec4 FragColor;

void main() 
{  
	// Access the cube map texture
	vec4 CubeMapColor = texture( CubeMapTex, ReflectDir );
	vec4 refractColor = texture( CubeMapTex, RefractDir );

	if( DrawSkyBox )
	{
		FragColor = CubeMapColor;
	}
	else
	{
		int mode = 0;
		vec3 norm = normalize(normalInterp);
		vec3 lightDir = normalize(lightPos - vertPos);

		float lambertian = max(dot(lightDir,norm), 0.0);
		float specular = 0.0;

		if(lambertian > 0.0) 
		{

			vec3 viewDir = normalize(-vertPos);

			// this is blinn phong
			vec3 halfDir = normalize(lightDir + viewDir);
			float specAngle = max(dot(halfDir, norm), 0.0);
			specular = pow(specAngle, shininess);
       
			// this is phong (for comparison)
			if(mode == 2) {
			 vec3 reflectDir = reflect(-lightDir, norm);
			specAngle = max(dot(reflectDir, viewDir), 0.0);
			// note that the exponent is different here
			specular = pow(specAngle, shininess/4.0);
		}
	}
	vec3 colorLinear = ambientColor + lambertian * diffuseColor + specular * specColor;
	// apply gamma correction (assume ambientColor, diffuseColor and specColor
	// have been linearized, i.e. have no gamma correction in them)
	vec3 colorGammaCorrected = pow(colorLinear, vec3(1.0/screenGamma));

		FragColor = mix(refractColor, CubeMapColor, ReflectFactor) * vec4(colorGammaCorrected, 1.0);
	}
}
