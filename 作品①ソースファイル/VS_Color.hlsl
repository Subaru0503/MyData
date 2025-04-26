// �C���v�b�g���C�A�E�g
// CPU����n����钸�_�̏����`��������
struct VS_IN
{
	float3 pos : POSITION0;		// �Z�}���e�B�N�X
	float2 uv : TEXCOORD0;
};

// ���_�V�F�[�_�[����s�N�Z���V�F�[�_�[�֑���f�[�^�̒�`
struct VS_OUT
{
	float4 pos : SV_POSITION0;
	float2 uv : TEXCOORD0;
	float4 color : COLOR;
};

// �萔�o�b�t�@
// CPU��GPU�ł���肷��A���_�ȊO�̃f�[�^���i�[�����
cbuffer WVP : register(b0)
{
	float4x4 world;
	float4x4 view;
	float4x4 proj;
};

cbuffer Param : register(b1)
{
	float2 offset;
	float2 size;
	float2 uvPos;
	float2 uvScale;
	float4 color;
};

VS_OUT main(VS_IN vin)
{
	VS_OUT vout;

	// ���[�J�����W���X�N���[�����W�֕ϊ�
	vout.pos = float4(vin.pos, 1.0f);	// ���[�J�����W
	vout.pos.xy *= size;
	vout.pos.xy += offset;
	vout.pos = mul(vout.pos, world);	// ���[���h���W
	vout.pos = mul(vout.pos, view);		// �r���[���W
	vout.pos = mul(vout.pos, proj);		// �v���W�F�N�V�������W

	// �s�N�Z���V�F�[�_�[�ŗ��p����UV���W��n��
	vout.uv = vin.uv;
	vout.uv *= uvScale;
	vout.uv += uvPos;

	vout.color = color;

	return vout;
}