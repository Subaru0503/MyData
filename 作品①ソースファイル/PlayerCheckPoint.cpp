///////////////////////////////////////
//
// プレイヤーチェックポイントクラス
//
// この位置に来たらリセット時にプレイヤーをここに移動させる
//
///////////////////////////////////////

//----インクルード部----
#include "PlayerCheckPoint.h"

#include "Player.h"

// コンストラクタ
PlayerCheckPoint::PlayerCheckPoint(std::string name)
	: GameObject(name)
{
	m_tag = "PlayerCheckPoint";
}

// デストラクタ
PlayerCheckPoint::~PlayerCheckPoint()
{
}
