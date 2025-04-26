#include "AreaSea.h"
#include "Collision.h"
#include "CollisionAreaManager.h"

#define REVISION_POS (1.05f)		// ŠÑ’Ê–hŽ~‚ÌÀ•W•â³
#define CLIMB_STAIRS (0.0f)			// ã‚ê‚é’i·‚Ì‚‚³

CAreaSea::CAreaSea(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ)
{
	m_pos = DirectX::XMFLOAT3(posX, posY, posZ);
	m_scale = DirectX::XMFLOAT3(scaleX, scaleY, scaleZ);
	m_areakind = sea;
}

// “–‚½‚Á‚½‚ç‚ß‚èž‚Ü‚È‚¢‚æ‚¤‚É‚·‚éˆ—
void CAreaSea::Update(CCollisionAreaMng* mng, bool objCollision)
{
	if (!objCollision) {
		if (CCollision::CheckCollisionRectToRect(m_pPlayer->GetPos(), m_pos, m_pPlayer->GetScale(), m_scale))
		{
			//---ƒXƒP[ƒ‹‚Ì”¼Œa€”õ
			DirectX::XMFLOAT3 SizeHalf1;
			SizeHalf1.x = m_pPlayer->GetScale().x / 2.0f;
			SizeHalf1.y = m_pPlayer->GetScale().y / 2.0f;
			SizeHalf1.z = m_pPlayer->GetScale().z / 2.0f;
			DirectX::XMFLOAT3 SizeHalf2;
			SizeHalf2.x = m_scale.x / 2.0f;
			SizeHalf2.y = m_scale.y / 2.0f;
			SizeHalf2.z = m_scale.z / 2.0f;

			//---YŽ²A‚‚³‚ÌŠÑ’Ê–hŽ~
			if (m_pPlayer->GetPos().y < m_pos.y + SizeHalf2.y && m_pPlayer->GetOldPos().y > m_pos.y + SizeHalf2.y)
			{
				m_pPlayer->SetPosY(m_pos.y + SizeHalf2.y + SizeHalf1.y * REVISION_POS);
			}

			//---’i·‚ðã‚é
			if ((m_pos.y + SizeHalf2.y - m_pPlayer->GetPos().y) <= CLIMB_STAIRS)
			{
				m_pPlayer->SetPosY(m_pos.y + SizeHalf2.y);
			}
			//---ã‚ê‚È‚¯‚ê‚ÎXZŽ²‚ÌŠÑ’Ê–hŽ~
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
			//m_pPlayer->SetPos(m_pPlayer->GetOldPos());	// ‰¼‚ß‚èž‚Ý•â³BŒã‚Åˆø‚ÁŠ|‚©‚è‚È‚µver‚É•ÏX
		}
	}
	else {
		if (CCollision::CheckCollisionRectToRect(m_pObject->GetPos(), m_pos, m_pObject->GetScale(), m_scale)) {
			m_pObject->SetPos(DirectX::XMFLOAT3(m_pObject->GetOldPos().x, m_pObject->GetPos().y, m_pObject->GetOldPos().z ));
		}
	}
}