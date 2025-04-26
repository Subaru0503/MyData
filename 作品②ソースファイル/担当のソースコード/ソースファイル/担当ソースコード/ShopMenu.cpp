// ShopMenu.cpp

//----インクルード部----
#include "ShopMenu.h"
#include "SceneGame.h"
#include "Input.h"
#include "EasingFunction.h"

//----定数・マクロ定義----
//----文章----
#define TEXT_ANIM_SHOP_MENU_NO	(19)								// アニメーションナンバー
#define SELECT_TEXT_ANIM_SHOP_MENU_NO	(18)						// アニメーションナンバー
#define ENTERING_LINE (1)											// 入店セリフ
#define FIRST_LINE (1)												// 1行目
#define SECOND_LINE (2)												// 2行目
#define THIRD_LINE (3)												// 3行目
#define FORCE_LINE (4)												// 4行目
//----共通シーン----
#define WINDOW_POSX (372.5f)										// ショップウィンドウ座標X
#define WINDOW_POSY (350.0f)										// ショップウィンドウ座標Y
#define WINDOW_START_POSY (-420.0f)									// ショップウィンドウ最初の座標Y
#define WINDOW_START_POSY (-420.0f)									// ショップウィンドウ最初の座標Y
#define MERCHANT_START_POSX (1700.0f)										// 商人の立ち絵座標X
#define MERCHANT_START_POSY (-450.0f)										// 商人の立ち絵座標X
#define MERCHANT_POSX (935.0f)										// 商人の立ち絵座標X
#define MERCHANT_POSY (323.0f)										// 商人の立ち絵座標Y
//#define Merchant_START_POSY (-130.0f)								// 文章枠最初の座標Y
#define LINE_FRAME_POSX (980.0f)									// 文章枠座標X
#define LINE_FRAME_POSY (624.0f)									// 文章枠座標Y
#define LINE_FRAME_START_POSY (-130.0f)								// 文章枠最初の座標Y
#define LINE_FRAME_START_POSX (1400.0f)								// 文章枠最初の座標Y
#define DOWN_ARROW_POSX (1225.0f)									// 下矢印座標X
#define DOWN_ARROW_POSY (665.0f)									// 下矢印座標Y
#define DOWN_ARROW_START_POSY (-80.0f)								// 下矢印最初の座標Y
#define RIGHT_ARROW_POSX (610.0f)									// 右向き矢印座標X
#define LEFT_ARROW_POSX (80.0f)										// 左向き矢印座標X
#define ARROW_POSY (370.0f)											// 矢印座標Y
//----セレクトシーン----
#define SELECT_LEFT_ICON_POSX (222.5f)										// ショップの左上の座標X
#define SELECT_LEFT_ICON_POSY (255.0f)										// ショップの左上の座標Y
#define SELECT_ICON_WIDTHX (260.0f)									// アイコンとアイコンの幅X
#define SELECT_ICON_WIDTHY (230.0f)									// アイコンとアイコンの幅Y
#define SELECT_ICON_SiZEX (245.0f)											// アイコンサイズX
#define SELECT_ICON_SiZEY (225.0f)											// アイコンサイズY
#define SELECT_SHOP (0)												// セレクトショップ
#define SELECT_ICON_KIND (3)										// セレクトシーンアイコンの種類
#define DRINK_KOMA_NO (0)											// ドリンクのコマ
#define SELECT_NOZZLE_KOMA_NO (3)									// ノズル強化のコマ
#define TIMER_KOMA_NO (6)											// タイマーのコマ
#define COUPON_KOMA_NO (9)											// クーポンのコマ
#define DRINK_LINE (6)												// ドリンクのセリフ
#define NOZZLE_STRONG_LINE (9)										// ノズル強化アイテムのセリフ
#define TIMER_LINE (12)												// 時間延長アイテムのセリフ
#define COUPON_LINE (14)											// クーポンアイテムのセリフ
#define SELECT_BUY_LINE (18)										// 購入
//----ゲームシーン----
#define ICON_SiZEX (245.0f)											// アイコンサイズX
#define ICON_SiZEY (235.0f)											// アイコンサイズY
#define GAME_SHOP (1)												// ゲーム内ショップ
#define ICON_KIND (5)												// アイコンの種類数
#define DRILL_KOMA_NO (9)											// ドリルのコマ
#define SAW_KOMA_NO (12)											// のこぎりのコマ
#define HAMMER_KOMA_NO (15)											// ハンマーのコマ
#define BOOTS_KOMA_NO (0)											// ブーツのコマ
#define NOZZLE_KOMA_NO (3)											// ノズルのコマ
#define HEAT_RESISTANT_KOMA_NO (6)									// 耐熱カスタムのコマ
#define SAW_LINE (11)												// のこぎりのセリフ
#define DRILL_LINE (5)												// ドリルのセリフ
#define HAMMER_LINE (8)												// ドリルのセリフ
#define NOZZLE_LINE (20)											// ノズルのセリフ
#define BOOTS_LINE (17)												// ブーツのセリフ
#define HEAT_RESISTANT_LINE (23)									// 耐火装置のセリフ
#define BUY_LINE (27)												// 購入のセリフ
#define BUY_CHECK_LINE (26)											// 購入確認のセリフ
//----分割----
#define PAGE_SPLIT_X (4)											// 横
#define PAGE_SPLIT_Y (4)											// 縦
//----アニメーション用----
#define ANIMETION_SECONDS (0.5f)									// 〇秒かけてアニメーション
#define DOWN_SPEED (30.0f)											// 降りてくるスピード
#define SHOP_RATIO (0.004f)											// 拡縮スピード
#define ENOUGH_MAX_RATIO (1.08f)									// 所持金が足りている時の最大倍率
#define NOT_ENOUGH_MAX_RATIO (1.04f)								// 所持金が足りていない時の最大倍率
#define ENOUGH_MIN_RATIO (0.92)									// 所持金が足りている時の最小倍率
#define NOT_ENOUGH_MIN_RATIO (0.96)								// 所持金が足りていない時の最小倍率
#define SIZE_RATIO (0.5f)											// サイズ調整用
#define ICON_RATIO (0.09f)											// アイコン倍率
#define SOLD_OUT_RATIO (0.7f)										// 売り切れアイコンの倍率

//----アイテム使用効果----
#define SHOP_COUPON (0.8f)											// 割引率

CShopMenu::CShopMenu(int scene, CUI* ui, CSoundMng *sound)	// コンストラクタ
	: m_pShopIcon{ nullptr }
	, pShopIcon{ nullptr }
	, m_pShopText{ nullptr }
	, m_bShop(true)
	, m_nShopCustom{ 0, 0, 0, 0, 0, 0 }
	, m_nCursor(1)
	, m_noldCursor(1)
	, m_pnMoney(nullptr)
	, m_pnCustom(nullptr)
	, m_pShop(nullptr)
	, m_pPrice{ nullptr }
	, m_nTotalPage(1)
	, m_nPage(1)
	, m_nBuy(0)
	, m_anBuy{ 0, 0, 0, 0, 0, 0, }
	, m_nLines(0)
	, m_nMove(0)
	, m_nNozzle(0)
	, m_fRatio(1.0f)
	, m_nMAXRatio(0)
	, m_fSizeRatio{ 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f }
	, m_naMinRatio{ 0, 0, 0, 0, 0, 0 }
	, m_nEnough{ 0 }
	, m_nCoupon(0)
	, m_nFirst(0)
	, m_nOpenAnimetion(1)
	, m_fAnimeMoveX(0.1f)
	, m_nAnimeMoved(0)
	, m_nFrame(0)
	, m_time(0.0f)
{
	m_pShop = new CShop();
	m_pShop->SetUI(ui);

	m_pSoundMng = sound;
	//----ベーステクスチャパラメータ設定----
	for (int i = 0; i < MAX_BASE_SHOP_MENU; i++)
	{
		m_BaseShopMenu[i].posTexCoord = DirectX::XMFLOAT2(0.0f, 0.0f);	// テクスチャ座標設定
		m_BaseShopMenu[i].sizeTexCoord = DirectX::XMFLOAT2(1.0f, 1.0f);	// テクスチャサイズ設定
		m_BaseShopMenu[i].pTexture = nullptr;							// テクスチャ初期化
	}

	//----ベーステクスチャを動的確保----
	for (int i = 0; i < MAX_BASE_SHOP_MENU; ++i)
	{
		m_BaseShopMenu[i].pTexture = new Texture();
	}

	//----ベーステクスチャ読み込み----
	//----商人の立ち絵----
	if (FAILED(m_BaseShopMenu[0].pTexture->Create("Assets/Texture/Merchant.png")))
	{
		MessageBox(NULL, "ShopMenu.cpp Merchant.png", "Error", MB_OK);
	}
	//----画面----
	if (FAILED(m_BaseShopMenu[1].pTexture->Create("Assets/Texture/ショップウィンドウ.png")))
	{
		MessageBox(NULL, "ShopMenu.cpp ショップウィンドウ.png", "Error", MB_OK);
	}
	//----文章枠----
	if (FAILED(m_BaseShopMenu[2].pTexture->Create("Assets/Texture/LineWindow.png")))
	{
		MessageBox(NULL, "ShopMenu.cpp LineWindow.png", "Error", MB_OK);
	}
	//----矢印----
	if (FAILED(m_BaseShopMenu[3].pTexture->Create("Assets/Texture/nikukyu.png")))
	{
		MessageBox(NULL, "ShopMenu.cpp nikukyu.png", "Error", MB_OK);
	}
	//----右矢印----
	if (FAILED(m_BaseShopMenu[4].pTexture->Create("Assets/Texture/Right.png")))
	{
		MessageBox(NULL, "ShopMenu.cpp Right.png", "Error", MB_OK);
	}
	//----数字----
	if (FAILED(m_BaseShopMenu[5].pTexture->Create("Assets/Texture/UI_number4.png")))
	{
		MessageBox(NULL, "ShopMenu.cpp UI_number4.png", "Error", MB_OK);
	}
	//----左矢印----
	if (FAILED(m_BaseShopMenu[6].pTexture->Create("Assets/Texture/Left.png")))
	{
		MessageBox(NULL, "ShopMenu.cpp Left.png", "Error", MB_OK);
	}
	//----商人の立ち絵----
	m_BaseShopMenu[0].size = DirectX::XMFLOAT2(m_BaseShopMenu[0].pTexture->GetWidth(),
		m_BaseShopMenu[0].pTexture->GetHeight());				// サイズ設定
	m_BaseShopMenu[0].pos = DirectX::XMFLOAT3(MERCHANT_POSX, MERCHANT_POSY, 0.0f);	// 座標設定

	//----画面----
	m_BaseShopMenu[1].size = DirectX::XMFLOAT2(m_BaseShopMenu[1].pTexture->GetWidth() * 0.625f
		, m_BaseShopMenu[1].pTexture->GetHeight() * 0.625f);			// サイズ設定
	m_BaseShopMenu[1].pos = DirectX::XMFLOAT3(WINDOW_POSX, WINDOW_START_POSY, 0.0f);	// 座標設定

	//----文章枠----
	m_BaseShopMenu[2].size = DirectX::XMFLOAT2(m_BaseShopMenu[2].pTexture->GetWidth() * 0.99f,
		m_BaseShopMenu[2].pTexture->GetHeight() * 0.99f);				// サイズ設定
	m_BaseShopMenu[2].pos = DirectX::XMFLOAT3(LINE_FRAME_POSX,LINE_FRAME_POSY, 0.0f);	// 座標設定

	//----下矢印----
	m_BaseShopMenu[3].size = DirectX::XMFLOAT2(m_BaseShopMenu[3].pTexture->GetWidth() * 0.2f
		, m_BaseShopMenu[3].pTexture->GetHeight() * 0.2f);
	m_BaseShopMenu[3].pos = DirectX::XMFLOAT3(DOWN_ARROW_POSX, DOWN_ARROW_START_POSY, 0.0f);

	//----スラッシュ---
	m_BaseShopMenu[5].size = DirectX::XMFLOAT2(m_BaseShopMenu[5].pTexture->GetWidth() * 0.12f,
		m_BaseShopMenu[5].pTexture->GetHeight() * 0.12f);
	m_BaseShopMenu[5].sizeTexCoord = DirectX::XMFLOAT2(1.0f / PAGE_SPLIT_X, 1.0f / PAGE_SPLIT_Y);	// テクスチャサイズ設定
	m_BaseShopMenu[5].posTexCoord = DirectX::XMFLOAT2(m_BaseShopMenu[5].sizeTexCoord.x * (13 % PAGE_SPLIT_X)
		, m_BaseShopMenu[5].sizeTexCoord.y * (13 / PAGE_SPLIT_X));	// テクスチャ座標設定

	m_nStage = scene;



	//----ステージごとのカスタム数だけ用意----
	switch (m_nStage)
	{
	case 0:
		// ステージ最大カスタム最大数代入
		m_nMaxCustom = 4;
		m_nTotalPage = 1;

		//----文章テクスチャを動的確保----
		m_pShopText = new CShopText(SELECT_SHOP, m_pSoundMng);
		pShopText = m_pShopText->GetText();	// パラメータ情報
		pShopText->pTexture = new Texture();
		//m_pShopText->SetSound(m_pSoundMng);

		//----文章テクスチャ読み込み----
		// テキスト
		if (FAILED(pShopText->pTexture->Create("Assets/Texture/SelectShopText.png")))
		{
			MessageBox(NULL, "ShopMenu.cpp SelectShopText.png", "Error", MB_OK);
		}
		m_pShopText->SetSize(pShopText->pTexture->GetWidth(), pShopText->pTexture->GetHeight());	// サイズ設定

		//----左上のアイコン----
		// ドリンク
		for (int i = 0; i < SELECT_ICON_KIND; i++)
		{
			// 通常、選択、アイコンの順に入力
			m_pShopIcon[i] = new CShopIcon(SELECT_LEFT_ICON_POSX, SELECT_LEFT_ICON_POSY, 0.0f, DRINK_KOMA_NO + i, m_nStage);
			pShopIcon[i] = m_pShopIcon[i]->GetIcon();												// パラメータ情報
			pShopIcon[i]->pTexture = new Texture();
			if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/セレクトアイテム.png")))	// カスタムアイコン
			{
				MessageBox(NULL, "ShopMenu.cpp セレクトアイテム.png", "Error", MB_OK);
			}
			m_pShopIcon[i]->SetSize(SELECT_ICON_SiZEX,			// サイズ設定
				SELECT_ICON_SiZEY);
		}

		m_nShopCustom[0] = Item::DRINK;													// ショップにあるアイテム情報
		m_pPrice[0] = new CPrice(LEFT_PRICE_POSX - 10.0f, LEFT_PRICE_POSY, 0.0f, PRICE_DRINK);// 価格情報

		//----右上のアイコン----
		//	ノズル強化
		for (int i = SELECT_ICON_KIND; i < SELECT_ICON_KIND * 2; i++)
		{
			// 通常、選択、アイコンの順に入力
			m_pShopIcon[i] = new CShopIcon(SELECT_LEFT_ICON_POSX + SELECT_ICON_WIDTHX,
				SELECT_LEFT_ICON_POSY, 0.0f, SELECT_NOZZLE_KOMA_NO + i - SELECT_ICON_KIND, m_nStage);
			pShopIcon[i] = m_pShopIcon[i]->GetIcon();									// パラメータ情報
			pShopIcon[i]->pTexture = new Texture();
			if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/セレクトアイテム.png")))	// カスタムアイコン
			{
				MessageBox(NULL, "ShopMenu.cpp セレクトアイテム.png", "Error", MB_OK);
			}
			m_pShopIcon[i]->SetSize(SELECT_ICON_SiZEX,			// サイズ設定
				SELECT_ICON_SiZEY);
		}
		m_nShopCustom[1] = Item::NOZZLE;														// ショップにあるアイテム情報
		m_pPrice[1] = new CPrice(LEFT_PRICE_POSX + PRICE_WIDTHX - 35.0f,						// 価格情報
			LEFT_PRICE_POSY, 0.0f, PRICE_NOZZLE);

		//----左下のアイコン----
		// 時間延長
		for (int i = SELECT_ICON_KIND * 2; i < SELECT_ICON_KIND * 3; i++)
		{
			// 通常、選択、アイコンの順に入力
			m_pShopIcon[i] = new CShopIcon(SELECT_LEFT_ICON_POSX,
				SELECT_LEFT_ICON_POSY + SELECT_ICON_WIDTHY - 5.0f, 0.0f, TIMER_KOMA_NO + i - SELECT_ICON_KIND * 2, m_nStage);
			pShopIcon[i] = m_pShopIcon[i]->GetIcon();												// パラメータ情報
			pShopIcon[i]->pTexture = new Texture();
			if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/セレクトアイテム.png")))	// カスタムアイコン
			{
				MessageBox(NULL, "ShopMenu.cpp セレクトアイテム.png", "Error", MB_OK);
			}
			m_pShopIcon[i]->SetSize(SELECT_ICON_SiZEX,			// サイズ設定
				SELECT_ICON_SiZEY);
		}

		m_nShopCustom[2] = Item::TIMER;											// ショップにあるアイテム情報
		m_pPrice[2] = new CPrice(LEFT_PRICE_POSX, LEFT_PRICE_POSY + PRICE_WIDTHY + 15.0f,	// 価格情報
			0.0f, PRICE_TIMER);

		//----右下のアイコン----
		// クーポン
		for (int i = SELECT_ICON_KIND * 3; i < SELECT_ICON_KIND * 4; i++)
		{
			// 通常、選択、アイコンの順に入力
			m_pShopIcon[i] = new CShopIcon(SELECT_LEFT_ICON_POSX + SELECT_ICON_WIDTHX,
				SELECT_LEFT_ICON_POSY + SELECT_ICON_WIDTHY, 0.0f, COUPON_KOMA_NO + i - SELECT_ICON_KIND * 3, m_nStage);
			pShopIcon[i] = m_pShopIcon[i]->GetIcon();									// パラメータ情報
			pShopIcon[i]->pTexture = new Texture();
			if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/セレクトアイテム.png")))	// カスタムアイコン
			{
				MessageBox(NULL, "ShopMenu.cpp セレクトアイテム.png", "Error", MB_OK);
			}
			m_pShopIcon[i]->SetSize(SELECT_ICON_SiZEX,			// サイズ設定
				SELECT_ICON_SiZEY);
		}
		m_nShopCustom[3] = Item::COUPON;												// ショップにあるアイテム情報
		m_pPrice[3] = new CPrice(LEFT_PRICE_POSX + PRICE_WIDTHX - 20.0f,						// 価格情報
			LEFT_PRICE_POSY + PRICE_WIDTHY + 15.0f,
			0.0f, PRICE_COUPON);
		break;
	case 1:
	case 2:
	case 3:
		// ステージ最大カスタム最大数代入
		if (m_nStage != 3)
		{
			m_nMaxCustom = 5;
		}
		else
		{
			m_nMaxCustom = 6;
		}
		// 総ページ数
		m_nTotalPage = 2;

		//----矢印----
		m_BaseShopMenu[4].size = DirectX::XMFLOAT2(m_BaseShopMenu[4].pTexture->GetWidth()
			, m_BaseShopMenu[4].pTexture->GetHeight());
		m_BaseShopMenu[4].pos = DirectX::XMFLOAT3(RIGHT_ARROW_POSX, ARROW_POSY, 0.0f);

		//----アイコン、文章テクスチャを動的確保----
		m_pShopText = new CShopText(GAME_SHOP, m_pSoundMng);
		pShopText = m_pShopText->GetText();	// パラメータ情報
		pShopText->pTexture = new Texture();

		//----文章テクスチャ読み込み----
		// テキスト
		if (FAILED(pShopText->pTexture->Create("Assets/Texture/ShopText.png")))
		{
			MessageBox(NULL, "ShopMenu.cpp ShopText.png", "Error", MB_OK);
		}
		m_pShopText->SetSize(pShopText->pTexture->GetWidth(), pShopText->pTexture->GetHeight());	// サイズ設定

		//----左上のアイコン----
		// のこぎり
		for (int i = 0; i < ICON_KIND; i++)
		{
			// 通常、選択、アイコン、売り切れ、売り切れ選択の順に入力
			if (i != 2)
			{
				m_pShopIcon[i] = new CShopIcon(LEFT_ICON_POSX, LEFT_ICON_POSY, 0.0f, SAW_KOMA_NO + i, m_nStage);
			}
			else
			{
				m_pShopIcon[i] = new CShopIcon(LEFT_ICON_POSX, LEFT_ICON_POSY - 5.0f, 0.0f, SAW_KOMA_NO + i, m_nStage);
			}
			pShopIcon[i] = m_pShopIcon[i]->GetIcon();												// パラメータ情報
			pShopIcon[i]->pTexture = new Texture();
			if ((i - 3) % 5 == 0)	// 4種類目なら
			{
				if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/UI_Urikire.png")))	// 通常アイコン
				{
					MessageBox(NULL, "ShopMenu.cpp UI_Urikire.png", "Error", MB_OK);
				}
			}
			else if ((i - 4) % 5 == 0)	// 5種類目なら
			{
				if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/UI_Urikire2.png")))	// 選択アイコン
				{
					MessageBox(NULL, "ShopMenu.cpp UI_Urikire2.png", "Error", MB_OK);
				}
			}
			else
			{
				if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/UI_Icon.png")))	// カスタムアイコン
				{
					MessageBox(NULL, "ShopMenu.cpp UI_Icon.png", "Error", MB_OK);
				}
			}
			m_pShopIcon[i]->SetSize(ICON_SiZEX,			// サイズ設定
				ICON_SiZEY);
		}

		m_nShopCustom[0] = Custom::SAW;																// ショップにあるカスタム情報
		m_pPrice[0] = new CPrice(LEFT_PRICE_POSX - 20.0f, LEFT_PRICE_POSY, 0.0f, PRICE_SAW_LEVEL1);			// 価格情報
		//----座標退避----
		m_anPricePos[0].x = LEFT_PRICE_POSX - 20.0f;
		m_anPricePos[0].y = LEFT_PRICE_POSY;
		for (int i = ICON_KIND - 2; i < ICON_KIND; i++)
		{
			m_pShopIcon[i]->SetTexCoord(0.0f, 1.0f);												// 売り切れサイズ調整
			m_pShopIcon[i]->SetPos(LEFT_ICON_POSX - 5.0f, LEFT_ICON_POSY + 5.0f);					// 座標設定
			m_pShopIcon[i]->SetSize(pShopIcon[i]->pTexture->GetWidth() * SOLD_OUT_RATIO				// サイズ設定
				, pShopIcon[i]->pTexture->GetHeight() * SOLD_OUT_RATIO);
		}

		//----右上のアイコン----
		// ハンマー
		for (int i = ICON_KIND; i < ICON_KIND * 2; i++)
		{
			// 通常、選択、アイコン、売り切れ、売り切れ選択の順に入力
			if (i != 7)
			{
				m_pShopIcon[i] = new CShopIcon(LEFT_ICON_POSX + ICON_WIDTHX,
					LEFT_ICON_POSY, 0.0f, HAMMER_KOMA_NO + i - ICON_KIND, m_nStage);
			}
			else
			{
				m_pShopIcon[i] = new CShopIcon(LEFT_ICON_POSX + ICON_WIDTHX,
					LEFT_ICON_POSY - 5.0f, 0.0f, HAMMER_KOMA_NO + i - ICON_KIND, m_nStage);
			}
			pShopIcon[i] = m_pShopIcon[i]->GetIcon();											// パラメータ情報
			pShopIcon[i]->pTexture = new Texture();
			if ((i - 3) % 5 == 0)	// 4種類目なら
			{
				if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/UI_Urikire.png")))	// 通常アイコン
				{
					MessageBox(NULL, "ShopMenu.cpp UI_Urikire.png", "Error", MB_OK);
				}
			}
			else if ((i - 4) % 5 == 0)	// 5種類目なら
			{
				if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/UI_Urikire2.png")))	// 選択アイコン
				{
					MessageBox(NULL, "ShopMenu.cpp UI_Urikire2.png", "Error", MB_OK);
				}
			}
			else
			{
				if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/UI_Icon.png")))	// カスタムアイコン
				{
					MessageBox(NULL, "ShopMenu.cpp UI_Icon.png", "Error", MB_OK);
				}
			}
			m_pShopIcon[i]->SetSize(ICON_SiZEX,			// サイズ設定
				ICON_SiZEY);
		}
		m_nShopCustom[1] = Custom::HAMMER;														// ショップにあるカスタム情報
		m_pPrice[1] = new CPrice(LEFT_PRICE_POSX + PRICE_WIDTHX - 35.0f,						// 価格情報
			LEFT_PRICE_POSY - 2.0f, 0.0f, PRICE_HAMMER_LEVEL1);
		//----座標退避----
		m_anPricePos[1].x = LEFT_PRICE_POSX + PRICE_WIDTHX - 35.0f;
		m_anPricePos[1].y = LEFT_PRICE_POSY - 2.0f;
		for (int i = ICON_KIND * 2 - 2; i < ICON_KIND * 2; i++)
		{
			m_pShopIcon[i]->SetTexCoord(0.0f, 1.0f);											// 売り切れサイズ調整
			m_pShopIcon[i]->SetPos(LEFT_ICON_POSX + ICON_WIDTHX - 5.0f,								// 座標設定
				LEFT_ICON_POSY + 6.0f);
			m_pShopIcon[i]->SetSize(pShopIcon[i]->pTexture->GetWidth() * SOLD_OUT_RATIO			// サイズ設定
				, pShopIcon[i]->pTexture->GetHeight() * SOLD_OUT_RATIO);
		}

		//----左下のアイコン----
		// ドリル
		for (int i = ICON_KIND * 2; i < ICON_KIND * 3; i++)
		{
			// 通常、選択、アイコン、売り切れ、売り切れ選択の順に入力
			if (i != 12)
			{
				m_pShopIcon[i] = new CShopIcon(LEFT_ICON_POSX,
					LEFT_ICON_POSY + ICON_WIDTHY, 0.0f, DRILL_KOMA_NO + i - ICON_KIND * 2, m_nStage);
			}
			else
			{
				m_pShopIcon[i] = new CShopIcon(LEFT_ICON_POSX + 15.0f,
					LEFT_ICON_POSY + ICON_WIDTHY - 8.0f, 0.0f, DRILL_KOMA_NO + i - ICON_KIND * 2, m_nStage);
			}
			pShopIcon[i] = m_pShopIcon[i]->GetIcon();												// パラメータ情報
			pShopIcon[i]->pTexture = new Texture();
			if ((i - 3) % 5 == 0)	// 4種類目なら
			{
				if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/UI_Urikire.png")))	// 通常アイコン
				{
					MessageBox(NULL, "ShopMenu.cpp UI_Urikire.png", "Error", MB_OK);
				}
			}
			else if ((i - 4) % 5 == 0)	// 5種類目なら
			{
				if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/UI_Urikire2.png")))	// 選択アイコン
				{
					MessageBox(NULL, "ShopMenu.cpp UI_Urikire2.png", "Error", MB_OK);
				}
			}
			else
			{
				if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/UI_Icon.png")))	// カスタムアイコン
				{
					MessageBox(NULL, "ShopMenu.cpp UI_Icon.png", "Error", MB_OK);
				}
			}
			if (i != 12)
			{
				m_pShopIcon[i]->SetSize(ICON_SiZEX,			// サイズ設定
					ICON_SiZEY);
			}
			else
			{
				m_pShopIcon[i]->SetSize(ICON_SiZEX - 10.0f,			// サイズ設定
					ICON_SiZEY - 10.0f);
			}
		}

		m_nShopCustom[2] = Custom::DRILL;													// ショップにあるカスタム情報
		m_pPrice[2] = new CPrice(LEFT_PRICE_POSX - 20.0f, LEFT_PRICE_POSY + PRICE_WIDTHY/* + 3.0f*/,	// 価格情報
			0.0f, PRICE_DRILL_LEVEL1);
		//----座標退避----
		m_anPricePos[2].x = LEFT_PRICE_POSX - 20.0f;
		m_anPricePos[2].y = LEFT_PRICE_POSY + PRICE_WIDTHY/* + 3.0f*/;
		for (int i = ICON_KIND * 3 - 2; i < ICON_KIND * 3; i++)
		{
			m_pShopIcon[i]->SetTexCoord(0.0f, 1.0f);												// 売り切れサイズ調整
			m_pShopIcon[i]->SetPos(LEFT_ICON_POSX - 5.0f,													// 座標設定
				LEFT_ICON_POSY + ICON_WIDTHY + 14.0f);
			m_pShopIcon[i]->SetSize(pShopIcon[i]->pTexture->GetWidth() * SOLD_OUT_RATIO				// サイズ設定
				, pShopIcon[i]->pTexture->GetHeight() * SOLD_OUT_RATIO);
		}

		//----右下のアイコン----
		// ノズル強化
		for (int i = ICON_KIND * 3; i < ICON_KIND * 4; i++)
		{
			// 通常、選択、アイコン、売り切れ、売り切れ選択に入力
			if (i != 17)
			{
				m_pShopIcon[i] = new CShopIcon(LEFT_ICON_POSX + ICON_WIDTHX,
					LEFT_ICON_POSY + ICON_WIDTHY, 0.0f, NOZZLE_KOMA_NO + i - ICON_KIND * 3, m_nStage);
			}
			else
			{
				m_pShopIcon[i] = new CShopIcon(LEFT_ICON_POSX + ICON_WIDTHX,
					LEFT_ICON_POSY + ICON_WIDTHY - 7.0f, 0.0f, NOZZLE_KOMA_NO + i - ICON_KIND * 3, m_nStage);
			}
			pShopIcon[i] = m_pShopIcon[i]->GetIcon();												// パラメータ情報
			pShopIcon[i]->pTexture = new Texture();
			if ((i - 3) % 5 == 0)	// 4種類目なら
			{
				if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/UI_Urikire.png")))	// 通常アイコン
				{
					MessageBox(NULL, "ShopMenu.cpp UI_Urikire.png", "Error", MB_OK);
				}
			}
			else if ((i - 4) % 5 == 0)	// 5種類目なら
			{
				if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/UI_Urikire2.png")))	// 選択アイコン
				{
					MessageBox(NULL, "ShopMenu.cpp UI_Urikire2.png", "Error", MB_OK);
				}
			}
			else
			{
				if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/UI_Icon.png")))	// カスタムアイコン
				{
					MessageBox(NULL, "ShopMenu.cpp UI_Icon.png", "Error", MB_OK);
				}
			}
			m_pShopIcon[i]->SetSize(ICON_SiZEX,			// サイズ設定
				ICON_SiZEY);
		}
		m_nShopCustom[3] = Custom::GAME_NOZZLE;														// ショップにあるカスタム情報
		m_pPrice[3] = new CPrice(LEFT_PRICE_POSX + PRICE_WIDTHX - 40.0f,							// 価格情報
			LEFT_PRICE_POSY + PRICE_WIDTHY,
			0.0f, PRICE_NOZZLE_LEVEL2);
		//----座標退避----
		m_anPricePos[3].x = LEFT_PRICE_POSX + PRICE_WIDTHX - 40.0f;
		m_anPricePos[3].y = LEFT_PRICE_POSY + PRICE_WIDTHY;
		for (int i = ICON_KIND * 4 - 2; i < ICON_KIND * 4; i++)
		{
			m_pShopIcon[i]->SetTexCoord(0.0f, 1.0f);												// 売り切れサイズ調整
			m_pShopIcon[i]->SetPos(LEFT_ICON_POSX + ICON_WIDTHX - 5.0f,								// 座標設定
				LEFT_ICON_POSY + ICON_WIDTHY + 16.0f);
			m_pShopIcon[i]->SetSize(pShopIcon[i]->pTexture->GetWidth() * SOLD_OUT_RATIO				// サイズ設定
				, pShopIcon[i]->pTexture->GetHeight() * SOLD_OUT_RATIO);
		}

		//----2ページ目----
		// 左上
		for (int i = ICON_KIND * 4; i < ICON_KIND * 5; i++)
		{
			// 通常、選択、アイコン、売り切れ、売り切れ選択の順に入力
			m_pShopIcon[i] = new CShopIcon(LEFT_ICON_POSX, LEFT_ICON_POSY,
				0.0f, BOOTS_KOMA_NO + i - ICON_KIND * 4, m_nStage);
			pShopIcon[i] = m_pShopIcon[i]->GetIcon();												// パラメータ情報
			pShopIcon[i]->pTexture = new Texture();
			if ((i - 3) % 5 == 0)	// 4種類目なら
			{
				if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/UI_Urikire.png")))	// 通常アイコン
				{
					MessageBox(NULL, "ShopMenu.cpp UI_Urikire.png", "Error", MB_OK);
				}
			}
			else if ((i - 4) % 5 == 0)	// 5種類目なら
			{
				if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/UI_Urikire2.png")))	// 選択アイコン
				{
					MessageBox(NULL, "ShopMenu.cpp UI_Urikire2.png", "Error", MB_OK);
				}
			}
			else
			{
				if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/UI_Icon.png")))	// カスタムアイコン
				{
					MessageBox(NULL, "ShopMenu.cpp UI_Icon.png", "Error", MB_OK);
				}
			}
			m_pShopIcon[i]->SetSize(ICON_SiZEX,			// サイズ設定
				ICON_SiZEY);
		}

		m_nShopCustom[4] = Custom::BOOTS;																// ショップにあるカスタム情報
		m_pPrice[4] = new CPrice(LEFT_PRICE_POSX - 20.0f, LEFT_PRICE_POSY, 0.0f, PRICE_BOOTS);			// 価格情報
		//----座標退避----
		m_anPricePos[4].x = LEFT_PRICE_POSX - 20.0f;
		m_anPricePos[4].y = LEFT_PRICE_POSY;
		for (int i = ICON_KIND * 5 - 2; i < ICON_KIND * 5; i++)
		{
			m_pShopIcon[i]->SetTexCoord(0.0f, 1.0f);												// 売り切れサイズ調整
			m_pShopIcon[i]->SetPos(LEFT_ICON_POSX - 5.0f, LEFT_ICON_POSY + 5.0f);					// 座標設定
			m_pShopIcon[i]->SetSize(pShopIcon[i]->pTexture->GetWidth() * SOLD_OUT_RATIO				// サイズ設定
				, pShopIcon[i]->pTexture->GetHeight() * SOLD_OUT_RATIO);
		}

		if (m_nStage == 3)
		{
			//----右上のアイコン----
			// 耐熱カスタム
			for (int i = ICON_KIND * 5; i < ICON_KIND * 6; i++)
			{
				// 通常、選択、アイコン、売り切れ、売り切れ選択の順に入力
				if (i != 27 && i != 26)
				{
					m_pShopIcon[i] = new CShopIcon(LEFT_ICON_POSX + ICON_WIDTHX,
						LEFT_ICON_POSY, 0.0f, HEAT_RESISTANT_KOMA_NO + i - ICON_KIND * 5, m_nStage);
				}
				else if (i == 26)
				{
					m_pShopIcon[i] = new CShopIcon(LEFT_ICON_POSX + ICON_WIDTHX + 5.0f,
						LEFT_ICON_POSY - 5.0f, 0.0f, HEAT_RESISTANT_KOMA_NO + i - ICON_KIND * 5, m_nStage);
				}
				else
				{
					m_pShopIcon[i] = new CShopIcon(LEFT_ICON_POSX + ICON_WIDTHX + 10.0f,
						LEFT_ICON_POSY - 15.0f, 0.0f, HEAT_RESISTANT_KOMA_NO + i - ICON_KIND * 5, m_nStage);
				}
				pShopIcon[i] = m_pShopIcon[i]->GetIcon();											// パラメータ情報
				pShopIcon[i]->pTexture = new Texture();
				if ((i - 3) % 5 == 0)	// 4種類目なら
				{
					if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/UI_Urikire.png")))	// 通常アイコン
					{
						MessageBox(NULL, "ShopMenu.cpp UI_Urikire.png", "Error", MB_OK);
					}
				}
				else if ((i - 4) % 5 == 0)	// 5種類目なら
				{
					if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/UI_Urikire2.png")))	// 選択アイコン
					{
						MessageBox(NULL, "ShopMenu.cpp UI_Urikire2.png", "Error", MB_OK);
					}
				}
				else
				{
					if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/UI_Icon.png")))	// カスタムアイコン
					{
						MessageBox(NULL, "ShopMenu.cpp UI_Icon.png", "Error", MB_OK);
					}
				}
				m_pShopIcon[i]->SetSize(ICON_SiZEX,			// サイズ設定
					ICON_SiZEY);
			}
			m_nShopCustom[5] = Custom::HEAT_RESISTANT;														// ショップにあるカスタム情報
			m_pPrice[5] = new CPrice(LEFT_PRICE_POSX + PRICE_WIDTHX - 35.0f,						// 価格情報
				LEFT_PRICE_POSY - 2.0f, 0.0f, PRICE_HEAT_RESISTANT);
			//----座標退避----
			m_anPricePos[5].x = LEFT_PRICE_POSX + PRICE_WIDTHX - 35.0f;
			m_anPricePos[5].y = LEFT_PRICE_POSY - 2.0f;
			for (int i = ICON_KIND * 6 - 2; i < ICON_KIND * 6; i++)
			{
				m_pShopIcon[i]->SetTexCoord(0.0f, 1.0f);											// 売り切れサイズ調整
				m_pShopIcon[i]->SetPos(LEFT_ICON_POSX + ICON_WIDTHX - 5.0f,								// 座標設定
					LEFT_ICON_POSY + 6.0f);
				m_pShopIcon[i]->SetSize(pShopIcon[i]->pTexture->GetWidth() * SOLD_OUT_RATIO			// サイズ設定
					, pShopIcon[i]->pTexture->GetHeight() * SOLD_OUT_RATIO);
			}
		}
		break;
	}
}


CShopMenu::~CShopMenu()	// デストラクタ
{
	//----ショップメモリ解放----
	if (m_pShop)
	{
		delete m_pShop;
		m_pShop = nullptr;
	}

	//----ベースメモリ解放----
	for (int i = 0; i < MAX_BASE_SHOP_MENU; ++i)
	{
		if (m_BaseShopMenu[i].pTexture)
		{
			delete m_BaseShopMenu[i].pTexture;
			m_BaseShopMenu[i].pTexture = nullptr;
		}
	}

	//----アイコンメモリ解放----
	for (int i = 0; i < MAX_CUSTOM * ICON_KIND; ++i)
	{
		if (m_pShopIcon[i])
		{
			if (pShopIcon[i]->pTexture)
			{
				delete pShopIcon[i]->pTexture;
				pShopIcon[i]->pTexture = nullptr;
			}
			delete m_pShopIcon[i];
			m_pShopIcon[i] = nullptr;
		}
	}

	//----文章メモリ解放----
	SAFE_DELETE(m_pShopText);

	// 価格メモリ解放
	for (int i = 0; i < MAX_CUSTOM; ++i)
	{
		if (m_pPrice[i])
		{
			delete m_pPrice[i];
			m_pPrice[i] = nullptr;
		}
	}
}

void CShopMenu::Update(float tick)	// 更新
{
	Animetion(tick);	// アニメーション処理

	//----アイテムが使用されたか----
	if (m_nCoupon && !m_nFirst)
	{
		// 割引
		m_pShop->SetItem(SHOP_COUPON);
		ALLCoupon();		// 値段表示調整関数
		m_nFirst = 1;
	}

	m_bShop = true;
	if (m_nOpenAnimetion)
	{
		return;
	}
	//コントローラー処理
	XINPUT_STATE state;
	XINPUT_KEYSTROKE stroke;
	XInputGetState(0, &state);
	XInputGetKeystroke(0, 0, &stroke);
	if ((state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		state.Gamepad.sThumbLX = 0;
		state.Gamepad.sThumbLY = 0;

	}
	if (state.dwPacketNumber != 3435973836)
	{
		if (state.Gamepad.sThumbLY > 0 &&
			state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && stroke.Flags == 0x0001
			|| state.Gamepad.wButtons&XINPUT_GAMEPAD_DPAD_UP&&stroke.Flags == 0x0001)
		{
			if (m_nCursor > 2)	// カーソル位置が下か
			{
				m_nCursor -= 2;	// カーソル位置を上へ
			}
			m_nLines = 0;	// セリフフラグ下げ
			m_nBuy = 0;		// 買いフラグ下げ
			m_nMove = 1;	// 移動フラグ上げ
			m_fRatio = 1.0f;	// 比率リセット
			m_pSoundMng->playSound(CSoundMng::SystemSE::select);//選択se
		}
		else if (state.Gamepad.sThumbLX < 0 &&
			state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && stroke.Flags == 0x0001
			|| state.Gamepad.wButtons&XINPUT_GAMEPAD_DPAD_LEFT&&stroke.Flags == 0x0001)
		{
			if (m_nCursor % 2 == 1 && m_nPage > 1)	// 左端で複数ページか
			{
				m_nPage -= 1;	// 前のページへ
				m_nCursor = 2;	// カーソル位置調整
				// アニメーション関係
				// 矢印の位置を変える
				m_BaseShopMenu[4].pos.x = RIGHT_ARROW_POSX;
				m_fAnimeMoveX = 0.1f;	// 移動量リセット
				m_nAnimeMoved = 0;		// フラグリセット
				m_nFrame = 0;			// フレームカウントリセット
			}
			else if (m_nCursor % 2 == 0)	// カーソル位置が右か
			{
				m_nCursor -= 1;				// カーソル位置を左へ
			}
			m_nLines = 0;	// セリフフラグ下げ
			m_nBuy = 0;		// 買いフラグ下げ
			m_nMove = 1;	// 移動フラグ上げ
			m_fRatio = 1.0f;	// 比率リセット
			m_pSoundMng->playSound(CSoundMng::SystemSE::select);//選択se
		}
		else if (state.Gamepad.sThumbLY < 0 &&
			state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && stroke.Flags == 0x0001
			|| state.Gamepad.wButtons&XINPUT_GAMEPAD_DPAD_DOWN&&stroke.Flags == 0x0001)
		{
			if (m_nCursor <= 2)	// カーソル位置が上か
			{
				m_nCursor += 2;	// カーソル位置を下へ
			}
			m_nLines = 0;	// セリフフラグ下げ
			m_nBuy = 0;		// 買いフラグ下げ
			m_nMove = 1;	// 移動フラグ上げ
			m_fRatio = 1.0f;	// 比率リセット
			m_pSoundMng->playSound(CSoundMng::SystemSE::select);//選択se
		}
		else if (state.Gamepad.sThumbLX > 0 &&
			state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && stroke.Flags == 0x0001
			|| state.Gamepad.wButtons&XINPUT_GAMEPAD_DPAD_RIGHT&&stroke.Flags == 0x0001)
		{
			if (m_nCursor % 2 == 0 && m_nPage < m_nTotalPage)	// 右端で複数ページか
			{
				m_nPage += 1;	// 次のページへ
				m_nCursor = 1;	// カーソル位置調整
				// アニメーション関係
				// 矢印の位置を変える
				m_BaseShopMenu[4].pos.x = LEFT_ARROW_POSX;
				m_fAnimeMoveX = 0.1f;	// 移動量リセット
				m_nAnimeMoved = 0;		// フラグリセット
				m_nFrame = 0;			// フレームカウントリセット
			}
			else if (m_nCursor % 2 == 1)	// カーソル位置を右へ
			{
				m_nCursor += 1;
			}
			m_nLines = 0;	// セリフフラグ下げ
			m_nBuy = 0;		// 買いフラグ下げ
			m_nMove = 1;	// 移動フラグ上げ
			m_fRatio = 1.0f;	// 比率リセット
			m_pSoundMng->playSound(CSoundMng::SystemSE::select);//選択se
		}
	}
	if (state.Gamepad.wButtons&XINPUT_GAMEPAD_A&&stroke.Flags == 0x0001)
	{
		// 購入できるか
		// 1ページ目だったら
		if (m_nPage == 1)
		{
			// ステージ内か
			if (m_nStage != 0)
			{
				// カスタマイズパーツ購入
				m_pShop->Buy(m_pnCustom, m_pnMoney, m_nShopCustom[m_nCursor - 1],
					&m_nBuy, &m_nNozzle);
			}
			// セレクトだったら
			else
			{
				// アイテム購入
				m_pShop->ItemBuy(m_pnItem, m_pnMoney, m_nShopCustom[m_nCursor - 1],
					&m_nBuy);
			}
			if (m_nBuy == 1)	// 購入されたら
			{
				m_nLines = 0;	// セリフフラグ下げ
				m_anBuyCustom = m_nShopCustom[m_nCursor - 1];
			}
		}
		// 2ページ目だったら
		else if (m_nPage == 2)
		{
			m_pShop->Buy(m_pnCustom, m_pnMoney, m_nShopCustom[m_nCursor + 3],
				&m_nBuy, &m_nNozzle);
			if (m_nBuy == 1)	// 購入されたら
			{
				m_nLines = 0;	// セリフフラグ下げ
				m_anBuyCustom = m_nShopCustom[m_nCursor + 3];
			}
		}
		if (m_nBuy == 1) m_pSoundMng->playSound(CSoundMng::ShopSE::buy);//レジ音
	}
	if (state.Gamepad.wButtons&XINPUT_GAMEPAD_B&&stroke.Flags == XINPUT_KEYSTROKE_KEYDOWN)
	{
		m_bShop = false;// ショップ画面閉じる
		m_nLines = 0;	// セリフフラグ下げ
		m_pShopText->SetTextNo(0, FIRST_LINE, FIRST_LINE);
		m_nBuy = 0;		// 買いフラグ下げ
		m_nMove = 0;	// カーソル移動フラグ下げ
		m_fRatio = 1.0f;	// 比率リセット
		//----座標リセット----
		//----座標リセット----
		m_time = 0.0f;
		m_BaseShopMenu[0].pos.x = MERCHANT_START_POSX;
		//		m_BaseShopMenu[0].pos.y = MERCHANT_START_POSY;
		m_BaseShopMenu[1].pos.y = WINDOW_START_POSY;
		//		m_BaseShopMenu[2].pos.y = LINE_FRAME_START_POSY;
		m_BaseShopMenu[2].pos.x = LINE_FRAME_START_POSX;
		//m_BaseShopMenu[3].pos.y = DOWN_ARROW_START_POSY;
		//m_BaseShopMenu[4].pos.y = ARROW_START_POSY;
		for (int i = 5; i < 8; i++)
		{
			m_BaseShopMenu[i].pos.y = -100.0f;	// 画面外へ移動させる
		}
		m_nOpenAnimetion = 1;	// アニメーションフラグ上げ
		m_pSoundMng->playSound(CSoundMng::SystemSE::cancel);//キャンセルse
	}

	//----入力処理----
	if (IsKeyTrigger('W'))	// 上
	{
		if (m_nCursor > 2)	// カーソル位置が下か
		{
			m_nCursor -= 2;	// カーソル位置を上へ
		}
		m_nLines = 0;	// セリフフラグ下げ
		m_nBuy = 0;		// 買いフラグ下げ
		m_nMove = 1;	// 移動フラグ上げ
		m_fRatio = 1.0f;	// 比率リセット
		m_pSoundMng->playSound(CSoundMng::SystemSE::select);//選択se
	}
	else if (IsKeyTrigger('A'))	// 左
	{
		if (m_nCursor % 2 == 1 && m_nPage > 1)	// 左端で複数ページか
		{
			m_nPage -= 1;	// 前のページへ
			m_nCursor = 2;	// カーソル位置調整
			// アニメーション関係
			// 矢印の位置を変える
			m_BaseShopMenu[4].pos.x = RIGHT_ARROW_POSX;
			m_fAnimeMoveX = 0.1f;	// 移動量リセット
			m_nAnimeMoved = 0;		// フラグリセット
			m_nFrame = 0;			// フレームカウントリセット
		}
		else if (m_nCursor % 2 == 0)	// カーソル位置が右か
		{
			m_nCursor -= 1;				// カーソル位置を左へ
		}
		m_nLines = 0;	// セリフフラグ下げ
		m_nBuy = 0;		// 買いフラグ下げ
		m_nMove = 1;	// 移動フラグ上げ
		m_fRatio = 1.0f;	// 比率リセット
		m_pSoundMng->playSound(CSoundMng::SystemSE::select);//選択se
	}
	else if (IsKeyTrigger('S'))	// 下
	{
		if (m_nCursor <= 2)	// カーソル位置が上か
		{
			m_nCursor += 2;	// カーソル位置を下へ
		}
		m_nLines = 0;	// セリフフラグ下げ
		m_nBuy = 0;		// 買いフラグ下げ
		m_nMove = 1;	// 移動フラグ上げ
		m_fRatio = 1.0f;	// 比率リセット
		m_pSoundMng->playSound(CSoundMng::SystemSE::select);//選択se
	}
	else if (IsKeyTrigger('D'))	// 右
	{
		if (m_nCursor % 2 == 0 && m_nPage < m_nTotalPage)	// 右端で複数ページか
		{
			m_nPage += 1;	// 次のページへ
			m_nCursor = 1;	// カーソル位置調整
			// アニメーション関係
			// 矢印の位置を変える
			m_BaseShopMenu[4].pos.x = LEFT_ARROW_POSX;
			m_fAnimeMoveX = 0.1f;	// 移動量リセット
			m_nAnimeMoved = 0;		// フラグリセット
			m_nFrame = 0;			// フレームカウントリセット
		}
		else if (m_nCursor % 2 == 1)	// カーソル位置を右へ
		{
			m_nCursor += 1;
		}
		m_nLines = 0;	// セリフフラグ下げ
		m_nBuy = 0;		// 買いフラグ下げ
		m_nMove = 1;	// 移動フラグ上げ
		m_fRatio = 1.0f;	// 比率リセット
		m_pSoundMng->playSound(CSoundMng::SystemSE::select);//選択se
	}
	if (IsKeyTrigger(VK_RETURN))	// 購入
	{
		// 購入できるか
		// 1ページ目だったら
		if (m_nPage == 1)
		{
			// ステージ内か
			if (m_nStage != 0)
			{
				// カスタマイズパーツ購入
				m_pShop->Buy(m_pnCustom, m_pnMoney, m_nShopCustom[m_nCursor - 1],
					&m_nBuy, &m_nNozzle);
			}
			// セレクトだったら
			else
			{
				// アイテム購入
				m_pShop->ItemBuy(m_pnItem, m_pnMoney, m_nShopCustom[m_nCursor - 1],
					&m_nBuy);
			}
			if (m_nBuy == 1)	// 購入されたら
			{
				m_nLines = 0;	// セリフフラグ下げ
				m_anBuyCustom = m_nShopCustom[m_nCursor - 1];
			}
		}
		// 2ページ目だったら
		else if (m_nPage == 2)
		{
			m_pShop->Buy(m_pnCustom, m_pnMoney, m_nShopCustom[m_nCursor + 3],
				&m_nBuy, &m_nNozzle);
			if (m_nBuy == 1)	// 購入されたら
			{
				m_nLines = 0;	// セリフフラグ下げ
				m_anBuyCustom = m_nShopCustom[m_nCursor + 3];
			}
		}
		if (m_nBuy == 1) m_pSoundMng->playSound(CSoundMng::ShopSE::buy);//レジ音

	}
	if (IsKeyTrigger('E'))	// 閉じる
	{
		m_bShop = false;// ショップ画面閉じる
		m_nLines = 0;	// セリフフラグ下げ
		m_pShopText->SetTextNo(0, FIRST_LINE, FIRST_LINE);
		m_nBuy = 0;		// 買いフラグ下げ
		m_nMove = 0;	// カーソル移動フラグ下げ
		m_fRatio = 1.0f;	// 比率リセット
		//----座標リセット----
		m_time = 0.0f;
		m_BaseShopMenu[0].pos.x = MERCHANT_START_POSX;
//		m_BaseShopMenu[0].pos.y = MERCHANT_START_POSY;
		m_BaseShopMenu[1].pos.y = WINDOW_START_POSY;	
//		m_BaseShopMenu[2].pos.y = LINE_FRAME_START_POSY;
		m_BaseShopMenu[2].pos.x = LINE_FRAME_START_POSX;
		//m_BaseShopMenu[3].pos.y = DOWN_ARROW_START_POSY;
		//m_BaseShopMenu[4].pos.y = ARROW_START_POSY;
		for (int i = 5; i < 8; i++)
		{
			m_BaseShopMenu[i].pos.y = -100.0f;	// 画面外へ移動させる
		}
		m_nOpenAnimetion = 1;	// アニメーションフラグ上げ
		m_pSoundMng->playSound(CSoundMng::SystemSE::cancel);//キャンセルse
	}

	LineSet();	// セリフ描画
}

void CShopMenu::Draw()	// 描画
{
	DirectX::XMFLOAT4X4 mat[3][MAX_BASE_SHOP_MENU];		// 一番総数が多いステージの分枠を作る

	DirectX::XMMATRIX world[MAX_BASE_SHOP_MENU];		// 一番総数が多いステージの分枠を作る

	if (!m_nOpenAnimetion)
	{
		PageSetDraw();	// ページ表記の設定
	}

	//----ベースショップ画面のワールド行列設定----
	for (int i = 0; i < MAX_BASE_SHOP_MENU; ++i)
	{
		if (!m_BaseShopMenu[i].pTexture) continue;

		//ワールド行列はX,Yのみを考慮して作成
		world[i] = DirectX::XMMatrixTranslation(m_BaseShopMenu[i].pos.x, m_BaseShopMenu[i].pos.y, m_BaseShopMenu[i].pos.z);
		DirectX::XMStoreFloat4x4(&mat[0][i], DirectX::XMMatrixTranspose(world[i]));
	}

	//ビュー行列は2dだとカメラの位置があまり関係ないので、単位行列を設定する
	DirectX::XMStoreFloat4x4(&mat[1][0], DirectX::XMMatrixIdentity());

	//プロジェクション行列は2dとして表示するための行列を設定する
	//この行列で2dスクリーンの大きさが決まる
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(ICON_LEFT, ICON_RIGHT, ICON_BOTTOM,
		ICON_TOP, ICON_NEAR, ICON_FAR);
	DirectX::XMStoreFloat4x4(&mat[2][0], DirectX::XMMatrixTranspose(proj));

	//ベースショップ画面スプライトの設定
	for (int i = 0; i < MAX_BASE_SHOP_MENU; ++i)
	{
		// 最初はアニメーションのあるものだけ描画
		if (m_nOpenAnimetion && i >= 4/* || i == 0)*/)
		{
			continue;	// 入店時のアニメーションがないものだったら次へ
		}
		Sprite::SetWorld(mat[0][i]);												// ワールドセット
		Sprite::SetView(mat[1][0]);													// ビューセット
		Sprite::SetProjection(mat[2][0]);											// プロジェクションセット
		Sprite::SetSize(DirectX::XMFLOAT2(m_BaseShopMenu[i].size.x,					// サイズセット
			-m_BaseShopMenu[i].size.y));
		Sprite::SetUVPos(DirectX::XMFLOAT2(m_BaseShopMenu[i].posTexCoord.x,			// UV座標セット
			m_BaseShopMenu[i].posTexCoord.y));
		Sprite::SetUVScale(DirectX::XMFLOAT2(m_BaseShopMenu[i].sizeTexCoord.x,		// UVサイズセット
			m_BaseShopMenu[i].sizeTexCoord.y));
		Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		if (m_nPage == 2 && i == 4)
		{
			Sprite::SetTexture(m_BaseShopMenu[6].pTexture);								// 左矢印テクスチャセット	
		}
		else if (i < 5)
		{
			Sprite::SetTexture(m_BaseShopMenu[i].pTexture);								// テクスチャセット	
		}
		else
		{
			Sprite::SetTexture(m_BaseShopMenu[5].pTexture);								// 数字テクスチャセット	
		}
		Sprite::Draw();																// 描画
	}

	if (m_nOpenAnimetion)	// オープンアニメーション処理をしていたら
	{
		return;
	}

	//----ショップ画面----
	if (!m_nMove && !m_nBuy)
	{
		m_pShopText->Draw();	// 来店セリフを描画
	}

	// お金が足りているか判定を取る
	MoneyEnough();

	// アイコン描画
	IconDraw();

	if (m_nBuy == 2)													// 購入したか
	{
		m_pShopText->Draw();									// 購入した時のセリフを描画
	}
}

void CShopMenu::Animetion(float tick)	// アニメーション用関数
{
	// 補間値 = (終了時の値 - 開始時の値) * イージング関数(現在の時間 / 総時間) + 開始時の値
	if (m_nOpenAnimetion)	// 開いた時のアニメーション
	{
		m_time += tick;	// 現在時間更新
		
		if (m_time > ANIMETION_SECONDS) { m_nOpenAnimetion = false; }
		float param = m_time / ANIMETION_SECONDS;	// 現在時間　÷　総時間

		m_BaseShopMenu[0].pos.x = (MERCHANT_POSX - MERCHANT_START_POSX) * EaseOutExpo(param) + MERCHANT_START_POSX;
//		m_BaseShopMenu[0].pos.y = (MERCHANT_POSY - MERCHANT_START_POSY) * EaseOutExpo(param) + MERCHANT_START_POSY;
		m_BaseShopMenu[1].pos.y = (WINDOW_POSY - WINDOW_START_POSY) * EaseOutExpo(param) + WINDOW_START_POSY;
//		m_BaseShopMenu[2].pos.y = (LINE_FRAME_POSY - LINE_FRAME_START_POSY) * EaseOutExpo(param) + LINE_FRAME_START_POSY;
		m_BaseShopMenu[2].pos.x = (LINE_FRAME_POSX - LINE_FRAME_START_POSX) * EaseOutExpo(param) + LINE_FRAME_START_POSX;
		//m_BaseShopMenu[3].pos.y = (DOWN_ARROW_POSY - DOWN_ARROW_START_POSY) * EaseOutExpo(param) + DOWN_ARROW_START_POSY;
		
		//if (m_BaseShopMenu[1].pos.y < WINDOW_POSY)		// 指定位置より上だったら
		//{
		//	m_BaseShopMenu[1].pos.y += DOWN_SPEED;		// 描画位置を下げる
		//}


		////else if ()
		////{

		////}
		//else
		//{
		//	m_BaseShopMenu[1].pos.y = WINDOW_POSY;		// 描画位置固定
		//	m_nOpenAnimetion = 0;
		//}
	//	if (m_BaseShopMenu[2].pos.y < LINE_FRAME_POSY)	// 指定位置より上だったら
	//	{
	//		m_BaseShopMenu[2].pos.y += DOWN_SPEED;		// 描画位置を下げる
	//	}
	//	else
	//	{
	//		m_BaseShopMenu[2].pos.y = LINE_FRAME_POSY;	// 描画位置固定
	//		//m_nOpenAnimetion = 0;
	//	}
	//	if (m_BaseShopMenu[3].pos.y < DOWN_ARROW_POSY)	// 指定位置より上だったら
	//	{
	//		m_BaseShopMenu[3].pos.y += DOWN_SPEED;		// 描画位置を下げる
	//	}
	//	else
	//	{
	//		m_BaseShopMenu[3].pos.y = DOWN_ARROW_POSY;	// 描画位置固定
	//	}
	}
	else if (m_nPage == 1)
	{
		if (!m_nAnimeMoved)		// 指定位置より上だったら
		{
			m_fAnimeMoveX *= 1.2f;
			m_BaseShopMenu[4].pos.x += m_fAnimeMoveX;		// 描画位置を下げる
			if (m_BaseShopMenu[4].pos.x >= RIGHT_ARROW_POSX + 15.0f)
			{
				m_nAnimeMoved = 1;
			}
		}
		else if (m_nAnimeMoved && m_nFrame != 0)
		{
			m_nFrame--;
			if (m_nFrame <= 0)
			{
				m_nFrame = 0;
				m_nAnimeMoved = 0;
			}
		}
		else if (m_nAnimeMoved)
		{
			m_fAnimeMoveX *= 0.9f;
			m_BaseShopMenu[4].pos.x -= m_fAnimeMoveX;		// 描画位置を下げる
			if (m_BaseShopMenu[4].pos.x <= RIGHT_ARROW_POSX)
			{
				m_nFrame = 40;
				m_fAnimeMoveX = 0.1f;
			}
		}
	}
	else if (m_nPage == 2)
	{
		if (!m_nAnimeMoved)		// 指定位置より上だったら
		{
			m_fAnimeMoveX *= 1.2f;
			m_BaseShopMenu[4].pos.x -= m_fAnimeMoveX;		// 描画位置を下げる
			if (m_BaseShopMenu[4].pos.x <= LEFT_ARROW_POSX - 15.0f)
			{
				m_nAnimeMoved = 1;
			}
		}
		else if (m_nAnimeMoved && m_nFrame != 0)
		{
			m_nFrame--;
			if (m_nFrame <= 0)
			{
				m_nFrame = 0;
				m_nAnimeMoved = 0;
			}
		}
		else if (m_nAnimeMoved)
		{
			m_fAnimeMoveX *= 0.9f;
			m_BaseShopMenu[4].pos.x += m_fAnimeMoveX;		// 描画位置を下げる
			if (m_BaseShopMenu[4].pos.x >= LEFT_ARROW_POSX)
			{
				m_nFrame = 40;
				m_fAnimeMoveX = 0.1f;
			}
		}
	}
}

void CShopMenu::LineSet()	// 流す文章セット
{
	// 2ページ目のアイコンと文章が合うように
	if (m_nPage == 2)	// 2ページ目だったら
	{
		// アイコンがあるかどうか
		if (m_nCursor > m_nMaxCustom - 4)
		{
			m_nCursor = m_noldCursor;	// 移動できなかったら元の位置に戻す
		}
	}
	//----セリフセット----
	if (!m_nMove && !m_nBuy)	// 入店時のセリフ
	{
		switch (m_nStage)
		{
		case 0:
			if (m_nLines && m_pShopText->GetLineNum() == FIRST_LINE &&
				m_pShopText->GetTextNo(FIRST_LINE) == ENTERING_LINE &&
				m_pShopText->GetAnimeNo(FIRST_LINE) >= SELECT_TEXT_ANIM_SHOP_MENU_NO)	// 一行目が描画されていたら
			{
				m_pShopText->SetTextNo(ENTERING_LINE + 1, SECOND_LINE, SECOND_LINE);					// 二行目
			}
			else if (m_nLines && m_pShopText->GetLineNum() == SECOND_LINE &&
				m_pShopText->GetTextNo(SECOND_LINE) == ENTERING_LINE + 1 &&
				m_pShopText->GetAnimeNo(SECOND_LINE) >= SELECT_TEXT_ANIM_SHOP_MENU_NO)	// 二行目が描画されていたら
			{
				m_pShopText->SetTextNo(ENTERING_LINE + 2, THIRD_LINE, THIRD_LINE);					// 三行目
			}
			else if (m_nLines && m_pShopText->GetLineNum() == THIRD_LINE &&
				m_pShopText->GetTextNo(THIRD_LINE) == ENTERING_LINE + 2 &&
				m_pShopText->GetAnimeNo(THIRD_LINE) >= SELECT_TEXT_ANIM_SHOP_MENU_NO)	// 三行目が描画されていたら
			{
				m_pShopText->SetTextNo(ENTERING_LINE + 3, FIRST_LINE, FORCE_LINE);					// 四行目
			}
			else if (m_nLines && m_pShopText->GetLineNum() == FORCE_LINE &&
				m_pShopText->GetTextNo(FIRST_LINE) == ENTERING_LINE + 3 &&
				m_pShopText->GetAnimeNo(FIRST_LINE) >= SELECT_TEXT_ANIM_SHOP_MENU_NO)	// 四行目が描画されていたら
			{
				m_pShopText->SetTextNo(ENTERING_LINE + 4, SECOND_LINE, 5);					// 五行目
			}
			else if (!m_nLines && m_pShopText->GetTextNo(FIRST_LINE) != ENTERING_LINE/* &&
				pShopText->currentAnimNo >= TEXT_ANIM_SHOP_MENU_NO*/)		// 描画されていなかったら
			{
				m_pShopText->SetTextNo(ENTERING_LINE, FIRST_LINE, FIRST_LINE);				// 一行目
				m_nLines = 1;													// ループ抑制
			}
			break;
		case 2:
		case 3:
			if (m_nLines && m_pShopText->GetLineNum() == FIRST_LINE &&
				m_pShopText->GetTextNo(FIRST_LINE) == ENTERING_LINE &&
				m_pShopText->GetAnimeNo(FIRST_LINE) >= TEXT_ANIM_SHOP_MENU_NO)			// 一行目が描画されていたら
			{
				m_pShopText->SetTextNo(ENTERING_LINE + 1, SECOND_LINE, SECOND_LINE);					// 二行目
			}
			else if (m_nLines && m_pShopText->GetLineNum() == SECOND_LINE &&
				m_pShopText->GetTextNo(SECOND_LINE) == ENTERING_LINE + 1 &&
				m_pShopText->GetAnimeNo(SECOND_LINE) >= TEXT_ANIM_SHOP_MENU_NO)			// 二行目が描画されていたら
			{
				m_pShopText->SetTextNo(ENTERING_LINE + 2, THIRD_LINE, THIRD_LINE);					// 三行目
			}
			else if (!m_nLines && m_pShopText->GetTextNo(FIRST_LINE) != ENTERING_LINE/* &&
				pShopText->currentAnimNo >= TEXT_ANIM_SHOP_MENU_NO*/)		// 描画されていなかったら
			{
				m_pShopText->SetTextNo(ENTERING_LINE, FIRST_LINE, FIRST_LINE);						// 一行目
				m_nLines = 1;													// ループ抑制
			}
			break;
		}
	}
	else if (!m_nBuy)	// カスタマイズパーツのセリフ
	{
		switch (m_nStage)
		{
		case 0:
			switch (m_nCursor)
			{
			case 1:	// ドリンクのセリフ
				if (m_nLines && m_pShopText->GetLineNum() == FIRST_LINE &&
					m_pShopText->GetTextNo(FIRST_LINE) == DRINK_LINE &&
					m_pShopText->GetAnimeNo(FIRST_LINE) >= SELECT_TEXT_ANIM_SHOP_MENU_NO)	// 一行目が描画されていたら
				{
					m_pShopText->SetTextNo(DRINK_LINE + 1, SECOND_LINE, SECOND_LINE);				// 二行目
				}
				else if (m_nLines && m_pShopText->GetLineNum() == SECOND_LINE &&
					m_pShopText->GetTextNo(SECOND_LINE) == DRINK_LINE + 1 &&
					m_pShopText->GetAnimeNo(SECOND_LINE) > SELECT_TEXT_ANIM_SHOP_MENU_NO + 1)	// 二行目が描画されていたら
				{
					m_pShopText->SetTextNo(DRINK_LINE + 2, THIRD_LINE, THIRD_LINE);				// 三行目
				}
				else if (!m_nLines && m_pShopText->GetTextNo(FIRST_LINE) != DRINK_LINE /*&&
					pShopText->currentAnimNo >= TEXT_ANIM_SHOP_MENU_NO*/)// 描画されていなかったら
				{
					m_pShopText->SetTextNo(DRINK_LINE, FIRST_LINE, FIRST_LINE);					// 一行目
					m_nLines = 1;											// ループ抑制
				}
				break;
			case 2:	// ノズル強化のセリフ
				if (m_nLines && m_pShopText->GetLineNum() == FIRST_LINE &&
					m_pShopText->GetTextNo(FIRST_LINE) == NOZZLE_STRONG_LINE &&
					m_pShopText->GetAnimeNo(FIRST_LINE) >= SELECT_TEXT_ANIM_SHOP_MENU_NO)// 一行目が描画されていたら
				{
					m_pShopText->SetTextNo(NOZZLE_STRONG_LINE + 1, SECOND_LINE, SECOND_LINE);					// 二行目
				}
				else if (m_nLines && m_pShopText->GetLineNum() == SECOND_LINE &&
					m_pShopText->GetTextNo(SECOND_LINE) == NOZZLE_STRONG_LINE + 1 &&
					m_pShopText->GetAnimeNo(SECOND_LINE) > SELECT_TEXT_ANIM_SHOP_MENU_NO + 1)// 二行目が描画されていたら
				{
					m_pShopText->SetTextNo(NOZZLE_STRONG_LINE + 2, THIRD_LINE, THIRD_LINE);					// 三行目
				}
				else if (!m_nLines && m_pShopText->GetTextNo(FIRST_LINE) != NOZZLE_STRONG_LINE /*&&
					pShopText->currentAnimNo >= TEXT_ANIM_SHOP_MENU_NO*/)	// 描画されていなかったら
				{
					m_pShopText->SetTextNo(NOZZLE_STRONG_LINE, FIRST_LINE, FIRST_LINE);						// 一行目
					m_nLines = 1;												// ループ抑制
				}
				break;
			case 3:	// 時間延長
				if (m_nLines && m_pShopText->GetLineNum() == FIRST_LINE &&
					m_pShopText->GetTextNo(FIRST_LINE) == TIMER_LINE &&
					m_pShopText->GetAnimeNo(FIRST_LINE) >= SELECT_TEXT_ANIM_SHOP_MENU_NO)		// 一行目が描画されていたら
				{
					m_pShopText->SetTextNo(TIMER_LINE + 1, SECOND_LINE, SECOND_LINE);					// 二行目
				}
				else if (!m_nLines && m_pShopText->GetTextNo(FIRST_LINE) != TIMER_LINE /*&&
					pShopText->currentAnimNo >= TEXT_ANIM_SHOP_MENU_NO*/)	// 描画されていなかったら
				{
					m_pShopText->SetTextNo(TIMER_LINE, FIRST_LINE, FIRST_LINE);						// 一行目
					m_nLines = 1;												// ループ抑制
				}
				break;
			case 4:// クーポン
				if (m_nLines && m_pShopText->GetLineNum() == FIRST_LINE &&
					m_pShopText->GetTextNo(FIRST_LINE) == COUPON_LINE &&
					m_pShopText->GetAnimeNo(FIRST_LINE) >= SELECT_TEXT_ANIM_SHOP_MENU_NO)		// 一行目が描画されていたら
				{
					m_pShopText->SetTextNo(COUPON_LINE + 1, SECOND_LINE, SECOND_LINE);					// 二行目
				}
				else if (m_nLines && m_pShopText->GetLineNum() == SECOND_LINE &&
					m_pShopText->GetTextNo(SECOND_LINE) == COUPON_LINE + 1 &&
					m_pShopText->GetAnimeNo(SECOND_LINE) > SELECT_TEXT_ANIM_SHOP_MENU_NO + 1)		// 二行目が描画されていたら
				{
					m_pShopText->SetTextNo(COUPON_LINE + 2, THIRD_LINE, THIRD_LINE);					// 三行目
				}
				else if (!m_nLines && m_pShopText->GetTextNo(FIRST_LINE) != COUPON_LINE /*&&
					pShopText->currentAnimNo >= TEXT_ANIM_SHOP_MENU_NO*/)	// 描画されていなかったら
				{
					m_pShopText->SetTextNo(COUPON_LINE, FIRST_LINE, FIRST_LINE);						// 一行目
					m_nLines = 1;												// ループ抑制
				}
				break;

			}
			break;
		case 2:
		case 3:
			switch (m_nCursor)
			{
			case 1:	// のこぎりのセリフ
				if (m_nPage == 1 && m_nLines && m_pShopText->GetLineNum() == FIRST_LINE &&
					m_pShopText->GetTextNo(FIRST_LINE) == SAW_LINE &&
					m_pShopText->GetAnimeNo(FIRST_LINE) >= TEXT_ANIM_SHOP_MENU_NO)	// 一行目が描画されていたら
				{
					m_pShopText->SetTextNo(SAW_LINE + 1, SECOND_LINE, SECOND_LINE);				// 二行目
				}
				else if (m_nPage == 1 && m_pShopText->GetLineNum() == SECOND_LINE &&
					m_nLines && m_pShopText->GetTextNo(SECOND_LINE) == SAW_LINE + 1 &&
					m_pShopText->GetAnimeNo(SECOND_LINE) >= TEXT_ANIM_SHOP_MENU_NO)	// 二行目が描画されていたら
				{
					m_pShopText->SetTextNo(SAW_LINE + 2, THIRD_LINE, THIRD_LINE);				// 三行目
				}
				// 購入確認
				else if (m_nPage == 1 && m_pShopText->GetLineNum() == THIRD_LINE &&
					m_nLines && m_pShopText->GetTextNo(THIRD_LINE) == SAW_LINE + 2 &&
					m_pShopText->GetAnimeNo(THIRD_LINE) >= TEXT_ANIM_SHOP_MENU_NO)	// 三行目が描画されていたら
				{
					m_pShopText->SetTextNo(BUY_CHECK_LINE, FIRST_LINE, FORCE_LINE);				// 四行目
				}
				else if (m_nPage == 1 && !m_nLines && m_pShopText->GetTextNo(FIRST_LINE) != SAW_LINE /*&&
					pShopText->currentAnimNo >= TEXT_ANIM_SHOP_MENU_NO*/)// 描画されていなかったら
				{
					m_pShopText->SetTextNo(SAW_LINE, FIRST_LINE, FIRST_LINE);					// 一行目
					m_nLines = 1;											// ループ抑制
				}

				// ブーツ
				if (m_nPage == 2 && m_nLines && m_pShopText->GetLineNum() == FIRST_LINE &&
					m_pShopText->GetTextNo(FIRST_LINE) == BOOTS_LINE &&
					m_pShopText->GetAnimeNo(FIRST_LINE) >= TEXT_ANIM_SHOP_MENU_NO)		// 一行目が描画されていたら
				{
					m_pShopText->SetTextNo(BOOTS_LINE + 1, SECOND_LINE, SECOND_LINE);					// 二行目
				}
				else if (m_nPage == 2 && m_nLines && m_pShopText->GetLineNum() == SECOND_LINE &&
					m_pShopText->GetTextNo(SECOND_LINE) == BOOTS_LINE + 1 &&
					m_pShopText->GetAnimeNo(SECOND_LINE) >= TEXT_ANIM_SHOP_MENU_NO)		// 二行目が描画されていたら
				{
					m_pShopText->SetTextNo(BOOTS_LINE + 2, THIRD_LINE, THIRD_LINE);					// 三行目
				}
				else if (m_nPage == 2 && !m_nLines && m_pShopText->GetTextNo(FIRST_LINE) != BOOTS_LINE /*&&
					pShopText->currentAnimNo >= TEXT_ANIM_SHOP_MENU_NO*/)	// 描画されていなかったら
				{
					m_pShopText->SetTextNo(BOOTS_LINE, FIRST_LINE, FIRST_LINE);						// 一行目
					m_nLines = 1;												// ループ抑制
				}
				break;
			case 2:	// ハンマーセリフ
				if (m_nPage == 1 && m_nLines && m_pShopText->GetLineNum() == FIRST_LINE &&
					m_pShopText->GetTextNo(FIRST_LINE) == HAMMER_LINE &&
					m_pShopText->GetAnimeNo(FIRST_LINE) >= TEXT_ANIM_SHOP_MENU_NO)		// 一行目が描画されていたら
				{
					m_pShopText->SetTextNo(HAMMER_LINE + 1, SECOND_LINE, SECOND_LINE);					// 二行目
				}
				else if (m_nPage == 1 && m_pShopText->GetLineNum() == SECOND_LINE &&
					m_nLines && m_pShopText->GetTextNo(SECOND_LINE) == HAMMER_LINE + 1 &&
					m_pShopText->GetAnimeNo(SECOND_LINE) >= TEXT_ANIM_SHOP_MENU_NO)		// 二行目が描画されていたら
				{
					m_pShopText->SetTextNo(HAMMER_LINE + 2, THIRD_LINE, THIRD_LINE);					// 三行目
				}
				// 購入確認
				else if (m_nPage == 1 && m_nLines && m_pShopText->GetLineNum() == THIRD_LINE &&
					m_pShopText->GetTextNo(THIRD_LINE) == HAMMER_LINE + 2 &&
					m_pShopText->GetAnimeNo(THIRD_LINE) >= TEXT_ANIM_SHOP_MENU_NO)	// 三行目が描画されていたら
				{
					m_pShopText->SetTextNo(BUY_CHECK_LINE, FIRST_LINE, FORCE_LINE);				// 四行目
				}
				else if (m_nPage == 1 && !m_nLines && m_pShopText->GetTextNo(FIRST_LINE) != HAMMER_LINE /*&&
					pShopText->currentAnimNo >= TEXT_ANIM_SHOP_MENU_NO*/)	// 描画されていなかったら
				{
					m_pShopText->SetTextNo(HAMMER_LINE, FIRST_LINE, FIRST_LINE);						// 一行目
					m_nLines = 1;												// ループ抑制
				}
				// 耐熱カスタム
				if (m_nPage == 2 && m_nLines && m_pShopText->GetLineNum() == FIRST_LINE &&
					m_pShopText->GetTextNo(FIRST_LINE) == HEAT_RESISTANT_LINE &&
					m_pShopText->GetAnimeNo(FIRST_LINE) >= TEXT_ANIM_SHOP_MENU_NO)		// 一行目が描画されていたら
				{
					m_pShopText->SetTextNo(HEAT_RESISTANT_LINE + 1, SECOND_LINE, SECOND_LINE);					// 二行目
				}
				else if (m_nPage == 2 && m_nLines && m_pShopText->GetLineNum() == SECOND_LINE &&
					m_pShopText->GetTextNo(SECOND_LINE) == HEAT_RESISTANT_LINE + 1 &&
					m_pShopText->GetAnimeNo(SECOND_LINE) >= TEXT_ANIM_SHOP_MENU_NO)		// 二行目が描画されていたら
				{
					m_pShopText->SetTextNo(HEAT_RESISTANT_LINE + 2, THIRD_LINE, THIRD_LINE);					// 三行目
				}
				// 購入確認
				else if (m_nPage == 2 && m_nLines && m_pShopText->GetLineNum() == THIRD_LINE &&
					m_pShopText->GetTextNo(THIRD_LINE) == HEAT_RESISTANT_LINE + 2 &&
					m_pShopText->GetAnimeNo(THIRD_LINE) >= TEXT_ANIM_SHOP_MENU_NO)	// 三行目が描画されていたら
				{
					m_pShopText->SetTextNo(BUY_CHECK_LINE, FIRST_LINE, FORCE_LINE);				// 四行目
				}
				else if (m_nPage == 2 && !m_nLines && m_pShopText->GetTextNo(FIRST_LINE) != HEAT_RESISTANT_LINE /*&&
					pShopText->currentAnimNo >= TEXT_ANIM_SHOP_MENU_NO*/)	// 描画されていなかったら
				{
					m_pShopText->SetTextNo(HEAT_RESISTANT_LINE, FIRST_LINE, FIRST_LINE);						// 一行目
					m_nLines = 1;												// ループ抑制
				}
				break;
			case 3:	// ドリルセリフ
				if (m_nLines && m_pShopText->GetLineNum() == FIRST_LINE &&
					m_pShopText->GetTextNo(FIRST_LINE) == DRILL_LINE &&
					m_pShopText->GetAnimeNo(FIRST_LINE) >= TEXT_ANIM_SHOP_MENU_NO)		// 一行目が描画されていたら
				{
					m_pShopText->SetTextNo(DRILL_LINE + 1, SECOND_LINE, SECOND_LINE);					// 二行目
				}
				else if (m_nLines && m_pShopText->GetLineNum() == SECOND_LINE &&
					m_pShopText->GetTextNo(SECOND_LINE) == DRILL_LINE + 1 &&
					m_pShopText->GetAnimeNo(SECOND_LINE) > TEXT_ANIM_SHOP_MENU_NO)		// 二行目が描画されていたら
				{
					m_pShopText->SetTextNo(DRILL_LINE + 2, THIRD_LINE, THIRD_LINE);					// 三行目
				}
				// 購入確認
				else if (m_nPage == 1 && m_nLines && m_pShopText->GetLineNum() == THIRD_LINE &&
					m_pShopText->GetTextNo(THIRD_LINE) == DRILL_LINE + 2 &&
					m_pShopText->GetAnimeNo(THIRD_LINE) >= TEXT_ANIM_SHOP_MENU_NO)	// 三行目が描画されていたら
				{
					m_pShopText->SetTextNo(BUY_CHECK_LINE, FIRST_LINE, FORCE_LINE);				// 四行目
				}
				else if (!m_nLines && m_pShopText->GetTextNo(FIRST_LINE) != DRILL_LINE /*&&
					pShopText->currentAnimNo >= TEXT_ANIM_SHOP_MENU_NO*/)	// 描画されていなかったら
				{
					m_pShopText->SetTextNo(DRILL_LINE, FIRST_LINE, FIRST_LINE);						// 一行目
					m_nLines = 1;												// ループ抑制
				}
				break;
			case 4:	//ノズル
				if (m_nLines && m_pShopText->GetLineNum() == FIRST_LINE &&
					m_pShopText->GetTextNo(FIRST_LINE) == NOZZLE_LINE &&
					m_pShopText->GetAnimeNo(FIRST_LINE) >= TEXT_ANIM_SHOP_MENU_NO)		// 一行目が描画されていたら
				{
					m_pShopText->SetTextNo(NOZZLE_LINE + 1, SECOND_LINE, SECOND_LINE);					// 二行目
				}
				else if (m_nLines && m_pShopText->GetLineNum() == SECOND_LINE &&
					m_pShopText->GetTextNo(SECOND_LINE) == NOZZLE_LINE + 1 &&
					m_pShopText->GetAnimeNo(SECOND_LINE) >= TEXT_ANIM_SHOP_MENU_NO)		// 二行目が描画されていたら
				{
					m_pShopText->SetTextNo(NOZZLE_LINE + 2, THIRD_LINE, THIRD_LINE);					// 三行目
				}
				else if (!m_nLines && m_pShopText->GetTextNo(FIRST_LINE) != NOZZLE_LINE /*&&
					pShopText->currentAnimNo >= TEXT_ANIM_SHOP_MENU_NO*/)	// 描画されていなかったら
				{
					m_pShopText->SetTextNo(NOZZLE_LINE, FIRST_LINE, FIRST_LINE);						// 一行目
					m_nLines = 1;												// ループ抑制
				}
				break;

			}
			break;
		}
	}
	else	// 購入時のセリフ
	{
		switch (m_nStage)
		{
		case 0:
			if (m_nLines && m_pShopText->GetLineNum() == FIRST_LINE &&
				m_pShopText->GetTextNo(FIRST_LINE) == SELECT_BUY_LINE &&
				m_pShopText->GetAnimeNo(FIRST_LINE) >= TEXT_ANIM_SHOP_MENU_NO)		// 一行目が描画されていたら
			{
				m_pShopText->SetTextNo(SELECT_BUY_LINE + 1, SECOND_LINE, SECOND_LINE);	// 二行目
			}
			else if (!m_nLines && m_pShopText->GetTextNo(FIRST_LINE) != SELECT_BUY_LINE/* &&
				pShopText->currentAnimNo >= TEXT_ANIM_SHOP_MENU_NO*/)// 描画されていなかったら
			{
				m_pShopText->SetTextNo(SELECT_BUY_LINE, FIRST_LINE, FIRST_LINE);	// 一行目
				m_nLines = 1;					// ループ抑制
			}
			break;
		case 2:
		case 3:
			if (m_nLines && m_pShopText->GetLineNum() == FIRST_LINE &&
				m_pShopText->GetTextNo(FIRST_LINE) == BUY_LINE &&
				m_pShopText->GetAnimeNo(FIRST_LINE) >= TEXT_ANIM_SHOP_MENU_NO)		// 一行目が描画されていたら
			{
				m_pShopText->SetTextNo(BUY_LINE + 1, SECOND_LINE, SECOND_LINE);	// 二行目
			}
			else if (!m_nLines && m_pShopText->GetTextNo(FIRST_LINE) != BUY_LINE/* &&
				pShopText->currentAnimNo >= TEXT_ANIM_SHOP_MENU_NO*/)// 描画されていなかったら
			{
				m_pShopText->SetTextNo(BUY_LINE, FIRST_LINE, FIRST_LINE);	// 一行目
				m_nLines = 1;					// ループ抑制
			}
			break;
		}
	}

	m_pShopText->Update();	// テキスト更新
}

void CShopMenu::MoneyEnough()									// お金が足りているか判定を取る
{
	//----カーソルとお金の判定を取る----
	if (m_nPage == 1)	// 1ページ目だったら
	{
		// アイコンがあるかどうか
		if (m_nCursor > m_nMaxCustom)
		{
			m_nCursor = m_noldCursor;	// 移動できなかったら元の位置に戻す
		}

		//----所持金が足りているか----
		for (int i = 0; i < m_nMaxCustom; i++)
		{
			if (i >= 4)
			{
				break;
			}
			if (m_nStage != 0)
			{
				if (m_pnMoney && m_pPrice[i]->GetPrice() > *m_pnMoney)	// 所持金が足りない
				{
					m_pShopIcon[i * 4 + i]->SetColor(0.5f, 0.5f, 0.5f, 1.0f);	// 色設定
					m_pShopIcon[i * 4 + i + 1]->SetColor(0.5f, 0.5f, 0.5f, 1.0f);	// 色設定
					m_pShopIcon[i * 4 + i + 2]->SetColor(0.5f, 0.5f, 0.5f, 1.0f);	// 色設定
					m_nEnough[i] = 0;											// 足りていないふらぐ
				}
				else if (m_pnMoney)										// 所持金が足りている
				{
					m_pShopIcon[i * 4 + i]->SetColor(1.0f, 1.0f, 1.0f, 1.0f);	// 色設定
					m_pShopIcon[i * 4 + i + 1]->SetColor(1.0f, 1.0f, 1.0f, 1.0f);	// 色設定
					m_pShopIcon[i * 4 + i + 2]->SetColor(1.0f, 1.0f, 1.0f, 1.0f);	// 色設定
					m_nEnough[i] = 1;											// 足りているフラグ
				}
			}
			else
			{
				if (m_pnMoney && m_pPrice[i]->GetPrice() > *m_pnMoney)	// 所持金が足りない
				{
					m_pShopIcon[i * 2 + i]->SetColor(0.5f, 0.5f, 0.5f, 1.0f);	// 色設定
					m_pShopIcon[i * 2 + i + 1]->SetColor(0.5f, 0.5f, 0.5f, 1.0f);	// 色設定
					m_pShopIcon[i * 2 + i + 2]->SetColor(0.5f, 0.5f, 0.5f, 1.0f);	// 色設定
					m_nEnough[i] = 0;											// 足りていないふらぐ
				}
				else if (m_pnMoney)										// 所持金が足りている
				{
					m_pShopIcon[i * 2 + i]->SetColor(1.0f, 1.0f, 1.0f, 1.0f);	// 色設定
					m_pShopIcon[i * 2 + i + 1]->SetColor(1.0f, 1.0f, 1.0f, 1.0f);	// 色設定
					m_pShopIcon[i * 2 + i + 2]->SetColor(1.0f, 1.0f, 1.0f, 1.0f);	// 色設定
					m_nEnough[i] = 1;											// 足りているフラグ
				}
			}
		}
	}
	else if (m_nPage == 2)	// 1ページ目だったら
	{
		// アイコンがあるかどうか
		if (m_nCursor > m_nMaxCustom - 4)
		{
			m_nCursor = m_noldCursor;	// 移動できなかったら元の位置に戻す
		}

		//----所持金が足りているか----
		for (int i = 4; i < m_nMaxCustom; i++)
		{
			if (i >= 8)
			{
				break;
			}
			if (m_nStage != 0)
			{
				if (m_pnMoney && m_pPrice[i]->GetPrice() > *m_pnMoney)	// 所持金が足りない
				{
					m_pShopIcon[i * 4 + i]->SetColor(0.5f, 0.5f, 0.5f, 1.0f);	// 色設定
					m_pShopIcon[i * 4 + i + 1]->SetColor(0.5f, 0.5f, 0.5f, 1.0f);	// 色設定
					m_pShopIcon[i * 4 + i + 2]->SetColor(0.5f, 0.5f, 0.5f, 1.0f);	// 色設定
					m_nEnough[i] = 0;											// 足りていないふらぐ
				}
				else if (m_pnMoney)										// 所持金が足りている
				{
					m_pShopIcon[i * 4 + i]->SetColor(1.0f, 1.0f, 1.0f, 1.0f);	// 色設定
					m_pShopIcon[i * 4 + i + 1]->SetColor(1.0f, 1.0f, 1.0f, 1.0f);	// 色設定
					m_pShopIcon[i * 4 + i + 2]->SetColor(1.0f, 1.0f, 1.0f, 1.0f);	// 色設定
					m_nEnough[i] = 1;											// 足りているフラグ
				}
			}
			else
			{
				if (m_pnMoney && m_pPrice[i]->GetPrice() > *m_pnMoney)	// 所持金が足りない
				{
					m_pShopIcon[i * 2 + i]->SetColor(0.5f, 0.5f, 0.5f, 1.0f);	// 色設定
					m_pShopIcon[i * 2 + i + 1]->SetColor(0.5f, 0.5f, 0.5f, 1.0f);	// 色設定
					m_pShopIcon[i * 2 + i + 2]->SetColor(0.5f, 0.5f, 0.5f, 1.0f);	// 色設定
					m_nEnough[i] = 0;											// 足りていないふらぐ
				}
				else if (m_pnMoney)										// 所持金が足りている
				{
					m_pShopIcon[i * 2 + i]->SetColor(1.0f, 1.0f, 1.0f, 1.0f);	// 色設定
					m_pShopIcon[i * 2 + i + 1]->SetColor(1.0f, 1.0f, 1.0f, 1.0f);	// 色設定
					m_pShopIcon[i * 2 + i + 2]->SetColor(1.0f, 1.0f, 1.0f, 1.0f);	// 色設定
					m_nEnough[i] = 1;											// 足りているフラグ
				}
			}
		}
	}
}

void CShopMenu::IconDraw()										// ショップアイコンの描画
{
	int ntemp = 0;	// 配列参照用
	int nRoop = m_nMaxCustom;	// ループ用
	int nPrice = 0;
	// アイコン仕分け用
	int nNozzle = -1;
	int nBoots = -1;
	int nHeat = -1;
	switch (m_nStage)
	{
	case 0:
		nBoots = 0;
		break;
		//case 1:
	case 2:
	case 3:
		nNozzle = 4;	// ノズル強化の位置
		break;
	}

	switch (m_nPage)
	{
	case 2:
		ntemp = 20;
		nRoop -= 4;
		nPrice = 4;
		nBoots = 5;		// ブーツの位置
		nHeat = 6;		// 耐熱カスタムの位置
		break;
	}

	if (m_nStage != 0)
	{
		for (int i = 0; i < nRoop; i++)
		{
			if (i > 3) break;	// 1ページ分以上になったら終了
			// 1ページ分のアイコン描画
			// レベル3段階あるものの専用処理
			if ((m_nCursor == i + 1 && m_anBuy[i] <= 2 && m_nBuy && (m_anBuyCustom == Custom::SAW ||
				m_anBuyCustom == Custom::DRILL || m_anBuyCustom == Custom::HAMMER)) ||
				m_anBuy[i + (4 * (m_nPage - 1))] == 3 && m_nPage == 1)	// 買ったor売り切れか
			{
				// 既に買っていたら
				if (m_nCursor == i + 1 && m_anBuy[i] == 3)			// カーソルが左下か
				{
					if (m_fSizeRatio[i] > SIZE_RATIO && !m_naMinRatio[i])	// 縮小仕切ったか
					{
						m_fSizeRatio[i] -= 0.06f;	// 縮小
					}
					else
					{
						m_pShopIcon[ntemp + i * ICON_KIND]->SetColor(0.3f, 0.3f, 0.3f, 1.0f);	// 色設定
						m_pShopIcon[ntemp + 2 + i * ICON_KIND]->SetColor(0.3f, 0.3f, 0.3f, 1.0f);	// 色設定
						m_fSizeRatio[i] = SIZE_RATIO;	// 最小倍率
						m_pShopIcon[ntemp + 3 + i * ICON_KIND]->SetSizeRatio(m_fSizeRatio[i]);	// 倍率設定
						m_naMinRatio[i] = 1;			// フラグ上げ
					}
					m_pShopIcon[ntemp + i * ICON_KIND]->Draw();	// アイコン描画
					m_pShopIcon[ntemp + 2 + i * ICON_KIND]->Draw();	// カスタマイズパーツ描画
					m_pShopIcon[ntemp + 4 + i * ICON_KIND]->SetSizeRatio(m_fSizeRatio[i]);	// 倍率設定
					m_pShopIcon[ntemp + 4 + i * ICON_KIND]->Draw();	// 選択されている色のアイコンを描画
				}
				else if (m_anBuy[i] == 3)
				{
					m_fSizeRatio[i] = SIZE_RATIO;	// 最小倍率
					m_pShopIcon[ntemp + 3 + i * ICON_KIND]->SetSizeRatio(m_fSizeRatio[i]);	// 倍率設定
					m_pShopIcon[ntemp + i * ICON_KIND]->SetColor(0.3f, 0.3f, 0.3f, 1.0f);	// 色設定
					m_pShopIcon[ntemp + 2 + i * ICON_KIND]->SetColor(0.3f, 0.3f, 0.3f, 1.0f);	// 色設定
					m_pShopIcon[ntemp + i * ICON_KIND]->Draw();	// アイコン描画
					m_pShopIcon[ntemp + 2 + i * ICON_KIND]->Draw();	// カスタマイズパーツ描画
					m_pShopIcon[ntemp + 3 + i * ICON_KIND]->Draw();	// 売り切れアイコン描画
				}
				if (!m_anBuy[i] && m_anBuyCustom >= 0)			// 初めて買われたか
				{
					m_anBuy[i] = m_nBuy;	// 買った情報を退避
					m_nBuy = 2;
					delete m_pPrice[nPrice + i];
					m_pPrice[nPrice + i] = nullptr;
					switch (m_anBuyCustom)
					{
					case Custom::SAW:
						m_pPrice[nPrice + i] = new CPrice(m_anPricePos[nPrice + i].x, m_anPricePos[nPrice + i].y,
							0.0f, PRICE_SAW_LEVEL2);
						OneCoupon(nPrice + i);	// 値段調整
						break;
					case Custom::DRILL:
						m_pPrice[nPrice + i] = new CPrice(m_anPricePos[nPrice + i].x, m_anPricePos[nPrice + i].y,
							0.0f, PRICE_DRILL_LEVEL2);
						OneCoupon(nPrice + i);	// 値段調整
						break;
					case Custom::HAMMER:
						m_pPrice[nPrice + i] = new CPrice(m_anPricePos[nPrice + i].x, m_anPricePos[nPrice + i].y,
							0.0f, PRICE_HAMMER_LEVEL2);
						OneCoupon(nPrice + i);	// 値段調整
						break;
					}
					m_anBuyCustom = -1;
				}
				else if (m_anBuy[i] == 1 && m_anBuyCustom >= 0)
				{
					m_anBuy[i] += m_nBuy;	// 買った情報を退避
					m_nBuy = 2;
					delete m_pPrice[nPrice + i];
					m_pPrice[nPrice + i] = nullptr;
					switch (m_anBuyCustom)
					{
					case Custom::SAW:
						m_pPrice[nPrice + i] = new CPrice(m_anPricePos[nPrice + i].x, m_anPricePos[nPrice + i].y,
							0.0f, PRICE_SAW_LEVEL3);
						OneCoupon(nPrice + i);	// 値段調整
						break;
					case Custom::DRILL:
						m_pPrice[nPrice + i] = new CPrice(m_anPricePos[nPrice + i].x, m_anPricePos[nPrice + i].y,
							0.0f, PRICE_DRILL_LEVEL3);
						OneCoupon(nPrice + i);	// 値段調整
						break;
					case Custom::HAMMER:
						m_pPrice[nPrice + i] = new CPrice(m_anPricePos[nPrice + i].x, m_anPricePos[nPrice + i].y,
							0.0f, PRICE_HAMMER_LEVEL3);
						OneCoupon(nPrice + i);	// 値段調整
						break;
					}
					m_anBuyCustom = -1;
				}
				else if (m_anBuy[i] == 2 && m_anBuyCustom >= 0)
				{
					m_anBuy[i] += m_nBuy;	// 買った情報を退避
					m_nBuy = 2;
					m_anBuyCustom = -1;
				}
			}
			// レベル2段階あるものの専用処理
			else if ((m_nCursor == i + 1 && m_anBuy[i] <= 1 && m_nBuy && m_nNozzle) ||
				m_anBuy[i + (4 * (m_nPage - 1))] == 2 && i + 1 == nNozzle)	// 買ったor売り切れか
			{
				// 既に買っていたら
				if (m_nCursor == i + 1 && m_anBuy[i] == 2)			// カーソルが左下か
				{
					if (m_fSizeRatio[i] > SIZE_RATIO && !m_naMinRatio[i])	// 縮小仕切ったか
					{
						m_fSizeRatio[i] -= 0.06f;	// 縮小
					}
					else
					{
						m_pShopIcon[ntemp + i * ICON_KIND]->SetColor(0.3f, 0.3f, 0.3f, 1.0f);	// 色設定
						m_pShopIcon[ntemp + 2 + i * ICON_KIND]->SetColor(0.3f, 0.3f, 0.3f, 1.0f);	// 色設定
						m_fSizeRatio[i] = SIZE_RATIO;	// 最小倍率
						m_pShopIcon[ntemp + 3 + i * ICON_KIND]->SetSizeRatio(m_fSizeRatio[i]);	// 倍率設定
						m_naMinRatio[i] = 1;			// フラグ上げ
					}
					m_pShopIcon[ntemp + i * ICON_KIND]->Draw();	// アイコン描画
					m_pShopIcon[ntemp + 2 + i * ICON_KIND]->Draw();	// カスタマイズパーツ描画
					m_pShopIcon[ntemp + 4 + i * ICON_KIND]->SetSizeRatio(m_fSizeRatio[i]);	// 倍率設定
					m_pShopIcon[ntemp + 4 + i * ICON_KIND]->Draw();	// 選択されている色のアイコンを描画
				}
				else if (m_anBuy[i] == 2)
				{
					m_fSizeRatio[i] = SIZE_RATIO;	// 最小倍率
					m_pShopIcon[ntemp + 3 + i * ICON_KIND]->SetSizeRatio(m_fSizeRatio[i]);	// 倍率設定
					m_pShopIcon[ntemp + i * ICON_KIND]->SetColor(0.3f, 0.3f, 0.3f, 1.0f);	// 色設定
					m_pShopIcon[ntemp + 2 + i * ICON_KIND]->SetColor(0.3f, 0.3f, 0.3f, 1.0f);	// 色設定
					m_pShopIcon[ntemp + i * ICON_KIND]->Draw();	// アイコン描画
					m_pShopIcon[ntemp + 2 + i * ICON_KIND]->Draw();	// カスタマイズパーツ描画
					m_pShopIcon[ntemp + 3 + i * ICON_KIND]->Draw();	// 売り切れアイコン描画
				}
				if (!m_anBuy[i] && m_nNozzle)			// 初めて買われたか
				{
					m_anBuy[i] = m_nBuy;	// 買った情報を退避
					m_nBuy = 2;
					m_nNozzle = 0;
					delete m_pPrice[nPrice + i];
					m_pPrice[nPrice + i] = nullptr;
					m_pPrice[nPrice + i] = new CPrice(LEFT_PRICE_POSX + PRICE_WIDTHX - 40.0f,					// 価格情報
						LEFT_PRICE_POSY + PRICE_WIDTHY,
						0.0f, PRICE_NOZZLE_LEVEL3);
					OneCoupon(nPrice + i);	// 値段調整
				}
				else if (m_anBuy[i] == 1 && m_nNozzle)
				{
					m_anBuy[i] += m_nBuy;	// 買った情報を退避
					m_nBuy = 2;
					m_nNozzle = 0;
				}
			}
			else if ((m_nCursor == i + 1 && !m_anBuy[i + (4 * (m_nPage - 1))] && m_nBuy && (m_anBuyCustom == Custom::BOOTS ||
				m_anBuyCustom == Custom::HEAT_RESISTANT)) ||
				(m_anBuy[i + (4 * (m_nPage - 1))] && (i == nBoots - 5 || i == nHeat - 5)))	// カーソルがあり買ったor売り切れか
			{
				// その他
				// 既に買っていてカーソルがそこにあったら
				if (m_nCursor == i + 1 && (i == nBoots - 5 || i == nHeat - 5))
				{
					if (m_fSizeRatio[i + (4 * (m_nPage - 1))] > SIZE_RATIO && !m_naMinRatio[i + (4 * (m_nPage - 1))])	// 縮小仕切ったか
					{
						m_fSizeRatio[i + (4 * (m_nPage - 1))] -= 0.06f;	// 縮小
					}
					else
					{
						m_pShopIcon[ntemp + i * ICON_KIND]->SetColor(0.3f, 0.3f, 0.3f, 1.0f);	// 色設定
						m_pShopIcon[ntemp + 2 + i * ICON_KIND]->SetColor(0.3f, 0.3f, 0.3f, 1.0f);	// 色設定
						m_fSizeRatio[i + (4 * (m_nPage - 1))] = SIZE_RATIO;	// 最小倍率
						m_pShopIcon[ntemp + 3 + i * ICON_KIND]->SetSizeRatio(m_fSizeRatio[i + (4 * (m_nPage - 1))]);	// 倍率設定
						m_naMinRatio[i + (4 * (m_nPage - 1))] = 1;			// フラグ上げ
					}
					m_pShopIcon[ntemp + i * ICON_KIND]->Draw();	// アイコン描画
					m_pShopIcon[ntemp + 2 + i * ICON_KIND]->Draw();	// カスタマイズパーツ描画
					m_pShopIcon[ntemp + 4 + i * ICON_KIND]->SetSizeRatio(m_fSizeRatio[i + (4 * (m_nPage - 1))]);	// 倍率設定
					m_pShopIcon[ntemp + 4 + i * ICON_KIND]->Draw();	// 選択されている色のアイコンを描画
				}
				// カーソルがなかったら
				// その他のカスタムアイコン
				else if (i == nBoots - 5 || i == nHeat - 5)
				{
					m_fSizeRatio[i + (4 * (m_nPage - 1))] = SIZE_RATIO;	// 最小倍率
					m_pShopIcon[ntemp + 3 + i * ICON_KIND]->SetSizeRatio(m_fSizeRatio[i + (4 * (m_nPage - 1))]);	// 倍率設定
					m_pShopIcon[ntemp + i * ICON_KIND]->SetColor(0.3f, 0.3f, 0.3f, 1.0f);	// 色設定
					m_pShopIcon[ntemp + 2 + i * ICON_KIND]->SetColor(0.3f, 0.3f, 0.3f, 1.0f);	// 色設定
					m_pShopIcon[ntemp + i * ICON_KIND]->Draw();	// アイコン描画
					m_pShopIcon[ntemp + 2 + i * ICON_KIND]->Draw();	// カスタマイズパーツ描画
					m_pShopIcon[ntemp + 3 + i * ICON_KIND]->Draw();	// 売り切れアイコン描画
				}
				// その他が初めて買われたか
				if (!m_anBuy[i + (4 * (m_nPage - 1))])
				{
					m_anBuy[i + (4 * (m_nPage - 1))] = m_nBuy;	// 買った情報を退避
					m_nBuy = 2;
				}

			}
			// まだ買ってなくて
			// カーソルがあるか
			else if (m_nCursor == i + 1)
			{
				// カスタムパーツ拡縮
				if (!m_nMAXRatio)	// 最大倍率じゃなかったら
				{
					m_fRatio += SHOP_RATIO;		// 倍率設定
					if (m_fRatio >= ENOUGH_MAX_RATIO && m_nEnough[i])	// 所持金が足りて最大倍率を超えたら
					{
						m_nMAXRatio ^= 1;	// フラグ上げ
					}
					else if (m_fRatio >= NOT_ENOUGH_MAX_RATIO && !m_nEnough[i])	// 所持金が足りなくて最大倍率を超えたら
					{
						m_nMAXRatio ^= 1;	// フラグ上げ
					}
				}
				// 所持金が足りていたら
				else
				{
					m_fRatio -= SHOP_RATIO;		// 倍率設定
					if (m_fRatio <= ENOUGH_MIN_RATIO && m_nEnough[i])	// 所持金が足りて最小倍率より小さくなったら
					{
						m_nMAXRatio ^= 1;	// フラグ上げ
					}
					else if (m_fRatio <= NOT_ENOUGH_MIN_RATIO && !m_nEnough[i])	// 所持金が足りなくて最小倍率を超えたら
					{
						m_nMAXRatio ^= 1;	// フラグ上げ
					}
				}
				m_pShopIcon[ntemp + 1 + i * ICON_KIND]->Draw();		// 選択されている色のアイコンを描画
				m_pShopIcon[ntemp + 2 + i * ICON_KIND]->SetSizeRatio(m_fRatio);	// 倍率設定
				m_pShopIcon[ntemp + 2 + i * ICON_KIND]->Draw();		// カスタマイズパーツ描画
				m_pShopText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);	// テキスト色設定
				m_pShopText->Draw();		// カスタムの説明のセリフを描画
			}
			else
			{
				m_pShopIcon[ntemp + i * ICON_KIND]->Draw();		// アイコン描画
				m_pShopIcon[ntemp + 2 + i * ICON_KIND]->ResetSize();	// サイズリセット
				m_pShopIcon[ntemp + 2 + i * ICON_KIND]->Draw();		// カスタマイズパーツ描画
			}
			m_pPrice[nPrice + i]->SetColor(1.0f, 1.0f, 1.0f, 1.0f);		// 値段の色設定
			m_pPrice[nPrice + i]->Draw();							// 値段白色で描画
		}
	}
	// セレクトシーンショップ
	else
	{
		for (int i = 0; i < nRoop; i++)
		{
			if (i > 3) break;	// 1ページ分以上になったら終了
			// アイテム
			// 1ページ分のアイコン描画
			if ((m_nCursor == i + 1 && !m_anBuy[i] && m_nBuy) ||
				m_anBuy[i])	// カーソルがあり買ったor売り切れか
			{
				// 既に買っていてカーソルがそこにあったら
				if (m_nCursor == i + 1)
				{
					m_pShopIcon[ntemp + 1 + i * SELECT_ICON_KIND]->SetColor(0.3f, 0.3f, 0.3f, 1.0f);	// 色設定
					m_pShopIcon[ntemp + 2 + i * SELECT_ICON_KIND]->SetColor(0.3f, 0.3f, 0.3f, 1.0f);	// 色設定
					m_pShopIcon[ntemp + 1 + i * SELECT_ICON_KIND]->Draw();	// アイコン描画
					m_pShopIcon[ntemp + 2 + i * SELECT_ICON_KIND]->Draw();	// カスタマイズパーツ描画
				}
				// カーソルがなかったら
				else
				{
					m_pShopIcon[ntemp + i * SELECT_ICON_KIND]->SetColor(0.3f, 0.3f, 0.3f, 1.0f);	// 色設定
					m_pShopIcon[ntemp + 2 + i * SELECT_ICON_KIND]->SetColor(0.3f, 0.3f, 0.3f, 1.0f);	// 色設定
					m_pShopIcon[ntemp + i * SELECT_ICON_KIND]->Draw();	// アイコン描画
					m_pShopIcon[ntemp + 2 + i * SELECT_ICON_KIND]->Draw();	// カスタマイズパーツ描画
				}
				// アイテムが初めて買われたか
				if (!m_anBuy[i])
				{
					m_anBuy[i] = m_nBuy;	// 買った情報を退避
					m_nBuy = 2;
				}

			}
			// まだ買われてない物で
			// カーソルがあるか
			else if (m_nCursor == i + 1)
			{
				// アイテム拡縮
				if (!m_nMAXRatio)	// 最大倍率じゃなかったら
				{
					m_fRatio += SHOP_RATIO;		// 倍率設定
					if (m_fRatio >= ENOUGH_MAX_RATIO && m_nEnough[i])	// 所持金が足りて最大倍率を超えたら
					{
						m_nMAXRatio ^= 1;	// フラグ上げ
					}
					else if (m_fRatio >= NOT_ENOUGH_MAX_RATIO && !m_nEnough[i])	// 所持金が足りなくて最大倍率を超えたら
					{
						m_nMAXRatio ^= 1;	// フラグ上げ
					}
				}
				// 所持金が足りていたら
				else
				{
					m_fRatio -= SHOP_RATIO;		// 倍率設定
					if (m_fRatio <= ENOUGH_MIN_RATIO && m_nEnough[i])	// 所持金が足りて最小倍率より小さくなったら
					{
						m_nMAXRatio ^= 1;	// フラグ上げ
					}
					else if (m_fRatio <= NOT_ENOUGH_MIN_RATIO && !m_nEnough[i])	// 所持金が足りなくて最小倍率を超えたら
					{
						m_nMAXRatio ^= 1;	// フラグ上げ
					}
				}
				m_pShopIcon[ntemp + 1 + i * SELECT_ICON_KIND]->Draw();		// 選択されている色のアイコンを描画
				m_pShopIcon[ntemp + 2 + i * SELECT_ICON_KIND]->SetSizeRatio(m_fRatio);	// 倍率設定
				m_pShopIcon[ntemp + 2 + i * SELECT_ICON_KIND]->Draw();		// カスタマイズパーツ描画
				m_pShopText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);			// テキスト色設定
				m_pShopText->Draw();		// カスタムの説明のセリフを描画
			}
			// 買ってなくてカーソルもあっていなかったら
			else
			{
				m_pShopIcon[ntemp + i * SELECT_ICON_KIND]->Draw();		// アイコン描画
				m_pShopIcon[ntemp + 2 + i * SELECT_ICON_KIND]->ResetSize();	// サイズリセット
				m_pShopIcon[ntemp + 2 + i * SELECT_ICON_KIND]->Draw();		// カスタマイズパーツ描画
			}
			m_pPrice[nPrice + i]->SetColor(1.0f, 1.0f, 1.0f, 1.0f);		// 値段の色設定
			m_pPrice[nPrice + i]->Draw();							// 値段白色で描画
		}
	}
}

void CShopMenu::PageSetDraw()
{
	//----スラッシュ---
	m_BaseShopMenu[5].pos = DirectX::XMFLOAT3(590.0f, 160.0f, 0.0f);	// ページ表記の区切り部分

	for (int i = 1; i < 3; i++)
	{
		switch (i)
		{
		case 1:
			switch (m_nPage)	// 現在の開いているページ
			{
			case 1:				// 1ページ目
				//----1----
				m_BaseShopMenu[6].size = DirectX::XMFLOAT2(m_BaseShopMenu[5].pTexture->GetWidth() * 0.07f,
					m_BaseShopMenu[5].pTexture->GetHeight() * 0.07f);						// サイズ
				m_BaseShopMenu[6].pos = DirectX::XMFLOAT3(575.0f, 152.0f, 0.0f);				// 座標
				m_BaseShopMenu[6].sizeTexCoord = DirectX::XMFLOAT2(1.0f / PAGE_SPLIT_X,
					1.0f / PAGE_SPLIT_Y);													// テクスチャサイズ設定
				m_BaseShopMenu[6].posTexCoord = DirectX::XMFLOAT2(m_BaseShopMenu[6].sizeTexCoord.x * (1 % PAGE_SPLIT_X)
					, m_BaseShopMenu[6].sizeTexCoord.y * (1 / PAGE_SPLIT_X));				// テクスチャ座標設定
				break;

			case 2:				// 2ページ目
				//----2----
				m_BaseShopMenu[6].size = DirectX::XMFLOAT2(m_BaseShopMenu[5].pTexture->GetWidth() * 0.07f,
					m_BaseShopMenu[5].pTexture->GetHeight() * 0.07f);						// サイズ
				m_BaseShopMenu[6].pos = DirectX::XMFLOAT3(575.0f, 152.0f, 0.0f);				// 座標
				m_BaseShopMenu[6].sizeTexCoord = DirectX::XMFLOAT2(1.0f / PAGE_SPLIT_X,
					1.0f / PAGE_SPLIT_Y);													// テクスチャサイズ設定
				m_BaseShopMenu[6].posTexCoord = DirectX::XMFLOAT2(m_BaseShopMenu[6].sizeTexCoord.x * (2 % PAGE_SPLIT_X)
					, m_BaseShopMenu[6].sizeTexCoord.y * (2 / PAGE_SPLIT_X));				// テクスチャ座標設定
				break;
			}
			break;
		case 2:
			switch (m_nTotalPage)	// 最大ページ数
			{
			case 1:
				//----1----		// 最大1ページ
				m_BaseShopMenu[7].size = DirectX::XMFLOAT2(m_BaseShopMenu[5].pTexture->GetWidth() * 0.07f,
					m_BaseShopMenu[5].pTexture->GetHeight() * 0.07f);						// サイズ
				m_BaseShopMenu[7].pos = DirectX::XMFLOAT3(613.0f, 176.0f, 0.0f);			// 座標
				m_BaseShopMenu[7].sizeTexCoord = DirectX::XMFLOAT2(1.0f / PAGE_SPLIT_X,
					1.0f / PAGE_SPLIT_Y);													// テクスチャサイズ設定
				m_BaseShopMenu[7].posTexCoord = DirectX::XMFLOAT2(m_BaseShopMenu[7].sizeTexCoord.x * (1 % PAGE_SPLIT_X)
					, m_BaseShopMenu[7].sizeTexCoord.y * (1 / PAGE_SPLIT_X));				// テクスチャ座標設定
				break;
			case 2:
				//----2----		// 最大2ページ
				m_BaseShopMenu[7].size = DirectX::XMFLOAT2(m_BaseShopMenu[5].pTexture->GetWidth() * 0.07f,
					m_BaseShopMenu[5].pTexture->GetWidth() * 0.07f);						// サイズ
				m_BaseShopMenu[7].pos = DirectX::XMFLOAT3(613.0f, 176.0f, 0.0f);			// 座標
				m_BaseShopMenu[7].sizeTexCoord = DirectX::XMFLOAT2(1.0f / PAGE_SPLIT_X,
					1.0f / PAGE_SPLIT_Y);													// テクスチャサイズ設定
				m_BaseShopMenu[7].posTexCoord = DirectX::XMFLOAT2(m_BaseShopMenu[7].sizeTexCoord.x * (2 % PAGE_SPLIT_X)
					, m_BaseShopMenu[7].sizeTexCoord.y * (2 / PAGE_SPLIT_X));				// テクスチャ座標設定
				break;
			}
			break;
		}
	}
}

// 複数用
void CShopMenu::ALLCoupon()			// 値段表示調整関数
{
	// ステージごとに処理分け
	switch (m_nStage)
	{
	case 2:	// 2ステージ
		for (int i = 0; i < m_nMaxCustom; i++)	// ステージ内最大数分
		{
			// 値段の表示を変更
			m_pPrice[i]->PriceSale(SHOP_COUPON);

		}
		break;
	}
}

// 単体用
void CShopMenu::OneCoupon(int element)		// 値段表示調整関数
{
	if (m_nCoupon)
	{
		m_pPrice[element]->PriceSale(SHOP_COUPON);
	}
}

bool CShopMenu::GetShop()							// ショップ画面を閉じるか
{
	return m_bShop;
}

void CShopMenu::SetMoney(int * Money)				// 所持金セット
{
	m_pnMoney = Money;
}

void CShopMenu::SetCustom(int * Custom)				// カスタムセット
{
	m_pnCustom = Custom;
}

void CShopMenu::SetItem(int * Item)
{
	m_pnItem = Item;
}


void CShopMenu::SetShopSuction(Suction * pSuction)	// 吸い込みクラスセット
{
	m_pShop->SetSuction(pSuction);	// ShopのSuctionクラスセット
}


void CShopMenu::SetItemUse(int coupon)	// アイテムが使用されたか
{
	m_nCoupon = coupon;
}

CShop * CShopMenu::GetShopCustom()
{
	return m_pShop;
}