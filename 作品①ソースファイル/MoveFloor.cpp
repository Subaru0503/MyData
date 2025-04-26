// ���ړ��M�~�b�N�N���X

// �C���N���[�h��
#include "MoveFloor.h"

// �V�X�e��
#include "Input.h"

// �萔�E�}�N����`
#define DIVISOR (23.5f) // ����

// �R���X�g���N�^
MoveFloor::MoveFloor(std::string name)
	: GimmickBase(name)
{
	m_tag = "MoveGimmick";
	// �R���|�[�l���g�ǉ�
	AddComponent<Move>();			// �ړ�

	// �R���|�[�l���g�擾
	_move = GetComponent<Move>();

	// �����o�ϐ�������
	m_Move = 1.0f;
}

// �f�X�g���N�^
MoveFloor::~MoveFloor()
{
}

// ������Ԃɖ߂�
// �I�u�W�F�N�g���V�[�����n�܂����Ƃ��̏�Ԃɖ߂�
void MoveFloor::ResetState()
{
	// �������W�ɖ߂�
	m_pos = m_InitPos;
}

// �^�[�Q�b�g�I�u�W�F�N�g�̏���
void MoveFloor::Gimmick(int index, float rotY)
{
	// �ړ��ʌv�Z
	float move = rotY / DIVISOR;

	// �ړ��ʃZ�b�g
	_move->SetMove(move * m_Move);

	// �ړ��M�~�b�N
	MoveGimmick();
}

// �ʏ�̃l�W���񂷕����Ƌt�����ɉ񂳂ꂽ�Ƃ��ɌĂ�
void MoveFloor::InvertGimmick(int index, float rotY)
{
	// �ړ��ʌv�Z
	float move = rotY / DIVISOR;

	// �ړ��ʃZ�b�g
	_move->SetMove(move * m_Move);

	// �t�����Ɉړ��M�~�b�N
	ReverseMoveGimmick();
}

// �ړ��M�~�b�N
void MoveFloor::MoveGimmick()
{
	// �ړ���ނɂ���ď�����ς���
	switch (m_moveType)
	{
	case MoveType::UpDown:

		// ��Ɉړ�
		_move->UPMove();

		break;
	case MoveType::LeftRight:

		// �E�Ɉړ�
		_move->RightMove();

		break;
	case MoveType::FrontBack:

		// �O�Ɉړ�
		_move->FrontMove();

		break;
	}
}

// �t�����ړ��M�~�b�N
void MoveFloor::ReverseMoveGimmick()
{
	// �ړ���ނɂ���ď�����ς���
	switch (m_moveType)
	{
	case MoveType::UpDown:

		// ���Ɉړ�
		_move->UPMove(false);

		break;

	case MoveType::LeftRight:

		// ���Ɉړ�
		_move->RightMove(false);

		break;
	case MoveType::FrontBack:

		// ���Ɉړ�
		_move->FrontMove(false);

		break;
	}
}
