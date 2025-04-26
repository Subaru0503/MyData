//=================================================================
//
//	SceneTitle.cpp
//	�^�C�g���V�[��
//
//=================================================================
#ifndef __SCENE_TITLE_H__
#define __SCENE_TITLE_H__

// ========== �C���N���[�h�� ==========
#include "SceneManager.h"	// �V�[���J�ڏ����p
#include "SoundManager.h"	// �T�E���h�Đ��p
#include "Title.h"
#include "Escape.h"
#include "TSuction.h"
// ========== �N���X ==========
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