#version 320

in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;
int Width = 1024;
int Height = 576;
float LumThresh = 0.3f; // Luminance threshold
// Weights and offsets for the Gaussian blur
float PixOffset[10] = float[](0.0,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0);
float Weight = 0.2f;

uniform sampler2D diffuse;
uniform sampler2D blurTex;
uniform vec3 R_ambient;

//subroutine vec4 RenderPassType();
//subroutine uniform RenderPassType RenderPass;

// Uniform variables for the Phong reflection model
// should be added here…
//layout( location = 0 ) out vec4 FragColor;

float luma( vec3 color ) 
{
	return 0.2126f * color.x + 0.7152f * color.y + 0.0722f * color.z;
}

float clampValue( float valueToCheck, float lowValue, float highValue )
{
	float returnValue;
	if(valueToCheck > lowValue && valueToCheck < highValue)
	{
		returnValue = valueToCheck;
	}
	else if(valueToCheck < lowValue)
	{
		returnValue = lowValue;
	}
	else if (valueToCheck > highValue)
	{
		returnValue = highValue;
	}
	
	return returnValue;
}

// See Chapter 2 for the ADS shading model code
vec3 phongModel( vec3 pos, vec3 norm ) 
{ 
	vec3 s = normalize(vec3(vec3(0.0f, 0.0f, -200.0f) - pos));
	vec3 v = normalize(-pos.xyz);
	vec3 r = reflect( -s, norm );
	float sDotN = max( dot(s, norm), 0.0 );
	vec3 diffuseVal = vec3(1.0, 1.0, 1.0) * sDotN;
	vec3 spec = vec3(0.0, 0.0, 0.0);
	if( sDotN > 0.0f )
	{
		spec *= 0.5f * pow( max( dot(r, v), 0.0f ), 4 );
	}
	return R_ambient + diffuseVal + spec;
}
// The render pass

//subroutine (RenderPassType) 
vec4 pass1()
{
	return vec4(phongModel( Position, Normal ), 1.0);
}
	// Pass to extract the bright parts
	
//subroutine( RenderPassType ) 
vec4 pass2()
{
	vec4 val = texture(diffuse, TexCoord);
	float bob =  luma(val.xyz) - LumThresh;
	float clampedValue = clampValue(bob, 0.0f, 1.0f );
	float multiValue = clampedValue * (1.0f / (1.0f - LumThresh));
	vec4 temp = val * multiValue;
	return temp;
}

// First blur pass
//subroutine( RenderPassType ) 
vec4 pass3()
{
	float dy = 1.0 / float(Height);
	vec4 sum = texture(blurTex, TexCoord) * Weight;
	for( int i = 1; i < 10; i++ )
	{
		vec2 pixelOffset = vec2(0.0f, float(PixOffset[i])) * float(dy);
		vec2 textureCoordsA = vec2(TexCoord + pixelOffset);
		vec2 textureCoordsB = vec2(TexCoord - pixelOffset);
		vec4 textureResultPos = texture(blurTex, textureCoordsA) * Weight;
		vec4 textureResultNeg = texture(blurTex, textureCoordsA) * Weight;
		
		sum += textureResultPos;
		sum += textureResultNeg;
	}

return sum;
}

// Second blur and add to original
//subroutine( RenderPassType ) 
vec4 pass4()
{
	float dx = 1.0 / float(Width);
	vec4 sum = texture(blurTex, TexCoord) * Weight;
	vec4 val = texture(diffuse, TexCoord);
	
	for( int i = 1; i < 10; i++ )
	{
		vec2 pixelOffset = vec2(float(PixOffset[i]), 0.0f) * float(dx);
		vec2 textureCoordsA = vec2(TexCoord + pixelOffset);
		vec2 textureCoordsB = vec2(TexCoord - pixelOffset);
		vec4 textureResultPos = texture( blurTex, textureCoordsA) * Weight;
		vec4 textureResultNeg = texture( blurTex, textureCoordsB) * Weight;
	
		sum += textureResultPos;
		sum += textureResultNeg;
	}
	return val + sum;
}

void main()
{
	gl_FragColor = pass1() + pass2() + pass3() + pass4();
}