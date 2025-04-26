#include "SceneRoot.h"
#include <stdio.h>
#include "CameraDCC.h"
#include "MoveLight.h"
#include "Input.h"
#include "Geometory.h"
#include "DebugMenu.h"

//----シーン関連----
#include "SceneTitle.h"
#include "SceneGame.h"
#include "SceneStage2.h"

//----マネージャー----
#include "TutorialManager.h"
#include "SoundManager.h"
#include "ResetManager.h"

// 静的変数初期化
SceneBase::Scene SceneRoot::m_NextScene = SceneBase::Scene::None;
SceneBase::Scene SceneRoot::m_CurrentScene = SceneBase::Scene::None;

// 初期化
void SceneRoot::Init()
{
	// オブジェクトの作成
	CameraDCC* pCamera = CreateObj<CameraDCC>("Camera");
	MoveLight* pLight = CreateObj<MoveLight>("Light");
	// フェード作成
	CreateSceneObj<Fade>("Fade");
	// 取得
	m_pFade = GetObj<Fade>("Fade");

	// リセットマネージャーにも渡す
	ResetManager::GetInstance().SetFade(m_pFade);

	// 次のシーンをセット
	m_NextScene = SceneBase::Scene::TITLE;

#ifdef _DEBUG
	// グリッド表示
	debug::Item* camera = debug::Item::CreateGroup("Grid");
	camera->AddGroupItem(debug::Item::CreateValue("Enable",	debug::Item::Bool,	true));
	camera->AddGroupItem(debug::Item::CreateValue("Size",	debug::Item::Float, true));
	camera->AddGroupItem(debug::Item::CreateValue("Margin",	debug::Item::Float, true));
	camera->AddGroupItem(debug::Item::CreateValue("Color",	debug::Item::Color, true));
	camera->AddGroupItem(debug::Item::CreateValue("Axis",	debug::Item::Bool,	true));
	debug::Menu::Get("00_Info").AddItem(camera);

	// シーン表示
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
 * シーンのメモリ解放
 * @brief 終了処理
 */
void SceneRoot::Uninit()
{
}

/**
 * @fn
 * シーンの更新処理
 * @brief 更新処理
 */
void SceneRoot::Update(float tick)
{
	if (!m_pFade) return;

	// 次のシーンがセットされていたら
	if (!m_pFade->GetPlay() && m_NextScene != SceneBase::Scene::None)
	{
		SceneChange();	// シーン切り替え
	}

	// 再生終了したスピーカーを破棄
	SoundManager::GetInstance().DeleteSpeaker();
}

/**
 * @fn
 * シーンの描画処理
 * @brief 描画処理
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

		// 網掛け描画
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
		// 軸描画
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

// シーン切り替え
void SceneRoot::SceneChange()
{
	// 全て破棄
	SoundManager::GetInstance().AllDeleteSpeaker();

	// シーン情報更新
	m_CurrentScene = m_NextScene;

	// シーン切り替え
	switch (m_NextScene)
	{
	// タイトル
	case SceneBase::Scene::TITLE:
		AddSubScene<SceneTitle>();
		// タイトルBGM再生
		SoundManager::GetInstance().playSound(SoundManager::BGM::Title);
		break;
	// ゲーム
	case SceneBase::Scene::GAME:
		AddSubScene<SceneGame>();
		// ステージBGM再生
		SoundManager::GetInstance().playSound(SoundManager::BGM::Stage);
		break;
	case SceneBase::Scene::STAGE2:
		AddSubScene<SceneStage2>();
		// ステージBGM再生
		SoundManager::GetInstance().playSound(SoundManager::BGM::Stage);
		break;
	}

	// フェードイン
	m_pFade->Start(FADE_IN, FADE_IN_TIME, Fade::FadeColor::Black);

	// 初期化
	m_NextScene = SceneBase::Scene::None;
}

// 次のシーン情報をセット
void SceneRoot::SetNextScene(SceneBase::Scene next)
{
	// フェード中に処理しない
	if (!m_pFade || m_pFade->GetPlay())
	{
		return;
	}

	// 次のシーンをセット
	m_NextScene = next;

	// フェードアウト
	m_pFade->Start(FADE_OUT, FADE_OUT_TIME, Fade::FadeColor::Black);
}

// 次のシーンを取得
SceneBase::Scene SceneRoot::GetNextScene()
{
	return m_NextScene;
}

// 現在のシーンを取得
SceneBase::Scene SceneRoot::GetCurrentScene()
{
	return m_CurrentScene;
}
