// Price.h

//----インクルードガード----
#ifndef ___PRICE_H___
#define ___PRICE_H___

//----インクルード部----
#include <DirectXMath.h>
#include "Defines.h"
#include "Sprite.h"
#include "Texture.h"

//----定数・マクロ定義----
#define MAX_PRICE (6)
#define DIGIT_PRICE			(6)			// 価格の桁数（配列の数）
#define ANIM_PRICE_SPLIT_X	(4)			// 画像分割数（横）
#define ANIM_PRICE_SPLIT_Y	(3)			// 画像分割数（縦）

//----クラス定義----
class CPrice
{

public:
	typedef struct
	{

		DirectX::XMFLOAT3 pos;			// 中心座標
		DirectX::XMFLOAT2 size;			// 横縦サイズ
		DirectX::XMFLOAT2 posTexCoord;	// テクスチャ座標（左上）
		DirectX::XMFLOAT2 sizeTexCoord;	// テクスチャサイズ（右下）
		int		frame;					// アニメーション管理フレーム
		int		currentAnimNo;			// アニメーションコマ番号（左上から０～）
		DirectX::XMFLOAT4 color;									// カラー
	}ST_PRICE_PARAM;					// 価格を管理するパラメータの構造体

public:
	CPrice(float PosX, float PosY, float PosZ, int Price);					// コンストラクタ
	~CPrice();							// デストラクタ
	void Update();						// 更新
	void Draw();						// 数字描画
	void UpdatePricetexCoord();
	void SetColor(float r, float g, float b, float a);				// カラー設定
	int GetPrice();						// 価格情報ゲット関数
	void PriceSale(float sale);			// 価格割引

private:
	ST_PRICE_PARAM m_Price[DIGIT_PRICE];
	int m_nPrice;						// 価格
	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;
	Texture* m_pTexture[MAX_PRICE];



};


#endif									 // !___PRICE_H___

