// �ړ��A�j���[�V�����@�\�N���X

// �C���N���[�h�K�[�h
#ifndef __MOVE_ANIMATION_H__
#define __MOVE_ANIMATION_H__

// �C���N���[�h��
#include "Component.h"

// �N���X��`
class Move2DAnimation : public Component
{
public:
	enum MoveKind
	{
		None,		// �Ȃ�
		Up_Down,	// �㉺
		Left_Right,	// ���E
	};
public:
	Move2DAnimation();	// �R���X�g���N�^
	~Move2DAnimation();	// �f�X�g���N�^

	void Execute();		// �X�V����

	void UpDownMove();		// �㉺�ړ��A�j���[�V����
	void LeftRightMove();	// ���E�ړ��A�j���[�V����

	// �Z�b�g�֐�
	// �A�j���[�V������ސݒ�
	void SetMoveKind(MoveKind kind);

	// �ړ��X�s�[�h
	void SetSpeed(DirectX::XMFLOAT2 speed);

	// �ړ��͈�
	void SetMoveArea(DirectX::XMFLOAT2 min, DirectX::XMFLOAT2 max);

	// �����ݒ�
	void SetDir(DirectX::XMFLOAT2 dir);

	// �A�j���[�V�������~�߂�
	//void Stop();

	//----�Q�b�g�֐�----
	// �X�s�[�h��Ԃ�
	DirectX::XMFLOAT2 GetSpeed();

	// �ړ��͈͂̍ő���W
	DirectX::XMFLOAT2 GetMaxPos();

	// �ړ��͈͂̍ŏ����W
	DirectX::XMFLOAT2 GetMinPos();

private:
	MoveKind m_Kind;				// �ړ����

	DirectX::XMFLOAT2 m_MaxPos;		// �ړ��͈͂̍ő���W
	DirectX::XMFLOAT2 m_MinPos;		// �ړ��͈͂̍ŏ����W
	DirectX::XMFLOAT2 m_MoveSpeed;	// �ړ��X�s�[�h
	DirectX::XMFLOAT2 m_Dir;		// �ړ�����

	//bool m_Stop;					// �A�j���[�V�������~�߂�
};

#endif // __MOVE_ANIMATION_H__