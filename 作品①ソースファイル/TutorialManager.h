// チュートリアル管理クラス

// インクルードガード
#ifndef __TUTORIAL_MANAGER_H__
#define __TUTORIAL_MANAGER_H__

// インクルード部
#include "GameObject.hpp"
#include <map>
// コンポーネント
#include "ModelRenderer2D.h"

// クラス定義
class TutorialManager
{
private:
	using UIList = std::map<int, std::vector<GameObject*>>;
public:
	inline static TutorialManager& GetInstance()
	{
		static TutorialManager instance;
		return instance;
	}

	// 更新処理
	void Update();

	// オブジェクト削除
	inline void RemoveALLObj()
	{
		// 全て削除
		for (auto it = m_UILists.begin(); it != m_UILists.end();)
		{
			it = m_UILists.erase(it);
		}
		for (auto it = m_pNormalUI.begin(); it != m_pNormalUI.end();)
		{
			it = m_pNormalUI.erase(it);
		}
	}

	// リセット関数
	inline void Reset()
	{
		m_TutorialFlg = true;
		m_Page = 1;
	}

	// セット関数
	inline void SetTutorialUI(int page, GameObject* obj)
	{
		m_UILists[page].push_back(obj);
		obj->GetComponent<ModelRenderer2D>()->SetDraw(false);
	}
	inline void SetNormalUI(GameObject* obj)
	{
		m_pNormalUI.push_back(obj);
		obj->GetComponent<ModelRenderer2D>()->SetDraw(false);
	}

	// ゲット関数
	inline bool GetTutorial()
	{
		return m_TutorialFlg;
	}

private:

	TutorialManager()
	{
		m_Page = 1;
		m_TutorialFlg = false;
	};
	~TutorialManager()
	{
	};

	// UI更新処理
	void UIUpdate(UIList::iterator& pair);

	// 描画ON
	void DrawFlgON(UIList::iterator& pair);
	// 描画OFF
	void DrawFlgOFF(UIList::iterator& pair);
	void DrawFlgOFF(std::vector<GameObject*>::iterator& pair);
private:
	UIList m_UILists;	// 描画するUIリスト
	std::vector<GameObject*> m_pNormalUI;	// ページに関係なく表示するUI

	int m_Page;			// 現在開いてるページ
	bool m_TutorialFlg;	// チュートリアルを行うフラグ
};

#endif // __TUTORIAL_MANAGER_H__