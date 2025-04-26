#include "Result_Window.h"

#define RATIO (0.005f)

ResultWindow::ResultWindow()
	: m_Left(0.0f)
	, m_Right((float)SCREEN_WIDTH)
	, m_Bottom((float)SCREEN_HEIGHT)
	, m_Top(0.0f)
	, m_near(1.0f)
	, m_far(10.0f)
	, m_pTexture{ nullptr, nullptr, nullptr }
	, m_WindowPos(0.0f, 0.0f)
	, m_WindowSize(0.0f, 0.0f)
	, m_ButtonPos{ {0.0f, 0.0f}, {0.0f, 0.0f} }
	, m_ButtonSize{ {0.0f, 0.0f}, {0.0f, 0.0f} }
	, m_ButtonPosTexCoord{ {0.0f, 0.0f}, {0.0f, 0.0f} }
	, m_nCorsor(0)
	, m_ButtonIconPos(0.0f, 0.0f)
	, m_ButtonIconSize(0.0f, 0.0f)
	, m_nMAXRatio(0)
	, m_fRatio0(1.0f)
{
	for (int i = 0; i < 4; ++i)
	{
		m_pTexture[i] = new Texture();
	}
	if (FAILED(m_pTexture[0]->Create("Assets/Texture/Result_Window.png")))
	{
		MessageBox(NULL, "ResultWindow Result_Window.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[1]->Create("Assets/Texture/Result_Button1.png")))
	{
		MessageBox(NULL, "ResultWindow Result_Button1.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[2]->Create("Assets/Texture/Result_Button2.png")))
	{
		MessageBox(NULL, "ResultWindow Result_Button2.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[3]->Create("Assets/Texture/Result_ButtonIcon.png")))
	{
		MessageBox(NULL, "ResultWindow Result_ButtonIcon.png", "Error", MB_OK);
	}

	m_WindowPos = DirectX::XMFLOAT2(960.0f, 580.0f);
	m_WindowSize = DirectX::XMFLOAT2(m_pTexture[0]->GetWidth() * 0.8f, m_pTexture[0]->GetHeight()* 0.8f);
	m_ButtonPos[0] = DirectX::XMFLOAT2(960.0f, 580.0f);
	m_ButtonPos[1] = DirectX::XMFLOAT2(960.0f, 580.0f);
	m_ButtonSize[0] = DirectX::XMFLOAT2(m_pTexture[1]->GetWidth() * 0.8f, m_pTexture[1]->GetHeight() / 2.0f * 0.8f);
	m_ButtonSize[1] = DirectX::XMFLOAT2(m_pTexture[2]->GetWidth() * 0.8f, m_pTexture[2]->GetHeight() / 2.0f * 0.8f);
	m_ButtonIconSize = DirectX::XMFLOAT2(m_pTexture[3]->GetWidth() * 0.8f, m_pTexture[3]->GetHeight() * 0.8f);
}

ResultWindow::~ResultWindow()
{

	for (int i = 0; i < 4; ++i)
	{
		delete m_pTexture[i];
		m_pTexture[i] = nullptr;
	}
}

void ResultWindow::Update()
{
	if (!m_nMAXRatio)			// 最大倍率じゃなかったら
	{


		m_fRatio0 += RATIO;// 倍率設定（ボタン１）



		if (m_nCorsor == 0 && m_fRatio0 >= 1.05f)	// 最大倍率を超えたら
		{
			m_nMAXRatio ^= 1;	// フラグ上げ
		}
		if (m_nCorsor == 1 && m_fRatio0 >= 1.05f)	// 最大倍率を超えたら
		{
			m_nMAXRatio ^= 1;	// フラグ上げ
		}

	}
	else
	{
		if (m_nCorsor == 0)
		{
			m_fRatio0 -= RATIO;// 倍率設定
		}
		else if (m_nCorsor == 1)
		{
			m_fRatio0 -= RATIO;
		}

		if (m_nCorsor == 0 && m_fRatio0 <= 0.95f)	// 最小倍率より小さくなったら
		{
			m_nMAXRatio ^= 1;	// フラグ上げ
		}
		if (m_nCorsor == 1 && m_fRatio0 <= 0.95f)	// 最小倍率より小さくなったら
		{
			m_nMAXRatio ^= 1;	// フラグ上げ
		}
	}





	if (m_nCorsor == 0)
	{
		m_ButtonPosTexCoord[0] = DirectX::XMFLOAT2(0.0f, 0.5f);
		m_ButtonPosTexCoord[1] = DirectX::XMFLOAT2(0.0f, 0.0f);
		m_ButtonIconPos = DirectX::XMFLOAT2(960.0f, 550.0f);
	}
	else
	{
		m_ButtonPosTexCoord[0] = DirectX::XMFLOAT2(0.0f, 0.0f);
		m_ButtonPosTexCoord[1] = DirectX::XMFLOAT2(0.0f, 0.5f);
		m_ButtonIconPos = DirectX::XMFLOAT2(960.0f, 620.0f);
	}
}

void ResultWindow::Draw()
{
	//ウィンドウ描画
	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMMATRIX world;

	world = DirectX::XMMatrixTranslation(m_WindowPos.x, m_WindowPos.y, 0.0f);
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));

	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());

	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));

	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(m_WindowSize.x, -m_WindowSize.y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[0]);
	Sprite::Draw();

	//ボタン1（セレクト）描画
	DirectX::XMFLOAT4X4 mat2[3];
	DirectX::XMMATRIX world2;

	world2 = DirectX::XMMatrixTranslation(m_ButtonPos[0].x, m_ButtonPos[0].y, 0.0f);
	DirectX::XMStoreFloat4x4(&mat2[0], DirectX::XMMatrixTranspose(world2));

	DirectX::XMStoreFloat4x4(&mat2[1], DirectX::XMMatrixIdentity());


	DirectX::XMStoreFloat4x4(&mat2[2], DirectX::XMMatrixTranspose(proj));

	Sprite::SetWorld(mat2[0]);
	Sprite::SetView(mat2[1]);
	Sprite::SetProjection(mat2[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(m_ButtonSize[0].x, -m_ButtonSize[0].y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(m_ButtonPosTexCoord[0].x, m_ButtonPosTexCoord[0].y));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 0.5f));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[1]);
	Sprite::Draw();

	//ボタン2（リスタート）描画
	DirectX::XMFLOAT4X4 mat3[3];
	DirectX::XMMATRIX world3;

	world3 = DirectX::XMMatrixTranslation(m_ButtonPos[1].x, m_ButtonPos[1].y, 0.0f);;
	DirectX::XMStoreFloat4x4(&mat3[0], DirectX::XMMatrixTranspose(world3));

	DirectX::XMStoreFloat4x4(&mat3[1], DirectX::XMMatrixIdentity());


	DirectX::XMStoreFloat4x4(&mat3[2], DirectX::XMMatrixTranspose(proj));

	Sprite::SetWorld(mat3[0]);
	Sprite::SetView(mat3[1]);
	Sprite::SetProjection(mat3[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(m_ButtonSize[1].x, -m_ButtonSize[1].y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(m_ButtonPosTexCoord[1].x, m_ButtonPosTexCoord[1].y));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 0.5f));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[2]);
	Sprite::Draw();

	//
	DirectX::XMFLOAT4X4 mat4[3];
	DirectX::XMMATRIX world4;

	world4 = DirectX::XMMatrixTranslation(m_ButtonIconPos.x, m_ButtonIconPos.y, 0.0f);;
	DirectX::XMStoreFloat4x4(&mat4[0], DirectX::XMMatrixTranspose(world4));

	DirectX::XMStoreFloat4x4(&mat4[1], DirectX::XMMatrixIdentity());


	DirectX::XMStoreFloat4x4(&mat4[2], DirectX::XMMatrixTranspose(proj));

	Sprite::SetWorld(mat4[0]);
	Sprite::SetView(mat4[1]);
	Sprite::SetProjection(mat4[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(m_ButtonIconSize.x * m_fRatio0, -m_ButtonIconSize.y * m_fRatio0));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[3]);
	Sprite::Draw();
}

void ResultWindow::SetSelect()
{
	m_nCorsor ^= 1;
}

void ResultWindow::SetRestart()
{
	m_nCorsor ^= 1;
}
