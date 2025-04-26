//=================================================================
//
//	CollisionAreaManager.cpp
//	エリア判定のマネージャー
//
//=================================================================

// ========== インクルード部 ========== 
#include "CollisionAreaManager.h"

// ========== 定数・マクロ定義==========
#define DEBUG_ON	(1)			// デバッグ用（実行する）
#define DEBUG_OFF	(0)			// デバッグ用（実行しない）

// ========== コンストラクタ ==========
CCollisionAreaMng::CCollisionAreaMng()
	: m_randSlope(false)
{
}

// ========== デストラクタ ==========
CCollisionAreaMng::~CCollisionAreaMng()
{
	// リスト内のすべてのオブジェクトを解放
	for (CCollisionArea* pArea : m_areaList) {
		if (pArea != nullptr)
		{
			delete pArea;
		}
	}
	m_areaList.clear();// 全要素削除
}

// 全てのエリア判定を行う
void CCollisionAreaMng::Update()
{
	m_randSlope = false;
	m_ht = false;
	m_pPlayer->SetRandSlope(false);

	// =-=-= 各エリアとの当たり判定 =-=-=
	for (CCollisionArea* pArea : m_areaList) {	// 全エリアを判定
		// ----- 対　プレイヤー -----
		pArea->SetPlayer(m_pPlayer);		// Player情報設定
		pArea->Update(this);				// 当たり判定処理

		// ----- 対　オブジェクト -----
		if (pArea->GetKind() == CCollisionArea::areaKind::hill ||
			pArea->GetKind() == CCollisionArea::areaKind::slope ||
			pArea->GetKind() == CCollisionArea::areaKind::sea) {	// 高台・海・坂の場合
			for (Object* pObj : *m_pObjList) {
				pArea->SetObj(pObj);
				pArea->Update(this, true);
			}
		}
	}
}


// 任意のエリアを可視化する(BOXとして表示する)
void CCollisionAreaMng::Draw(DirectX::XMFLOAT4X4* mat)
{
	//for (CCollisionArea* pArea : m_areaList) {	// 全エリアを確認
	//	switch (pArea->GetKind())				// 種類ごとに可視化状況を設定する
	//	{
	//	case CCollisionArea::sea:		// 海(不可侵領域)
	//		if (DEBUG_OFF) { pArea->Draw(mat); }	// ONなら描画
	//		break;
	//	case CCollisionArea::ground:	// 地面の種類
	//		if (DEBUG_OFF) { pArea->Draw(mat); }
	//		break;
	//	case CCollisionArea::hill:		// 高台
	//		if (DEBUG_OFF) { pArea->Draw(mat); }
	//		break;
	//	case CCollisionArea::slope:		// 坂
	//		if (DEBUG_OFF) { pArea->Draw(mat); }
	//		break;
	//	}
	//}
}

// ========== SetPlayer ==========
// 引　数：
// CPlayer* プレイヤーの実体ポインタ
// 戻り値：なし
// プレイヤーの実体を貰う
// ============================== 
void CCollisionAreaMng::SetPlayer(CPlayer * pPlayer)
{
	m_pPlayer = pPlayer;
}

// オブジェクトリストを取得し、高さ情報の初期設定をする
void CCollisionAreaMng::SetObjList(list<Object*>* pObj)
{
	m_pObjList = pObj;

	// =-=-= 各エリアとの当たり判定 =-=-=
	for (CCollisionArea* pArea : m_areaList) {	// 全エリアを判定

		if (pArea->GetKind() == CCollisionArea::areaKind::hill/*	||
			pArea->GetKind() == CCollisionArea::areaKind::slope*/) {	// 高台の場合のみ判定
			for (Object* pObj : *m_pObjList) {
				pArea->SetObj(pObj);
				pArea->InitObjHieght();
			}
		}
	}
}

// ========== GetAreaList ==========
// 引　数：なし
// 戻り値：list<CCollisionArea*>*
// エリアリストの実体を渡す
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

