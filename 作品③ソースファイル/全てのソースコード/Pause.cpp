#include "Pause.h"

#define RATIO (0.005f)

Pause::Pause()
	: m_Left(0.0f)
	, m_Right((float)SCREEN_WIDTH)
	, m_Bottom((float)SCREEN_HEIGHT)
	, m_Top(0.0f)
	, m_near(1.0f)
	, m_far(10.0f)
	, m_pTexture{ nullptr, nullptr, nullptr, nullptr , nullptr, nullptr }
	, m_WindowPos(0.0f, 0.0f)
	, m_WindowSize(0.0f, 0.0f)
	, m_ButtonPos{ {0.0f, 0.0f}, {0.0f, 0.0f} ,{0.0f, 0.0f} }
	, m_ButtonSize{ {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f,0.0f} }
	, m_BGPos((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2)
	, m_BGSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT)
	, m_ButtonPosTexCoord{ {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f} }
	, m_nCorsor(0)
	, m_nMAXRatio(0)
	, m_fRatio0(1.0f)
	, m_fRatio1(1.0f)
	, m_fRatio2(1.0f)
	, m_ButtonIconPos(0.0f, 0.0f)
	, m_ButtonIconSize(0.0f, 0.0f)
{
	for (int i = 0; i < 6; ++i)
	{
		m_pTexture[i] = new Texture();
	}

	if (FAILED(m_pTexture[0]->Create("Assets/Texture/Shop_BG.png")))
	{
		MessageBox(NULL, "Escape Shop_BG.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[1]->Create("Assets/Texture/Pause_Window2.png")))
	{
		MessageBox(NULL, "Escape Pause_Window.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[2]->Create("Assets/Texture/Pause_BackButton.png")))
	{
		MessageBox(NULL, "Escape Pause_BackButton.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[3]->Create("Assets/Texture/Pause_RestartButton.png")))
	{
		MessageBox(NULL, "Escape Pause_RestartButton.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[4]->Create("Assets/Texture/Pause_SelectButton.png")))
	{
		MessageBox(NULL, "Escape Pause_SelectButton.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[5]->Create("Assets/Texture/Pause_BackButtonIcon.png")))
	{
		MessageBox(NULL, "Escape Pause_SelectButtonIcon.png", "Error", MB_OK);
	}

	m_WindowPos = DirectX::XMFLOAT2((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2);
	m_WindowSize = DirectX::XMFLOAT2((float)m_pTexture[1]->GetWidth(), (float)m_pTexture[1]->GetHeight());

	for (int i = 0; i < 3; ++i)
	{
		m_ButtonPos[i] = DirectX::XMFLOAT2((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2);
		m_ButtonSize[i] = DirectX::XMFLOAT2((float)m_pTexture[i + 2]->GetWidth() * 0.5f, (float)m_pTexture[i + 2]->GetHeight());
	}
	m_ButtonIconSize = DirectX::XMFLOAT2(m_pTexture[5]->GetWidth(), m_pTexture[5]->GetHeight());


}

Pause::~Pause()
{
	for (int i = 0; i < 6; ++i)
	{
		SAFE_DELETE(m_pTexture[i]);
	}

}

void Pause::Update(int select)
{
	m_nCorsor = select;

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
		if (m_nCorsor == 2 && m_fRatio0 >= 1.05f)	// 最大倍率を超えたら
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
		else if (m_nCorsor == 2)
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
		if (m_nCorsor == 2 && m_fRatio0 <= 0.95f)	// 最小倍率より小さくなったら
		{
			m_nMAXRatio ^= 1;	// フラグ上げ
		}
	}



	if (m_nCorsor == 0)
	{
		m_ButtonPosTexCoord[0] = DirectX::XMFLOAT2(0.5f, 0.0f);
		m_ButtonPosTexCoord[1] = DirectX::XMFLOAT2(0.0f, 0.0f);
		m_ButtonPosTexCoord[2] = DirectX::XMFLOAT2(0.0f, 0.0f);
		m_ButtonIconPos = DirectX::XMFLOAT2(640.0f, 250.0f);
	}
	else if (m_nCorsor == 1)
	{
		m_ButtonPosTexCoord[1] = DirectX::XMFLOAT2(0.5f, 0.0f);
		m_ButtonPosTexCoord[0] = DirectX::XMFLOAT2(0.0f, 0.0f);
		m_ButtonPosTexCoord[2] = DirectX::XMFLOAT2(0.0f, 0.0f);
		m_ButtonIconPos = DirectX::XMFLOAT2(640.0f, 420.0f);
	}
	else if (m_nCorsor == 2)
	{
		m_ButtonPosTexCoord[2] = DirectX::XMFLOAT2(0.5f, 0.0f);
		m_ButtonPosTexCoord[1] = DirectX::XMFLOAT2(0.0f, 0.0f);
		m_ButtonPosTexCoord[0] = DirectX::XMFLOAT2(0.0f, 0.0f);
		m_ButtonIconPos = DirectX::XMFLOAT2(640.0f, 580.0f);
	}
}

void Pause::Draw()
{
	//BG描画
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
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 0.8f));
	Sprite::SetTexture(m_pTexture[0]);
	Sprite::Draw();


	//ウィンドウ描画
	DirectX::XMFLOAT4X4 mat2[3];
	DirectX::XMMATRIX world2;

	world2 = DirectX::XMMatrixTranslation(m_WindowPos.x, m_WindowPos.y, 0.0f);
	DirectX::XMStoreFloat4x4(&mat2[0], DirectX::XMMatrixTranspose(world2));

	DirectX::XMStoreFloat4x4(&mat2[1], DirectX::XMMatrixIdentity());


	DirectX::XMStoreFloat4x4(&mat2[2], DirectX::XMMatrixTranspose(proj));

	Sprite::SetWorld(mat2[0]);
	Sprite::SetView(mat2[1]);
	Sprite::SetProjection(mat2[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(m_WindowSize.x, -m_WindowSize.y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[1]);
	Sprite::Draw();

	//戻るボタン描画
	DirectX::XMFLOAT4X4 mat3[3];
	DirectX::XMMATRIX world3;

	world3 = DirectX::XMMatrixTranslation(m_ButtonPos[0].x, m_ButtonPos[0].y, 0.0f);
	DirectX::XMStoreFloat4x4(&mat3[0], DirectX::XMMatrixTranspose(world3));

	DirectX::XMStoreFloat4x4(&mat3[1], DirectX::XMMatrixIdentity());


	DirectX::XMStoreFloat4x4(&mat3[2], DirectX::XMMatrixTranspose(proj));

	Sprite::SetWorld(mat3[0]);
	Sprite::SetView(mat3[1]);
	Sprite::SetProjection(mat3[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(m_ButtonSize[0].x, -m_ButtonSize[0].y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(m_ButtonPosTexCoord[0].x, m_ButtonPosTexCoord[0].y));
	Sprite::SetUVScale(DirectX::XMFLOAT2(0.5f, 1.0f));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[2]);
	Sprite::Draw();

	//リスタートボタン描画
	DirectX::XMFLOAT4X4 mat4[3];
	DirectX::XMMATRIX world4;

	world4 = DirectX::XMMatrixTranslation(m_ButtonPos[1].x, m_ButtonPos[1].y, 0.0f);
	DirectX::XMStoreFloat4x4(&mat4[0], DirectX::XMMatrixTranspose(world4));

	DirectX::XMStoreFloat4x4(&mat4[1], DirectX::XMMatrixIdentity());


	DirectX::XMStoreFloat4x4(&mat4[2], DirectX::XMMatrixTranspose(proj));

	Sprite::SetWorld(mat4[0]);
	Sprite::SetView(mat4[1]);
	Sprite::SetProjection(mat4[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(m_ButtonSize[1].x, -m_ButtonSize[1].y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(m_ButtonPosTexCoord[1].x, m_ButtonPosTexCoord[1].y));
	Sprite::SetUVScale(DirectX::XMFLOAT2(0.5f, 1.0f));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[3]);
	Sprite::Draw();

	//最初から描画
	DirectX::XMFLOAT4X4 mat5[3];
	DirectX::XMMATRIX world5;

	world5 = DirectX::XMMatrixTranslation(m_ButtonPos[2].x, m_ButtonPos[2].y, 0.0f);
	DirectX::XMStoreFloat4x4(&mat5[0], DirectX::XMMatrixTranspose(world5));

	DirectX::XMStoreFloat4x4(&mat5[1], DirectX::XMMatrixIdentity());


	DirectX::XMStoreFloat4x4(&mat5[2], DirectX::XMMatrixTranspose(proj));

	Sprite::SetWorld(mat5[0]);
	Sprite::SetView(mat5[1]);
	Sprite::SetProjection(mat5[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(m_ButtonSize[2].x, -m_ButtonSize[2].y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(m_ButtonPosTexCoord[2].x, m_ButtonPosTexCoord[2].y));
	Sprite::SetUVScale(DirectX::XMFLOAT2(0.5f, 1.0f));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[4]);
	Sprite::Draw();

	//ボタンアイコンから描画
	DirectX::XMFLOAT4X4 mat6[3];
	DirectX::XMMATRIX world6;

	world6 = DirectX::XMMatrixTranslation(m_ButtonIconPos.x, m_ButtonIconPos.y, 0.0f);
	DirectX::XMStoreFloat4x4(&mat6[0], DirectX::XMMatrixTranspose(world6));

	DirectX::XMStoreFloat4x4(&mat6[1], DirectX::XMMatrixIdentity());


	DirectX::XMStoreFloat4x4(&mat6[2], DirectX::XMMatrixTranspose(proj));

	Sprite::SetWorld(mat6[0]);
	Sprite::SetView(mat6[1]);
	Sprite::SetProjection(mat6[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(m_ButtonIconSize.x * m_fRatio0, -m_ButtonIconSize.y * m_fRatio0));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[5]);
	Sprite::Draw();
}
