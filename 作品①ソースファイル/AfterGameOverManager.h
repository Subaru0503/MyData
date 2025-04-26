// ゲームオーバー後管理クラス

// インクルードガード
#ifndef __AFTER_GAME_OVER_MANAGER_H__
#define __AFTER_GAME_OVER_MANAGER_H__

// インクルード部
#include "GameObject.hpp"
#include "SkyDome.h"
#include "GameOver.h"

// クラス定義
class AfterGameOverManager
{
public:
	inline static AfterGameOverManager& GetInstance()
	{
		static AfterGameOverManager instance;
		return instance;
	}

	// 更新処理
	void Update();

	// リセット関数
	inline void Reset()
	{
		m_pObj = nullptr;
		m_pSkyDome = nullptr;
	}

	// セット関数
	inline void SetObj(GameOver* obj, SkyDome* skydome)
	{
		m_pObj = obj;
		m_pSkyDome = skydome;
	}

	// ゲット関数
	inline bool GetObj()
	{
		return m_pObj == nullptr;
	}

private:

	AfterGameOverManager()
	{
	};
	~AfterGameOverManager()
	{
	};

private:
	SkyDome* m_pSkyDome;	// スカイドーム
	GameOver* m_pObj;		// ゲームオーバーUI

};

#endif // __AFTER_GAME_OVER_MANAGER_H__