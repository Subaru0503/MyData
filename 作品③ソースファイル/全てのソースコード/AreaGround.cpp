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

// 当たったら足音SEを変える
void CAreaGround::Update(CCollisionAreaMng* mng, bool b)
{
	// ----- 今いる地面の種類を設定 -----
	if ((CAreaGround::kind)m_pPlayer->GetRandKind() != m_kind) {	// 今乗っている種類以外と判定
		if (CCollision::CheckCollisionRectToRect(m_pPlayer->GetPos(), m_pos, m_pPlayer->GetScale(), m_scale)) {	// 範囲内なら
			m_pPlayer->SetRandKind((int)m_kind);																// 現在プレイヤーが立ってる地面の種類を変更
		}
	}
}