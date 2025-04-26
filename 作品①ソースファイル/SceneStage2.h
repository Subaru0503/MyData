///////////////////////////////////////
//
// ステージ2シーンクラス
//
// シーンの読み込む、管理をする
//
///////////////////////////////////////

//----インクルードガード----
#ifndef __SCENE_STAGE2_H__
#define __SCENE_STAGE2_H__

//----インクルード部----
#include "SceneBase.hpp"

//---ファイル読み込みに使用----
#include <iostream>
#include <fstream>
#include <string>

#include "float3.h"

using namespace std;

// クラス定義
class SceneStage2 : public SceneBase
{
public:

	// コンストラクタ
	SceneStage2() : SceneBase("Stage2") {}

	// 初期化処理
	void Init();

	// 終了処理
	void Uninit();

	// 更新処理
	void Update(float tick);

	// 描画
	void Draw();

private:

	// ゴールしてないときだけする処理
	bool ProcessNotGoal();


	//----ステージ作成関係の関数----

	// ファイル読み込み
	void Load();

	// プレイヤー作成
	void PlayerCreate(ifstream& file, string cell);

	// 地面作成
	void GroundCreate(ifstream& file, string cell);

	// ゴール作成
	void GoalCreate(ifstream& file, string cell);

	// ネジ作成
	void ScrewCreate(ifstream& file, string cell);

	// ギミック作成
	void GimmickCreate(ifstream& file, string cell);

	// プレイヤーチェックポイント作成
	void PlayerCheckPointCreate(ifstream& file, string cell);


	//----ギミックの設定----

	// ギミックに対象のネジを設定
	void SetTargetScrew(ifstream& file, string cell);

	// ギミックのチェックポイント設定
	void SetCheckPoint(ifstream& file, string cell, vector<float3> checkPoint);

	// 一時的に出現する床に必要な情報を設定
	void SetTemporaryInfo(ifstream& file, string cell);


	//----インゲームUI----

	// 時間UI作成
	void TimeCreate(ifstream& file, string cell);

	// 通常UI作成(特に特有の動きがないUI)
	void InGameNormalUICreate(ifstream& file, string cell);

	// ポーズUI作成
	void PauseMoziUICreate(ifstream& file, string cell);


	//----チュートリアルUI----

	// 通常UI作成(チュートリアル画面)
	void MenuNormalUICreate(ifstream& file, string cell);

	// 左矢印UI作成
	void LeftUICreate(ifstream& file, string cell);

	// 右矢印UI作成
	void RightUICreate(ifstream& file, string cell);

	// ゲームスタートUI作成
	void StartUICreate(ifstream& file, string cell);


	//----ゲームオーバーした後にする----

	// ゲームオーバー後に表示するUIを作成
	void GameOverUICreate();


	//----ゴールした後にする---

	// ゴール後に表示するUIを作成
	void GoalUICreate();

	// クリアタイムを表示するUIを作成
	void ClearTimeUICreate();

private:

	// 合計2Dオブジェクト番号
	int m_Total2DObjNo;

	// 合計3Dオブジェクト番号
	int m_Total3DObjNo;

	// 合計時間UI番号
	int m_TotalTimeUINo;

	// ゲームオーバーフラグ
	bool m_GameOver;
};

#endif // __SCENE_STAGE2_H__