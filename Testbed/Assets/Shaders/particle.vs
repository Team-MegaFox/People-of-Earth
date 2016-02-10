#version 120

// Input vertex data, different for all executions of this shader.
attribute vec3 squareVertices;
attribute vec4 position; // Position of the center of the particule and size of the square
attribute vec4 color; // Position of the center of the particule and size of the square

// Output data ; will be interpolated for each fragment.
varying vec2 texCoord;
varying vec4 particlecolor;

// Values that stay constant for the whole mesh.
uniform vec3 C_right;
uniform vec3 C_up;
uniform mat4 T_VP; // Model-View-Projection matrix, but without the Model (the position is in BillboardPos; the orientation depends on the camera)

void main()
{
	float particleSize = position.w; // because we encoded it this way.
	vec3 particleCenter_wordspace = position.xyz;
	
	vec3 vertexPosition_worldspace = 
		particleCenter_wordspace
		+ C_right * squareVertices.x * particleSize
		+ C_up * squareVertices.y * particleSize;

	// Output position of the vertex
	gl_Position = T_MVP * vec4(vertexPosition_worldspace, 1.0f);

	// UV of the vertex. No special space for this one.
	texCoord = squareVertices.xy + vec2(0.5, 0.5);
	particlecolor = color;
}
