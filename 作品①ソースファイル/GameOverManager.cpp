// インクルード部
#include "GameOverManager.h"

// マネージャー
#include "TimeManager.h"	// タイムマネージャー
#include "SoundManager.h"	// サウンドマネージャー

// 更新処理
void GameOverManager::Update()
{
	// プレイヤーがNULLもしくは
	// ゲームオーバーになってたら処理しない
	if (!m_pPlayer || m_GameOverFlg) return;

	// 落下死チェック
	FallDeadCheck();

	// タイムオーバーチェック
	TimeOverCheck();
}

// 落下死チェック
void GameOverManager::FallDeadCheck()
{
	DirectX::XMFLOAT3 pos = m_pPlayer->GetPos();

	if (pos.y <= -10.0f)
	{
		m_GameOverFlg = true;
	}
}

// タイムオーバーチェック
void GameOverManager::TimeOverCheck()
{
	// 時間取得
	float time = TimeManager::GetInstance().GetTime();

	if (time <= 0.0f)
	{
		m_GameOverFlg = true;
		SoundManager::GetInstance().playSound(SoundManager::SystemSE::TimeOver);
	}
}
