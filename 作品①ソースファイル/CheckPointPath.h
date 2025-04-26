///////////////////////////////////////
//
// チェックポイントを順に移動するギミッククラス
//
// 登録したチェックポイントを辿っていく
//
///////////////////////////////////////

// インクルードガード
#ifndef __CHECK_POINT_PATH_H__
#define __CHECK_POINT_PATH_H__

// インクルード部
#include "GimmickBase.h"
#include <vector>
#include "float3.h"

// コンポーネント
#include "Move.h"	// 移動

// クラス定義
class CheckPointPath : public GimmickBase
{
public:

	// チェックポイントに必要な情報をまとめたもの
	struct MovePath
	{
		// チェックポイント座標
		float3 pos;

		// 次のチェックポイント
		MovePath* nextPoint;

		// 一個前のチェックポイント
		MovePath* prePoint;
	};

public:

	// コンストラクタ
	CheckPointPath(std::string name = "CheckPointPath");

	// デストラクタ
	~CheckPointPath();

	// 初期状態に戻す
	void ResetState();

	// ターゲットオブジェクトの処理
	void Gimmick(int index, float rotY);

	// 通常のネジを回す方向と逆方向に回されたときに呼ぶ
	void InvertGimmick(int index, float rotY);

	// ターゲットのチェックポイントを消す
	inline void AllDeleteCheckPoint()
	{
		m_TargetCheckpoint = nullptr;
	}

	// セット関数
	// 移動量セット
	inline void SetMove(float move)
	{
		m_Move = move;
	}

	// チェックポイントの座標を設定する
	inline void SetCheckPointPos(float3 pos)
	{
		MovePath movePath;

		// 座標設定
		movePath.pos = pos;

		// チェックポイントとして登録
		m_CheckPoint.push_back(movePath);
	}

	// チェックポイントに必要な情報を設定する
	inline void SetCheckPointInfo()
	{
		// 目指すチェックポイント設定
		m_TargetCheckpoint = &m_CheckPoint[0];

		// int型にデータ型変換
		int index = (int)m_CheckPoint.size();

		for (int i = 0; i < index; i++)
		{
			// 次のチェックポイントのポインタを設定する
			m_CheckPoint[i].nextPoint = &m_CheckPoint[(i + 1) % index];

			// 一個前のチェックポイントのポインタを設定する
			m_CheckPoint[i].prePoint = &m_CheckPoint[(i + index - 1) % index];
		}
	}

private:

	// 移動ギミック
	void MoveGimmick();

	// 逆方向移動ギミック
	void ReverseMoveGimmick();

private:
	//----コンポーネント----

	// 移動コンポーネント
	Move* _move;

	// 辿るチェックポイントの数
	std::vector<MovePath>  m_CheckPoint;

	// 今目指しているチェックポイント
	MovePath* m_TargetCheckpoint;

	// 移動量
	float m_Move;
};

#endif // __CHECK_POINT_PATH_H__