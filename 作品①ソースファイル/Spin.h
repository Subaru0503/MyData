// ��]�@�\�N���X

// �C���N���[�h�K�[�h
#ifndef __SPIN_H__
#define __SPIN_H__

// �C���N���[�h��
#include "Component.h"

// �N���X��`
class Spin : public Component
{
public:

	void XSpin(bool Right = true, float time = 0.7f);	// true�Ȃ�E��]�Afalse�Ȃ獶��]
	void YSpin(bool Right = true, float time = 0.7f);	// true�Ȃ�E��]�Afalse�Ȃ獶��]
	void ZSpin(bool Right = true, float time = 0.7f);	// true�Ȃ�E��]�Afalse�Ȃ獶��]

	// �Z�b�g�֐�
	inline void SetTorque(float torque)
	{
		m_Torque = torque;
	}
	inline void SetMoment(float moment)
	{
		m_MomentOfInertia = moment;
	}

	// �Q�b�g�֐�
	inline float GetTorque()
	{
		return m_Torque;
	}
	inline float GetMoment()
	{
		return m_MomentOfInertia;
	}
	inline float GetScrewTravel()
	{
		return m_ScrewTravel;
	}

private:
	float AngularAcceleration();	// �p�����x�����߂�
private:
	float m_ScrewTravel;		// �l�W�̐i�񂾋���
	float m_Torque;				// �g���N
	float m_MomentOfInertia;	// �������[�����g
};

#endif // __SPIN_H__