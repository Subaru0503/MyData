#include "SceneRoot.h"
#include <stdio.h>
#include "CameraDCC.h"
#include "MoveLight.h"
#include "Input.h"
#include "Geometory.h"
#include "DebugMenu.h"

//----�V�[���֘A----
#include "SceneTitle.h"
#include "SceneGame.h"
#include "SceneStage2.h"

//----�}�l�[�W���[----
#include "TutorialManager.h"
#include "SoundManager.h"
#include "ResetManager.h"

// �ÓI�ϐ�������
SceneBase::Scene SceneRoot::m_NextScene = SceneBase::Scene::None;
SceneBase::Scene SceneRoot::m_CurrentScene = SceneBase::Scene::None;

// ������
void SceneRoot::Init()
{
	// �I�u�W�F�N�g�̍쐬
	CameraDCC* pCamera = CreateObj<CameraDCC>("Camera");
	MoveLight* pLight = CreateObj<MoveLight>("Light");
	// �t�F�[�h�쐬
	CreateSceneObj<Fade>("Fade");
	// �擾
	m_pFade = GetObj<Fade>("Fade");

	// ���Z�b�g�}�l�[�W���[�ɂ��n��
	ResetManager::GetInstance().SetFade(m_pFade);

	// ���̃V�[�����Z�b�g
	m_NextScene = SceneBase::Scene::TITLE;

#ifdef _DEBUG
	// �O���b�h�\��
	debug::Item* camera = debug::Item::CreateGroup("Grid");
	camera->AddGroupItem(debug::Item::CreateValue("Enable",	debug::Item::Bool,	true));
	camera->AddGroupItem(debug::Item::CreateValue("Size",	debug::Item::Float, true));
	camera->AddGroupItem(debug::Item::CreateValue("Margin",	debug::Item::Float, true));
	camera->AddGroupItem(debug::Item::CreateValue("Color",	debug::Item::Color, true));
	camera->AddGroupItem(debug::Item::CreateValue("Axis",	debug::Item::Bool,	true));
	debug::Menu::Get("00_Info").AddItem(camera);

	// �V�[���\��
	debug::Window& scene = debug::Menu::Create("Scene");
	debug::Item* list = debug::Item::CreateList("Scenes", [this](const void* arg) {
		RemoveSubScene();
		const char* name = reinterpret_cast<const char*>(arg);
		//if (strcmp(name, "Shading") == 0) AddSubScene<SceneShading>();
		//else if (strcmp(name, "Lights") == 0) AddSubScene<SceneLights>();
		//else if (strcmp(name, "Postprocess") == 0) AddSubScene<ScenePostprocess>();
		//else if (strcmp(name, "Bloom") == 0) AddSubScene<SceneBloom>();
		//else if (strcmp(name, "Shadow") == 0) AddSubScene<SceneShadow>();
		//else if (strcmp(name, "Deferred") == 0) AddSubScene<SceneDeferred>();
		//if (strcmp(name, "Title") == 0) AddSubScene<SceneTitle>();
		//else if (strcmp(name, "Game") == 0) AddSubScene<SceneGame>();
	}, true);
	//list->AddListItem("Shading");
	//list->AddListItem("Lights");
	//list->AddListItem("Postprocess");
	//list->AddListItem("Bloom");
	//list->AddListItem("Shadow");
	//list->AddListItem("Deferred");
	list->AddListItem("Title");
	list->AddListItem("Game");
	scene.AddItem(list);
#else

#endif
}

/**
 * @fn
 * �V�[���̃��������
 * @brief �I������
 */
void SceneRoot::Uninit()
{
}

/**
 * @fn
 * �V�[���̍X�V����
 * @brief �X�V����
 */
void SceneRoot::Update(float tick)
{
	if (!m_pFade) return;

	// ���̃V�[�����Z�b�g����Ă�����
	if (!m_pFade->GetPlay() && m_NextScene != SceneBase::Scene::None)
	{
		SceneChange();	// �V�[���؂�ւ�
	}

	// �Đ��I�������X�s�[�J�[��j��
	SoundManager::GetInstance().DeleteSpeaker();
}

/**
 * @fn
 * �V�[���̕`�揈��
 * @brief �`�揈��
 */
void SceneRoot::Draw()
{

#ifdef _DEBUG
	Camera* pCamera = GetObj<CameraDCC>("Camera")->GetComponent<Camera>();
	Light* pLight = GetObj<MoveLight>("Light")->GetComponent<Light>();

	Geometory::SetView(pCamera->GetView());
	Geometory::SetProjection(pCamera->GetProj());
	pCamera->Draw();
	pLight->Draw();

	debug::Window& window = debug::Menu::Get("00_Info");
	if (window["Grid"]["Enable"].GetBool())
	{
		DirectX::XMFLOAT4X4 fmat;
		DirectX::XMStoreFloat4x4(&fmat, DirectX::XMMatrixIdentity());
		Geometory::SetWorld(fmat);

		// �Ԋ|���`��
		float GridSize = window["Grid"]["Size"].GetFloat();
		GridSize *= 0.5f;
		float GridMargin = window["Grid"]["Margin"].GetFloat();
		DirectX::XMFLOAT4 color;
		color = window["Grid"]["Color"].GetColor();
		Geometory::SetColor(color);
		float d = GridMargin;
		float s = GridSize;
		while (s >= GridMargin && GridMargin > 0.0f)
		{
			Geometory::AddLine(DirectX::XMFLOAT3( d, 0.0f, -GridSize), DirectX::XMFLOAT3( d, 0.0f, GridSize));
			Geometory::AddLine(DirectX::XMFLOAT3(-d, 0.0f, -GridSize), DirectX::XMFLOAT3(-d, 0.0f, GridSize));
			Geometory::AddLine(DirectX::XMFLOAT3(-GridSize, 0.0f,  d), DirectX::XMFLOAT3(GridSize, 0.0f,  d));
			Geometory::AddLine(DirectX::XMFLOAT3(-GridSize, 0.0f, -d), DirectX::XMFLOAT3(GridSize, 0.0f, -d));
			d += GridMargin;
			s -= GridMargin;
		}
		// ���`��
		if (window["Grid"]["Axis"].GetBool())
		{
			Geometory::SetColor(DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
			Geometory::AddLine(DirectX::XMFLOAT3(-GridSize, 0.0f, 0.0f), DirectX::XMFLOAT3(GridSize, 0.0f, 0.0f));
			Geometory::SetColor(DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
			Geometory::AddLine(DirectX::XMFLOAT3(0.0f, -GridSize, 0.0f), DirectX::XMFLOAT3(0.0f, GridSize, 0.0f));
			Geometory::SetColor(DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));
			Geometory::AddLine(DirectX::XMFLOAT3(0.0f, 0.0f, -GridSize), DirectX::XMFLOAT3(0.0f, 0.0f, GridSize));
		}
		else
		{
			Geometory::AddLine(DirectX::XMFLOAT3(-GridSize, 0.0f, 0.0f), DirectX::XMFLOAT3(GridSize, 0.0f, 0.0f));
			Geometory::AddLine(DirectX::XMFLOAT3(0.0f, 0.0f, -GridSize), DirectX::XMFLOAT3(0.0f, 0.0f, GridSize));
		}
		Geometory::DrawLines();
	}
#endif
}

// �V�[���؂�ւ�
void SceneRoot::SceneChange()
{
	// �S�Ĕj��
	SoundManager::GetInstance().AllDeleteSpeaker();

	// �V�[�����X�V
	m_CurrentScene = m_NextScene;

	// �V�[���؂�ւ�
	switch (m_NextScene)
	{
	// �^�C�g��
	case SceneBase::Scene::TITLE:
		AddSubScene<SceneTitle>();
		// �^�C�g��BGM�Đ�
		SoundManager::GetInstance().playSound(SoundManager::BGM::Title);
		break;
	// �Q�[��
	case SceneBase::Scene::GAME:
		AddSubScene<SceneGame>();
		// �X�e�[�WBGM�Đ�
		SoundManager::GetInstance().playSound(SoundManager::BGM::Stage);
		break;
	case SceneBase::Scene::STAGE2:
		AddSubScene<SceneStage2>();
		// �X�e�[�WBGM�Đ�
		SoundManager::GetInstance().playSound(SoundManager::BGM::Stage);
		break;
	}

	// �t�F�[�h�C��
	m_pFade->Start(FADE_IN, FADE_IN_TIME, Fade::FadeColor::Black);

	// ������
	m_NextScene = SceneBase::Scene::None;
}

// ���̃V�[�������Z�b�g
void SceneRoot::SetNextScene(SceneBase::Scene next)
{
	// �t�F�[�h���ɏ������Ȃ�
	if (!m_pFade || m_pFade->GetPlay())
	{
		return;
	}

	// ���̃V�[�����Z�b�g
	m_NextScene = next;

	// �t�F�[�h�A�E�g
	m_pFade->Start(FADE_OUT, FADE_OUT_TIME, Fade::FadeColor::Black);
}

// ���̃V�[�����擾
SceneBase::Scene SceneRoot::GetNextScene()
{
	return m_NextScene;
}

// ���݂̃V�[�����擾
SceneBase::Scene SceneRoot::GetCurrentScene()
{
	return m_CurrentScene;
}
