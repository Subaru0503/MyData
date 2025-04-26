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
	float3 lightDir; // ���C�g�̕���
	float dummy; // 16�o�C�g�ɑ�����ׂ̃_�~�[
	float4 lightColor; // ���C�g�̐F
	float4 lightAmbient;
};

float4 main(PS_IN pin) : SV_TARGET
{
	// �@��
	// normalize ... ���K��(�P�ʃx�N�g���ɕϊ�
	float3 N = normalize(pin.normal);

	// ���C�g�̕���
	float3 L = normalize(lightDir);
	// ���ς̌v�Z���ʂ������ڂɍ����悤��
	// ���O�Ƀ��C�g�̕����𔽓]�����Ă���
	L *= -1.0f;

	// ���ς̌v�Z
	float d = dot(L, N);
	d = saturate(d); // 0������0,1���傫����1�ɂ���

	// ���̐F���v�Z
	float3 diffuseLig =
		lightColor.rgb * d;

	// �e�N�X�`���̐F
	float4 finalColor =
		tex.Sample(samp, pin.uv);

	// �����̌v�Z
	diffuseLig.rgb += lightAmbient.rgb;

	// �ŏI�J���[�Ɍ�����Z
	finalColor.rgb *= diffuseLig;

	return finalColor;
}