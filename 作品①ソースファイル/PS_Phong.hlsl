struct PS_IN
{
	float4 pos : SV_POSITION0;
	float2 uv : TEXCOORD0;
	float3 normal : NORMAL0;
	float4 worldPos : TEXCOORD1;
};

Texture2D tex : register(t0);
SamplerState samp : register(s0);

// �萔�o�b�t�@
cbuffer LightBuf : register(b0)
{
	float3 lightDir;
	float dummy;
	float4 lightColor;
	float4 lightAmbient;
};
cbuffer CameraBuf : register(b1)
{
	float3 cameraPos;
	float camDummy;
};

float4 main(PS_IN pin) : SV_TARGET
{
	// ���˃x�N�g���̌v�Z
	float3 N = normalize(pin.normal);
	float3 R = reflect(lightDir, N);
	R = normalize(R);

	// ����(�J����)�Ɍ������x�N�g���̌v�Z
	float3 V = cameraPos - pin.worldPos.xyz;
	V = normalize(V);

	// ���ʔ��˂̋��������߂�
	float d = dot(R, V);
	if (d < 0.0f)
		d = 0.0f;

	// ���ʔ��˂̋������i��
	d = pow(d, 30.0f);

	// ���ʔ��˂̌��̐F���v�Z
	float3 specularLig = lightColor.rgb * d;

	// �g�U���˂̌v�Z
	float3 L = normalize(lightDir);
	L *= -1.0f;
	d = dot(L, N);
	d = saturate(d);
	float3 diffuseLig = lightColor.rgb * d;
	diffuseLig.rgb += lightAmbient.rgb;

	float3 lig = diffuseLig + specularLig;
	float4 finalColor = tex.Sample(samp, pin.uv);
	finalColor.rgb *= lig;

	return finalColor;
}