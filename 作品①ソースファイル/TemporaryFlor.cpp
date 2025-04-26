///////////////////////////////////////
//
// 一時的に出現する床ギミッククラス
//
// ネジの回し量によって一時的に出現する
// 回し量が満たなかったら消える
//
///////////////////////////////////////

// インクルード部
#include "TemporaryFloor.h"

// コンストラクタ
TemporaryFloor::TemporaryFloor(std::string name)
	: GimmickBase(name)
{
	// タグ設定
	m_tag = "TemporaryFloor";

	// 描画フラグを下げる
	_modelRenderer3D->SetDrawFlg(false);

	// 構造体情報初期化
	m_TemporaryFloorData.draw = false;
	m_TemporaryFloorData.nextObj = nullptr;
	m_TemporaryFloorData.preObj = nullptr;
}

// デストラクタ
TemporaryFloor::~TemporaryFloor()
{
}

// ターゲットオブジェクトの処理
void TemporaryFloor::Gimmick(int index, float rotY)
{
	//----変数宣言----

	// ネジの締め割合
	float ratio;
	
	// 目標割合
	float targetRatio;


	//----割合計算----

	// ネジの割合取得
	ratio = m_TargetScrew[index]->GetRatio();

	// 目標割合計算
	// 余裕を作るために一個前との間隔を少し空けるように計算する
	if (m_TemporaryFloorData.preObj)
	{
		targetRatio = 1.0f - 1.0f / ((float)m_TemporaryFloorData.totalNo * 2) * (m_TemporaryFloorData.myNo + m_TemporaryFloorData.preObj->myNo);
	}
	else
	{
		targetRatio = 1.0f - 1.0f / ((float)m_TemporaryFloorData.totalNo * 2) * m_TemporaryFloorData.myNo;
	}

	//----ゴール側から順に床となるオブジェクトを描画していく----

	// 目標割合に達してなかったら処理しない
	if (targetRatio > ratio) return;

	// 先の床の設定がされてないとき
	// もしくは先の床が描画されていたら
	if (!m_TemporaryFloorData.nextObj || m_TemporaryFloorData.nextObj->draw)
	{
		// 描画フラグを上げる
		_modelRenderer3D->SetDrawFlg(true);
		m_TemporaryFloorData.draw = true;
	}
}

// 通常のネジを回す方向と逆方向に回されたときに呼ぶ
void TemporaryFloor::InvertGimmick(int index, float rotY)
{
	//----変数宣言----

	// ネジの締め割合
	float ratio;

	// 目標割合
	float targetRatio;


	//----割合計算----

	// ネジの割合取得
	ratio = m_TargetScrew[index]->GetRatio();

	// 目標割合計算
	// 余裕を作るために一個前との間隔を少し空けるように計算する
	if (m_TemporaryFloorData.preObj)
	{
		targetRatio = 1.0f - 1.0f / ((float)m_TemporaryFloorData.totalNo * 2) * (m_TemporaryFloorData.myNo + m_TemporaryFloorData.preObj->myNo);
	}
	else
	{
		targetRatio = 1.0f - 1.0f / ((float)m_TemporaryFloorData.totalNo * 2) * m_TemporaryFloorData.myNo;
	}


	//----スタート側から順に床となるオブジェクトを消していく----

	// 目標割合を切ってなかったら処理しない
	if (targetRatio < ratio) return;

	// 一個前の床の設定がされてないとき
	// もしくは一個前の床が消されていたら
	if (!m_TemporaryFloorData.preObj || !m_TemporaryFloorData.preObj->draw)
	{
		// 描画フラグを下げる
		_modelRenderer3D->SetDrawFlg(false);
		m_TemporaryFloorData.draw = false;
	}
}