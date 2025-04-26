// インクルード部
#include "PauseManager.h"
#include "SceneRoot.h"
#include "Input.h"

// コンポーネント
#include "ModelRenderer2D.h"

// マネージャー
#include "SoundManager.h"	// サウンドマネージャー

// 初期化
void PauseManager::Init()
{
	// ページ設定あるUI
	// 同じ名前があったら補正する
	for (UIList::iterator itA = m_PauseUILists.begin(); itA != m_PauseUILists.end(); ++itA)
	{
		for (UIPosScaleList::iterator itB = m_UIPosScale.begin(); itB != m_UIPosScale.end(); ++itB)
		{
			// 一致したら次のUIチェック
			if (NameCheck(itA->second, itB)) continue;
		}
	}

	// 通常UI
	// 同じ名前があったら補正する
	for (std::vector<GameObject*>::iterator it = m_pNormalUI.begin(); it != m_pNormalUI.end(); ++it)
	{
		for (UIPosScaleList::iterator itB = m_UIPosScale.begin(); itB != m_UIPosScale.end(); ++itB)
		{
			// 一致したら次のUIチェック
			if (NameCheck(it, itB)) continue;
		}
	}
}

// 更新処理
void PauseManager::Update()
{
	// チュートリアルUI処理
	for (UIList::iterator it = m_PauseUILists.begin(); it != m_PauseUILists.end(); ++it)
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
	// ゲームに戻る
	else if (IsKeyTrigger(VK_ESCAPE))
	{
		// 全て描画フラグOFF
		m_PauseOpenFlg = false;
		for (UIList::iterator it = m_PauseUILists.begin(); it != m_PauseUILists.end(); ++it)
		{
			DrawFlgOFF(it);
		}
		for (std::vector<GameObject*>::iterator it = m_pNormalUI.begin(); it != m_pNormalUI.end(); ++it)
		{
			DrawFlgOFF(it);
		}
		// ポーズ画面を閉じる
		SoundManager::GetInstance().playSound(SoundManager::SystemSE::PauseClose);
	}
	// リトライ
	else if (IsKeyTrigger('R'))
	{
		// 同じステージをもう一回やる
		SceneRoot::SetNextScene(SceneRoot::GetCurrentScene());
		// 決定SE
		SoundManager::GetInstance().playSound(SoundManager::SystemSE::Decision);
	}
	// タイトルに戻る
	else if (IsKeyTrigger('Z'))
	{
		// タイトルに戻る
		SceneRoot::SetNextScene(SceneBase::Scene::TITLE);
		// 決定SE
		SoundManager::GetInstance().playSound(SoundManager::SystemSE::Decision);
	}
}

// 名前を確認して座標、サイズを補正
bool PauseManager::NameCheck(std::vector<GameObject*>& itA, UIPosScaleList::iterator itB)
{
	// 事前に用意したUI分回す(ページ設定されてるもの)
	for (auto it = itA.begin(); it != itA.end(); ++it)
	{
		// オブジェクト番号が一致するのがあるか
		int uiNo = (*it)->Get2DObjNo();
		if (uiNo == itB->first)
		{
			GameObject* ui = (*it);
			DirectX::XMFLOAT3 pos = (itB->second)[0];	// 座標
			DirectX::XMFLOAT3 scale = (itB->second)[1];	// サイズ

			// 座標、サイズを補正
			ui->SetPos(pos);
			ui->SetScale(scale);

			return true;
		}
	}

	return false;
}

// 名前を確認して座標、サイズを補正
bool PauseManager::NameCheck(std::vector<GameObject*>::iterator itA, UIPosScaleList::iterator itB)
{
	// 事前に用意したUI分回す(ページ設定されてるもの)
	// オブジェクト番号が一致するのがあるか
	int uiNo = (*itA)->Get2DObjNo();
	if (uiNo == itB->first)
	{
		GameObject* ui = (*itA);
		DirectX::XMFLOAT3 pos = (itB->second)[0];	// 座標
		DirectX::XMFLOAT3 scale = (itB->second)[1];	// サイズ

		// 座標、サイズを補正
		ui->SetPos(pos);
		ui->SetScale(scale);

		return true;
	
	}
	return false;
}


// UI更新処理
void PauseManager::UIUpdate(UIList::iterator & pair)
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
void PauseManager::DrawFlgON(UIList::iterator & pair)
{
	ModelRenderer2D* modelRenderer2D;
	for (GameObject* obj : pair->second)
	{
		modelRenderer2D = obj->GetComponent<ModelRenderer2D>();
		modelRenderer2D->SetDraw(true);
	}
}

// 描画OFF
void PauseManager::DrawFlgOFF(UIList::iterator & pair)
{
	ModelRenderer2D* modelRenderer2D;
	for (GameObject* obj : pair->second)
	{
		modelRenderer2D = obj->GetComponent<ModelRenderer2D>();
		modelRenderer2D->SetDraw(false);
	}
}

// 描画OFF
void PauseManager::DrawFlgOFF(std::vector<GameObject*>::iterator & pair)
{
	ModelRenderer2D* modelRenderer2D;
	modelRenderer2D = (*pair)->GetComponent<ModelRenderer2D>();
	modelRenderer2D->SetDraw(false);
}