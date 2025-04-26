#include "SceneOpening.h"

SceneOpening::SceneOpening(CSceneMng* pscene, CSoundMng* psound)
	: m_pSceneMng(pscene)
	, m_pSoundMng(psound)
{
	m_pOpening = new Opening();
}

SceneOpening::~SceneOpening()
{
	SAFE_DELETE(m_pOpening);
}

void SceneOpening::Update()
{
	if (m_pSoundMng->CheckSoundEnd(CSoundMng::BGM::Op))
		m_pSoundMng->playSound(CSoundMng::BGM::Op);
	if (m_pOpening->IsEndAnime()) {
		m_pSceneMng->SetNextScene(CSceneMng::SceneKind::SCENE_TITLE);
	}
	else {
		m_pOpening->Update();
	}
}

void SceneOpening::Draw()
{
	m_pOpening->Draw();
}
