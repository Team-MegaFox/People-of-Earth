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
	if(vertex.x > 0)
	{
		texCoord0.x = 1.0;
	}
	else
	{
		texCoord0.x = 0.0;
	}
	if(vertex.y > 0)
	{
		texCoord0.y = 1.0;
	}
	else
	{
		texCoord0.y = 0.0;
	}
	
	float size = particlePosition.w;
	vec3 finalVertexPos = particlePosition.xyz + C_right * vertex.x * size + C_up * vertex.y * size;

	float angle = 180.0 * 3.14159265359 / 180.0;
	mat4 rotateToFaceYou = mat4(
	cos(angle), 0, sin(angle), 0.0,
	0.0, 1.0, 0.0, 0.0,
	-sin(angle), 0.0, cos(angle), 0.0,
	0.0, 0.0, 0.0, 1.0);
	
    gl_Position = T_MVP * rotateToFaceYou * vec4(finalVertexPos, 1.0);
	color0 = color;
}