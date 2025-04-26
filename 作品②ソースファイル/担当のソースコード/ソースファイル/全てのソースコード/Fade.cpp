//=================================================================
//
//	Fade.cpp
//	フェード関連
//
//=================================================================

// ========== インクルード部 ==========
#include "Fade.h"

// ========== コンストラクタ ==========
Fade::Fade()
	: m_alpha(0.0f)
	, m_isIn(false)
	, m_time(0.0f)
	, m_totalTime(0.0f)
	, m_BGKind(NONE)
{
	// ----- テクスチャ読み込み -----
	for (int i = 0; i < MAX_FADE; i++) {
		m_pTexture[i] = new Texture();
	}
	// 真っ白フェード
	if (FAILED(m_pTexture[kind::WHITE]->Create("Assets/Texture/whiteFade.png"))) {
		MessageBox(NULL, "whiteFade.png", "Error", MB_OK);
	}
	// 真っ黒フェード
	if (FAILED(m_pTexture[kind::BLACK]->Create("Assets/Texture/Shop_BG.png"))) {
		MessageBox(NULL, "blackFade.png", "Error", MB_OK);
	}
	// tips
	if (FAILED(m_pTexture[kind::TIPS]->Create("Assets/Texture/TIPS　背景.png"))) {
		MessageBox(NULL, "tipsFade.png", "Error", MB_OK);
	}
	// 惑星フェード
	if (FAILED(m_pTexture[kind::PLANET]->Create("Assets/Texture/PlanetFade.png"))) {
		MessageBox(NULL, "PlanetFade.png", "Error", MB_OK);
	}

}

// ========== デストラクタ ==========
Fade::~Fade()
{
	for (int i = 0; i < MAX_FADE; i++) {
		delete m_pTexture[i];
		m_pTexture[i] = nullptr;
	}
}

// ========== Update関数 ==========
void Fade::Update()
{
	// フェードを実行する必要があるか
	if (!IsPlay())
	{
		return;
	}

	// カウントダウン
	m_time -= 1.0f / 60.0f;// 60フレームで１

	// フェードの経過時間の割合から透明度を求める
	float rate = m_time / m_totalTime;

	// フェードインの場合だけ、透明度を反転させる
	if (!m_isIn)
	{
		rate = 1.0f - rate;
	}

	m_alpha = rate;
}

// ========== Draw関数 ==========
void Fade::Draw()
{
	// ----- 要素準備 -----
	DirectX::XMFLOAT4X4 mat[3];

	DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(1280.0f / 2.0f, 720.0f / 2, 0.0f);
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));
	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(
		0.0f, 1280.0f, 720.0f, 0.0f, 1.0f, 10.0f);
	DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));


	switch (m_BGKind) {	// 設定された種類によってテクスチャを選択
	case Fade::NONE:	return;
	case Fade::WHITE:	Sprite::SetTexture(m_pTexture[WHITE]);	break;
	case Fade::BLACK:	Sprite::SetTexture(m_pTexture[BLACK]);	break;
	case Fade::TIPS:	Sprite::SetTexture(m_pTexture[TIPS]);	break;
	case Fade::PLANET:	Sprite::SetTexture(m_pTexture[PLANET]);	break;
	}

	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(1280.0f, -720.0f));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, m_alpha));
	Sprite::Draw();
}

// フェード開始のため必要情報を設定する
void Fade::Start(bool isIn, float time, kind kind)
{
	// フェード再生中は設定できない
	if (IsPlay())
	{
		return;
	}

	if (isIn)	m_alpha = 1.0f;
	else		m_alpha = 0.0f;
	m_isIn = isIn;
	m_time = time;
	m_totalTime = time;	// timeの時間かけてフェード完了する
	m_BGKind = kind;	// 背景種類設定
}

// フェード中か
bool Fade::IsPlay()
{
	if (m_time == 0.0f)
		m_BGKind = NONE;

	return m_time > 0.0f;
}

// フェードの透明度(進捗)
float Fade::GetAlpha()
{
	return m_alpha;
}
