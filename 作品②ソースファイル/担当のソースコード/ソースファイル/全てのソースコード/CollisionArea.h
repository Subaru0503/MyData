#ifndef COLLISION_AREA_H
#define COLLISION_AREA_H

// ========== �C���N���[�h�� ==========
#include "Player.h"
#include "ObjectManager.h"
#include <DirectXMath.h>
#include "Geometory.h"
class CCollisionAreaMng;
#include <list>

// ========== �N���X ==========
class CCollisionArea
{
public:// �p�����[�^
	enum areaKind {
		sea = 1,
		ground,
		hill,
		slope,
	};

public:// �֐�
	CCollisionArea() {}
	virtual ~CCollisionArea() {}

	virtual void Update(CCollisionAreaMng* mng, bool objCollision = false) = 0;
	void Draw(DirectX::XMFLOAT4X4* mat);		// �����Ԃ�����
	DirectX::XMFLOAT3 GetPos();					// ���W�n��
	DirectX::XMFLOAT3 GetScale();				// �T�C�Y�n��
	areaKind GetKind();							// ����̎�ޓn��
	void SetPlayer(CPlayer* pPlayer);			// �v���C���[�̍��W�E�T�C�Y���擾
	void SetObj(Object* pObj);					// �I�u�W�F�N�g���X�g�擾
	void InitObjHieght();						// 

protected:
	int m_stage;								// ���X�e�[�W��
	DirectX::XMFLOAT3 m_pos, m_scale;			// ���W�E�T�C�Y
	areaKind m_areakind;						// ����̎��
	CPlayer* m_pPlayer;							// �v���C���[���󂯎��p
	Object* m_pObject;							// �I�u�W�F�N�g�󂯎��p
	int m_height;								// �V�ʂ̍���(�`�i��)
	int m_lowHt;								// ���(�ݒu�ʒu)�̍���(�`�i��)
};

#endif // !COLLISION_AREA_H