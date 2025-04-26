// �C���N���[�h��
#include "Move2DAnimation.h"

// �R���X�g���N�^
Move2DAnimation::Move2DAnimation()
{
	// �����o�ϐ�������
	m_Kind = MoveKind::None;
	m_MaxPos = DirectX::XMFLOAT2(0.0f, 0.0f);
	m_MinPos = DirectX::XMFLOAT2(0.0f, 0.0f);
	m_MoveSpeed = DirectX::XMFLOAT2(0.0f, 0.0f);
	m_Dir = DirectX::XMFLOAT2(1.0f, 1.0f);
}

// �f�X�g���N�^
Move2DAnimation::~Move2DAnimation()
{
}

// �X�V����
void Move2DAnimation::Execute()
{
	// ��ނɂ���ď�����ς���
	switch (m_Kind)
	{
	case MoveKind::Up_Down:
		UpDownMove();		// �㉺�ړ�
		break;
	case MoveKind::Left_Right:
		LeftRightMove();	// ���E�ړ�
		break;
	}
}

// �㉺�ړ��A�j���[�V����
void Move2DAnimation::UpDownMove()
{
	// ���݂̍��W�擾
	DirectX::XMFLOAT3 pos = transform->GetPos();

	// �����ݒ�
	if (m_MinPos.y >= pos.y)
	{
		m_Dir.y = 1;
	}
	else if(m_MaxPos.y <= pos.y)
	{
		m_Dir.y = -1;
	}

	// ���W�ݒ�
	pos.y += m_MoveSpeed.y * m_Dir.y;

	transform->SetPos(pos);
}

// ���E�ړ��A�j���[�V����
void Move2DAnimation::LeftRightMove()
{
	// ���݂̍��W�擾
	DirectX::XMFLOAT3 pos = transform->GetPos();

	// �����ݒ�
	if (m_MinPos.x >= pos.x)
	{
		m_Dir.x = 1;
	}
	else if (m_MaxPos.x <= pos.x)
	{
		m_Dir.x = -1;
	}

	// ���W�ݒ�
	pos.x += m_MoveSpeed.x * m_Dir.x;

	transform->SetPos(pos);
}

// �A�j���[�V������ސݒ�
void Move2DAnimation::SetMoveKind(MoveKind kind)
{
	m_Kind = kind;	// ��ސݒ�
}

// �ړ��X�s�[�h
void Move2DAnimation::SetSpeed(DirectX::XMFLOAT2 speed)
{
	m_MoveSpeed = speed;	// �����ݒ�
}

// �ړ��͈�
void Move2DAnimation::SetMoveArea(DirectX::XMFLOAT2 min, DirectX::XMFLOAT2 max)
{
	m_MinPos = min;	// �ŏ����W�ݒ�
	m_MaxPos = max;	// �ő���W�ݒ�
}

// �����ݒ�
void Move2DAnimation::SetDir(DirectX::XMFLOAT2 dir)
{
	m_Dir = dir;	// �����ݒ�
}

// �X�s�[�h��Ԃ�
DirectX::XMFLOAT2 Move2DAnimation::GetSpeed()
{
	return m_MoveSpeed;
}

// �ړ��͈͂̍ő���W
DirectX::XMFLOAT2 Move2DAnimation::GetMaxPos()
{
	return m_MaxPos;
}

// �ړ��͈͂̍ŏ����W
DirectX::XMFLOAT2 Move2DAnimation::GetMinPos()
{
	return m_MinPos;
}
