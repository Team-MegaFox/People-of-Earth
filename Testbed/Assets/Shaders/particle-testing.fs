#version 120
#include "sampling.glh"

varying vec2 texCoord0;
varying vec4 color0;

uniform vec3 R_ambient;
uniform sampler2D diffuse;

void main()
{
	gl_FragColor = texture2D(diffuse, texCoord0) *  color0 * vec4(R_ambient, 1);
}
