// Strawberry.cpp

//=====インクルード=====
#include "Strawberry.h"

#define BASE_SIZE_X	(0.5)

/************************************************
*@brief 座標＆スケール設定引数付きコンストラクタ
*************************************************/
Strawberry::Strawberry(float posX, float posY, float posZ,
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
	m_nKind = Object::STRAWBERRY;

	// 吸い込み時の取得金額設定
	m_nMoney = 250;

	// オブジェクトレベル設定
	m_nLevel = 2;

	// モデルの拡縮率設定
	m_modelRatio = sizeX / BASE_SIZE_X;

	// モデル分類設定
	m_modelKey = "いちご";
}

/********************
*@brief デストラクタ
*********************/
Strawberry::~Strawberry()	// デストラクタ
{

}