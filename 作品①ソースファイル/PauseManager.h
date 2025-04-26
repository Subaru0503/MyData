// ポーズ画面管理クラス

// インクルードガード
#ifndef __PAUSE_MENU_MANAGER_H__
#define __PAUSE_MENU_MANAGER_H__

// インクルード部
#include "GameObject.hpp"
#include <map>
// コンポーネント
#include "ModelRenderer2D.h"

// クラス定義
class PauseManager
{
private:
	using UIList = std::map<int, std::vector<GameObject*>>;
	using UIPosScaleList = std::map<int, std::vector<DirectX::XMFLOAT3>>;
public:
	inline static PauseManager& GetInstance()
	{
		static PauseManager instance;
		return instance;
	}

	// 初期化
	void Init();

	// 更新処理
	void Update();

	// オブジェクト削除
	inline void RemoveALLObj()
	{
		// 全て削除
		for (auto it = m_PauseUILists.begin(); it != m_PauseUILists.end();)
		{
			it = m_PauseUILists.erase(it);
		}
		for (auto it = m_pNormalUI.begin(); it != m_pNormalUI.end();)
		{
			it = m_pNormalUI.erase(it);
		}
		for (auto it = m_UIPosScale.begin(); it != m_UIPosScale.end();)
		{
			it = m_UIPosScale.erase(it);
		}
	}

	inline void PauseOpen()
	{
		m_PauseOpenFlg = true;
	}

	// リセット関数
	inline void Reset()
	{
		m_PauseOpenFlg = false;
		m_Page = 1;
	}

	// セット関数
	inline void SetPauseUI(int page, GameObject* obj)
	{
		m_PauseUILists[page].push_back(obj);
		obj->GetComponent<ModelRenderer2D>()->SetDraw(false);
	}
	inline void SetNormalUI(GameObject* obj)
	{
		m_pNormalUI.push_back(obj);
		obj->GetComponent<ModelRenderer2D>()->SetDraw(false);
	}
	inline void SetPosScale(int no, DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 scale)
	{
		m_UIPosScale[no].push_back(pos);
		m_UIPosScale[no].push_back(scale);
	}

	// ゲット関数
	inline bool GetPause()
	{
		return m_PauseOpenFlg;
	}

private:

	PauseManager()
	{
		m_Page = 1;
		m_PauseOpenFlg = false;
	};
	~PauseManager()
	{
	};

	// 名前を確認して座標、サイズを補正
	bool NameCheck(std::vector<GameObject*>& itA, UIPosScaleList::iterator itB);
	bool NameCheck(std::vector<GameObject*>::iterator itA, UIPosScaleList::iterator itB);


	// UI更新処理
	void UIUpdate(UIList::iterator& pair);

	// 描画ON
	void DrawFlgON(UIList::iterator& pair);
	// 描画OFF
	void DrawFlgOFF(UIList::iterator& pair);
	void DrawFlgOFF(std::vector<GameObject*>::iterator& pair);
private:
	UIList m_PauseUILists;					// 描画するUIリスト
	std::vector<GameObject*> m_pNormalUI;	// ページに関係なく表示するUI
	UIPosScaleList m_UIPosScale;			// 描画するUIの座標とサイズ

	int m_Page;				// 現在開いてるページ
	bool m_PauseOpenFlg;	// ポーズ画面を開いているフラグ
};

#endif // __PAUSE_MENU_MANAGER_H__