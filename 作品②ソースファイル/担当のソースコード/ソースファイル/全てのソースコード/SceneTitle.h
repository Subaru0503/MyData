//=================================================================
//
//	SceneTitle.cpp
//	タイトルシーン
//
//=================================================================
#ifndef __SCENE_TITLE_H__
#define __SCENE_TITLE_H__

// ========== インクルード部 ==========
#include "SceneManager.h"	// シーン遷移処理用
#include "SoundManager.h"	// サウンド再生用
#include "Title.h"
#include "Escape.h"
#include "TSuction.h"
// ========== クラス ==========
class CSceneTitle
{
public:
	CSceneTitle(CSceneMng* pSceneMng, CSoundMng* pSoundMng);
	~CSceneTitle();
	void Update();
	void Draw();

private:
	bool m_pushEsc, m_select;

	CSceneMng* m_pSceneMng;
	CSoundMng* m_pSoundMng;
	TItle* m_pTitle;
	EscapeUI* m_pEscape;
	TSuction* m_pTSuction;
	bool animefin;
	bool animestart;
	bool m_startPush;
};

#endif // !__SCENE_TITLE_H__