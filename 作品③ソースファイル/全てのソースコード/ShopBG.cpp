#include "ShopBG.h"

ShopBG::ShopBG()
	: m_Left(0.0f)
	, m_Right(1280.0f)
	, m_Bottom(720.0f)
	, m_Top(0.0f)
	, m_near(1.0f)
	, m_far(10.0f)

{
	m_pTexture = new Texture();
	if (FAILED(m_pTexture->Create("Assets/Texture/Shop_BG.png")))
	{
		MessageBox(NULL, "ShopBG Shop_BG.png", "Error", MB_OK);
	}
}

ShopBG::~ShopBG()
{
	SAFE_DELETE(m_pTexture);
}

void ShopBG::Draw()
{
	DirectX::XMFLOAT4X4 mat[3];

	DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(1280.0f / 2.0f, 720.0f / 2, 0.0f);
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));
	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(
		m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));


	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(1280.0f, -720.0f));
	Sprite::SetUVPos(DirectX::XMFLOAT2( 0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2( 1.0f, 1.0f));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 0.8f));
	Sprite::SetTexture(m_pTexture);
	Sprite::Draw();
}
