// インクルード部
#include "StartSetUpManager.h"

// マネージャー
#include "PauseManager.h"	// ポーズ画面マネージャー

// コンポーネント
#include "ModelRenderer2D.h"

// 更新処理
void StartSetUpManager::Update()
{
	ModelRenderer2D* modelRenderer2D = m_UI->GetComponent<ModelRenderer2D>();

	m_UI->Execute();
	if (!m_UI->GetStart() && !modelRenderer2D->GetDraw())
	{
		modelRenderer2D->SetDraw(true);
	}

	// ゲームスタートフラグが立ってたら
	if (m_UI->GetStart())
	{
		// 座標やサイズを設定し直しとく
		PauseManager::GetInstance().Init();			// 初期化処理
		m_StartSetUpFlg = true;
	}
}
