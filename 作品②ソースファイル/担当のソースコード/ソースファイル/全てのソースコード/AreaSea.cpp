#include "AreaSea.h"
#include "Collision.h"
#include "CollisionAreaManager.h"

#define REVISION_POS (1.05f)		// 貫通防止の座標補正
#define CLIMB_STAIRS (0.0f)			// 上れる段差の高さ

CAreaSea::CAreaSea(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ)
{
	m_pos = DirectX::XMFLOAT3(posX, posY, posZ);
	m_scale = DirectX::XMFLOAT3(scaleX, scaleY, scaleZ);
	m_areakind = sea;
}

// 当たったらめり込まないようにする処理
void CAreaSea::Update(CCollisionAreaMng* mng, bool objCollision)
{
	if (!objCollision) {
		if (CCollision::CheckCollisionRectToRect(m_pPlayer->GetPos(), m_pos, m_pPlayer->GetScale(), m_scale))
		{
			//---スケールの半径準備
			DirectX::XMFLOAT3 SizeHalf1;
			SizeHalf1.x = m_pPlayer->GetScale().x / 2.0f;
			SizeHalf1.y = m_pPlayer->GetScale().y / 2.0f;
			SizeHalf1.z = m_pPlayer->GetScale().z / 2.0f;
			DirectX::XMFLOAT3 SizeHalf2;
			SizeHalf2.x = m_scale.x / 2.0f;
			SizeHalf2.y = m_scale.y / 2.0f;
			SizeHalf2.z = m_scale.z / 2.0f;

			//---Y軸、高さの貫通防止
			if (m_pPlayer->GetPos().y < m_pos.y + SizeHalf2.y && m_pPlayer->GetOldPos().y > m_pos.y + SizeHalf2.y)
			{
				m_pPlayer->SetPosY(m_pos.y + SizeHalf2.y + SizeHalf1.y * REVISION_POS);
			}

			//---段差を上る
			if ((m_pos.y + SizeHalf2.y - m_pPlayer->GetPos().y) <= CLIMB_STAIRS)
			{
				m_pPlayer->SetPosY(m_pos.y + SizeHalf2.y);
			}
			//---上れなければXZ軸の貫通防止
			else
			{
				if (m_pPlayer->GetPos().x - SizeHalf1.x < m_pos.x + SizeHalf2.x && m_pPlayer->GetOldPos().x - SizeHalf1.x > m_pos.x + SizeHalf2.x)
				{
					m_pPlayer->SetPosX(m_pos.x + SizeHalf2.x + SizeHalf1.x * REVISION_POS);
				}
				if (m_pPlayer->GetPos().x + SizeHalf1.x > m_pos.x - SizeHalf2.x && m_pPlayer->GetOldPos().x + SizeHalf1.x < m_pos.x - SizeHalf2.x)
				{
					m_pPlayer->SetPosX(m_pos.x - SizeHalf2.x - SizeHalf1.x * REVISION_POS);
				}
				if (m_pPlayer->GetPos().z - SizeHalf1.z < m_pos.z + SizeHalf2.z && m_pPlayer->GetOldPos().z - SizeHalf1.z > m_pos.z + SizeHalf2.z)
				{
					m_pPlayer->SetPosZ(m_pos.z + SizeHalf2.z + SizeHalf1.z * REVISION_POS);
				}
				if (m_pPlayer->GetPos().z + SizeHalf1.z > m_pos.z - SizeHalf2.z && m_pPlayer->GetOldPos().z + SizeHalf1.z < m_pos.z - SizeHalf2.z)
				{
					m_pPlayer->SetPosZ(m_pos.z - SizeHalf2.z - SizeHalf1.z * REVISION_POS);
				}
			}
			//m_pPlayer->SetPos(m_pPlayer->GetOldPos());	// 仮めり込み補正。後で引っ掛かりなしverに変更
		}
	}
	else {
		if (CCollision::CheckCollisionRectToRect(m_pObject->GetPos(), m_pos, m_pObject->GetScale(), m_scale)) {
			m_pObject->SetPos(DirectX::XMFLOAT3(m_pObject->GetOldPos().x, m_pObject->GetPos().y, m_pObject->GetOldPos().z ));
		}
	}
}