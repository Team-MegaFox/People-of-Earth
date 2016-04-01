#version 120
#include "sampling.glh"

varying vec2 texCoord0;
varying vec4 color0;

uniform vec4 R_ambient
uniform sampler2D diffuse;

void main()
{
    //Not actually using colour.
    vec4 color = color0;
	gl_FragColor = texture2D(diffuse, texCoord0) * R_ambient;
}
