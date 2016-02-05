#version 120
attribute vec3 position;

varying vec3 texCoord;

uniform mat4 T_VP;

void main()
{
    vec4 pos = T_VP * vec4(position, 1.0);
    gl_Position = pos.xyww;
    texCoord = position;
} 