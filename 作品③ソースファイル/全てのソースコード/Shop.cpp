//----Shop.cpp----
//----インクルード部----
#include "Shop.h"
#include "Input.h"
#include "Value.h"
#include "XController.h"
#include "ObjectManager.h"
#include "SceneGame.h"

CShop::CShop()	// コンストラクタ
//----カスタムパーツ----
	: m_saw(3)		// のこぎり在庫数
	, m_hammer(3)	// ハンマー在庫数
	, m_drill(3)	// ドリル在庫数
	, m_Boots(1)	// ブーツ在庫数
	//, m_hose(1)		// ホース在庫数
	, m_Nozzle(2)	// ノズル在庫数
	, m_nHeat(1)	// 耐熱カスタム在庫数
//----アイテム----
	, m_drink(1)	// ドリンク在庫数
	, m_nozzle(1)	// ノズル強化在庫数
	, m_timer(1)	// 時間延長在庫数
	, m_coupon(1)	// クーポン在庫数
	, m_fCoupon(1.0f)
	, m_bDrill(false)
	, m_bSaw(false)
	, m_bHammer(false)
{
}

CShop::~CShop()	// デストラクタ
{

}

void CShop::Buy(int* Custom, int* Money, int Cursor, int* Buy, int* Nozzle)	// カスタマイズパーツ購入
{
	// のこぎり
	// 在庫数でレベルを判断
	if (Cursor == Custom::SAW && ((Custom[SAW] == 0 && *Money >= PRICE_SAW_LEVEL1 * m_fCoupon && m_saw == 3) ||
		(Custom[SAW] == 1 && *Money >= PRICE_SAW_LEVEL2 * m_fCoupon && m_saw == 2) ||
		(Custom[SAW] == 2 && *Money >= PRICE_SAW_LEVEL3 * m_fCoupon && m_saw == 1)))
	{
		switch (m_saw)
		{
		case 3:
			*Money -= (int)(PRICE_SAW_LEVEL1 * m_fCoupon);	// のこぎりレベル1の値段分引く
			m_saw = 2;							// 在庫数を減らす
			Custom[SAW] = 1;					// カスタムにセット
			m_pUI_Money->AddMoney
			(-PRICE_SAW_LEVEL1 * m_fCoupon);	// のこぎりレベル1の値段分引く
			*Buy = 1;							// 購入フラグ上げ
			m_bSaw = true;
			break;
		case 2:
			*Money -= (int)(PRICE_SAW_LEVEL2 * m_fCoupon);	// のこぎりレベル2の値段分引く
			m_saw = 1;							// 在庫数を減らす
			Custom[SAW] = 2;					// カスタムにセット
			m_pUI_Money->AddMoney
			(-PRICE_SAW_LEVEL2 * m_fCoupon);	// のこぎりレベル2の値段分引く
			*Buy = 1;							// 購入フラグ上げ
			break;
		case 1:
			*Money -= (int)(PRICE_SAW_LEVEL3 * m_fCoupon);	// のこぎりレベル3の値段分引く
			m_saw = 0;							// 在庫数を減らす
			Custom[SAW] = 3;					// カスタムにセット
			m_pUI_Money->AddMoney
			(-PRICE_SAW_LEVEL3 * m_fCoupon);	// のこぎりレベル3の値段分引く
			*Buy = 1;							// 購入フラグ上げ
			break;
		}
	}
	// ドリル
	// 在庫数でレベルを判断
	else if (Cursor == Custom::DRILL && ((Custom[DRILL] == 0 && *Money >= PRICE_DRILL_LEVEL1 * m_fCoupon && m_drill == 3) ||
		(Custom[DRILL] == 1 && *Money >= PRICE_DRILL_LEVEL2 * m_fCoupon && m_drill == 2) ||
		(Custom[DRILL] == 2 && *Money >= PRICE_DRILL_LEVEL3 * m_fCoupon && m_drill == 1)))
	{
		switch (m_drill)
		{
		case 3:
			*Money -= PRICE_DRILL_LEVEL1 * m_fCoupon;	// ドリルレベル1の値段分引く
			m_drill = 2;									// 在庫数を減らす
			Custom[DRILL] = 1;			// カスタムセット
			m_pUI_Money->AddMoney
			(-PRICE_DRILL_LEVEL1 * m_fCoupon);			// ドリルレベル1の値段分引く
			*Buy = 1;									// 購入フラグ上げ
			m_bDrill = true;
			break;
		case 2:
			*Money -= PRICE_DRILL_LEVEL2 * m_fCoupon;	// ドリルレベル2の値段分引く
			m_drill = 1;									// 在庫数を減らす
			Custom[DRILL] = 2;			// カスタムセット
			m_pUI_Money->AddMoney
			(-PRICE_DRILL_LEVEL2 * m_fCoupon);			// ドリルレベル2の値段分引く
			*Buy = 1;									// 購入フラグ上げ
			break;
		case 1:
			*Money -= PRICE_DRILL_LEVEL3 * m_fCoupon;	// ドリルレベル3の値段分引く
			m_drill = 0;									// 在庫数を減らす
			Custom[DRILL] = 3;			// カスタムセット
			m_pUI_Money->AddMoney
			(-PRICE_DRILL_LEVEL3 * m_fCoupon);			// ドリルレベル3の値段分引く
			*Buy = 1;									// 購入フラグ上げ
			break;
		}
		//break;
	}
	// ハンマー
	// 在庫数でレベルを判断
	else if ((Custom[HAMMER] == 0 || Custom[HAMMER] == 1 || Custom[HAMMER] == 2) &&
		Cursor == Custom::HAMMER && ((*Money >= PRICE_HAMMER_LEVEL1 * m_fCoupon && m_hammer == 3) ||
		(*Money >= PRICE_HAMMER_LEVEL2 * m_fCoupon && m_hammer == 2) ||
			(*Money >= PRICE_HAMMER_LEVEL3 * m_fCoupon && m_hammer == 1)))
	{
		switch (m_hammer)
		{
		case 3:
			*Money -= PRICE_HAMMER_LEVEL1 * m_fCoupon;	// ハンマーレベル1の値段分引く
			m_hammer = 2;									// 在庫数を減らす
			Custom[HAMMER] = 1;			// カスタムセット
			m_pUI_Money->AddMoney
			(-PRICE_HAMMER_LEVEL1 * m_fCoupon);			// ハンマーレベル1の値段分引く
			*Buy = 1;									// 購入フラグ上げ
			m_bHammer = true;
			break;
		case 2:
			*Money -= PRICE_HAMMER_LEVEL2 * m_fCoupon;	// ハンマーレベル2の値段分引く
			m_hammer = 1;									// 在庫数を減らす
			Custom[HAMMER] = 2;			// カスタムセット
			m_pUI_Money->AddMoney
			(-PRICE_HAMMER_LEVEL2 * m_fCoupon);			// ハンマーレベル2の値段分引く
			*Buy = 1;									// 購入フラグ上げ
			break;
		case 1:
			*Money -= PRICE_HAMMER_LEVEL3 * m_fCoupon;	// ハンマーレベル3の値段分引く
			m_hammer = 0;									// 在庫数を減らす
			Custom[HAMMER] = 3;			// カスタムセット
			m_pUI_Money->AddMoney
			(-PRICE_HAMMER_LEVEL3 * m_fCoupon);			// ハンマーレベル3の値段分引く
			*Buy = 1;									// 購入フラグ上げ
			break;
		}
		//break;
	}
	else if (Custom[BOOTS] == 0 && Cursor == Custom::BOOTS && *Money >= PRICE_BOOTS * m_fCoupon &&	// ブーツ
		m_Boots > 0)
	{
		*Money -= PRICE_BOOTS * m_fCoupon;		// ブーツの値段分引く
		m_Boots--;								// 在庫数を減らす
		Custom[BOOTS] = 1;				// カスタムセット
		m_pUI_Money->AddMoney
		(-PRICE_BOOTS * m_fCoupon);				// ブーツの値段分引く
		*Buy = 1;								// 購入フラグ上げ
		//break;
	}
	else if (Custom[HEAT_RESISTANT] == 0 && Cursor == Custom::HEAT_RESISTANT && *Money >= PRICE_HEAT_RESISTANT * m_fCoupon &&	// 耐熱カスタム
		m_nHeat > 0)
	{
		*Money -= PRICE_HEAT_RESISTANT * m_fCoupon;	// 耐熱カスタムの値段分引く
		m_nHeat--;									// 在庫数を減らす
		Custom[HEAT_RESISTANT] = 1;					// カスタムセット
		m_pUI_Money->AddMoney
		(-PRICE_HEAT_RESISTANT * m_fCoupon);		// 耐熱カスタムの値段分引く
		*Buy = 1;									// 購入フラグ上げ
	}
	else if ((Custom[GAME_NOZZLE] == 0 || Custom[GAME_NOZZLE] == 2) &&
		Cursor == Custom::GAME_NOZZLE && ((*Money >= PRICE_NOZZLE_LEVEL2 * m_fCoupon && m_Nozzle > 1) ||
		(*Money >= PRICE_NOZZLE_LEVEL3 * m_fCoupon && m_Nozzle > 0)))
	{
		switch (m_Nozzle)
		{
		case 2:
			*Money -= PRICE_NOZZLE_LEVEL2 * m_fCoupon;	// ノズルレベル2の値段分引く
			m_Nozzle--;									// 在庫数を減らす
			Custom[GAME_NOZZLE] = 2;					// カスタムセット
			m_pUI_Money->AddMoney
			(-PRICE_NOZZLE_LEVEL2 * m_fCoupon);			// ノズルレベル2の値段分引く
			m_pSuction->NozzleLevelUp();				// 吸い込みレベルアップ
			*Buy = 1;									// 購入フラグ上げ
			*Nozzle = 1;								// ノズル強化購入フラグ上げ
			break;
		case 1:
			*Money -= PRICE_NOZZLE_LEVEL3 * m_fCoupon;	// ノズルレベル2の値段分引く
			m_Nozzle--;									// 在庫数を減らす
			Custom[GAME_NOZZLE] = 3;							// カスタムセット
			m_pUI_Money->AddMoney
			(-PRICE_NOZZLE_LEVEL3 * m_fCoupon);			// ノズルレベル2の値段分引く
			m_pSuction->NozzleLevelUp();				// 吸い込みレベルアップ
			*Buy = 1;									// 購入フラグ上げ
			*Nozzle = 1;								// ノズル強化購入フラグ上げ
			break;
		}
	}
}

void CShop::ItemBuy(int* Item, int* Money, int Cursor, int* Buy)
{
	for (int i = 0; i < MAX_ITEM; i++)
	{
		if (Item[i] != 0) continue;
		if (Cursor == Item::DRINK && *Money >= PRICE_DRINK &&	// ドリンク
			/*Item[i] != Item::SAW &&*/ m_drink > 0)
		{
			*Money -= PRICE_DRINK;					// ドリンクの値段分引く
			m_drink--;								// 在庫数を減らす
			Item[0] = Item::DRINK;					// アイテム使用にセット
			m_pUI_Money->AddMoney(-PRICE_DRINK);	// ドリンクの値段分引く
			*Buy = 1;								// 購入フラグ上げ
			break;
		}
		else if (Cursor == Item::NOZZLE && *Money >= PRICE_NOZZLE &&	// ノズル強化
			m_nozzle > 0)
		{
			*Money -= PRICE_NOZZLE;					// ノズル強化の値段分引く
			m_nozzle--;								// 在庫数を減らす
			Item[1] = Item::NOZZLE;					// アイテム使用にセット
			m_pUI_Money->AddMoney(-PRICE_NOZZLE);	// ノズル強化の値段分引く
			*Buy = 1;								// 購入フラグ上げ
			break;
		}
		else if (Cursor == Item::TIMER && *Money >= PRICE_TIMER &&	// 時間延長
			m_timer > 0)
		{
			*Money -= PRICE_TIMER;					// 時間延長アイテムの値段分引く
			m_timer--;								// 在庫数を減らす
			Item[2] = Item::TIMER;					// アイテム使用にセット
			m_pUI_Money->AddMoney(-PRICE_TIMER);	// 時間延長アイテムの値段分引く
			*Buy = 1;								// 購入フラグ上げ
			break;
		}
		else if (Cursor == Item::COUPON && *Money >= PRICE_COUPON &&	// クーポン
			m_coupon > 0)
		{
			*Money -= PRICE_COUPON;					// クーポンの値段分引く
			m_coupon--;								// 在庫数を減らす
			Item[3] = Item::COUPON;					// アイテム使用にセット
			m_pUI_Money->AddMoney(-PRICE_COUPON);	// クーポンの値段分引く
			*Buy = 1;								// 購入フラグ上げ
			break;
		}
		break;
	}
}

void CShop::SetSuction(Suction * pSuction)							// 吸い込みクラスゲット
{
	m_pSuction = pSuction;
}

void CShop::SetItem(float coupon)									// アイテムを使用しているか
{
	m_fCoupon = coupon;
}

void CShop::SetUI(CUI * ui)
{
	m_pUI_Money = ui;
}

void CShop::StockReduse()											// 在庫数調整
{
	m_Nozzle--;
}

bool* CShop::GetDrill()
{
	return &m_bDrill;
}

bool* CShop::GetSaw()
{
	return &m_bSaw;
}

bool* CShop::GetHammer()
{
	return &m_bHammer;
}