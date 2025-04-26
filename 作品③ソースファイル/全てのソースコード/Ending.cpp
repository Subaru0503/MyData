#include "Ending.h"
#include "Input.h"


#define CHANGE_ANIME (3)
Ending::Ending()
	: m_Left(0.0f)
	, m_Right((float)SCREEN_WIDTH)
	, m_Bottom((float)SCREEN_HEIGHT)
	, m_Top(0.0f)
	, m_near(1.0f)
	, m_far(10.0f)
	, m_pTexture{ nullptr, nullptr, nullptr, nullptr }
	, m_basePosX((float)SCREEN_WIDTH / 2)
	, m_basePosY((float)SCREEN_HEIGHT / 2)
	, m_animeNo(0)
	, m_frame(0)
	, m_totalFrame(0)
	, m_bEndAnime(false)
	, m_nTexNo(0)
{
	for (int i = 0; i < 4; ++i)
	{
		m_pTexture[i] = new Texture();
	}
	if (FAILED(m_pTexture[0]->Create("Assets/Texture/ED1.jpg")))
	{
		MessageBox(NULL, "ED1", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[1]->Create("Assets/Texture/ED2.jpg")))
	{
		MessageBox(NULL, "ED2", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[2]->Create("Assets/Texture/ED3.jpg")))
	{
		MessageBox(NULL, "ED3", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[3]->Create("Assets/Texture/ED4.jpg")))
	{
		MessageBox(NULL, "ED4", "Error", MB_OK);
	}
}

Ending::~Ending()
{
	for (int i = 0; i < 4; ++i)
	{
		SAFE_DELETE(m_pTexture[i]);
	}
}

void Ending::Update()
{
	m_uvSize.x = 1.0f / 5.0f;
	m_uvSize.y = 1.0f / 20.0f;
	XInputGetState(0, &state);
	XInputGetKeystroke(0, 0, &stroke);

	m_frame++;

	if (IsKeyTrigger(VK_SPACE) 
		|| state.Gamepad.wButtons&XINPUT_GAMEPAD_START&&stroke.Flags == 0x0001)
	{
		m_nTexNo = 3;
		m_animeNo = 99;
	}


	if (m_animeNo < 99)
	{
		if (m_frame >= CHANGE_ANIME)
		{
			m_frame = 0;
			m_animeNo++;
		}
	}
	else
	{
		if (m_nTexNo < 3)
		{
			m_frame = 0;
			m_animeNo = 0;
			m_nTexNo++;
		}

	}

	m_uvPos.x = (m_animeNo % 5) / 5.0f;
	m_uvPos.y = (m_animeNo / 5) / 20.0f;

	/*float totalTime = 6.0f;
	float totalFrame = totalTime * 60.0f;
	float rate = m_totalFrame / totalFrame;
	m_totalFrame;*/

	if (m_nTexNo >= 3 && m_animeNo >= 99)
	{
		m_bEndAnime = true;
	}





}

void Ending::Draw()
{

	switch (m_nTexNo)
	{
	case 0:
		Sprite::SetTexture(m_pTexture[0]);
		break;
	case 1:
		Sprite::SetTexture(m_pTexture[1]);
		break;
	case 2:
		Sprite::SetTexture(m_pTexture[2]);
		break;
	case 3:
		Sprite::SetTexture(m_pTexture[3]);
		break;
	default:
		break;
	}

	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMMATRIX world;

	world = DirectX::XMMatrixTranslation(m_basePosX, m_basePosY, 0.0f);
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));

	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());

	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));

	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::SetSize(DirectX::XMFLOAT2(1280.0f, -720.0f));
	Sprite::SetUVPos(DirectX::XMFLOAT2(m_uvPos.x, m_uvPos.y));
	Sprite::SetUVScale(DirectX::XMFLOAT2(m_uvSize.x, m_uvSize.y));
	//Sprite::SetTexture(m_pTexture);
	Sprite::Draw();
}

bool Ending::IsEndAnime()
{
	return m_bEndAnime;
}
