//SceneResult.h
//=====インクルードガード=====
#ifndef __SCENE_RESULT_H__
#define __SCENE_RESULT_H__
//=====インクルード部=====
#include "Shader.h"
#include "SoundManager.h"
#include "SceneManager.h"
#include "Result_BG.h"
#include "Result_Star.h"
#include "Result_Percent.h"
#include "Result_Message.h"
#include "Result_Time.h"
#include "UI.h"
#include "Result_Stamp.h"
#include "Result_Player.h"
#include "Result_Window.h"

//=====クラス=====
class SceneResult
{
public:
	SceneResult(CSceneMng* pSceneMng, CSoundMng* pSoundMng);
	~SceneResult();
	void Update(float tick);
	void Draw();
	void SetMoney(int money);				//金額受け取り
	void SetPer(int per);					//達成度受け取り
	void SetTime(int time);					//クリアタイム受け取り
	void SetOldPlayStage(int stage);		// 前回プレイステージ番号取得

private:
	VertexShader* m_pVS;
	ResultBG* m_pBG;
	ResultStar* m_pStar[3];
	ResultPer* m_pPer;
	ResultMsg* m_pMsg;
	ResultTime* m_pTime;
	CUI* m_pUI;
	ResultStamp* m_pStamp;
	ResultPlayer* m_pPlayerUI;
	ResultWindow* m_pWindow;
	CSoundMng* m_pSoundMng;		// サウンド
	CSceneMng* m_pSceneMng;		// シーンマネージャー
	bool m_select;
	bool m_SoundOne;
	bool m_SoundStop;
	int m_nMoney;				//稼いだ金額
	int m_nPer;					//達成度
	int m_nTime;				//クリアタイム	
	int m_oldPlayStage;			// 前回プレイステージ
	int m_EndingCountDown;		// エンディング強制再生までのカウントダウン
};

#endif