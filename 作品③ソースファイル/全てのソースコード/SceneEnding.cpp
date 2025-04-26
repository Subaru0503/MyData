#include "SceneEnding.h"

SceneEnding::SceneEnding(CSceneMng* pscene, CSoundMng* psound)
	: m_pSceneMng(pscene)
	, m_pSoundMng(psound)
{
	m_pEnding = new Ending();
}

SceneEnding::~SceneEnding()
{
	SAFE_DELETE(m_pEnding);
}

void SceneEnding::Update()
{
	if (m_pSoundMng->CheckSoundEnd(CSoundMng::BGM::Ed))
		m_pSoundMng->playSound(CSoundMng::BGM::Ed);
	m_pEnding->Update();
	if (m_pEnding->IsEndAnime()) {
		m_pSceneMng->SetNextScene(CSceneMng::SceneKind::SCENE_TITLE);

	}
}

void SceneEnding::Draw()
{
	m_pEnding->Draw();
}
