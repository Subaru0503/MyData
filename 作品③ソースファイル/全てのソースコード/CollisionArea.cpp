//=================================================================
//
//	CollisionArea.cpp
//	�G���A����e�֘A
//
//=================================================================

// ========== �C���N���[�h�� ==========
#include "CollisionArea.h"
#include "CollisionAreaManager.h"
#include "Collision.h"

// ����G���A��\������B�f�o�b�O�p
void CCollisionArea::Draw(DirectX::XMFLOAT4X4* mat)
{
	// ----- �e���̉�]�s����v�Z ------
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
	DirectX::XMMATRIX xmat = S * T;

	// ------ �e���̍s��𓝍� ------
	xmat = DirectX::XMMatrixTranspose(xmat);	// �]�u

	 // ------ �V�F�[�_��������^�ɕϊ� ------
	DirectX::XMFLOAT4X4 fMat;				// �^�ϊ���s��i�[�p
	DirectX::XMStoreFloat4x4(&fMat, xmat);

	// ------ �l�X�V ------
	Geometory::SetWorld(fMat);				// �{�b�N�X�ɕϊ��s���ݒ�
	Geometory::SetView(mat[1]);
	Geometory::SetProjection(mat[2]);

	// ------ �`�� ------
	Geometory::DrawBox();
}

// ========== GetPos ==========
// ���@���F�Ȃ�
// �߂�l�FXMFLOAT3
// ���W��n��
// ==============================
DirectX::XMFLOAT3 CCollisionArea::GetPos()
{
	return m_scale;
}

// ========== GetScale ==========
// ���@���F�Ȃ�
// �߂�l�FXMFLOAT3
// �T�C�Y��n��
// ==============================
DirectX::XMFLOAT3 CCollisionArea::GetScale()
{
	return m_scale;
}

CCollisionArea::areaKind CCollisionArea::GetKind()
{
	return m_areakind;
}

// ========== SetPlayer ==========
// ���@���F
// CPlayer* �v���C���[�̎��̃|�C���^
// �߂�l�F�Ȃ�
// �v���C���[�̎��̂����炤
// ==============================
void CCollisionArea::SetPlayer(CPlayer* pPlayer)
{
	m_pPlayer = pPlayer;
}

// ========== SetObjList ==========
// ���@���F
// list<Object*>* �I�u�W�F�N�g���X�g�̎��̃|�C���^
// �߂�l�F�Ȃ�
// �I�u�W�F�N�g���X�g�̎��̂����炤
// ==============================
void CCollisionArea::SetObj(Object* pObj)
{
	m_pObject = pObj;
}

void CCollisionArea::InitObjHieght()
{
	if (CCollision::CheckCollisionRectToRect(m_pObject->GetPos(), m_pos, m_pObject->GetScale(), m_scale)) {
		if (m_pObject->GetKind() == Object::Kind::BISCUIT) { return; }	// �r�X�P�b�g�͏��O

		// ----- ����␳ -----
		switch (m_stage)	// �X�e�[�W�ɂ���č���̍�����ς���
		{
		case 1:	// �X�e�[�W�P
			// �n�ʂ̃Z�b�g
			switch (m_height)
			{
			case 0:
				m_pObject->SetRandHeight(STAGE1_HT0);
				break;
			case 1:
				m_pObject->SetRandHeight(STAGE1_HT1);
				break;
			case 2:
				m_pObject->SetRandHeight(STAGE1_HT2);
				break;
			}
			break;
		case 2:	// �X�e�[�W2
			// �n�ʂ̃Z�b�g
			switch (m_height)
			{
			case 0:
				m_pObject->SetRandHeight(STAGE2_HT0);
				break;
			case 1:
				m_pObject->SetRandHeight(STAGE2_HT1);
				break;
			case 2:
				m_pObject->SetRandHeight(STAGE2_HT2);
				break;
			}
			break;
		case 3:	// �X�e�[�W3
			// �n�ʂ̃Z�b�g
			switch (m_height)
			{
			case 0:
				m_pObject->SetRandHeight(STAGE3_HT0);
				break;
			case 1:
				m_pObject->SetRandHeight(STAGE3_HT1);
				break;
			case 2:
				m_pObject->SetRandHeight(STAGE3_HT2);
				break;
			}
			break;
		}
	}
}
