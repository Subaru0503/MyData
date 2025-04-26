//=================================================================
//
//	sceneManager.cpp
//	シーン管理
//
//=================================================================

// ========== インクルード部 ==========
#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneSelect.h"
#include "SceneStageBase.h"
#include "SceneStage1.h"
#include "SceneStage2.h"
#include "SceneStage3.h"
#include "SceneResult.h"
#include "SceneOpening.h"
#include "SceneEnding.h"

#include <thread>

// ========== 定数・マクロ定義 ==========
#define FADE_IN			(true)
#define FADE_OUT		(false)
#define FADE_IN_TIME	(1.0f)
#define FADE_OUT_TIME	(1.0f)

// ========== コンストラクタ ==========
CSceneMng::CSceneMng()
	: m_scene(SCENE_OPENING)
	, m_nextScene(SCENE_OPENING)
	, m_GameEnd(false)
	, m_oldPlayStage(SCENE_STAGE1)
	, m_money(0)
	, m_clearTime{ 999, 999, 999 }
	, m_score{ 0 }
	, m_clearCount{ 0 }
	, m_openStageNum(0)
	, m_openStage(false)
	, m_loadEnd(false)
	, m_isViewEnding(false)
{
	// =-=-= データ作成 =-=-=
	m_pSoundMng = new CSoundMng();		// サウンド
	m_pFade = new Fade();				// フェード
	m_pRoad = new Road();
	m_pOpening = new SceneOpening(this, m_pSoundMng);
}

// ========== デストラクタ ==========
CSceneMng::~CSceneMng()
{
	// =-=-= シーンに応じたデータ削除 =-=-=
	// 存在していれば削除
	switch (m_scene)
	{
	case SCENE_OPENING: SAFE_DELETE(m_pOpening); break;
	case SCENE_TITLE:	SAFE_DELETE(m_pTitle);	break;
	case SCENE_SELECT:	SAFE_DELETE(m_pSelect); break;
	case SCENE_STAGE1:
	case SCENE_STAGE2:
	case SCENE_STAGE3:	SAFE_DELETE(m_pStage);  break;
	case SCENE_RESULT:	SAFE_DELETE(m_pResult); break;
	case SCENE_ENDING:	SAFE_DELETE(m_pEnding); break;
	default: break;
	}
	SAFE_DELETE(m_pSoundMng);
	SAFE_DELETE(m_pFade);
	SAFE_DELETE(m_pRoad);
}

// ========== 更新 ==========
void CSceneMng::Update(float tick)
{
	if (!m_pFade->IsPlay()) {			//いろんな処理はフェード処理が終わってから。
		if (m_scene != m_nextScene) {	// シーンチェンジが行われていれば遷移
			if (m_nextScene != SCENE_RESTART) SceneSwap();
			else RestartSwap();
		}
	}

	// =-=-= シーンに応じた更新 =-=-=
	switch (m_scene)
	{
	case SCENE_OPENING: m_pOpening->Update();		break;
	case SCENE_TITLE:	m_pTitle->Update();			break;
	case SCENE_SELECT:	m_pSelect->Update(tick);	break;
	case SCENE_STAGE1:
	case SCENE_STAGE2:
	case SCENE_STAGE3:	m_pStage->Update(tick); 	break;
	case SCENE_RESULT:	m_pResult->Update(tick);	break;
	case SCENE_ENDING:  m_pEnding->Update();		break;
	default: break;
	}

	// ----- 各種更新 -----
	m_pSoundMng->DeleteSpeaker();	// 再生終了したスピーカーを破棄
	m_pFade->Update();
}

// ========== 描画 ==========
void CSceneMng::Draw()
{
	switch (m_scene)
	{
	case SCENE_OPENING: m_pOpening->Draw(); break;
	case SCENE_TITLE:	m_pTitle->Draw();	break;
	case SCENE_SELECT:	m_pSelect->Draw();	break;
	case SCENE_STAGE1:
	case SCENE_STAGE2:
	case SCENE_STAGE3:	m_pStage->Draw();	break;
	case SCENE_RESULT:	m_pResult->Draw();	break;
	case SCENE_ENDING:  m_pEnding->Draw();  break;
	default: break;
	}
	m_pFade->Draw();
}

// ========== シーン切り替え設定 ==========
// 引　数：SceneKind 遷移先シーン
// 戻り値：なし
// 指定のシーンを遷移先に設定。
// ======================================
void CSceneMng::SetNextScene(SceneKind scene)
{
	// フェード中は次のシーンを予約しない
	if (m_pFade->IsPlay())
	{
		return;
	}

	m_nextScene = scene;	// 次シーン予約

	// ----- フェード -----
	// エンディングorオープニング→タイトルの場合のみ白フェード
	if (m_nextScene == SCENE_TITLE && (m_scene == SCENE_ENDING || m_scene == SCENE_OPENING)) {
		m_pFade->Start(FADE_OUT, FADE_OUT_TIME, Fade::WHITE);
		return;
	}

	switch (m_nextScene)
	{
	case SCENE_TITLE:
	case SCENE_SELECT:
		m_pFade->Start(FADE_OUT, FADE_OUT_TIME, Fade::PLANET);	break;
	case SCENE_STAGE1:
	case SCENE_STAGE2:
	case SCENE_STAGE3:
		m_pFade->Start(FADE_OUT, FADE_OUT_TIME, Fade::TIPS);	break;
	case SCENE_RESULT:
	case SCENE_ENDING:
		m_pFade->Start(FADE_OUT, FADE_OUT_TIME, Fade::WHITE);	break;
	default:	break;
	}

}

// ========== シーン切り替え ==========
// 引　数：なし
// 戻り値：なし
// 指定のシーンに切り替え、必要情報を引き継ぐ
// ==================================
void CSceneMng::SceneSwap()
{
	switch (m_scene)	// 遊んだステージの情報を格納
	{
	case SCENE_STAGE1:	m_oldPlayStage = SCENE_STAGE1;	break;
	case SCENE_STAGE2:	m_oldPlayStage = SCENE_STAGE2;	break;
	case SCENE_STAGE3:	m_oldPlayStage = SCENE_STAGE3;	break;
	}

	// =-=-= 新しいシーンの読み込み =-=-=
	m_pSoundMng->AllDeleteSpeaker();
	switch (m_nextScene)
	{
	case SCENE_TITLE:
		m_pTitle = new CSceneTitle(this, m_pSoundMng);	// シーン遷移処理呼び出しのためSceneMng*受け渡し
		m_pSoundMng->playSound(CSoundMng::BGM::title);	// 次のシーンのBGMを再生
		m_pSoundMng->StopSound(CSoundMng::BGM::Op);
		m_pSoundMng->StopSound(CSoundMng::BGM::Ed);
		break;
	case SCENE_SELECT:
		m_pSelect = new CSceneSelect(this, m_pSoundMng, m_pFade, m_oldPlayStage);
		m_pSoundMng->playSound(CSoundMng::BGM::Select);
		break;
	case SCENE_STAGE1:
	case SCENE_STAGE2:
	case SCENE_STAGE3: LoadGameScene();	m_pStage->Init(); break;
	case SCENE_RESULT:
		m_pResult = new SceneResult(this, m_pSoundMng);
		break;
	case SCENE_ENDING: m_pEnding = new SceneEnding(this, m_pSoundMng);
	}

	// =-=-= 必要情報引継ぎ =-=-=
	switch (m_scene)
	{
	case SCENE_TITLE:	break;
	case SCENE_SELECT:	if (m_nextScene != SCENE_TITLE) PassData(m_pSelect, m_pStage); break;	// ゲームステージへ
	case SCENE_STAGE1:
	case SCENE_STAGE2:
	case SCENE_STAGE3:	if (m_nextScene == SCENE_RESULT)PassData(m_pStage, m_pResult);	break;	// リザルトへ
	case SCENE_RESULT:	break;
	}

	// =-=-= 現在のシーン削除 =-=-=
	switch (m_scene)
	{
	case SCENE_OPENING: SAFE_DELETE(m_pOpening); break;
	case SCENE_TITLE:	SAFE_DELETE(m_pTitle);	break;
	case SCENE_SELECT:	SAFE_DELETE(m_pSelect);	break;
	case SCENE_STAGE1:
	case SCENE_STAGE2:
	case SCENE_STAGE3:	SAFE_DELETE(m_pStage);	break;
	case SCENE_RESULT:	SAFE_DELETE(m_pResult);	break;
	case SCENE_ENDING:  SAFE_DELETE(m_pEnding); break;
	default: break;
	}

	switch (m_nextScene)
	{
	case SCENE_TITLE:
		if (m_scene == SCENE_ENDING || m_scene == SCENE_OPENING) {
			m_pFade->Start(FADE_IN, FADE_IN_TIME, Fade::WHITE);	break;
		}
	case SCENE_SELECT:
		m_pFade->Start(FADE_IN, FADE_IN_TIME, Fade::PLANET);	break;
	case SCENE_STAGE1:
	case SCENE_STAGE2:
	case SCENE_STAGE3:
	case SCENE_RESULT:
	case SCENE_ENDING:
		m_pFade->Start(FADE_IN, FADE_IN_TIME, Fade::WHITE);	break;
	default: break;
	}

	m_scene = m_nextScene;	// シーン情報上書き
}

// ========== ゲームローディング ==========
// 引　数：なし
// 戻り値：なし
// ゲームシーンを作成し、その間ロード画面を表示
// ======================================
void CSceneMng::LoadGameScene()
{
	// =-=-= ロード開始 =-=-=
	std::thread LoadThread(&CSceneMng::Load, this);	// シーンロードスレッドを作成
	m_pRoad->SetRatio();
	m_loadEnd = false;
	// =-=-= ロード中 =-=-=
	while (1)
	{
		// ----- 画面更新処理 -----


		//ここにローディング画面のUpdate
		m_pFade->Update();
		m_pRoad->Update(m_nextScene);


		//Draw処理
		BeginDrawDirectX();

		m_pFade->Draw();
		m_pRoad->Draw();

		EndDrawDirectX();



		// =-=-= ロード終了 =-=-=
		if (m_loadEnd) {
			LoadThread.join();	// スレッドの終了を待つ
			m_pFade->Start(FADE_OUT, FADE_OUT_TIME, Fade::WHITE);	// tipsを見えなくするため
			while (m_pFade->GetAlpha() < 1.0f)
			{
				// ＊＊＊＊＊＊＊＊ここにもUpdate
				m_pRoad->Update(m_nextScene);
				m_pFade->Update();

				// ＊＊＊＊＊＊＊＊ここにもDraw
				BeginDrawDirectX();

				m_pRoad->Draw();
				m_pFade->Draw();

				EndDrawDirectX();
			}


			break;
		}
	}
}

// ========== ゲームシーンロード ==========
// 引　数：なし
// 戻り値：なし
// ゲームシーンを作成
// ======================================
void CSceneMng::Load()
{
	switch (m_nextScene)
	{
	case SCENE_STAGE1:
		m_pStage = new CSceneStage1(this, m_pSoundMng);
		break;
	case SCENE_STAGE2:
		m_pStage = new CSceneStage2(this, m_pSoundMng);
		break;
	case SCENE_STAGE3:
		m_pStage = new CSceneStage3(this, m_pSoundMng);
		break;
	}
	m_loadEnd = true;

	return;
}

// ========== ゲームリスタート ==========
// 引　数：なし
// 戻り値：なし
// リスタートの設定をする
// ==================================
void CSceneMng::GameRestart()
{
	// フェード中は次のシーンを予約しない
	if (m_pFade->IsPlay())
	{
		return;
	}

	m_nextScene = SCENE_RESTART;	// 次シーン予約

	m_pFade->Start(FADE_OUT, FADE_OUT_TIME, Fade::TIPS);
}

// ========== ゲームリスタート用シーン遷移 ==========
// 引　数：なし
// 戻り値：なし
// 現在のシーンと同じゲームシーンを読み込む
// ==================================
void CSceneMng::RestartSwap()
{
	m_nextScene = m_scene;
	m_pSoundMng->AllDeleteSpeaker();
	SAFE_DELETE(m_pStage);

	LoadGameScene();
	m_pStage->Init();

	m_pFade->Start(FADE_IN, FADE_IN_TIME, Fade::WHITE);
}

// ========== シーン間データ引継ぎ:Select → Stage==========
// 引　数：
// CSceneSelect* 
// CSceneStageBase* 
// 戻り値：なし
// ～関数概要～
// セレクトからステージシーンへ必要なデータを引き継ぐ
// ========================================================
void CSceneMng::PassData(CSceneSelect * select, CSceneStageBase * stage)	// Select → Stage
{
	// ----- 受け渡し -----
	stage->ItemCheck(select->GetItem());	// アイテム使用情報
}

// ========== シーン間データ引継ぎ:Stage → リザルト==========
// 引　数：
// SceneStage* 
// SceneResult* 
// 戻り値：なし
// ～関数概要～
// ステージからリザルトシーンへ必要なデータを引き継ぐ
// ========================================================
void CSceneMng::PassData(CSceneStageBase * stage, SceneResult * result)
{
	// =-=-= 遷移先へデータ受け渡し =-=-=
	int per;	// 達成度の値調整用

	// ----- 値調整 -----
	per = stage->getPer();
	if (per >= 100)	per = 100;						// あふれていたら１００％にそろえる

	// ----- 受け渡し -----
	result->SetMoney(stage->getMoney());			// 所持金
	result->SetTime(stage->getTime());				// クリアタイム
	result->SetPer(per);							// 達成度
	result->SetOldPlayStage(m_scene);				// プレイしたステージ番号(リスタート処理のため)

	// =-=-= セレクト画面用の値保存 =-=-=
	// ----- プレイデータ更新 -----
	if (stage->getPer() >= 60) {
		m_clearCount[m_scene]++;						// クリア回数加算
	}
	m_money += stage->getMoney();					// 所持金加算
	if (m_clearTime[m_scene] > stage->getTime()) {	// 最速なら
		m_clearTime[m_scene] = stage->getTime();	// 最速クリアタイム更新
	}
	if (m_score[m_scene] < stage->getPer()) {		// 最高なら
		m_score[m_scene] = stage->getPer();			// ハイスコア更新
	}

	// ----- ステージ開放状況更新 -----
	if ((m_scene == m_openStageNum) && (m_scene < MAX_STAGE - 1)) {				// プレイしたのが最新マップであるか
		if (m_score[m_scene] >= 60) {				// ノルマ達成していれば
			m_openStageNum++;						// ステージ開放数加算
			m_openStage = true;						// ステージ開放
		}
	}
}

// ========== Get ==========

// ゲーム終了状況
bool CSceneMng::GetGameEnd()
{
	return m_GameEnd;
}

// 現在の所持金額
int CSceneMng::GetMoney()
{
	return m_money;
}

// 各ステージの最速クリアタイム情報配列
int * CSceneMng::GetClearTime()
{
	return m_clearTime;
}

// 各ステージの最高スコア情報配列
int * CSceneMng::GetScore()
{
	return m_score;
}

// 各ステージのクリア回数情報配列
int* CSceneMng::GetClearCnt()
{
	return m_clearCount;
}

// ステージ開放数
int CSceneMng::GetOpenStageNum()
{
	return m_openStageNum;
}

// ステージ開放条件を満たしたか
bool CSceneMng::GetOpenStage()
{
	if (m_openStage) {
		m_openStage = false;	// 惑星開放は各惑星一度きりの処理のためフラグ下げ
		return true;
	}
	else {
		return false;
	}

	// **フラグの管理をSceneMngで完結させたかったので、読みにくいですがここでフラグ下げもしています。
}

bool CSceneMng::isVewEnd()
{
	return m_isViewEnding;
}

void CSceneMng::SetVewEnd()
{
	m_isViewEnding = true;
}

// ========== Set ==========

// ゲーム終了フラグを立てる
void CSceneMng::SetGameEnd()
{
	m_GameEnd = true;
}

void CSceneMng::SetTSuction(TSuction * pTSuction)
{
	m_pTSuction = pTSuction;
}