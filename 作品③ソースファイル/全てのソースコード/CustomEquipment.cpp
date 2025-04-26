// CustomEquipment.cpp

//----インクルード部----
#include "CustomEquipment.h"
#include "Shop.h"

//----定数・マクロ定義----
#define AnimeNo (MAX_CUSTOM)	// コマ番号

CCustomEquipment::CCustomEquipment()	// コンストラクタ
	: m_Left(0.0f)
	, m_Right((float)SCREEN_WIDTH)
	, m_Bottom((float)SCREEN_HEIGHT)
	, m_Top(0.0f)
	, m_near(1.0f)
	, m_far(10.0f)
	, m_pTexture(nullptr)
	, m_pos{{0.0f, 0.0f, 0.0f},{0.0f, 0.0f, 0.0f} ,{0.0f, 0.0f, 0.0f} ,{0.0f, 0.0f, 0.0f} }
{
	m_basePosX = 260.0f;
	m_basePosY = 640.0f;

	//----テクスチャ確保----
	m_pTexture = new Texture();

	//----テクスチャ読み込み----
	if (FAILED(m_pTexture->Create("Assets/Texture/Custom.png")))
	{
		MessageBox(NULL, "CustomEquipment Custom.png", "Error", MB_OK);
	}

	//----設定----
	for (int i = 0; i < MAX_CUSTOM; ++i)
	{
		m_Custom[i].size = DirectX::XMFLOAT2(200.0f, 100.0f);
		m_Custom[i].pos = DirectX::XMFLOAT3(m_basePosX + i * 140.0f, m_basePosY, 0.0f);
		m_Custom[i].sizeTexCoord = DirectX::XMFLOAT2(1.0f / (float)ANIM_CUSTOM_EQUIPMENT_SPLIT_X,
			1.0f / (float)ANIM_CUSTOM_EQUIPMENT_SPLIT_Y);
		m_Custom[i].posTexCoord = DirectX::XMFLOAT2(0.0f,
			m_Custom[i].sizeTexCoord.y * (i % ANIM_CUSTOM_EQUIPMENT_SPLIT_Y));
		m_Custom[i].frame = 0;
		m_Custom[i].currentAnimNo = 0;
	}
}

CCustomEquipment::~CCustomEquipment()	// デストラクタ
{
	if (m_pTexture)
	{
		delete m_pTexture;
		m_pTexture = nullptr;
	}
}

void CCustomEquipment::Update()
{

}

void CCustomEquipment::Draw()
{
	DirectX::XMFLOAT4X4 mat[3][MAX_CUSTOM];

	DirectX::XMMATRIX world[MAX_CUSTOM];

	for (int i = 0; i < MAX_CUSTOM; ++i)
	{
		// 装備してなかったら次へ
		if (!m_nCustom[i]) continue;

		//----装備してたらUV座標調整----
		switch (m_nCustom[i])
		{
		case 1:	// レベル1
			m_Custom[i].posTexCoord.x = m_Custom[i].sizeTexCoord.x * (0 % ANIM_CUSTOM_EQUIPMENT_SPLIT_X);
			//m_pos[0] =  m_Custom[i].pos;
			break;
		case 2:	// レベル2
			m_Custom[i].posTexCoord.x = m_Custom[i].sizeTexCoord.x * (1 % ANIM_CUSTOM_EQUIPMENT_SPLIT_X);
			break;
		case 3:	// レベル3
			m_Custom[i].posTexCoord.x = m_Custom[i].sizeTexCoord.x * (2 % ANIM_CUSTOM_EQUIPMENT_SPLIT_X);

			break;
		}
		//ワールド行列はX,Yのみを考慮して作成

		world[i] = DirectX::XMMatrixTranslation(m_Custom[i].pos.x, m_Custom[i].pos.y, m_Custom[i].pos.z);
		DirectX::XMStoreFloat4x4(&mat[0][i], DirectX::XMMatrixTranspose(world[i]));

	}

	//ビュー行列は2dだとカメラの位置があまり関係ないので、単位行列を設定する
	DirectX::XMStoreFloat4x4(&mat[1][0], DirectX::XMMatrixIdentity());

	//プロジェクション行列は2dとして表示するための行列を設定する
	//この行列で2dスクリーンの大きさが決まる
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat[2][0], DirectX::XMMatrixTranspose(proj));

	//スプライトの設定
	for (int i = 0; i < MAX_CUSTOM; i++)
	{
		//----装備してなかったら次へ----
		if (m_nCustom[i] == 0) continue;

		Sprite::SetWorld(mat[0][i]);
		Sprite::SetView(mat[1][0]);
		Sprite::SetProjection(mat[2][0]);
		Sprite::SetSize(DirectX::XMFLOAT2(m_Custom[i].size.x, -m_Custom[i].size.y));
		Sprite::SetUVPos(DirectX::XMFLOAT2(m_Custom[i].posTexCoord.x, m_Custom[i].posTexCoord.y));
		Sprite::SetUVScale(DirectX::XMFLOAT2(m_Custom[i].sizeTexCoord.x, m_Custom[i].sizeTexCoord.y));
		Sprite::SetTexture(m_pTexture);
		Sprite::Draw();
	}

}

void CCustomEquipment::SetCustom(int * Custom)
{
	for (int i = 0; i < MAX_CUSTOM; i++)
	{
		m_nCustom[i] = Custom[i];
	}
}