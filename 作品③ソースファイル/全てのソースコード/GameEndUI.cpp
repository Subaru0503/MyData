#include "GameEndUI.h"

#define TIMEUP_TEXTURE_RATIO	(0.3f)
#define CLEAR_TEXTURE_RATIO		(0.4f)
#define SIZE_UP_FRAME			(10)		// テクスチャ拡縮速度

GameEndUI::GameEndUI(float PosX, float PosY, float PosZ)
: m_Left(0.0f)
, m_Right((float)SCREEN_WIDTH)
, m_Bottom((float)SCREEN_HEIGHT)
, m_Top(0.0f)
, m_near(1.0f)
, m_far(10.0f)
, m_pTexture{nullptr, nullptr}
, m_fsizeTimeUpX(0.0f)
, m_fsizeTimeUpY(0.0f)
, m_fsizeClearX(0.0f)
, m_fsizeClearY(0.0f)
, m_nMAXRatio(0)
, m_fRatio(1.0f)
, m_bRatio(false)
, m_nCnt(0)
{
	m_basePosX = PosX;
	m_basePosY = PosY;

	for (int i = 0; i < 2; ++i)
	{
		m_pTexture[i] = new Texture();
	}
	

	if (FAILED(m_pTexture[0]->Create("Assets/Texture/UI_TimeUp.png")))
	{
		MessageBox(NULL, "Progress UI_TimeUp.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[1]->Create("Assets/Texture/UI_Clear.png")))
	{
		MessageBox(NULL, "Progress UI_Clear.png", "Error", MB_OK);
	}

	m_textureSize[TimeUp].x = m_pTexture[TimeUp]->GetWidth() * TIMEUP_TEXTURE_RATIO;
	m_textureSize[TimeUp].y = m_pTexture[TimeUp]->GetHeight() * TIMEUP_TEXTURE_RATIO;
	m_textureSize[Clear].x = m_pTexture[Clear]->GetWidth() * CLEAR_TEXTURE_RATIO;
	m_textureSize[Clear].y = m_pTexture[Clear]->GetHeight() * CLEAR_TEXTURE_RATIO;
}

GameEndUI::~GameEndUI()
{
	for (int i = 0; i < 2; ++i)
	{
		if (m_pTexture)
		{
			delete m_pTexture[i];
			m_pTexture[i] = nullptr;
		}
	}
}

void GameEndUI::Update(float SizeX, float SizeY)
{
	
	//m_fsizeTimeUpX += SizeX / 60.0f;
	//m_fsizeTimeUpY += SizeY / 60.0f;
	//if (m_fsizeTimeUpX >= SizeX || m_fsizeTimeUpY >= SizeY)
	//{
	//	m_fsizeTimeUpX = 400.0f;
	//	m_fsizeTimeUpY = 400.0f;
	//}

	float sizeUPx, sizeUPy;
	if (m_fsizeTimeUpX <= m_textureSize[TimeUp].x * 2.0f) {
		sizeUPx = m_textureSize[TimeUp].x / SIZE_UP_FRAME;
		sizeUPy = m_textureSize[TimeUp].y / SIZE_UP_FRAME;
		m_fsizeTimeUpX += sizeUPx;
		m_fsizeTimeUpY += sizeUPy;
		
	}

	

	if (m_fsizeClearX <= m_textureSize[Clear].x * 2.0f) {
		sizeUPx = m_textureSize[Clear].x / SIZE_UP_FRAME;
		sizeUPy = m_textureSize[Clear].y / SIZE_UP_FRAME;
		m_fsizeClearX += sizeUPx;
		m_fsizeClearY += sizeUPy;
	}
	

	if (!m_nMAXRatio && m_fsizeTimeUpX >= m_textureSize[TimeUp].x* 2.0f && !m_bRatio )
	{
		m_fRatio -= RATIO;
		if (m_fRatio <= 0.70f)
		{
			m_nCnt++;
			m_nMAXRatio ^= 1;
		}
		
	}
	else if(m_nMAXRatio && m_fsizeTimeUpX >= m_textureSize[TimeUp].x* 2.0f)
	{
		
		m_fRatio += RATIO;
		if (m_fRatio >= 0.90f  && m_nCnt== 1)
		{
			
			m_nMAXRatio ^= 1;

		}
		else if (m_fRatio >= 0.80f  && m_nCnt == 2)
		{
			m_nMAXRatio ^= 1;
		}
		else if (m_fRatio >= 0.75f  && m_nCnt == 3)
		{
			
			m_nMAXRatio ^= 1;
		}
		else if (m_fRatio >= 0.70f  && m_nCnt == 4)
		{
			m_bRatio = true;
			m_nMAXRatio ^= 1;
		}
		/*else if (m_fRatio >= 0.60f  && m_nCnt == 3)
		{
			m_nMAXRatio ^= 1;
		}
		else if (m_fRatio >= 0.50f  && m_nCnt == 4)
		{
			m_bRatio = true;
			m_nMAXRatio ^= 1;
		}*/
	}
}

void GameEndUI::DrawTimeUp()
{
	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMMATRIX world;

	world = DirectX::XMMatrixTranslation(m_basePosX, m_basePosY, 0.0f);
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));

	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());

	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));
	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(m_fsizeTimeUpX * m_fRatio, -m_fsizeTimeUpY*m_fRatio));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[0]);
	Sprite::Draw();
}

void GameEndUI::DrawClear()
{
	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMMATRIX world;

	world = DirectX::XMMatrixTranslation(m_basePosX, m_basePosY, 0.0f);
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));

	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());

	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));
	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(m_fsizeClearX * m_fRatio, -m_fsizeClearY *m_fRatio));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[1]);
	Sprite::Draw();
}
