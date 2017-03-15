struct INPUT
{
	float4 Position : SV_POSITION;
	float2 UV : TEXCOORD;
	float4 Color : COLOR;
};

SamplerState samperState;
Texture2D texture2;

//Vertex Shader
INPUT VS_Main(float3 aPosition : POSITION, float2 aUV : TEXCOORD, float4 aColor : COLOR)
{
	INPUT output;

	output.Position.xyz = aPosition;
	output.Position.y *= -1;
	output.Position.w = 1;

	output.UV = aUV;

	output.Color = aColor;

	return output;
}

//Pixel Shader
float4 PS_Main(float4 aPosition : SV_POSITION, float2 aUV : TEXCOORD, float4 aColor : COLOR) : SV_TARGET
{
		return texture2.Sample(samperState, aUV).rgba * float4(aColor.r, aColor.g, aColor.b, aColor.a);
}