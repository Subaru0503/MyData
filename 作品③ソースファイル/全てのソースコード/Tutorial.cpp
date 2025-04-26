#include "Tutorial.h"

Tutorial::Tutorial()
	: m_pTexture{nullptr, nullptr, nullptr, nullptr}
	, m_pPlayer(nullptr)
	, m_pIconTex(nullptr)
	, m_nMaxRatio(0)
	, m_fRatio(1.0f)
{
	for (int i = 0; i < 4; ++i)
	{
		m_pTexture[i] = new Texture();
	}

	if (FAILED(m_pTexture[0]->Create("Assets/Texture/Shop_BG.png"))) {
		MessageBox(NULL, "Shop_BG.png", "Error", MB_OK);
	}
	
	if (FAILED(m_pTexture[1]->Create("Assets/Texture/ƒqƒ“ƒg_1.png"))) {
		MessageBox(NULL, "ƒqƒ“ƒg_1.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[2]->Create("Assets/Texture/ƒqƒ“ƒg_2.png"))) {
		MessageBox(NULL, "ƒqƒ“ƒg_2.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[3]->Create("Assets/Texture/ƒqƒ“ƒg_3.png"))) {
		MessageBox(NULL, "ƒqƒ“ƒg_3.png", "Error", MB_OK);
	}

	m_pIconTex = new Texture();
	if (FAILED(m_pIconTex->Create("Assets/Texture/UI_TradeIcon.png"))) {
		MessageBox(NULL, "UI_TradeIcon.png", "Error", MB_OK);
	}

}

Tutorial::~Tutorial()
{
	for (int i = 0; i < 4; ++i)
	{
		delete m_pTexture[i];
		m_pTexture[i] = nullptr;
	}
	delete m_pIconTex;
	m_pIconTex = nullptr;
}

void Tutorial::Update()
{
}

void Tutorial::Draw(int num)
{
	switch (num)
	{
	case 0:
		Sprite::SetTexture(m_pTexture[1]);
		break;
	case 1:
		Sprite::SetTexture(m_pTexture[2]);
		break;
	case 2:
		Sprite::SetTexture(m_pTexture[3]);
		break;
	default:
		break;
	}

	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMMATRIX world;

	world = DirectX::XMMatrixTranslation(640.0f, 360.0f, 0.0f);
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));

	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());

	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 1.0f, 10.0f);
	DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));

	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(1280.0f, -720.0f));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::Draw();
}

void Tutorial::DrawIcon()
{
	DirectX::XMFLOAT4X4 mat[3];
	//‚«o‚µ•\Ž¦
	DirectX::XMFLOAT4X4 inv;
	inv = m_pPlayer->GetViewMatrix();
	DirectX::XMMATRIX matinv = DirectX::XMLoadFloat4x4(&inv);
	matinv = DirectX::XMMatrixTranspose(matinv);

	DirectX::XMStoreFloat4x4(&inv, matinv);
	inv._41 = inv._42 = inv._43 = 0.0f;
	matinv = DirectX::XMLoadFloat4x4(&inv);
	matinv = DirectX::XMMatrixInverse(nullptr, matinv);

	if (m_pPlayer->IsTutorial())
	{
		if (!m_nMaxRatio)
		{
			m_fRatio += 0.01f;
			if (m_fRatio >= 1.1f)
			{
				m_nMaxRatio ^= 1;
			}
		}
		else
		{
			m_fRatio -= 0.01f;
			if (m_fRatio <= 0.9f)
			{
				m_nMaxRatio ^= 1;
			}
		}



		DirectX::XMMATRIX ShopIcon = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y + 2.0f, m_pos.z);
		DirectX::XMMATRIX IconWorld = matinv * ShopIcon;
		DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(IconWorld));
		Sprite::SetWorld(mat[0]);
		Sprite::SetView(m_pPlayer->GetViewMatrix());
		Sprite::SetProjection(m_pPlayer->GetProjectionMatrix());
		Sprite::SetSize(DirectX::XMFLOAT2(2.0f * m_fRatio, 2.0f * m_fRatio));
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
		Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
		Sprite::SetTexture(m_pIconTex);
		Sprite::Draw();
	}
}

void Tutorial::SetPlayer(CPlayer * player)
{
	m_pPlayer = player;
}

void Tutorial::SetPos(DirectX::XMFLOAT3 pos)
{
	m_pos = pos;
}
