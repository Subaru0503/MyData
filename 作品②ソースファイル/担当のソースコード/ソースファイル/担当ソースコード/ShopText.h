// ShopText.h

//----インクルードガード----
#ifndef ___SHOP_TEXT_H___
#define ___SHOP_TEXT_H___

//----インクルード部----
#include <DirectXMath.h>
#include "Defines.h"
#include "Sprite.h"
#include "Texture.h"
#include "SoundManager.h"

#define MAX_LINE (3)	// 表示最大行数

//----クラス定義----
class CShopText
{

public:
	typedef struct
	{
		DirectX::XMFLOAT3 pos;										// 中心座標
		DirectX::XMFLOAT2 size;										// 横縦サイズ
		DirectX::XMFLOAT2 posTexCoord;								// テクスチャ座標（左上）
		DirectX::XMFLOAT2 sizeTexCoord;								// テクスチャサイズ（右下）
		int	frame;													// アニメーション管理フレーム
		int	currentAnimNo;											// アニメーションコマ番号（左上から０～）
		int textNo;													// テキストコマ番号
		DirectX::XMFLOAT4 color;									// カラー
		Texture* pTexture;											// テクスチャ
	}ST_SHOP_TEXT_PARAM;											// ショップの画面を管理するパラメータの構造体

public:
	CShopText(int text, CSoundMng *sound);													// コンストラクタ
	~CShopText();													// デストラクタ
	void Update();													// 更新
	void Draw();													// 描画
	void SetSize(float sizex, float sizey);							// サイズセット
	void SetColor(float r, float g, float b, float a);				// カラー設定
	void SetTextNo(int next, int element, int line);				// テキストナンバーセット
	ST_SHOP_TEXT_PARAM* GetText();									// アイコンパラメータゲット関数
	void SetSound(CSoundMng* sound);

	int GetTextNo(int No);											// テキストコマ番号入手
	int GetAnimeNo(int No);											// アニメーションコマ番号入手
	int GetLineNum();												// 行数情報入手
private:
	ST_SHOP_TEXT_PARAM ShopText[3];
	CSoundMng* m_pSoundMng;

	// テキスト判定用
	int m_nShopText;												// テキストフラグ
	int m_nLineNum;													// 何行目か格納する変数
	int m_nLineNumElement;											// 配列の要素指定用
};


#endif // ___SHOP_TEXT_H___

