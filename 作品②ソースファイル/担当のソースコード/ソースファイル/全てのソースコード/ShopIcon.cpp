// ShopIcon.cpp

//----インクルード部----
#include "ShopIcon.h"

CShopIcon::CShopIcon(float PosX, float PosY, float PosZ, int AnimNo, int Stage)	// コンストラクタ
{
	ShopIcon.pos = DirectX::XMFLOAT3(PosX, PosY, PosZ);		// 座標設定
	ShopIcon.size = DirectX::XMFLOAT2(150.0f, 300.0f);		// サイズ設定
	ShopIcon.Texturesize = DirectX::XMFLOAT2(150.0f, 300.0f);	// サイズ設定
	if (Stage != 0)
	{
		// テクスチャサイズ設定
		ShopIcon.sizeTexCoord = DirectX::XMFLOAT2((1.0f / (float)ICON_ANIM_SHOP_MENU_SPLIT_X),
			(1.0f / (float)ICON_ANIM_SHOP_MENU_SPLIT_Y));
		// テクスチャ座標設定
		ShopIcon.posTexCoord = DirectX::XMFLOAT2(ShopIcon.sizeTexCoord.x * (AnimNo % ICON_ANIM_SHOP_MENU_SPLIT_X),
			ShopIcon.sizeTexCoord.y * (AnimNo / ICON_ANIM_SHOP_MENU_SPLIT_X));
	}
	else
	{
		// テクスチャサイズ設定
		ShopIcon.sizeTexCoord = DirectX::XMFLOAT2((1.0f / (float)ICON_ANIM_SHOP_MENU_SPLIT_X),
			(1.0f / (float)SELECT_ICON_ANIM_SHOP_MENU_SPLIT_Y));
		// テクスチャ座標設定
		ShopIcon.posTexCoord = DirectX::XMFLOAT2(ShopIcon.sizeTexCoord.x * (AnimNo % ICON_ANIM_SHOP_MENU_SPLIT_X),
			ShopIcon.sizeTexCoord.y * (AnimNo / ICON_ANIM_SHOP_MENU_SPLIT_X));
	}
	ShopIcon.color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	ShopIcon.pTexture = nullptr;							// テクスチャ初期化
}

CShopIcon::~CShopIcon()	// デストラクタ
{
	if (ShopIcon.pTexture)
	{
		delete ShopIcon.pTexture;
		ShopIcon.pTexture = nullptr;
	}
}

void CShopIcon::Update()	// 更新
{

}

void CShopIcon::Draw()	// 描画
{
	DirectX::XMFLOAT4X4 mat[3];	// 描画に必要な情報

	DirectX::XMMATRIX world;	// ワールド行列

	//ワールド行列はX,Yのみを考慮して作成
	world = DirectX::XMMatrixTranslation(ShopIcon.pos.x, ShopIcon.pos.y, ShopIcon.pos.z);
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));

	//ビュー行列は2dだとカメラの位置があまり関係ないので、単位行列を設定する
	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());

	//プロジェクション行列は2dとして表示するための行列を設定する
	//この行列で2dスクリーンの大きさが決まる
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(ICON_LEFT, ICON_RIGHT, ICON_BOTTOM,
		ICON_TOP, ICON_NEAR, ICON_FAR);
	DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));

	Sprite::SetWorld(mat[0]);											// ワールドセット
	Sprite::SetView(mat[1]);											// ビューセット
	Sprite::SetProjection(mat[2]);										// プロジェクションセット
	Sprite::SetSize(DirectX::XMFLOAT2(ShopIcon.size.x,					// サイズセット
		-ShopIcon.size.y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(ShopIcon.posTexCoord.x,			// UV座標セット
		ShopIcon.posTexCoord.y));
	Sprite::SetUVScale(DirectX::XMFLOAT2(ShopIcon.sizeTexCoord.x,		// UVサイズセット
		ShopIcon.sizeTexCoord.y));
	Sprite::SetColor(DirectX::XMFLOAT4(ShopIcon.color));				// カラーセット
	Sprite::SetTexture(ShopIcon.pTexture);								// テクスチャセット
	Sprite::Draw();
}

void CShopIcon::SetPos(float PosX, float PosY)
{
	ShopIcon.pos.x = PosX;
	ShopIcon.pos.y = PosY;
}

void CShopIcon::SetSizeRatio(float ratio)
{
	ShopIcon.size.x = ShopIcon.Texturesize.x * ratio;	// サイズ設定
	ShopIcon.size.y = ShopIcon.Texturesize.y * ratio;	// サイズ設定
}

void CShopIcon::SetSize(float sizex, float sizey)
{
	ShopIcon.size.x = ShopIcon.Texturesize.x = sizex;	// サイズ設定
	ShopIcon.size.y = ShopIcon.Texturesize.y = sizey;	// サイズ設定
}

void CShopIcon::ResetSize()
{
	ShopIcon.size.x = ShopIcon.Texturesize.x;	// サイズ設定 
	ShopIcon.size.y = ShopIcon.Texturesize.y;	// サイズ設定 
}

void CShopIcon::SetTexCoord(float Pos, float Size)
{
	// テクスチャサイズ設定
	ShopIcon.posTexCoord = DirectX::XMFLOAT2(Pos, Pos);
	ShopIcon.sizeTexCoord = DirectX::XMFLOAT2(Size, Size);
}

void CShopIcon::SetColor(float r, float g, float b, float a)
{
	ShopIcon.color.x = r;
	ShopIcon.color.y = g;
	ShopIcon.color.z = b;
	ShopIcon.color.w = a;
}

CShopIcon::ST_SHOP_ICON_PARAM* CShopIcon::GetIcon()
{
	return &ShopIcon;
}
