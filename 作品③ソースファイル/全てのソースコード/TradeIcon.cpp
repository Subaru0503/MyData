#include "TradeIcon.h"

TradeIcon::TradeIcon()
	: m_pTex(nullptr)
	, m_pos(0.0f, 0.0f,0.0f)
	, m_pPlayer(nullptr)
	, m_fRatio(1.0f)
	, m_nMaxRatio(0)
{
	m_pTex = new Texture();

	if (FAILED(m_pTex->Create("Assets/Texture/UI_TradeIcon.png")))
	{
		MessageBox(NULL, "UI_TradeIcon.png", "Error", MB_OK);
	}
}

TradeIcon::~TradeIcon()
{
	SAFE_DELETE(m_pTex);
}

void TradeIcon::Update()
{
}

void TradeIcon::Draw()
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

	if (m_pPlayer->GetTrade())
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



	DirectX::XMMATRIX ShopIcon = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y + 3.0f, m_pos.z);
	DirectX::XMMATRIX IconWorld = matinv * ShopIcon;
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(IconWorld));
	Sprite::SetWorld(mat[0]);
	Sprite::SetView(m_pPlayer->GetViewMatrix());
	Sprite::SetProjection(m_pPlayer->GetProjectionMatrix());
	Sprite::SetSize(DirectX::XMFLOAT2(2.0f * m_fRatio, 2.0f * m_fRatio));
	Sprite::SetUVPos(DirectX::XMFLOAT2( 0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetTexture(m_pTex);
	Sprite::Draw();
	}
}

void TradeIcon::SetPos(DirectX::XMFLOAT3 pos)
{
	m_pos = pos;
}

void TradeIcon::SetPlayer(CPlayer * player)
{
	m_pPlayer = player;
}
