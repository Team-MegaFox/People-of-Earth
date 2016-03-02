#version 120
// The original texture
uniform sampler2D referenceTex;

// The width and height of each pixel in texture coordinates

attribute vec2 pixelDims;

varying vec2 texCoords0;

void main()
{
	// Current texture coordinate
	vec2 texel = vec2(texCoords0);
	vec4 pixel = vec4(texture2D(referenceTex, texel));
	
	pixelDims = vec2(2.0, 2.0);
	
	// Larger constant = bigger glow
	float glow = 4.0 * ((pixelDims.x + pixelDims.y) / 2.0);
	
	// The vector to contain the new, "bloomed" colour values
	vec4 bloom = vec4(0);
	
	// Loop over all the pixels on the texture in the area given by the constant in glow
	int count = 0;
	for(float x = texel.x - glow; x < texel.x + glow; x += pixelDims.x)
	{
		for(float y = texel.y - glow; y < texel.y + glow; y += pixelDims.y)
		{
			// Add that pixel's value to the bloom vector
			bloom += (texture2D(referenceTex, vec2(x, y)) - 0.4) * 30.0;
			// Add 1 to the number of pixels sampled
			count++;
		}
	}
	// Divide by the number of pixels sampled to average out the value
	// The constant being multiplied with count here will dim the bloom effect a bit, with higher values
	// Clamp the value between a 0.0 to 1.0 range
	bloom = clamp(bloom / (count * 30), 0.0, 1.0);
	
	// Set the current fragment to the original texture pixel, with our bloom value added on
	gl_FragColor = pixel + bloom;
}