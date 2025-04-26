#ifndef __SCENE_OPENING_H__
#define __SCENE_OPENING_H__

// ========== インクルード部 ==========
#include "SceneManager.h"
#include "SoundManager.h"
#include "Opening.h"

// ========== クラス ==========
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
