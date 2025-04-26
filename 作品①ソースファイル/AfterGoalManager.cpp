// インクルード部
#include "AfterGoalManager.h"
#include "SceneRoot.h"
#include "Input.h"

// マネージャー
#include "SoundManager.h"	// サウンドマネージャー

// 更新処理
void AfterGoalManager::Update()
{
	if (!m_pClear) return;

	float3 goalPos = float3::Tofloat3(m_pGoal->GetPos());
	float3 playerPos = float3::Tofloat3(m_pPlayer->GetPos());

	// プレイヤーの高さに合わせる
	goalPos.y = playerPos.y;

	// ゴール中央までの距離を計算
	float distance = float3::distance(goalPos, playerPos);

	if (distance > 0.1f)
	{
		m_pPlayer->MoveAfterGoal(m_pGoal);	// 中央まで移動させる
		// カメラとスカイドーム更新処理
		for (auto itA = m_pObjList.begin(); itA != m_pObjList.end(); ++itA)
		{
			GameObject* obj = *itA;
			obj->Execute();			// 更新処理
		}
		return;
	}
	// BGMを再生してなかったら再生
	else if (!m_PlayBGM)
	{
		// 全て破棄
		SoundManager::GetInstance().AllDeleteSpeaker();
		// クリアBGM再生
		SoundManager::GetInstance().playSound(SoundManager::BGM::Clear);
		m_PlayBGM = true;
	}

	// カメラとスカイドーム更新処理
	for (auto itA = m_pObjList.begin(); itA != m_pObjList.end(); ++itA)
	{
		GameObject* obj = *itA;
		obj->Execute();			// 更新処理
	}

	// 透明度がなくなって描画出来てるか確認
	bool draw = m_pClear->GetDraw();
	if (!draw)
	{
		m_pClear->Update();	// 更新処理
		AlphaUpdate();		// 時間UIも一緒にに変化
		return;
	}

	// 次のステージへ
	if (IsKeyTrigger(VK_RETURN))
	{
		// 現在のシーン取得
		SceneBase::Scene scene = SceneRoot::GetCurrentScene();

		// 1加算して次のシーンへ
		// 次のシーンがなかったらタイトルシーンに戻る
		scene = static_cast<SceneBase::Scene>((scene + 1) % SceneBase::Scene::MAX + (scene + 1) / SceneBase::Scene::MAX);

		// 次のステージに行く
		SceneRoot::SetNextScene(scene);
		// 決定SE
		SoundManager::GetInstance().playSound(SoundManager::SystemSE::Decision);
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
	else if (IsKeyTrigger(VK_ESCAPE))
	{
		// タイトルに戻る
		SceneRoot::SetNextScene(SceneBase::Scene::TITLE);
		// 決定SE
		SoundManager::GetInstance().playSound(SoundManager::SystemSE::Decision);
	}
}

// アルファ値変化
void AfterGoalManager::AlphaUpdate()
{
	for (int i = 0; i < m_TimeObj.size(); i++)
	{
		m_TimeObj[i]->AlphaUpdate();
	}
}