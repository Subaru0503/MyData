// Signboard.cpp

//=====インクルード=====
#include "TutorialSignboard.h"

/************************************************
*@brief 座標＆スケール設定引数付きコンストラクタ
*************************************************/
CTutorialSignboard::CTutorialSignboard(float posX, float posY, float posZ,
	float sizeX, float sizeY, float sizeZ, float rot, int kind)
	: Object(posX, posY, posZ)	// 親クラスのコンストラクタに引数を渡す)
{
	// 基本初期化処理
	Init();

	// 引数からスケール設定
	m_scale = { sizeX, sizeY, sizeZ };

	// 引数から向き設定
	m_rotate.y = rot;

	// 削除フラグ初期化
	m_bDelete = false;

	// オブジェクトの種類の設定
	m_nKind = Object::TUTORIALSIGNBOARD;

	// 吸い込み時の取得金額設定
	m_nMoney = 250;

	// 破壊時の木材生成個数
	m_createNum = 2;

	// オブジェクトレベル設定
	m_nLevel = 3;

	switch (kind)
	{
	case textureKind::suction:
		m_nTuturoalKind = textureKind::suction;
		break;
	case textureKind::custom:
		m_nTuturoalKind = textureKind::custom;
		break;
	case textureKind::shop:
		m_nTuturoalKind = textureKind::shop;
		break;
	}

	// モデル分類設定
	m_modelKey = "チュートリアル看板";


}

/********************
*@brief デストラクタ
*********************/
CTutorialSignboard::~CTutorialSignboard()	// デストラクタ
{
}

