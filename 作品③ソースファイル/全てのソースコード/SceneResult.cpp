//SceneResult.cpp
//=====インクルード部=====
#include "SceneResult.h"
#include "CameraDebug.h"
#include "Geometory.h"
#include "Defines.h"
#include "Value.h"
#include "Input.h"
#include "Startup.h"
#include "XController.h"

//=====コンストラクタ=====
SceneResult::SceneResult(CSceneMng* pSceneMng, CSoundMng* pSoundMng)
	: m_pSceneMng(pSceneMng)
	, m_pSoundMng(pSoundMng)
	, m_nMoney(0)
	, m_nPer(0)
	, m_nTime(0)
	, m_SoundOne(true)
	, m_select(true)
	, m_SoundStop(true)
	, m_EndingCountDown(ENDUNG_WAIT_TIME)
{
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso")))
	{
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}

	m_pBG = new ResultBG();

	m_pStar[0] = new ResultStar(217.0f, 160.0f, 0.0f, 340.0f);
	m_pStar[1] = new ResultStar(339.0f, 113.0f, 0.0f, -5.0f);
	m_pStar[2] = new ResultStar(468.0f, 150.0f, 0.0f, 370.0f);

	m_pPer = new ResultPer(370.0f, 350.0f, 0.0f, -4.0f, m_nPer);
	m_pMsg = new ResultMsg(310.0f, 580.0f, 0.0f, -3.0f);
	m_pTime = new ResultTime(370.0f, 450.0f, 0.0f, -3.0f);
	m_pUI = new CUI();
	m_pStamp = new ResultStamp(550.0f, 550.0f, 0.0f, 0.0f);
	m_pPlayerUI = new ResultPlayer(1000.0f, 400.0f, 0.0f);
	m_pWindow = new ResultWindow();
}


//=====デストラクタ=====
SceneResult::~SceneResult()
{
	if (m_pVS)
	{
		delete m_pVS;
		m_pVS = nullptr;
	}
	if (m_pBG)
	{
		delete m_pBG;
		m_pBG = nullptr;
	}

	for (int i = 0; i < 3; ++i)
	{
		if (m_pStar)
		{
			delete m_pStar[i];
			m_pStar[i] = nullptr;
		}
	}
	if (m_pPer)
	{
		delete m_pPer;
		m_pPer = nullptr;
	}
	if (m_pMsg)
	{
		delete m_pMsg;
		m_pMsg = nullptr;
	}
	if (m_pTime)
	{
		delete m_pTime;
		m_pTime = nullptr;
	}
	if (m_pUI)
	{
		delete m_pUI;
		m_pUI = nullptr;
	}
	if (m_pStamp)
	{
		delete m_pStamp;
		m_pStamp = nullptr;
	}
	if (m_pPlayerUI)
	{
		delete m_pPlayerUI;
		m_pPlayerUI = nullptr;
	}
	if (m_pWindow)
	{
		delete m_pWindow;
		m_pWindow = nullptr;
	}
}

//=====更新処理=====
void SceneResult::Update(float tick)
{
	XINPUT_STATE state;
	XInputGetState(0, &state);
	XINPUT_KEYSTROKE stroke;
	XInputGetKeystroke(0, 0, &stroke);
	XINPUT_VIBRATION vibration;
	vibration.wLeftMotorSpeed = 0;
	vibration.wRightMotorSpeed = 0;
	XInputSetState(0, &vibration);
	m_pBG->Update();
	m_pPer->Update(m_nPer);
	m_pTime->Update(m_nTime);
	m_pStamp->Update();
	if (m_SoundStop) {
		m_pSoundMng->playSound(CSoundMng::SystemSE::Fpon);
		m_SoundStop = false;
	}//アニメーションSE

	int* clearCnt = m_pSceneMng->GetClearCnt();
	if (clearCnt[2] == 1 && !m_pSceneMng->isVewEnd()) {
		m_EndingCountDown--;
		if (!m_EndingCountDown) {
			m_pSceneMng->SetNextScene(CSceneMng::SceneKind::SCENE_ENDING);
			m_pSceneMng->SetVewEnd();
		}
	}
	else {

		// =-=-= 入力 =-=-=
		// ----- ボタン選択状況：はい -----
		if (m_pBG->IsEndAnime())
		{
			if (m_select) {
				if ((state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
					(state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
				{
					state.Gamepad.sThumbLX = 0;
					state.Gamepad.sThumbLY = 0;
				}

				if (IsKeyTrigger('S') || IsKeyTrigger(VK_DOWN) ||
					(state.dwPacketNumber != 3435973836 && state.Gamepad.sThumbLY < 0 &&
						state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
						state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && stroke.Flags == 0x0001
						|| state.Gamepad.wButtons&XINPUT_GAMEPAD_DPAD_DOWN&&stroke.Flags == 0x0001))				// リスタートにカーソル移動
				{
					m_select ^= 1;
					m_pWindow->SetRestart();
					m_pSoundMng->playSound(CSoundMng::SystemSE::select);
				}
				else if (IsKeyTrigger(VK_RETURN)/*|| IsKeyTrigger(VK_SPACE)*/
					|| state.Gamepad.wButtons&XINPUT_GAMEPAD_A&&stroke.Flags == 0x0001)	// セレクト画面
				{
					m_pSceneMng->SetNextScene(CSceneMng::SceneKind::SCENE_SELECT);
					if (m_pSoundMng->CheckSoundEnd(CSoundMng::SystemSE::decision)) {
						m_pSoundMng->playSound(CSoundMng::SystemSE::decision);
					}
				}
			}
			// ----- ボタン選択状況：いいえ -----
			else {
				if (IsKeyTrigger('W') || IsKeyTrigger(VK_UP) ||
					(state.dwPacketNumber != 3435973836 && state.Gamepad.sThumbLY > 0 &&
						state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
						state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && stroke.Flags == 0x0001
						|| state.Gamepad.wButtons&XINPUT_GAMEPAD_DPAD_UP&&stroke.Flags == 0x0001))				// はいにカーソル移動
				{
					m_select ^= 1;
					m_pWindow->SetSelect();
					m_pSoundMng->playSound(CSoundMng::SystemSE::select);
				}
				else if (IsKeyPress(VK_RETURN) /*|| IsKeyTrigger(VK_SPACE)*/
					|| state.Gamepad.wButtons&XINPUT_GAMEPAD_A&&stroke.Flags == 0x0001)	// リスタート処理実装
				{
					m_pSceneMng->SetNextScene((CSceneMng::SceneKind)m_oldPlayStage);
					//m_pSceneMng->Init();
					if (m_pSoundMng->CheckSoundEnd(CSoundMng::SystemSE::decision)) {
						m_pSoundMng->playSound(CSoundMng::SystemSE::decision);
					}
				}
			}
		}
	}

	// =-=-= 各種更新 =-=-=
	// ----- UIアニメーション・サウンド -----



	if (m_pBG->IsEndAnime())
	{
		if (m_nPer < 60 && m_SoundOne)
		{
			m_pSoundMng->playSound(CSoundMng::ResultSE::gameOver);
			m_SoundOne = false;
		}
		else if (m_nPer >= 60 && m_nPer < 80)
		{
			m_pStar[0]->Update();
			if (m_SoundOne)
			{
				m_pSoundMng->playSound(CSoundMng::ResultSE::gameClear);
				m_SoundOne = false;
			}
		}
		else if (m_nPer >= 80 && m_nPer < 100)
		{
			m_pStar[0]->Update();
			m_pStar[1]->Update();
			if (m_SoundOne)
			{
				m_pSoundMng->playSound(CSoundMng::ResultSE::gameClear);
				m_SoundOne = false;
			}
		}
		else if (m_nPer == 100)
		{
			m_pStar[0]->Update();
			m_pStar[1]->Update();
			m_pStar[2]->Update();
			if (m_SoundOne)
			{
				m_pSoundMng->playSound(CSoundMng::ResultSE::gameClear);
				m_SoundOne = false;
			}
		}
		m_pWindow->Update();	// ボタン
	}

	
	
}

//=====描画処理=====
void SceneResult::Draw()
{
	RenderTarget* pRTV = GetDefaultRTV();
	DepthStencil* pDSV = GetDefaultDSV();
	SetRenderTargets(1, &pRTV, nullptr);
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	m_pBG->Draw();


	if (m_pBG->IsEndAnime())
	{
		m_pPer->Draw();

		if (m_nPer < 60)
		{
			m_pMsg->DrawEval0();
			m_pTime->DrawTimeUp();
			m_pPlayerUI->DrawEval0();
		}
		else if (m_nPer >= 60 && m_nPer < 80)
		{
			m_pStar[0]->Draw();
			m_pMsg->DrawEval1();
			m_pTime->DrawTimeUp();
			m_pStamp->DrawEval1();
			m_pPlayerUI->DrawEval1();
		}
		else if (m_nPer >= 80 && m_nPer < 100)
		{
			m_pStar[0]->Draw();
			m_pStar[1]->Draw();
			m_pMsg->DrawEval2();
			m_pTime->DrawTimeUp();
			m_pStamp->DrawEval2();
			m_pPlayerUI->DrawEval2();
		}
		else if (m_nPer == 100)
		{
			m_pStar[0]->Draw();
			m_pStar[1]->Draw();
			m_pStar[2]->Draw();
			m_pMsg->DrawEval3();
			m_pTime->Draw();
			m_pStamp->DrawEval3();
			m_pPlayerUI->DrawEval3();
		}
		m_pUI->DrawResult(m_nMoney);

		m_pWindow->Draw();
	}



	/*m_pStar[0]->Draw();
	m_pStar[1]->Draw();
	m_pStar[2]->Draw();*/
}

//=====金額受け取り=====
void SceneResult::SetMoney(int money)
{
	m_nMoney = money;
}

//=====達成度受け取り=====
void SceneResult::SetPer(int per)
{
	m_nPer = per;
}

//=====クリアタイム受け取り======
void SceneResult::SetTime(int time)
{
	m_nTime = time;
}

void SceneResult::SetOldPlayStage(int stage)
{
	m_oldPlayStage = stage;
}

