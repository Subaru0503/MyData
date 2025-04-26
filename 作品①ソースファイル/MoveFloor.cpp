// 床移動ギミッククラス

// インクルード部
#include "MoveFloor.h"

// システム
#include "Input.h"

// 定数・マクロ定義
#define DIVISOR (23.5f) // 除数

// コンストラクタ
MoveFloor::MoveFloor(std::string name)
	: GimmickBase(name)
{
	m_tag = "MoveGimmick";
	// コンポーネント追加
	AddComponent<Move>();			// 移動

	// コンポーネント取得
	_move = GetComponent<Move>();

	// メンバ変数初期化
	m_Move = 1.0f;
}

// デストラクタ
MoveFloor::~MoveFloor()
{
}

// 初期状態に戻す
// オブジェクトをシーンが始まったときの状態に戻す
void MoveFloor::ResetState()
{
	// 初期座標に戻す
	m_pos = m_InitPos;
}

// ターゲットオブジェクトの処理
void MoveFloor::Gimmick(int index, float rotY)
{
	// 移動量計算
	float move = rotY / DIVISOR;

	// 移動量セット
	_move->SetMove(move * m_Move);

	// 移動ギミック
	MoveGimmick();
}

// 通常のネジを回す方向と逆方向に回されたときに呼ぶ
void MoveFloor::InvertGimmick(int index, float rotY)
{
	// 移動量計算
	float move = rotY / DIVISOR;

	// 移動量セット
	_move->SetMove(move * m_Move);

	// 逆方向に移動ギミック
	ReverseMoveGimmick();
}

// 移動ギミック
void MoveFloor::MoveGimmick()
{
	// 移動種類によって処理を変える
	switch (m_moveType)
	{
	case MoveType::UpDown:

		// 上に移動
		_move->UPMove();

		break;
	case MoveType::LeftRight:

		// 右に移動
		_move->RightMove();

		break;
	case MoveType::FrontBack:

		// 前に移動
		_move->FrontMove();

		break;
	}
}

// 逆方向移動ギミック
void MoveFloor::ReverseMoveGimmick()
{
	// 移動種類によって処理を変える
	switch (m_moveType)
	{
	case MoveType::UpDown:

		// 下に移動
		_move->UPMove(false);

		break;

	case MoveType::LeftRight:

		// 左に移動
		_move->RightMove(false);

		break;
	case MoveType::FrontBack:

		// 後ろに移動
		_move->FrontMove(false);

		break;
	}
}
