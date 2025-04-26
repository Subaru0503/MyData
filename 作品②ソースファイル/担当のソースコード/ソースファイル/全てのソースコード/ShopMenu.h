// ShopMenu.h

//----インクルードガード----
#ifndef ___SHOP_MENU_H___
#define ___SHOP_MENU_H___

//----インクルード部----
#include <DirectXMath.h>
#include "Value.h"
#include "Sprite.h"
#include "Texture.h"
#include "ShopIcon.h"
#include "ShopText.h"
#include "Shop.h"
#include "Price.h"
#include "Suction.h"
#include "XController.h"
#include "SoundManager.h"
#include "UI.h"

//----定数・マクロ定義----
#define MAX_BASE_SHOP_MENU (8)										// ショップ画面ベーステクスチャの最大数
#define LEFT_ICON_POSX (222.5f)										// ショップの左上の座標X
#define LEFT_ICON_POSY (260.0f)										// ショップの左上の座標Y
#define ICON_WIDTHX (260.0f)										// アイコンとアイコンの幅X
#define ICON_WIDTHY (210.0f)										// アイコンとアイコンの幅Y
#define LEFT_PRICE_POSX (174.5f)									// お金の左上の座標X
#define LEFT_PRICE_POSY (331.0f)									// お金の左上の座標Y
#define PRICE_WIDTHX (283.0f)										// アイコンとアイコンの幅X
#define PRICE_WIDTHY (210.0f)										// アイコンとアイコンの幅Y

//----クラス定義----
class CShopMenu
{

public:
	typedef struct
	{
		DirectX::XMFLOAT3 pos;										// 中心座標
		DirectX::XMFLOAT2 size;										// 横縦サイズ
		DirectX::XMFLOAT2 posTexCoord;								// テクスチャ座標（左上）
		DirectX::XMFLOAT2 sizeTexCoord;								// テクスチャサイズ（右下）
		Texture* pTexture;											// テクスチャ
	}ST_SHOP_MENU_PARAM;											// ショップの画面を管理するパラメータの構造体

public:
	CShopMenu(int scene, CUI* ui,CSoundMng *sound);									// コンストラクタ
	~CShopMenu();													// デストラクタ
	void Update(float tick);													// 更新
	void Draw();													// 描画
	void Animetion(float tick);												// アニメーション関数
	void LineSet();													// セリフセット
	void MoneyEnough();												// お金が足りているか判定を取る
	void IconDraw();												// カスタムアイコン描画
	void PageSetDraw();												// ページ描画
	void ALLCoupon();												// 今セットされてる全てのカスタムパーツの値段表示に適用
	void OneCoupon(int element);									// 指定された一つのカスタムパーツの値段表示に適用
	bool GetShop();													// 購入画面を終わるフラグ
	void SetMoney(int* Money);										// 所持金セット
	void SetCustom(int* Custom);									// 所持カスタマイズパーツセット
	void SetItem(int* Item);										// アイテム使用格納変数セット
	void SetShopSuction(Suction* pSuction);							// 吸い込みクラスセット
	void SetItemUse(int coupon);									// アイテムが使用されたか
	CShop* GetShopCustom();

private:
	//----アイテム使用確認用----
	int m_nCoupon;		// クーポンフラグ
	int m_nFirst;		// 最初のメニューに適用されたか
	//----情報格納----
	ST_SHOP_MENU_PARAM m_BaseShopMenu[MAX_BASE_SHOP_MENU];			// ベースショップメニュー
	int m_nMaxCustom;												// ステージごとのカスタム最大数
	int m_nStage;													// ステージ
	CShopIcon* m_pShopIcon[MAX_CUSTOM * 6];							// アイコンクラス
	CShopIcon::ST_SHOP_ICON_PARAM* pShopIcon[MAX_CUSTOM * 6];		// アイコンパラメータ格納用変数
	CShopText* m_pShopText;								// パーツ説明文章クラス
	CShopText::ST_SHOP_TEXT_PARAM* pShopText;			// パーツ説明文章パラメータ格納用変数
	bool m_bShop;													// 購入画面を終わるフラグ
	int m_nShopCustom[MAX_CUSTOM];									// 購入画面にあるカスタマイズパーツの情報
	CPrice* m_pPrice[MAX_CUSTOM];									// 価格クラス
	//----他クラスの情報----
	int* m_pnMoney;													// 所持金
	int* m_pnCustom;												// 所持カスタマイズパーツ
	int* m_pnItem;													// 使用アイテム
	CShop* m_pShop;													// ショップ機能クラス
	//----処理判定用----
	DirectX::XMFLOAT2 m_anPricePos[MAX_CUSTOM];						// 価格座標退避用
	int m_nCursor;													// カーソルの座標判定
	int m_noldCursor;												// カーソルの前座標判定
	int m_nTotalPage;												// 全何ページか
	int m_nPage;													// 現在のページ
	int m_nBuy;														// 買ったフラグ
	int m_anBuy[MAX_CUSTOM];										// 購入済みフラグ
	int m_anBuyCustom;												// 購入したカスタム情報格納用
	int m_nLines;													// セリフを言い切ったか
	int m_nMove;													// カーソルを動かした
	int m_nNozzle;													// ノズルを強化したか
	int m_nEnough[MAX_CUSTOM];										// お金が足りているフラグ
	//----アニメーション用----
	float m_time;													// アニメーション用の経過秒数
	int m_nOpenAnimetion;											// ショップを開いた時のアニメーションフラグ
	float m_fAnimeMoveX;											// アニメーション用移動量X
	int m_nAnimeMoved;												// 動いたフラグ
	int m_nFrame;													// フレームカウント用変数
	float m_fRatio;													// 倍率
	int m_nMAXRatio;												// 最大倍率フラグ
	float m_fSizeRatio[MAX_CUSTOM];									// サイズ拡縮
	int m_naMinRatio[MAX_CUSTOM];									// 最低倍率フラグ	
	//----音----
	CSoundMng* m_pSoundMng;
	bool m_SoundOne;
};


#endif // ___SHOP_MENU_H___

