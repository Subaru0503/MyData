// Rubbish.cpp

//=====インクルード=====
#include "Rubbish.h"

/************************************************
*@brief 座標設定引数付きコンストラクタ
*************************************************/
CRubbish::CRubbish(float posX, float posY, float posZ)
	: Object(posX, posY, posZ)	// 親クラスのコンストラクタに引数を渡す
{
	// 基本初期化処理
	Init();

	// 削除フラグ初期化
	m_bDelete = false;

	// スケール設定
	m_scale = { 0.5f,0.5f,0.5f };

	// オブジェクトの種類の設定
	m_nKind = Object::RUBBISH;

	// 吸い込み時の取得金額設定
	m_nMoney = 50;

	// オブジェクトレベル設定
	m_nLevel = 1;

	// モデル分類設定
	// m_modelKey = "ゴミくず";
}

/********************
*@brief デストラクタ
*********************/
CRubbish::~CRubbish()	// デストラクタ
{
}
