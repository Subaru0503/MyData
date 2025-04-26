#include "RoadUI.h"

#define RATIO (0.0001f)
Road::Road()
	: m_RoadUIPos(1150.0f, 660.0f, 0.0f)
	, m_RoadUISize(100.0f, 100.0f)
	, m_nMaxRatio(0)
	, m_fRadian(0.0f)
	, m_fRatio(1.0f)
	, m_TipsPos(640.0f, 360.0f, 0.0f)
	, m_nStageNum(0)
	, m_nFrame(0)
	, m_nSwitchFlg(0)
	, m_fAlpha(0.0f)
{
	for (int i = 0; i < 6; ++i)
	{
		m_pTexture[i] = new Texture();

	}
	if (FAILED(m_pTexture[0]->Create("Assets/Texture/ロード画面1.png"))) {
		MessageBox(NULL, "whiteFade.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[1]->Create("Assets/Texture/ロード画面2.png"))) {
		MessageBox(NULL, "whiteFade.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[2]->Create("Assets/Texture/ロード画面3.png"))) {
		MessageBox(NULL, "whiteFade.png", "Error", MB_OK);
	}
	//ロードUI
	if (FAILED(m_pTexture[3]->Create("Assets/Texture/ロード中.png"))) {
		MessageBox(NULL, "ロード中.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[4]->Create("Assets/Texture/ロード画面3-2.png"))) {
		MessageBox(NULL, "whiteFade.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[5]->Create("Assets/Texture/TIPS　背景.png"))) {
		MessageBox(NULL, "TIPS　背景.png", "Error", MB_OK);
	}


}

Road::~Road()
{
	for (int i = 0; i < 6; ++i)
	{
		SAFE_DELETE(m_pTexture[i]);
	}
}

void Road::Update(int StageNum)
{
	m_nStageNum = StageNum;
	if (!m_nMaxRatio)			// 最大倍率じゃなかったら
	{


		m_fRatio += RATIO;// 倍率設定（ボタン１）



		if (m_fRatio >= 1.2f)	// 最大倍率を超えたら
		{
			m_nMaxRatio ^= 1;	// フラグ上げ
		}


	}
	else
	{

		m_fRatio -= RATIO;// 倍率設定


		if (m_fRatio <= 0.8f)	// 最小倍率より小さくなったら
		{
			m_nMaxRatio ^= 1;	// フラグ上げ
		}

	}

	m_fRadian += 0.05f;

	if (m_nStageNum == 2)
	{
		if (!m_nSwitchFlg)
		{
			m_nFrame++;
			if (m_nFrame >= 7200)
			{
				m_nFrame = 7200;

				m_nSwitchFlg ^= 1;
			}
		}
		else
		{
			m_nFrame--;
			if (m_nFrame <= 0)
			{
				m_nFrame = 0;

				m_nSwitchFlg ^= 1;
			}
		}
	}





}

void Road::Draw()
{



	DirectX::XMFLOAT4X4 mat2[3];
	DirectX::XMMATRIX world2 = DirectX::XMMatrixTranslation(640.0f, 360.0f, 0.0f);
	DirectX::XMStoreFloat4x4(&mat2[0], DirectX::XMMatrixTranspose(world2));
	DirectX::XMStoreFloat4x4(&mat2[1], DirectX::XMMatrixIdentity());
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(
		0.0f, 1280.0f, 720.0f, 0.0f, 1.0f, 10.0f);
	DirectX::XMStoreFloat4x4(&mat2[2], DirectX::XMMatrixTranspose(proj));

	Sprite::SetWorld(mat2[0]);
	Sprite::SetView(mat2[1]);
	Sprite::SetProjection(mat2[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(1280.0f, -720.0f));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[5]);
	Sprite::Draw();

	switch (m_nStageNum)
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
	}


	if (m_nSwitchFlg)
	{
		Sprite::SetTexture(m_pTexture[4]);
		Sprite::Draw();
	}
	else
	{
		Sprite::Draw();
	}



	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_RoadUIPos.x, m_RoadUIPos.y, m_RoadUIPos.z);
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_fRadian));
	DirectX::XMMATRIX world = R * T;
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));
	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());
	/*DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(
		0.0f, 1280.0f, 720.0f, 0.0f, 1.0f, 10.0f);*/
	DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));

	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(m_RoadUISize.x * m_fRatio, -m_RoadUISize.y * m_fRatio));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[3]);
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::Draw();


}

void Road::SetRatio()
{
	m_nMaxRatio = 0;
	m_fRatio = 1.0f;
	m_fRadian = 0.0f;
}
