#version 120
attribute vec3 position;
attribute vec4 particlePosition;
attribute vec4 color;

varying vec2 texCoord0;
varying vec4 color0;

uniform mat4 T_MVP;

void main()
{
    gl_Position = T_MVP * vec4(position + particlePosition.xyz, 1.0);
    texCoord0 = position.xy + vec2(0.5, 0.5);
	color0 = color;
    
    //vec3 n = normalize((T_model * vec4(normal, 0.0)).xyz);
    //vec3 t = normalize((T_model * vec4(tangent, 0.0)).xyz);
    //t = normalize(t - dot(t, n) * n);
    
    //vec3 biTangent = cross(t, n);
    //tbnMatrix = mat3(t, biTangent, n);
}
