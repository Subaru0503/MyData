// 移動機能クラス

// インクルードガード
#ifndef __MOVE_H__
#define __MOVE_H__

// インクルード部
#include "Component.h"

// システム
#include "float3.h"

// クラス定義
class Move : public Component
{
public:

	void UPMove(bool UP = true);		// 高さ移動
	void RightMove(bool Right = true);	// 左右移動
	void FrontMove(bool Front = true);	// 前後移動
	void DiagonalMove(float3 dir);		// 斜め移動

	// セット関数
	inline void SetMove(float move)
	{
		m_Move = move;
	}

	// ゲット関数
	inline float GetMove()
	{
		return m_Move;
	}

private:
	float m_Move;		// 移動量
};

#endif // __MOVE_H__