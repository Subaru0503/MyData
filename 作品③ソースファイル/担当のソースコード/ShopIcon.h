// ShopIcon.h

//----インクルードガード----
#ifndef ___SHOP_ICON_H___
#define ___SHOP_ICON_H___

//----インクルード部----
#include <DirectXMath.h>
#include "Defines.h"
#include "Sprite.h"
#include "Texture.h"

//----定数・マクロ定義----
#define ICON_LEFT (0.0f)												// 画面左の座標
#define ICON_RIGHT (1280.0f)												// 画面右の座標
#define ICON_BOTTOM (720.0f)											// 画面下の座標
#define ICON_TOP (0.0f)													// 画面上の座標
#define ICON_NEAR (1.0f)												// カメラの見え始める距離
#define ICON_FAR (10.0f)												// カメラの見える距離
//#define ICON_ANIM_SHOP_MENU_FRAME	(2)									//アニメーション一コマフレーム数
#define ICON_ANIM_SHOP_MENU_SPLIT_X	(3)									//画像分割数（横）
#define ICON_ANIM_SHOP_MENU_SPLIT_Y	(6)									//画像分割数（縦）
#define SELECT_ICON_ANIM_SHOP_MENU_SPLIT_Y (4)							//画像分割数（縦）

//----クラス定義----
class CShopIcon
{

public:
	typedef struct
	{
		DirectX::XMFLOAT3 pos;										// 中心座標
		DirectX::XMFLOAT2 size;										// 横縦サイズ
		DirectX::XMFLOAT2 Texturesize;										// 横縦サイズ
		DirectX::XMFLOAT2 posTexCoord;								// テクスチャ座標（左上）
		DirectX::XMFLOAT2 sizeTexCoord;								// テクスチャサイズ（右下）
		DirectX::XMFLOAT4 color;									// カラー
		Texture* pTexture;											// テクスチャ
	}ST_SHOP_ICON_PARAM;											// ショップの画面を管理するパラメータの構造体

public:
	CShopIcon(float PosX, float PosY, float PosZ, int AnimNo, int Stage);		// コンストラクタ
	~CShopIcon();													// デストラクタ
	void Update();													// 更新
	void Draw();													// 描画
	void SetPos(float PosX, float PosY);							// 座標セット
	void SetSizeRatio(float ratio);									// サイズ倍率セット
	void SetSize(float sizex, float sizey);							// サイズセット
	void ResetSize();												// サイズリセット
	void SetTexCoord(float Pos, float Size);						// テクスチャ設定
	void SetColor(float r, float g, float b, float a);				// カラー設定
	ST_SHOP_ICON_PARAM* GetIcon();									// アイコンパラメータゲット関数

private:
	ST_SHOP_ICON_PARAM ShopIcon;
};


#endif // ___SHOP_ICON_H___

