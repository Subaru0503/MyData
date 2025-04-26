#include "Result_Message.h"

ResultMsg::ResultMsg(float PosX, float PosY, float PosZ, float radian)
	: m_Left(0.0f)
	, m_Right((float)SCREEN_WIDTH)
	, m_Bottom((float)SCREEN_HEIGHT)
	, m_Top(0.0f)
	, m_near(1.0f)
	, m_far(10.0f)
	, m_fradian(0.0f)
	, m_pTexture{nullptr, nullptr, nullptr, nullptr}
	
{
	m_basePosX = PosX;
	m_basePosY = PosY;
	m_fsize.x = 600.0f;
	m_fsize.y = 400.0f;
	m_fradian = radian;

	for (int i = 0; i < 4; ++i)
	{
		m_pTexture[i] = new Texture();
		
	}
	if (FAILED(m_pTexture[0]->Create("Assets/Texture/UI_ResultMsg_Eval0.png")))
	{
		MessageBox(NULL, "ResultMsg UI_ResultMsg_Eval0.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[1]->Create("Assets/Texture/UI_ResultMsg_Eval1.png")))
	{
		MessageBox(NULL, "ResultMsg UI_ResultMsg_Eval1.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[2]->Create("Assets/Texture/UI_ResultMsg_Eval2.png")))
	{
		MessageBox(NULL, "ResultMsg UI_ResultMsg_Eval2.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[3]->Create("Assets/Texture/UI_ResultMsg_Eval3.png")))
	{
		MessageBox(NULL, "ResultMsg UI_ResultMsg_Eval3.png", "Error", MB_OK);
	}
}

ResultMsg::~ResultMsg()
{
	for (int i = 0; i < 4; ++i)
	{
		delete m_pTexture[i];
		m_pTexture[i] = nullptr;
	}
}

void ResultMsg::Update()
{
}

void ResultMsg::DrawEval3()
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
	Sprite::SetSize(DirectX::XMFLOAT2( m_fsize.x, -m_fsize.y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[3]);
	Sprite::Draw();
}

void ResultMsg::DrawEval2()
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
	Sprite::SetSize(DirectX::XMFLOAT2(m_fsize.x, -m_fsize.y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[2]);
	Sprite::Draw();
}

void ResultMsg::DrawEval1()
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
	Sprite::SetSize(DirectX::XMFLOAT2(m_fsize.x, -m_fsize.y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[1]);
	Sprite::Draw();
}

void ResultMsg::DrawEval0()
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
	Sprite::SetSize(DirectX::XMFLOAT2(m_fsize.x, -m_fsize.y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[0]);
	Sprite::Draw();
}
