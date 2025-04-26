// House.cpp

//=====インクルード=====
#include "House.h"

/************************************************
*@brief 座標＆スケール設定引数付きコンストラクタ
*************************************************/
CHouse::CHouse(float posX, float posY, float posZ,
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
	m_nKind = Object::HOUSE;

	// 吸い込み時の取得金額設定
	m_nMoney = 1500;

	// 破壊時の木材生成個数
	m_createNum = 15;

	// オブジェクトレベル設定
	m_nLevel = level;

	// モデル分類設定
	// m_modelKey = "家";
}

/********************
*@brief デストラクタ
*********************/
CHouse::~CHouse()	// デストラクタ
{

}