//////////////////////////////
//
// ゲームスタート文字UI
//
//////////////////////////////

// インクルード部
#include "Start.h"

// 定数・マクロ定義
#define VALUE (0.005f)

// コンストラクタ
Start::Start(std::string name)
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
Start::~Start()
{
}

// 更新処理
void Start::Update()
{
	
}