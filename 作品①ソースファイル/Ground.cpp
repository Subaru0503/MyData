///////////////////////////////////////
//
// 地面クラス
//
// ステージの床
//
///////////////////////////////////////

//----インクルード部----
#include "Ground.h"

// コンストラクタ
Ground::Ground(std::string name)
	: GameObject(name)
{
	m_tag = "Ground";

	// コンポーネント追加
	AddComponent<BoxCollider>();			// 当たり判定追加。
	AddComponent<ModelRenderer3D>();		// 3D描画

	// コンポーネント取得
	_boxCollider = GetComponent<BoxCollider>();
	_modelRenderer3D = GetComponent<ModelRenderer3D>();

	// シェーダーセット
	const char* file[] = {
		"VS_Object",
		"PS_TexColor",
	};

	_modelRenderer3D->SetShader(file);
}

// デストラクタ
Ground::~Ground()
{
}

// 更新処理
void Ground::Update()
{

}