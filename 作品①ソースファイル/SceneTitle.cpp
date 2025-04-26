//----インクルード部----
#include "SceneTitle.h"
#include "Model.h"
#include "Camera.h"
#include "Light.h"
#include "Input.h"
#include "Sprite.h"
#include "Defines.h"
#include "CameraDCC.h"

//----背景----
#include "SkyDome.h"			// スカイドーム

//----シーン----
#include "SceneRoot.h"
#include "SceneGame.h"	// ゲームシーン

#include "ModelRenderer3D.h"

//----マネージャー----
#include "TutorialManager.h"	// チュートリアルマネージャー
#include "SoundManager.h"		// サウンドマネージャー

//----UI----
#include "Title.h"			// タイトル名
#include "TitleScrew.h"		// ネジUI
#include "StartMessage.h"	// ゲームスタート文字
#include "Bird.h"			// 鳥

// コンポーネント
#include "Move2DAnimation.h"	// 移動アニメーションコンポーネント
#include "SpinAnimation.h"		// 回転アニメーションコンポーネント
#include "OpacityController.h"	// 点滅処理コンポーネント

// 初期化
void SceneTitle::Init()
{
	// メンバ変数初期化
	m_Total2DObjNo = 0;
	m_Total3DObjNo = 0;
	m_Change = false;

	// 背景
	CreateSceneObj<SkyDome>("SkyDome");	// スカイドーム

	// UI生成
	Load();	// ファイル読み込み

	// カメラ情報取得
	CameraDCC* pCamObj = GetObj<CameraDCC>("Camera");

	// スカイドームをカメラ座標に合わせる
	SkyDome* skydome = GetObj<SkyDome>("SkyDome");
	skydome->SetCamera(pCamObj);

}

// デストラクタ
void SceneTitle::Uninit()
{
	// チュートリアルを行うフラグを立てる
	TutorialManager::GetInstance().Reset();
}
void SceneTitle::Update(float tick)
{
	// 次のシーンを取得
	SceneBase::Scene nextScene = SceneRoot::GetNextScene();

	// 次のシーンがセットされてなく
	// キーを押されたら
	if (nextScene == SceneBase::Scene::None &&
		(IsKeyTrigger(VK_RETURN) || IsKeyTrigger(VK_SPACE)))
	{
		SceneRoot::SetNextScene(SceneBase::Scene::GAME);

		// 次のシーンを取得
		nextScene = SceneRoot::GetNextScene();

		// セット出来てなかったらSE再生しない
		if (nextScene != SceneBase::Scene::GAME)
		{
			return;
		}

		// スタートSE再生
		SoundManager::GetInstance().playSound(SoundManager::SystemSE::Tstrat);
	}

}
void SceneTitle::Draw()
{
	// 各種データの準備
	GameObject* pObjs[] = {
		GetObj<GameObject>("Camera"),
	};
	Camera* pCamera = pObjs[0]->GetComponent<Camera>();

	// 描画前準備
	RenderTarget* pRTV = GetObj<RenderTarget>("RTV");
	DepthStencil* pDSV = GetObj<DepthStencil>("DSV");

	// スカイドーム描画
	SetRenderTargets(1, &pRTV, nullptr);

	GameObject* skyDome = GetObj<GameObject>("SkyDome");
	ModelRenderer3D* _modelRenderer3D = skyDome->GetComponent<ModelRenderer3D>();
	// セット
	_modelRenderer3D->SetCamera(pCamera);
	// 描画
	_modelRenderer3D->Draw();

	// レンダーターゲットの変更
	// ※描き込み先の変更
	SetRenderTargets(1, &pRTV, pDSV);	// 数、描き込み先の情報、深度バッファ

	// 3D描画
	// シーンが所持しているオブジェクトの描画
	for (int j = 1; j <= m_Total3DObjNo; j++)
	{
		ModelRenderer3D*  _modelRenderer3D = Get3DObj(j)->GetComponent<ModelRenderer3D>();

		if (_modelRenderer3D)
		{
			// セット
			_modelRenderer3D->SetCamera(pCamera);

			// 描画
			_modelRenderer3D->Draw();
		}
	}

	// 元のディスプレイ表示に戻す
	// レンダーターゲットに描きこまれた内容は
	// 2D画像となるので、2D画像を改めて
	// ディスプレイに表示するとき、深度バッファは
	// 不要となる(呼び出し順で画面に描画)
	SetRenderTargets(1, &pRTV, nullptr);

	// 2D描画
	// シーンが所持しているオブジェクトの描画
	for (int j = 1; j <= m_Total2DObjNo; j++)
	{

		ModelRenderer2D*  _modelRenderer2D = Get2DObj(j)->GetComponent<ModelRenderer2D>();

		if (_modelRenderer2D)
		{
			// セット
			_modelRenderer2D->SetCamera(pObjs[0], pCamera);

			// 描画
			_modelRenderer2D->Draw();
		}
	}
}

// ファイル読み込み
void SceneTitle::Load()
{
	ifstream file("Assets/UI/Title/TitleUI.csv");	// ファイルオープン
	string cell;	// セルごとの読み込み先
	int MaxLine;	// 行数格納用

	if (!file)
	{
		MessageBox(NULL, "TitleUI.csvファイルが読み込めませんでした", "SceneGame.cpp", MB_OK);
		return;
	}

	getline(file, cell, ',');	// 行数抽出
	MaxLine = stoi(cell);		// 行数格納

	// 3行目まで移動
	getline(file, cell);
	getline(file, cell);

	// ファイルからデータを読み込む
	for (int i = 0; i < MaxLine; i++)
	{
		getline(file, cell, ',');	// セル抽出(1列目)

		// UIごとに処理をわける
		if (cell == "TitleName")
		{
			TitleNameCreate(file, cell);	// タイトル名UI作成
		}
		else if (cell == "TitleLeftScrew" ||
			cell == "TitleRightScrew")
		{
			// ネジUI作成
			TitleScrewCreate(file, cell);
		}
		else if (cell == "GameStart")
		{
			GameStartCreate(file, cell);	// ゲームスタートUI作成
		}
		else if (cell == "Bird")
		{
			BirdCreate(file, cell);			// 鳥UI作成
		}
		else
		{
			NormalUICreate(file, cell);		// 通常UI作成
		}

		getline(file, cell);		// 次の行へ
	}
	file.close();	// ファイルを閉じる
}

// タイトル名UI作成
void SceneTitle::TitleNameCreate(ifstream & file, string cell)
{
	// 変数宣言
	Title* titleUI;
	ModelRenderer2D* _modelRenderer2D;	// モデルレンダラーコンポーネント
	Move2DAnimation* _move2DAnimation;	// 2Dアニメーションコンポーネント
	SpinAnimation* _spinAnimation;		// 回転アニメーションコンポーネント
	DirectX::XMFLOAT3 pos;				// 座標
	DirectX::XMFLOAT3 scale;			// サイズ
	string path;						// パス
	string objName = cell;				// オブジェクトに関連づける名前
	DirectX::XMFLOAT2 normalSpeed;		// 移動速度
	DirectX::XMFLOAT2 animationSpeed;	// アニメーションスピード
	Move2DAnimation::MoveKind kind;		// アニメーション方向
	DirectX::XMFLOAT2 min;				// 最小座標
	DirectX::XMFLOAT2 max;				// 最大座標
	int spinNum;						// 回転数
	int deltaSpin;						// 回転量
	DirectX::XMFLOAT4 axis;				// 回転軸
	size_t commaPos;					// ,の位置
	
	// オブジェクトナンバー
	getline(file, cell, ',');		// オブジェクトNo取得
	m_Total2DObjNo++;				// オブジェクトカウントアップ

	objName += "UI" + cell;			// 名前

	// 座標
	getline(file, cell, ',');		// X座標
	pos.x = stof(cell);				// float型に変
	getline(file, cell, ',');		// Y座標
	pos.y = stof(cell);				// float型に変換
	pos.z = 0.0f;					// Z値初期化

	// サイズ
	getline(file, cell, ',');		// Xサイズ
	scale.x = stof(cell);			// float型に変換
	getline(file, cell, ',');		// Yサイズ
	scale.y = stof(cell);			// float型に変換
	scale.z = 0.0f;					// Z値初期化


	// テクスチャ名読み込み
	getline(file, cell, ',');		// テクスチャ名
	path = "Assets/Texture/Title/" + cell + ".png";		// パス作成

	// 移動速度
	getline(file, cell, ',');		// 移動速度取得
	commaPos = cell.find(' ');
	// ,より前部分を取り出してfloat型に変換して設定
	normalSpeed.x = stof(cell.substr(0, commaPos));
	normalSpeed.y = stof(cell.substr(commaPos + 1));

	// 対象項目までずらす
	getline(file, cell, ',');		// 加速度

	// アニメーションスピード
	getline(file, cell, ',');		// アニメーションスピード取得
	commaPos = cell.find(' ');
	// ,より前部分を取り出してfloat型に変換してアニメーションスピード設定
	animationSpeed.x = stof(cell.substr(0, commaPos));
	animationSpeed.y = stof(cell.substr(commaPos + 1));

	// アニメーション方向
	getline(file, cell, ',');
	if (cell == "X")
	{
		kind = Move2DAnimation::MoveKind::Left_Right;
	}
	else
	{
		kind = Move2DAnimation::MoveKind::Up_Down;
	}

	// 最小座標
	getline(file, cell, ',');
	commaPos = cell.find(' ');
	// ,より前部分を取り出してfloat型に変換して最小座標設定
	min.x = stof(cell.substr(0, commaPos));
	min.y = stof(cell.substr(commaPos + 1));

	// 最大座標
	getline(file, cell, ',');
	commaPos = cell.find(' ');
	// ,より前部分を取り出してfloat型に変換して最小座標設定
	max.x = stof(cell.substr(0, commaPos));
	max.y = stof(cell.substr(commaPos + 1));

	// 回転数
	getline(file, cell, ',');		// 回転数取得
	spinNum = stoi(cell);			// int型に変換して回転数設定

	// 回転量
	getline(file, cell, ',');		// 回転量取得
	deltaSpin = stoi(cell);			// int型に変換して回転量設定

	// 回転軸
	getline(file, cell, ',');
	if (cell == "X")
	{
		axis = DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 0.0f);
	}
	else if(cell == "Y")
	{
		axis = DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f);
	}
	else
	{
		axis = DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 0.0f);
	}

	CreateSceneObj<Title>(objName.c_str());		// 通常UI作成
	titleUI = GetObj<Title>(objName.c_str());	// 実体取得
	titleUI->Set2DObjNo(m_Total2DObjNo);		// オブジェクトナンバーセット
	titleUI->SetPos(pos);						// 座標セット
	titleUI->SetScale(scale);					// サイズセット
	// コンポーネント取得
	_modelRenderer2D = titleUI->GetComponent<ModelRenderer2D>();
	_move2DAnimation = titleUI->GetComponent<Move2DAnimation>();
	_spinAnimation = titleUI->GetComponent<SpinAnimation>();
	_modelRenderer2D->Load(path.c_str());		// パス設定

	_move2DAnimation->SetSpeed(normalSpeed);	// 移動速度設定
	titleUI->SetAnimationSpeed(animationSpeed);	// アニメーション速度設定
	_move2DAnimation->SetMoveKind(kind);		// 移動方向設定
	_move2DAnimation->SetMoveArea(min, max);	// 移動範囲設定
	_spinAnimation->SetSpinNum(spinNum);		// 回転数設定
	_spinAnimation->SetDeltaRot(deltaSpin);		// 回転量設定
	_spinAnimation->SetAxis(axis);				// 回転軸設定
}

// ネジUI作成
void SceneTitle::TitleScrewCreate(ifstream & file, string cell)
{
	//----変数宣言----
	TitleScrew* titleScrewUI;

	// モデルレンダラーコンポーネント
	ModelRenderer2D* _modelRenderer2D;

	// 2Dアニメーションコンポーネント
	Move2DAnimation* _move2DAnimation;

	// 回転アニメーションコンポーネント
	SpinAnimation* _spinAnimation;

	// 座標
	DirectX::XMFLOAT3 pos;

	// サイズ
	DirectX::XMFLOAT3 scale;

	// パス
	string path;

	// オブジェクトに関連づける名前
	string objName = cell;

	// 移動速度
	DirectX::XMFLOAT2 normalSpeed;

	// アニメーションスピード
	DirectX::XMFLOAT2 animationSpeed;

	// アニメーション方向
	Move2DAnimation::MoveKind kind;

	// 最小座標
	DirectX::XMFLOAT2 min;

	// 最大座標
	DirectX::XMFLOAT2 max;

	// 回転数
	int spinNum;

	// 回転量
	int deltaSpin;

	// 回転軸
	DirectX::XMFLOAT4 axis;

	// ,の位置
	size_t commaPos;

	// ターゲット座標
	DirectX::XMFLOAT3 targetPos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);


	//----データ取得----

	// オブジェクトナンバー
	getline(file, cell, ',');		// オブジェクトNo取得

	// オブジェクトカウントアップ
	m_Total2DObjNo++;

	// 名前作成
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


	// テクスチャ名読み込み

	// テクスチャ名
	getline(file, cell, ',');

	// パス作成
	path = "Assets/Texture/Title/" + cell + ".png";

	// 移動速度

	// 移動速度取得
	getline(file, cell, ',');
	commaPos = cell.find(' ');
	// ,より前部分を取り出してfloat型に変換して設定
	normalSpeed.x = stof(cell.substr(0, commaPos));
	normalSpeed.y = stof(cell.substr(commaPos + 1));

	// 対象項目までずらす
	getline(file, cell, ',');		// 加速度

	// アニメーションスピード
	getline(file, cell, ',');		// アニメーションスピード取得
	commaPos = cell.find(' ');
	// ,より前部分を取り出してfloat型に変換してアニメーションスピード設定
	animationSpeed.x = stof(cell.substr(0, commaPos));
	animationSpeed.y = stof(cell.substr(commaPos + 1));

	// アニメーション方向
	getline(file, cell, ',');
	if (cell == "X")
	{
		kind = Move2DAnimation::MoveKind::Left_Right;
	}
	else
	{
		kind = Move2DAnimation::MoveKind::Up_Down;
	}

	// 最小座標
	getline(file, cell, ',');
	commaPos = cell.find(' ');
	// ,より前部分を取り出してfloat型に変換して最小座標設定
	min.x = stof(cell.substr(0, commaPos));
	min.y = stof(cell.substr(commaPos + 1));

	// 最大座標
	getline(file, cell, ',');
	commaPos = cell.find(' ');
	// ,より前部分を取り出してfloat型に変換して最小座標設定
	max.x = stof(cell.substr(0, commaPos));
	max.y = stof(cell.substr(commaPos + 1));

	// 回転数
	getline(file, cell, ',');		// 回転数取得
	spinNum = stoi(cell);			// int型に変換して回転数設定

	// 回転量
	getline(file, cell, ',');		// 回転量取得
	deltaSpin = stoi(cell);			// int型に変換して回転量設定

	// 回転軸
	getline(file, cell, ',');
	if (cell == "X")
	{
		axis = DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 0.0f);
	}
	else if (cell == "Y")
	{
		axis = DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f);
	}
	else
	{
		axis = DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 0.0f);
	}

	// ターゲット座標Y取得
	getline(file, cell, ',');
	targetPos.x = pos.x;
	targetPos.y = stof(cell);

	//----設定----

	// ネジUI作成
	CreateSceneObj<TitleScrew>(objName.c_str());

	// 実体取得
	titleScrewUI = GetObj<TitleScrew>(objName.c_str());

	// オブジェクトナンバーセット
	titleScrewUI->Set2DObjNo(m_Total2DObjNo);

	// 座標セット
	titleScrewUI->SetPos(pos);

	// サイズセット
	titleScrewUI->SetScale(scale);

	// コンポーネント取得

	// 2Dモデルレンダラーコンポーネント
	_modelRenderer2D = titleScrewUI->GetComponent<ModelRenderer2D>();

	// 移動アニメーションコンポーネント
	_move2DAnimation = titleScrewUI->GetComponent<Move2DAnimation>();

	// 回転アニメーションコンポーネント
	_spinAnimation = titleScrewUI->GetComponent<SpinAnimation>();

	// パス設定
	_modelRenderer2D->Load(path.c_str());

	// 移動速度設定
	_move2DAnimation->SetSpeed(normalSpeed);

	// アニメーション速度設定
	titleScrewUI->SetAnimationSpeed(animationSpeed);

	// 移動方向設定
	_move2DAnimation->SetMoveKind(kind);

	// 移動範囲設定
	_move2DAnimation->SetMoveArea(min, max);

	// 回転数設定
	_spinAnimation->SetSpinNum(spinNum);

	// 回転量設定
	_spinAnimation->SetDeltaRot(deltaSpin);

	// 回転軸設定
	_spinAnimation->SetAxis(axis);

	// ターゲット座標設定
	titleScrewUI->SetTargetPos(targetPos);
}

// ゲームスタートUI作成
void SceneTitle::GameStartCreate(ifstream & file, string cell)
{
	// 変数宣言
	StartMessage* startMessageUI;
	ModelRenderer2D* _modelRenderer2D;	// モデルレンダラーコンポーネント
	Opacity* _opacity;					// オパシティコンポーネント
	DirectX::XMFLOAT3 pos;				// 座標
	DirectX::XMFLOAT3 scale;			// サイズ
	string path;						// パス
	string objName = cell;				// オブジェクトに関連づける名前
	float animationSpeed;				// アニメーションスピード

	// オブジェクトナンバー
	getline(file, cell, ',');		// オブジェクトNo取得
	m_Total2DObjNo++;				// オブジェクトカウントアップ

	objName += "UI" + cell;			// 名前

	// 座標
	getline(file, cell, ',');		// X座標
	pos.x = stof(cell);				// float型に変
	getline(file, cell, ',');		// Y座標
	pos.y = stof(cell);				// float型に変換
	pos.z = 0.0f;					// Z値初期化

	// サイズ
	getline(file, cell, ',');		// Xサイズ
	scale.x = stof(cell);			// float型に変換
	getline(file, cell, ',');		// Yサイズ
	scale.y = stof(cell);			// float型に変換
	scale.z = 0.0f;					// Z値初期化


	// テクスチャ名読み込み
	getline(file, cell, ',');		// テクスチャ名
	path = "Assets/Texture/Title/" + cell + ".png";		// パス作成

	// 対象項目までずらす
	getline(file, cell, ',');		// 移動速度取得
	getline(file, cell, ',');		// 加速度

	// アニメーションスピード
	getline(file, cell, ',');		// アニメーションスピード取得
	animationSpeed = stof(cell);	// アニメーションスピード設定


	CreateSceneObj<StartMessage>(objName.c_str());			// 通常UI作成
	startMessageUI = GetObj<StartMessage>(objName.c_str());	// 実体取得
	startMessageUI->Set2DObjNo(m_Total2DObjNo);				// オブジェクトナンバーセット
	startMessageUI->SetPos(pos);							// 座標セット
	startMessageUI->SetScale(scale);						// サイズセット
	// コンポーネント取得
	_modelRenderer2D = startMessageUI->GetComponent<ModelRenderer2D>();
	_opacity = startMessageUI->GetComponent<Opacity>();
	_modelRenderer2D->Load(path.c_str());					// パス設定

	_opacity->SetChangeValue(animationSpeed);				// アニメーションスピード設定
}

// 鳥UI作成
void SceneTitle::BirdCreate(ifstream & file, string cell)
{
	// 変数宣言
	Bird* birdUI;
	ModelRenderer2D* _modelRenderer2D;	// モデルレンダラーコンポーネント
	DirectX::XMFLOAT3 pos;				// 座標
	DirectX::XMFLOAT3 scale;			// サイズ
	string path;						// パス
	string objName = cell;				// オブジェクトに関連づける名前
	float speed;						// 通常スピード
	float acceleration;					// 加速度

	// オブジェクトナンバー
	getline(file, cell, ',');		// オブジェクトNo取得
	m_Total2DObjNo++;				// オブジェクトカウントアップ

	objName += "UI" + cell;			// 名前

	// 座標
	getline(file, cell, ',');		// X座標
	pos.x = stof(cell);				// float型に変
	getline(file, cell, ',');		// Y座標
	pos.y = stof(cell);				// float型に変換
	pos.z = 0.0f;					// Z値初期化

	// サイズ
	getline(file, cell, ',');		// Xサイズ
	scale.x = stof(cell);			// float型に変換
	getline(file, cell, ',');		// Yサイズ
	scale.y = stof(cell);			// float型に変換
	scale.z = 0.0f;					// Z値初期化


	// テクスチャ名読み込み
	getline(file, cell, ',');		// テクスチャ名
	path = "Assets/Texture/Title/" + cell + ".png";		// パス作成

	// 移動速度
	getline(file, cell, ',');		// 移動速度取得
	speed = stof(cell);				// 移動速度設定

	// 加速度
	getline(file, cell, ',');		// 加速度取得
	acceleration = stof(cell);		// 加速度設定


	CreateSceneObj<Bird>(objName.c_str());	// 通常UI作成
	birdUI = GetObj<Bird>(objName.c_str());	// 実体取得
	birdUI->Set2DObjNo(m_Total2DObjNo);		// オブジェクトナンバーセット
	birdUI->SetPos(pos);					// 座標セット
	birdUI->SetScale(scale);				// サイズセット
	// コンポーネント取得
	_modelRenderer2D = birdUI->GetComponent<ModelRenderer2D>();
	_modelRenderer2D->Load(path.c_str());	// パス設定

	birdUI->SetVelocity(speed);				// 移動速度設定
	birdUI->SetAcceleration(acceleration);	// 加速度設定
}

// 通常UI作成
void SceneTitle::NormalUICreate(ifstream & file, string cell)
{
	// 変数宣言
	GameObject* normalUI;
	ModelRenderer2D* _modelRenderer2D;	// モデルレンダラーコンポーネント
	DirectX::XMFLOAT3 pos;				// 座標
	DirectX::XMFLOAT3 scale;			// サイズ
	string path;						// パス
	string objName = cell;				// オブジェクトに関連づける名前

	// オブジェクトナンバー
	getline(file, cell, ',');	// オブジェクトNo取得
	m_Total2DObjNo++;			// オブジェクトカウントアップ

	objName += "UI" + cell;		// 名前

	// 座標
	getline(file, cell, ',');	// X座標
	pos.x = stof(cell);			// float型に変
	getline(file, cell, ',');	// Y座標
	pos.y = stof(cell);			// float型に変換
	pos.z = 0.0f;				// Z値初期化

	// サイズ
	getline(file, cell, ',');	// Xサイズ
	scale.x = stof(cell);		// float型に変換
	getline(file, cell, ',');	// Yサイズ
	scale.y = stof(cell);		// float型に変換
	scale.z = 0.0f;				// Z値初期化


	// テクスチャ名読み込み
	getline(file, cell, ',');	// テクスチャ名
	path = "Assets/Texture/Title/" + cell + ".png";		// パス作成


	CreateSceneObj<GameObject>(objName.c_str());	// 通常UI作成
	normalUI = GetObj<GameObject>(objName.c_str());	// 実体取得
	normalUI->Set2DObjNo(m_Total2DObjNo);			// オブジェクトナンバーセット
	normalUI->SetPos(pos);							// 座標セット
	normalUI->SetScale(scale);						// サイズセット
	normalUI->AddComponent<ModelRenderer2D>();		// コンポーネントセット
	_modelRenderer2D = normalUI->GetComponent<ModelRenderer2D>();	// コンポーネント取得
	_modelRenderer2D->Load(path.c_str());			// パス設定

}
