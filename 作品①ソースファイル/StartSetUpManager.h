// ゲームスタート準備管理クラス

// インクルードガード
#ifndef __START_SETUP_MANAGER_H__
#define __START_SETUP_MANAGER_H__

// インクルード部
#include "GameObject.hpp"
#include "Ready.h"

// コンポーネント
#include "ModelRenderer2D.h"

// クラス定義
class StartSetUpManager
{
public:
	inline static StartSetUpManager& GetInstance()
	{
		static StartSetUpManager instance;
		return instance;
	}

	// 更新処理
	void Update();

	// リセット関数
	inline void Reset()
	{
		m_StartSetUpFlg = false;
	}

	// セット関数
	inline void SetStartSetUpUI(Ready* obj)
	{
		m_UI = obj;
		obj->GetComponent<ModelRenderer2D>()->SetDraw(false);
	}

	// ゲット関数
	inline bool GetStartSetUp()
	{
		return m_StartSetUpFlg;
	}

private:

	StartSetUpManager()
	{
		m_StartSetUpFlg = false;
	};
	~StartSetUpManager()
	{
	};

private:
	Ready* m_UI;

	bool m_StartSetUpFlg;	// スタート準備がされたフラグ
};

#endif // __START_SETUP_MANAGER_H__