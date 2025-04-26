//=================================================================
//
//	SceneTitle.cpp
//	タイトルシーン
//
//=================================================================

// ========== インクルード部 ==========
#include "SceneTitle.h"
#include "Input.h"
#include  "XController.h"


// ========== コンストラクタ ==========
CSceneTitle::CSceneTitle(CSceneMng* pSceneMng, CSoundMng* pSoundMng)
	: m_pushEsc(false)
	, m_select(true)
	, m_pSceneMng(pSceneMng)
	, m_pSoundMng(pSoundMng)
	, animestart(false)
	, animefin(false)
	, m_startPush(false)
{
	m_pTitle = new TItle();
	m_pEscape = new EscapeUI();
	m_pTSuction = new TSuction();
	m_pSceneMng->SetTSuction(m_pTSuction);
}

// ========== デストラクタ ==========
CSceneTitle::~CSceneTitle()
{
	SAFE_DELETE(m_pTitle);
	SAFE_DELETE(m_pEscape);
	SAFE_DELETE(m_pTSuction);
}

// ========== Update関数 ==========
void CSceneTitle::Update()
{
	// =-=-= ゲーム終了確認画面 =-=-=
	XINPUT_STATE state;
	XINPUT_KEYSTROKE stroke;
	XInputGetState(0, &state);
	XInputGetKeystroke(0, 0, &stroke);
	//キーボード・コントローラー操作
	if (m_pushEsc) {
		// ----- ボタン選択状況：はい -----
		if (m_select) {
			if (IsKeyTrigger('D') || IsKeyTrigger(VK_RIGHT) ||
				(state.dwPacketNumber != 3435973836 && state.Gamepad.sThumbLX > 0 &&
					state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
					state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && stroke.Flags == 0x0001
					|| state.Gamepad.wButtons&XINPUT_GAMEPAD_DPAD_RIGHT&&stroke.Flags == 0x0001))			// いいえにカーソル移動
			{
				m_select ^= 1;
				m_pEscape->SetNo();
				m_pSoundMng->playSound(CSoundMng::SystemSE::select);

			}
			else if (IsKeyPress(VK_RETURN) || IsKeyTrigger(VK_SPACE)
				|| state.Gamepad.wButtons&XINPUT_GAMEPAD_A&&stroke.Flags == 0x0001)	// ゲーム終了
			{
				m_pSceneMng->SetGameEnd();
				m_pSoundMng->playSound(CSoundMng::SystemSE::decision);
			}
		}
		// ----- ボタン選択状況：いいえ -----
		else {
			if (IsKeyTrigger('A') || IsKeyTrigger(VK_LEFT) ||
				(state.dwPacketNumber != 3435973836 && state.Gamepad.sThumbLX < 0 &&
					state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
					state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && stroke.Flags == 0x0001
					|| state.Gamepad.wButtons&XINPUT_GAMEPAD_DPAD_LEFT&&stroke.Flags == 0x0001))				// はいにカーソル移動
			{
				m_select ^= 1;
				m_pEscape->SetYes();
				m_pSoundMng->playSound(CSoundMng::SystemSE::select);
			}
			else if (IsKeyPress(VK_RETURN) || IsKeyTrigger(VK_SPACE)
				|| state.Gamepad.wButtons&XINPUT_GAMEPAD_A&&stroke.Flags == 0x0001)	// 確認画面を閉じる
			{
				m_pushEsc = false;
				m_pEscape->SetWindowAnime();
				m_pSoundMng->playSound(CSoundMng::SystemSE::decision);
			}
		}
	}

	// =-=-= タイトル画面 =-=-=
	else {	// 終了確認画面を開いていない
		if (IsKeyTrigger(VK_ESCAPE) || state.Gamepad.wButtons&XINPUT_GAMEPAD_START)	m_pushEsc = true;		// ESCで確認画面開く

		// ----- ゲームスタート -----
		else if ((IsKeyTrigger(VK_RETURN) || state.Gamepad.wButtons&XINPUT_GAMEPAD_A&&stroke.Flags == 0x0001)) {
			if (!m_startPush) {
				m_pSoundMng->playSound(CSoundMng::SystemSE::Tstrat);
				//m_pTitle->Update();
				m_startPush = true;
				animestart = true;
			}
		}
	}

	if (animestart)
	{
		animefin = m_pTitle->AnimeButton();
		if (animefin)
		{
			m_pSceneMng->SetNextScene(CSceneMng::SceneKind::SCENE_SELECT);
			animestart = false;
		}
	}
	
	// =-=-= 各種更新 =-=-=
	// ----- ボタンアニメーション -----
	m_pTitle->Update();
	//m_pTSuction->Update();
	m_pEscape->Update();


	
}

// ========== Draw関数 ==========
void CSceneTitle::Draw()
{
	RenderTarget* pRTV = GetDefaultRTV();
	SetRenderTargets(1, &pRTV, nullptr);

	m_pTitle->Draw();
	//if (!m_pTitle->GetPlayerAnime())//キャラが定位置についたらエフェクトを描画
	//{
	//	m_pTSuction->Draw();
	//}
	if (m_pushEsc)	{	// 終了確認画面中はウィンドウ表示
		m_pEscape->Draw();
	}

	
}