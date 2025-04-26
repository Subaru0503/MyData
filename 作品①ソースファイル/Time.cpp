//////////////////////////////
//
// 時間
//
//////////////////////////////

// インクルード部
#include "Time.h"

// 定数・マクロ定義
#define TOTAL_TIME (1.0f)	// フェードアウトにかかる時間(秒)

// コンストラクタ
Time::Time(std::string name)
	: GameObject(name)
{
	// コンポーネント追加
	AddComponent<ModelRenderer2D>();

	// コンポーネント取得
	_modelRenderer2D = GetComponent<ModelRenderer2D>();

	// メンバ変数初期化
	_modelRenderer2D_param = _modelRenderer2D->GetParam();

	_modelRenderer2D_param->MaxGrid = DirectX::XMINT2(5, 2);
	_modelRenderer2D_param->uvSize.x = 1.0f / _modelRenderer2D_param->MaxGrid.x;
	_modelRenderer2D_param->uvSize.y = 1.0f / _modelRenderer2D_param->MaxGrid.y;
	m_Time = 0.0f;

	// 値セット
	m_Alpha = 0.5f;
}

// デストラクタ
Time::~Time()
{
}

// 更新処理
void Time::Update()
{
}

void Time::AlphaUpdate()
{
	// 透明度がなくなってたら処理しない
	if (m_Alpha >= 1.0f) return;

	m_Time += 1.0f / 60.0f;

	// フェードの経過時間の割合から透明度を求める
	float rate = m_Time / TOTAL_TIME;
	rate = 0.5f + 0.5f * rate;	// 0.5～1.0に補正をかける
	m_Alpha = rate;				// 透明度を下げる
	// 透明度更新
	_modelRenderer2D_param->color.w = m_Alpha;
}
