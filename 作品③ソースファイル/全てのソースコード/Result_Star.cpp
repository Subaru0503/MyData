#include "Result_Star.h"

ResultStar::ResultStar(float PosX, float PosY, float PosZ, float radian)
	: m_Left(0.0f)
	, m_Right((float)SCREEN_WIDTH)
	, m_Bottom((float)SCREEN_HEIGHT)
	, m_Top(0.0f)
	, m_near(1.0f)
	, m_far(10.0f)
	, m_pTexture(nullptr)
	, m_basePosX(0.0f)
	, m_basePosY(0.0f)
{
	star.pos = DirectX::XMFLOAT3(PosX, PosY, PosZ);
	star.size = DirectX::XMFLOAT2(0.0f, 0.0f);
	star.radian = radian;

	m_pTexture = new Texture();
	if (FAILED(m_pTexture->Create("Assets/Texture/UI_star.png")))
	{
		MessageBox(NULL, "Resultstar UI_star.png", "Error", MB_OK);
	}
}

ResultStar::~ResultStar()
{
	if (m_pTexture)
	{
		delete m_pTexture;
		m_pTexture = nullptr;
	}
}

void ResultStar::Update()
{
	star.size.x += 2.0f;
	star.size.y += 2.0f;
	if (star.size.x >= 140.0f || star.size.y >= 140.0f)
	{
		star.size.x = 140.0f;
		star.size.y = 140.0f;
	}
}

void ResultStar::Draw()
{
	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMMATRIX world;

	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(star.pos.x, star.pos.y, star.pos.z);
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(star.radian));
	world = R * T;
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));

	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());

	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));

	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(star.size.x, -star.size.y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture);
	Sprite::Draw();
}
