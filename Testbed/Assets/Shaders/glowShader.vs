#version 120
attribute vec3 position;
attribute vec3 normal;
attribute vec2 texCoords;

uniform mat4 T_MVP;

varying vec2 texCoords0;

void main(void)
{
	gl_Position = (T_MVP * vec4(position, 1.0));
	texCoords0 = texCoords;
}