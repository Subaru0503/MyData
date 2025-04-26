struct PS_IN
{
	float4 pos : SV_POSITION0;
	float2 uv : TEXCOORD0;
	float3 normal : NORMAL0;
};

Texture2D tex : register(t0);
SamplerState samp : register(s0);

// 定数バッファ
cbuffer LightBuf : register(b0)
{
	float3 lightDir;
	float dummy;
	float4 lightColor;
	float4 lightAmbient;
};
cbuffer Light : register(b1)
{
	float4 groundColor;
	float4 skyColor;
	float4 groundNormal;
};

float4 main(PS_IN pin) : SV_TARGET
{
	// サーフェスの法線と地面の法線の内積
	float3 N = normalize(pin.normal);
	float t = dot(N, groundNormal.xyz);

	// 内積の結果(-1～1)を0～1に変換
	t = (t + 1.0f) / 2.0f;

	// 半球ライトの色を計算
	float3 hemiLight = skyColor.rgb * t + groundColor.rgb * (1.0f - t);

	// 拡散反射の計算
	float3 L = normalize(lightDir);
	L *= -1.0f;
	float d = dot(L, N);
	d = saturate(d);
	float3 diffuseLig = lightColor.rgb * d;

	// 環境光(半球ライト)の計算
	float3 lig = diffuseLig + hemiLight;

	// テクスチャ込でライトの計算
	float4 finalColor = tex.Sample(samp, pin.uv);
	finalColor.rgb *= lig;

	return finalColor;
}