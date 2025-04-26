// �M�~�b�N���N���X

// �C���N���[�h�K�[�h
#ifndef __Gimmick_Base_H__
#define __Gimmick_Base_H__

// �C���N���[�h��
#include "GameObject.hpp"
#include "Screw.h"

// �R���|�[�l���g
#include "BoxCollider.h"		// �����蔻��
#include "ModelRenderer3D.h"	// 3D���f���`��

// �N���X��`
class GimmickBase : public GameObject
{
public:
	GimmickBase(std::string name);	// �R���X�g���N�^
	~GimmickBase();									// �f�X�g���N�^

	void Update();									// �X�V����

	// �^�[�Q�b�g�I�u�W�F�N�g�̏���
	virtual void Gimmick(int index, float rotY);
	// �ʏ�̃l�W���񂷕����Ƌt�����ɉ񂳂ꂽ�Ƃ��ɌĂ�
	virtual void InvertGimmick(int index, float rotY);

	// ���������I�u�W�F�N�g�̂��Ƃ̏���
	virtual void OnCollision(GameObject* obj);

	// �Z�b�g�֐�
	// �������W���Z�b�g
	inline void SetInitePos(DirectX::XMFLOAT3 pos)
	{
		m_InitPos = pos;
	}

	// �y�A�M�~�b�N�I�u�W�F�N�g�Z�b�g
	inline void SetPair(GameObject* pair)
	{
		m_PairGimmick = pair;
	}
	// �Ώۃl�W�Z�b�g
	inline void SetScrew(Screw* obj)
	{
		m_TargetScrew.push_back(obj);
		m_OldRotY.push_back(m_TargetScrew.back()->GetQuat().y);
	}
	// ���ʔ��]�t���O
	inline void SetInvertEffect(bool flg)
	{
		m_invertEffectFlg = flg;
	}
	// �n�ʂɓ��������t���O�ɐݒ�
	inline void SetGroundCollision(bool flg)
	{
		m_GroundCollision = flg;
		m_CollisionUpdate = flg;
	}

	// �Q�b�g�֐�
	inline GameObject* GetPair()
	{
		return m_PairGimmick;
	}
	// �n�ʂɓ��������t���O��Ԃ�
	inline bool GetGroundCollision()
	{
		return m_GroundCollision;
	}

protected:
	// �R���|�[�l���g
	BoxCollider* _boxCollider;			// �{�b�N�X�R���C�_�[�R���|�[�l���g
	ModelRenderer3D* _modelRenderer3D;	// 3D�`��R���|�[�l���g

	GameObject* m_PairGimmick;			// �y�A�̃M�~�b�N�I�u�W�F�N�g

	std::vector<Screw*> m_TargetScrew;	// �Ώۃl�W
	std::vector<float> m_OldRotY;		// �ߋ��p�x

	DirectX::XMFLOAT3 m_InitPos;		// �������W

	// �l�W���񂵂������ŌĂԊ֐����t�ɂ���
	bool m_invertEffectFlg;				// ���]�t���O
	bool m_CollisionUpdate;				// ����������̏������ʂ����t���O
	bool m_GroundCollision;				// �n�ʂɓ��������t���O
};

#endif // __Gimmick_Base_H__