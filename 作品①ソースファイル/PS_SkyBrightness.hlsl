struct PS_IN
{
	float4 pos : SV_POSITION0;
	float2 uv : TEXCOORD0;
	float3 normal : NORMAL0;
};

// 定数バッファ

// 時間の情報
cbuffer TimeBuffer : register(b0)
{
	float timeOfDay;
};

Texture2D tex : register(t0);
SamplerState samp : register(s0);

float4 main(PS_IN pin) : SV_TARGET
{
	// 昼から夜への色変化をシミュレート
	float3 dayColor = float3(1.0, 1.0, 1.0);
	float3 eveningColor = float3(1.0, 0.5, 0.3);
	float3 nightColor = float3(0.1, 0.1, 0.1);

	float3 finalColor;
	if (timeOfDay < 0.33f)
	{
		finalColor = lerp(dayColor, eveningColor, timeOfDay / 0.33);
	}
	else if (timeOfDay < 0.66f)
	{
		finalColor = lerp(eveningColor, nightColor, (timeOfDay - 0.33) / 0.33);
	}
	else
	{
		finalColor = lerp(nightColor, dayColor, (timeOfDay - 0.66) / 0.34);
	}

	// 最終出力
	float4 color = float4(1.0f, 1.0f, 1.0f, 1.0f);
	color.rgb = tex.Sample(samp, pin.uv) * finalColor;

	return color;
}