#include "AreaGround.h"
#include "Collision.h"
#include "CollisionAreaManager.h"

CAreaGround::CAreaGround(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ, int kind)
{
	m_pos = DirectX::XMFLOAT3(posX, posY, posZ);
	m_scale = DirectX::XMFLOAT3(scaleX, scaleY, scaleZ);
	m_kind = (CAreaGround::kind)kind;
	m_areakind = ground;
}

// ���������瑫��SE��ς���
void CAreaGround::Update(CCollisionAreaMng* mng, bool b)
{
	// ----- ������n�ʂ̎�ނ�ݒ� -----
	if ((CAreaGround::kind)m_pPlayer->GetRandKind() != m_kind) {	// ������Ă����ވȊO�Ɣ���
		if (CCollision::CheckCollisionRectToRect(m_pPlayer->GetPos(), m_pos, m_pPlayer->GetScale(), m_scale)) {	// �͈͓��Ȃ�
			m_pPlayer->SetRandKind((int)m_kind);																// ���݃v���C���[�������Ă�n�ʂ̎�ނ�ύX
		}
	}
}