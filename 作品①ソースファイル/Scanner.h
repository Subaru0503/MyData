// �I�u�W�F�N�g�X�L���i�N���X

// �C���N���[�h�K�[�h
#ifndef __SCANNER_H__
#define __SCANNER_H__

// �C���N���[�h��
#include "Component.h"
#include "float3.h"

// �N���X��`
class Scanner : public Component
{
public:
	Scanner();	// �R���X�g���N�^

	// obb���m�̓����蔻��`�F�b�N
	bool CheckObb(GameObject* objA, GameObject* objB);

	// �������ɓ��e���ꂽ���������瓊�e���������Z�o
	float LenSegOnSeparateAxis(float3* Sep, float3* e1, float3* e2, float3* e3 = 0);

	// �v���C���[�̍��W�^�񒆂ɕ␳
	DirectX::XMFLOAT3 PlayerAdjust(GameObject* obj);

	// �Z�b�g�֐�
	inline void SetScale(float3 scale)
	{
		m_Scale = scale;
	}
	inline void SetCollision(bool flg)
	{
		m_Collision = flg;
	}

	// �Q�b�g�֐�

	inline bool GetCollision()
	{
		return m_Collision;
	}

private:
	bool m_Collision;	// ���������t���O
	float3 m_Scale;		// �����蔻��T�C�Y
};

#endif // __SCANNER_H__