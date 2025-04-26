//////////////////////////////
//
// タイトルスタートメッセージ
//
//////////////////////////////

// インクルード部
#include "StartMessage.h"

// コンストラクタ
StartMessage::StartMessage(std::string name)
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
	_opacity->SetParam(_modelRenderer2D_param);

}

// デストラクタ
StartMessage::~StartMessage()
{
}

// 更新処理
void StartMessage::Update()
{
	
}