///////////////////////////////////////
//
// チェックポイントを順に移動するギミッククラス
//
// 登録したチェックポイントを辿っていく
//
///////////////////////////////////////

// インクルード部
#include "CheckPointPath.h"

// システム
#include "Input.h"
#include <math.h>

// コンストラクタ
CheckPointPath::CheckPointPath(std::string name)
	: GimmickBase(name)
{
	m_tag = "CheckPointPath";

	//----コンポーネント追加----

	// 移動
	AddComponent<Move>();

	//----コンポーネント取得----
	_move = GetComponent<Move>();
}

// デストラクタ
CheckPointPath::~CheckPointPath()
{
	// メモリを削除
	std::vector<MovePath>().swap(m_CheckPoint);
}

// 初期状態に戻す
// オブジェクトをシーンが始まったときの状態に戻す
void CheckPointPath::ResetState()
{
	// 初期座標に戻す
	m_pos = m_InitPos;

	// 初期の目指すチェックポイントに設定
	m_TargetCheckpoint = &m_CheckPoint[0];
}

// ターゲットオブジェクトの処理
void CheckPointPath::Gimmick(int index, float rotY)
{
	// チェックポイントが設定されていなかったら処理しない
	if (!m_TargetCheckpoint) return;

	// 移動量セット
	_move->SetMove(0.1f);

	// 移動ギミック
	MoveGimmick();
}

// 通常のネジを回す方向と逆方向に回されたときに呼ぶ
void CheckPointPath::InvertGimmick(int index, float rotY)
{
	// チェックポイントが設定されてなかったら処理しない
	if (!m_TargetCheckpoint) return;

	// 移動量セット
	_move->SetMove(0.1f);

	// 逆方向に移動ギミック
	ReverseMoveGimmick();
}

// 移動ギミック
void CheckPointPath::MoveGimmick()
{
	// データ型を変換(計算しやすいように)
	float3 pos = float3::Tofloat3(m_pos);

	// 次のチェックポイント - 現在の座標
	float3 N = m_TargetCheckpoint->pos - pos;

	// チェックポイントまでの距離を計算
	float distance = float3::distance(m_TargetCheckpoint->pos, pos);

	// 方向を正規化
	N = N.normalize();

	// 移動処理
	_move->DiagonalMove(N);

	if (distance <= 0.1f)
	{
		m_pos = float3::ToXMFLOAT3(m_TargetCheckpoint->pos);
		m_TargetCheckpoint = m_TargetCheckpoint->nextPoint;
	}
}

// 逆方向移動ギミック
void CheckPointPath::ReverseMoveGimmick()
{
	// データ型を変換(計算しやすいように)
	float3 pos = float3::Tofloat3(m_pos);

	// 一個前のチェックポイント - 現在の座標
	float3 N = m_TargetCheckpoint->prePoint->pos - pos;

	// チェックポイントまでの距離を計算
	float distance = float3::distance(m_TargetCheckpoint->prePoint->pos, pos);

	// 方向を正規化
	N = N.normalize();

	// 移動処理
	_move->DiagonalMove(N);

	if (distance <= 0.1f)
	{
		m_pos = float3::ToXMFLOAT3(m_TargetCheckpoint->prePoint->pos);
		m_TargetCheckpoint = m_TargetCheckpoint->prePoint;
	}
}
