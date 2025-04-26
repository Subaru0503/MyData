// ゴールクラス

// インクルード部
#include "Goal.h"

#include "Player.h"

// コンストラクタ
Goal::Goal(std::string name)
	: GameObject(name)
	, m_GoalFlg(false)
{
	m_tag = "Goal";

	// コンポーネント追加
	AddComponent<BoxCollider>();			// 当たり判定追加。
	//AddComponent<Scanner>();				// スキャナ
	AddComponent<ModelRenderer3D>();		// 3D描画

	// コンポーネント取得
	_boxCollider = GetComponent<BoxCollider>();
	//_scanner = GetComponent<Scanner>();
	_modelRenderer3D = GetComponent<ModelRenderer3D>();

	// シェーダーセット
	const char* file[] = {
		"VS_Object",
		"PS_TexColor",
	};

	_modelRenderer3D->SetShader(file);
}

// デストラクタ
Goal::~Goal()
{
}

// 更新処理
void Goal::Update()
{

}

// ゴール判定チェック
void Goal::OnCollision(GameObject* obj)
{
	if (obj && obj->GetTag() == "Player")
	{
		m_GoalFlg = true;	// ゴールフラグを上げる
	}
	// 実体なし
	else if (!obj)
	{
		m_pCollisionObj = nullptr;
	}
}