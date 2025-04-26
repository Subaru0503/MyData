#include "CollisionAreaManager.h"
#include "AreaHill.h"
#include "Collision.h"
#include "Value.h"

//=====マクロ定義=====
#define REVISION_POS (1.05f)		// 貫通防止の座標補正

CAreaHill::CAreaHill(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ, int height, int stage)
{
	m_pos = DirectX::XMFLOAT3(posX, posY, posZ);
	m_scale = DirectX::XMFLOAT3(scaleX, scaleY, scaleZ);
	m_height = height;
	m_areakind = hill;
	m_stage = stage;
}

// あったたらｙを補正＆崖に当たる処理する処理
void CAreaHill::Update(CCollisionAreaMng* mng, bool objCollision)
{
	if (!objCollision) {
		// =-=-= プレイヤー =-=-=
		if (mng->isRandSlope() || m_pPlayer->GetRandBiscuit()) { return; }	// 坂登り中&ビスケット上は判定しない

		if (CCollision::CheckCollisionRectToRect(m_pPlayer->GetPos(), m_pos, m_pPlayer->GetScale(), m_scale)) {
			// ----- 崖当たり判定 -----
			if (m_pPlayer->GetRandHeight() < CCollisionAreaMng::CheckHeight(m_stage, m_height))
			{	// 当たったのが高台なら
				SetPlayerPos(m_pPlayer->GetPos(), m_pos, m_pPlayer->GetScale(), m_scale);

				//return;	// 崖に当たった場合は高台補正しない
			}

			// ----- 高台補正 -----
			if (!mng->isHtCheck()) {
				m_pPlayer->SetRandHeight(CCollisionAreaMng::CheckHeight(m_stage, m_height));	// ステージによって高台の高さを変える
				mng->SethtCheck(true);
			}
		}
	}
	else {
		// =-=-= オブジェクト =-=-=
		if (m_pObject->GetRandSlope() || m_pObject->GetKind() == Object::Kind::BISCUIT) { return; }	// ビスケットは判定しない

		if (CCollision::CheckCollisionRectToRect(m_pObject->GetPos(), m_pos, DirectX::XMFLOAT3(0.5, 0.5, 0.5), m_scale)) {
			// ----- 崖当たり判定 -----
			if (m_pObject->GetRandHeight() < m_height && m_pObject->IsMove()) {	// 当たったのが高台なら
				m_pObject->SetPos(m_pObject->GetOldPos());

				//return;	// 崖に当たった場合は高台補正しない
			}

			// ----- 高台補正 -----
			m_pObject->SetRandHeight(CCollisionAreaMng::CheckHeight(m_stage, m_height));
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
void CAreaHill::SetPlayerPos(DirectX::XMFLOAT3 Pos1, DirectX::XMFLOAT3 Pos2,
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
		// ----- 高台補正 -----
		m_pPlayer->SetPosY(Pos2.y + SizeHalf2.y + SizeHalf1.y * REVISION_POS);
	}
	//---上れなければXZ軸の貫通防止
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
