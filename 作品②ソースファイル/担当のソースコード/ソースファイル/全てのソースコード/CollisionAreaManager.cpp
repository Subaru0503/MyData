//=================================================================
//
//	CollisionAreaManager.cpp
//	�G���A����̃}�l�[�W���[
//
//=================================================================

// ========== �C���N���[�h�� ========== 
#include "CollisionAreaManager.h"

// ========== �萔�E�}�N����`==========
#define DEBUG_ON	(1)			// �f�o�b�O�p�i���s����j
#define DEBUG_OFF	(0)			// �f�o�b�O�p�i���s���Ȃ��j

// ========== �R���X�g���N�^ ==========
CCollisionAreaMng::CCollisionAreaMng()
	: m_randSlope(false)
{
}

// ========== �f�X�g���N�^ ==========
CCollisionAreaMng::~CCollisionAreaMng()
{
	// ���X�g���̂��ׂẴI�u�W�F�N�g�����
	for (CCollisionArea* pArea : m_areaList) {
		if (pArea != nullptr)
		{
			delete pArea;
		}
	}
	m_areaList.clear();// �S�v�f�폜
}

// �S�ẴG���A������s��
void CCollisionAreaMng::Update()
{
	m_randSlope = false;
	m_ht = false;
	m_pPlayer->SetRandSlope(false);

	// =-=-= �e�G���A�Ƃ̓����蔻�� =-=-=
	for (CCollisionArea* pArea : m_areaList) {	// �S�G���A�𔻒�
		// ----- �΁@�v���C���[ -----
		pArea->SetPlayer(m_pPlayer);		// Player���ݒ�
		pArea->Update(this);				// �����蔻�菈��

		// ----- �΁@�I�u�W�F�N�g -----
		if (pArea->GetKind() == CCollisionArea::areaKind::hill ||
			pArea->GetKind() == CCollisionArea::areaKind::slope ||
			pArea->GetKind() == CCollisionArea::areaKind::sea) {	// ����E�C�E��̏ꍇ
			for (Object* pObj : *m_pObjList) {
				pArea->SetObj(pObj);
				pArea->Update(this, true);
			}
		}
	}
}


// �C�ӂ̃G���A����������(BOX�Ƃ��ĕ\������)
void CCollisionAreaMng::Draw(DirectX::XMFLOAT4X4* mat)
{
	//for (CCollisionArea* pArea : m_areaList) {	// �S�G���A���m�F
	//	switch (pArea->GetKind())				// ��ނ��Ƃɉ����󋵂�ݒ肷��
	//	{
	//	case CCollisionArea::sea:		// �C(�s�N�̈�)
	//		if (DEBUG_OFF) { pArea->Draw(mat); }	// ON�Ȃ�`��
	//		break;
	//	case CCollisionArea::ground:	// �n�ʂ̎��
	//		if (DEBUG_OFF) { pArea->Draw(mat); }
	//		break;
	//	case CCollisionArea::hill:		// ����
	//		if (DEBUG_OFF) { pArea->Draw(mat); }
	//		break;
	//	case CCollisionArea::slope:		// ��
	//		if (DEBUG_OFF) { pArea->Draw(mat); }
	//		break;
	//	}
	//}
}

// ========== SetPlayer ==========
// ���@���F
// CPlayer* �v���C���[�̎��̃|�C���^
// �߂�l�F�Ȃ�
// �v���C���[�̎��̂�Ⴄ
// ============================== 
void CCollisionAreaMng::SetPlayer(CPlayer * pPlayer)
{
	m_pPlayer = pPlayer;
}

// �I�u�W�F�N�g���X�g���擾���A�������̏����ݒ������
void CCollisionAreaMng::SetObjList(list<Object*>* pObj)
{
	m_pObjList = pObj;

	// =-=-= �e�G���A�Ƃ̓����蔻�� =-=-=
	for (CCollisionArea* pArea : m_areaList) {	// �S�G���A�𔻒�

		if (pArea->GetKind() == CCollisionArea::areaKind::hill/*	||
			pArea->GetKind() == CCollisionArea::areaKind::slope*/) {	// ����̏ꍇ�̂ݔ���
			for (Object* pObj : *m_pObjList) {
				pArea->SetObj(pObj);
				pArea->InitObjHieght();
			}
		}
	}
}

// ========== GetAreaList ==========
// ���@���F�Ȃ�
// �߂�l�Flist<CCollisionArea*>*
// �G���A���X�g�̎��̂�n��
// ============================== 
list<CCollisionArea*>* CCollisionAreaMng::GetAreaList()
{
	return &m_areaList;
}

bool CCollisionAreaMng::isRandSlope()
{
	return m_randSlope;
}

bool CCollisionAreaMng::isHtCheck()
{
	return m_ht;
}

void CCollisionAreaMng::SethtCheck(bool is)
{
	m_ht = is;
}

void CCollisionAreaMng::SetRandSlepe(bool rand)
{
	m_randSlope = rand;
}

float CCollisionAreaMng::CheckHeight(int stage, int height)
{
	switch (stage)
	{
	case 1:
		switch (height)
		{
		case 0:
			return STAGE1_HT0;
			break;
		case 1:
			return STAGE1_HT1;
			break;
		case 2:
			return STAGE1_HT2;
			break;
		}
		break;
	case 2:
		switch (height)
		{
		case 0:
			return STAGE2_HT0;
			break;
		case 1:
			return STAGE2_HT1;
			break;
		case 2:
			return STAGE2_HT2;
			break;
		}
		break;
	case 3:
		switch (height)
		{
		case 0:
			return STAGE3_HT0;
			break;
		case 1:
			return STAGE3_HT1;
			break;
		case 2:
			return STAGE3_HT2;
			break;
		}
		break;
	}
}

