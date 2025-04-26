//////////////////////////////
//
// ポーズ文字UI
//
//////////////////////////////

// インクルード部
#include "PauseMozi.h"

// 定数・マクロ定義
#define VALUE (0.005f)

// コンストラクタ
PauseMozi::PauseMozi(std::string name)
	: GameObject(name)
{
	// コンポーネント追加
	AddComponent<ModelRenderer2D>();
	AddComponent<Opacity>();

	// コンポーネント取得
	_modelRenderer2D = GetComponent<ModelRenderer2D>();
	_opacity = GetComponent<Opacity>();

	// メンバ変数初期化
	_modelRenderer2D_param = _modelRenderer2D->GetParam();
	_opacity->SetChangeValue(VALUE);
	_opacity->SetParam(_modelRenderer2D_param);
}

// デストラクタ
PauseMozi::~PauseMozi()
{
}

// 更新処理
void PauseMozi::Update()
{

}