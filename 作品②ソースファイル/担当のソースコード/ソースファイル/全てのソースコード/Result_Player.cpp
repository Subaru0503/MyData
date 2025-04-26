#include "Result_Player.h"

ResultPlayer::ResultPlayer(float PosX, float PosY, float PosZ)
	: m_Left(0.0f)
	, m_Right((float)SCREEN_WIDTH)
	, m_Bottom((float)SCREEN_HEIGHT)
	, m_Top(0.0f)
	, m_near(1.0f)
	, m_far(10.0f)
	, m_pTexture{nullptr, nullptr, nullptr, nullptr}
{
	m_basePosX = PosX;
	m_basePosY = PosY;

	for (int i = 0; i < 4; ++i)
	{
		m_pTexture[i] = new Texture();
	}
	if (FAILED(m_pTexture[0]->Create("Assets/Texture/Result_PlayerEval0.png")))
	{
		MessageBox(NULL, "ResultPlayer Result_PlayerEval0.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[1]->Create("Assets/Texture/Result_PlayerEval1.png")))
	{
		MessageBox(NULL, "ResultPlayer Result_PlayerEval1.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[2]->Create("Assets/Texture/Result_PlayerEval2.png")))
	{
		MessageBox(NULL, "ResultPlayer Result_PlayerEval2.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[3]->Create("Assets/Texture/Result_PlayerEval3.png")))
	{
		MessageBox(NULL, "ResultPlayer Result_PlayerEval3.png", "Error", MB_OK);
	}
}

ResultPlayer::~ResultPlayer()
{
	for (int i = 0; i < 4; ++i)
	{
		delete m_pTexture[i];
		m_pTexture[i] = nullptr;
	}
}

void ResultPlayer::DrawEval0()
{
	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(m_basePosX, m_basePosY, 0.0f);
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));

	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());

	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));
	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(DirectX::XMFLOAT2((float)m_pTexture[0]->GetWidth(), -(float)m_pTexture[0]->GetHeight()));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[0]);
	Sprite::SetColor(DirectX::XMFLOAT4( 1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::Draw();

}

void ResultPlayer::DrawEval1()
{
	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(m_basePosX, m_basePosY, 0.0f);
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));

	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());

	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));
	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(DirectX::XMFLOAT2((float)m_pTexture[1]->GetWidth(), -(float)m_pTexture[1]->GetHeight()));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[1]);
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::Draw();
}

void ResultPlayer::DrawEval2()
{
	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(m_basePosX, m_basePosY, 0.0f);
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));

	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());

	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));
	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(DirectX::XMFLOAT2((float)m_pTexture[2]->GetWidth(), -(float)m_pTexture[2]->GetHeight()));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[2]);
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::Draw();
}

void ResultPlayer::DrawEval3()
{
	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(m_basePosX, m_basePosY, 0.0f);
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));

	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());

	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));
	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(DirectX::XMFLOAT2((float)m_pTexture[3]->GetWidth(), -(float)m_pTexture[3]->GetHeight()));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[3]);
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::Draw();
}
