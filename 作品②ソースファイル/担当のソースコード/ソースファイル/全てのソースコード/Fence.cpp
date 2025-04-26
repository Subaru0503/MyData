// Fence.cpp

//=====インクルード=====
#include "Fence.h"

/************************************************
*@brief 座標＆スケール設定引数付きコンストラクタ
*************************************************/
CFence::CFence(float posX, float posY, float posZ,
	float sizeX, float sizeY, float sizeZ, float rot, int level)
	: Object(posX, posY, posZ)	// 親クラスのコンストラクタに引数を渡す)
{
	// 基本初期化処理
	Init();

	// 引数からスケール設定
	m_scale = { sizeX, sizeY, sizeZ };

	// 引数から回転設定
	m_rotate.y = rot;

	// 削除フラグ初期化
	m_bDelete = false;

	// オブジェクトの種類の設定
	m_nKind = Object::FENCE;

	// オブジェクトレベル設定
	m_nLevel = level;



	// ----- レベルごとに設定 -----
	switch (m_nLevel)
	{
	case 1:	// ない
		break;
	case 2:	// 木
		m_nMoney = 200;		// 吸い込み時の取得金額設定
		m_createNum = 2;	// 破壊時の木材生成個数
		m_modelKey = "木フェンス";	// モデル分類設定
		break;
	case 3:	// 石
		m_nMoney = 600;
		m_createNum = 6;
		m_modelKey = "石フェンス";	// モデル分類設定
		break;
	case 4:	// 鉄
		m_nMoney = 2400;
		m_createNum = 6;
		m_modelKey = "鉄フェンス";	// モデル分類設定
		break;
	}
}

/********************
*@brief デストラクタ
*********************/
CFence::~CFence()	// デストラクタ
{

}