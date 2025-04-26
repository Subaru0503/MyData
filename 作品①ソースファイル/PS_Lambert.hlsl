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
	float3 lightDir; // ライトの方向
	float dummy; // 16バイトに揃える為のダミー
	float4 lightColor; // ライトの色
	float4 lightAmbient;
};

float4 main(PS_IN pin) : SV_TARGET
{
	// 法線
	// normalize ... 正規化(単位ベクトルに変換
	float3 N = normalize(pin.normal);

	// ライトの方向
	float3 L = normalize(lightDir);
	// 内積の計算結果が見た目に合うように
	// 事前にライトの方向を反転させておく
	L *= -1.0f;

	// 内積の計算
	float d = dot(L, N);
	d = saturate(d); // 0未満は0,1より大きいと1にする

	// 光の色を計算
	float3 diffuseLig =
		lightColor.rgb * d;

	// テクスチャの色
	float4 finalColor =
		tex.Sample(samp, pin.uv);

	// 環境光の計算
	diffuseLig.rgb += lightAmbient.rgb;

	// 最終カラーに光を乗算
	finalColor.rgb *= diffuseLig;

	return finalColor;
}