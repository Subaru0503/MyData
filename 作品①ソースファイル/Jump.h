// �W�����v�N���X

// �C���N���[�h�K�[�h
#ifndef __JUMP_H__
#define __JUMP_H__

// �C���N���[�h��
#include "Component.h"

// �N���X��`
class Jump : public Component
{
private:
#define JUMP_POWER 0.35f	// �W�����v�p���[

public:
	Jump();				// �R���X�g���N�^

	void Execute();		// �X�V

	// �Z�b�g�֐�
	inline void SetJump()
	{
		m_JumpForce = JUMP_POWER;
		//m_JumpForce += 0.15f;
		//if (m_JumpForce >= JUMP_POWER)
		//{
		//	m_JumpForce = JUMP_POWER;
		//	return;
		//}
	}

	// �Q�b�g�֐�
	inline bool GetJump()
	{
		return m_JumpForce <= 0.0f;
	}

private:
	float m_JumpForce;		// �W�����v��
	float m_CurrentTime;	// �o�ߎ���
};

#endif // __JUMP_H__