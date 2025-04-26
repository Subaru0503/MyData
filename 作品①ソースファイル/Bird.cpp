//////////////////////////////
//
// 鳥
//
//////////////////////////////

// インクルード部
#include "Bird.h"

// コンストラクタ
Bird::Bird(std::string name)
	: GameObject(name)
{
	// コンポーネント追加
	AddComponent<ModelRenderer2D>();

	// コンポーネント取得
	_modelRenderer2D = GetComponent<ModelRenderer2D>();

	// テクスチャ読み込み
	//_modelRenderer2D->Load("Assets/Texture/Bird.png");

	// メンバ変数初期化
	m_Time = 0.0f;
	m_Velocity = 0.0f;
	m_Acceleration = 0.0f;

}

// デストラクタ
Bird::~Bird()
{
}

// 更新処理
void Bird::Update()
{
	fly();

	m_Time += 1.0f / 60.0f;
}

// 飛行
void Bird::fly()
{
	m_pos.x += m_Velocity + (m_Acceleration *(m_Time * m_Time)) / 2.0f;				// 座標変化
	m_pos.y -= (m_Velocity / 16) + (m_Acceleration *(m_Time * m_Time)) / 2.0f;		// 座標変化

	if (m_pos.x >= 1500.0f)
	{
		m_pos.x = -300.0f;
		m_pos.y = 600.0f;
		m_Time = 0.0f;
	}
}

// 速度設定
void Bird::SetVelocity(float velocity)
{
	m_Velocity = velocity;
}

// 加速度設定
void Bird::SetAcceleration(float acceleration)
{
	m_Acceleration = acceleration;
}
