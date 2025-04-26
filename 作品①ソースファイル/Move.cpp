// インクルード部
#include "Move.h"

// 高さ移動
void Move::UPMove(bool UP)
{
	float dir;
	if (UP)
	{
		dir = 1;
	}
	else
	{
		dir = -1;
	}

	DirectX::XMFLOAT3 pos = transform->GetPos();

	pos.y += m_Move * dir;

	transform->SetPos(pos);
}

// 左右移動
void Move::RightMove(bool Right)
{
	float dir;
	if (Right)
	{
		dir = 1;
	}
	else
	{
		dir = -1;
	}
	DirectX::XMFLOAT3 pos = transform->GetPos();

	pos.x += m_Move * dir;

	transform->SetPos(pos);
}

// 前後移動
void Move::FrontMove(bool Front)
{
	float dir;
	if (Front)
	{
		dir = 1;
	}
	else
	{
		dir = -1;
	}
	DirectX::XMFLOAT3 pos = transform->GetPos();

	pos.z += m_Move * dir;

	transform->SetPos(pos);
}

// 斜め移動
void Move::DiagonalMove(float3 dir)
{
	// 進行方向に移動量を掛ける
	float3 move = dir * m_Move;

	// データ型を変換する
	DirectX::XMFLOAT3 newPos = float3::ToXMFLOAT3(move);

	// 現在の座標の取得
	DirectX::XMFLOAT3 pos = transform->GetPos();

	// 現在の座標に足す
	pos.x += newPos.x;
	pos.y += newPos.y;
	pos.z += newPos.z;

	// 新しい座標をセット
	transform->SetPos(pos);
}
