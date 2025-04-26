//=================================================================
//
//	SceneSelect.cpp
//	ステージ選択シーン
//
//=================================================================

// ========== インクルード部 ==========
#include "SceneSelect.h"
#include "MushroomPlanet.h"
#include "GreenPlanet.h"
#include "WholeCakePlanet.h"
#include "Input.h"
#include "XController.h"
#include "Value.h"

#define DRAW_UI_FRAME	(240)	//「新しい依頼」UI表示フレーム（長さは仮）


CSceneSelect::CSceneSelect(CSceneMng* pSceneMng, CSoundMng* pSoundMng, Fade* pFade, int OldPlayStage)
	: m_pSceneMng(pSceneMng)
	, m_pSoundMng(pSoundMng)
	, m_pFade(pFade)
	, m_bShop(false)
	, m_camMove(false)
	, m_select(OldPlayStage)
	, m_openFrame(0)
	, m_nItem{ 0 }
	, m_nMoney(0)
	, m_openStage(false)
	, m_openUI(false)
	, m_sceneSwap(false)
{
	// ----- 頂点シェーダー読み込み -----
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}

	m_pCamera = new CCameraSelect();
	

	m_pSelect = new Select();
	m_pShopBG = new ShopBG();
	m_pScore = new SelectScore();
	m_pMoney = new CUI(m_pSceneMng->GetMoney());
	m_pShopMenu = new CShopMenu(0, m_pMoney, m_pSoundMng);
	m_nMoney = m_pSceneMng->GetMoney();

	m_pPlanets[CSceneMng::SceneKind::SCENE_STAGE1] = new GreenPlanet();		// ステージ１の惑星追加
	m_pPlanets[CSceneMng::SceneKind::SCENE_STAGE2] = new MushroomPlanet();	// きのこ惑星追加
	m_pPlanets[CSceneMng::SceneKind::SCENE_STAGE3] = new WholeCakePlanet();	// ホールケーキアイランド追加
	m_pPlanets[OldPlayStage]->StartFocus();		// 選択中の惑星を自転

	m_pCamera->SetGreen(m_pPlanets[CSceneMng::SceneKind::SCENE_STAGE1]);
	m_pCamera->SetMushroom(m_pPlanets[CSceneMng::SceneKind::SCENE_STAGE2]);
	m_pCamera->SetWholeCake(m_pPlanets[CSceneMng::SceneKind::SCENE_STAGE3]);
	
	m_openStage = m_pSceneMng->GetOpenStage();								// ステージ開放したかどうかを取得
	m_pCamera->Init(m_select);

	m_pSelectModel = new Model;	// 宇宙
	if (!m_pSelectModel->Load("Assets/Model/Univers/Univers.fbx", 1.0f, Model::Flip::XFlip)) {
		MessageBox(NULL, "Assets/Model/Univers/Univers.fbx", "Error", MB_OK);
	}
}

CSceneSelect::~CSceneSelect()
{
	SAFE_DELETE(m_pShopMenu);
	SAFE_DELETE(m_pSelect);
	SAFE_DELETE(m_pShopBG);
	SAFE_DELETE(m_pScore);
	for (int i = 0; i < CSceneMng::MAX_STAGE; ++i)
	{
		SAFE_DELETE(m_pPlanets[i]);
	}
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pMoney);
	SAFE_DELETE(m_pSelectModel);
	SAFE_DELETE(m_pVS);
}

void CSceneSelect::Update(float tick)
{
	// =-=-= 更新 =-=-=
	for (int i = 0; i < CSceneMng::MAX_STAGE; ++i)		// 惑星更新処理
	{
		m_pPlanets[i]->Update(tick);
	}
	m_pCamera->Update();
	
	// ===== 惑星開放画面 =====
	if (m_openStage) {		// 解放中
		// ----- カメラ移動前 -----
		if (!m_camMove) {
			m_camMove = true;
			m_select++;
			m_pPlanets[m_select]->StartFocus();	// 自転始め
			m_pCamera->SetMoveRight(m_select);			// カメラ移動方向をセット(右)
		}
		// ----- カメラ移動後 -----
		if (!m_pCamera->GetMove()) {	
			m_openUI = true;			// 「新しい依頼」UI表示
			m_pSelect->UpdateNewRequest();
			if (m_openFrame > DRAW_UI_FRAME) {	// 一定時間経過したら
				m_openStage = false;	// 惑星開放演出を終了する
				m_openUI = false;		// UI非表示
			}
			m_openFrame++;				// フレームカウント
		}
		return; // 以下を処理しない
	}

	// ===== ショップ画面 =====
	if (m_bShop) {
		//----準備----
		m_pShopMenu->SetItem(m_nItem);							// アイテム使用格納変数セット
		m_pShopMenu->SetMoney(&m_nMoney);						// 所持金セット
		
		//----更新処理----
		m_pShopMenu->Update(tick);					// ショップメニュー更新
		m_bShop = m_pShopMenu->GetShop();		// ショップを閉じるか

		return;	// 以下を処理しない（入れ子防止）
	}

	// ===== 惑星選択画面 =====
	// =-=-= キー入力 =-=-=
	XINPUT_STATE state;
	XInputGetState(0, &state);		
	if ((state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
			(state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
		{
			state.Gamepad.sThumbLX = 0;
			state.Gamepad.sThumbLY = 0;
		}
	// ----- 惑星切り替え -----
	if (!m_pCamera->GetMove()) {

#if DEBUG_KEY	// ステージ直移動
		if (IsKeyTrigger('1')) m_pSceneMng->SetNextScene(CSceneMng::SCENE_STAGE1);
		else if (IsKeyTrigger('2')) m_pSceneMng->SetNextScene(CSceneMng::SCENE_STAGE2);
		else if (IsKeyTrigger('3')) m_pSceneMng->SetNextScene(CSceneMng::SCENE_STAGE3);
#endif // !DEBUG
		XINPUT_KEYSTROKE stroke;
		XInputGetKeystroke(0, 0, &stroke);
		if (state.dwPacketNumber != 3435973836)
		{
			if (state.Gamepad.sThumbLX < 0 &&
				state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
				state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
				|| state.Gamepad.wButtons&XINPUT_GAMEPAD_DPAD_LEFT)
			{
				StageSawpLeft();
			}
			else if (state.Gamepad.sThumbLX > 0 &&
				state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
				state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
				|| state.Gamepad.wButtons&XINPUT_GAMEPAD_DPAD_RIGHT)	// 右移動
			{
				StageSawpRight();
			}
			// ----- 惑星決定 -----
			else if (state.Gamepad.wButtons&XINPUT_GAMEPAD_A) {
				if (m_select <= m_pSceneMng->GetOpenStageNum() && !m_sceneSwap && !m_pFade->IsPlay()) {	// 解放済みかつ初回かつフェード中でなければ
					m_sceneSwap = true;
					m_pSceneMng->SetNextScene((CSceneMng::SceneKind)m_select);	// 選択中の惑星ステージシーンへ遷移
					if (m_pSoundMng->CheckSoundEnd(CSoundMng::SystemSE::decision)) {
						m_pSoundMng->playSound(CSoundMng::SystemSE::decision);
					}
				}
			}
			else if (state.Gamepad.wButtons&XINPUT_GAMEPAD_Y) {
				m_bShop = true;
			}
			// ----- 戻るボタン -----
			else if (state.Gamepad.wButtons&XINPUT_GAMEPAD_B&&stroke.Flags==0x0001) {
				m_pSceneMng->SetNextScene(CSceneMng::SCENE_TITLE); // タイトルへ遷移
				if (m_pSoundMng->CheckSoundEnd(CSoundMng::SystemSE::cancel))
					m_pSoundMng->playSound(CSoundMng::SystemSE::cancel);//se

			}
		}
		if ((IsKeyTrigger('A') || IsKeyTrigger(VK_LEFT)))	// 左移動
		{
			StageSawpLeft();
		}
		else if ((IsKeyTrigger('D') || IsKeyTrigger(VK_RIGHT)))	// 右移動
		{
			StageSawpRight();
		}
		// ----- 惑星決定 -----
		else if (IsKeyTrigger(VK_RETURN) || IsKeyTrigger(VK_SPACE)) {
			if (m_select <= m_pSceneMng->GetOpenStageNum() && !m_sceneSwap && !m_pFade->IsPlay()) {	// 解放済みかつ初回かつフェード中でなければ
				m_sceneSwap = true;
				m_pSceneMng->SetNextScene((CSceneMng::SceneKind)m_select);	// 選択中の惑星ステージシーンへ遷移
				m_pSoundMng->playSound(CSoundMng::SystemSE::decision);
			}
		}
		// ----- ショップ開く -----
		else if (IsKeyTrigger('E')) {
			m_bShop = true;
		}
		// ----- 戻るボタン -----
		else if (IsKeyTrigger(VK_ESCAPE)) {
			m_pSceneMng->SetNextScene(CSceneMng::SCENE_TITLE); // タイトルへ遷移
			if(m_pSoundMng->CheckSoundEnd(CSoundMng::SystemSE::cancel))
			m_pSoundMng->playSound(CSoundMng::SystemSE::cancel);//se
		}
	}

	m_pSelect->Update(m_select);
	m_pScore->Update(m_pSceneMng->GetScore(), m_pSceneMng->GetClearTime(), m_select);
	m_pSoundMng->StopSound(CSoundMng::SystemSE::Fpon);
}

void CSceneSelect::Draw()
{
	//=====惑星描画=====
	DirectX::XMFLOAT4X4 mat[3];	// 変換行列格納場所

	// ----- 各種行列設定 -----
	mat[1] = m_pCamera->GetViewMatrix();
	mat[2] = m_pCamera->GetProjectionMatrix();

	m_pVS->WriteBuffer(0, mat);
	RenderTarget* ModelpRTV = GetDefaultRTV();
	DepthStencil* ModelpDSV = GetDefaultDSV();
	SetRenderTargets(1, &ModelpRTV, ModelpDSV);

	// ----- ステージ -----
	DrawSelect(mat, m_pVS);	// 宇宙

	// 惑星描画処理
	for (int i = 0; i < CSceneMng::MAX_STAGE; ++i)
	{
		m_pPlanets[i]->Draw(mat);
	}

	RenderTarget* pRTV = GetDefaultRTV();
	DepthStencil* pDSV = GetDefaultDSV();
	SetRenderTargets(1, &pRTV, nullptr);

	// ===== 依頼書 =====
	if (!m_pCamera->GetMove()) {	// カメラ移動中は非表示
		m_pSelect->Draw();
		m_pScore->Draw();
	}

	// ===== 「新しい依頼が～」UI =====
	if (m_openUI) {					// 特定のタイミングのみ表示
		m_pSelect->DrawNewRequest();
	}

	// ===== ショップ =====
	if (m_bShop)
	{
		m_pShopBG->Draw();
		m_pShopMenu->Draw();
		m_pMoney->Draw();
	}
}

void CSceneSelect::DrawSelect(DirectX::XMFLOAT4X4 * mat, VertexShader * vs)
{
	DirectX::XMMATRIX world;
	RenderTarget* pRTV = GetDefaultRTV();
	DepthStencil* pDSV = GetDefaultDSV();

	SetRenderTargets(1, &pRTV, nullptr);

	world = DirectX::XMMatrixTranspose(DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f));

	DirectX::XMStoreFloat4x4(&mat[0], world);

	//---変換行列を設定
	vs->WriteBuffer(0, mat);
	m_pSelectModel->SetVertexShader(vs);
	m_pSelectModel->Draw();

}

int * CSceneSelect::GetItem()			// アイテム使用情報ゲット
{
	return m_nItem;
}

Planet * CSceneSelect::GetPlanet(int num)
{
	return m_pPlanets[num];
}

void CSceneSelect::StageSawpLeft()
{
	// ----- 解放済みかチェック -----
	int CheckSelect = m_select;		// 作業用変数にうつす

	CheckSelect--;
	if (CheckSelect < CSceneMng::SCENE_STAGE1) {			// 選択範囲を超えていたら補正
		CheckSelect = CSceneMng::MAX_STAGE - 1;
	}
	if (CheckSelect > m_pSceneMng->GetOpenStageNum()) {
		return;												// 開放していなければカメラ移動しない
	}

	// ----- 値更新 -----
	m_pPlanets[m_select]->EndFocus();	// 自転止め
	m_select--;

	if (m_select < CSceneMng::SCENE_STAGE1) {		// 選択範囲を超えていたら補正
		m_select = CSceneMng::MAX_STAGE - 1;
	}

	// ----- カメラ移動 -----
	m_pPlanets[m_select]->StartFocus();	// 自転始め
	m_pCamera->SetMoveLeft(m_select);

	//SE
	if (m_pSoundMng->CheckSoundEnd(CSoundMng::SystemSE::swap))
	{
		m_pSoundMng->playSound(CSoundMng::SystemSE::swap);
	}
}

void CSceneSelect::StageSawpRight()
{
	// ----- 解放済みかチェック -----
	int CheckSelect = m_select;		// 作業用変数にうつす

	CheckSelect++;
	if (CheckSelect > CSceneMng::MAX_STAGE - 1) {		// 選択範囲を超えていたら補正
		CheckSelect = CSceneMng::SCENE_STAGE1;
	}
	if (CheckSelect > m_pSceneMng->GetOpenStageNum()) {
		return;												// 開放していなければカメラ移動しない
	}

	// ----- 値更新 -----
	m_pPlanets[m_select]->EndFocus();	// 自転止め
	m_select++;

	if (m_select > CSceneMng::MAX_STAGE - 1) {			// 選択範囲を超えていたら補正
		m_select = CSceneMng::SCENE_STAGE1;
	}

	// ----- カメラ移動 -----
	m_pCamera->SetMoveRight(m_select);
	m_pPlanets[m_select]->StartFocus();	// 自転始め

	//SE
	if (m_pSoundMng->CheckSoundEnd(CSoundMng::SystemSE::swap))
	{
		m_pSoundMng->playSound(CSoundMng::SystemSE::swap);
	}
}
