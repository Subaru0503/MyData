// ���_�V�F�[�_�[����󂯎�邽�߂̃f�[�^���`
struct PS_IN
{
	float4 pos : SV_POSITION0;
	float2 uv : TEXCOORD0;
	float4 color : COLOR;
};

// �e�N�X�`�����󂯎��
Texture2D tex : register(t0);
SamplerState samp : register(s0); // �e�N�X�`���̌J��Ԃ��ݒ�

cbuffer ColorModifier : register(b0) {
	float4 colorTint; // �F�ύX�̏�Z�l
};

float4 main(PS_IN pin) : SV_TARGET
{
	float4 color = tex.Sample(samp, pin.uv);

	float colorDifference = length(color.rgb - float3(1.0f, 0.0f, 0.0f));

	if (colorDifference <= 0.25f)
	{
		// �e�N�X�`������f�[�^���擾
		return colorTint;
	}

	return color;
}