#ifndef __PLAYER_TEXT_MANAGER_H__
#define __PLAYER_TEXT_MANAGER_H__

// ========== インクルード部 ==========
#include "PlayerText.h"

// ========== クラス ==========
class CPlayerTextManager
{
public:
	CPlayerTextManager();
	~CPlayerTextManager();
	void Update();
	void Draw();

private:
};

#endif // !__PLAYER_TEXT_MANAGER_H__

// プレイヤーイラスト出現アニメーション
// 画面右端、下からぴょこって感じで出てくる。→出てくると同時に吹き出し表示も開始する(もしくはちょい遅れぐらい)