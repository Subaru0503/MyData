// BlueMushroom.cpp

//=====インクルード=====
#include "BlueMushroom.h"

#define BASE_SIZE_X	(0.5)

/************************************************
*@brief 座標＆スケール設定引数付きコンストラクタ
*************************************************/
BlueMushroom::BlueMushroom(float posX, float posY, float posZ,
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
	m_nKind = Object::BLUE_MUSHROOM;

	// 吸い込み時の取得金額設定
	m_nMoney = 1000;

	// オブジェクトレベル設定
	m_nLevel = 3;

	// モデルの拡縮率設定
	m_modelRatio = sizeX / BASE_SIZE_X;

	// モデル分類設定
	m_modelKey = "青キノコ";

	// ギミックオブジェクト登録
	m_bGimmick = true;
}

/********************
*@brief デストラクタ
*********************/
BlueMushroom::~BlueMushroom()	// デストラクタ
{

}