// �C���N���[�h��
#include "Move.h"

// �����ړ�
void Move::UPMove(bool UP)
{
	float dir;
	if (UP)
	{
		dir = 1;
	}
	else
	{
		dir = -1;
	}

	DirectX::XMFLOAT3 pos = transform->GetPos();

	pos.y += m_Move * dir;

	transform->SetPos(pos);
}

// ���E�ړ�
void Move::RightMove(bool Right)
{
	float dir;
	if (Right)
	{
		dir = 1;
	}
	else
	{
		dir = -1;
	}
	DirectX::XMFLOAT3 pos = transform->GetPos();

	pos.x += m_Move * dir;

	transform->SetPos(pos);
}

// �O��ړ�
void Move::FrontMove(bool Front)
{
	float dir;
	if (Front)
	{
		dir = 1;
	}
	else
	{
		dir = -1;
	}
	DirectX::XMFLOAT3 pos = transform->GetPos();

	pos.z += m_Move * dir;

	transform->SetPos(pos);
}

// �΂߈ړ�
void Move::DiagonalMove(float3 dir)
{
	// �i�s�����Ɉړ��ʂ��|����
	float3 move = dir * m_Move;

	// �f�[�^�^��ϊ�����
	DirectX::XMFLOAT3 newPos = float3::ToXMFLOAT3(move);

	// ���݂̍��W�̎擾
	DirectX::XMFLOAT3 pos = transform->GetPos();

	// ���݂̍��W�ɑ���
	pos.x += newPos.x;
	pos.y += newPos.y;
	pos.z += newPos.z;

	// �V�������W���Z�b�g
	transform->SetPos(pos);
}
