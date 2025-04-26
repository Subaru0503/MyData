// ジャンプクラス

// インクルードガード
#ifndef __JUMP_H__
#define __JUMP_H__

// インクルード部
#include "Component.h"

// クラス定義
class Jump : public Component
{
private:
#define JUMP_POWER 0.35f	// ジャンプパワー

public:
	Jump();				// コンストラクタ

	void Execute();		// 更新

	// セット関数
	inline void SetJump()
	{
		m_JumpForce = JUMP_POWER;
		//m_JumpForce += 0.15f;
		//if (m_JumpForce >= JUMP_POWER)
		//{
		//	m_JumpForce = JUMP_POWER;
		//	return;
		//}
	}

	// ゲット関数
	inline bool GetJump()
	{
		return m_JumpForce <= 0.0f;
	}

private:
	float m_JumpForce;		// ジャンプ力
	float m_CurrentTime;	// 経過時間
};

#endif // __JUMP_H__