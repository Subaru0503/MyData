// ModelManager.h
#ifndef __MODELMANAGER_H__
#define __MODELMANAGER_H__

#include <map>		// map用
#include "Model.h"	// モデル読み込み用

/**
*@brief	複数のオブジェクトのモデルデータたちを管理するクラス
*/
class ModelManager
{
public:
	ModelManager();			// コンストラクタ
	~ModelManager();		// デストラクタ
	void LoadModelList();	// 全てのモデルをロード
	Model* FindModel(std::string modelTag);		// タグに応じたモデルデータのポインタを返す

private:
	std::map<std::string, Model*> m_models;		// ロードしたモデルデータのマップ

	// Stage01,02
	Model* mushroom;	// きのこ
	Model* mushroomCat;	// ねこきのこ	
	Model* rock;		// 岩
	Model* tree;		// 木
	Model* fenceWood;	// 木フェンス
	Model* fenceStone;	// 石フェンス
	Model* fenceIron;	// 鉄フェンス
	Model* wood;        // 木材
	Model* koisi;       // 小石
	Model* board;       // 看板
	Model* metal;		// 鋼材
	Model* tutorialSignboard;	// チュートリアル看板
	// Stage03
	Model* ChocolateDonuts;		// チョコドーナツ
	Model* StrawberryChocolateDonuts;		// 苺チョコドーナツ
	Model* cakePiece;	// ケーキ1ピース
	Model* strawberry;	// いちご
	Model* apolo;		// アポロ
	Model* cookie1;		// クッキー1
	Model* cookie2;		// クッキー2
	Model* cookie3;		// クッキー3
	Model* chocolateTree;// チョコの木
	Model* BlueCandyRock;				// 青キャンディーの岩
	Model* RedCandyRock;				// 赤キャンディーの岩
	Model* chocolateFence;				// チョコのフェンス
	Model* StrawberryChocolateFence;	// 苺チョコのフェンス
	Model* chocolatePiece;				// チョコのかけら
	Model* StrawberryChocolatePiece;	// 苺チョコのかけら
	Model* GreapCandyPiece;				// グレープキャンディーのかけら
	Model* GreapFishCandyPiece;			// グレープ魚キャンディーのかけら
	Model* OrangeCandyPiece;			// オレンジキャンディーのかけら
	Model* OrangeFishCandyPiece;		// オレンジ魚キャンディーのかけら
	Model* SodaCandyPiece;				// ソーダキャンディーのかけら
	Model* SodaFishCandyPiece;			// ソーダ魚キャンディーのかけら
	Model* BigCandle;			// 大きいろうそく
	Model* MiddleCandle;		// 小さいろうそく
	Model* sweetsHouse;	// お菓子の家
	// ギミック
	Model* blueMushroom;// 青キノコ
	Model* blueMushroomNemoto;// 青キノコの根本
	Model* biscuit;		// ビスケット
	Model* biscuitPiece;// ビスケットのかけら
};

#endif

