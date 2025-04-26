// Cookie.cpp

//=====インクルード=====
#include "Cookie.h"

#define BASE_SIZE_X	(0.5)

/************************************************
*@brief 座標＆スケール設定引数付きコンストラクタ
*************************************************/
Cookie::Cookie(float posX, float posY, float posZ,
	float sizeX, float sizeY, float sizeZ)
	: Object(posX, posY, posZ)	// 親クラスのコンストラクタに引数を渡す)
{
	// 基本初期化処理
	Init();

	// 引数からスケール設定
	m_scale = { sizeX, sizeY, sizeZ };

	// 削除フラグ初期化
	m_bDelete = false;

	// オブジェクトの種類の設定
	m_nKind = Object::COOKIE;

	// 吸い込み時の取得金額設定
	m_nMoney = 50;

	// オブジェクトレベル設定
	m_nLevel = 1;

	// モデルの拡縮率設定
	m_modelRatio = sizeX / BASE_SIZE_X;

	// モデル分類設定
	int random = (int)m_pos.z % 3;
	switch (random)
	{
	case 0:
		m_modelKey = "クッキー1";
		break;
	case 1:
	case -1:
		m_modelKey = "クッキー2";
		break;
	case 2:
	case -2:
		m_modelKey = "クッキー3";
		break;
	}
}

/********************
*@brief デストラクタ
*********************/
Cookie::~Cookie()	// デストラクタ
{

}