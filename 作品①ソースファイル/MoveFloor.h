// 床移動ギミッククラス

// インクルードガード
#ifndef __MOVE_FLOOR_H__
#define __MOVE_FLOOR_H__

// インクルード部
#include "GimmickBase.h"

// コンポーネント
#include "Move.h"	// 移動

// クラス定義
class MoveFloor : public GimmickBase
{
public:
	enum class MoveType
	{
		UpDown,		// 上下移動
		LeftRight,	// 左右移動
		FrontBack,	// 前後移動
	};
public:
	MoveFloor(std::string name = "MoveFloor");	// コンストラクタ
	~MoveFloor();									// デストラクタ

	// 初期状態に戻す
	void ResetState();

	// ターゲットオブジェクトの処理
	void Gimmick(int index, float rotY);
	// 通常のネジを回す方向と逆方向に回されたときに呼ぶ
	void InvertGimmick(int index, float rotY);

	// 移動量セット
	inline void SetMove(float move)
	{
		m_Move = move;
	}

	// 移動タイプセット
	inline void SetType(MoveType type)
	{
		m_moveType = type;
	}
private:
	void MoveGimmick();			// 移動ギミック
	void ReverseMoveGimmick();	// 逆方向移動ギミック

private:
	// コンポーネント
	Move* _move;			// 移動コンポーネント

	MoveType m_moveType;	// 移動タイプ

	float m_Move;			// 移動量
};

#endif // __MOVE_FLOOR_H__