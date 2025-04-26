#// Shop.h

//----インクルードガード----
#ifndef __SHOP_H__
#define __SHOP_H__

//----インクルード部----
#include "UI.h"
#include "Suction.h"

//----マクロ定義----
//----カスタムアイコン----
#define MAX_LEVEL (3)
#define HAVE (1)
//----のこぎり----
#define PRICE_SAW_LEVEL1 (1500)		// のこぎりレベル1価格
#define PRICE_SAW_LEVEL2 (3000)		// のこぎりレベル2価格
#define PRICE_SAW_LEVEL3 (7000)	// のこぎりレベル3価格
//----ハンマー----
#define PRICE_HAMMER_LEVEL1 (1500)		// ハンマー価格
#define PRICE_HAMMER_LEVEL2 (3000)		// ハンマー価格
#define PRICE_HAMMER_LEVEL3 (7000)		// ハンマー価格
//----ドリル----
#define PRICE_DRILL_LEVEL1 (1500)		// ドリル価格
#define PRICE_DRILL_LEVEL2 (3000)		// ドリル価格
#define PRICE_DRILL_LEVEL3 (7000)		// ドリル価格
//----ブーツ----
#define PRICE_BOOTS (1500)		// ブーツ価格
//----ノズル----
#define PRICE_NOZZLE_LEVEL2 (8000)		// ノズルLv.2価格
#define PRICE_NOZZLE_LEVEL3 (12000)		// ノズルLv.3価格
//----耐熱----
#define PRICE_HEAT_RESISTANT (3000)	// 耐熱カスタム

//----お助けアイテム----
#define PRICE_DRINK (30000)			// スピードアップドリンク価格
#define PRICE_NOZZLE (30000)		// ノズル強化価格
#define PRICE_TIMER (50000)		// 時間延長価格
#define PRICE_COUPON (50000)		// ショップ割引券価格

// 列挙型
enum Custom
{
	//----のこぎり----
	SAW,		// のこぎり
	//----ハンマー----
	HAMMER,	// ハンマー
	//----ドリル----
	DRILL,	// ドリル
	//----ブーツ----
	BOOTS,			// ブーツ
	//----ノズル----
	GAME_NOZZLE,	// ノズル
	//----耐熱カスタム----
	HEAT_RESISTANT,	// 耐熱カスタム	
};

enum Item
{
	ITEM_NONE,
	DRINK,			// スピードアップドリンク
	NOZZLE,			// ノズル強化
	TIMER,			// 時間延長
	COUPON,			// ショップ割引券
};

class CShop
{
public:
	CShop();	// コンストラクタ
	~CShop();	// デストラクタ
	void Buy(int* Custom, int* Money, int Cursor, int* Buy, int* Nozzle);	// カスタマイズパーツ購入
	void ItemBuy(int* Item, int* Money, int Cursor, int* Buy);	// アイテム購入
	void SetSuction(Suction* pSuction);							// 吸い込みクラスゲット
	void SetItem(float coupon);									// アイテムを使用しているか
	void SetUI(CUI* ui);										// 所持金データ取得
	void StockReduse();								// 在庫数調整
	bool* GetDrill();
	bool* GetSaw();
	bool* GetHammer();
private:
	int m_saw, m_hammer, m_drill, m_Boots, m_hose, m_Nozzle,	// パーツ在庫数
		m_nHeat;
	int m_drink, m_nozzle, m_timer, m_coupon;					// アイテム在庫数
	CUI* m_pUI_Money;											// お金UI
	Suction* m_pSuction;										// 吸い込み機能クラスポインタ

	//----アイテムが使用されたら----
	float m_fCoupon;// クーポン使用フラグ
	bool m_bDrill;
	bool m_bSaw;
	bool m_bHammer;
};

#endif	// _SHOP_H__