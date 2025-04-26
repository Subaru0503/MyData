// BurningObject.cpp

//=====インクルード=====
#include "BurningObject.h"

/************************************************
*@brief 座標＆スケール設定引数付きコンストラクタ
*************************************************/
CBurningObject::CBurningObject(float posX, float posY, float posZ,
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
	m_nKind = Object::BURNINGOBJECT;

	// 破壊時の生成オブジェクト数設定
	m_createNum = 2;
}

/********************
*@brief デストラクタ
*********************/
CBurningObject::~CBurningObject()
{
}