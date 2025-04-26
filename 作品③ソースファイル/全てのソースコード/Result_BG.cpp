#include "Result_BG.h"
#include "Input.h"

#define CHANGE_ANIME (2)
ResultBG::ResultBG()
	: m_Left(0.0f)
	, m_Right((float)SCREEN_WIDTH)
	, m_Bottom((float)SCREEN_HEIGHT)
	, m_Top(0.0f)
	, m_near(1.0f)
	, m_far(10.0f)
	, m_pTexture(nullptr)
	, m_basePosX((float)SCREEN_WIDTH / 2)
	, m_basePosY((float)SCREEN_HEIGHT / 2)
	, m_animeNo(0)
	, m_frame(0)
	, m_totalFrame(0)
	, m_bEndAnime(false)
{
	m_pTexture = new Texture();

	if (FAILED(m_pTexture->Create("Assets/Texture/ResultAnime.jpg")))
	{
		MessageBox(NULL, "ResultAnime.jpg", "Error", MB_OK);
	}
}

ResultBG::~ResultBG()
{
	if (m_pTexture)
	{
		delete m_pTexture;
		m_pTexture = nullptr;
	}
}

void ResultBG::Update()
{
	m_uvSize.x = 1.0f / 12.0f;
	m_uvSize.y = 1.0f / 12.0f;

	m_uvPos.x = (m_animeNo % 12) / 12.0f;
	m_uvPos.y = (m_animeNo / 12) / 12.0f;

	m_frame++;
	if (m_animeNo < 143)
	{
		if (m_frame >= CHANGE_ANIME)
		{
			m_frame = 0;
			m_animeNo++;

		}
	}

	float totalTime = 6.0f;
	float totalFrame = totalTime * 60.0f;
	float rate = m_totalFrame / totalFrame;
	m_totalFrame;


	if (m_animeNo >= 143 && !m_bEndAnime)
	{
		m_bEndAnime = true;
	}


	if (IsKeyTrigger(VK_SPACE))
	{
		m_animeNo = 143;
		m_bEndAnime = true;
	}
}

void ResultBG::Draw()
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
	Sprite::SetSize(DirectX::XMFLOAT2(1280.0f, -720.0f));
	Sprite::SetUVPos(DirectX::XMFLOAT2(m_uvPos.x, m_uvPos.y));
	Sprite::SetUVScale(DirectX::XMFLOAT2(m_uvSize.x, m_uvSize.y));
	Sprite::SetTexture(m_pTexture);
	Sprite::Draw();
}

bool ResultBG::IsEndAnime()
{
	return m_bEndAnime;
}
