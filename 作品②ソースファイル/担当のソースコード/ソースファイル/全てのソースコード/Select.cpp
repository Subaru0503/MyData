#include "Select.h"

#define RATIO (0.001f)

static int cnt = 0;

Select::Select()
	: m_Left(0.0f)
	, m_Right((float)SCREEN_WIDTH)
	, m_Bottom((float)SCREEN_HEIGHT)
	, m_Top(0.0f)
	, m_near(1.0f)
	, m_far(10.0f)
	, m_pTexture{ nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}
	, m_NewRequestPos((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2)
	, m_NewRequestSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT)
	, m_RequenstPos((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2)
	, m_RequenstSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT)
	, m_BackButtonPos((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2)
	, m_BackButtonSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT)
	, m_PlayButtonPos(1020.0f, 610.0f)
	, m_PlayButtonSize(0.0f, 0.0f)
	, m_nMAXRatio(1)
	, m_fRatio(1.0f)
	, m_fRatio2(1.0f)
	, m_RequestPosTexCoord(0.0f, 0.0f)
	, m_falPha(0.0f)
	, m_falPha2(0.0f)
	, m_nCnt(0)
{
	for (int i = 0; i < 5; ++i)
	{
		m_pTexture[i] = new Texture();
	}


	if (FAILED(m_pTexture[0]->Create("Assets/Texture/Select_clear.png")))
	{
		MessageBox(NULL, "Select Select_clear.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[1]->Create("Assets/Texture/Select_Request.png")))
	{
		MessageBox(NULL, "Select Select_Request.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[2]->Create("Assets/Texture/Select_PlayButton.png")))
	{
		MessageBox(NULL, "Select Select_PlayButton.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[3]->Create("Assets/Texture/Select_BackButton.png")))
	{
		MessageBox(NULL, "Select Select_BackButton.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[4]->Create("Assets/Texture/Shop_BG.png")))
	{
		MessageBox(NULL, "Select Select_BackButton.png", "Error", MB_OK);
	}
	
	
	
	m_PlayButtonSize = DirectX::XMFLOAT2(m_pTexture[2]->GetWidth(), m_pTexture[2]->GetHeight());
}

Select::~Select()
{
	for (int i = 0; i < 5; ++i)
	{
		if (m_pTexture[i])
		{
			delete m_pTexture[i];
			m_pTexture[i] = nullptr;
		}
	}
}

void Select::Update(int select)
{
	if (!m_nMAXRatio)			// ç≈ëÂî{ó¶Ç∂Ç·Ç»Ç©Ç¡ÇΩÇÁ
	{
		m_fRatio += RATIO;		// î{ó¶ê›íË
		m_fRatio2 -= RATIO;
		if (m_fRatio >= 1.03f)	// ç≈ëÂî{ó¶Çí¥Ç¶ÇΩÇÁ
		{
			m_nMAXRatio ^= 1;	// ÉtÉâÉOè„Ç∞
		}
	}
	else
	{
		m_fRatio -= RATIO;		// î{ó¶ê›íË
		m_fRatio2 += RATIO;
		if (m_fRatio <= 0.97f)	// ç≈è¨î{ó¶ÇÊÇËè¨Ç≥Ç≠Ç»Ç¡ÇΩÇÁ
		{
			m_nMAXRatio ^= 1;	// ÉtÉâÉOè„Ç∞
		}
	}

	if (select == 0)
	{
		m_RequestPosTexCoord = DirectX::XMFLOAT2(0.0f, 0.0f);

	}
	else if (select == 1)
	{
		m_RequestPosTexCoord = DirectX::XMFLOAT2(0.0f, 1.0f / 3.0f);

	}
	else if(select == 2)
	{
		m_RequestPosTexCoord = DirectX::XMFLOAT2(0.0f, (1.0f / 3.0f) * 2);
	}
}

void Select::Draw()
{
	
	//àÀóäèëï`âÊ
	DirectX::XMFLOAT4X4 mat2[3];
	DirectX::XMMATRIX world2;

	world2 = DirectX::XMMatrixTranslation(m_RequenstPos.x, m_RequenstPos.y, 0.0f);
	DirectX::XMStoreFloat4x4(&mat2[0], DirectX::XMMatrixTranspose(world2));

	DirectX::XMStoreFloat4x4(&mat2[1], DirectX::XMMatrixIdentity());

	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat2[2], DirectX::XMMatrixTranspose(proj));

	Sprite::SetWorld(mat2[0]);
	Sprite::SetView(mat2[1]);
	Sprite::SetProjection(mat2[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(m_RequenstSize.x, -m_RequenstSize.y));
	Sprite::SetUVPos(DirectX::XMFLOAT2( m_RequestPosTexCoord.x, m_RequestPosTexCoord.y));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f / 3.0f));
	Sprite::SetColor(DirectX::XMFLOAT4( 1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[1]);
	Sprite::Draw();

	//playÉ{É^Éìï`âÊ
	DirectX::XMFLOAT4X4 mat3[3];
	DirectX::XMMATRIX world3;

	world3 = DirectX::XMMatrixTranslation(m_PlayButtonPos.x, m_PlayButtonPos.y, 0.0f);
	DirectX::XMStoreFloat4x4(&mat3[0], DirectX::XMMatrixTranspose(world3));

	DirectX::XMStoreFloat4x4(&mat3[1], DirectX::XMMatrixIdentity());


	DirectX::XMStoreFloat4x4(&mat3[2], DirectX::XMMatrixTranspose(proj));

	Sprite::SetWorld(mat3[0]);
	Sprite::SetView(mat3[1]);
	Sprite::SetProjection(mat3[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(m_PlayButtonSize.x * m_fRatio2 , -m_PlayButtonSize.y * m_fRatio));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[2]);
	Sprite::Draw();

	//ñﬂÇÈÉ{É^Éìï`âÊ
	DirectX::XMFLOAT4X4 mat4[3];
	DirectX::XMMATRIX world4;

	world4 = DirectX::XMMatrixTranslation(m_BackButtonPos.x, m_BackButtonPos.y, 0.0f);
	DirectX::XMStoreFloat4x4(&mat4[0], DirectX::XMMatrixTranspose(world4));

	DirectX::XMStoreFloat4x4(&mat4[1], DirectX::XMMatrixIdentity());


	DirectX::XMStoreFloat4x4(&mat4[2], DirectX::XMMatrixTranspose(proj));

	Sprite::SetWorld(mat4[0]);
	Sprite::SetView(mat4[1]);
	Sprite::SetProjection(mat4[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(m_BackButtonSize.x, -m_BackButtonSize.y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[3]);
	Sprite::Draw();

	
}

void Select::UpdateNewRequest()
{
	m_nCnt++;
}

void Select::DrawNewRequest()
{
	//ï`âÊ
	DirectX::XMFLOAT4X4 mat0[3];
	DirectX::XMMATRIX world0;

	world0 = DirectX::XMMatrixTranslation(m_NewRequestPos.x, m_NewRequestPos.y, 0.0f);
	DirectX::XMStoreFloat4x4(&mat0[0], DirectX::XMMatrixTranspose(world0));

	DirectX::XMStoreFloat4x4(&mat0[1], DirectX::XMMatrixIdentity());

	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat0[2], DirectX::XMMatrixTranspose(proj));

	Sprite::SetWorld(mat0[0]);
	Sprite::SetView(mat0[1]);
	Sprite::SetProjection(mat0[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(m_NewRequestSize.x, -m_NewRequestSize.y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 0.8f));
	Sprite::SetTexture(m_pTexture[4]);
	Sprite::Draw();


	//ï`âÊ
	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMMATRIX world;

	world = DirectX::XMMatrixTranslation(m_NewRequestPos.x, m_NewRequestPos.y, 0.0f);
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));

	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());

	
	DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));

	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(m_NewRequestSize.x, -m_NewRequestSize.y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetColor(DirectX::XMFLOAT4( 1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[0]);

	if(m_nCnt >= 30) Sprite::Draw();
	


}
