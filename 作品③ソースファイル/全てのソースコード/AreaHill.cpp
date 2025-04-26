#include "CollisionAreaManager.h"
#include "AreaHill.h"
#include "Collision.h"
#include "Value.h"

//=====�}�N����`=====
#define REVISION_POS (1.05f)		// �ђʖh�~�̍��W�␳

CAreaHill::CAreaHill(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ, int height, int stage)
{
	m_pos = DirectX::XMFLOAT3(posX, posY, posZ);
	m_scale = DirectX::XMFLOAT3(scaleX, scaleY, scaleZ);
	m_height = height;
	m_areakind = hill;
	m_stage = stage;
}

// ���������炙��␳���R�ɓ����鏈�����鏈��
void CAreaHill::Update(CCollisionAreaMng* mng, bool objCollision)
{
	if (!objCollision) {
		// =-=-= �v���C���[ =-=-=
		if (mng->isRandSlope() || m_pPlayer->GetRandBiscuit()) { return; }	// ��o�蒆&�r�X�P�b�g��͔��肵�Ȃ�

		if (CCollision::CheckCollisionRectToRect(m_pPlayer->GetPos(), m_pos, m_pPlayer->GetScale(), m_scale)) {
			// ----- �R�����蔻�� -----
			if (m_pPlayer->GetRandHeight() < CCollisionAreaMng::CheckHeight(m_stage, m_height))
			{	// ���������̂�����Ȃ�
				SetPlayerPos(m_pPlayer->GetPos(), m_pos, m_pPlayer->GetScale(), m_scale);

				//return;	// �R�ɓ��������ꍇ�͍���␳���Ȃ�
			}

			// ----- ����␳ -----
			if (!mng->isHtCheck()) {
				m_pPlayer->SetRandHeight(CCollisionAreaMng::CheckHeight(m_stage, m_height));	// �X�e�[�W�ɂ���č���̍�����ς���
				mng->SethtCheck(true);
			}
		}
	}
	else {
		// =-=-= �I�u�W�F�N�g =-=-=
		if (m_pObject->GetRandSlope() || m_pObject->GetKind() == Object::Kind::BISCUIT) { return; }	// �r�X�P�b�g�͔��肵�Ȃ�

		if (CCollision::CheckCollisionRectToRect(m_pObject->GetPos(), m_pos, DirectX::XMFLOAT3(0.5, 0.5, 0.5), m_scale)) {
			// ----- �R�����蔻�� -----
			if (m_pObject->GetRandHeight() < m_height && m_pObject->IsMove()) {	// ���������̂�����Ȃ�
				m_pObject->SetPos(m_pObject->GetOldPos());

				//return;	// �R�ɓ��������ꍇ�͍���␳���Ȃ�
			}

			// ----- ����␳ -----
			m_pObject->SetRandHeight(CCollisionAreaMng::CheckHeight(m_stage, m_height));
		}
	}
}


// ========== SetPlayerPos ==========
// ���@���F
// XMFLOAT3 Pos1	�ΏۂP�̒��S���W
// XMFLOAT3 Pos2	�ΏۂQ�̒��S���W
// XMFLOAT3	Scale1	�ΏۂP�̑傫��
// XMFLOAT3	Scale2	�ΏۂQ�̑傫��
// �߂�l�F�Ȃ�
// �v���C���[�̍��W��XYZ�e�v�f���ݒ�
// ==================================
void CAreaHill::SetPlayerPos(DirectX::XMFLOAT3 Pos1, DirectX::XMFLOAT3 Pos2,
	DirectX::XMFLOAT3 Scale1, DirectX::XMFLOAT3 Scale2)
{
	//---�X�P�[���̔��a����
	DirectX::XMFLOAT3 SizeHalf1;
	SizeHalf1.x = Scale1.x / 2.0f;
	SizeHalf1.y = Scale1.y / 2.0f;
	SizeHalf1.z = Scale1.z / 2.0f;
	DirectX::XMFLOAT3 SizeHalf2;
	SizeHalf2.x = Scale2.x / 2.0f;
	SizeHalf2.y = Scale2.y / 2.0f;
	SizeHalf2.z = Scale2.z / 2.0f;

	//---Y���A�����̊ђʖh�~
	if (Pos1.y < Pos2.y + SizeHalf2.y && m_pPlayer->GetOldPos().y > Pos2.y + SizeHalf2.y)
	{
		// ----- ����␳ -----
		m_pPlayer->SetPosY(Pos2.y + SizeHalf2.y + SizeHalf1.y * REVISION_POS);
	}
	//---���Ȃ����XZ���̊ђʖh�~
	else
	{
		if (Pos1.x - SizeHalf1.x < Pos2.x + SizeHalf2.x && m_pPlayer->GetOldPos().x - SizeHalf1.x > Pos2.x + SizeHalf2.x)
		{
			m_pPlayer->SetPosX(Pos2.x + SizeHalf2.x + SizeHalf1.x * REVISION_POS);
		}
		if (Pos1.x + SizeHalf1.x > Pos2.x - SizeHalf2.x && m_pPlayer->GetOldPos().x + SizeHalf1.x < Pos2.x - SizeHalf2.x)
		{
			m_pPlayer->SetPosX(Pos2.x - SizeHalf2.x - SizeHalf1.x * REVISION_POS);
		}
		if (Pos1.z - SizeHalf1.z < Pos2.z + SizeHalf2.z && m_pPlayer->GetOldPos().z - SizeHalf1.z > Pos2.z + SizeHalf2.z)
		{
			m_pPlayer->SetPosZ(Pos2.z + SizeHalf2.z + SizeHalf1.z * REVISION_POS);
		}
		if (Pos1.z + SizeHalf1.z > Pos2.z - SizeHalf2.z && m_pPlayer->GetOldPos().z + SizeHalf1.z < Pos2.z - SizeHalf2.z)
		{
			m_pPlayer->SetPosZ(Pos2.z - SizeHalf2.z - SizeHalf1.z * REVISION_POS);
		}
	}
}

void CAreaHill::SetObjectPos(DirectX::XMFLOAT3 Pos1, DirectX::XMFLOAT3 Pos2, DirectX::XMFLOAT3 Scale1, DirectX::XMFLOAT3 Scale2)
{
	//---�X�P�[���̔��a����
	DirectX::XMFLOAT3 SizeHalf1;
	SizeHalf1.x = Scale1.x / 2.0f;
	SizeHalf1.y = Scale1.y / 2.0f;
	SizeHalf1.z = Scale1.z / 2.0f;
	DirectX::XMFLOAT3 SizeHalf2;
	SizeHalf2.x = Scale2.x / 2.0f;
	SizeHalf2.y = Scale2.y / 2.0f;
	SizeHalf2.z = Scale2.z / 2.0f;

	if (Pos1.x - SizeHalf1.x < Pos2.x + SizeHalf2.x && m_pObject->GetOldPos().x - SizeHalf1.x > Pos2.x + SizeHalf2.x)
	{
		m_pObject->SetPosX(Pos2.x + SizeHalf2.x + SizeHalf1.x * REVISION_POS);
	}
	if (Pos1.x + SizeHalf1.x > Pos2.x - SizeHalf2.x && m_pObject->GetOldPos().x + SizeHalf1.x < Pos2.x - SizeHalf2.x)
	{
		m_pObject->SetPosX(Pos2.x - SizeHalf2.x - SizeHalf1.x * REVISION_POS);
	}
	if (Pos1.z - SizeHalf1.z < Pos2.z + SizeHalf2.z && m_pObject->GetOldPos().z - SizeHalf1.z > Pos2.z + SizeHalf2.z)
	{
		m_pObject->SetPosZ(Pos2.z + SizeHalf2.z + SizeHalf1.z * REVISION_POS);
	}
	if (Pos1.z + SizeHalf1.z > Pos2.z - SizeHalf2.z && m_pObject->GetOldPos().z + SizeHalf1.z < Pos2.z - SizeHalf2.z)
	{
		m_pObject->SetPosZ(Pos2.z - SizeHalf2.z - SizeHalf1.z * REVISION_POS);
	}
}
