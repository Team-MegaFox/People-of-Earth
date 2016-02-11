#version 120
attribute vec3 vertex;
attribute vec4 particlePosition;
attribute vec4 color;

varying vec2 texCoord0;
varying vec4 color0;

uniform mat4 T_MVP;
uniform vec3 C_up;
uniform vec3 C_right;

void main()
{
	float size = particlePosition.w;
	vec3 finalVertexPos = particlePosition.xyz + C_right * vertex.x * size + C_up * vertex.y * size;

    gl_Position = T_MVP * vec4(finalVertexPos, 1.0);
    texCoord0 = vertex.xy + vec2(0.5, 0.5);
	color0 = color;
}