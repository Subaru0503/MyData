//=================================================================
//
//	CollisionArea.cpp
//	エリア判定親関連
//
//=================================================================

// ========== インクルード部 ==========
#include "CollisionArea.h"
#include "CollisionAreaManager.h"
#include "Collision.h"

// 判定エリアを表示する。デバッグ用
void CCollisionArea::Draw(DirectX::XMFLOAT4X4* mat)
{
	// ----- 各軸の回転行列を計算 ------
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
	DirectX::XMMATRIX xmat = S * T;

	// ------ 各軸の行列を統合 ------
	xmat = DirectX::XMMatrixTranspose(xmat);	// 転置

	 // ------ シェーダが扱える型に変換 ------
	DirectX::XMFLOAT4X4 fMat;				// 型変換後行列格納用
	DirectX::XMStoreFloat4x4(&fMat, xmat);

	// ------ 値更新 ------
	Geometory::SetWorld(fMat);				// ボックスに変換行列を設定
	Geometory::SetView(mat[1]);
	Geometory::SetProjection(mat[2]);

	// ------ 描画 ------
	Geometory::DrawBox();
}

// ========== GetPos ==========
// 引　数：なし
// 戻り値：XMFLOAT3
// 座標を渡す
// ==============================
DirectX::XMFLOAT3 CCollisionArea::GetPos()
{
	return m_scale;
}

// ========== GetScale ==========
// 引　数：なし
// 戻り値：XMFLOAT3
// サイズを渡す
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
// 引　数：
// CPlayer* プレイヤーの実体ポインタ
// 戻り値：なし
// プレイヤーの実体をもらう
// ==============================
void CCollisionArea::SetPlayer(CPlayer* pPlayer)
{
	m_pPlayer = pPlayer;
}

// ========== SetObjList ==========
// 引　数：
// list<Object*>* オブジェクトリストの実体ポインタ
// 戻り値：なし
// オブジェクトリストの実体をもらう
// ==============================
void CCollisionArea::SetObj(Object* pObj)
{
	m_pObject = pObj;
}

void CCollisionArea::InitObjHieght()
{
	if (CCollision::CheckCollisionRectToRect(m_pObject->GetPos(), m_pos, m_pObject->GetScale(), m_scale)) {
		if (m_pObject->GetKind() == Object::Kind::BISCUIT) { return; }	// ビスケットは除外

		// ----- 高台補正 -----
		switch (m_stage)	// ステージによって高台の高さを変える
		{
		case 1:	// ステージ１
			// 地面のセット
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
		case 2:	// ステージ2
			// 地面のセット
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
		case 3:	// ステージ3
			// 地面のセット
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
