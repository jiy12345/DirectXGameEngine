struct VS_in
{
	float3 position : POSITION;
    float3 normal : NORMAL;
	float4 color : COLOR;
	float2 tex : TEXTURE;
};
struct VS_out
{
	float4 p : SV_POSITION;
    float3 n : NORMAL;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
    float4 lightcolor : TEXCOORD1;
};
cbuffer cb_data : register(b0)
{
	matrix g_matWorld : packoffset(c0);
	matrix g_matView : packoffset(c4);
	matrix g_matProj : packoffset(c8);
	float4 g_vLight : packoffset(c12);
};

VS_out VS(VS_in input) 
{
	VS_out output = (VS_out)0;
    float4 vLocal = float4(input.position, 1.0f);

	float4 vWorld = mul(vLocal, g_matWorld);
	float4 vView = mul(vWorld, g_matView);
	float4 vProj = mul(vView, g_matProj);
	
	output.p = vProj;
    output.n = input.normal;
    float3 vLight = g_vLight.xyz;
    float fDot = max(0.3f, dot(input.normal, -vLight));
    output.lightcolor = float4(fDot, fDot, fDot, 1);
	output.c = input.color;
	output.t = input.tex;

	return output;
}