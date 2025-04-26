#include "SceneBase.hpp"
#include "DebugMenu.h"
#include "GameObject.hpp"
#include <typeinfo>
#include <string.h>

//----�I�u�W�F�N�g----
#include "CameraDCC.h"
#include "Goal.h"				// �S�[��

//----�R���|�[�l���g----
#include "BoxCollider.h"		// �����蔻��
#include "ModelRenderer3D.h"	// 2D�`��
#include "ModelRenderer2D.h"	// 3D�`��

//----�}�l�[�W���[----
#include "CollisionManager.h"	// �����蔻��Ǘ��}�l�[�W���[
#include "GameOverManager.h"	// �Q�[���I�[�o�[�}�l�[�W���[
#include "TimeManager.h"		// �^�C���}�l�[�W���[
#include "TutorialManager.h"	// �`���[�g���A���}�l�[�W���[
#include "StartSetUpManager.h"	// �Z�b�g�A�b�v�}�l�[�W���[
#include "PauseManager.h"		// �|�[�Y��ʃ}�l�[�W���[
#include "ResetManager.h"		// ���Z�b�g�}�l�[�W���[

Fade* SceneBase::m_pFade = nullptr;

SceneBase::Objects SceneBase::m_objects;
#ifdef _DEBUG
debug::Item* SceneBase::hierarchy;
debug::Item* SceneBase::inspector;
#endif

SceneBase::SceneBase(const char* name)
	: m_pParent(nullptr)
	, m_pSubScene(nullptr)
	, m_name(name)
	, m_ObjUpdateStopFlg(false)
{
}
SceneBase::~SceneBase()
{
	// �T�u�V�[�����폜
	RemoveSubScene();

	// �J�����̃^�[�Q�b�g�ݒ�𖳂���
	CameraDCC* cam = GetObj<CameraDCC>("Camera");
	cam->ResetTarget();

	// �폜
	while (!m_items.empty())
	{
		DestroyObj(m_items.begin()->c_str());
	}
	m_items.clear();

	// �폜
	CollisionManager::GetInstance().RemoveALLObj();
	// ���胊�Z�b�g
	//GameOverManager::GetInstance().Reset();
	// ���Z�b�g
	TimeManager::GetInstance().ResetTime();
	// ���Z�b�g
	StartSetUpManager::GetInstance().Reset();

	// �e�̎Q�Ƃ��폜
	if(m_pParent)
		m_pParent->m_pSubScene = nullptr;
}
void SceneBase::Initialize()
{
#ifdef _DEBUG
	debug::Menu::Create("Inspector");
	debug::Window& window = debug::Menu::Create("Hierarchy");
	hierarchy = debug::Item::CreateList("Name", [](const void* arg)
		{
			const char* name = reinterpret_cast<const char*>(arg);
			auto it = m_objects.find(name);
			if (it == m_objects.end()) return;
			auto& window = debug::Menu::Get("Inspector");
			window.Clear();
			window.AddItem(debug::Item::CreateValue(it->first.c_str(), debug::Item::Label));
			if (!it->second->isGameObject) return;
			
			static_cast<GameObject*>(it->second->m_pObj)->Debug(&window);
		});
	window.AddItem(hierarchy);
#endif
}
void SceneBase::_update(float tick)
{
	// �X�V����
	if (m_name == "Root" || m_name == "Title")
	{
		ParentorTitleObjUpdate();
	}
	else
	{
		StageObjUpdate();
	}

	// �V�[�����̂̍X�V(�N���A����Ȃ�
	Update(tick);

	// �T�u�V�[���̍X�V
	if (m_pSubScene)
	{
		m_pSubScene->_update(tick);
	}
	// �t�F�[�h�X�V����
	if (m_pFade)
	{
		m_pFade->Update();
	}
}
void SceneBase::_draw()
{
	// �V�[���̕`�揈��
	Draw();

	// �q�̃V�[���`�揈��
	if (m_pSubScene)
	{
		m_pSubScene->_draw();
	}

	// �t�F�[�h�`�揈��
	if (m_pFade)
	{
		// �J�������擾
		GameObject* camObj = GetObj<CameraDCC>("Camera");
		Camera* pCamera = camObj->GetComponent<Camera>();

		// �t�F�[�h�`��
		ModelRenderer2D* _modelRenderer2D = m_pFade->GetComponent<ModelRenderer2D>();
		_modelRenderer2D->SetCamera(camObj, pCamera);
		_modelRenderer2D->Draw();
	}
}

// �e�̃V�[���̃I�u�W�F�N�g�X�V����
void SceneBase::ParentorTitleObjUpdate()
{
	// �V�[�����������Ă���I�u�W�F�N�g�̍X�V
	auto itemIt = m_items.begin();
	while (itemIt != m_items.end())
	{
		auto objIt = m_objects.find(*itemIt);

		// �^�`�F�b�N
		if (objIt != m_objects.end() && objIt->second->isGameObject)
		{
			GameObject* obj = reinterpret_cast<GameObject*>(objIt->second->m_pObj);
			obj->Execute();
		}
		++itemIt;
	}

}

// �q�̃V�[���̃I�u�W�F�N�g�X�V����
void SceneBase::StageObjUpdate()
{
	// �S�[���I�u�W�F�N�g�擾
	Goal* goal = GetObj<Goal>("Goal1");

	// �S�[���t���O���オ���Ă邩�Q�[���I�[�o�[�Ȃ�
	if (goal && (goal->GetGoalFlg() ||
		GameOverManager::GetInstance().GetGameOverFlg()))
	{
		return;	// �I�u�W�F�N�g�̍X�V�������X�g�b�v����
	}

	// �`���[�g���A�������ǂ����ōX�V������̂�ς���
	if (TutorialManager::GetInstance().GetTutorial())
	{
		return;
	}
	// ���f�B�[�S�[�A�j���[�V���������m�F
	else if (!StartSetUpManager::GetInstance().GetStartSetUp())
	{
		return;
	}
	// �|�[�Y��ʂ��`�F�b�N
	else if (PauseManager::GetInstance().GetPause())
	{
		return;
	}
	// ���Z�b�g�����`�F�b�N
	else if (ResetManager::GetInstance().GetResetFlg())
	{
		return;
	}


	// �V�[�����������Ă���I�u�W�F�N�g�̍X�V
	auto itemIt = m_items.begin();
	while (itemIt != m_items.end())
	{
		auto objIt = m_objects.find(*itemIt);

		// �^�`�F�b�N
		if (objIt != m_objects.end() && objIt->second->isGameObject)
		{
			GameObject* obj = reinterpret_cast<GameObject*>(objIt->second->m_pObj);
			obj->Execute();
		}
		++itemIt;
	}
}

/// @brief �T�u�V�[���̍폜
void SceneBase::RemoveSubScene()
{
	// �폜����T�u�V�[�������݂��邩
	if (!m_pSubScene) return;

	// �K�w���̃T�u�V�[����D�悵�č폜
	m_pSubScene->RemoveSubScene();

	// �����̃T�u�V�[�����폜
	m_pSubScene->Uninit();

	delete m_pSubScene;
	m_pSubScene = nullptr;
}

void SceneBase::DestroyObj(const char* name)
{
	auto obj = m_objects.find(name);
	if (obj == m_objects.end()) return;

	delete obj->second;
	m_objects.erase(obj);

#ifdef _DEBUG
	debug::Window& hieralchy = debug::Menu::Get("Hierarchy");
	hierarchy->RemoveListItem(name);
#endif

	m_items.remove(name);
}

GameObject* SceneBase::Get3DObj(int no)
{
	auto itemIt = m_items.begin();
	while (itemIt != m_items.end())
	{
		auto objIt = m_objects.find(*itemIt);
		// �^�`�F�b�N
		if (objIt != m_objects.end() && objIt->second->isGameObject)
		{
			GameObject* obj = reinterpret_cast<GameObject*>(objIt->second->m_pObj);
			if (obj->Get3DObjNo() == no)
			{
				return obj;
			}
		}
		++itemIt;
	}
	return nullptr;
}

GameObject * SceneBase::Get2DObj(int no)
{
	auto itemIt = m_items.begin();
	while (itemIt != m_items.end())
	{
		auto objIt = m_objects.find(*itemIt);
		// �^�`�F�b�N
		if (objIt != m_objects.end() && objIt->second->isGameObject)
		{
			GameObject* obj = reinterpret_cast<GameObject*>(objIt->second->m_pObj);
			if (obj->Get2DObjNo() == no)
			{
				return obj;
			}
		}
		++itemIt;
	}
	return nullptr;
}
