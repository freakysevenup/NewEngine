#version 130

precision mediump float; 

varying vec3 normalInterp;
varying vec3 vertPos;
varying vec2 textureCoords0;

uniform int mode;
uniform sampler2D texture;
uniform vec3 lightPos;

const vec3 ambientColor = vec3(0.1, 0.1, 0.1); //Ambient Colour in the environment
const vec3 diffuseColor = vec3(0.5, 0.5, 0.5);
const vec3 specColor = vec3(0.0, 0.5, 1.0);
const float shininess = 4.0;
const float screenGamma = 1.2; // Assume the monitor is calibrated to the sRGB color space

void main() {

  vec3 normal = normalize(normalInterp);
  vec3 lightDir = normalize(lightPos - vertPos);

  float lambertian = max(dot(lightDir,normal), 0.0);
  float specular = 0.0;

  if(lambertian > 0.0) {

    vec3 viewDir = normalize(-vertPos);

    // this is blinn phong
    vec3 halfDir = normalize(lightDir + viewDir);
    float specAngle = max(dot(halfDir, normal), 0.0);
    specular = pow(specAngle, shininess);
       
    // this is phong (for comparison)
    if(mode == 2) {
      vec3 reflectDir = reflect(-lightDir, normal);
      specAngle = max(dot(reflectDir, viewDir), 0.0);
      // note that the exponent is different here
      specular = pow(specAngle, shininess/4.0);
    }
  }
  vec3 colorLinear = ambientColor +
                     lambertian * diffuseColor +
                     specular * specColor;
  // apply gamma correction (assume ambientColor, diffuseColor and specColor
  // have been linearized, i.e. have no gamma correction in them)
  vec3 colorGammaCorrected = pow(colorLinear, vec3(1.0/screenGamma));
  // use the gamma corrected color in the fragment
  gl_FragColor = texture2D(texture, textureCoords0) * vec4(colorGammaCorrected, 1.0);
}