struct VS_IN
{
	float3 pos : POSITION0;
	float3 normal : NORMAL0;
	float2 uv : TEXCOORD0;
};
struct VS_OUT
{
	float4 pos : SV_POSITION0;
	float2 uv : TEXCOORD0;
	float3 normal : NORMAL0;
	float4 worldPos : TEXCOORD1;
};

cbuffer WVP : register(b0)
{
	float4x4 world;
	float4x4 view;
	float4x4 proj;
};

VS_OUT main(VS_IN vin)
{
	VS_OUT vout;

	vout.pos = float4(vin.pos, 1.0f);
	vout.pos = mul(vout.pos, world);
	vout.worldPos = vout.pos;
	vout.pos = mul(vout.pos, view);
	vout.pos = mul(vout.pos, proj);

	vout.uv = vin.uv;

	// (float3x3)�͊g�k���l�����Ȃ��@���̌v�Z
	vout.normal = mul(vin.normal, (float3x3)world);
	// x,y,z�ł��ꂼ��Ⴄ�g�k�̏ꍇ�A��L�̌v�Z�ł�
	// �������@�����v�Z�ł��Ȃ��B��CPU�Ŏ��O�Ɍv�Z����
	// �n���K�v����B
	// �Ⴆ�Ή��ɐL�΂��g����s�����Ƃ��A�΂ߕ����̖@����
	// ���ɐL�т�̂ł͂Ȃ��A�c�ɐL�тȂ���΂��������B
	// ���ɒ[�Șb�A�����ɉ��ɐL�΂��Ώ�����������ʂɂȂ�͂�
	// �����ŁA�g�k�̂ݍs��̐�����ł������t�s��Ƃ��邱�Ƃ�
	// �������@�����v�Z�ł���B
	// �菇)
	// 1.��]�Ɗg�k���܂܂ꂽ�s��̋t�s����v�Z����B
	// 2.�P�Ōv�Z���ꂽ�t�s���]�u����B
	// �@�����s��̋t�s��͓]�u�s��̌��ʂƓ������B

	return vout;
}