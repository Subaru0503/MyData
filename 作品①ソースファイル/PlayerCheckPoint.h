///////////////////////////////////////
//
// プレイヤーチェックポイントクラス
//
// この位置に来たらリセット時にプレイヤーをここに移動させる
//
///////////////////////////////////////

//----インクルードガード----
#ifndef __PLAYER_CHECKPOINT_H__
#define __PLAYER_CHECKPOINT_H__

//----インクルード部----
#include "GameObject.hpp"

// クラス定義
class PlayerCheckPoint : public GameObject
{
public:

	// コンストラクタ
	PlayerCheckPoint(std::string name = "PlayerCheckPoint");

	// デストラクタ
	~PlayerCheckPoint();

private:

};

#endif // __PLAYER_CHECKPOINT_H__