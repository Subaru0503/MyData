// 頂点シェーダーから受け取るためのデータを定義
struct PS_IN
{
	float4 pos : SV_POSITION0;
	float2 uv : TEXCOORD0;
	float4 color : COLOR;
};

// テクスチャを受け取る
Texture2D tex : register(t0);
SamplerState samp : register(s0); // テクスチャの繰り返し設定

cbuffer ColorModifier : register(b0) {
	float4 colorTint; // 色変更の乗算値
};

float4 main(PS_IN pin) : SV_TARGET
{
	float4 color = tex.Sample(samp, pin.uv);

	float colorDifference = length(color.rgb - float3(1.0f, 0.0f, 0.0f));

	if (colorDifference <= 0.25f)
	{
		// テクスチャからデータを取得
		return colorTint;
	}

	return color;
}