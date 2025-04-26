///////////////////////////////////////
//
// �l�W���N���X
//
///////////////////////////////////////

// �C���N���[�h�K�[�h
#ifndef __SCREW_H__
#define __SCREW_H__

// �C���N���[�h��
#include "GameObject.hpp"

// �R���|�[�l���g
#include "Move.h"	// �ړ�
#include "Spin.h"	// ��]
#include "BoxCollider.h"		// �����蔻��
#include "ModelRenderer3D.h"	// 3D���f���`��

// �N���X��`
class Screw : public GameObject
{
public:

	// �R���X�g���N�^
	Screw(std::string name = "Screw");

	// �f�X�g���N�^
	~Screw();

	// �X�V����
	void Update();

	// ������Ԃɖ߂�
	void ResetState();

	// ��]�֐�
	virtual void ObjRightSpin(bool Right = true);

	// ���Z�b�g�^�C��
	inline void ResetTime()
	{
		m_SpinFlg = false;
	}

	// �i�b�g�Ƃ̋����������ɂ��ĕԂ�
	float GetRatio()
	{
		float ratio = 1 - abs((m_Nut->GetPos().y - m_pos.y)) / m_SpinDistance;
		// �␳
		if (0.98f < ratio)
		{
			ratio = 1.0f;
		}
		else if (0.02f > ratio)
		{
			ratio = 0.0f;
		}

		return ratio;
	}

	//----�Z�b�g�֐�----

	// �������W���Z�b�g
	inline void SetInitePos(DirectX::XMFLOAT3 pos)
	{
		m_InitPos = pos;
	}

	// �i�b�g�Z�b�g
	void SetNut(GameObject* nut)
	{
		m_Nut = nut;
	}

	// �i�b�g�Ƃ̍Œ������Z�b�g
	void SetNutMaxDistance(float distance)
	{
		m_SpinDistance = distance;
	}

	// ���ʔ{���Z�b�g
	void SetMultiplier(float mul)
	{
		m_Multiplier = mul;
	}

	// ��]�́A��R�̓Z�b�g
	void SetSpinParam(float torque, float moment)
	{
		_spin->SetTorque(torque);
		_spin->SetMoment(moment);
	}

	//----�Q�b�g�֐�----

	// �X�s���t���O�擾
	bool GetSpinFlg()
	{
		return m_SpinFlg;
	}

	// ���ʔ{���擾
	float GetMultiplier()
	{
		return m_Multiplier;
	}

protected:
	//----�R���|�[�l���g----

	// �ړ��R���|�[�l���g
	Move* _move;

	// ��]�R���|�[�l���g
	Spin* _spin;

	// �{�b�N�X�R���C�_�[�R���|�[�l���g
	BoxCollider* _boxCollider;

	// 3D�`��R���|�[�l���g
	ModelRenderer3D* _modelRenderer3D;


	//----�����o�ϐ�----

	// �i�b�g
	GameObject* m_Nut;

	// �������W
	DirectX::XMFLOAT3 m_InitPos;

	// ��]�ʂ̌��ʔ{��
	float m_Multiplier;

	// �l�W�𓮂�����ő��
	float m_SpinDistance;

	// �񂳂�Ă���t���O
	bool m_SpinFlg;

	// SE�Đ��t���O
	bool m_SpinMaxPlayingSE;
};

#endif // __SCREW_H__