// ShopText[0].cpp

//----インクルード部----
#include "ShopText.h"

//----定数・マクロ定義----
#define TEXT_LEFT (0.0f)												// 画面左の座標
#define TEXT_RIGHT (1280.0f)												// 画面右の座標
#define TEXT_BOTTOM (720.0f)											// 画面下の座標
#define TEXT_TOP (0.0f)													// 画面上の座標
#define TEXT_NEAR (1.0f)												// カメラの見え始める距離
#define TEXT_FAR (10.0f)												// カメラの見える距離
#define TEXT_ANIM_SHOP_MENU_SPLIT_X	(1.0f / 19.0f)						//画像分割数（横）
#define SELECT_TEXT_ANIM_SHOP_MENU_SPLIT_X	(1.0f / 19.0f)				//画像分割数（横）(セレクトショップ)
#define TEXT_ANIM_SHOP_MENU_SPLIT_Y	(1.0f / 29.0f)						//画像分割数（縦）
#define SELECT_TEXT_ANIM_SHOP_MENU_SPLIT_Y	(1.0f / 23.0f)				//画像分割数（縦）(セレクトショップ)
//#define TEXT_ANIM_SHOP_MENU_SPLIT_Y2 (1.0f / 28.5f)						// 調整用
#define TEXT_RATIO (0.02f)												// テキストサイズ

CShopText::CShopText(int text, CSoundMng *sound)	// コンストラクタ
	: m_nLineNum(0)
	, m_nLineNumElement(0)
{
	m_nShopText = text;

	for (int i = 0; i < MAX_LINE; i++)
	{
		ShopText[i].pos = DirectX::XMFLOAT3(0.0f, 590.0f + i * 30.0f, 0.0f);	// 座標設定
		ShopText[i].size = DirectX::XMFLOAT2(0.0f, 60.0f);		// サイズ設定
		if (!m_nShopText)
		{
			ShopText[i].posTexCoord = DirectX::XMFLOAT2(0.0f, SELECT_TEXT_ANIM_SHOP_MENU_SPLIT_Y);	// テクスチャ座標設定
			ShopText[i].sizeTexCoord = DirectX::XMFLOAT2(SELECT_TEXT_ANIM_SHOP_MENU_SPLIT_X,
				SELECT_TEXT_ANIM_SHOP_MENU_SPLIT_Y);	// テクスチャサイズ設定
		}
		else
		{
			ShopText[i].posTexCoord = DirectX::XMFLOAT2(0.0f, TEXT_ANIM_SHOP_MENU_SPLIT_Y);	// テクスチャ座標設定
			ShopText[i].sizeTexCoord = DirectX::XMFLOAT2(TEXT_ANIM_SHOP_MENU_SPLIT_X,
				TEXT_ANIM_SHOP_MENU_SPLIT_Y);	// テクスチャサイズ設定
		}
		ShopText[i].frame = 0;										// アニメーション管理フレーム設定
		ShopText[i].currentAnimNo = -1;								// アニメーションコマ設定
		ShopText[i].textNo = 0;									// テキストナンバー設定
		ShopText[i].color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);	// カラー設定
		ShopText[i].pTexture = nullptr;							// テクスチャ初期化
	}
	m_pSoundMng = sound;
}

CShopText::~CShopText()	// デストラクタ
{
	for (int i = 0; i < MAX_LINE; i++)
	{
		if (ShopText[i].pTexture)
		{
			delete ShopText[i].pTexture;
			ShopText[i].pTexture = nullptr;
		}
	}
}

void CShopText::Update()	// 更新
{
	//---- アニメーション----
	//---- コマ計算----
	ShopText[m_nLineNumElement].posTexCoord.x = 0.0f;
	if (!m_nShopText)
	{
		ShopText[m_nLineNumElement].posTexCoord.y = SELECT_TEXT_ANIM_SHOP_MENU_SPLIT_Y * (float)(ShopText[m_nLineNumElement].textNo - 1);
		ShopText[m_nLineNumElement].sizeTexCoord.x = SELECT_TEXT_ANIM_SHOP_MENU_SPLIT_X * (float)ShopText[m_nLineNumElement].currentAnimNo;
	}
	else
	{
		ShopText[m_nLineNumElement].posTexCoord.y = TEXT_ANIM_SHOP_MENU_SPLIT_Y * (float)(ShopText[m_nLineNumElement].textNo - 1);
		ShopText[m_nLineNumElement].sizeTexCoord.x = TEXT_ANIM_SHOP_MENU_SPLIT_X * (float)ShopText[m_nLineNumElement].currentAnimNo;
	}
	ShopText[m_nLineNumElement].size.x = 28.0f * (float)ShopText[m_nLineNumElement].currentAnimNo;
	ShopText[m_nLineNumElement].pos.x = 715 + 14.0f * (float)ShopText[m_nLineNumElement].currentAnimNo;

	if (ShopText[m_nLineNumElement].frame >= 7)
	{
		ShopText[m_nLineNumElement].frame = 0;
		ShopText[m_nLineNumElement].currentAnimNo++;
		//m_pSoundMng->playSound(CSoundMng::ShopSE::text);//テキストse

	}

	// 文字が出きるまで(ゲーム内ショップ)
	if (m_nShopText && (ShopText[m_nLineNumElement].currentAnimNo < 19 || ShopText[m_nLineNumElement].textNo - 1 == 5))
	{
		ShopText[m_nLineNumElement].frame++;
	}
	// 文字ができるまで(セレクトショップ)
	else if (!m_nShopText && ShopText[m_nLineNumElement].currentAnimNo <= 18)
	{
		ShopText[m_nLineNumElement].frame++;
	}
	else if (!m_nShopText && (ShopText[m_nLineNumElement].textNo - 1 == 6 || ShopText[m_nLineNumElement].textNo - 1 == 9 || ShopText[m_nLineNumElement].textNo - 1 == 14))
	{
		ShopText[m_nLineNumElement].frame++;
	}
}

void CShopText::Draw()	// 描画
{
	for (int i = 0; i < MAX_LINE; i++)
	{
		// アニメーションコマ番号が0より小さいならつぎへ
		if (ShopText[i].currentAnimNo < 0) return;

		if (ShopText[i].textNo)
		{
			DirectX::XMFLOAT4X4 mat[3];	// 描画に必要な情報

			DirectX::XMMATRIX world;	// ワールド行列

			//ワールド行列はX,Yのみを考慮して作成
			world = DirectX::XMMatrixTranslation(ShopText[i].pos.x, ShopText[i].pos.y, ShopText[i].pos.z);
			DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));

			//ビュー行列は2dだとカメラの位置があまり関係ないので、単位行列を設定する
			DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());

			//プロジェクション行列は2dとして表示するための行列を設定する
			//この行列で2dスクリーンの大きさが決まる
			DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(TEXT_LEFT, TEXT_RIGHT, TEXT_BOTTOM,
				TEXT_TOP, TEXT_NEAR, TEXT_FAR);
			DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));

			Sprite::SetWorld(mat[0]);											// ワールドセット
			Sprite::SetView(mat[1]);											// ビューセット
			Sprite::SetProjection(mat[2]);										// プロジェクションセット
			Sprite::SetSize(DirectX::XMFLOAT2(ShopText[i].size.x,					// サイズセット
				-ShopText[i].size.y));
			Sprite::SetUVPos(DirectX::XMFLOAT2(ShopText[i].posTexCoord.x,			// UV座標セット
				ShopText[i].posTexCoord.y));
			Sprite::SetUVScale(DirectX::XMFLOAT2(ShopText[i].sizeTexCoord.x,		// UVサイズセット
				ShopText[i].sizeTexCoord.y));
			Sprite::SetColor(DirectX::XMFLOAT4(ShopText[i].color));				// カラーセット
			Sprite::SetTexture(ShopText[0].pTexture);								// テクスチャセット
			Sprite::Draw();
		}
	}
}

void CShopText::SetSize(float sizex, float sizey)
{
	for (int i = 0; i < 3; i++)
	{
		ShopText[i].size.x = sizex * TEXT_RATIO;	// サイズ設定
		ShopText[i].size.y = sizey * TEXT_RATIO;	// サイズ設定
	}
}

void CShopText::SetColor(float r, float g, float b, float a)
{
	for (int i = 0; i < 3; i++)
	{
		ShopText[i].color.x = r;
		ShopText[i].color.y = g;
		ShopText[i].color.z = b;
		ShopText[i].color.w = a;
	}
}

void CShopText::SetTextNo(int next, int element, int line)				// テキストナンバーセット
{
	m_nLineNum = line;	// 何行目か格納
	m_nLineNumElement = element - 1;	// 何行目か格納(配列用)
	ShopText[element - 1].textNo = next;
	ShopText[element - 1].currentAnimNo = 0;
	if (element == 1)
	{
		ShopText[1].currentAnimNo = -1;
		ShopText[2].currentAnimNo = -1;
	}
}

CShopText::ST_SHOP_TEXT_PARAM* CShopText::GetText()
{
	return &ShopText[0];
}

void CShopText::SetSound(CSoundMng * sound)
{
	m_pSoundMng = sound;
}

int CShopText::GetTextNo(int No)
{
	return ShopText[No - 1].textNo;
}

int CShopText::GetAnimeNo(int No)
{
	return ShopText[No - 1].currentAnimNo;
}

int CShopText::GetLineNum()
{
	return m_nLineNum;
}
