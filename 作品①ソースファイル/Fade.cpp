//////////////////////////////
//
// フェード
//
//////////////////////////////

// インクルード部
#include "Fade.h"

// コンストラクタ
Fade::Fade(std::string name)
	: GameObject(name)
{
	// コンポーネント追加
	AddComponent<ModelRenderer2D>();

	// コンポーネント取得
	_modelRenderer2D = GetComponent<ModelRenderer2D>();

	// テクスチャ読み込み
	_modelRenderer2D->Load("Assets/Texture/BlackFade.png");

	// メンバ変数初期化
	_modelRenderer2D_param = _modelRenderer2D->GetParam();
	m_FadeIn = false;
	m_Time = 0.0f;
	m_TotalTime = 0.0f;

	// 値セット
	m_Alpha = 0.0f;
	m_pos.x = 640.0f;
	m_pos.y = 360.0f;
	m_scale.x = 1280.0f;
	m_scale.y = 720.0f;
	_modelRenderer2D_param->color.w = m_Alpha;
	m_FadeColor = FadeColor::Black;
}

// デストラクタ
Fade::~Fade()
{
}

// 更新処理
void Fade::Update()
{
	// フェードを実行する必要があるか
	if (!GetPlay())
	{
		return;
	}

	// カウントダウン
	m_Time -= 1.0f / 60.0f;

	// フェードの経過時間の割合から透明度を求める
	float rate = m_Time / m_TotalTime;

	// フェードアウトの場合だけ、透明度を反転させる
	if (!m_FadeIn)
	{
		rate = 1.0f - rate;
	}

	// 0.5～1.0になるように補正
	//rate = 0.5f + 0.5f * rate;

	m_Alpha = rate;

	_modelRenderer2D_param->color.w = m_Alpha;
}

// フェード開始のため必要情報を設定する
void Fade::Start(bool fadeIn, float time, FadeColor fadeColor)
{
	// フェード再生中は設定できない
	if (GetPlay())
	{
		return;
	}

	// フェードカラー設定
	if (m_FadeColor != FadeColor::Black &&
		fadeColor == FadeColor::Black)
	{
		// 現在のフェードカラー情報設定
		m_FadeColor = FadeColor::Black;

		// テクスチャ読み込み
		_modelRenderer2D->Load("Assets/Texture/BlackFade.png");
	}
	else if (m_FadeColor != FadeColor::White &&
		fadeColor == FadeColor::White)
	{
		// 現在のフェードカラー情報設定
		m_FadeColor = FadeColor::White;

		// テクスチャ読み込み
		_modelRenderer2D->Load("Assets/Texture/WhiteFade.png");
	}

	if (fadeIn)	m_Alpha = 1.0f;
	else		m_Alpha = 0.0f;
	m_FadeIn = fadeIn;
	m_Time = time;
	m_TotalTime = time;	// timeの時間かけてフェード完了する
}

// フェード中か
bool Fade::GetPlay()
{
	return m_Time > 0.0f;
}

// フェードインかどうかを返す
bool Fade::GetFadeIn()
{
	return m_FadeIn;
}