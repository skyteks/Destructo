struct INPUT
{
    float4 Position : SV_POSITION;
    float2 UV : TEXCOORD;
    float4 Color : COLOR;
    //uint Opacity : UINT;
    //float4 Mask : COLOR;
};

SamplerState samperState;
Texture2D texture2d;
Texture2D opacityMask2d;

//Vertex Shader
INPUT VS_Main(float3 aPosition : POSITION, float2 aUV : TEXCOORD, float4 aColor : COLOR)//, uint aOpacity : UINT, float4 aMask : COLOR)
{
    INPUT output;

    output.Position.xyz = aPosition;
    output.Position.y *= -1;
    output.Position.w = 1;

    output.UV = aUV;
    output.Color = aColor;

    //output.Opacity = aOpacity;
    //outpur.Mask = aMask;

    return output;
}

//Pixel Shader
float4 PS_Main(float4 aPosition : SV_POSITION, float2 aUV : TEXCOORD, float4 aColor : COLOR) : SV_TARGET//, uint aOpacity : UINT, float4 aMask : COLOR) : SV_TARGET
{
    return texture2d.Sample(samperState, aUV).rgba;// *opacityMask2d.Sample(samplerState, aUV).r;
}