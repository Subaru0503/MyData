// CandyRock.cpp

//=====インクルード=====
#include "CandyRock.h"

#define BASE_SIZE_X	(0.5)

/************************************************
*@brief 座標＆スケール設定引数付きコンストラクタ
*************************************************/
CandyRock::CandyRock(float posX, float posY, float posZ,
	float sizeX, float sizeY, float sizeZ, int level)
	: Object(posX, posY, posZ)	// 親クラスのコンストラクタに引数を渡す)
{
	// 基本初期化処理
	Init();

	// 引数からスケール設定
	m_scale = { sizeX, sizeY, sizeZ };

	// 削除フラグ初期化
	m_bDelete = false;

	// オブジェクトの種類の設定
	m_nKind = Object::CANDYROCK;

	// オブジェクトレベル設定
	m_nLevel = level;

	switch (m_nLevel)
	{
	case 1:
		break;
	case 2:
		m_nMoney = 300;		// 吸い込み時の取得金額設定
		m_createNum = 3;	// キャンディーのかけらの生成数設定
		break;
	case 3:
		m_nMoney = 600;
		m_createNum = 6;
		break;
	case 4:
		m_nMoney = 1200;
		m_createNum = 6;
		break;
	}

	// モデルの拡縮率設定
	m_modelRatio = sizeX / BASE_SIZE_X;

	// モデル分類設定
	int random = (int)m_pos.x % 2;
	switch (random)
	{
	case 0:
		m_modelKey = "青キャンディーの岩";
		break;
	case 1:
	case -1:
		m_modelKey = "赤キャンディーの岩";
		break;
	}
}

/********************
*@brief デストラクタ
*********************/
CandyRock::~CandyRock()	// デストラクタ
{

}