// インクルード部
#include "Jump.h"

// コンストラクタ
Jump::Jump()
	: m_JumpForce(0.0f)
	, m_CurrentTime(0.0f)
{

}

// 更新処理
void Jump::Execute()
{
	// ジャンプをしてなかったら処理をしない
	if (m_JumpForce <= 0.0f) return;

	DirectX::XMFLOAT3 newPos = transform->GetPos();	// 座標取得

	newPos.y += m_JumpForce * (1.0f - m_CurrentTime);		// ジャンプ

	transform->SetPos(newPos);						// 座標セット

	m_CurrentTime += 1.0f / 60.0f;	// 時間経過

	// 1秒を超えたら値をリセット
	if (m_CurrentTime >= 1.0f)
	{
		m_JumpForce = 0.0f;		// ジャンプ力リセット
		m_CurrentTime = 0.0f;	// 経過時間リセット
	}
}
