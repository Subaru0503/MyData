//=================================================================
//
//	sceneManager.cpp
//	シーン管理
//
//=================================================================

#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

// ========== インクルード部 ==========
#include "SoundManager.h"
#include "Fade.h"
#include "RoadUI.h"
#include "TSuction.h"
// 相互インクルード防止
class CSceneTitle;
class CSceneSelect;
class CSceneStageBase;
class SceneResult;
class SceneOpening;
class SceneEnding;

// ========== クラス ==========
class CSceneMng
{
public:
	enum SceneKind		// ステージの種類、総数
	{
		SCENE_STAGE1,
		SCENE_STAGE2,
		SCENE_STAGE3,
		MAX_STAGE,

		SCENE_TITLE = 3,
		SCENE_SELECT,
		SCENE_RESULT,
		SCENE_RESTART,
		SCENE_OPENING,
		SCENE_ENDING,
		SCENE_MAX,
	};

public:
	CSceneMng();
	~CSceneMng();
	void Update(float tick);
	void Draw();

	void SetNextScene(SceneKind scene);	// 次のシーンを設定し、遷移する
	void GameRestart();					// ゲームをリスタートする(リロード)
	void SetGameEnd();					// ゲーム終了させる

	bool GetGameEnd();					// ゲーム終了状況を取得
	int* GetClearCnt();					// 各ステージクリア回数
	int  GetMoney();					// 現在の所持金取得
	int* GetClearTime();				// 各ステージ最速クリアタイム取得
	int* GetScore();					// 各ステージ最高スコア取得
	int  GetOpenStageNum();				// ステージ開放数
	bool GetOpenStage();				// ステージ開放するか
	bool isVewEnd();					// エンディング視聴済みか
	void SetVewEnd();					// エンディング視聴済みに設定
	void SetTSuction(TSuction* pTSuction);
private:
	void SceneSwap();					// シーンを切り替える
	void RestartSwap();					// リスタートシーン遷移
	void LoadGameScene();				// ゲームシーンを読み込み、その間ロード画面を表示
	void Load();						// ゲームシーンを作成する

	// ----- 次のシーンで必要な情報を引き継ぐ -----
	void PassData(CSceneSelect* select, CSceneStageBase* stage);	// Select → Stage
	void PassData(CSceneStageBase* stage, SceneResult* result);		// Stage  → Result

private:
	// ----- シーン管理 -----
	bool m_GameEnd;			// ゲームループ抜ける
	int	 m_scene;			// 現在実行中のシーン
	int	 m_nextScene;		// 次のシーン
	int	 m_oldPlayStage;	// 前回遊んだステージ
	bool m_loadEnd;			// ロード終了したか
	bool m_isViewEnding;	// エンディングを見たことあるか

	// ----- シーンデータ -----
	SceneOpening*		m_pOpening;		// オープニング
	CSceneTitle*		m_pTitle;		// タイトル
	CSceneSelect*		m_pSelect;		// セレクト
	CSceneStageBase*	m_pStage;		// ステージ
	SceneResult*		m_pResult;		// リザルト
	SceneEnding*		m_pEnding;		// エンディング

	// ----- ゲーム全体で保持するデータ -----
	CSoundMng*	m_pSoundMng;			// サウンド
	Fade*		m_pFade;				// フェード
	Road* m_pRoad;						// ロード
	//エフェクト
	TSuction* m_pTSuction;
	int m_money;						// 所持金額
	int m_clearTime[MAX_STAGE];			// 各ステージ最速クリアタイム
	int m_score[MAX_STAGE];				// 各ステージ最高お掃除率
	int m_clearCount[MAX_STAGE];		// 各ステージクリア回数
	int m_openStageNum;					// ステージ開放数
	bool m_openStage;					// ステージ開放するか
};

#endif // !__SCENE_MANAGER_H__