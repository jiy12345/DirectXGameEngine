struct VS_in
{
	float3 p : POSITION;
	float4 color : COLOR;
	float2 tex : TEXTURE;
};
struct VS_out
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};
VS_out VS(VS_in input) 
{
	VS_out output = (VS_out)0;

	output.p = float4(input.p,1.0f);
	output.c = input.color;
	output.t = input.tex;
	return output;
}
struct PS_input
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};
float4 PS(	PS_input input) : SV_Target
{
	return input.c;
}