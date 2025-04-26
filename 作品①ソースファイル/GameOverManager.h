// ゲームオーバー判定管理クラス

// インクルードガード
#ifndef __GAME_OVER_MANAGER_H__
#define __GAME_OVER_MANAGER_H__

// インクルード部
#include "GameObject.hpp"

// クラス定義
class GameOverManager
{
public:
	inline static GameOverManager& GetInstance()
	{
		static GameOverManager instance;
		return instance;
	}

	// 更新処理
	void Update();

	// 落下死チェック
	void FallDeadCheck();
	// タイムオーバーチェック
	void TimeOverCheck();

	// リセット関数
	inline void Reset()
	{
		m_GameOverFlg = false;
	}

	// セット関数
	inline void SetPlyer(GameObject* obj)
	{
		m_pPlayer = obj;
	}

	// ゲット関数
	inline bool GetGameOverFlg()
	{
		return m_GameOverFlg;
	}

private:

	GameOverManager()
	{
		m_GameOverFlg = false;
	};
	~GameOverManager()
	{
	};

private:
	GameObject* m_pPlayer;	// プレイヤーオブジェクト

	bool m_GameOverFlg;	// ゲームオーバーフラグ
};

#endif // __GAME_OVER_MANAGER_H__