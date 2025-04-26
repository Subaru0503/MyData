#include "SceneBase.hpp"
#include "DebugMenu.h"
#include "GameObject.hpp"
#include <typeinfo>
#include <string.h>

//----オブジェクト----
#include "CameraDCC.h"
#include "Goal.h"				// ゴール

//----コンポーネント----
#include "BoxCollider.h"		// 当たり判定
#include "ModelRenderer3D.h"	// 2D描画
#include "ModelRenderer2D.h"	// 3D描画

//----マネージャー----
#include "CollisionManager.h"	// 当たり判定管理マネージャー
#include "GameOverManager.h"	// ゲームオーバーマネージャー
#include "TimeManager.h"		// タイムマネージャー
#include "TutorialManager.h"	// チュートリアルマネージャー
#include "StartSetUpManager.h"	// セットアップマネージャー
#include "PauseManager.h"		// ポーズ画面マネージャー
#include "ResetManager.h"		// リセットマネージャー

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
	// サブシーンを削除
	RemoveSubScene();

	// カメラのターゲット設定を無くす
	CameraDCC* cam = GetObj<CameraDCC>("Camera");
	cam->ResetTarget();

	// 削除
	while (!m_items.empty())
	{
		DestroyObj(m_items.begin()->c_str());
	}
	m_items.clear();

	// 削除
	CollisionManager::GetInstance().RemoveALLObj();
	// 判定リセット
	//GameOverManager::GetInstance().Reset();
	// リセット
	TimeManager::GetInstance().ResetTime();
	// リセット
	StartSetUpManager::GetInstance().Reset();

	// 親の参照を削除
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
	// 更新処理
	if (m_name == "Root" || m_name == "Title")
	{
		ParentorTitleObjUpdate();
	}
	else
	{
		StageObjUpdate();
	}

	// シーン自体の更新(クリア判定など
	Update(tick);

	// サブシーンの更新
	if (m_pSubScene)
	{
		m_pSubScene->_update(tick);
	}
	// フェード更新処理
	if (m_pFade)
	{
		m_pFade->Update();
	}
}
void SceneBase::_draw()
{
	// シーンの描画処理
	Draw();

	// 子のシーン描画処理
	if (m_pSubScene)
	{
		m_pSubScene->_draw();
	}

	// フェード描画処理
	if (m_pFade)
	{
		// カメラ情報取得
		GameObject* camObj = GetObj<CameraDCC>("Camera");
		Camera* pCamera = camObj->GetComponent<Camera>();

		// フェード描画
		ModelRenderer2D* _modelRenderer2D = m_pFade->GetComponent<ModelRenderer2D>();
		_modelRenderer2D->SetCamera(camObj, pCamera);
		_modelRenderer2D->Draw();
	}
}

// 親のシーンのオブジェクト更新処理
void SceneBase::ParentorTitleObjUpdate()
{
	// シーンが所持しているオブジェクトの更新
	auto itemIt = m_items.begin();
	while (itemIt != m_items.end())
	{
		auto objIt = m_objects.find(*itemIt);

		// 型チェック
		if (objIt != m_objects.end() && objIt->second->isGameObject)
		{
			GameObject* obj = reinterpret_cast<GameObject*>(objIt->second->m_pObj);
			obj->Execute();
		}
		++itemIt;
	}

}

// 子のシーンのオブジェクト更新処理
void SceneBase::StageObjUpdate()
{
	// ゴールオブジェクト取得
	Goal* goal = GetObj<Goal>("Goal1");

	// ゴールフラグが上がってるかゲームオーバーなら
	if (goal && (goal->GetGoalFlg() ||
		GameOverManager::GetInstance().GetGameOverFlg()))
	{
		return;	// オブジェクトの更新処理をストップする
	}

	// チュートリアル中かどうかで更新するものを変える
	if (TutorialManager::GetInstance().GetTutorial())
	{
		return;
	}
	// レディーゴーアニメーション中か確認
	else if (!StartSetUpManager::GetInstance().GetStartSetUp())
	{
		return;
	}
	// ポーズ画面かチェック
	else if (PauseManager::GetInstance().GetPause())
	{
		return;
	}
	// リセット中かチェック
	else if (ResetManager::GetInstance().GetResetFlg())
	{
		return;
	}


	// シーンが所持しているオブジェクトの更新
	auto itemIt = m_items.begin();
	while (itemIt != m_items.end())
	{
		auto objIt = m_objects.find(*itemIt);

		// 型チェック
		if (objIt != m_objects.end() && objIt->second->isGameObject)
		{
			GameObject* obj = reinterpret_cast<GameObject*>(objIt->second->m_pObj);
			obj->Execute();
		}
		++itemIt;
	}
}

/// @brief サブシーンの削除
void SceneBase::RemoveSubScene()
{
	// 削除するサブシーンが存在するか
	if (!m_pSubScene) return;

	// 階層内のサブシーンを優先して削除
	m_pSubScene->RemoveSubScene();

	// 直下のサブシーンを削除
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
		// 型チェック
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
		// 型チェック
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
