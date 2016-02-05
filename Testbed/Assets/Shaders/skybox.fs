#version 120
varying vec3 texCoord;

uniform samplerCube S_skybox;

void main()
{    
    gl_FragColor = texture(S_skybox, texCoord);
}