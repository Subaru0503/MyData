// インクルード部
#include "Move2DAnimation.h"

// コンストラクタ
Move2DAnimation::Move2DAnimation()
{
	// メンバ変数初期化
	m_Kind = MoveKind::None;
	m_MaxPos = DirectX::XMFLOAT2(0.0f, 0.0f);
	m_MinPos = DirectX::XMFLOAT2(0.0f, 0.0f);
	m_MoveSpeed = DirectX::XMFLOAT2(0.0f, 0.0f);
	m_Dir = DirectX::XMFLOAT2(1.0f, 1.0f);
}

// デストラクタ
Move2DAnimation::~Move2DAnimation()
{
}

// 更新処理
void Move2DAnimation::Execute()
{
	// 種類によって処理を変える
	switch (m_Kind)
	{
	case MoveKind::Up_Down:
		UpDownMove();		// 上下移動
		break;
	case MoveKind::Left_Right:
		LeftRightMove();	// 左右移動
		break;
	}
}

// 上下移動アニメーション
void Move2DAnimation::UpDownMove()
{
	// 現在の座標取得
	DirectX::XMFLOAT3 pos = transform->GetPos();

	// 方向設定
	if (m_MinPos.y >= pos.y)
	{
		m_Dir.y = 1;
	}
	else if(m_MaxPos.y <= pos.y)
	{
		m_Dir.y = -1;
	}

	// 座標設定
	pos.y += m_MoveSpeed.y * m_Dir.y;

	transform->SetPos(pos);
}

// 左右移動アニメーション
void Move2DAnimation::LeftRightMove()
{
	// 現在の座標取得
	DirectX::XMFLOAT3 pos = transform->GetPos();

	// 方向設定
	if (m_MinPos.x >= pos.x)
	{
		m_Dir.x = 1;
	}
	else if (m_MaxPos.x <= pos.x)
	{
		m_Dir.x = -1;
	}

	// 座標設定
	pos.x += m_MoveSpeed.x * m_Dir.x;

	transform->SetPos(pos);
}

// アニメーション種類設定
void Move2DAnimation::SetMoveKind(MoveKind kind)
{
	m_Kind = kind;	// 種類設定
}

// 移動スピード
void Move2DAnimation::SetSpeed(DirectX::XMFLOAT2 speed)
{
	m_MoveSpeed = speed;	// 速さ設定
}

// 移動範囲
void Move2DAnimation::SetMoveArea(DirectX::XMFLOAT2 min, DirectX::XMFLOAT2 max)
{
	m_MinPos = min;	// 最小座標設定
	m_MaxPos = max;	// 最大座標設定
}

// 方向設定
void Move2DAnimation::SetDir(DirectX::XMFLOAT2 dir)
{
	m_Dir = dir;	// 方向設定
}

// スピードを返す
DirectX::XMFLOAT2 Move2DAnimation::GetSpeed()
{
	return m_MoveSpeed;
}

// 移動範囲の最大座標
DirectX::XMFLOAT2 Move2DAnimation::GetMaxPos()
{
	return m_MaxPos;
}

// 移動範囲の最小座標
DirectX::XMFLOAT2 Move2DAnimation::GetMinPos()
{
	return m_MinPos;
}
