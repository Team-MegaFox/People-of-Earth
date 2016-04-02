#version 320

in vec3 position0;
in vec2 texCoord0;
in vec3 normal0;

out vec3 Position;
out vec3 Normal;
out vec2 TexCoord;

uniform mat4 T_model;
uniform mat4 T_VP;
uniform mat4 T_MVP;

void main()
{
	mat3 NormalMatrix = transpose( inverse ( mat3( T_VP * T_model ) ) );
	TexCoord = texCoord0;
	Normal = normalize( NormalMatrix * normal0 );
	Position = vec3( T_model * vec4( position0, 1.0) );
	gl_Position = T_MVP * vec4( position0, 1.0 );
}