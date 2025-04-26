// インクルード部
#include "AfterGameOverManager.h"
#include "SceneRoot.h"
#include "Input.h"

// マネージャー
#include "SoundManager.h"	// サウンドマネージャー

// 更新処理
void AfterGameOverManager::Update()
{
	if (!m_pObj) return;

	// 透明度がなくなって描画出来てるか確認
	bool draw = m_pObj->GetDraw();
	if (!draw)
	{
		m_pObj->Update();	// 更新処理
		// スカイドーム更新処理
		m_pSkyDome->Update();	// ずれないように更新処理
		return;
	}

	// リトライ
	if (IsKeyTrigger('R'))
	{
		// 同じステージをもう一回やる
		SceneRoot::SetNextScene(SceneRoot::GetCurrentScene());
		// リトライSE
		SoundManager::GetInstance().playSound(SoundManager::SystemSE::Decision);
	}
	// タイトルに戻る
	else if (IsKeyTrigger(VK_ESCAPE))
	{
		// タイトルに戻る
		SceneRoot::SetNextScene(SceneBase::Scene::TITLE);
		// タイトル戻るSE
		SoundManager::GetInstance().playSound(SoundManager::SystemSE::Decision);
	}

	// スカイドーム更新処理
	m_pSkyDome->Update();	// ずれないように更新処理
}