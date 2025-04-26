// �ړ��@�\�N���X

// �C���N���[�h�K�[�h
#ifndef __MOVE_H__
#define __MOVE_H__

// �C���N���[�h��
#include "Component.h"

// �V�X�e��
#include "float3.h"

// �N���X��`
class Move : public Component
{
public:

	void UPMove(bool UP = true);		// �����ړ�
	void RightMove(bool Right = true);	// ���E�ړ�
	void FrontMove(bool Front = true);	// �O��ړ�
	void DiagonalMove(float3 dir);		// �΂߈ړ�

	// �Z�b�g�֐�
	inline void SetMove(float move)
	{
		m_Move = move;
	}

	// �Q�b�g�֐�
	inline float GetMove()
	{
		return m_Move;
	}

private:
	float m_Move;		// �ړ���
};

#endif // __MOVE_H__