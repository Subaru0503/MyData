///////////////////////////////////////
//
// �����蔻��N���X
// OBB�ɂ�铖���蔻��
// �I�u�W�F�N�g���Ƃ̕␳������
// 
///////////////////////////////////////

// �C���N���[�h�K�[�h
#ifndef __BOXCOLLIDER_H__
#define __BOXCOLLIDER_H__

// �C���N���[�h��
#include "Component.h"
#include <string>
#include "float3.h"

using namespace std;

// �N���X��`
class BoxCollider : public Component
{
public:
	// �R���X�g���N�^
	BoxCollider();

	// obb���m�̓����蔻��`�F�b�N
	bool CheckObb(GameObject* objA, GameObject* objB);

	// �������ɓ��e���ꂽ���������瓊�e���������Z�o
	float LenSegOnSeparateAxis(float3* Sep, float3* e1, float3* e2, float3* e3 = 0);

	// ���W�␳
	void FixPos(GameObject* objB);

	// �����o���ĕ␳
	bool PushAdjust(GameObject* objB);

	// �����݂̂̕␳������+�␳������
	bool CheckHeightOnly(GameObject* objB);

	// �ړ����͈̔͊O�ɂ��邩���肷��֐�
	bool FloorInSide(GameObject* objB);
	// �ړ����p�̍��W�␳
	void MoveGimmickFixPos(GameObject* objB);

	// �ʏ�␳
	void NormalFixPos(GameObject* objB);

	// �����蔻������Ȃ��^�O�ݒ�
	inline void SetTag(string tag)
	{
		m_noHitTag.push_back(tag);
	}

	// �^�O�`�F�b�N
	inline bool CheckTag(GameObject* objB)
	{
		for (auto it = m_noHitTag.begin(); it != m_noHitTag.end(); it++)
		{			
			// �ݒ肵�Ă�^�O��
			if (*it == objB->GetTag())
			{
				return true;	// ��������Ȃ��^�O������
			}
		}

		return false;			// �Ώۂ̃^�O���Ȃ�����
	}

	// �v���C���[�̍��W�^�񒆂ɕ␳
	DirectX::XMFLOAT3 PlayerAdjust(GameObject* obj);

	// �����̐��l���擾����
	int extractNumber(const string& str);

	//----�Z�b�g�֐�----

	// �ђʃt���O���Z�b�g
	inline void SetIsTrigger(bool flg)
	{
		m_isTrigger = flg;
	}

	// �T�C�Y���Z�b�g
	inline void SetScale(float3 scale)
	{
		m_Scale = scale;
	}

	// �����蔻��t���O�Z�b�g
	inline void SetCollision(bool collision)
	{
		m_Collision = collision;
	}

	//----�Q�b�g�֐�----

	// �ђʃt���O���擾
	inline bool GetIsTrigger()
	{
		return m_isTrigger;
	}

	// �T�C�Y���擾
	inline float3 GetScale()
	{
		return m_Scale;
	}

	// �����蔻��t���O���擾
	inline bool GetCollision()
	{
		return m_Collision;
	}

private:
	// ���蔲����Ԃɂ���t���O
	bool m_isTrigger;

	// �����蔻������Ȃ��^�O
	std::vector<string> m_noHitTag;

	// �����蔻��T�C�Y
	float3 m_Scale;

	// ���������t���O
	bool m_Collision;
};

#endif // __BOXCOLLIDER_H__