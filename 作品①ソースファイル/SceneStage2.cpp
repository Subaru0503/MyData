//----インクルード部----
#include "SceneStage2.h"
#include "Model.h"
#include "Camera.h"
#include "Light.h"
#include "Input.h"
#include "Sprite.h"

#include "CameraDCC.h"

//----背景----
#include "SkyDome.h"			// スカイドーム

//----オブジェクト----
#include "Player.h"				// プレイヤー
#include "Ground.h"				// 地面
#include "Goal.h"				// ゴール
#include "PlayerCheckPoint.h"	// プレイヤーチェックポイント

//----ネジ----
#include "Screw.h"				// ネジ
#include "LoosenRate.h"			// 緩んでいくネジ
#include "EndLess.h"			// 一生回せるネジ

//----ギミック----
#include "MoveFloor.h"			// 移動オブジェクト
#include "SpinFloor.h"			// 回転オブジェクト
#include "CheckPointPath.h"		// チェックポイントを移動するギミック
#include "TemporaryFloor.h"		// 一時的に出現する床

//----UI----
//----インゲームUI----
#include "Time.h"				// 時間UI
#include "PauseMozi.h"			// ポーズ文字UI

#include "Clear.h"				// クリアUI
#include "GameOver.h"			// ゲームオーバーUI

//----チュートリアルUI----
#include "Left.h"				// 左矢印
#include "Right.h"				// 右矢印
#include "Start.h"				// ゲームスタート文字
//----ゲーム開始前UI----
#include "Ready.h"				// レディーゴー文字

//---コンポーネント----
#include "ModelRenderer2D.h"	// 2D描画

//----マネージャー----
#include "ShaderManager.h"		// シェーダーマネージャー
#include "CollisionManager.h"	// 当たり判定管理マネージャー
#include "GameOverManager.h"	// ゲームオーバーマネージャー
#include  "TimeManager.h"		// タイムマネージャー
#include "AfterGameOverManager.h"	// アフターゲームオーバーマネージャー
#include "AfterGoalManager.h"	// アフターゴールマネージャー
#include "TutorialManager.h"	// チュートリアルマネージャー
#include "StartSetUpManager.h"	// ゲームスタート準備マネージャー
#include "PauseManager.h"		// ポーズ画面マネージャー
#include "SoundManager.h"		// サウンドマネージャー
#include "ResetManager.h"		// リセットマネージャー

//----システム----
#include <vector>

using namespace std;

// コンストラクタ
void SceneStage2::Init()
{
	// メンバ変数初期化

	// 合計2Dオブジェクト
	m_Total2DObjNo = 0;

	// 合計3Dオブジェクト
	m_Total3DObjNo = 0;

	// 合計時間UI
	m_TotalTimeUINo = 0;

	// 背景
	CreateSceneObj<SkyDome>("SkyDome");	// スカイドーム

	Load();	// ファイル読み込み

	// レディーゴーアニメーション
	CreateSceneObj<Ready>("Ready");
	Ready* obj = GetObj<Ready>("Ready");
	m_Total2DObjNo++;
	obj->Set2DObjNo(m_Total2DObjNo);
	StartSetUpManager::GetInstance().SetStartSetUpUI(obj);

	// カメラ情報取得
	CameraDCC* pCamObj = GetObj<CameraDCC>("Camera");
	// プレイヤー情報取得
	Player* player = GetObj<Player>("Player1");

	// ゲームオーバー管理クラスにプレイヤーの情報を渡す
	GameOverManager::GetInstance().SetPlyer(player);

	// カメラが追従するターゲット設定
	pCamObj->SetTarget(player);

	// スカイドームをカメラ座標に合わせる
	SkyDome* skydome = GetObj<SkyDome>("SkyDome");
	skydome->SetCamera(pCamObj);

}
void SceneStage2::Uninit()
{

	// ゲームオーバー判定リセット
	GameOverManager::GetInstance().Reset();

	// ゲームオーバー後オブジェクト削除
	AfterGameOverManager::GetInstance().Reset();

	// ゴール後オブジェクト削除
	AfterGoalManager::GetInstance().Reset();

	// チュートリアルオブジェクト削除
	TutorialManager::GetInstance().RemoveALLObj();

	// ポーズ画面オブジェクト削除
	PauseManager::GetInstance().RemoveALLObj();
	PauseManager::GetInstance().Reset();

	// リセット対象オブジェクト削除
	ResetManager::GetInstance().RemoveALLObj();
}
void SceneStage2::Update(float tick)
{
	// チュートリアル中はチュートリアルのみ更新
	if (TutorialManager::GetInstance().GetTutorial())
	{
		SkyDome* skydome = GetObj<SkyDome>("SkyDome");
		TutorialManager::GetInstance().Update();
		skydome->Update();
		return;
	}
	// レディーゴーアニメーション
	if (!StartSetUpManager::GetInstance().GetStartSetUp())
	{
		SkyDome* skydome = GetObj<SkyDome>("SkyDome");
		StartSetUpManager::GetInstance().Update();
		skydome->Update();
		return;
	}

	// オブジェクト取得
	Goal* goal = GetObj<Goal>("Goal1");					// ゴール

	// NULLなら処理しない
	if (!goal) return;

	// ゴールしてないかチェック
	if ((!goal->GetGoalFlg() &&
		!GameOverManager::GetInstance().GetGameOverFlg()))
	{
		// ポーズ画面だったらこれ以降処理しない
		if (ProcessNotGoal())	return; // ゴールをしてないときだけする処理をまとめた関数
	}


	// ゲームオーバーフラグが上がってたら
	if (GameOverManager::GetInstance().GetGameOverFlg())
	{
		// nullptrか確認
		if (AfterGameOverManager::GetInstance().GetObj())
		{
			GameOverUICreate();	// ゲームオーバー後のUI作成
		}

		// ゲームオーバー後更新処理
		AfterGameOverManager::GetInstance().Update();
	}
	// ゴールフラグが上がってたら
	else if (goal->GetGoalFlg())
	{
		// nullptrか確認
		if (AfterGoalManager::GetInstance().GetObj())
		{
			GoalUICreate();		// ゴール後のUI作成
		}

		// ゴール後更新処理
		AfterGoalManager::GetInstance().Update();
	}

}

// 描画
void SceneStage2::Draw()
{
	// カメラ、ライト取得
	GameObject* pObjs[] = {
		GetObj<GameObject>("Camera"),
	};

	// カメラコンポーネント取得
	Camera* pCamera = pObjs[0]->GetComponent<Camera>();

	// 描画前準備
	RenderTarget* pRTV = GetObj<RenderTarget>("RTV");

	// 深度バッファ取得
	DepthStencil* pDSV = GetObj<DepthStencil>("DSV");

	// スカイドーム描画
	SetRenderTargets(1, &pRTV, nullptr);

	GameObject* skyDome = GetObj<GameObject>("SkyDome");
	ModelRenderer3D* _modelRenderer3D = skyDome->GetComponent<ModelRenderer3D>();
	// セット
	_modelRenderer3D->SetCamera(pCamera);
	// 描画
	_modelRenderer3D->Draw();

	// 3D描画用のレンダーターゲットにする
	SetRenderTargets(1, &pRTV, pDSV);

	// オブジェクト番号を登録した3Dオブジェクト分ループする
	for (int j = 1; j <= m_Total3DObjNo; j++)
	{
		// 3Dモデルレンダラーコンポーネント取得
		_modelRenderer3D = Get3DObj(j)->GetComponent<ModelRenderer3D>();

		// 3Dモデルレンダラーを持ってたら処理する
		if (_modelRenderer3D)
		{
			// セット
			_modelRenderer3D->SetCamera(pCamera);

			// 描画
			_modelRenderer3D->Draw();
		}
	}

	// 2D描画ように設定する
	SetRenderTargets(1, &pRTV, nullptr);

	// オブジェクト番号を登録した2Dオブジェクト分ループする
	for (int j = 1; j <= m_Total2DObjNo; j++)
	{
		// 2Dモデルレンダラーコンポーネント取得
		ModelRenderer2D*  _modelRenderer2D = Get2DObj(j)->GetComponent<ModelRenderer2D>();

		// 2Dモデルレンダラーを持ってたら処理する
		if (_modelRenderer2D)
		{
			// セット
			_modelRenderer2D->SetCamera(pObjs[0], pCamera);

			// 描画
			_modelRenderer2D->Draw();
		}
	}

}

// ゴールしてないときだけする処理
bool SceneStage2::ProcessNotGoal()
{
	// リセットボタンが押されたかチェック
	ResetManager::GetInstance().Update();

	// 当たり判定チェック
	CollisionManager::GetInstance().Update();

	// ゲームオーバーチェック
	GameOverManager::GetInstance().Update();

	// 時間UI処理
	TimeManager::GetInstance().Update();

	// ポーズ画面を開く
	if (!PauseManager::GetInstance().GetPause() && IsKeyTrigger(VK_ESCAPE))
	{
		// ポーズ画面フラグを上げる
		PauseManager::GetInstance().PauseOpen();

		// ポーズ画面を開くSE
		SoundManager::GetInstance().playSound(SoundManager::SystemSE::Pause);
		return true;
	}
	// ポーズ画面が開いてたら
	else if (PauseManager::GetInstance().GetPause())
	{
		// スカイドーム取得
		SkyDome* skydome = GetObj<SkyDome>("SkyDome");

		// ポーズ画面更新処理処理
		PauseManager::GetInstance().Update();

		// スカイドーム更新処理
		skydome->Update();

		return true;
	}

	return false;
}

// ステージ作成
void SceneStage2::Load()
{
	//----ステージ生成----

	// ファイル読み込み
	ifstream file("Assets/Map/Stage2.csv");

	// セルの読み込み用
	string cell;

	// 行数格納用
	int MaxLine;		
	
	// 制限時間
	float time;

	// チェックポイント
	vector<float3> checkPoint;

	// ファイルが読み込めてるか
	if (!file)
	{
		MessageBox(NULL, "Stage2.csvファイルが読み込めませんでした", "SceneStage2.cpp", MB_OK);
		return;
	}

	// 行数情報取得
	getline(file, cell, ',');

	// 行数格納
	MaxLine = stoi(cell);

	// 3行目まで移動
	getline(file, cell);
	getline(file, cell);

	// ファイルからデータを読み込む
	for (int i = 0; i < MaxLine; i++)
	{
		// オブジェクトに種類取得
		getline(file, cell, ',');

		// オブジェクトごとに処理をわける
		if (cell == "Player")
		{
			// プレイヤー作成
			PlayerCreate(file, cell);
		}
		else if (cell == "Ground")
		{
			// 地面作成
			GroundCreate(file, cell);
		}
		else if (cell == "Goal")
		{
			// ゴール作成
			GoalCreate(file, cell);
		}
		else if (cell == "Screw")
		{
			// ネジ作成
			ScrewCreate(file, cell);
		}
		else if (cell == "Gimmick")
		{
			// ギミック作成
			GimmickCreate(file, cell);
		}
		else if (cell == "CheckPoint")
		{
			float3 pos;

			// 番号取得
			getline(file, cell, ',');

			// 座標

			// X座標取得
			getline(file, cell, ',');

			// float型に変換して設定
			pos.x = stof(cell);

			// Z座標取得
			getline(file, cell, ',');

			// float型に変換して設定
			pos.z = stof(cell);

			// Y座標取得
			getline(file, cell, ',');

			// float型に変換
			pos.y = stof(cell);

			// チェックポイント追加
			checkPoint.push_back(pos);
		}
		else if (cell == "PlayerCheckPoint")
		{
			// プレイヤーチェックポイント作成
			PlayerCheckPointCreate(file, cell);
		}

		// 次の行へ
		getline(file, cell);
	}

	// ファイルを閉じる
	file.close();


	//----ギミックに対応するネジの設定----

	// ファイル読み込み
	file.open("Assets/TargetScrew/Stage2TargetScrew.csv");

	// ファイルが読み込めてるか
	if (!file)
	{
		MessageBox(NULL, "Stage2TargetScrew.csvファイルが読み込めませんでした", "SceneGame.cpp", MB_OK);
		return;
	}

	// 行数情報取得
	getline(file, cell, ',');

	// 行数格納
	MaxLine = stoi(cell);

	// 3行目まで移動
	getline(file, cell);
	getline(file, cell);

	// ファイルからデータを読み込む
	for (int i = 0; i < MaxLine; i++)
	{
		// ギミックに対象のネジを設定する
		SetTargetScrew(file, cell);

		// 次の行へ
		getline(file, cell);
	}

	// ファイルを閉じる
	file.close();


	//----チェックポイント設定----

	// ファイル読み込み
	file.open("Assets/CheckPoint/Stage2CheckPoint.csv");

	// ファイルが読み込めてるか
	if (!file)
	{
		MessageBox(NULL, "Stage2CheckPoint.csvファイルが読み込めませんでした", "SceneGame.cpp", MB_OK);
		return;
	}

	// 行数情報取得
	getline(file, cell, ',');

	// 行数格納
	MaxLine = stoi(cell);

	// 3行目まで移動
	getline(file, cell);
	getline(file, cell);

	// ファイルからデータを読み込む
	for (int i = 0; i < MaxLine; i++)
	{
		// ギミックのチェックポイント設定
		SetCheckPoint(file, cell, checkPoint);

		// 次の行へ
		getline(file, cell);
	}

	// ファイルを閉じる
	file.close();


	//----チェックポイント設定----

// ファイル読み込み
	file.open("Assets/Temporary/Stage2TemporaryFloor.csv");

	// ファイルが読み込めてるか
	if (!file)
	{
		MessageBox(NULL, "Stage2TemporaryFloor.csvファイルが読み込めませんでした", "SceneGame.cpp", MB_OK);
		return;
	}

	// 行数情報取得
	getline(file, cell, ',');

	// 行数格納
	MaxLine = stoi(cell);

	// 3行目まで移動
	getline(file, cell);
	getline(file, cell);

	// ファイルからデータを読み込む
	for (int i = 0; i < MaxLine; i++)
	{
		// 一時的に出現する床の情報設定
		SetTemporaryInfo(file, cell);

		// 次の行へ
		getline(file, cell);
	}

	// ファイルを閉じる
	file.close();


	//----ステージUI生成----

	// ファイル読み込み
	file.open("Assets/UI/InGame/UI.csv");	// ファイルオープン

	// ファイルが読み込めてるか
	if (!file)
	{
		MessageBox(NULL, "UI.csvファイルが読み込めませんでした", "SceneStage2.cpp", MB_OK);
		return;
	}

	// 行数情報取得
	getline(file, cell, ',');

	// 行数格納
	MaxLine = stoi(cell);

	// 3行目まで移動
	getline(file, cell);
	getline(file, cell);

	// ファイルからデータを読み込む
	for (int i = 0; i < MaxLine; i++)
	{
		// UI種類取得
		getline(file, cell, ',');

		// オブジェクトごとに処理をわける
		if (cell == "Time")
		{
			// 時間UI作成
			TimeCreate(file, cell);
		}
		else if (cell == "PauseMozi")
		{
			// ポーズ文字UI作成
			PauseMoziUICreate(file, cell);
		}
		else
		{
			// ゴールUI作成
			InGameNormalUICreate(file, cell);
		}

		// 次の行へ
		getline(file, cell);
	}

	// ファイルを閉じる
	file.close();


	//----制限時間設定----

	// ファイル読み込み
	file.open("Assets/Time/TimeParam.csv");

	// ファイルが読み込めてるか
	if (!file)
	{
		MessageBox(NULL, "TimeParam.csvファイルが読み込めませんでした", "SceneStage2.cpp", MB_OK);
		return;
	}

	// 2行目まで移動
	getline(file, cell);
	getline(file, cell);

	// ステージ名取得
	getline(file, cell, ',');	// セル(1列目)
	getline(file, cell, ',');	// セル(2列目)

	// 制限時間取得
	time = stof(cell);

	// 制限時間設定
	TimeManager::GetInstance().SetTime(time);

	// ファイルを閉じる
	file.close();


	//----チュートリアルUI生成----

	// ファイル読み込み
	file.open("Assets/UI/Tutorial/Tutorial.csv");	// ファイルオープン

	// ファイルが読み込めてるか
	if (!file)
	{
		MessageBox(NULL, "Tutorial.csvファイルが読み込めませんでした", "SceneStage2.cpp", MB_OK);
		return;
	}

	// 行数情報取得
	getline(file, cell, ',');

	// 行数格納
	MaxLine = stoi(cell);

	// 3行目まで移動
	getline(file, cell);
	getline(file, cell);

	// ファイルからデータを読み込む
	for (int i = 0; i < MaxLine; i++)
	{
		// UI種類取得
		getline(file, cell, ',');

		// UIごとに処理をわける
		if (cell == "Right")
		{
			// 右矢印UI作成
			RightUICreate(file, cell);
		}
		else if (cell == "Left")
		{
			// 左矢印UI作成
			LeftUICreate(file, cell);
		}
		else if (cell == "Start")
		{
			// ゲームスタート文字UI作成
			StartUICreate(file, cell);
		}
		else
		{
			// チュートリアル画面UI作成
			MenuNormalUICreate(file, cell);
		}

		// 次の行へ
		getline(file, cell);
	}

	// ファイルを閉じる
	file.close();


	//----ポーズ画面UI生成----

	// ファイル読み込み
	file.open("Assets/UI/Pause/Pause.csv");

	// ファイルが読み込めてるか
	if (!file)
	{
		MessageBox(NULL, "Pause.csvファイルが読み込めませんでした", "SceneStage2.cpp", MB_OK);
		return;
	}

	// 行数情報取得
	getline(file, cell, ',');

	// 行数格納
	MaxLine = stoi(cell);

	// 3行目まで移動
	getline(file, cell);
	getline(file, cell);

	// ファイルからデータを読み込む
	for (int i = 0; i < MaxLine; i++)
	{
		// UIの種類取得
		getline(file, cell, ',');

		// UIごとに処理をわける
		if (cell == "Right")
		{
			// 右矢印UI作成
			RightUICreate(file, cell);
		}
		else if (cell == "Left")
		{
			// 左矢印UI作成
			LeftUICreate(file, cell);
		}
		else
		{
			// ポーズ画面UI作成
			MenuNormalUICreate(file, cell);
		}

		// 次の行へ
		getline(file, cell);
	}

	// ファイルを閉じる
	file.close();
}

// プレイヤー作成
void SceneStage2::PlayerCreate(ifstream& file, string cell)
{
	//----変数宣言----

	// プレイヤー
	Player* player;

	// Boxコライダーコンポーネント
	BoxCollider* _boxCollider;

	// モデルレンダラーコンポーネント
	ModelRenderer3D* _modelRenderer3D;

	// 座標
	DirectX::XMFLOAT3 pos;

	// サイズ
	DirectX::XMFLOAT3 scale;

	// 当たり判定サイズ
	float3 colliderScale;

	// パス
	string path;

	// オブジェクトに関連づける名前
	string objName = cell;

	// リセット有無
	string reset;


	//----データ取得----

	// オブジェクトNo取得
	getline(file, cell, ',');

	// オブジェクトカウントアップ
	m_Total3DObjNo++;

	// 名前作成
	objName += cell;


	// X座標取得
	getline(file, cell, ',');

	// float型に変換して設定
	pos.x = stof(cell);

	// Z座標取得
	getline(file, cell, ',');

	// float型に変換して設定
	pos.z = stof(cell);

	// Y座標取得
	getline(file, cell, ',');

	// float型に変換して設定
	pos.y = stof(cell);


	// Xサイズ取得
	getline(file, cell, ',');

	// float型に変換して設定
	scale.x = stof(cell);

	// Zサイズ取得
	getline(file, cell, ',');

	// float型に変換して設定
	scale.z = stof(cell);

	// Yサイズ取得
	getline(file, cell, ',');

	// float型に変換して設定
	scale.y = stof(cell);


	// モデル名取得
	getline(file, cell, ',');

	// パス作成
	path = "Assets/Model/" + cell + "/" + cell + ".fbx";

	// 対象項目までずらす
	// ネジの種類
	getline(file, cell, ',');
	// ネジとナットの距離
	getline(file, cell, ',');
	// ネジとナットの最長距離
	getline(file, cell, ',');
	// トルク
	getline(file, cell, ',');
	// モーメント
	getline(file, cell, ',');
	// ネジ効果倍率
	getline(file, cell, ',');
	// 効果反転
	getline(file, cell, ',');

	// リセット機能有無取得
	getline(file, cell, ',');
	reset = cell;


	//----設定----

	// プレイヤー作成
	CreateSceneObj<Player>(objName.c_str());

	// プレイヤー取得
	player = GetObj<Player>(objName.c_str());

	// オブジェクトナンバーセット
	player->Set3DObjNo(m_Total3DObjNo);

	// 座標セット
	player->SetPos(pos);

	// サイズセット
	player->SetScale(scale);

	// ボックスコライダーコンポーネント取得
	_boxCollider = player->GetComponent<BoxCollider>();

	// 3Dモデルレンダラーコンポーネント取得
	_modelRenderer3D = player->GetComponent<ModelRenderer3D>();

	// サイズを取得
	colliderScale = float3::Tofloat3(scale);

	// 当たり判定用に調整
	colliderScale /= 2;

	// サイズ設定
	_boxCollider->SetScale(colliderScale);

	// モデル読み込み
	_modelRenderer3D->SetPath(path);

	// リセット機能ありなら
	if (reset == "TRUE")
	{
		// オブジェクト設定
		ResetManager::GetInstance().SetObj(player);
	}

	// 当たり判定処理のマネージャーに追加
	CollisionManager::GetInstance().AddObj(player);
}

// 地面作成
void SceneStage2::GroundCreate(ifstream & file, string cell)
{
	//----変数宣言----

	// 地面
	Ground* ground;

	// Boxコライダーコンポーネント
	BoxCollider* _boxCollider;

	// モデルレンダラーコンポーネント
	ModelRenderer3D* _modelRenderer3D;

	// 座標
	DirectX::XMFLOAT3 pos;

	// サイズ
	DirectX::XMFLOAT3 scale;

	// 当たり判定サイズ
	float3 colliderScale;

	// パス
	string path;

	// オブジェクトに関連づける名前
	string objName = cell;


	//----データ取得----

	// オブジェクトNo取得
	getline(file, cell, ',');

	// オブジェクトカウントアップ
	m_Total3DObjNo++;

	// 名前作成
	objName += cell;


	// X座標取得
	getline(file, cell, ',');

	// float型に変換して設定
	pos.x = stof(cell);

	// Z座標取得
	getline(file, cell, ',');

	// float型に変換して設定
	pos.z = stof(cell);

	// Y座標取得
	getline(file, cell, ',');

	// float型に変換して設定
	pos.y = stof(cell);


	// Xサイズ取得
	getline(file, cell, ',');

	// float型に変換して設定
	scale.x = stof(cell);

	// Zサイズ取得
	getline(file, cell, ',');

	// float型に変換して設定
	scale.z = stof(cell);

	// Yサイズ取得
	getline(file, cell, ',');

	// float型に変換して設定
	scale.y = stof(cell);


	// モデル名取得
	getline(file, cell, ',');

	// パス作成
	path = "Assets/Model/" + cell + "/" + cell + ".fbx";


	//----設定----

	// 地面作成
	CreateSceneObj<Ground>(objName.c_str());

	// 地面取得
	ground = GetObj<Ground>(objName.c_str());

	// オブジェクトナンバーセット
	ground->Set3DObjNo(m_Total3DObjNo);

	// 座標セット
	ground->SetPos(pos);

	// サイズセット
	ground->SetScale(scale);

	// ボックスコライダーコンポーネント取得
	_boxCollider = ground->GetComponent<BoxCollider>();

	// 3Dモデルレンダラーコンポーネント取得
	_modelRenderer3D = ground->GetComponent<ModelRenderer3D>();

	// 当たり判定取得
	colliderScale = float3::Tofloat3(scale);

	// 当たり判定用に調整
	colliderScale /= 2;

	// サイズ設定
	_boxCollider->SetScale(colliderScale);

	// モデル読み込み
	_modelRenderer3D->SetPath(path);

	// 当たり判定処理のマネージャーに追加
	CollisionManager::GetInstance().AddObj(ground);
}

// ゴール作成
void SceneStage2::GoalCreate(ifstream & file, string cell)
{
	//----変数宣言----

	// ゴール
	Goal* goal;

	// Boxコライダーコンポーネント
	BoxCollider* _boxCollider;

	// モデルレンダラーコンポーネント
	ModelRenderer3D* _modelRenderer3D;

	// 座標
	DirectX::XMFLOAT3 pos;

	// サイズ
	DirectX::XMFLOAT3 scale;

	// 当たり判定サイズ
	float3 colliderScale;

	// パス
	string path;

	// オブジェクトに関連づける名前
	string objName = cell;

	
	//----データ取得----

	// オブジェクトNo取得
	getline(file, cell, ',');
	// オブジェクトカウントアップ
	m_Total3DObjNo++;

	// 名前作成
	objName += cell;

	// X座標取得
	getline(file, cell, ',');

	// float型に変換して設定
	pos.x = stof(cell);

	// Z座標取得
	getline(file, cell, ',');

	// float型に変換して設定
	pos.z = stof(cell);

	// Y座標取得
	getline(file, cell, ',');

	// float型に変換して設定
	pos.y = stof(cell);


	// Xサイズ取得
	getline(file, cell, ',');

	// float型に変換して設定
	scale.x = stof(cell);

	// Zサイズ取得
	getline(file, cell, ',');

	// float型に変換して設定
	scale.z = stof(cell);

	// Yサイズ取得
	getline(file, cell, ',');

	// float型に変換して設定
	scale.y = stof(cell);

	// モデル名取得
	getline(file, cell, ',');

	// パス作成
	path = "Assets/Model/" + cell + "/" + cell + ".fbx";


	//----設定----

	// ゴール作成
	CreateSceneObj<Goal>(objName.c_str());

	// ゴールの取得
	goal = GetObj<Goal>(objName.c_str());

	// オブジェクトナンバーセット
	goal->Set3DObjNo(m_Total3DObjNo);

	// 座標セット
	goal->SetPos(pos);

	// サイズセット
	goal->SetScale(scale);

	// ボックスコライダーコンポーネント取得
	_boxCollider = goal->GetComponent<BoxCollider>();

	// 3Dモデルレンダラーコンポーネント取得
	_modelRenderer3D = goal->GetComponent<ModelRenderer3D>();

	// モデル読み込み
	_modelRenderer3D->SetPath(path);

	// サイズ取得
	colliderScale = float3::Tofloat3(scale);

	// 当たり判定用に調整
	colliderScale /= 2.0f;

	// サイズセット
	_boxCollider->SetScale(colliderScale);

	// 当たり判定処理のマネージャーに追加
	CollisionManager::GetInstance().AddObj(goal);
}

// ネジ作成
void SceneStage2::ScrewCreate(ifstream & file, string cell)
{
	//----変数宣言----

	// ネジ
	Screw* screw;

	// ナット
	GameObject* nut;

	// Boxコライダーコンポーネント
	BoxCollider* _boxCollider;

	// モデルレンダラーコンポーネント
	ModelRenderer3D* _modelRenderer3D;

	// ネジ番号
	int screwNo;

	// 座標
	DirectX::XMFLOAT3 pos;

	// サイズ
	DirectX::XMFLOAT3 scale;

	// 当たり判定サイズ
	float3 colliderScale;

	// パス
	string path;

	// パス名一部変更の対象
	string targetName = "Screw";

	// 置き換える名前
	string NutName = "Nut";

	// ネジの種類
	string screwType;

	// ナットとの距離
	float nutDistance;

	// ナットとの最長距離
	float nutMaxDistance;

	// トルク
	float torque;

	// モーメント
	float moment;

	// ネジを回したときの効果倍率
	float mul;

	// オブジェクトに関連づける名前
	string objName = cell;

	// リセット有無
	string reset;


	//----データ取得----

	// オブジェクトNo取得
	getline(file, cell, ',');

	// オブジェクトカウントアップ
	m_Total3DObjNo++;	

	// ネジ番号
	screwNo = stoi(cell) + (stoi(cell) - 1);

	// 名前作成
	objName += cell;


	// X座標取得
	getline(file, cell, ',');

	// float型に変換して設定
	pos.x = stof(cell);

	// Z座標取得
	getline(file, cell, ',');

	// float型に変換して設定
	pos.z = stof(cell);

	// Y座標取得
	getline(file, cell, ',');

	// float型に変換して設定
	pos.y = stof(cell);


	// Xサイズ取得
	getline(file, cell, ',');

	// float型に変換して設定
	scale.x = stof(cell);

	// Zサイズ取得
	getline(file, cell, ',');

	// float型に変換して設定
	scale.z = stof(cell);

	// Yサイズ取得
	getline(file, cell, ',');

	// float型に変換して設定
	scale.y = stof(cell);


	// モデル名取得
	getline(file, cell, ',');

	// パス作成
	path = "Assets/Model/" + cell + "/" + cell + ".fbx";


	// ネジの種類取得
	getline(file, cell, ',');

	// ネジの種類設定
	screwType = cell;

	// ナットとの距離
	getline(file, cell, ',');

	// float型に変換して設定
	nutDistance = stof(cell);

	// ナットとの最長距離取得
	getline(file, cell, ',');

	// float型に変換して設定
	nutMaxDistance = stof(cell);

	// トルク取得
	getline(file, cell, ',');

	// float型に変換して設定
	torque = stof(cell);


	// モーメント取得
	getline(file, cell, ',');

	// float型に変換して設定
	moment = stof(cell);

	// ネジ効果倍率取得
	getline(file, cell, ',');

	// float型に変換して設定
	mul = stof(cell);

	// 対象項目までずらす
	// 効果反転
	getline(file, cell, ',');

	// リセット機能有無取得
	getline(file, cell, ',');
	reset = cell;


	//----設定----
	// ネジ作成
	if (screwType == "LoosenRate")
	{
		// 締めた後緩んでいくネジ作成
		CreateSceneObj<LoosenRate>(objName.c_str());

		// 締めた後緩んでいくネジ取得
		screw = GetObj<LoosenRate>(objName.c_str());
	}
	else if (screwType == "EndLess")
	{
		// 一生回せるネジ作成
		CreateSceneObj<EndLess>(objName.c_str());

		// 一生回せるネジ取得
		screw = GetObj<EndLess>(objName.c_str());
	}
	else
	{
		// 通常ネジ作成
		CreateSceneObj<Screw>(objName.c_str());

		// 通常ネジ取得
		screw = GetObj<Screw>(objName.c_str());
	}

	// オブジェクトナンバーセット
	screw->Set3DObjNo(m_Total3DObjNo);

	// 座標セット
	screw->SetPos(pos);

	// サイズセット
	screw->SetScale(scale);

	// 角度初期化
	screw->SetQuat(DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	// 3Dモデルレンダラーコンポーネント取得
	_modelRenderer3D = screw->GetComponent<ModelRenderer3D>();

	// モデル読み込み
	_modelRenderer3D->SetPath(path);

	// ナットとの最長距離設定
	screw->SetNutMaxDistance(nutMaxDistance);

	// トルク、モーメント設定
	screw->SetSpinParam(torque, moment);

	// 効果倍率設定
	screw->SetMultiplier(mul);

	// リセット機能ありなら
	if (reset == "TRUE")
	{
		// 座標保持
		screw->SetInitePos(pos);

		// オブジェクト設定
		ResetManager::GetInstance().SetObj(screw);
	}

	// 当たり判定処理のマネージャーに追加
	CollisionManager::GetInstance().AddObj(screw);


	//----ナットの作成、設定----
	// 番号増加
	m_Total3DObjNo++;

	// 名前作成
	objName = "Nut" + to_string(screwNo);

	// サイズ設定
	scale = DirectX::XMFLOAT3(1.1f, 1.1f, 1.1f);

	// ナット作成
	CreateSceneObj<GameObject>(objName.c_str());

	// ナット取得
	nut = GetObj<GameObject>(objName.c_str());

	// オブジェクト番号セット
	nut->Set3DObjNo(m_Total3DObjNo);

	// ナットの位置
	pos.y -= nutDistance;

	// 座標セット
	nut->SetPos(pos);

	// サイズセット
	nut->SetScale(scale);

	// タグ設定
	nut->SetTag("Nut");

	// ボックスコライダーコンポーネント追加
	nut->AddComponent<BoxCollider>();

	// 3Dモデルレンダラーコンポーネント追加
	nut->AddComponent<ModelRenderer3D>();

	// ボックスコライダーコンポーネント取得
	_boxCollider = nut->GetComponent<BoxCollider>();

	// 3Dモデルレンダラーコンポーネント取得
	_modelRenderer3D = nut->GetComponent<ModelRenderer3D>();

	// サイズ取得
	colliderScale = float3::Tofloat3(scale);

	// 当たり判定用に調整
	colliderScale /= 2.0f;

	// 当たり判定サイズセット
	_boxCollider->SetScale(colliderScale);


	// ScrewをNutに置換
	size_t namePos = path.find(targetName);
	while (namePos != string::npos)
	{
		// Nutに置換
		path.replace(namePos, targetName.length(), "Nut");

		// 次の位置を検索
		namePos = path.find(targetName, namePos + NutName.length());
	}

	// モデル読み込み
	_modelRenderer3D->SetPath(path);

	// シェーダーファイル
	const char* Shaderfile[] = {
		"VS_Object",
		"PS_TexColor",
	};

	// シェーダーセット
	_modelRenderer3D->SetShader(Shaderfile);

	// ナットセット
	screw->SetNut(nut);

	// 当たり判定処理のマネージャーに追加
	CollisionManager::GetInstance().AddObj(nut);
}

// ギミック作成
void SceneStage2::GimmickCreate(ifstream & file, string cell)
{
	//----変数宣言----

	// ギミック
	GimmickBase* gimmick;

	// Boxコライダーコンポーネント
	BoxCollider* _boxCollider;

	// モデルレンダラーコンポーネント
	ModelRenderer3D* _modelRenderer3D;

	// 座標
	DirectX::XMFLOAT3 pos;

	// サイズ
	DirectX::XMFLOAT3 scale;

	// 当たり判定サイズ
	float3 colliderScale;

	// パス
	string path;

	// 効果反転フラグ
	string InvertFrg;

	// クラス名
	string className;

	// ペアギミック
	string pairName = "";

	// 移動量
	float move = 1.0f;
    
	// オブジェクトに関連づける名前
	string objName = cell;

	// リセット有無
	string reset;


	//----データ取得----

	// オブジェクトNo取得
	getline(file, cell, ',');

	// オブジェクトカウントアップ
	m_Total3DObjNo++;

	// 名前
	objName += cell;

	// X座標取得
	getline(file, cell, ',');

	// float型に変換して設定
	pos.x = stof(cell);

	// Z座標取得
	getline(file, cell, ',');

	// float型に変換して設定
	pos.z = stof(cell);

	// Y座標取得
	getline(file, cell, ',');

	// float型に変換して設定
	pos.y = stof(cell);


	// Xサイズ取得
	getline(file, cell, ',');

	// float型に変換して設定
	scale.x = stof(cell);

	// Zサイズ取得
	getline(file, cell, ',');

	// float型に変換して設定
	scale.z = stof(cell);

	// Yサイズ
	getline(file, cell, ',');

	// float型に変換
	scale.y = stof(cell);


	// モデル名取得
	getline(file, cell, ',');

	// パス作成
	path = "Assets/Model/" + cell + "/" + cell + ".fbx";


	// 対象項目までずらす
	getline(file, cell, ',');		// 回転有無
	getline(file, cell, ',');		// ナットとの距離
	getline(file, cell, ',');		// ナットとの最長距離
	getline(file, cell, ',');		// トルク
	getline(file, cell, ',');		// モーメント
	getline(file, cell, ',');		// 効果倍率


	// 効果反転フラグ取得
	getline(file, cell, ',');
	// フラグ設定
	InvertFrg = cell;

	// リセット機能有無
	getline(file, cell, ',');
	reset = cell;

	// ギミック種類取得
	getline(file, cell, ',');

	// クラス名設定
	className = cell;


	// ペアギミック取得
	getline(file, cell, ',');

	// 書いてあるときだけ処理
	if (cell != "")
	{
		// ペアのギミック名
		pairName = "Gimmick" + cell;
	}

	// ギミック移動量取得
	getline(file, cell, ',');

	// 書いてあるときだけ処理
	if (cell != "")
	{
		// float型に変換
		move = stof(cell);
	}


	//----設定----

	// クラス作成
	// タイプ設定
	if (className == "UpDownFloor")
	{
		// ギミック作成
		CreateSceneObj<MoveFloor>(objName.c_str());

		// ギミック取得
		gimmick = GetObj<MoveFloor>(objName.c_str());

		// 子クラスにキャスト
		MoveFloor* moveFloor = dynamic_cast<MoveFloor*>(gimmick);

		// 移動量セット
		moveFloor->SetMove(move);

		// 移動タイプセット
		moveFloor->SetType(MoveFloor::MoveType::UpDown);
	}
	else if (className == "LeftRightFloor")
	{
		// ギミック作成
		CreateSceneObj<MoveFloor>(objName.c_str());

		// ギミック取得
		gimmick = GetObj<MoveFloor>(objName.c_str());

		// 子クラスにキャスト
		MoveFloor* moveFloor = dynamic_cast<MoveFloor*>(gimmick);

		// 移動量セット
		moveFloor->SetMove(move);

		// 移動タイプセット
		moveFloor->SetType(MoveFloor::MoveType::LeftRight);
	}
	else if (className == "YSpin")
	{
		// ギミック作成
		CreateSceneObj<SpinFloor>(objName.c_str());

		// ギミック取得
		gimmick = GetObj<SpinFloor>(objName.c_str());

		// 子クラスにキャスト
		SpinFloor* spinFloor = dynamic_cast<SpinFloor*>(gimmick);

		// 回転タイプセット
		spinFloor->SetType(SpinFloor::SpinType::YSpin);
	}
	else if (className == "CheckPointPath")
	{
		// ギミック作成
		CreateSceneObj<CheckPointPath>(objName.c_str());

		// ギミック取得
		gimmick = GetObj<CheckPointPath>(objName.c_str());

		// 子クラスにキャスト
		CheckPointPath* checkPointPath = dynamic_cast<CheckPointPath*>(gimmick);

		// 移動量セット
		checkPointPath->SetMove(move);
	}
	else if(className == "TemporaryFloor")
	{
		// ギミック作成
		CreateSceneObj<TemporaryFloor>(objName.c_str());

		// ギミック取得
		gimmick = GetObj<TemporaryFloor>(objName.c_str());
	}

	// ペアギミック設定
	if (pairName != "")
	{
		// ギミック取得
		GameObject* pairGimmick = GetObj<GameObject>(pairName.c_str());

		// 情報設定
		gimmick->SetPair(pairGimmick);
	}

	// オブジェクトナンバーセット
	gimmick->Set3DObjNo(m_Total3DObjNo);

	// 座標セット
	gimmick->SetPos(pos);

	// サイズセット
	gimmick->SetScale(scale);

	// 角度初期化
	gimmick->SetQuat(DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	// ボックスコライダーコンポーネント取得
	_boxCollider = gimmick->GetComponent<BoxCollider>();

	// 3Dモデルレンダラーコンポーネント取得
	_modelRenderer3D = gimmick->GetComponent<ModelRenderer3D>();

	// サイズ取得
	colliderScale = float3::Tofloat3(scale);

	// 当たり判定用に調整
	colliderScale /= 2.0f;

	// サイズ設定
	_boxCollider->SetScale(colliderScale);

	// モデル読み込み
	_modelRenderer3D->SetPath(path);

	// ネジの回したときの効果反転
	if (InvertFrg == "TRUE")
	{
		gimmick->SetInvertEffect(true);
	}

	// リセット機能ありなら
	if (reset == "TRUE")
	{
		// 座標保持
		gimmick->SetInitePos(pos);

		// オブジェクト設定
		ResetManager::GetInstance().SetObj(gimmick);
	}

	// 当たり判定処理のマネージャーに追加
	CollisionManager::GetInstance().AddObj(gimmick);
}

// プレイヤーチェックポイント作成
void SceneStage2::PlayerCheckPointCreate(ifstream & file, string cell)
{
	//----変数宣言----

	// プレイヤー
	PlayerCheckPoint* playerCheckPoint;

	// 座標
	DirectX::XMFLOAT3 pos;

	// サイズ
	DirectX::XMFLOAT3 scale;

	// オブジェクトに関連づける名前
	string objName = cell;


	//----データ取得----

	// オブジェクトNo取得
	getline(file, cell, ',');

	// オブジェクトカウントアップ
	m_Total3DObjNo++;

	// 名前作成
	objName += cell;


	// X座標取得
	getline(file, cell, ',');

	// float型に変換して設定
	pos.x = stof(cell);

	// Z座標取得
	getline(file, cell, ',');

	// float型に変換して設定
	pos.z = stof(cell);

	// Y座標取得
	getline(file, cell, ',');

	// float型に変換して設定
	pos.y = stof(cell);


	// Xサイズ取得
	getline(file, cell, ',');

	// float型に変換して設定
	scale.x = stof(cell);

	// Zサイズ取得
	getline(file, cell, ',');

	// float型に変換して設定
	scale.z = stof(cell);

	// Yサイズ取得
	getline(file, cell, ',');

	// float型に変換して設定
	scale.y = stof(cell);


	//----設定----

	// プレイヤーチェックポイント作成
	CreateSceneObj<PlayerCheckPoint>(objName.c_str());

	// プレイヤー取得
	playerCheckPoint = GetObj<PlayerCheckPoint>(objName.c_str());

	// オブジェクトナンバーセット
	playerCheckPoint->Set3DObjNo(m_Total3DObjNo);

	// 座標セット
	playerCheckPoint->SetPos(pos);

	// サイズセット
	playerCheckPoint->SetScale(scale);

	// 当たり判定処理のマネージャーに追加
	CollisionManager::GetInstance().AddObj(playerCheckPoint);
}

// ギミックに対象のネジを設定
void SceneStage2::SetTargetScrew(ifstream & file, string cell)
{
	//----変数宣言----

	// ギミック
	GimmickBase* gimmick;

	// 対象ネジ番号
	//std::vector<int> targetScrewNo;

	// オブジェクトに関連づける名前
	string objName;

	// ネジの名前
	string screwName;

	// クラス名
	string className;


	//----データ取得、設定----

	// オブジェクト名取得
	getline(file, cell, ',');

	// オブジェクト名設定
	objName = cell;

	// ギミックオブジェクト番号
	getline(file, cell, ',');

	// 名前
	objName += cell;

	// ギミック取得
	gimmick = GetObj<GimmickBase>(objName.c_str());

	// ギミックの種類取得
	getline(file, cell, ',');
	className = cell;

	// 設定が終わるまでループ
	while (true)
	{
		// ネジ番号取得
		getline(file, cell, ',');

		// 書いてあったら処理
		if (cell != "")
		{
			// 名前作成
			screwName = "Screw" + cell;

			// 対象ネジセット
			gimmick->SetScrew(GetObj<Screw>(screwName.c_str()));
		}
		else
		{
			break;
		}
	}

	// Y軸回転の種類のみ
	if (className == "YSpin")
	{
		// 子クラスにキャスト
		SpinFloor* spinfloor = dynamic_cast<SpinFloor*>(GetObj<GimmickBase>(objName.c_str()));

		// 初期角度設定
		spinfloor->SetInitAngle();
	}
}

// ギミックのチェックポイント設定
void SceneStage2::SetCheckPoint(ifstream & file, string cell, vector<float3> checkPoint)
{
	//----変数宣言----

	// ギミック
	CheckPointPath* gimmick;

	// オブジェクトに関連づける名前
	string objName;


	//----データ取得、設定----

	// オブジェクト名取得
	getline(file, cell, ',');
	objName = cell;

	// ギミックオブジェクト番号取得
	getline(file, cell, ',');
	objName += cell;

	// 子クラスにキャスト
	gimmick = dynamic_cast<CheckPointPath*>(GetObj<GimmickBase>(objName.c_str()));

	// 設定が終わるまでループ
	while (true)
	{
		// チェックポイント番号の取得
		getline(file, cell, ',');

		// 書いてあったら処理
		if (cell != "")
		{
			// チェックポイントの座標設定
			gimmick->SetCheckPointPos(checkPoint[stoi(cell) - 1]);
		}
		else
		{
			break;
		}
	}

	// チェックポイントの情報を設定
	gimmick->SetCheckPointInfo();
}

// 一時的に出現する床に必要な情報を設定
void SceneStage2::SetTemporaryInfo(ifstream & file, string cell)
{
	//----変数宣言----

	// ギミック
	TemporaryFloor* gimmick;

	// 前の床
	TemporaryFloor* preGimmick = nullptr;

	// 次の床
	TemporaryFloor* nextGimmick = nullptr;

	// 前の床の情報
	TemporaryFloor::TemporaryFloorData* preGimmickData = nullptr;

	// 次の床の情報
	TemporaryFloor::TemporaryFloorData* nextGimmickData = nullptr;

	// オブジェクトに関連づける名前
	string objName;

	// 入れ替える数字
	string targetName;

	// 自分の番号(リスト関係のあるギミックの中での番号)
	int myNo;

	// 合計数(リスト関係のあるギミックの合計数)
	int totalNo;

	//----データ取得、設定----

	// オブジェクト名取得
	getline(file, cell, ',');
	objName = cell;

	// ギミックオブジェクト番号取得
	getline(file, cell, ',');
	objName += cell;
	targetName = cell;

	// 子クラスにキャスト
	gimmick = dynamic_cast<TemporaryFloor*>(GetObj<GimmickBase>(objName.c_str()));

	// 対象項目まで移動
	// ギミックの種類
	getline(file, cell, ',');

	// Gimmickの後ろの数字を削除
	size_t pos;
	while ((pos = objName.find(targetName)) != std::string::npos)
	{
		objName.erase(pos, targetName.length()); // 数字を削除
	}

	// 一個前のギミック番号
	getline(file, cell, ',');
	if (cell != "")
	{
		// 番号取得
		targetName = cell;

		// 名前作成
		objName += targetName;

		// 一個前のギミック取得
		preGimmick = dynamic_cast<TemporaryFloor*>(GetObj<GimmickBase>(objName.c_str()));

		// 情報取得
		preGimmickData = preGimmick->GetTemporaryData();
	}

	// Gimmickの後ろの数字を削除
	while ((pos = objName.find(targetName)) != std::string::npos)
	{
		objName.erase(pos, targetName.length()); // 数字を削除
	}

	// 次のギミック番号
	getline(file, cell, ',');
	if (cell != "")
	{
		// 番号取得
		targetName = cell;

		// 名前作成
		objName += targetName;

		// 次のギミック取得
		nextGimmick = dynamic_cast<TemporaryFloor*>(GetObj<GimmickBase>(objName.c_str()));

		// 情報取得
		nextGimmickData = nextGimmick->GetTemporaryData();
	}

	// 自分の番号
	getline(file, cell, ',');
	myNo = stoi(cell);

	// 合計数
	getline(file, cell, ',');
	totalNo = stoi(cell);

	// 情報設定
	gimmick->SetTemporaryFloorInfo(preGimmickData, nextGimmickData, myNo, totalNo);
}

// 時間UI作成
void SceneStage2::TimeCreate(ifstream & file, string cell)
{
	//----変数宣言----

	// 時間
	Time* time;

	// 2Dモデルレンダラーコンポーネント
	ModelRenderer2D* _modelRenderer2D;

	// 座標
	DirectX::XMFLOAT3 pos;

	// サイズ
	DirectX::XMFLOAT3 scale;

	// パス
	string path;

	// オブジェクトに関連づける名前
	string objName = cell;


	//----データ取得----

	// オブジェクトNo取得
	getline(file, cell, ',');

	// オブジェクトカウントアップ
	m_Total2DObjNo++;

	// 時間UI番号カウントアップ
	m_TotalTimeUINo++;

	// 名前
	objName += "UI" + std::to_string(m_TotalTimeUINo);

	// X座標取得
	getline(file, cell, ',');

	// float型に変換して設定
	pos.x = stof(cell);

	// Y座標取得
	getline(file, cell, ',');

	// float型に変換して変換
	pos.y = stof(cell);

	// Z値初期化
	pos.z = 0.0f;

	// Xサイズ取得
	getline(file, cell, ',');

	// float型に変換して設定
	scale.x = stof(cell);

	// Yサイズ取得
	getline(file, cell, ',');

	// float型に変換して設定
	scale.y = stof(cell);

	// Z値初期化
	scale.z = 0.0f;


	// テクスチャ名取得
	getline(file, cell, ',');

	// パス作成
	path = "Assets/Texture/InGame/" + cell + ".png";


	//----設定----

	// 時間UI作成
	CreateSceneObj<Time>(objName.c_str());

	// 時間UI取得
	time = GetObj<Time>(objName.c_str());

	// オブジェクトナンバーセット
	time->Set2DObjNo(m_Total2DObjNo);

	// 座標セット
	time->SetPos(pos);

	// サイズセット
	time->SetScale(scale);

	// コンポーネント取得
	_modelRenderer2D = time->GetComponent<ModelRenderer2D>();

	// パス設定	
	_modelRenderer2D->Load(path.c_str());


	// ステージUI→クリアUIの順に時間UIを生成する
	// ステージUIの時間が4桁
	// それより上ならステージUIの作成と判断して処理を変える
	if (m_TotalTimeUINo < 5)
	{
		// マネージャーに情報を渡す
		TimeManager::GetInstance().SetTimeObj(time);
	}
	else
	{
		// ゴール後マネージャーに情報を渡す
		AfterGoalManager::GetInstance().SetTimeObj(time);
		_modelRenderer2D->GetParam()->color.w = 0.5f;
		_modelRenderer2D->SetDraw(false);
	}
}

// 通常UI作成(特に特有の動きがないUI)
void SceneStage2::InGameNormalUICreate(ifstream & file, string cell)
{
	//----変数宣言----

	// 通常UI(ステージUI)
	GameObject* normalUI;

	// 2Dモデルレンダラーコンポーネント
	ModelRenderer2D* _modelRenderer2D;

	// 座標
	DirectX::XMFLOAT3 pos;

	// サイズ
	DirectX::XMFLOAT3 scale;

	// パス
	string path;

	// オブジェクトに関連づける名前
	string objName = cell;


	//----データ取得----

	// オブジェクトNo取得
	getline(file, cell, ',');

	// オブジェクトカウントアップ
	m_Total2DObjNo++;

	// 名前
	objName += "UI" + cell;

	// X座標取得
	getline(file, cell, ',');

	// float型に変換して設定
	pos.x = stof(cell);

	// Y座標取得
	getline(file, cell, ',');

	// float型に変換して設定
	pos.y = stof(cell);

	// Z値初期化
	pos.z = 0.0f;

	// Xサイズ取得
	getline(file, cell, ',');

	// float型に変換して設定
	scale.x = stof(cell);

	// Yサイズ取得
	getline(file, cell, ',');

	// float型に変換して設定
	scale.y = stof(cell);

	// Z値初期化
	scale.z = 0.0f;


	// テクスチャ名取得
	getline(file, cell, ',');

	// パス作成
	path = "Assets/Texture/InGame/" + cell + ".png";


	//----設定----

	// 通常UI作成
	CreateSceneObj<GameObject>(objName.c_str());

	// 通常UI取得
	normalUI = GetObj<GameObject>(objName.c_str());

	// オブジェクトナンバーセット
	normalUI->Set2DObjNo(m_Total2DObjNo);

	// 座標セット
	normalUI->SetPos(pos);

	// サイズセット
	normalUI->SetScale(scale);

	// 2Dモデルレンダラーコンポーネントセット
	normalUI->AddComponent<ModelRenderer2D>();

	// 2Dモデルレンダラーコンポーネント取得
	_modelRenderer2D = normalUI->GetComponent<ModelRenderer2D>();

	// パス設定
	_modelRenderer2D->Load(path.c_str());
}

// ポーズUI作成
void SceneStage2::PauseMoziUICreate(ifstream & file, string cell)
{
	//----変数宣言----

	// ポーズ画面文字
	PauseMozi* pauseMozi;

	// 2Dモデルレンダラーコンポーネント
	ModelRenderer2D* _modelRenderer2D;

	// 座標
	DirectX::XMFLOAT3 pos;

	// サイズ
	DirectX::XMFLOAT3 scale;

	// パス
	string path;

	// オブジェクトに関連づける名前
	string objName = cell;


	//----データ取得----

	// オブジェクトNo取得
	getline(file, cell, ',');

	// オブジェクトカウントアップ
	m_Total2DObjNo++;

	// 名前
	objName += "UI" + cell;

	// X座標取得
	getline(file, cell, ',');

	// float型に変換して設定
	pos.x = stof(cell);

	// Y座標取得
	getline(file, cell, ',');

	// float型に変換して設定
	pos.y = stof(cell);

	// Z値初期化
	pos.z = 0.0f;

	// Xサイズ取得
	getline(file, cell, ',');

	// float型に変換して設定
	scale.x = stof(cell);

	// Yサイズ取得
	getline(file, cell, ',');

	// float型に変換して設定
	scale.y = stof(cell);

	// Z値初期化
	scale.z = 0.0f;


	// テクスチャ名取得
	getline(file, cell, ',');

	// パス作成
	path = "Assets/Texture/InGame/" + cell + ".png";


	//----設定----

	// ポーズ画面文字UI作成
	CreateSceneObj<PauseMozi>(objName.c_str());

	// ポーズ画面文字UI取得
	pauseMozi = GetObj<PauseMozi>(objName.c_str());

	// オブジェクトナンバーセット
	pauseMozi->Set2DObjNo(m_Total2DObjNo);

	// 座標セット
	pauseMozi->SetPos(pos);

	// サイズセット
	pauseMozi->SetScale(scale);

	// 2Dコンポーネント取得
	_modelRenderer2D = pauseMozi->GetComponent<ModelRenderer2D>();

	// パス設定	
	_modelRenderer2D->Load(path.c_str());

}

// 通常UI作成(チュートリアル画面
void SceneStage2::MenuNormalUICreate(ifstream & file, string cell)
{
	//----変数宣言----

	// 通常UI(チュートリアル画面)
	GameObject* normalUI;

	// 2Dモデルレンダラーコンポーネント
	ModelRenderer2D* _modelRenderer2D;

	// 座標
	DirectX::XMFLOAT3 pos;

	// サイズ
	DirectX::XMFLOAT3 scale;

	// パス
	string path;

	// オブジェクトに関連づける名前
	string objName = cell;

	// ページ番号
	int page = 0;

	// オブジェクトNo取得
	getline(file, cell, ',');

	// オブジェクトカウントアップ
	m_Total2DObjNo++;

	// 一個分空けるポーズ画面背景用に
	if (objName == "BackGround")
	{
		m_Total2DObjNo++;
	}

	// 名前
	objName += "UI" + cell;

	// X座標取得
	getline(file, cell, ',');

	// float型に変換して設定
	pos.x = stof(cell);

	// Y座標取得
	getline(file, cell, ',');

	// float型に変換して設定
	pos.y = stof(cell);

	// Z値初期化
	pos.z = 0.0f;

	// Xサイズ取得
	getline(file, cell, ',');

	// float型に変換して設定
	scale.x = stof(cell);

	// Yサイズ取得
	getline(file, cell, ',');

	// float型に変換して設定
	scale.y = stof(cell);

	// Z値初期化
	scale.z = 0.0f;


	// テクスチャ名取得
	getline(file, cell, ',');

	// パス作成
	path = "Assets/Texture/Menu/" + cell + ".png";

	// ページ数読み込み
	getline(file, cell, ',');	// ページ数
	if (cell != "")
	{
		page = stoi(cell);		// ページ数設定
	}

	// 既にチュートリアル画面で作成されているものか確認＋ポーズ画面背景はこっちで処理する
	normalUI = GetObj<GameObject>(objName.c_str());	// 実体取得
	
	// 作られているものなら
	if (normalUI)
	{
		// オブジェクト番号取得
		int no = normalUI->Get2DObjNo();

		// カウントを戻す
		m_Total2DObjNo--;

		// UI、オブジェクト番号、座標、サイズ設定
		if (page)
		{
			PauseManager::GetInstance().SetPauseUI(page, normalUI);
		}
		else
		{
			PauseManager::GetInstance().SetNormalUI(normalUI);
		}
		PauseManager::GetInstance().SetPosScale(no, pos, scale);
		return;
	}


	//----設定----

	// 通常UI作成
	CreateSceneObj<GameObject>(objName.c_str());

	// 通常UI取得
	normalUI = GetObj<GameObject>(objName.c_str());

	// オブジェクトナンバーセット
	normalUI->Set2DObjNo(m_Total2DObjNo);

	// 座標セット
	normalUI->SetPos(pos);

	// サイズセット
	normalUI->SetScale(scale);

	// 2Dモデルレンダラーコンポーネントセット
	normalUI->AddComponent<ModelRenderer2D>();

	// 2Dモデルレンダラーコンポーネント取得
	_modelRenderer2D = normalUI->GetComponent<ModelRenderer2D>();

	// パス設定
	_modelRenderer2D->Load(path.c_str());

	// ポーズ画面背景用処理
	if (objName == "PauseBackGroundUI1")
	{
		GameObject* obj = GetObj<GameObject>("BackGroundUI1");
		// チュートリアル背景の一個前に来るように調整
		int objNo = obj->Get2DObjNo() - 1;
		m_Total2DObjNo--;

		// オブジェクト番号設定し直し
		normalUI->Set2DObjNo(objNo);
		// UI、オブジェクト番号、座標、サイズ設定
		PauseManager::GetInstance().SetNormalUI(normalUI);
		PauseManager::GetInstance().SetPosScale(objNo, pos, scale);
		return;
	}

	// チュートリアルマネージャー設定
	if (page)
	{
		TutorialManager::GetInstance().SetTutorialUI(page, normalUI);
	}
	else
	{
		TutorialManager::GetInstance().SetNormalUI(normalUI);
	}
}

// 左矢印UI作成
void SceneStage2::LeftUICreate(ifstream & file, string cell)
{
	//----変数宣言----

	// 左矢印
	Left* leftUI;

	// 確認用
	GameObject* checkLeftUI;

	// 2Dモデルレンダラーコンポーネント
	ModelRenderer2D* _modelRenderer2D;

	// 座標
	DirectX::XMFLOAT3 pos;

	// サイズ
	DirectX::XMFLOAT3 scale;

	// パス
	string path;

	// オブジェクトに関連づける名前
	string objName = cell;

	// ページ番号
	int page = 0;


	//----データ取得----

	// オブジェクトNo取得
	getline(file, cell, ',');

	// オブジェクトカウントアップ
	m_Total2DObjNo++;

	// 名前
	objName += "UI" + cell;

	// X座標取得
	getline(file, cell, ',');

	// float型に変換して設定
	pos.x = stof(cell);

	// Y座標取得
	getline(file, cell, ',');

	// float型に変換して設定
	pos.y = stof(cell);

	// Z値初期化
	pos.z = 0.0f;

	// Xサイズ取得
	getline(file, cell, ',');

	// float型に変換して設定
	scale.x = stof(cell);

	// Yサイズ取得
	getline(file, cell, ',');

	// float型に変換して設定
	scale.y = stof(cell);

	// Z値初期化
	scale.z = 0.0f;


	// テクスチャ名取得
	getline(file, cell, ',');

	// パス作成
	path = "Assets/Texture/Menu/" + cell + ".png";

	// ページ数取得
	getline(file, cell, ',');
	page = stoi(cell);


	// 既に作成されているものか確認
	checkLeftUI = GetObj<GameObject>(objName.c_str());
	if (checkLeftUI)
	{
		// オブジェクト番号取得
		int no = checkLeftUI->Get2DObjNo();

		// カウントを戻す
		m_Total2DObjNo--;

		// UI、オブジェクト番号、座標、サイズ設定
		PauseManager::GetInstance().SetPauseUI(page, checkLeftUI);
		PauseManager::GetInstance().SetPosScale(no, pos, scale);
		return;
	}


	//----設定----

	// 左矢印UI作成
	CreateSceneObj<Left>(objName.c_str());

	// 左矢印取得
	leftUI = GetObj<Left>(objName.c_str());

	// オブジェクトナンバーセット
	leftUI->Set2DObjNo(m_Total2DObjNo);

	// 座標セット
	leftUI->SetPos(pos);

	// サイズセット
	leftUI->SetScale(scale);

	// 2Dモデルレンダラーコンポーネント取得
	_modelRenderer2D = leftUI->GetComponent<ModelRenderer2D>();

	// パス設定
	_modelRenderer2D->Load(path.c_str());

	// チュートリアルに設定
	TutorialManager::GetInstance().SetTutorialUI(page, leftUI);
}

// 右矢印UI作成
void SceneStage2::RightUICreate(ifstream & file, string cell)
{
	//----変数宣言----

	// 右矢印
	Right* rightUI;
	GameObject* checkRightUI;

	// 2Dモデルレンダラーコンポーネント
	ModelRenderer2D* _modelRenderer2D;

	// 座標
	DirectX::XMFLOAT3 pos;

	// サイズ
	DirectX::XMFLOAT3 scale;

	// パス
	string path;

	// オブジェクトに関連づける名前
	string objName = cell;

	// ページ番号
	int page = 0;

	// オブジェクトNo取得
	getline(file, cell, ',');

	// オブジェクトカウントアップ
	m_Total2DObjNo++;

	// 名前
	objName += "UI" + cell;

	// X座標取得
	getline(file, cell, ',');

	// float型に変換して設定
	pos.x = stof(cell);

	// Y座標取得
	getline(file, cell, ',');

	// float型に変換して設定
	pos.y = stof(cell);

	// Z値初期化
	pos.z = 0.0f;

	// Xサイズ取得
	getline(file, cell, ',');

	// float型に変換して設定
	scale.x = stof(cell);

	// Yサイズ取得
	getline(file, cell, ',');

	// float型に変換して設定
	scale.y = stof(cell);

	// Z値初期化
	scale.z = 0.0f;


	// テクスチャ名取得
	getline(file, cell, ',');

	// パス作成
	path = "Assets/Texture/Menu/" + cell + ".png";

	// ページ数取得
	getline(file, cell, ',');
	page = stoi(cell);


	// 既に作成されているものか確認
	checkRightUI = GetObj<GameObject>(objName.c_str());	// 実体取得
	if (checkRightUI)
	{
		// オブジェクト番号取得
		int no = checkRightUI->Get2DObjNo();

		// カウントを戻す
		m_Total2DObjNo--;

		// UI、オブジェクト番号、座標、サイズ設定
		PauseManager::GetInstance().SetPauseUI(page, checkRightUI);
		PauseManager::GetInstance().SetPosScale(no, pos, scale);
		return;
	}

	//----設定----

	// 右矢印UI作成
	CreateSceneObj<Right>(objName.c_str());

	// 右矢印取得
	rightUI = GetObj<Right>(objName.c_str());

	// オブジェクトナンバーセット
	rightUI->Set2DObjNo(m_Total2DObjNo);

	// 座標セット
	rightUI->SetPos(pos);

	// サイズセット
	rightUI->SetScale(scale);

	// 2Dモデルレンダラーコンポーネント取得
	_modelRenderer2D = rightUI->GetComponent<ModelRenderer2D>();

	// パス設定
	_modelRenderer2D->Load(path.c_str());

	// チュートリアル設定
	TutorialManager::GetInstance().SetTutorialUI(page, rightUI);
}

// ゲームスタートUI作成
void SceneStage2::StartUICreate(ifstream & file, string cell)
{
	//----変数宣言----

	// ゲームスタートUI
	Start* startUI;

	// 2Dモデルレンダラーコンポーネント
	ModelRenderer2D* _modelRenderer2D;

	// 座標
	DirectX::XMFLOAT3 pos;

	// サイズ
	DirectX::XMFLOAT3 scale;

	// パス
	string path;

	// オブジェクトに関連づける名前
	string objName = cell;

	// ページ番号
	int page = 0;

	// オブジェクトNo取得
	getline(file, cell, ',');

	// オブジェクトカウントアップ
	m_Total2DObjNo++;

	// 名前
	objName += "UI" + cell;

	// X座標取得
	getline(file, cell, ',');

	// float型に変換して設定
	pos.x = stof(cell);

	// Y座標取得
	getline(file, cell, ',');

	// float型に変換して設定
	pos.y = stof(cell);

	// Z値初期化
	pos.z = 0.0f;

	// Xサイズ取得
	getline(file, cell, ',');

	// float型に変換設定
	scale.x = stof(cell);

	// Yサイズ取得
	getline(file, cell, ',');

	// float型に変換して設定
	scale.y = stof(cell);

	// Z値初期化
	scale.z = 0.0f;


	// テクスチャ名取得
	getline(file, cell, ',');

	// パス作成
	path = "Assets/Texture/Menu/" + cell + ".png";

	// ページ数読み込み
	getline(file, cell, ',');
	page = stoi(cell);


	//----設定----

	// ゲームスタートUI作成
	CreateSceneObj<Start>(objName.c_str());

	// ゲームスタートUI取得
	startUI = GetObj<Start>(objName.c_str());

	// オブジェクトナンバーセット
	startUI->Set2DObjNo(m_Total2DObjNo);

	// 座標セット
	startUI->SetPos(pos);

	// サイズセット
	startUI->SetScale(scale);

	// 2Dモデルレンダラーコンポーネント取得
	_modelRenderer2D = startUI->GetComponent<ModelRenderer2D>();

	// パス設定
	_modelRenderer2D->Load(path.c_str());

	// チュートリアル設定
	TutorialManager::GetInstance().SetTutorialUI(page, startUI);
}

// ゲームオーバー後に表示するUIを作成
void SceneStage2::GameOverUICreate()
{
	// スカイドーム取得
	SkyDome* skydome = GetObj<SkyDome>("SkyDome");

	// ゲームオーバーUI作成
	CreateSceneObj<GameOver>("GameOver1");

	// ゲームオーバーUI修正
	GameOver* obj = GetObj<GameOver>("GameOver1");

	// オブジェクトNo増加
	m_Total2DObjNo++;

	// オブジェクト番号セット
	obj->Set2DObjNo(m_Total2DObjNo);

	// オブジェクトセット
	AfterGameOverManager::GetInstance().SetObj(obj, skydome);

}

// ゴール後に表示するUIを作成
void SceneStage2::GoalUICreate()
{
	// プレイヤー取得
	Player* player = GetObj<Player>("Player1");

	// ゴール取得
	Goal* goal = GetObj<Goal>("Goal1");

	// カメラ取得
	GameObject* camera = GetObj<GameObject>("Camera");

	// スカイドーム取得
	SkyDome* skyDome = GetObj<SkyDome>("SkyDome");

	// クリアUI作成
	CreateSceneObj<Clear>("Clear1");

	// クリアUI取得
	Clear*	obj = GetObj<Clear>("Clear1");

	// 番号増加
	m_Total2DObjNo++;

	// オブジェクト番号セット
	obj->Set2DObjNo(m_Total2DObjNo);

	// オブジェクトセット
	AfterGoalManager::GetInstance().SetObj(obj, player, goal);
	AfterGoalManager::GetInstance().AddObj(camera);
	AfterGoalManager::GetInstance().AddObj(skyDome);

	// クリアタイムUI作成
	ClearTimeUICreate();
	AfterGoalManager::GetInstance().DrawON();
	std::vector<Time*> time = AfterGoalManager::GetInstance().GetTimeObj();
	// クリアタイム計算
	TimeManager::GetInstance().CreateClearTime(time);
}

// クリアタイムを表示するUIを作成
void SceneStage2::ClearTimeUICreate()
{
	//----クリアUI生成----

	// ファイル読み込み
	ifstream file("Assets/UI/Clear/Clear.csv");

	// セルごとの読み込み先
	string cell;

	// 行数格納用
	int MaxLine;

	// ファイル読み込みができたか
	if (!file)
	{
		MessageBox(NULL, "Clear.csvファイルが読み込めませんでした", "SceneStage2.cpp", MB_OK);
		return;
	}

	// 行数情報取得
	getline(file, cell, ',');

	// 行数格納
	MaxLine = stoi(cell);

	// 3行目まで移動
	getline(file, cell);
	getline(file, cell);

	// ファイルからデータを読み込む
	for (int i = 0; i < MaxLine; i++)
	{
		// UIの種類で分ける
		getline(file, cell, ',');

		// UIごとに処理をわける
		if (cell == "Time")
		{
			// 時間UI作成
			TimeCreate(file, cell);
		}

		// 次の行へ
		getline(file, cell);
	}

	// ファイルを閉じる
	file.close();
}