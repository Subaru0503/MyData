#ifndef __SCENE_OPENING_H__
#define __SCENE_OPENING_H__

// ========== �C���N���[�h�� ==========
#include "SceneManager.h"
#include "SoundManager.h"
#include "Opening.h"

// ========== �N���X ==========
class SceneOpening
{
public:
	SceneOpening(CSceneMng*, CSoundMng*);
	~SceneOpening();
	void Update();
	void Draw();

private:
	CSceneMng* m_pSceneMng;
	CSoundMng* m_pSoundMng;
	Opening*   m_pOpening;
};

#endif // !__SCENE_OPENING_H__
