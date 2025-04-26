//CSceneStage2.cpp
//=====インクルード部=====
#include "SceneStage2.h"
#include "Geometory.h"
#include "Defines.h"
#include "Input.h"
#include "ShaderList.h"
#include "BlueMushroomNemoto.h"
// ----- マップ読み込み -----
#include <fstream>
#include <sstream>
#include <string>

//=====グローバル宣言=====

//=====コンストラクタ=====
CSceneStage2::CSceneStage2(CSceneMng* pSceneMng, CSoundMng* pSoundMng)
	: CSceneStageBase(pSceneMng, pSoundMng)
{
	m_pShopMenu = new CShopMenu(2, m_pUI, m_pSoundMng);
	m_pTimer = new CTimer(210);
	// マップ読み込み
	LoadMap(m_pObjectMng->GetObjectList(), m_pCollisionAreaMng->GetAreaList(), m_pPlayer, m_pObjectMng);
	m_pProgress = new CProgress(m_pObjectMng->GetTotalObjNum(), m_pSoundMng);
	m_pCollision->SetTrade(m_pTrade);
	m_pCollisionAreaMng->SetObjList(m_pObjectMng->GetObjectList());
	m_pCollision->SetTradeIcon(m_pTradeIcon);
	// オブジェクトへのモデル割り当て
	m_pObjectMng->ModelSetting();
	// オブジェクトマネージャーにプレイヤー情報をセット
	m_pObjectMng->SetPlayer(m_pPlayer);
	m_pObjectMng->Update(0.0f);		// オブジェクトの高さを調整するため一度処理

	// ----- ステージモデル読み込み -----
	m_pStageModel[0] = new Model;	// 空
	if (!m_pStageModel[0]->Load("Assets/Model/Stage/Sky/Sky.fbx", 1.0f, Model::Flip::XFlip)) {
		MessageBox(NULL, "Assets/map/Stage/sky/sky.fbx", "Error", MB_OK);
	}
	m_pStageModel[1] = new Model;	// 海
	if (!m_pStageModel[1]->Load("Assets/Model/Stage/Sea/Sea.fbx", 1.0f, Model::Flip::XFlip)) {
		MessageBox(NULL, "Assets/map/Stage/Sea.fbx", "Error", MB_OK);
	}
	m_pStageModel[2] = new Model;	// 陸
	if (!m_pStageModel[2]->Load("Assets/Model/Stage/Stage2/Stage.fbx", 1.0f, Model::Flip::ZFlip)) {
		MessageBox(NULL, "Assets/Model/Stage/Stage/stage2/Stage2.fbx", "Error", MB_OK);
	}
	//m_pStageModel[1]->SetPixelShader(ShaderList::GetPS(ShaderList::PS_FOG));
	m_pStageModel[2]->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_pPlayer->SetShopCustom(m_pShopMenu->GetShopCustom());
}

//=====デストラクタ=====
CSceneStage2::~CSceneStage2()
{
	//ShaderList::Uninit();
	for (int i = 0; i < 3; i++)
	{
		SAFE_DELETE(m_pStageModel[i]);
	}
}


//=====更新処理=====
void CSceneStage2::Update(float tick)
{
#if DEBUG_KEY
	// ----- 強制シーン遷移 -----
	if (IsKeyTrigger('R'))	m_pSceneMng->SetNextScene(CSceneMng::SceneKind::SCENE_RESULT);
	else if (IsKeyTrigger('C')) {
		m_pProgress->SetClear();
		m_pSceneMng->SetNextScene(CSceneMng::SceneKind::SCENE_RESULT);
		return;
	}

	// ----- お金増やし -----
	if (IsKeyTrigger('Q')) {
		m_pUI->AddMoney(50000);
		m_pPlayer->SetMoney(50000);
	}
#endif

	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	// ===== ゲームの状況によって処理を分岐 =====
	m_pCountDown->Update();
	// =-=-= ゲーム開始前 =-=-=
	if (!m_start) {
		if (!m_count) {	// 一度だけ処理
			m_pSoundMng->playSound(CSoundMng::TimeSE::countDown1);			// カウントダウン再生
			m_pPlayer->Update(tick);											// カメラなどを正しくセット
			m_pCustomEquipment->SetCustom(m_pPlayer->GetCustom());			// カスタム状態セット
			m_count = true;
		}
		if (time < 2) {														// タイマーを正しくセット
			m_pTimer->Update();
			time++;
		}

		// ----- 開始カメラワーク -----
		StartCameraWork();

		if (m_pSoundMng->CheckSoundEnd(CSoundMng::TimeSE::countDown1))		// カウントダウンが鳴りやんだら
		{
			Sleep(300);														// ずれるので調整
			m_start = true;													// ゲームスタート
			m_pSoundMng->playSound(CSoundMng::BGM::game2);					// BGM再生
			m_pSoundMng->playSound(CSoundMng::TimeSE::countDown1_pi);		// 開始音再生
		}

		return;	// ゲームが始まってないので以下を処理しない(入れ子防止)
	}
	// =-=-= ポーズ画面 =-=-=
	XINPUT_STATE state;
	XInputGetState(0, &state);

	if (m_pause) {
		XINPUT_KEYSTROKE stroke;
		XInputGetKeystroke(0, 0, &stroke);
		if ((state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
			(state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
		{
			state.Gamepad.sThumbLX = 0;
			state.Gamepad.sThumbLY = 0;
		}
		LibEffekseer::GetManager().Get()->StopAllEffects();
		// ----- メニュー選択 -----
		if ((IsKeyTrigger('W') || IsKeyTrigger(VK_UP))
			|| (state.dwPacketNumber != 3435973836 && state.Gamepad.sThumbLY > 0 &&
				state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
				state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && stroke.Flags == 0x0001
				|| state.Gamepad.wButtons&XINPUT_GAMEPAD_DPAD_UP&&stroke.Flags == 0x0001) && (m_pauseSelect > 0)) {			// 上移動
			m_pauseSelect--;
			if (m_pauseSelect < 0)
			{
				m_pauseSelect = 0;
			}
			m_pSoundMng->playSound(CSoundMng::SystemSE::select);
		}
		else if ((IsKeyTrigger('S') || IsKeyTrigger(VK_DOWN)) ||
			(state.dwPacketNumber != 3435973836 && state.Gamepad.sThumbLY < 0 &&
				state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
				state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && stroke.Flags == 0x0001
				|| state.Gamepad.wButtons&XINPUT_GAMEPAD_DPAD_DOWN&&stroke.Flags == 0x0001) && (m_pauseSelect < MAX_PAUSEMENU - 1)) {	// 下移動
			m_pauseSelect++;
			if (m_pauseSelect > 2)
			{
				m_pauseSelect = 2;
			}
			m_pSoundMng->playSound(CSoundMng::SystemSE::select);
		}
		m_pPause->Update(m_pauseSelect);

		// ----- 決定 -----
		if (IsKeyTrigger(VK_RETURN) || IsKeyTrigger(VK_SPACE)
			|| state.Gamepad.wButtons&XINPUT_GAMEPAD_A&&stroke.Flags == 0x0001) {
			switch (m_pauseSelect)
			{
			case 0:	// 戻る
				m_pause = false;
				m_pSoundMng->playSound(CSoundMng::SystemSE::decision);
				break;
			case 1:	// リスタート
				m_pSoundMng->playSound(CSoundMng::SystemSE::decision);
				m_pSceneMng->GameRestart();
				break;
			case 2:	// セレクトへ
				m_pSoundMng->playSound(CSoundMng::SystemSE::decision);
				m_pSceneMng->SetNextScene(CSceneMng::SceneKind::SCENE_SELECT);
				break;
			}
		}

		return;	// 以下を処理しない
	}
	// =-=-= 通常プレイ画面 =-=-=
	if (!m_pPlayer->GetShop()) {
		m_pObjectMng->Update(tick);
		m_pCollision->Update();
		m_pCollisionAreaMng->Update();
		m_pDust->Update();

		if (!m_pProgress->GetEndFlg()) {// リザルトに移る時にオブジェクト以外の処理を止める(吸い込み時の慣性を残すためオブジェクトは処理)
			m_pPlayer->Update(tick);

			m_pCollisionAreaMng->Update();
			for (auto pTrade : m_pTrade) {
				if (pTrade) {
					pTrade->Update(tick);	// 商人更新
				}
			}
			m_pCustomEquipment->SetCustom(m_pPlayer->GetCustom());	// カスタム状態セット

			m_pTimer->Update();
			m_pProgress->Update(m_pObjectMng->GetSuctionedObjNum(), m_pTimer->GetTime(), m_pTimer->GetMaxTime());
			m_pPlayerText->Update();

			// ポーズ画面開いたか
			if (IsKeyTrigger(VK_ESCAPE) || state.Gamepad.wButtons&XINPUT_GAMEPAD_START)	m_pause = true;
		}
	}
	// =-=-= ショップ画面 =-=-=
	else {

		m_pShopMenu->SetShopSuction(m_pPlayer->GetSuction());	// 吸い込みクラスセット
		m_pShopMenu->SetMoney(m_pPlayer->GetMoney());			// 所持金セット
		m_pShopMenu->SetCustom(m_pPlayer->GetCustom());			// カスタムセット
		m_pShopMenu->Update(tick);									// ショップメニュー更新
		m_pShopMenu->SetMoney(m_pPlayer->GetMoney());			// 所持金セット
		m_pPlayer->SetShop(m_pShopMenu->GetShop());				// ショップ画面を閉じるか
		m_pCustomEquipment->SetCustom(m_pPlayer->GetCustom());	// カスタム状態確認
	}

	// =-=-= ゲーム終了後～遷移前 =-=-=
	if (m_pProgress->GetEndFlg()) {
		// ゲーム終了SEが鳴りやんだら
		if (m_pSoundMng->CheckSoundEnd(CSoundMng::TimeSE::timeUp1) && m_pSoundMng->CheckSoundEnd(CSoundMng::TimeSE::timeUp2)) {
			m_pSceneMng->SetNextScene(CSceneMng::SceneKind::SCENE_RESULT);	// (仮)鳴りやんだらすぐ遷移
			m_pSoundMng->AllDeleteSpeaker();								// SEをとめる
		}
		//ゲーム終了UI
		m_pEndUI->Update(400.0f, 400.0f);
		LibEffekseer::GetManager().Get()->StopAllEffects();
	}
}

//=====描画処理=====
void CSceneStage2::Draw()
{
	DirectX::XMFLOAT4X4 mat[3];

	mat[0] = m_pPlayer->GetWorldMatrix();
	mat[1] = m_pPlayer->GetViewMatrix();
	mat[2] = m_pPlayer->GetProjectionMatrix();

	m_pVS->WriteBuffer(0, mat);
	RenderTarget* pRTV = GetDefaultRTV();
	DepthStencil* pDSV = GetDefaultDSV();
	SetRenderTargets(1, &pRTV, pDSV);

	// ----- ステージ -----
	DrawStage(mat, m_pVS);	// 陸・海・空

	//----- オブジェクト -----
	m_pPlayer->Draw();
	for (auto pTrade : m_pTrade) {
		if (pTrade) {
			pTrade->Draw();	// 商人更新
		}
	}
	m_pObjectMng->Draw(mat);

#if DEBUG	//** エリア判定確認用
	Geometory::SetWorld(mat[0]);
	Geometory::SetView(mat[1]);
	Geometory::SetProjection(mat[2]);

	m_pCollisionAreaMng->Draw(mat);
#endif

	SetRenderTargets(1, &pRTV, nullptr);

	// ----- UI -----
	m_pUI->Draw();				// お金描画
	m_pTimer->Draw();			// 時間描画
	m_pCustomEquipment->Draw();	// 装備アイコン描画
	m_pProgress->Draw();		// ノルマ描画
	m_pCountDown->Draw();		// カウントダウン
	m_pPlayerText->Draw();		// プレイヤー吹き出し

	//商人UI
	if (m_pPlayer->GetTrade())
	{
		m_pTradeIcon->Draw();
	}

	// -----エフェクト-----
	m_pDust->Draw();
	m_pLeaf->Draw();
	m_pEBag->Draw();
	if (m_pUI->GetAdd())
	{
		m_pUI->DrawAdd();
		Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	}

	if (m_pPlayer->GetShop())	// ショップ画面なら描画
	{
		m_pShopBG->Draw();
		Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		m_pShopMenu->Draw();
		m_pUI->Draw();				// お金描画
		if (m_pUI->GetAdd())
		{
			m_pUI->DrawAdd();
			Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}

	//ポーズ画面
	if (m_pause)
	{
		m_pPause->Draw();
	}

	//ゲーム終了UI	if (m_pProgress->GetEndFlg())
	{
		if (m_pProgress->GetProgressNum() >= 100)
		{
			m_pEndUI->DrawClear();
			
		}
		else
		{
			m_pEndUI->DrawTimeUp();
		}
	}
}

void CSceneStage2::DrawStage(DirectX::XMFLOAT4X4 *mat, VertexShader* vs)
{
	DirectX::XMMATRIX world;
	RenderTarget* pRTV = GetDefaultRTV();
	DepthStencil* pDSV = GetDefaultDSV();

	SetRenderTargets(1, &pRTV, nullptr);

	for (int i = 0; i < 3; i++)
	{
		switch (i)
		{
		case 0:	// 空
			world = DirectX::XMMatrixTranspose(DirectX::XMMatrixScaling(0.05f, 0.02f, 0.05f));
			break;
		case 1:	// 海
			//SetRenderTargets(1, &pRTV, pDSV);
			world = DirectX::XMMatrixTranspose(DirectX::XMMatrixScaling(0.1f, 0.15f, 0.1f) *
				DirectX::XMMatrixTranslation(0.0f, -1.0f, 0.0f));
			break;
		case 2:	// 陸
			SetRenderTargets(1, &pRTV, pDSV);

			//---変換行列を計算
			world = DirectX::XMMatrixTranspose(DirectX::XMMatrixScaling(0.57, 1.0, 0.63)*
				DirectX::XMMatrixTranslation(0.0f, -2.13f, 0.0f));
			break;
		}

		DirectX::XMStoreFloat4x4(&mat[0], world);

		//---変換行列を設定
		vs->WriteBuffer(0, mat);
		m_pStageModel[i]->SetVertexShader(vs);
		m_pStageModel[i]->Draw();
	}

}

// ========== マップ情報読み込み ==========
// 引　数：
// (int 現在のステージ数)
// list<Object*>*	objリストポインタ
// ColArea*			CollisionAreaリストポインタ
// CPlayer*			Playerポインタ
// 戻り値：なし
// ～関数概要～
// マップ2を読み込んでデータを各オブジェクトに設定する
// ======================================
void CSceneStage2::LoadMap(list<Object*>* pObjList, list<CCollisionArea*>* pAreaList, CPlayer* pPlayer, CObjectMng* pObjMng)
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
	ifstream file("Assets/map/STAGE2.csv");
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
			switch (height) {
			case 0: y = STAGE2_HT0;	break;
			case 1: y = STAGE2_HT1;	break;
			case 2: y = STAGE2_HT2;	break;
			}
			pPlayer->SetPos(DirectX::XMFLOAT3(x, y, z));
			pPlayer->SetRandHeight(y);
			break;
		case 2:		// 商人
			switch (height)	{
			case 0: y = STAGE2_HT0;	break;
			case 1: y = STAGE2_HT1;	break;
			case 2: y = STAGE2_HT2;	break;
			}
			m_pTrade.push_back(new CTrade(x, y, z, 90.0f * (direct - 1)));
			m_pTrade[tradeNum]->SetPlayer(m_pPlayer);
			m_pTradeIcon->SetPlayer(m_pPlayer);
			tradeNum++;
			break;
		case 3:		// マット ※削除
			break;
		case 4:		// 看板
			pObjList->push_back(new CSignboard(x, y, z, sx, sy, sz, 90.0f * (direct - 1)));
			break;
		case 5:		// 海
			pAreaList->push_back(new CAreaSea(x, y, z, sx, sy, sz));
			break;
		case 6:		// 地面
			pAreaList->push_back(new CAreaGround(x, y, z, sx, sy, sz, attr));
			break;
		case 7:		// 高台
			pAreaList->push_back(new CAreaHill(x, y, z, sx, sy, sz, attr, 2));
			break;
		case 8:		// 坂
			pAreaList->push_front(new CAreaSlope(height, x, y, z, sx, sy, sz, direct, attr, 2));
			break;
		case 9:		// 木
			pObjList->push_back(new CTree(x, y - 0.2f, z, sx, sy - 0.4f, sz, level));
			break;
		case 10:	// 岩
			pObjList->push_back(new CRock(x, y, z, sx, sy, sz, level));
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
			pObjList->push_back(new CFence(x, y, z, sx, sy, sz, 90.0f * (direct - 1), level));
			break;
		case 15:	// きのこ
			pObjList->push_back(new Mushroom(x, y, z, sx, sy, sz, level));
			break;
		case 16:	// あおきのこギミック
			pObjList->push_back(new BlueMushroom(x, y, z, sx, sy, sz));
			// 根本の座標セット
			for (int i = 0; i < 5; i++)
			{
				pObjList->push_back(new BlueMushroomNemoto(x, y - 0.8f, z, 1.0f, 1.0f, 1.0f));
			}
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

void CSceneStage2::StartCameraWork()
{
	if (m_flg)
	{
		// ----- 変数宣言 -----
		m_wait = 0;													// カーブ計算待機フレーム
		m_camRad = m_pPlayer->GetRadius();							// カメラ初期半径
		//m_camRad = CAM_RAD_BEFORE;
		m_camPosY = m_pPlayer->GetCameraPos().y;					// カメラ初期位置Y
		m_horizon = START_HORIZON;									// 平行ラジアン変換前
		m_horizonRad = DirectX::XMConvertToRadians(START_HORIZON);	// カメラ平行位置
		m_vertical = DirectX::XMConvertToRadians(START_VERTICAL);	// カメラ縦位置
		m_factor = 0.0f;											// フレーム計算用
		m_value = 0.0f;												// カーブ値

		m_frame = 0;			// フレーム用
		m_flg = true;
		m_zoomFlg = true;

		// ----- カメラ座標計算 -----

		m_pPlayer->SetHorizon(m_horizon);
		m_pPlayer->SetCameraPosX(m_camRad * sin((float)m_vertical) * cos((float)m_horizonRad));
		m_pPlayer->SetCameraPosZ(m_camRad * sin((float)m_vertical) * sin((float)m_horizonRad));
		m_flg = false;
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
	if (m_wait > WAIT_FRAME && m_zoomFlg)
	{
		// ----- カーブ計算 -----
		if (m_frame < MAX_FRAME) m_frame++;
		else m_zoomFlg = false;
		m_factor = static_cast<float>(m_frame) / static_cast<float>(MAX_FRAME);
		m_value = m_factor * m_factor * (3.0f - 2.0f * m_factor);

		// ----- カメラ平行位置変動 -----
		if (m_camRad < CAMERA_RAD)
		{
			m_camRad += CAL_CAMERA * m_value;

			m_pPlayer->SetCamRadius(m_camRad);
		}
		else m_pPlayer->SetCamRadius(CAMERA_RAD);

		// ----- カメラ回転計算 -----
		if (m_horizon < HORIZON)
		{
			m_horizon += CAL_CAMERA * m_value * ((HORIZON - START_HORIZON) / (CAMERA_RAD - START_CAM_RAD));
		}
		else m_horizon = HORIZON;

		m_horizonRad = DirectX::XMConvertToRadians(m_horizon);

		// ----- カメラ座標計算 -----
		m_pPlayer->SetHorizon(m_horizon);
		m_pPlayer->SetCameraPosX(m_camRad * sin((float)m_vertical) * cos((float)m_horizonRad));
		m_pPlayer->SetCameraPosZ(m_camRad * sin((float)m_vertical) * sin((float)m_horizonRad));

		// ----- カメラの高さ変動 -----
		if (m_camPosY < CAMERA_POS_Y)
		{
			m_camPosY += (CAL_CAMERA * m_value * (CAMERA_POS_Y - START_CAM_POS_Y / (CAMERA_RAD - START_CAM_RAD)));
			m_pPlayer->SetCameraPosY(m_camPosY);
		}
		else m_pPlayer->SetCameraPosY(CAMERA_POS_Y);
	}
	else m_wait++;
}