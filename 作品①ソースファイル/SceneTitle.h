//----インクルードガード----
#ifndef __SCENE_TITLE_H__
#define __SCENE_TITLE_H__

//----インクルード部----
#include "SceneBase.hpp"

//---ファイル読み込みに使用----
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// クラス定義
class SceneTitle : public SceneBase
{
public:
	SceneTitle() : SceneBase("Title") {}
	void Init();					// 初期化
	void Uninit();					// 終了処理
	void Update(float tick);		// 更新
	void Draw();					// 描画

private:
	//----UI作成関係の関数----
	void Load();					// ファイル読み込み

	// タイトル名UI作成
	void TitleNameCreate(ifstream& file, string cell);

	// ネジUI作成
	void TitleScrewCreate(ifstream& file, string cell);

	// ゲームスタートUI作成
	void GameStartCreate(ifstream& file, string cell);

	// タイトル名UI作成
	void BirdCreate(ifstream& file, string cell);

	// 通常UI作成
	void NormalUICreate(ifstream& file, string cell);


private:
	int m_Total2DObjNo;			// 合計2Dオブジェクト番号
	int m_Total3DObjNo;			// 合計3Dオブジェクト番号
	bool m_Change;
};

#endif // __SCENE_TITLE_H__