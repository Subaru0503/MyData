///////////////////////////////////////
//
// オブジェクトリセット管理クラス
//
// オブジェクトの配置を初期位置に戻す
//
///////////////////////////////////////

// インクルード部
#include "ResetManager.h"
#include "SceneRoot.h"
#include "Input.h"

// マネージャー
#include "SoundManager.h"	// サウンドマネージャー

// 更新処理
void ResetManager::Update()
{
	// リセット前準備
	if (IsKeyTrigger('R') && !m_ResetFlg &&
		!m_pFade->GetPlay())
	{
		// フェードアウト
		m_pFade->Start(FADE_OUT, FADE_OUT_TIME, Fade::FadeColor::White);

		// リセットフラグを上げる
		m_ResetFlg = true;

		// 決定SE
		SoundManager::GetInstance().playSound(SoundManager::SystemSE::Decision);
	}

	// リセットフラグが上がってたら
	if (m_ResetFlg && !m_pFade->GetPlay())
	{
		// オブジェクトを初期状態に戻す
		ResetState();
	}
}

// オブジェクトを初期状態に戻す
void ResetManager::ResetState()
{
	// 登録している分ループして戻す
	for (auto it = m_Obj.begin(); it != m_Obj.end(); it++)
	{
		// データ型を変換
		GameObject* obj = *(it);

		// 初期状態に戻す
		obj->ResetState();
	}

	// フェードイン
	m_pFade->Start(FADE_IN, FADE_IN_TIME, Fade::FadeColor::White);

	// リセットフラグを下げる
	m_ResetFlg = false;
}

// フェードセット
void ResetManager::SetFade(Fade * fade)
{
	m_pFade = fade;
}

// リセットフラグを返す
bool ResetManager::GetResetFlg()
{
	return m_ResetFlg;
}
