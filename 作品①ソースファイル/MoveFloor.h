// ���ړ��M�~�b�N�N���X

// �C���N���[�h�K�[�h
#ifndef __MOVE_FLOOR_H__
#define __MOVE_FLOOR_H__

// �C���N���[�h��
#include "GimmickBase.h"

// �R���|�[�l���g
#include "Move.h"	// �ړ�

// �N���X��`
class MoveFloor : public GimmickBase
{
public:
	enum class MoveType
	{
		UpDown,		// �㉺�ړ�
		LeftRight,	// ���E�ړ�
		FrontBack,	// �O��ړ�
	};
public:
	MoveFloor(std::string name = "MoveFloor");	// �R���X�g���N�^
	~MoveFloor();									// �f�X�g���N�^

	// ������Ԃɖ߂�
	void ResetState();

	// �^�[�Q�b�g�I�u�W�F�N�g�̏���
	void Gimmick(int index, float rotY);
	// �ʏ�̃l�W���񂷕����Ƌt�����ɉ񂳂ꂽ�Ƃ��ɌĂ�
	void InvertGimmick(int index, float rotY);

	// �ړ��ʃZ�b�g
	inline void SetMove(float move)
	{
		m_Move = move;
	}

	// �ړ��^�C�v�Z�b�g
	inline void SetType(MoveType type)
	{
		m_moveType = type;
	}
private:
	void MoveGimmick();			// �ړ��M�~�b�N
	void ReverseMoveGimmick();	// �t�����ړ��M�~�b�N

private:
	// �R���|�[�l���g
	Move* _move;			// �ړ��R���|�[�l���g

	MoveType m_moveType;	// �ړ��^�C�v

	float m_Move;			// �ړ���
};

#endif // __MOVE_FLOOR_H__