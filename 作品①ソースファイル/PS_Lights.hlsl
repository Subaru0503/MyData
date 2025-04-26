struct PS_IN
{
	float4 pos : SV_POSITION0;
	float2 uv : TEXCOORD0;
	float3 normal : NORMAL0;
	float4 worldPos : TEXCOORD1;
};

// 定数バッファ
struct LightInfo
{
	float3 pos;
	float range;
	float3 color;
	int type;
	float3 dir;
	float angle;
};
cbuffer Lights : register(b0)
{
	LightInfo lights[5];
};

SamplerState samp : register(s0);
Texture2D tex : register(t0);

float4 main(PS_IN pin) : SV_TARGET
{
	float4 color = tex.Sample(samp, pin.uv);
	float3 N = normalize(pin.normal);

	float3 diffuse = float3(0.0f, 0.0f, 0.0f); 
	for (int i = 0; i < 5; ++i)
	{
		float3 dist = lights[i].pos - pin.worldPos;
		float atten = saturate(1.0f - (length(dist) / lights[i].range));
		float d = saturate(dot(normalize(dist), N) + 0.2f);
		diffuse += lights[i].color * pow(atten, 2.0f) * d;
	}


	color.rgb *= diffuse;
	return color;
}