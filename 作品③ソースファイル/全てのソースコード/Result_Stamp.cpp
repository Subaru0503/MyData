#include "Result_Stamp.h"


ResultStamp::ResultStamp(float PosX, float PosY, float PosZ, float radian)
	: m_Left(0.0f)
	, m_Right((float)SCREEN_WIDTH)
	, m_Bottom((float)SCREEN_HEIGHT)
	, m_Top(0.0f)
	, m_near(1.0f)
	, m_far(10.0f)
	, m_fradian(0.0f)
	, m_pTexture(nullptr)
	, m_fAlpha(0.0f)
	, m_fRatio(1.5f)
{
	m_basePosX = PosX;
	m_basePosY = PosY;
	m_fsize.x = 100.0f;
	m_fsize.y = 100.0f;
	m_fradian = radian;

	m_pTexture = new Texture();
	if (FAILED(m_pTexture->Create("Assets/Texture/UI_Stamp.png")))
	{
		MessageBox(NULL, "ResultStamp UI_Stamp.png", "Error", MB_OK);

	}
}

ResultStamp::~ResultStamp()
{
	SAFE_DELETE(m_pTexture);
}

void ResultStamp::Update()
{
	m_fAlpha += 0.02f;
	if (m_fAlpha >= 1.0f)
	{
		m_fAlpha = 1.0f;
	}

	if (m_fRatio >= 1.0f && m_fAlpha >= 1.0f)
	{
		m_fRatio -= 0.02f;
	}

}

void ResultStamp::DrawEval3()
{
	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMMATRIX world;

	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_basePosX, m_basePosY, 0.0f);
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_fradian));
	world = R * T;

	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));

	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());

	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));

	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(m_fsize.x * m_fRatio, -m_fsize.y * m_fRatio));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(0.5f, 0.5f));
	Sprite::SetTexture(m_pTexture);
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, m_fAlpha));
	Sprite::Draw();
}

void ResultStamp::DrawEval2()
{
	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMMATRIX world;

	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_basePosX, m_basePosY, 0.0f);
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_fradian));
	world = R * T;

	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));

	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());

	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));

	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(m_fsize.x * m_fRatio, -m_fsize.y * m_fRatio));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.5f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(0.5f, 0.5f));
	Sprite::SetTexture(m_pTexture);
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, m_fAlpha));
	Sprite::Draw();
}

void ResultStamp::DrawEval1()
{
	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMMATRIX world;

	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_basePosX, m_basePosY, 0.0f);
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_fradian));
	world = R * T;

	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));

	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());

	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));

	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(m_fsize.x * m_fRatio, -m_fsize.y * m_fRatio));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.5f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(0.5f, 0.5f));
	Sprite::SetTexture(m_pTexture);
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, m_fAlpha));
	Sprite::Draw();
}
