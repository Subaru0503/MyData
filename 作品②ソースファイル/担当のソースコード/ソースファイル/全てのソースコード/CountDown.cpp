//=================================================================
//
//	CountDown.cpp
//	カウントダウンUIを描画する
//
//=================================================================

#include "CountDown.h"

#define NUM_MAX_SIZE_X		(270.0f)	// 数字のサイズ
#define NUM_MAX_SIZE_Y		(250.0f)
#define MOJI_SIZE_RATIO		(0.35f)		// 文字のサイズ倍率
#define SIZE_UP_FRAME		(12)		// テクスチャ拡縮速度
#define WAIT				(53)		// 拡縮が始まってから次の数字が出るまでのフレーム数

CCountDown::CCountDown()
	: m_kind(0)
	, m_waitFrame(0)
{
	// 数字テクスチャ読み込み
	m_Count[0].pTexture = new Texture();
	if (FAILED(m_Count[0].pTexture->Create("Assets/Texture/UI_ResultNumber.png"))) {	// 数字
		MessageBox(NULL, "ItemUI UI_ResultNumber.png", "Error", MB_OK);
	}
	// スタートテクスチャ読み込み
	m_Count[1].pTexture = new Texture();
	if (FAILED(m_Count[1].pTexture->Create("Assets/Texture/UI_start.png"))) {	// スタート
		MessageBox(NULL, "ItemUI Star.png", "Error", MB_OK);
	}
	m_textureSize.x = m_Count[1].pTexture->GetWidth() * MOJI_SIZE_RATIO;	// テクスチャの本来の画像サイズを取得し、ちょうどいいサイズにする
	m_textureSize.y = m_Count[1].pTexture->GetHeight() * MOJI_SIZE_RATIO;	// （縦横比はそのまま）

	m_Count[0].AnimeNo = 3;
	m_Count[0].pos = DirectX::XMFLOAT2(640.0f, 360.0f);
	m_Count[0].size = DirectX::XMFLOAT2(0.0f, 0.0f);
	m_Count[0].sizeTexCoord = DirectX::XMFLOAT2(1.0f / 4, 1.0f / 3);
	m_Count[0].posTexCoord = DirectX::XMFLOAT2(m_Count[0].sizeTexCoord.x * 2, 0.0f);
	m_Count[0].phase = 0;

	m_Count[1].AnimeNo = 0;
	m_Count[1].pos = DirectX::XMFLOAT2(640.0f, 360.0f);
	m_Count[1].size = DirectX::XMFLOAT2(0.0f, 0.0f);
	m_Count[1].sizeTexCoord = DirectX::XMFLOAT2(1.0f, 1.0f);
	m_Count[1].posTexCoord = DirectX::XMFLOAT2(0.0f, 0.0f);
	m_Count[1].phase = 0;
}

CCountDown::~CCountDown()
{
	SAFE_DELETE(m_Count[0].pTexture);
	SAFE_DELETE(m_Count[1].pTexture);
}

void CCountDown::Update()
{
	// ----- カウントダウン -----
	if (m_Count[0].AnimeNo > 0) {										// カウント中なら
		if (m_Count[0].size.x >= NUM_MAX_SIZE_X && m_waitFrame > WAIT) {// 拡大しきったら
		// ----- 数字切り替え -----
			m_Count[0].size = DirectX::XMFLOAT2(0.0f, 0.0f);			// サイズを最小に
			m_Count[0].AnimeNo--;										// 次の数字へ
			m_waitFrame = 0;											// 再カウント
		}
		else if (m_Count[0].size.x < NUM_MAX_SIZE_X) {					// 拡大しきっていなければ
		// ----- テクスチャ拡大 -----
			float sizeUPx = NUM_MAX_SIZE_X / SIZE_UP_FRAME;	// 拡大率
			float sizeUPy = NUM_MAX_SIZE_Y / SIZE_UP_FRAME;
			m_Count[0].size = DirectX::XMFLOAT2(m_Count[0].size.x + sizeUPx, m_Count[0].size.y + sizeUPy);
		}
	}
	else {	// カウントが終わったらスタートを表示
		switch (m_Count[1].phase)
		{
		case 0:	// 拡大
			m_kind = 1;	// 描画を「すたーと」に
			if (m_Count[1].size.x < m_textureSize.x) {
				float sizeUPx = m_textureSize.x / SIZE_UP_FRAME;		// 拡大率
				float sizeUPy = m_textureSize.y / SIZE_UP_FRAME;
				m_Count[1].size = DirectX::XMFLOAT2(m_Count[1].size.x + sizeUPx, m_Count[1].size.y + sizeUPy);
			}
			else if (m_waitFrame > WAIT) { m_Count[1].phase = 1; }
			break;
		case 1:	// 縮小
			if (m_Count[1].size.x > 0.0f) {
				float sizeUPx = m_textureSize.x / SIZE_UP_FRAME;		// 拡大率
				float sizeUPy = m_textureSize.y / SIZE_UP_FRAME;
				m_Count[1].size = DirectX::XMFLOAT2(m_Count[1].size.x - sizeUPx, m_Count[1].size.y - sizeUPy);
			}
			break;
		}
	}
	m_waitFrame++;
}

void CCountDown::Draw()
{
	DirectX::XMFLOAT4X4 mat[3];

	DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(m_Count[m_kind].pos.x, m_Count[m_kind].pos.y, 0.0f);
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));
	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(
		0.0f/*画面左端X*/, 1280.0f/*画面右端*/, 0.0f/*画面上端*/, 720.0f/*画面下端*/, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));


	// スプライトの設定
	m_Count[m_kind].posTexCoord.x = m_Count[m_kind].sizeTexCoord.x * m_Count[m_kind].AnimeNo;
	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(m_Count[m_kind].size.x, m_Count[m_kind].size.y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(m_Count[m_kind].posTexCoord.x, m_Count[m_kind].posTexCoord.y));
	Sprite::SetUVScale(DirectX::XMFLOAT2(m_Count[m_kind].sizeTexCoord.x, m_Count[m_kind].sizeTexCoord.y));
	Sprite::SetTexture(m_Count[m_kind].pTexture);

	Sprite::Draw();
}
