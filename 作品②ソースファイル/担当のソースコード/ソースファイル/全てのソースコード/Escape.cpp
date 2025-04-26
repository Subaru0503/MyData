#include "Escape.h"
#include "Input.h"
#include "XController.h"

#define RATIO (0.005f)
#define RATIO2 (0.005f)

EscapeUI::EscapeUI()
	: m_Left(0.0f)
	, m_Right((float)SCREEN_WIDTH)
	, m_Bottom((float)SCREEN_HEIGHT)
	, m_Top(0.0f)
	, m_near(1.0f)
	, m_far(10.0f)
	, m_pTexture{ nullptr, nullptr, nullptr, nullptr }
	, m_WindowPos(0.0f, 0.0f)
	, m_WindowSize(0.0f, 0.0f)
	, m_ButtonPos{ {0.0f, 0.0f}, {0.0f, 0.0f} }
	, m_ButtonSize{ {0.0f, 0.0f}, {0.0f, 0.0f} }
	, m_EscapeBGPos((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2)
	, m_EscapeBGSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT)
	, m_nCorsor(0)
	, m_nMAXRatio(1)
	, m_nMAXRatio2(0)
	, m_fRatio0(1.0f)
	, m_fRatio1(1.0f)
	, m_fRatio2(1.0f)
	, m_ButtonPosTexCoord{ {0.0f, 0.0f}, {0.0f, 0.0f} }
	, m_bIsEscape(false)
	, m_bRatio(false)
	, m_nCnt(0)
	, m_nCnt2(0)
{
	for (int i = 0; i < 4; ++i)
	{
		m_pTexture[i] = new Texture();
	}
	if (FAILED(m_pTexture[0]->Create("Assets/Texture/Shop_BG.png")))
	{
		MessageBox(NULL, "Escape Shop_BG.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[1]->Create("Assets/Texture/Escape_Window.png")))
	{
		MessageBox(NULL, "Escape Escape_Window.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[2]->Create("Assets/Texture/Escape_Button1.png")))
	{
		MessageBox(NULL, "Escape Escape_Button1.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[3]->Create("Assets/Texture/Escape_Button2.png")))
	{
		MessageBox(NULL, "Escape Escape_Button2.png", "Error", MB_OK);
	}

	m_WindowPos = DirectX::XMFLOAT2((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2);
	//m_WindowSize = DirectX::XMFLOAT2((float)m_pTexture[1]->GetWidth(), /*(float)m_pTexture[1]->GetHeight()*/ 0.0f);
	m_ButtonPos[0] = DirectX::XMFLOAT2(450.0f, 400.0f);
	m_ButtonPos[1] = DirectX::XMFLOAT2(930.0f, 400.0f);
	/*m_ButtonSize[0] = DirectX::XMFLOAT2((float)m_pTexture[2]->GetWidth() / 2.0f * 0.7f, (float)m_pTexture[2]->GetHeight()* 0.7f);
	m_ButtonSize[1] = DirectX::XMFLOAT2((float)m_pTexture[3]->GetWidth() / 2.0f * 0.7f, (float)m_pTexture[3]->GetHeight()* 0.7f);*/
	m_fBSTemp[0] = DirectX::XMFLOAT2((float)m_pTexture[2]->GetWidth() / 2.0f * 0.7f, (float)m_pTexture[2]->GetHeight()* 0.7f);
	m_fBSTemp[1] = DirectX::XMFLOAT2((float)m_pTexture[3]->GetWidth() / 2.0f * 0.7f, (float)m_pTexture[3]->GetHeight()* 0.7f);
}

EscapeUI::~EscapeUI()
{
	for (int i = 0; i < 4; ++i)
	{
		delete m_pTexture[i];
		m_pTexture[i] = nullptr;
	}
}

void EscapeUI::Update()
{
	XINPUT_STATE state;
	XInputGetState(0, &state);
	if (m_nCorsor == 0)
	{
		m_ButtonPosTexCoord[0] = DirectX::XMFLOAT2(0.5f, 0.0f);
		m_ButtonPosTexCoord[1] = DirectX::XMFLOAT2(0.0f, 0.0f);
	}
	else
	{
		m_ButtonPosTexCoord[0] = DirectX::XMFLOAT2(0.0f, 0.0f);
		m_ButtonPosTexCoord[1] = DirectX::XMFLOAT2(0.5f, 0.0f);
	}

	if (IsKeyTrigger(VK_ESCAPE) || state.Gamepad.wButtons&XINPUT_GAMEPAD_START)
	{
		m_bIsEscape = true;
	}

	if (m_bIsEscape)
	{



		m_ButtonSize[0].x += m_fBSTemp[0].x / 13.0f;
		m_ButtonSize[0].y += m_fBSTemp[0].y / 13.0f;
		m_ButtonSize[1].x += m_fBSTemp[1].x / 13.0f;
		m_ButtonSize[1].y += m_fBSTemp[1].y / 13.0f;
		m_WindowSize.x += 1280.0f / 13.0f;

		m_WindowSize.y += 720.0f / 13.0f;
		if (m_WindowSize.x >= 1280.0f)
		{
			m_ButtonSize[0] = DirectX::XMFLOAT2(m_fBSTemp[0].x, m_fBSTemp[0].y);
			m_ButtonSize[1] = DirectX::XMFLOAT2(m_fBSTemp[1].x, m_fBSTemp[1].y);
			m_WindowSize.x = 1280.0f;
			m_WindowSize.y = 720.0f;
			m_bIsEscape = false;


		}






	}

	//ウィンドウ
	if (!m_nMAXRatio2 && m_WindowSize.x >= 1280.0f && !m_bRatio && !m_bIsEscape)
	{

		m_fRatio2 += RATIO2;
		if (m_fRatio2 >= 1.05f)
		{

			m_nMAXRatio2 ^= 1;


		}
	}
	else if (m_nMAXRatio2 && m_WindowSize.x >= 1280.0f && !m_bRatio && !m_bIsEscape)
	{


		m_fRatio2 -= RATIO2 * 1.2f;
		if (m_fRatio2 <= 1.0f)
		{
			m_bRatio = true;
			m_nMAXRatio2 ^= 1;
		}



	}


	//ボタン
	if (!m_nMAXRatio)			// 最大倍率じゃなかったら
	{
		if (m_nCorsor == 0) m_fRatio0 += RATIO;// 倍率設定（ボタン１）
		else
		{
			m_fRatio1 += RATIO;// 倍率設定（ボタン2）
		}

		if (m_nCorsor == 0 && m_fRatio0 >= 1.05f)	// 最大倍率を超えたら
		{
			m_nMAXRatio ^= 1;	// フラグ上げ
		}
		if (m_nCorsor == 1 && m_fRatio1 >= 1.05f)	// 最大倍率を超えたら
		{
			m_nMAXRatio ^= 1;	// フラグ上げ
		}
	}
	else
	{
		if (m_nCorsor == 0) m_fRatio0 -= RATIO;// 倍率設定
		else
		{
			m_fRatio1 -= RATIO;
		}

		if (m_nCorsor == 0 && m_fRatio0 <= 0.95f)	// 最小倍率より小さくなったら
		{
			m_nMAXRatio ^= 1;	// フラグ上げ
		}
		if (m_nCorsor == 1 && m_fRatio1 <= 0.95f)	// 最小倍率より小さくなったら
		{
			m_nMAXRatio ^= 1;	// フラグ上げ
		}
	}

	





}

void EscapeUI::Draw()
{
	//BG描画
	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMMATRIX world;

	world = DirectX::XMMatrixTranslation(m_EscapeBGPos.x, m_EscapeBGPos.y, 0.0f);
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));

	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());

	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));

	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(m_EscapeBGSize.x, -m_EscapeBGSize.y));
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
	Sprite::SetSize(DirectX::XMFLOAT2(m_WindowSize.x * m_fRatio2, -m_WindowSize.y * m_fRatio2));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[1]);
	Sprite::Draw();

	//ボタン１描画
	DirectX::XMFLOAT4X4 mat3[3];
	DirectX::XMMATRIX world3;

	world3 = DirectX::XMMatrixTranslation(m_ButtonPos[0].x, m_ButtonPos[0].y, 0.0f);
	DirectX::XMStoreFloat4x4(&mat3[0], DirectX::XMMatrixTranspose(world3));

	DirectX::XMStoreFloat4x4(&mat3[1], DirectX::XMMatrixIdentity());


	DirectX::XMStoreFloat4x4(&mat3[2], DirectX::XMMatrixTranspose(proj));

	Sprite::SetWorld(mat3[0]);
	Sprite::SetView(mat3[1]);
	Sprite::SetProjection(mat3[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(m_ButtonSize[0].x * m_fRatio0, -m_ButtonSize[0].y* m_fRatio0));
	Sprite::SetUVPos(DirectX::XMFLOAT2(m_ButtonPosTexCoord[0].x, m_ButtonPosTexCoord[0].y));
	Sprite::SetUVScale(DirectX::XMFLOAT2(0.5f, 1.0f));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[2]);
	Sprite::Draw();

	//ボタン2描画
	DirectX::XMFLOAT4X4 mat4[3];
	DirectX::XMMATRIX world4;

	world4 = DirectX::XMMatrixTranslation(m_ButtonPos[1].x, m_ButtonPos[1].y, 0.0f);
	DirectX::XMStoreFloat4x4(&mat4[0], DirectX::XMMatrixTranspose(world4));

	DirectX::XMStoreFloat4x4(&mat4[1], DirectX::XMMatrixIdentity());


	DirectX::XMStoreFloat4x4(&mat4[2], DirectX::XMMatrixTranspose(proj));

	Sprite::SetWorld(mat4[0]);
	Sprite::SetView(mat4[1]);
	Sprite::SetProjection(mat4[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(m_ButtonSize[1].x * m_fRatio1, -m_ButtonSize[1].y * m_fRatio1));
	Sprite::SetUVPos(DirectX::XMFLOAT2(m_ButtonPosTexCoord[1].x, m_ButtonPosTexCoord[1].y));
	Sprite::SetUVScale(DirectX::XMFLOAT2(0.5f, 1.0f));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[3]);
	Sprite::Draw();
}

void EscapeUI::SetYes()
{
	m_fRatio0 = 1.0f;
	m_fRatio1 = 1.0f;
	m_nCorsor ^= 1;			//カーソル変数を0に
}

void EscapeUI::SetNo()
{
	m_fRatio0 = 1.0f;
	m_fRatio1 = 1.0f;
	m_nCorsor ^= 1;			//カーソル変数を1に

}

void EscapeUI::SetWindowAnime()
{
	m_WindowSize = DirectX::XMFLOAT2(0.0f, 0.0f);
	m_ButtonSize[0] = DirectX::XMFLOAT2(0.0f, 0.0f);
	m_ButtonSize[1] = DirectX::XMFLOAT2(0.0f, 0.0f);

	m_fRatio2 = 1.0f;
	m_nMAXRatio2 = 0;
	m_bRatio = false;


}