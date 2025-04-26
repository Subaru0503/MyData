//////////////////////////////
//
// 右矢印UI
//
//////////////////////////////

// インクルード部
#include "Right.h"

#include "ShaderManager.h"

// 定数・マクロ定義
#define VALUE (0.0025f)

// コンストラクタ
Right::Right(std::string name)
	: GameObject(name)
{
	// コンポーネント追加
	AddComponent<ModelRenderer2D>();

	// コンポーネント取得
	_modelRenderer2D = GetComponent<ModelRenderer2D>();

	// メンバ変数初期化
	_modelRenderer2D_param = _modelRenderer2D->GetParam();

	_modelRenderer2D_param->color = DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);

	// シェーダーファイル
	const char* file[] = {
		"VS_Color",
		"PS_Color",
	};

	// シェーダー設定
	_modelRenderer2D->SetVertexShader(ShaderManager::GetInstance().GetShader<VertexShader>(file[0]), file[0]);
	_modelRenderer2D->SetPixelShader(ShaderManager::GetInstance().GetShader<PixelShader>(file[1]), file[1]);

	m_MaxFlg = false;
}

// デストラクタ
Right::~Right()
{
}

// 更新処理
void Right::Update()
{
	Blink();
}

// 点滅処理
void Right::Blink()
{
	float G = _modelRenderer2D_param->color.y;
	// 透明になっていたら
	if (m_MaxFlg)
	{
		G += VALUE;		// 緑上げる
		// 一定値までいったら
		if (G >= 0.15f)
		{
			m_MaxFlg = false;	// フラグ下げ
		}
	}
	// 透明度がなくなっていたら
	else
	{
		G -= VALUE;		// 緑を下げる
		// 透明になったら
		if (G <= 0.0f)
		{
			m_MaxFlg = true;	// フラグ上げ
		}
	}

	_modelRenderer2D_param->color.y = G;
}