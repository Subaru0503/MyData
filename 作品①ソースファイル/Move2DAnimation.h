// 移動アニメーション機能クラス

// インクルードガード
#ifndef __MOVE_ANIMATION_H__
#define __MOVE_ANIMATION_H__

// インクルード部
#include "Component.h"

// クラス定義
class Move2DAnimation : public Component
{
public:
	enum MoveKind
	{
		None,		// なし
		Up_Down,	// 上下
		Left_Right,	// 左右
	};
public:
	Move2DAnimation();	// コンストラクタ
	~Move2DAnimation();	// デストラクタ

	void Execute();		// 更新処理

	void UpDownMove();		// 上下移動アニメーション
	void LeftRightMove();	// 左右移動アニメーション

	// セット関数
	// アニメーション種類設定
	void SetMoveKind(MoveKind kind);

	// 移動スピード
	void SetSpeed(DirectX::XMFLOAT2 speed);

	// 移動範囲
	void SetMoveArea(DirectX::XMFLOAT2 min, DirectX::XMFLOAT2 max);

	// 方向設定
	void SetDir(DirectX::XMFLOAT2 dir);

	// アニメーションを止める
	//void Stop();

	//----ゲット関数----
	// スピードを返す
	DirectX::XMFLOAT2 GetSpeed();

	// 移動範囲の最大座標
	DirectX::XMFLOAT2 GetMaxPos();

	// 移動範囲の最小座標
	DirectX::XMFLOAT2 GetMinPos();

private:
	MoveKind m_Kind;				// 移動種類

	DirectX::XMFLOAT2 m_MaxPos;		// 移動範囲の最大座標
	DirectX::XMFLOAT2 m_MinPos;		// 移動範囲の最小座標
	DirectX::XMFLOAT2 m_MoveSpeed;	// 移動スピード
	DirectX::XMFLOAT2 m_Dir;		// 移動方向

	//bool m_Stop;					// アニメーションを止める
};

#endif // __MOVE_ANIMATION_H__