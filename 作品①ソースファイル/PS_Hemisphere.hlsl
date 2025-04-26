struct PS_IN
{
	float4 pos : SV_POSITION0;
	float2 uv : TEXCOORD0;
	float3 normal : NORMAL0;
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
cbuffer Light : register(b1)
{
	float4 groundColor;
	float4 skyColor;
	float4 groundNormal;
};

float4 main(PS_IN pin) : SV_TARGET
{
	// �T�[�t�F�X�̖@���ƒn�ʂ̖@���̓���
	float3 N = normalize(pin.normal);
	float t = dot(N, groundNormal.xyz);

	// ���ς̌���(-1�`1)��0�`1�ɕϊ�
	t = (t + 1.0f) / 2.0f;

	// �������C�g�̐F���v�Z
	float3 hemiLight = skyColor.rgb * t + groundColor.rgb * (1.0f - t);

	// �g�U���˂̌v�Z
	float3 L = normalize(lightDir);
	L *= -1.0f;
	float d = dot(L, N);
	d = saturate(d);
	float3 diffuseLig = lightColor.rgb * d;

	// ����(�������C�g)�̌v�Z
	float3 lig = diffuseLig + hemiLight;

	// �e�N�X�`�����Ń��C�g�̌v�Z
	float4 finalColor = tex.Sample(samp, pin.uv);
	finalColor.rgb *= lig;

	return finalColor;
}