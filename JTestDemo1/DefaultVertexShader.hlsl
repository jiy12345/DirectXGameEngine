struct VS_in
{
	float3 position : POSITION;
    float4 normal : NORMAL;
	float4 color : COLOR;
	float2 tex : TEXTURE;
};
struct VS_out
{
	float4 p : SV_POSITION;
    float4 n : NORMAL;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};
cbuffer cb_data : register(b0)
{
	matrix g_matWorld : packoffset(c0);
	matrix g_matView : packoffset(c4);
	matrix g_matProj : packoffset(c8);
	float  fTimer : packoffset(c12.z);
};
VS_out VS(VS_in input) 
{
	VS_out output = (VS_out)0;
    float4 vLocal = float4(input.position, 1.0f);

	float4 vWorld = mul(vLocal, g_matWorld);
	float4 vView = mul(vWorld, g_matView);
	float4 vProj = mul(vView, g_matProj);
	
	output.p = vProj;
	output.c = input.color;
	output.t = input.tex;

	return output;
}