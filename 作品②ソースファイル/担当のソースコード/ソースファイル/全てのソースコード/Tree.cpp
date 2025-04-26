// Tree.cpp

//=====インクルード=====
#include "Tree.h"

#define BASE_SIZE_X	(1)

/************************************************
*@brief 座標＆スケール設定引数付きコンストラクタ
*************************************************/
CTree::CTree(float posX, float posY, float posZ,
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
	m_nKind = Object::TREE;

	// オブジェクトレベル設定
	m_nLevel = level;

	switch (m_nLevel)
	{
	case 1:
		break;
	case 2:
		m_nMoney = 200;		// 吸い込み時の取得金額設定
		m_createNum = 2;	// 破壊時の木材生成個数
		break;
	case 3:
		m_nMoney = 600;		// 吸い込み時の取得金額設定
		m_createNum = 6;	// 破壊時の木材生成個数
		break;
	case 4:
		m_nMoney = 2400;		// 吸い込み時の取得金額設定
		m_createNum = 6;	// 破壊時の木材生成個数
		break;
	}

	// モデルの拡縮率設定
	m_modelRatio = sizeX / BASE_SIZE_X;

	// モデル分類設定
	m_modelKey = "木";

	//回転ランダム力技
	m_rotate.y = (posX + posY + posZ) * (posX + posY + posZ) * (posX + posY + posZ) * (posX + posY + posZ) * (posX + posY + posZ);
}

/********************
*@brief デストラクタ
*********************/
CTree::~CTree()	// デストラクタ
{

}