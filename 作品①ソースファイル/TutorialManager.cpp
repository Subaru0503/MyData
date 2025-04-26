// インクルード部
#include "TutorialManager.h"
#include "Input.h"

// コンポーネント
#include "ModelRenderer2D.h"

// マネージャー
#include "SoundManager.h"	// サウンドマネージャー

// 更新処理
void TutorialManager::Update()
{
	// チュートリアルUI処理
	for (UIList::iterator it = m_UILists.begin(); it != m_UILists.end(); ++it)
	{
		if (it->first == m_Page)
		{
			UIUpdate(it);	// UI更新処理
			DrawFlgON(it);	// 描画フラグON
		}
		else
		{
			DrawFlgOFF(it);	// 描画フラグOFF
		}
	}

	// 2ページ目へ
	if (IsKeyTrigger(VK_RIGHT) || IsKeyTrigger('D'))
	{
		m_Page = 2;	// 2ページ目
		// 遷移SE再生
		SoundManager::GetInstance().playSound(SoundManager::SystemSE::Select);
	}
	// 1ページ目へ
	else if (IsKeyTrigger(VK_LEFT) || IsKeyTrigger('A'))
	{
		m_Page = 1;	// 1ページ目
		// 遷移SE再生
		SoundManager::GetInstance().playSound(SoundManager::SystemSE::Select);
	}
	// ゲームスタート
	else if (m_Page == 2 && IsKeyTrigger(VK_RETURN))
	{
		// 全て描画フラグOFF
		m_TutorialFlg = false;
		for (UIList::iterator it = m_UILists.begin(); it != m_UILists.end(); ++it)
		{
			DrawFlgOFF(it);
		}
		for (std::vector<GameObject*>::iterator it = m_pNormalUI.begin(); it != m_pNormalUI.end(); ++it)
		{
			DrawFlgOFF(it);
		}

		// 決定SE再生
		SoundManager::GetInstance().playSound(SoundManager::SystemSE::Decision);
	}
}

// UI更新処理
void TutorialManager::UIUpdate(UIList::iterator & pair)
{
	// 開いているページUI更新処理
	for (GameObject* obj : pair->second)
	{
		obj->Execute();
	}
	// ページ関係なく表示されているUI更新処理
	for (std::vector<GameObject*>::iterator it = m_pNormalUI.begin(); it != m_pNormalUI.end(); ++it)
	{
		(*it)->GetComponent<ModelRenderer2D>()->SetDraw(true);
		(*it)->Execute();
	}
}

// 描画ON
void TutorialManager::DrawFlgON(UIList::iterator & pair)
{
	ModelRenderer2D* modelRenderer2D;
	for (GameObject* obj : pair->second)
	{
		modelRenderer2D = obj->GetComponent<ModelRenderer2D>();
		modelRenderer2D->SetDraw(true);
	}
}

// 描画OFF
void TutorialManager::DrawFlgOFF(UIList::iterator & pair)
{
	ModelRenderer2D* modelRenderer2D;
	for (GameObject* obj : pair->second)
	{
		modelRenderer2D = obj->GetComponent<ModelRenderer2D>();
		modelRenderer2D->SetDraw(false);
	}
}

// 描画OFF
void TutorialManager::DrawFlgOFF(std::vector<GameObject*>::iterator & pair)
{
	ModelRenderer2D* modelRenderer2D;
	modelRenderer2D = (*pair)->GetComponent<ModelRenderer2D>();
	modelRenderer2D->SetDraw(false);
}