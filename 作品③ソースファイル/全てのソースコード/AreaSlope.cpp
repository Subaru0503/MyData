#include "AreaSlope.h"
#include "CollisionAreaManager.h"
#include "Collision.h"

#define REVISION_POS (1.05f)		// 貫通防止の座標補正

CAreaSlope::CAreaSlope(int lowHt, float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ, int direct, int height, int stage)
{
	m_lowHt = lowHt;
	m_pos = DirectX::XMFLOAT3(posX, posY, posZ);
	m_scale = DirectX::XMFLOAT3(scaleX, scaleY, scaleZ);
	m_height = height;
	m_direct = direct;
	m_areakind = slope;
	m_stage = stage;
}

// 正面方向から当たったら坂を上がる処理
void CAreaSlope::Update(CCollisionAreaMng* mng, bool objCollition)
{
	if (!objCollition) {
		// =-=-= プレイヤー =-=-=
		if (CCollision::CheckCollisionRectToRect(m_pPlayer->GetPos(), m_pos, m_pPlayer->GetScale(), m_scale)) {
			CheckSlopePlayer(mng);	// 坂の当たり判定＆坂でのｙ補正
		}
	}
	else {
		// =-=-= オブジェクト =-=-=
		if (CCollision::CheckCollisionRectToRect(m_pObject->GetPos(), m_pos, m_pObject->GetScale(), m_scale)) {
			CheckSlopeObj(mng);	// 坂の当たり判定＆坂でのｙ補正
		}
	}
}

void CAreaSlope::CheckSlopePlayer(CCollisionAreaMng* mng)
{
	// =-=-= 準備 =-=-=
	float rate;			// 坂上での位置
	float slopeHt;		// 坂の高さ
	slopeHt = CCollisionAreaMng::CheckHeight(m_stage, m_height) - m_lowHt;

	if (m_direct % 2) {	// z向き
		if (m_pos.x - m_scale.x / 2.0f < m_pPlayer->GetOldPos().x && m_pPlayer->GetOldPos().x < m_pos.x + m_scale.x / 2.0f) {
			// 坂を上り下りしている
			m_pPlayer->SetRandSlope(true);
			m_pPlayer->SetRandHeight(m_height);
			mng->SetRandSlepe(true);
		}
		else {	// 坂の側面に当たった
			// 外に出す判定
			m_pPlayer->SetRandSlope(false);
			mng->SetRandSlepe(false);
			SetPlayerPos(m_pPlayer->GetPos(), m_pos, m_pPlayer->GetScale(), m_scale);
			return;
		}
		if (!CCollision::CheckCollisionRectToPoint(m_pos, m_pPlayer->GetPos(), m_scale)) { return; }

		// ----- y補正処理
		if (m_direct == 1) {
			rate = ((m_pPlayer->GetPos().z - (m_pos.z - m_scale.z / 2.0f)) / m_scale.z);
			m_pPlayer->SetPos(DirectX::XMFLOAT3(m_pPlayer->GetPos().x, slopeHt * rate + m_lowHt, m_pPlayer->GetPos().z));
		}
		else {
			rate = (((m_pos.z + m_scale.z / 2.0f) - m_pPlayer->GetPos().z) / m_scale.z);
			m_pPlayer->SetPos(DirectX::XMFLOAT3(m_pPlayer->GetPos().x, slopeHt * rate + m_lowHt, m_pPlayer->GetPos().z));
		}
	}
	else {// x向き
		if (m_pos.z - m_scale.z / 2.0f < m_pPlayer->GetOldPos().z && m_pPlayer->GetOldPos().z < m_pos.z + m_scale.z / 2.0f) {
			// 坂を上り下りしている
			m_pPlayer->SetRandSlope(true);
			m_pPlayer->SetRandHeight(m_height);
			mng->SetRandSlepe(true);
		}
		else {	// 坂の側面に当たった
			// 外に出す判定
			m_pPlayer->SetRandSlope(false);
			mng->SetRandSlepe(false);
			SetPlayerPos(m_pPlayer->GetPos(), m_pos, m_pPlayer->GetScale(), m_scale);
			return;
		}
		if (!CCollision::CheckCollisionRectToPoint(m_pos, m_pPlayer->GetPos(), m_scale)) { return; }

		// ----- y補正処理
		if (m_direct == 2) {
			rate = ((m_pPlayer->GetPos().x - (m_pos.x - m_scale.x / 2.0f)) / m_scale.x);
			m_pPlayer->SetPos(DirectX::XMFLOAT3(m_pPlayer->GetPos().x, slopeHt * rate + m_lowHt, m_pPlayer->GetPos().z));
		}
		else {
			rate = (((m_pos.x + m_scale.x / 2.0f) - m_pPlayer->GetPos().x) / m_scale.x);
			m_pPlayer->SetPos(DirectX::XMFLOAT3(m_pPlayer->GetPos().x, slopeHt * rate + m_lowHt, m_pPlayer->GetPos().z));
		}
	}
}

void CAreaSlope::CheckSlopeObj(CCollisionAreaMng * mng)
{
	float rate;			// 坂上での位置
	float slopeHt;		// 坂の高さ
	slopeHt = CCollisionAreaMng::CheckHeight(m_stage, m_height) - m_lowHt;

	if (m_direct % 2) {	// z向き
		if (m_pos.x - m_scale.x / 2.0f < m_pObject->GetOldPos().x && m_pObject->GetOldPos().x < m_pos.x + m_scale.x / 2.0f) {
			// 坂を上り下りしている
			m_pObject->SetRandSlope(true);
			m_pObject->SetRandHeight(m_height);
			//mng->SetRandSlepe(true);
		}
		else {	// 坂の側面に当たった
			// 外に出す判定
			m_pObject->SetRandSlope(false);
			//mng->SetRandSlepe(false);
			SetObjectPos(m_pObject->GetPos(), m_pos, m_pObject->GetScale(), m_scale);
			return;
		}

		// ----- y補正処理
		if (m_direct == 1) {
			rate = ((m_pObject->GetPos().z - (m_pos.z - m_scale.z / 2.0f)) / m_scale.z);
			m_pObject->SetPos(DirectX::XMFLOAT3(m_pObject->GetPos().x, slopeHt * rate + m_lowHt, m_pObject->GetPos().z));
		}
		else {
			rate = (((m_pos.z + m_scale.z / 2.0f) - m_pObject->GetPos().z) / m_scale.z);
			m_pObject->SetPos(DirectX::XMFLOAT3(m_pObject->GetPos().x, slopeHt * rate + m_lowHt, m_pObject->GetPos().z));
		}
	}
	else {// x向き
		if (m_pos.z - m_scale.z / 2.0f < m_pObject->GetOldPos().z && m_pObject->GetOldPos().z < m_pos.z + m_scale.z / 2.0f) {
			// 坂を上り下りしている
			m_pObject->SetRandSlope(true);
			m_pObject->SetRandHeight(m_height);
			//mng->SetRandSlepe(true);
		}
		else {	// 坂の側面に当たった
			// 外に出す判定
			m_pObject->SetRandSlope(false);
			//mng->SetRandSlepe(false);
			SetObjectPos(m_pObject->GetPos(), m_pos, m_pObject->GetScale(), m_scale);
			return;
		}

		// ----- y補正処理
		if (m_direct == 2) {
			rate = ((m_pObject->GetPos().x - (m_pos.x - m_scale.x / 2.0f)) / m_scale.x);
			m_pObject->SetPos(DirectX::XMFLOAT3(m_pObject->GetPos().x, slopeHt * rate + m_lowHt, m_pObject->GetPos().z));
		}
		else {
			rate = (((m_pos.x + m_scale.x / 2.0f) - m_pObject->GetPos().x) / m_scale.x);
			m_pObject->SetPos(DirectX::XMFLOAT3(m_pObject->GetPos().x, slopeHt * rate + m_lowHt, m_pObject->GetPos().z));
		}
	}
}

// ========== SetPlayerPos ==========
// 引　数：
// XMFLOAT3 Pos1	対象１の中心座標
// XMFLOAT3 Pos2	対象２の中心座標
// XMFLOAT3	Scale1	対象１の大きさ
// XMFLOAT3	Scale2	対象２の大きさ
// 戻り値：なし
// プレイヤーの座標をXYZ各要素ずつ設定
// ==================================
void CAreaSlope::SetPlayerPos(DirectX::XMFLOAT3 Pos1, DirectX::XMFLOAT3 Pos2,
	DirectX::XMFLOAT3 Scale1, DirectX::XMFLOAT3 Scale2)
{
	//---スケールの半径準備
	DirectX::XMFLOAT3 SizeHalf1;
	SizeHalf1.x = Scale1.x / 2.0f;
	SizeHalf1.y = Scale1.y / 2.0f;
	SizeHalf1.z = Scale1.z / 2.0f;
	DirectX::XMFLOAT3 SizeHalf2;
	SizeHalf2.x = Scale2.x / 2.0f;
	SizeHalf2.y = Scale2.y / 2.0f;
	SizeHalf2.z = Scale2.z / 2.0f;

	//---Y軸、高さの貫通防止
	if (Pos1.y < Pos2.y + SizeHalf2.y && m_pPlayer->GetOldPos().y > Pos2.y + SizeHalf2.y)
	{
		m_pPlayer->SetPosY(Pos2.y + SizeHalf2.y + SizeHalf1.y * REVISION_POS);
	}


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

void CAreaSlope::SetObjectPos(DirectX::XMFLOAT3 Pos1, DirectX::XMFLOAT3 Pos2, DirectX::XMFLOAT3 Scale1, DirectX::XMFLOAT3 Scale2)
{
	//---スケールの半径準備
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
