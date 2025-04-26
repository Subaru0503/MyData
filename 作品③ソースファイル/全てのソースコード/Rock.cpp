// Rock.cpp

//=====インクルード=====
#include "Rock.h"

#define BASE_SIZE_X	(2)

/************************************************
*@brief 座標＆スケール設定引数付きコンストラクタ
*************************************************/
CRock::CRock(float posX, float posY, float posZ,
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
	m_nKind = Object::ROCK;

	// オブジェクトレベル設定
	m_nLevel = level;

	// レベル別設定
	switch (m_nLevel)
	{
	case 2:
		m_createNum = 2;	// 破壊時の小石生成個数
		m_nMoney = 200;		// 吸い込み時の取得金額設定
		break;
	case 3:
		m_createNum = 6;
		m_nMoney = 600;
		break;
	case 4:
		m_createNum = 6;
		m_nMoney = 2400;
		break;
	}

	// モデルの拡縮率設定
	m_modelRatio = sizeX / BASE_SIZE_X;

	// モデル分類設定
	m_modelKey = "岩";
}

/********************
*@brief デストラクタ
*********************/
CRock::~CRock()	// デストラクタ
{

}
