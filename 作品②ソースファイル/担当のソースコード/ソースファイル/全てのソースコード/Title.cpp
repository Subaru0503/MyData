#include "Title.h"

#define RATIO (0.002f)
TItle::TItle()
	: m_Left(0.0f)
	, m_Right((float)SCREEN_WIDTH)
	, m_Bottom((float)SCREEN_HEIGHT)
	, m_Top(0.0f)
	, m_near(1.0f)
	, m_far(10.0f)
	, m_pTexture{nullptr, nullptr, nullptr, nullptr, nullptr}
	, m_BGPos((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2)
	, m_BGSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT)
	, m_PlayerPos(0.0f, 0.0f)
	, m_PlayerSize(0.0f, 0.0f)
	, m_ButtonPos(0.0f, 0.0f)
	, m_ButtonSize(0.0f, 0.0f)
	, m_LogoPos(0.0f, 0.0f)
	, m_LogoSize(0.0f, 0.0f)
	, m_nMAXRatio(0)
	, m_nMAXRatio2(0)
	, m_fRatio(1.0f)
	, m_fRadius(0.0f)
	, AnimeFinish(false)
	, m_LogoBasePos(0.0f, 0.0f)
	, m_LogoBaseSize(0.0f, 0.0f)
	, m_fRadian(0.0f)
	, m_fRadian2(0.0f)
	, LogoAnime(true)
	, PlayerAnime(true)
{
	for (int i = 0; i < 5; ++i)
	{
		m_pTexture[i] = new Texture();
	}
	

	if (FAILED(m_pTexture[0]->Create("Assets/Texture/Title_BG.png")))
	{
		MessageBox(NULL, "Title Title_BG.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[1]->Create("Assets/Texture/Title_Player.png")))
	{
		MessageBox(NULL, "Title Title_Player.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[2]->Create("Assets/Texture/Title_Button.png")))
	{
		MessageBox(NULL, "Title Title_Button.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[3]->Create("Assets/Texture/Title_Logo.png")))
	{
		MessageBox(NULL, "Title Title_Logo.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[4]->Create("Assets/Texture/Result_BG.png")))
	{
		MessageBox(NULL, "ResultBG Result_BG.png", "Error", MB_OK);
	}

	//m_PlayerPos = DirectX::XMFLOAT2(960.0f, 360.0f);
	m_PlayerPos = DirectX::XMFLOAT2((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT / 2);
	m_PlayerSize = DirectX::XMFLOAT2((float)m_pTexture[1]->GetWidth(), (float)m_pTexture[1]->GetHeight());
	m_ButtonPos = DirectX::XMFLOAT2(200.0f, 540.0f);
	m_ButtonSize = DirectX::XMFLOAT2((float)m_pTexture[2]->GetWidth()* 1.1f, (float)m_pTexture[2]->GetHeight() * 1.1f);
	m_LogoBasePos = DirectX::XMFLOAT2(320.0f, 180.0f);
	m_LogoBaseSize = DirectX::XMFLOAT2((float)m_pTexture[3]->GetWidth(), (float)m_pTexture[3]->GetHeight());
}

TItle::~TItle()
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

void TItle::Update()
{
	if (!m_nMAXRatio)			// ç≈ëÂî{ó¶Ç∂Ç·Ç»Ç©Ç¡ÇΩÇÁ
	{
		m_fRatio += RATIO;		// î{ó¶ê›íË
		
		if (!LogoAnime) m_fRadian += 0.08f;
		if (!PlayerAnime) m_fRadian2 -= 0.03f;
		if (m_fRatio >= 1.05f)	// ç≈ëÂî{ó¶Çí¥Ç¶ÇΩÇÁ
		{
			m_nMAXRatio ^= 1;	// ÉtÉâÉOè„Ç∞
		}
	}
	else
	{
		m_fRatio -= RATIO;		// î{ó¶ê›íË
		if (!LogoAnime) m_fRadian -= 0.08f;
		if (!PlayerAnime) m_fRadian2 += 0.03f;
		
		if (m_fRatio <= 0.95f)	// ç≈è¨î{ó¶ÇÊÇËè¨Ç≥Ç≠Ç»Ç¡ÇΩÇÁ
		{
			m_nMAXRatio ^= 1;	// ÉtÉâÉOè„Ç∞
		}
	}

	////ÉvÉåÉCÉÑÅ[
	//if (!m_nMAXRatio2)			// ç≈ëÂî{ó¶Ç∂Ç·Ç»Ç©Ç¡ÇΩÇÁ
	//{
	//	m_PlayerPos.x += 1.0f;

	//	

	//	if (m_PlayerPos.x >= 641.0f)	// ç≈ëÂî{ó¶Çí¥Ç¶ÇΩÇÁ
	//	{
	//		m_nMAXRatio2 ^= 1;	// ÉtÉâÉOè„Ç∞
	//	}
	//}
	//else
	//{
	//	
	//	m_PlayerPos.x -= 1.0f;

	//	if (m_PlayerPos.x <= 639.0f)	// ç≈è¨î{ó¶ÇÊÇËè¨Ç≥Ç≠Ç»Ç¡ÇΩÇÁ
	//	{
	//		m_nMAXRatio2 ^= 1;	// ÉtÉâÉOè„Ç∞
	//	}
	//}



	m_LogoSize.x += m_LogoBaseSize.x / 60.0f;
	m_LogoSize.y += m_LogoBaseSize.y / 60.0f;
	m_LogoPos.x += m_LogoBasePos.x / 60.0f;
	m_LogoPos.y += m_LogoBasePos.y / 60.0f;

	
	if (m_fRadian2 <= 1800.0f && LogoAnime)
	{
		m_fRadian += 30.0f;
	}
	
	if (m_LogoSize.x >= m_LogoBaseSize.x)
	{
		m_LogoPos = DirectX::XMFLOAT2(m_LogoBasePos.x, m_LogoBasePos.y);
		m_LogoSize = DirectX::XMFLOAT2(m_LogoBaseSize.x, m_LogoBaseSize.y);
		//m_PlayerPos.x = 640.0f;
		LogoAnime = false;
		PlayerAnime = false;
		
	}

	
	if (m_PlayerPos.x >= 640.0f && PlayerAnime)
	{
		m_PlayerPos.x -= 640.0f / 60.0f;
		
	}
	

}

void TItle::Draw()
{

	//BGï`âÊ
	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMMATRIX world;

	world = DirectX::XMMatrixTranslation(m_BGPos.x, m_BGPos.y, 0.0f);
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));

	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());

	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));

	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(m_BGSize.x, -m_BGSize.y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[0]);
	Sprite::Draw();

	//Playerï`âÊ
	DirectX::XMFLOAT4X4 mat2[3];
	DirectX::XMMATRIX world2;
	DirectX::XMMATRIX T3 = DirectX::XMMatrixTranslation(m_PlayerPos.x, m_PlayerPos.y, 0.0f);
	DirectX::XMMATRIX R3 = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_fRadian2));

	world2 = R3 * T3;
	DirectX::XMStoreFloat4x4(&mat2[0], DirectX::XMMatrixTranspose(world2));

	DirectX::XMStoreFloat4x4(&mat2[1], DirectX::XMMatrixIdentity());

	
	DirectX::XMStoreFloat4x4(&mat2[2], DirectX::XMMatrixTranspose(proj));

	Sprite::SetWorld(mat2[0]);
	Sprite::SetView(mat2[1]);
	Sprite::SetProjection(mat2[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(m_PlayerSize.x, -m_PlayerSize.y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[1]);
	Sprite::Draw();

	//É{É^Éìï`âÊ
	DirectX::XMFLOAT4X4 mat3[3];
	DirectX::XMMATRIX world3;
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_ButtonPos.x, m_ButtonPos.y, 0.0f);
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_fRadius));
	world3 = R * T;
	DirectX::XMStoreFloat4x4(&mat3[0], DirectX::XMMatrixTranspose(world3));

	DirectX::XMStoreFloat4x4(&mat3[1], DirectX::XMMatrixIdentity());

	
	DirectX::XMStoreFloat4x4(&mat3[2], DirectX::XMMatrixTranspose(proj));

	Sprite::SetWorld(mat3[0]);
	Sprite::SetView(mat3[1]);
	Sprite::SetProjection(mat3[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(m_ButtonSize.x * m_fRatio, -m_ButtonSize.y * m_fRatio));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[2]);
	Sprite::Draw();

	//ÉçÉSï`âÊ
	DirectX::XMFLOAT4X4 mat4[3];
	DirectX::XMMATRIX world4;
	DirectX::XMMATRIX T2 = DirectX::XMMatrixTranslation(m_LogoPos.x, m_LogoPos.y, 0.0f);;
	DirectX::XMMATRIX R2 = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_fRadian));

	world4 = R2 * T2;
	DirectX::XMStoreFloat4x4(&mat4[0], DirectX::XMMatrixTranspose(world4));

	DirectX::XMStoreFloat4x4(&mat4[1], DirectX::XMMatrixIdentity());

	
	DirectX::XMStoreFloat4x4(&mat4[2], DirectX::XMMatrixTranspose(proj));

	Sprite::SetWorld(mat4[0]);
	Sprite::SetView(mat4[1]);
	Sprite::SetProjection(mat4[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(m_LogoSize.x, -m_LogoSize.y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[3]);
	Sprite::Draw();
}

bool TItle::AnimeButton()
{
	m_fRadius += 20.0f;
	if (m_ButtonSize.y > 0)
	{
		m_ButtonSize.x -= 4.0f;
		m_ButtonSize.y -= 2.0f;
		m_ButtonPos.x += 7.0f;
		m_ButtonPos.y -= 2.5f;
	}
	else if (m_ButtonSize.y <= 0)
	{
		m_ButtonSize.x = 0.0f;
		m_ButtonSize.y = 0.0f;
		AnimeFinish = true;
	}


	return AnimeFinish;
}
bool TItle::GetPlayerAnime()
{
	return PlayerAnime;
}