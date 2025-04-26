// インクルードガード
#ifndef __SCENE_GAME_H__
#define __SCENE_GAME_H__

// インクルード部
#include "SceneBase.hpp"

//---ファイル読み込みに使用----
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// クラス定義
class SceneGame : public SceneBase
{
public:
	SceneGame() : SceneBase("Game") {}
	void Init();				// 初期化処理
	void Uninit();				// 終了処理
	void Update(float tick);	// 更新処理
	void Draw();				// 描画

private:

	// ゴールしてないときだけする処理
	bool ProcessNotGoal();

	//----ステージ作成関係の関数----
	void Load();				// ファイル読み込み

	void PlayerCreate(ifstream& file, string cell);		// プレイヤー作成
	void GroundCreate(ifstream& file, string cell);		// 地面作成
	void GoalCreate(ifstream& file, string cell);		// ゴール作成
	void ScrewCreate(ifstream& file, string cell);		// ネジ作成
	void GimmickCreate(ifstream& file, string cell);	// ギミック作成

	void SetTargetScrew(ifstream& file, string cell);	// ギミックに対象のネジを設定

	// インゲームUI
	void TimeCreate(ifstream& file, string cell);		// 時間UI作成
	void InGameNormalUICreate(ifstream& file, string cell);		// 通常UI作成(特に特有の動きがないUI)
	void PauseMoziUICreate(ifstream& file, string cell);		// ポーズUI作成
	// チュートリアルUI
	void MenuNormalUICreate(ifstream& file, string cell);	// 通常UI作成(チュートリアル画面)
	void LeftUICreate(ifstream& file, string cell);		// 左矢印UI作成
	void RightUICreate(ifstream& file, string cell);	// 右矢印UI作成
	void StartUICreate(ifstream& file, string cell);	// ゲームスタートUI作成

	//----ゲームオーバーした後にする----
	void GameOverUICreate();			// ゲームオーバー後に表示するUIを作成

	//----ゴールした後にする---
	void GoalUICreate();				// ゴール後に表示するUIを作成
	void ClearTimeUICreate();			// クリアタイムを表示するUIを作成

private:
	int m_Total2DObjNo;			// 合計2Dオブジェクト番号
	int m_Total3DObjNo;			// 合計3Dオブジェクト番号
	int m_TotalTimeUINo;		// 合計時間UI番号
	bool m_GameOver;			// ゲームオーバーフラグ
};

#endif // __SCENE_GAME_H__