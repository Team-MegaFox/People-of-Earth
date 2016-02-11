#version 120

varying vec2 texCoord;
varying vec4 particlecolor;

uniform sampler2D diffuse;

void main()
{
	gl_FragColor = texture2D(diffuse, texCoord) * particlecolor;
}