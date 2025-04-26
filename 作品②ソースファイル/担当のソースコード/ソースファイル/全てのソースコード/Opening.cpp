#include "Opening.h"
#include "Input.h"

#define CHANGE_ANIME (3)

Opening::Opening()
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
	for (int i = 0; i < 6; ++i)
	{
		m_pTexture[i] = new Texture();
	}
	if (FAILED(m_pTexture[0]->Create("Assets/Texture/OP1.jpg")))
	{
		MessageBox(NULL, "OP1", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[1]->Create("Assets/Texture/OP2.jpg")))
	{
		MessageBox(NULL, "OP2", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[2]->Create("Assets/Texture/OP3.jpg")))
	{
		MessageBox(NULL, "OP3", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[3]->Create("Assets/Texture/OP4.jpg")))
	{
		MessageBox(NULL, "OP4", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[4]->Create("Assets/Texture/OP5.jpg")))
	{
		MessageBox(NULL, "OP5", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[5]->Create("Assets/Texture/OP6.jpg")))
	{
		MessageBox(NULL, "OP6", "Error", MB_OK);
	}
}

Opening::~Opening()
{
	for (int i = 0; i < 6; ++i)
	{
		SAFE_DELETE(m_pTexture[i]);
	}
}

void Opening::Update()
{
	
	


	XInputGetState(0, &state);
	XInputGetKeystroke(0, 0, &stroke);
		m_frame++;
	
	

	//入力判定（スキップ）
	if (IsKeyTrigger(VK_SPACE) 
		|| state.Gamepad.wButtons&XINPUT_GAMEPAD_START&&stroke.Flags == 0x0001)
	{
		m_nTexNo = 5;
		m_animeNo = 28;
	}


	//アニメーション分割
	

	
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
			//最後のスプライトシート以外
			if (m_nTexNo < 5)
			{
				m_frame = 0;
				m_animeNo = 0;
				m_nTexNo++;
			}

		}
	
	
		

	//UV分割
	if (m_nTexNo != 5)
	{
		m_uvSize.x = 1.0f / 5.0f;
		m_uvSize.y = 1.0f / 20.0f;
		m_uvPos.x = (m_animeNo % 5) / 5.0f;
		m_uvPos.y = (m_animeNo / 5) / 20.0f;
	}
	else
	{
		m_uvSize.x = 1.0f / 5.0f;
		m_uvSize.y = 1.0f / 6.0f;
		m_uvPos.x = (m_animeNo % 5) / 5.0f;
		m_uvPos.y = (m_animeNo / 5) / 6.0f;
	}
	
	//アニメーション終了フラグ
	if (m_nTexNo >= 5 && m_animeNo >= 28)
	{
		m_animeNo = 28;
		m_bEndAnime = true;
	}
}

void Opening::Draw()
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
	case 4:
		Sprite::SetTexture(m_pTexture[4]);
		break;
	case 5:
		Sprite::SetTexture(m_pTexture[5]);
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
	Sprite::SetSize(DirectX::XMFLOAT2(1280.0f, -720.0f));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::SetUVPos(DirectX::XMFLOAT2(m_uvPos.x, m_uvPos.y));
	Sprite::SetUVScale(DirectX::XMFLOAT2(m_uvSize.x, m_uvSize.y));
	//Sprite::SetTexture(m_pTexture);
	Sprite::Draw();
}

bool Opening::IsEndAnime()
{
	return m_bEndAnime;
}
