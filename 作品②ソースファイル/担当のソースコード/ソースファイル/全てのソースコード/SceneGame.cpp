//SceneGame.cpp
//=====インクルード部=====
#include "SceneGame.h"
#include "Geometory.h"
#include "Defines.h"
#include "Input.h"
#include "CameraDebug.h"
// ----- マップ読み込み -----
#include <fstream>
#include <sstream>
#include <string>

//=====定数・マクロ定義=====
#define DEBUG	(1)
#define MAX_FRAME (53)
#define WAIT_FRAME (53)
#define CAL_CAMERA (0.79f)
#define CAM_RAD_BEFORE (10.0f)
#define START_CAM_RAD (2.0f)
#define CAMERA_RAD (20.0f)
#define START_CAM_POS_Y (1.5f)
#define CAMERA_POS_Y (6.0f)
#define HORIZON (50.0f)
#define VERTICAL (45.0f)
#define START_HORIZON (-270.0f)
#define START_VERTICAL (45.0f)


//=====グローバル宣言=====
CUI* g_pUI;

//=====コンストラクタ=====
SceneGame::SceneGame(CSceneMng* pSceneMng, CSoundMng* pSoundMng)
	: m_pSceneMng(pSceneMng)
	, m_pSoundMng(pSoundMng)
	, m_pTrade{ nullptr }
	, m_start(false)
	, m_count(false)
	, time(0)
	, addtime(0)
	, Alpha(1.0f)
{
	// ----- 頂点シェーダー読み込み -----
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}

	m_pSkyModel = new Model;
	if (!m_pSkyModel->Load("Assets/Model/sky/sky.fbx", 1.0f, Model::Flip::XFlip)) {
		MessageBox(NULL, "Assets/map/sky/sky.fbx", "Error", MB_OK);
	}

	m_pSeaModel = new Model;
	if (!m_pSeaModel->Load("Assets/Model/Stage/Sea/Sea.fbx", 1.0f, Model::Flip::XFlip)) {
		MessageBox(NULL, "Assets/map/Stage/Sea.fbx", "Error", MB_OK);
	}

	// ----- データ作成 -----
	g_pUI = new CUI();
	m_pTimer = new CTimer();
	m_pCamera = new CameraDebug;
	m_pObjectMng = new CObjectMng;
	m_pPlayer = new CPlayer;
	m_pPlayer->SetObjectMng(m_pObjectMng);
	m_pPlayer->SetSoundMng(m_pSoundMng);
	m_pCollisionAreaMng = new CCollisionAreaMng;
	m_pCollisionAreaMng->SetPlayer(m_pPlayer);
	m_pCollision = new CCollision;
	m_pCollision->SetPlayer(m_pPlayer);
	m_pCollision->SetObjectManager(m_pObjectMng);
	m_pObjectMng->SetSound(m_pSoundMng);
	m_pObjectMng->SetSuction(m_pPlayer->GetSuction());
	m_pShopMenu = new CShopMenu();
	m_pShopMenu->SetSound(m_pSoundMng);
	m_pShopText = new CShopText();
	m_pShopText->SetSound(m_pSoundMng);
	m_pCountDown = new CCountDown();
	m_pShopBG = new ShopBG();
	m_pPlayerText = new CPlayerText();
	m_pPlayerText->SetObjMng(m_pObjectMng);
	m_pEndUI = new GameEndUI(640.0f, 360.0f, 0.0f);
	// マップ読み込み
	LoadMap(/*int 読み込むステージ番号, */m_pObjectMng->GetObjectList(), m_pCollisionAreaMng->GetAreaList(), m_pPlayer, m_pObjectMng);
	m_pProgress = new CProgress(m_pObjectMng->GetTotalObjNum(), m_pSoundMng);
	m_pCustomEquipment = new CCustomEquipment();
	// オブジェクトへのモデル割り当て
	m_pObjectMng->ModelSetting();
}

//=====デストラクタ=====
SceneGame::~SceneGame()
{
	// ----- データが存在したら削除 -----
	SAFE_DELETE(m_pVS);
	SAFE_DELETE(g_pUI);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pObjectMng);
	SAFE_DELETE(m_pCollisionAreaMng);
	SAFE_DELETE(m_pCollision);
	SAFE_DELETE(m_pTimer);
	SAFE_DELETE(m_pCustomEquipment);
	for (int i = 0; i < MAX_TRADE; i++) {
		SAFE_DELETE(m_pTrade[i]);
	}
	SAFE_DELETE(m_pShopMenu);
	SAFE_DELETE(m_pShopText);
	SAFE_DELETE(m_pProgress);
	SAFE_DELETE(m_pCountDown);
	SAFE_DELETE(m_pEndUI);
	SAFE_DELETE(m_pShopBG);
	SAFE_DELETE(m_pPlayerText);
	SAFE_DELETE(m_pSkyModel);
	SAFE_DELETE(m_pSeaModel);
}

//=====更新処理=====
void SceneGame::Update(float tick)
{
	// ----- 変数宣言 -----
	static int wait = 0;											// サインカーブ計算待機フレーム
	static float camRad = m_pPlayer->GetRadius();					// カメラ初期半径
	//static float camRad = CAM_RAD_BEFORE;
	static float camPosY = m_pPlayer->GetCameraPos().y;				// カメラ初期位置Y
	static float horizon = START_HORIZON;							// 平行ラジアン変換前
	float  horizonRad = DirectX::XMConvertToRadians(START_HORIZON);	// カメラ平行位置
	float  vertical = DirectX::XMConvertToRadians(START_VERTICAL);	// カメラ縦位置
	static float factor = 0.0f;										// フレーム計算用
	static float value = 0.0f;										// サインカーブ値

	static int frame = 0;			// フレーム用
	static int frame2 = 0;
	static bool flg = true;
	static bool zoomFlg = true;

	// ----- カメラ座標計算 -----
	if (flg)
	{
		m_pPlayer->SetHorizon(horizon);
		m_pPlayer->SetCameraPosX(camRad * sin((float)vertical) * cos((float)horizonRad));
		m_pPlayer->SetCameraPosZ(camRad * sin((float)vertical) * sin((float)horizonRad));
		flg = false;
	}
	//// ----- ズームイン -----
	//if (frame2 < MAX_FRAME) frame2++;
	//factor = static_cast<float>(frame2) / static_cast<float>(MAX_FRAME);
	//value = factor * factor * (3.0f - 2.0f * factor);

	//// ----- カメラ平行位置変動 -----
	//if (camRad > START_CAM_RAD && flg)
	//{
	//	camRad -= CAL_CAMERA * value;

	//	m_pPlayer->SetCamRadius(camRad);
	//}
	//else
	//{
	//	flg = false;
	//	m_pPlayer->SetCamRadius(START_CAM_RAD);
	//}

	// ----- 回転ズームアウト -----
	if (wait > WAIT_FRAME && zoomFlg)
	{
		// ----- サインカーブ計算 -----
		if (frame < MAX_FRAME) frame++;
		else zoomFlg = false;
		factor = static_cast<float>(frame) / static_cast<float>(MAX_FRAME);
		value = factor * factor * (3.0f - 2.0f * factor);

		// ----- カメラ平行位置変動 -----
		if (camRad < CAMERA_RAD)
		{
			camRad += CAL_CAMERA * value;

			m_pPlayer->SetCamRadius(camRad);
		}
		else m_pPlayer->SetCamRadius(CAMERA_RAD);

		// ----- カメラ回転計算 -----
		if (horizon < HORIZON)
		{
			horizon += CAL_CAMERA * value * ((HORIZON - START_HORIZON) / (CAMERA_RAD - START_CAM_RAD));
		}
		else horizon = HORIZON;

		horizonRad = DirectX::XMConvertToRadians(horizon);

		// ----- カメラ座標計算 -----
		m_pPlayer->SetHorizon(horizon);
		m_pPlayer->SetCameraPosX(camRad * sin((float)vertical) * cos((float)horizonRad));
		m_pPlayer->SetCameraPosZ(camRad * sin((float)vertical) * sin((float)horizonRad));

		// ----- カメラの高さ変動 -----
		if (camPosY < CAMERA_POS_Y)
		{
			camPosY += (CAL_CAMERA * value * (CAMERA_POS_Y - START_CAM_POS_Y / (CAMERA_RAD - START_CAM_RAD)));
			m_pPlayer->SetCameraPosY(camPosY);
		}
		else m_pPlayer->SetCameraPosY(CAMERA_POS_Y);
	}
	else wait++;

	Sprite::SetColor(DirectX::XMFLOAT4( 1.0f, 1.0f, 1.0f, 1.0f));
	// =-=-= ゲームの状況によって処理を分岐 =-=-=
	m_pCountDown->Update();
	// ----- ゲーム開始前 -----
	if (!m_start) {
		if (!m_count) {	// 一度だけ処理
			m_pSoundMng->playSound(CSoundMng::TimeSE::countDown1);			// カウントダウン再生
			m_pPlayer->Update();											// カメラなどを正しくセット
			m_pCustomEquipment->SetCustom(m_pPlayer->GetCustom());			// カスタム状態セット
			m_count = true;
		}

		if (time < 2) {														// タイマーを正しくセット
			m_pTimer->Update();
			time++;
		}
		if (m_pSoundMng->CheckSoundEnd(CSoundMng::TimeSE::countDown1))		// カウントダウンが鳴りやんだら
		{
			Sleep(300);														// ずれるので調整
			m_start = true;													// ゲームスタート
			m_pSoundMng->playSound(CSoundMng::BGM::game);					// BGM再生
			m_pSoundMng->playSound(CSoundMng::TimeSE::countDown1_pi);		// 開始音再生
		}

		return;	// ゲームが始まってないので以下を処理しない(入れ子防止)
	}
	// ----- 通常プレイ画面 -----
	if (!m_pPlayer->GetShop()) {
		m_pObjectMng->Update(tick);
		m_pCollision->Update();

		if (!m_pProgress->GetEndFlg()) {// リザルトに移る時にオブジェクト以外の処理を止める(吸い込み時の慣性を残すためオブジェクトは処理)
			m_pPlayer->Update();

			m_pCollisionAreaMng->Update();
			for (int i = 0; i < MAX_TRADE; i++)
			{
				if (m_pTrade[i])
				{
					m_pTrade[i]->Update();	// 商人更新
				}
			}
			m_pCustomEquipment->SetCustom(m_pPlayer->GetCustom());	// カスタム状態セット

			m_pTimer->Update();
			m_pProgress->Update(m_pObjectMng->GetSuctionedObjNum(), m_pTimer->GetTime());
			m_pPlayerText->Update();
		}
	}
	// ----- ショップ画面 -----
	else {
		
		m_pShopMenu->SetShopSuction(m_pPlayer->GetSuction());	// 吸い込みクラスセット
		m_pShopMenu->SetMoney(m_pPlayer->GetMoney());			// 所持金セット
		m_pShopMenu->SetCustom(m_pPlayer->GetCustom());			// カスタムセット
		m_pShopMenu->Update();									// ショップメニュー更新
		m_pShopMenu->SetMoney(m_pPlayer->GetMoney());			// 所持金セット
		m_pPlayer->SetShop(m_pShopMenu->GetShop());				// ショップ画面を閉じるか
		m_pCustomEquipment->SetCustom(m_pPlayer->GetCustom());	// カスタム状態確認
	}

	// ----- ゲーム終了後～遷移前 -----
	if (m_pProgress->GetEndFlg()) {
		// ゲーム終了SEが鳴りやんだら
		if (m_pSoundMng->CheckSoundEnd(CSoundMng::TimeSE::timeUp1) && m_pSoundMng->CheckSoundEnd(CSoundMng::TimeSE::timeUp2)) {
			m_pSceneMng->SetNextScene(CSceneMng::SceneKind::SCENE_RESULT);	// (仮)鳴りやんだらすぐ遷移
			// ＊＊ゲーム終了UI実装予定
			m_pSoundMng->AllDeleteSpeaker();								// SEをとめる
		}
		//ゲーム終了UI
		m_pEndUI->Update(400.0f, 400.0f);
	}
}

//=====描画処理=====
void SceneGame::Draw()
{
	DirectX::XMFLOAT4X4 mat[3];

	mat[0] = m_pPlayer->GetWorldMatrix();
	mat[1] = m_pPlayer->GetViewMatrix();
	mat[2] = m_pPlayer->GetProjectionMatrix();

	Geometory::SetWorld(mat[0]);
	Geometory::SetView(mat[1]);
	Geometory::SetProjection(mat[2]);

	m_pVS->WriteBuffer(0, mat);

	DrawSky(mat, m_pVS);
	DrawSea(mat, m_pVS);

	RenderTarget* pRTV = GetDefaultRTV();
	DepthStencil* pDSV = GetDefaultDSV();
	SetRenderTargets(1, &pRTV, pDSV);

	//----- オブジェクト -----
	for (int i = 0; i < MAX_TRADE; i++)	{
		if (m_pTrade[i])		{
			m_pTrade[i]->Draw();
		}
	}

	m_pPlayer->Draw();
	m_pObjectMng->Draw(mat);

#if DEBUG	//** エリア判定確認用
	m_pCollisionAreaMng->Draw(mat);
#endif

	// ----- UI -----
	SetRenderTargets(1, &pRTV, nullptr);
	g_pUI->Draw();				// お金描画
	m_pTimer->Draw();			// 時間描画
	m_pCustomEquipment->Draw();	// 装備アイコン描画
	m_pProgress->Draw();		// ノルマ描画
	m_pCountDown->Draw();		// カウントダウン
	m_pPlayerText->Draw();		// プレイヤー吹き出し

	if (g_pUI->GetAdd())
	{
		g_pUI->DrawAdd();
		Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		
	}

	if (m_pPlayer->GetShop())	// ショップ画面なら描画
	{
		m_pShopBG->Draw();
		Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		m_pShopMenu->Draw();
		g_pUI->Draw();				// お金描画
		if (g_pUI->GetAdd())
		{
			g_pUI->DrawAdd();
			Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}

	//ゲーム終了UI
	if (m_pProgress->GetEndFlg())
	{
		if (*m_pProgress->GetTime() <= 0)
		{
			m_pEndUI->DrawTimeUp();
		}
		else
		{
			m_pEndUI->DrawClear();
		}
	}
}

int * SceneGame::getMoney()
{
	return g_pUI->GetMoney();
}

int * SceneGame::getPer()
{
	return m_pProgress->GetProgressNum();
}

int * SceneGame::getTime()
{
	return m_pProgress->GetTime();
}

CUI * GetUI()
{
	return g_pUI;
}

// ========== マップ情報読み込み ==========
// 引　数：
// (int 現在のステージ数)
// list<Object*>*	objリストポインタ
// ColArea*			CollisionAreaリストポインタ
// CPlayer*			Playerポインタ
// 戻り値：なし
// ～関数概要～
// マップを読み込んでデータを各オブジェクトに設定する
// ======================================
void SceneGame::LoadMap(/*enum crntStage, */list<Object*>* pObjList, list<CCollisionArea*>* pAreaList, CPlayer* pPlayer, CObjectMng* pObjMng)
{
	// =-=-= 準備 =-=-=
	// ----- 変数宣言 -----
	string line;		// 行ごとの文字列
	string cell;		// セルごとの文字列
	char ch;			// 一文字ずつ読み込む際の文字列
	int comma = 0;		// カンマカウント
	int numLine = 0;	// 行カウント
	int numColumn = 0;	// 列カウント
	int maxLine;		// 最大行数
	int maxColumn;		// 最大列数
	float halfWidth;	// マップ最大幅
	float halfHeight;	// マップ最大高さ
	int objKind;		// オブジェクトの種類
	int height;			// オブジェクト設置する高さ(地面～段目)
	float x, y, z;		// 中心座標
	float sx, sy, sz;	// スケール
	int direct;			// 正面方向。１：奥　２：右　３：手前　４：左
	int attr;			// 属性
	int level;			// オブジェクトレベル

	int tradeNum = 0;	// 商人を読み込んだ回数
	int totalObjNum = 0;// 吸い込めるオブジェクトの総数

	// ----- マップデータ読み込み -----
	ifstream file("Assets/map/STAGEa.csv");
	if (!file.is_open()) {
		MessageBox(NULL, "Stageが読み込めない", "Error", MB_OK);
	}

	// =-=-= オブジェクトデータ読み込み =-=-=
	// ----- 全体情報読み込み -----
	getline(file, cell, ',');								// 行数を文字列として取得
	maxLine = stoi(cell);									// 文字列を整数に変換して格納
	getline(file, cell, ',');	maxColumn = stoi(cell);		// 列数
	getline(file, cell, ',');	halfWidth = stof(cell) / 2;	// マップ幅 / 2
	getline(file, cell, ',');	halfHeight = stof(cell) / 2;// マップ高さ / 2

	getline(file, cell);			// 現在行の末尾に移動

	// ----- 各オブジェクトデータ読み込み -----
	for (int i = 0; i < maxLine; i++)	// 全ての行を読み込み
	{
		// ----- 準備 -----
		getline(file, cell);		// 現在行の末尾に移動
		getline(file, cell, ',');	// 次の行の2列目へ
		comma = 0;					// ０から
		while (comma != 2) {		// データ読み込み先頭列までスキップ
			file.get(ch);
			if (ch == ',') {
				++comma;
			}
		}

		// ----- 各種パロメータ読み込み -----
		getline(file, cell, ',');	objKind = stoi(cell);	// 種類
		getline(file, cell, ',');	height = stoi(cell);	// 高さ
		getline(file, cell, ',');	x = stof(cell) * -1;	// 中心座標
		x += halfWidth;
		getline(file, cell, ',');	y = stof(cell);
		getline(file, cell, ',');	z = stof(cell);
		z -= halfHeight;
		getline(file, cell, ',');	sx = stof(cell);		// スケール
		getline(file, cell, ',');	sy = stof(cell);
		getline(file, cell, ',');	sz = stof(cell);
		getline(file, cell, ',');							// 正面方向
		if (!cell.empty()) {	// 空でなければ
			direct = stoi(cell);
		}
		getline(file, cell, ',');							// 属性
		if (!cell.empty()) {	// 空でなければ
			attr = stoi(cell);
		}
		getline(file, cell, ',');							// オブジェクトレベル
		if (!cell.empty()) {	// 空でなければ
			level = stoi(cell);
		}

		// ----- オブジェクトに設定 -----
		switch (objKind) {
		case 1:	// プレイヤー
			pPlayer->SetPos(DirectX::XMFLOAT3(x, y, z));
			break;
		case 2:		// 商人
			m_pTrade[tradeNum] = new CTrade(x, y, z, 90.0f * (direct - 1));
			m_pTrade[tradeNum]->SetPlayer(m_pPlayer);
			m_pCollision->SetTrade(m_pTrade[tradeNum]);
			tradeNum++;
			break;
		case 3:		// マット ※削除
			break;
		case 4:		// 看板
			pObjList->push_back(new CSignboard(x, y, z, sx, sy, sz));
			break;
		case 5:		// 海
			pAreaList->push_back(new CAreaSea(x, y, z, sx, sy, sz));
			break;
		case 6:		// 地面
			pAreaList->push_back(new CAreaGround(x, y, z, sx, sy, sz, attr));
			break;
		case 7:		// 高台
			pAreaList->push_back(new CAreaHill(x, y, z, sx, sy, sz, attr));
			break;
		case 8:		// 坂
			pAreaList->push_back(new CAreaSlope(x, y, z, sx, sy, sz, direct, attr));
			break;
		case 9:		// 木
			if (level == 2)
				pObjList->push_back(new CTreeSmall(x, y, z, sx, sy, sz, m_pSoundMng));
			else if (level == 3)
				pObjList->push_back(new CTree(x, y, z, sx, sy, sz, m_pSoundMng));
			break;
		case 10:	// 岩
			if (level == 2) {
				pObjList->push_back(new CRockSmall(x, y, z, sx, sy, sz, m_pSoundMng));
			}
			else if (level == 3) {
				pObjList->push_back(new CRock(x, y, z, sx, sy, sz, m_pSoundMng));
			}
			break;
		case 11:	// 家
			//pObjList->push_back(new CHouse(x, y, z, sx, sy, sz,m_pSoundMng));
			break;
		case 12:	// 木材
			pObjList->push_back(new CWood(x, y, z));
			break;
		case 13:	// 石
			pObjList->push_back(new CStone(x, y, z));
			break;
		case 14:	// フェンス
			pObjList->push_back(new CFence(x, y, z, sx, sy, sz, 90.0f * (direct - 1), m_pSoundMng));
			break;
		case 15:	// きのこ
			if (level == 1)
				pObjList->push_back(new Mushroom(x, y, z, sx, sy, sz));
			else if (level == 2)
				pObjList->push_back(new MushroomMedium(x, y, z, sx, sy, sz));
			break;
		}
	}

	// ----- 吸い込めるオブジェクトの総数をカウント -----
	for (Object* pObj : *pObjList) {
		if (pObj->GetCreateNum() == 0) {
			totalObjNum += 1;
		}
		else {
			totalObjNum += pObj->GetCreateNum();
		}
	}
	pObjMng->SetTotalObjNum(totalObjNum);	// 総数を渡す
}

void SceneGame::DrawSky(DirectX::XMFLOAT4X4 * mat, VertexShader * vs)
{

	DirectX::XMMATRIX world;
	//---変換行列を計算
	world = DirectX::XMMatrixScaling(1.0f, 0.2f, 1.0f) *
		DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);

	world = DirectX::XMMatrixTranspose(world);
	DirectX::XMStoreFloat4x4(&mat[0], world);

	//---変換行列を設定
	Geometory::SetWorld(mat[0]);
	Geometory::SetView(mat[1]);
	Geometory::SetProjection(mat[2]);

	RenderTarget* pRTV = GetDefaultRTV();
	DepthStencil* pDSV = GetDefaultDSV();
	SetRenderTargets(1, &pRTV, nullptr);

	//	m_pVertexShader = vs;
	vs->WriteBuffer(0, mat);
	m_pSkyModel->SetVertexShader(vs);
	m_pSkyModel->Draw();
}

void SceneGame::DrawSea(DirectX::XMFLOAT4X4 * mat, VertexShader * vs)
{

	DirectX::XMMATRIX world;
	//---変換行列を計算
	world = DirectX::XMMatrixScaling(0.15f, 0.45f, 0.15f) *
		DirectX::XMMatrixTranslation(0.0f, -3.0f, 0.0f);

	world = DirectX::XMMatrixTranspose(world);
	DirectX::XMStoreFloat4x4(&mat[0], world);

	//---変換行列を設定
	Geometory::SetWorld(mat[0]);
	Geometory::SetView(mat[1]);
	Geometory::SetProjection(mat[2]);

	RenderTarget* pRTV = GetDefaultRTV();
	DepthStencil* pDSV = GetDefaultDSV();
	SetRenderTargets(1, &pRTV, nullptr);

	//	m_pVertexShader = vs;
	vs->WriteBuffer(0, mat);
	m_pSeaModel->SetVertexShader(vs);
	m_pSeaModel->Draw();
}