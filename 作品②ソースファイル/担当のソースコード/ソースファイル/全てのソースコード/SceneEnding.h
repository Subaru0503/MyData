#ifndef __SCENE_ENDING_H__
#define __SCENE_ENDING_H__

// ========== �C���N���[�h�� ==========
#include "SceneManager.h"
#include "SoundManager.h"
#include "Ending.h"

// ========== �N���X ==========
class SceneEnding
{
public:
	SceneEnding(CSceneMng*, CSoundMng*);
	~SceneEnding();
	void Update();
	void Draw();

private:
	CSceneMng* m_pSceneMng;
	CSoundMng* m_pSoundMng;
	Ending*    m_pEnding;
};

#endif // !__SCENE_ENDING_H__
