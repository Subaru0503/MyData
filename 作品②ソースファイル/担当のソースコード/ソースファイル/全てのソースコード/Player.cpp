//Player.cpp Test　test2 test3
//=====インクルード部=====
#include "Player.h"
#include "Input.h"
#include "Geometory.h"
#include "XController.h"
#include "SceneGame.h"
#include "ShaderList.h"
#include <cmath>

//=====マクロ定義=====
#define MOVE_SPEED (0.15f)				//プレイヤー移動速度
#define MOVE_DASH (0.2f)				//プレイヤー加速度
#define MOVE_DASH2 (0.05f)				//プレイヤー加速度
#define MOVE_SLANTING (0.75f)			//斜め移動時の制御計算値
#define CAMERA_ROTATION_SPEED (0.1f)	//カメラ回転速度、ラジアン角利用時
#define CAMERA_ANGLE_MOVE (3.0f)		//カメラ回転速度、角度利用時
#define CAMERA_MOVE_SPEED (0.1f)		//カメラ移動速度
#define CAMERA_FOVY (40.0f)				//カメラ視野角
#define CAMERA_NEAR (1.0f)				//カメラ投影近距離限界
#define CAMERA_FAR (20.0f)				//カメラ投影遠距離限界
#define MIN_VERTICAL (0.5f)				//カメラ縦アングル制御最小値、ラジアン角
#define MAX_VERTICAL (1.5f)				//カメラ縦アングル制御最大値、ラジアン角
#define MAX_ANGLE_VERTICAL (80.0f)		//カメラ縦アングル制御最大値、角度
#define MIN_ANGLE_VERTICAL (10.0f)		//カメラ縦アングル制御最小値、角度
#define MAX_CAMERA_POS_Y (10.0f)		//プレイヤーとカメラとの距離最大値
#define MIN_CAMERA_POS_Y (0.5f)			//プレイヤーとカメラとの距離最小値
#define PI (180.0f / 3.14f)				//ラジアン変換用
#define MAX_TIME (180.0f)				//制限時間
#define PLAYER_GRAVITY (0.4f)
#define BOOTS_SPEED	(1.3f)				// ブーツ解放時の移動速度倍率
#define FRAME (53)
//===== アイテムの効果 =====
#define SPEED_UP (1.2f)				// 速度アップ

//===== デメリット時間 =====
#define DEMELIT_TIME (3)			// デメリットの時間(秒)

//===== コンストラクタ =====
CPlayer::CPlayer()
	: m_pos(-115.0f, 0.0f, 152.0f)	//プレイヤー座標
	, m_scale(1.0f, 1.0f, 1.0f)		//プレイヤーの大きさ
	, m_camPos(0.0f, 1.5f, 9.0f)	//プレイヤー座標を原点としたカメラ座標
	, m_look(0.0f, 0.3f, 0.0f)		//焦点
	, m_up(0.0f, 1.0f, 0.0f)		//カメラの上方向
	, m_move(0.0f, 0.0f, 0.0f)		//移動速度
	, m_fovy(DirectX::XMConvertToRadians(CAMERA_FOVY))	//視野角
	, m_aspect(16.0f / 9.0f)		//画面比率
	, m_near(0.1f)					//メッシュ表示近距離限界
	, m_far(100.0f)					//メッシュ表示遠距離限界
	, m_radius(2.0f)				//プレイヤーとの距離
	, m_horizon(1.55f)				//平行方向ラジアン角
	, m_vertical(1.0f)				//縦方向ラジアン角
	, m_angleHorizon(50.0f)			//平行角度
	, m_angleVertical(45.0f)		//縦角度
	, m_directRad(0.0f)				//プレイヤーの向きラジアン角
	, m_directAngle(0.0f)			//プレイヤーの向き角度
	, m_direct(DIRECT_UP)			//プレイヤーの向き　上下左右
	, m_pObjectMng(nullptr)
	, m_pModel(nullptr)
	, m_pVS(nullptr)
	, m_pSuction(nullptr)			// 吸い込み機能クラス
	, m_oldPlayerForward(0.0f, 0.0f, 1.0f)// プレイヤー方向退避
	, m_nCustom{ 0, 0, 0, 0, 0 }
	, m_nMoney(0)
	, m_nTime(0)
	, m_fTimeLimit(MAX_TIME)
	, m_trade(false)
	, m_gravity(0.0f)
	, m_randKind(CAreaGround::kind::grass)
	, m_randHeight(0)
	, m_randSlope(false)
	, m_randBiscuit(false)
	, m_bShop(false)
	, m_nCandleDemerit(0)
	, m_nDemelitFrame(0)
	, m_nDrink(0)
	, m_nNozzle(0)
	, IsMove(false)
	, Pmove(false)
	, Pvaccum(false)
	, m_tutorial(false)
	, m_tutorialDraw(false)
	, m_suction(false)
	, m_bDrill(nullptr)
	, m_bSaw(nullptr)
	, m_bHammer(nullptr)
	, m_pShadowTex(nullptr)
{
	// =-=-= 初期化 =-=-=
	m_horizon = m_angleHorizon / PI;
	m_vertical = m_angleVertical / PI;
	m_pSuction = new Suction();	
	m_pDrill = new CDrill();
	m_pSaw = new CSaw();
	m_pHammer = new CHammer();

	m_pSuction->SetDrill(m_pDrill);
	m_pSuction->SetHammer(m_pHammer);
	m_pSuction->SetSaw(m_pSaw);// 吸い込み機能クラス作成

	// =-=-= 各種データ読み込み =-=-=
	// ----- モデル -----
	m_pModel = new Model;
	if (!m_pModel->Load("Assets/Model/Player/taiki.fbx", 0.17f, Model::Flip::XFlip, Model::Kind::Anime)) {
		MessageBox(NULL, "Assets/Model/Player/taiki.fbx", "Error", MB_OK);
	}
	// ----- 深度バッファ設定 -----
	//RenderTarget* pRTV = GetDefaultRTV();
	//DepthStencil* pDSV = GetDefaultDSV();
	//SetRenderTargets(1, &pRTV, pDSV);	// ３D表示

	// ----- 頂点シェーダー -----
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}
	m_pModel->SetVertexShader(m_pVS);	//モデルへ読み込んだ頂点シェーダーを設定
	m_pModel->SetVertexShader(ShaderList::GetVS(ShaderList::VS_ANIME));
	m_pModel->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	anime[0] = m_pModel->AddAnimation("Assets/Model/Player/taiki.fbx");
	anime[1] = m_pModel->AddAnimation("Assets/Model/Player/run.fbx");
	anime[2] = m_pModel->AddAnimation("Assets/Model/Player/tati_suikomi.fbx");
	anime[3] = m_pModel->AddAnimation("Assets/Model/Player/run_suikomi.fbx");
	
	m_pSuction->SetPlayer(this);

	m_pShadowTex = new Texture();
	if (FAILED(m_pShadowTex->Create("Assets/Texture/Shadow.png")))
	{
		MessageBox(NULL, "shadow", "Error", MB_OK);
	}
}

//=====デストラクタ=====
CPlayer::~CPlayer()
{
	// ----- データが存在していれば削除 -----
	SAFE_DELETE(m_pModel);
	SAFE_DELETE(m_pVS);
	SAFE_DELETE(m_pSuction);
	SAFE_DELETE(m_pEffect);
	SAFE_DELETE(m_pRunSmoke);
	SAFE_DELETE(m_pESuction);
	SAFE_DELETE(m_pEStun);
	SAFE_DELETE(m_pDrill);
	SAFE_DELETE(m_pSaw);
	SAFE_DELETE(m_pHammer);
	SAFE_DELETE(m_pShadowTex);
}

//=====更新処理=====
void CPlayer::Update(float tick)
{
	// =-=-= 値退避 =-=-=
	// --- プレイヤー過去座標
	m_oldPos = m_pos;
	// ---プレイヤーの向きベクトル
	DirectX::XMFLOAT3 playerForward = GetForwardVector();

	float Speed;
	//----プレイヤーのスピードの設定----
	if (!m_nDrink)
	{
		Speed = MOVE_SPEED;
	}
	else
	{
		Speed = MOVE_SPEED * SPEED_UP;
	}

	//----ノズル強化のアイテムが使用されていたら----
	if (m_nNozzle)
	{
		m_pSuction->PowerUP();			// 吸引力強化
		m_nNozzle = 0;					// ノズルフラグ下げ
	}
	//---------プレイヤー操作処理---------
	//---プレイヤー移動
	Pmove = false;
	//XINPUT_STATE state;
	XInputGetState(0, &state);	XInputGetKeystroke(0, 0, &stroke);
	if (state.dwPacketNumber == 3452816845)
	{
		state.Gamepad.sThumbLX = 0; state.Gamepad.sThumbLY = 0;
		state.Gamepad.sThumbRX = 0; state.Gamepad.sThumbRY = 0;
		state.Gamepad.bLeftTrigger = 0; state.Gamepad.bRightTrigger = 0;
	}
	if ((state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		state.Gamepad.sThumbLX = 0;
		state.Gamepad.sThumbLY = 0;

	}
	if ((state.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
		(state.Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
	{
		state.Gamepad.sThumbRX = 0;
		state.Gamepad.sThumbRY = 0;
	}
	if (state.dwPacketNumber != 3452816845)
	{
		if (state.Gamepad.sThumbLY != 0 || state.Gamepad.sThumbLX != 0)
		{
			Pmove = true;
			if (state.Gamepad.sThumbLY > 0 &&
				state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
				state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			{
				if (m_direct == DIRECT_DOWN) { m_move.z = 0.0f; m_move.x = 0.0f; }	//切り返しを高速に
				m_direct = DIRECT_UP;
				m_move.x += playerForward.x;
				m_move.z += playerForward.z;
				m_oldPlayerForward = playerForward;	// プレイヤーの向きを退避
				CPlayer::Footsteps(state);
			}
			if (state.Gamepad.sThumbLY < 0 &&
				state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
				state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)//後ろ
			{
				if (m_direct == DIRECT_UP) { m_move.z = 0.0f; m_move.x = 0.0f; }
				m_direct = DIRECT_DOWN;
				m_move.x -= playerForward.x;
				m_move.z -= playerForward.z;
				DirectX::XMStoreFloat3(&m_oldPlayerForward, DirectX::XMVectorSet(playerForward.x * -1.0f, playerForward.y * 1, playerForward.z*-1.0f, 0.0f));	// プレイヤーの向きを退避
				CPlayer::Footsteps(state);
			}
			if (state.Gamepad.sThumbLX < 0 &&
				state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
				state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)//左
			{
				if (m_direct == DIRECT_RIGHT) { m_move.x = 0.0f; m_move.z = 0.0f; }
				m_direct = DIRECT_LEFT;
				DirectX::XMFLOAT3 playerRight = GetRightVector();
				m_move.x += playerRight.x;
				m_move.z += playerRight.z;
				m_oldPlayerForward = playerRight;	// プレイヤーの向きを退避
				CPlayer::Footsteps(state);
			}
			if (state.Gamepad.sThumbLX > 0 &&
				state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
				state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)//右
			{

				if (m_direct == DIRECT_LEFT) { m_move.x = 0.0f; m_move.z = 0.0f; }
				m_direct = DIRECT_RIGHT;
				DirectX::XMFLOAT3 playerRight = GetRightVector();
				m_move.x -= playerRight.x;
				m_move.z -= playerRight.z;
				DirectX::XMStoreFloat3(&m_oldPlayerForward, DirectX::XMVectorSet(playerRight.x * -1, playerRight.y * 1, playerRight.z * -1, 0.0f));;	// プレイヤーの向きを退避
				CPlayer::Footsteps(state);
			}
			if (state.Gamepad.sThumbLX > 0 &&
				state.Gamepad.sThumbLY > 0 &&
				state.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
				state.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)//右上
			{
				if (m_direct == DIRECT_DOWNL) { m_move.x = 0.0f; m_move.z = 0.0f; }
				m_direct = DIRECT_UPR;
				DirectX::XMFLOAT3 playerUpRight = GetUpRightVector();
				m_move.x += playerUpRight.x;
				m_move.z += playerUpRight.z;
				m_oldPlayerForward = playerUpRight;
				CPlayer::Footsteps(state);
			}
			if (state.Gamepad.sThumbLX < 0 &&
				state.Gamepad.sThumbLY > 0 &&
				state.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
				state.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)//左上
			{
				if (m_direct == DIRECT_DOWNR) { m_move.x = 0.0f; m_move.z = 0.0f; }
				m_direct = DIRECT_UPL;
				DirectX::XMFLOAT3 playerUpLeft = GetUpLeftVector();
				m_move.x += playerUpLeft.x;
				m_move.z += playerUpLeft.z;
				m_oldPlayerForward = playerUpLeft;
				CPlayer::Footsteps(state);
			}
			if (state.Gamepad.sThumbLX > 0 &&
				state.Gamepad.sThumbLY < 0 &&
				state.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
				state.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)//右下
			{
				if (m_direct == DIRECT_UPL) { m_move.x = 0.0f; m_move.z = 0.0f; }
				m_direct = DIRECT_DOWNR;
				DirectX::XMFLOAT3 playerUpLeft = GetUpLeftVector();
				m_move.x -= playerUpLeft.x;
				m_move.z -= playerUpLeft.z;
				DirectX::XMStoreFloat3(&m_oldPlayerForward, DirectX::XMVectorSet(playerUpLeft.x * -1, playerUpLeft.y * 1, playerUpLeft.z * -1, 0.0f));;	// プレイヤーの向きを退避
				CPlayer::Footsteps(state);
			}
			if (state.Gamepad.sThumbLX < 0 &&
				state.Gamepad.sThumbLY < 0 &&
				state.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
				state.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)//左下
			{
				if (m_direct == DIRECT_UPR) { m_move.x = 0.0f; m_move.z = 0.0f; }
				m_direct = DIRECT_DOWNL;
				DirectX::XMFLOAT3 playerUpRight = GetUpRightVector();
				m_move.x -= playerUpRight.x;
				m_move.z -= playerUpRight.z;
				DirectX::XMStoreFloat3(&m_oldPlayerForward, DirectX::XMVectorSet(playerUpRight.x * -1, playerUpRight.y * 1, playerUpRight.z * -1, 0.0f));;	// プレイヤーの向きを退避
				CPlayer::Footsteps(state);
			}
			CPlayer::Footsteps(state);
		}
	}
	
	ShowCursor(false);		//カーソル消し
	if (state.dwPacketNumber == 3452816845)
	{
		if (IsKeyPress('W'))	//前
		{
			if (m_direct == DIRECT_DOWN) { m_move.z = 0.0f; m_move.x = 0.0f; }	//切り返しを高速に
			m_direct = DIRECT_UP;
			m_move.x += playerForward.x;
			m_move.z += playerForward.z;
			m_oldPlayerForward = playerForward;	// プレイヤーの向きを退避
			// ----- 歩行音 -----
			CPlayer::Footsteps(state);// SEを再生
			Pmove = true;
		}
		CPlayer::Footsteps(state);
		// SEを停止
		if (IsKeyPress('S'))	//後ろ
		{
			if (m_direct == DIRECT_UP) { m_move.z = 0.0f; m_move.x = 0.0f; }
			m_direct = DIRECT_DOWN;
			m_move.x -= playerForward.x;
			m_move.z -= playerForward.z;
			DirectX::XMStoreFloat3(&m_oldPlayerForward, DirectX::XMVectorSet(playerForward.x * -1.0f, playerForward.y * 1.0f, playerForward.z*-1.0f, 0.0f));	// プレイヤーの向きを退避
			CPlayer::Footsteps(state);
			// SEを再生
			Pmove = true;
		}
		CPlayer::Footsteps(state);
		// SEを停止
		if (IsKeyPress('A'))	//左
		{
			if (m_direct == DIRECT_RIGHT) { m_move.x = 0.0f; m_move.z = 0.0f; }
			m_direct = DIRECT_LEFT;
			DirectX::XMFLOAT3 playerRight = GetRightVector();
			m_move.x += playerRight.x;
			m_move.z += playerRight.z;
			m_oldPlayerForward = playerRight;	// プレイヤーの向きを退避
			CPlayer::Footsteps(state);
			// SEを再生
			Pmove = true;
		}
		CPlayer::Footsteps(state);
		// SEを停止
		if (IsKeyPress('D'))	//右
		{
			if (m_direct == DIRECT_LEFT) { m_move.x = 0.0f; m_move.z = 0.0f; }
			m_direct = DIRECT_RIGHT;
			DirectX::XMFLOAT3 playerRight = GetRightVector();
			m_move.x -= playerRight.x;
			m_move.z -= playerRight.z;
			DirectX::XMStoreFloat3(&m_oldPlayerForward, DirectX::XMVectorSet(playerRight.x * -1.0f, playerRight.y * 1.0f, playerRight.z * -1.0f, 0.0f));;	// プレイヤーの向きを退避
			CPlayer::Footsteps(state);
			// SEを再生
			Pmove = true;
		}
		CPlayer::Footsteps(state);
	}

	// SEを停止
	//---吸込み、破壊処理
	XINPUT_VIBRATION vibration;
	vibration.wLeftMotorSpeed = 0;
	vibration.wRightMotorSpeed = 0;
	XInputSetState(0, &vibration);
	if (!m_nCandleDemerit &&state.dwPacketNumber == 3452816845 && IsKeyPress(VK_SPACE) && !IsKeyPress(VK_RSHIFT)
		|| !m_nCandleDemerit &&state.dwPacketNumber != 3452816845 &&state.Gamepad.bRightTrigger && !state.Gamepad.bLeftTrigger)	// スペースキーを押している間
	{
		Pvaccum = true;
		// リスト内のオブジェクトが吸い込み範囲内か判定し真偽を格納
		m_pSuction->IsObjectInSuctionRange(m_pObjectMng->GetObjectList(), m_pos, m_oldPlayerForward,
			m_nCustom);
		//---吸込み処理
		m_pSuction->SuctionObject(&m_nCandleDemerit, m_nCustom);
		if (m_suction)
		{
			m_pSuction->PlayGimmick();	// ギミック
		}
		m_pESuction->Update();//吸い込みエフェクト
		//----移動速度ダウン----
		Speed *= 0.8f;

		//----吸い込み音------
		if (m_pSuction->GetNozzleLevel() == 1)
		{
			if (m_pSoundMng->CheckSoundEnd(CSoundMng::SuctionSE::wind))
				m_pSoundMng->playSound(CSoundMng::SuctionSE::wind);
		}
		else if (m_pSuction->GetNozzleLevel() == 2)
		{
			if (m_pSoundMng->CheckSoundEnd(CSoundMng::SuctionSE::wind2))
				m_pSoundMng->playSound(CSoundMng::SuctionSE::wind2);
		}
		else
		{
			if (m_pSoundMng->CheckSoundEnd(CSoundMng::SuctionSE::wind3))
				m_pSoundMng->playSound(CSoundMng::SuctionSE::wind3);
		}

		vibration.wRightMotorSpeed = 65535;
		XInputSetState(0, &vibration);
	}
	else if (m_nCandleDemerit)
	{
		m_nDemelitFrame++;	// フレームカウント
		if (m_nDemelitFrame / 60 >= DEMELIT_TIME)	// 一d定時間経過したか
		{
			m_nCandleDemerit = 0;	// デメリットフラグ下げ
			m_nDemelitFrame = 0;	// フレームカウントリセット
			m_pEStun->Stop();
		}
		m_pEStun->Update();
		m_pESuction->Stop();
		StopSound();
	}
	if (state.dwPacketNumber == 3452816845&&IsKeyRelease(VK_SPACE) ||
		state.dwPacketNumber != 3452816845 &&state.Gamepad.bRightTrigger==0)	// スペースキーを離した瞬間
	{
		Pvaccum = false;
		for (Object* pObj : *m_pObjectMng->GetObjectList())
		{
			// オブジェクトの吸い込まれフラグと揺れフラグを全ておろす
			pObj->SetSuctionFlg(false);
			pObj->SetShake(false);
			pObj->SetSuctionGimmick(false);
		}
		StopSound();
		m_pESuction->Stop();
		vibration.wLeftMotorSpeed = 0;
		vibration.wRightMotorSpeed = 0;
		XInputSetState(0, &vibration);
	}

	// ギミック開始
	if (m_pSuction->GetStart())
	{
		m_pSuction->ReleaseGimmick();
	}

	for (Object* pObj : *m_pObjectMng->GetObjectList())
	{
		if (pObj->IsGetMoney() && pObj->GetDelete())
		{
			m_nMoney += pObj->GetMoney();
			m_pUI_Money->AddMoney(pObj->GetMoney());
		}
	}

	// 商人に話しかける
		// 商人に話しかける
	if (m_trade && IsKeyTrigger('E') || m_trade && state.Gamepad.wButtons&XINPUT_GAMEPAD_A)
	{
		m_bShop = true;
		LibEffekseer::GetManager().Get()->StopAllEffects();
		StopSound();
	}

	// チュートリアル看板を見る
	if ((m_tutorial && IsKeyTrigger('E') && !m_bShop) || (m_tutorial && state.Gamepad.wButtons&XINPUT_GAMEPAD_A&&stroke.Flags== 0x0001 && !m_bShop)) {
		m_tutorialDraw = true;
		StopSound();
		m_pESuction->Stop();
	}
	if (m_tutorialDraw&&m_tutorial&&state.Gamepad.wButtons&XINPUT_GAMEPAD_B&&stroke.Flags == 0x0001 && !m_bShop)
	{
		m_tutorialDraw = false;
		StopSound();
		m_pESuction->Stop();

	}

	//---正規化(長さを1にする)
	float length = sqrt(m_move.x * m_move.x + m_move.z * m_move.z);
	if (length > 0)
	{
		m_move.x /= length;
		m_move.z /= length;
	}

	//---プレイヤーの回転角度を計算
	float rotationAngle = atan2(-m_move.x, -m_move.z);

	//---プレイヤーの回転行列を更新
	m_directRad = rotationAngle;
	m_directAngle = rotationAngle * PI;  // ラジアン角から度数に変換

	// プレイヤー強化カスタム効果反映
	// ブーツで速度強化
	if (m_nCustom[BOOTS] == 1)
	{
		m_move.x *= BOOTS_SPEED;
		m_move.z *= BOOTS_SPEED;
	}

	//---プレイヤーの移動
	if ((IsKeyPress('W') || IsKeyPress('A') || IsKeyPress('S') || IsKeyPress('D'))
		&& state.dwPacketNumber == 3452816845)
	{
		//---ダッシュ 移動 + RShift
		if (IsKeyPress(VK_RSHIFT))
		{
			if (Speed > 0.15f)	// アイテム使用していたら
			{
				// 早くなった速度に合わせたダッシュ
				MoveModel(m_move.x * (Speed + MOVE_DASH2), m_move.z * (Speed + MOVE_DASH2));
			}
			else
			{
				MoveModel(m_move.x * MOVE_DASH, m_move.z * MOVE_DASH);
			}
			if (!m_pEffect->IsPlay() && IsMove) { m_pEffect->Play(); }
			m_pESuction->Stop();
			CPlayer::Footsteps(state);// SEを再生
		}

		//---通常移動

		else { MoveModel(m_move.x * Speed, m_move.z * Speed); }
	}
	if (state.dwPacketNumber != 3452816845 &&
		state.Gamepad.sThumbLY != 0 || state.Gamepad.sThumbLX != 0)
	{
		//---ダッシュ 移動 + RShift
		if (state.Gamepad.bLeftTrigger)
		{
			if (Speed > 0.15f)	// アイテム使用していたら
			{
				// 早くなった速度に合わせたダッシュ
				MoveModel(m_move.x * (Speed + MOVE_DASH2), m_move.z * (Speed + MOVE_DASH2));
			}
			else
			{
				MoveModel(m_move.x * MOVE_DASH, m_move.z * MOVE_DASH);
			}
			if (!m_pEffect->IsPlay() && IsMove) { m_pEffect->Play(); }
			m_pESuction->Stop();
			CPlayer::Footsteps(state);// SEを再生
		}

		//---通常移動

		else { MoveModel(m_move.x * Speed, m_move.z * Speed); }
	}
	if (IsKeyTrigger(VK_RSHIFT) || state.Gamepad.bLeftTrigger) { IsMove = true; }
	if (IsKeyRelease(VK_RSHIFT) ||
		state.dwPacketNumber != 3452816845&&state.Gamepad.bLeftTrigger==0) { IsMove = false; }
	m_pEffect->Update();
	m_pEffect->SetPos(m_pos);

	if (IsKeyRelease(VK_RSHIFT) || 
		state.dwPacketNumber != 3452816845 && state.Gamepad.bLeftTrigger == 0) { m_pSoundMng->StopSound(CSoundMng::PlayerSE::ranGrass); }

	//---ラジアン角変換
	m_horizon = m_angleHorizon / PI;
	m_vertical = m_angleVertical / PI;
	m_directRad = m_directAngle / PI;

	//---カメラ操作計算
	m_camPos.x = m_radius * sin((float)m_vertical) * cos((float)m_horizon);
	//m_camPos.y = m_radius * cos((float)m_vertical);
	m_camPos.z = m_radius * sin((float)m_vertical) * sin((float)m_horizon);

	//---キー入力 カメラ回転
	if (IsKeyPress(VK_DOWN) || state.Gamepad.sThumbRY > 0 &&
		state.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
		state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) {
		m_camPos.y -= CAMERA_MOVE_SPEED;
	}
	if (IsKeyPress(VK_UP) || state.Gamepad.sThumbRY < 0 &&
		state.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
		state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) {
		m_camPos.y += CAMERA_MOVE_SPEED;
	}
	if (IsKeyPress(VK_RIGHT)) { m_angleHorizon -= CAMERA_ANGLE_MOVE; }
	if (state.Gamepad.sThumbRX > 0 &&
		state.Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
		state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) {
		m_angleHorizon -= CAMERA_ANGLE_MOVE;
	}
	if (IsKeyPress(VK_LEFT)) { m_angleHorizon += CAMERA_ANGLE_MOVE; }
	if (state.Gamepad.sThumbRX < 0 &&
		state.Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
		state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) {
		m_angleHorizon += CAMERA_ANGLE_MOVE;
	}


	//---縦ラジアン角度制御
	if (m_vertical > MAX_VERTICAL) { m_vertical = MAX_VERTICAL; }
	if (m_vertical < MIN_VERTICAL) { m_vertical = MIN_VERTICAL; }

	//---縦角度制御
	if (m_angleVertical > MAX_ANGLE_VERTICAL) { m_angleVertical = MAX_ANGLE_VERTICAL; }
	if (m_angleVertical < MIN_ANGLE_VERTICAL) { m_angleVertical = MIN_ANGLE_VERTICAL; }

	//---カメラ位置制御縦方向
	if (m_camPos.y > MAX_CAMERA_POS_Y) { m_camPos.y = MAX_CAMERA_POS_Y; }
	if (m_camPos.y < MIN_CAMERA_POS_Y) { m_camPos.y = MIN_CAMERA_POS_Y; }

	//---キー入力 ズーム
	if (IsKeyPress(VK_LSHIFT) || state.Gamepad.wButtons&XINPUT_GAMEPAD_RIGHT_THUMB&&
		state.Gamepad.sThumbRY > 0 &&
		state.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
		state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) {
		m_radius += CAMERA_MOVE_SPEED;
	}
	if (IsKeyPress(VK_LCONTROL) || state.Gamepad.wButtons&XINPUT_GAMEPAD_RIGHT_THUMB&&
		state.Gamepad.sThumbRY < 0 &&
		state.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
		state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) {
		m_radius -= CAMERA_MOVE_SPEED;
	}

	//---ズーム距離制御
	if (m_radius > CAMERA_FAR) { m_radius = CAMERA_FAR; }
	if (m_radius < CAMERA_NEAR) { m_radius = CAMERA_NEAR; }

	////---時間表示
	//m_nTime++;
	//if (!(m_nTime % 6))
	//{
	//	m_fTimeLimit -= 0.1f;
	//}
	//if (m_fTimeLimit < 0.0f) m_fTimeLimit = 0.0f;
	//sprintf(str, "money:%d, time:%.1f", m_nMoney, m_fTimeLimit);
	//SetWindowText(GetActiveWindow(), str);

	//---重力
	if (!m_randSlope) {	// 坂に乗ってないときは重力有効
		m_gravity -= 0.001f;
		if (m_pos.y <= m_randHeight)
		{
			m_pos.y = m_randHeight;
			m_gravity = 0.0f;
		}
		else
		{
			m_pos.y -= PLAYER_GRAVITY;
		}
	}
	if (Pmove == false && Pvaccum == false)
	{
		m_pModel->Play(anime[0], true, 1.0f);
	}
	if (Pmove == true && Pvaccum == false)
	{
		m_pModel->Play(anime[1], true, 1.0f);
	}
	if (Pmove == false && Pvaccum == true)
	{
		m_pModel->Play(anime[2], true, 1.0f);
	}
	if (Pmove == true && Pvaccum == true)
	{
		m_pModel->Play(anime[3], true, 1.0f);
	}
	m_pModel->Step(tick);

	m_pDrill->Update(tick);
	m_pSaw->Update(tick);
	m_pHammer->Update(tick);

	m_pDrill->SetPlayerPos(m_pos);
	m_pSaw->SetPlayerPos(m_pos);
	m_pHammer->SetPlayerPos(m_pos);
}

void CPlayer::Draw()
{
	DirectX::XMFLOAT4X4 mat[3];

	mat[0] = GetWorldMatrix();
	mat[1] = GetViewMatrix();
	mat[2] = GetProjectionMatrix();

	Geometory::SetWorld(mat[0]);
	Geometory::SetView(mat[1]);
	Geometory::SetProjection(mat[2]);

	RenderTarget* pRTV = GetDefaultRTV();
	DepthStencil* pDSV = GetDefaultDSV();
	SetRenderTargets(1, &pRTV, pDSV);

	m_pVS->WriteBuffer(0, mat);
	//m_pModel->Draw();
	ShaderList::SetWVP(mat);
	m_pModel->Draw(nullptr, [this](int index)
	{
		const Model::Mesh* pMesh = m_pModel->GetMesh(index);
		const Model::Material* pMaterial = m_pModel->GetMaterial(pMesh->materialID);
		ShaderList::SetMaterial(*pMaterial);

		DirectX::XMFLOAT4X4 bones[500];
		for (int i = 0; i < pMesh->bones.size() && i < 500; ++i)
		{
			// この計算はゲームつくろー「スキンメッシュの仕組み」が参考になる
			DirectX::XMStoreFloat4x4(&bones[i], DirectX::XMMatrixTranspose(
				pMesh->bones[i].invOffset *
				m_pModel->GetBone(pMesh->bones[i].index)
			));
		}
		ShaderList::SetBones(bones);
	});

#ifdef _DEBUG
	//m_pModel->DrawBone();
#endif

//プレイヤー影
	//影の描画
	DirectX::XMMATRIX mat1 = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y + 0.01f, m_pos.z);//移動
	DirectX::XMMATRIX mat2 = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(90.0f));//回転
	DirectX::XMMATRIX mat3 = mat2 * mat1;


	DirectX::XMFLOAT4X4 world;

	DirectX::XMStoreFloat4x4(&world, DirectX::XMMatrixTranspose(mat3));
	Sprite::SetWorld(world);
	Sprite::SetView(GetViewMatrix());
	Sprite::SetProjection(GetProjectionMatrix());
	//Sprite::SetColor(DirectX::XMFLOAT4(0.f, 0.8f, 0.8f, 1.0f));
	Sprite::SetSize(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetTexture(m_pShadowTex);
	Sprite::Draw();


	DirectX::XMFLOAT4X4 inv;//逆配列(inverse)の格納先
	inv = GetViewMatrix();

	//カメラの行列はGPUに渡す際に転置されているため、逆行列のために一度先に渡す。
	DirectX::XMMATRIX matInv = DirectX::XMLoadFloat4x4(&inv);
	matInv = DirectX::XMMatrixTranspose(matInv);

	//移動成分は逆行列で打ち消す必要がないので、0を指定して移動を無視する。
	DirectX::XMStoreFloat4x4(&inv, matInv);
	inv._41 = inv._42 = inv._43 = 0.0f;

	matInv = DirectX::XMLoadFloat4x4(&inv);
	matInv = DirectX::XMMatrixInverse(nullptr, matInv);

	DirectX::XMFLOAT4X4 matBill;
	DirectX::XMStoreFloat4x4(&matBill, matInv);
	m_pEffect->SetBillboardMatrix(matBill);
	m_pEffect->Draw(
		GetViewMatrix(),
		GetProjectionMatrix());
	m_pEffect->Draw(GetViewMatrix(), GetProjectionMatrix());
	XInputGetState(0, &state);
	if (IsKeyPress(VK_SPACE) || state.Gamepad.bLeftTrigger) {
		m_pESuction->Draw();
	}

	m_pEStun->Draw();

	if (*m_pshop->GetDrill())  //カスタム
	{
		m_pDrill->Draw(mat, m_pVS);
	}
	if (*m_pshop->GetSaw())  //カスタム
	{
		m_pSaw->Draw(mat, m_pVS);
	}

	if (*m_pshop->GetHammer())  //カスタム
	{
		m_pHammer->Draw(mat, m_pVS);
	}

}

//=====プレイヤーの移動=====
void CPlayer::MoveModel(float deltaX, float deltaZ)
{
	//---プレイヤー移動計算
	m_pos.x += deltaX;
	m_pos.z += deltaZ;
}



DirectX::XMFLOAT3 CPlayer::GetPos()
{
	return m_pos;
}

DirectX::XMFLOAT3 CPlayer::GetMove()
{
	return m_move;
}

DirectX::XMFLOAT3 CPlayer::GetCameraPos()
{
	DirectX::XMFLOAT3 camera;
	camera.x = m_pos.x + m_camPos.x;
	camera.y = m_pos.y + m_camPos.y;
	camera.z = m_pos.z + m_camPos.z;
	return camera;
}

DirectX::XMFLOAT3 CPlayer::GetOldPos()
{
	return m_oldPos;
}

DirectX::XMFLOAT3 CPlayer::GetScale()
{
	return m_scale;
}

//=====ワールド情報受け渡し=====
DirectX::XMFLOAT4X4 CPlayer::GetWorldMatrix()
{
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMFLOAT3 centerOfRotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);	//原点
	//---ワールド行列 Player Transform
	DirectX::XMMATRIX worldTrans = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
	DirectX::XMMATRIX Rx = DirectX::XMMatrixRotationX(0.0f);
	DirectX::XMMATRIX Ry = DirectX::XMMatrixRotationY(0.0f);
	DirectX::XMMATRIX Rz = DirectX::XMMatrixRotationZ(0.0f);
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);

	//---TransformとRotationを統合
	DirectX::XMMATRIX worldMatrix = S * Rx * Ry * Rz * worldTrans;

	//---中心点の変換
	DirectX::XMMATRIX centerTranslationMatrix =
		DirectX::XMMatrixTranslation(-centerOfRotation.x, -centerOfRotation.y, -centerOfRotation.z);
	DirectX::XMMATRIX centerRotationMatrix = DirectX::XMMatrixRotationY(m_directRad);  // 同じ回転を適用
	DirectX::XMMATRIX centerWorldMatrix = centerRotationMatrix * centerTranslationMatrix;

	//---中心点を中心にモデルを回転
	worldMatrix = centerWorldMatrix * worldMatrix;

	worldMatrix = DirectX::XMMatrixTranspose(worldMatrix);
	DirectX::XMStoreFloat4x4(&mat, worldMatrix);

	return mat;
}

//=====ビュー情報受け渡し=====
DirectX::XMFLOAT4X4 CPlayer::GetViewMatrix()
{
	//---格納場所準備
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMMATRIX view;
	//---要素準備
	DirectX::XMVECTOR eye = DirectX::XMVectorSet
	(m_pos.x + m_camPos.x, m_pos.y + m_camPos.y, m_pos.z + m_camPos.z, 0.0f);
	DirectX::XMVECTOR focus = DirectX::XMVectorSet
	(m_look.x + m_pos.x, m_look.y + m_pos.y, m_look.z + m_pos.z, 0.0f);
	DirectX::XMVECTOR up = DirectX::XMVectorSet(m_up.x, m_up.y, m_up.z, 0.0f);
	//---格納
	view = DirectX::XMMatrixLookAtLH(eye, focus, up);
	//---転置
	view = DirectX::XMMatrixTranspose(view);
	DirectX::XMStoreFloat4x4(&mat, view);

	return mat;
}

//=====プロジェクション情報受け渡し=====
DirectX::XMFLOAT4X4 CPlayer::GetProjectionMatrix()
{
	//---格納場所準備
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMMATRIX proj;
	//---格納
	proj = DirectX::XMMatrixPerspectiveFovLH(m_fovy, m_aspect, m_near, m_far);
	//---転置
	proj = DirectX::XMMatrixTranspose(proj);
	DirectX::XMStoreFloat4x4(&mat, proj);

	return mat;
}

DirectX::XMFLOAT4X4 CPlayer::GetNViewMatrix()
{
	//---格納場所準備
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMMATRIX view;
	//---要素準備
	DirectX::XMVECTOR eye = DirectX::XMVectorSet
	(m_pos.x + m_camPos.x, m_pos.y + m_camPos.y, m_pos.z + m_camPos.z, 0.0f);
	DirectX::XMVECTOR focus = DirectX::XMVectorSet
	(m_look.x + m_pos.x, m_look.y + m_pos.y, m_look.z + m_pos.z, 0.0f);
	DirectX::XMVECTOR up = DirectX::XMVectorSet(m_up.x, m_up.y, m_up.z, 0.0f);
	//---格納
	view = DirectX::XMMatrixLookAtLH(eye, focus, up);

	DirectX::XMStoreFloat4x4(&mat, view);

	return mat;
}

DirectX::XMFLOAT4X4 CPlayer::GetNProjectionMatrix()
{
	//---格納場所準備
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMMATRIX proj;
	//---格納
	proj = DirectX::XMMatrixPerspectiveFovLH(m_fovy, m_aspect, m_near, m_far);

	DirectX::XMStoreFloat4x4(&mat, proj);

	return mat;
}

//=====前方向ベクトル受け渡し=====
DirectX::XMFLOAT3 CPlayer::GetForwardVector()
{
	DirectX::XMFLOAT3 forwardVector;

	// カメラの位置 (eye)
	DirectX::XMFLOAT3 eye = { m_pos.x + m_camPos.x, m_pos.y + m_camPos.y, m_pos.z + m_camPos.z };

	// カメラの注視点 (focus)
	DirectX::XMFLOAT3 focus = { m_look.x + m_pos.x, m_look.y + m_pos.y, m_look.z + m_pos.z };

	// 注視点からカメラ位置へのベクトルを計算
	DirectX::XMFLOAT3 lookDirection;
	lookDirection.x = focus.x - eye.x;
	lookDirection.y = focus.y - eye.y;
	lookDirection.z = focus.z - eye.z;

	// このベクトルを正規化 (長さを1にする) して前方ベクトルを得る
	float length = sqrt(lookDirection.x * lookDirection.x + lookDirection.y * lookDirection.y + lookDirection.z * lookDirection.z);
	forwardVector.x = lookDirection.x / length;
	forwardVector.y = lookDirection.y / length;
	forwardVector.z = lookDirection.z / length;

	return forwardVector;
}

//=====横方向ベクトル受け渡し=====
DirectX::XMFLOAT3 CPlayer::GetRightVector()
{
	DirectX::XMFLOAT3 rightVector;

	// カメラの前方ベクトルを取得
	DirectX::XMFLOAT3 forwardVector = GetForwardVector();

	// カメラの上方向 (up)
	DirectX::XMFLOAT3 up = { m_up.x, m_up.y, m_up.z };

	// カメラの右方向ベクトルを計算 (前方ベクトルと上方向ベクトルの外積)
	rightVector.x = forwardVector.y * up.z - forwardVector.z * up.y;
	rightVector.y = forwardVector.z * up.x - forwardVector.x * up.z;
	rightVector.z = forwardVector.x * up.y - forwardVector.y * up.x;

	// ベクトルを正規化
	float length = sqrt(rightVector.x * rightVector.x + rightVector.y * rightVector.y + rightVector.z * rightVector.z);
	rightVector.x /= length;
	rightVector.y /= length;
	rightVector.z /= length;

	return rightVector;
}

DirectX::XMFLOAT3  CPlayer::GetUpRightVector()
{
	DirectX::XMFLOAT3 UprightVector;

	// カメラの前方ベクトルを取得
	DirectX::XMFLOAT3 forwardVector = GetForwardVector();
	DirectX::XMVECTOR vforwardVector = DirectX::XMLoadFloat3(&forwardVector);
	DirectX::XMMATRIX matRotSide = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(45.0f));
	DirectX::XMVECTOR vUpright = DirectX::XMVector3TransformCoord(vforwardVector, matRotSide);
	DirectX::XMVector3Normalize(vUpright);
	DirectX::XMStoreFloat3(&UprightVector, vUpright);
	return UprightVector;
}
DirectX::XMFLOAT3 CPlayer::GetUpLeftVector()
{
	DirectX::XMFLOAT3 UpLeftVector;
	// カメラの前方ベクトルを取得
	DirectX::XMFLOAT3 forwardVector = GetForwardVector();
	DirectX::XMVECTOR vforwardVector = DirectX::XMLoadFloat3(&forwardVector);
	DirectX::XMMATRIX matRotSide = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(-45.0f));
	DirectX::XMVECTOR vUpLeft = DirectX::XMVector3TransformCoord(vforwardVector, matRotSide);
	DirectX::XMVector3Normalize(vUpLeft);
	DirectX::XMStoreFloat3(&UpLeftVector, vUpLeft);
	return UpLeftVector;
}

void CPlayer::Footsteps(XINPUT_STATE state)
{
	XInputGetState(0, &state);
	switch (m_randKind)
	{
	case CAreaGround::kind::grass:
		if (IsKeyPress('W') || IsKeyPress('A') || IsKeyPress('S') || IsKeyPress('D') ||
			state.Gamepad.sThumbLY != 0 || state.Gamepad.sThumbLX != 0) {
			if (m_pSoundMng->CheckSoundEnd(CSoundMng::PlayerSE::walkGrass)) {	// 音がなってなければ(重複して鳴らさない)
				m_pSoundMng->playSound(CSoundMng::PlayerSE::walkGrass);
			}
			if (IsKeyPress(VK_RSHIFT) || state.Gamepad.bLeftTrigger)
			{
				if (m_pSoundMng->CheckSoundEnd(CSoundMng::PlayerSE::ranGrass))
					m_pSoundMng->playSound(CSoundMng::PlayerSE::ranGrass);
				m_pSoundMng->StopSound(CSoundMng::PlayerSE::walkGrass);
				StopSound();//吸い込み音停止
			}
		}
		if (IsKeyRelease(VK_RSHIFT) || state.dwPacketNumber != 3452816845 && state.Gamepad.bLeftTrigger == 0) {
			m_pSoundMng->StopSound(CSoundMng::PlayerSE::ranGrass);
		}
		if (IsKeyRelease('W') || IsKeyRelease('A') || IsKeyRelease('S') || IsKeyRelease('D')
			|| state.dwPacketNumber != 3452816845&&state.Gamepad.sThumbLY == 0
			|| state.dwPacketNumber != 3452816845&&state.Gamepad.sThumbLX == 0)
		{
			m_pSoundMng->StopSound(CSoundMng::PlayerSE::walkGrass);
		}
		break;
	case CAreaGround::kind::beach:
		if (IsKeyPress('W') || IsKeyPress('A') || IsKeyPress('S') || IsKeyPress('D')
			|| state.Gamepad.sThumbLY != 0 || state.Gamepad.sThumbLX != 0)
		{
			if (m_pSoundMng->CheckSoundEnd(CSoundMng::PlayerSE::walkGround)) {	// 音がなってなければ(重複して鳴らさない)
				m_pSoundMng->playSound(CSoundMng::PlayerSE::walkGround);
			}
			if (IsKeyPress(VK_RSHIFT) || state.Gamepad.bLeftTrigger)
			{
				if (m_pSoundMng->CheckSoundEnd(CSoundMng::PlayerSE::ranGround))
					m_pSoundMng->playSound(CSoundMng::PlayerSE::ranGround);
				m_pSoundMng->StopSound(CSoundMng::PlayerSE::walkGround);
				StopSound();//吸い込み音停止
			}
		}
		if (IsKeyRelease(VK_RSHIFT) || state.dwPacketNumber != 3452816845 && state.Gamepad.bLeftTrigger == 0) {
			m_pSoundMng->StopSound(CSoundMng::PlayerSE::ranGround);
		}
		if (IsKeyRelease('W') || IsKeyRelease('A') || IsKeyRelease('S') || IsKeyRelease('D')
			|| state.dwPacketNumber != 3452816845&& state.Gamepad.sThumbLY == 0 
			|| state.dwPacketNumber != 3452816845&& state.Gamepad.sThumbLX == 0)
		{
			m_pSoundMng->StopSound(CSoundMng::PlayerSE::walkGround);
		}
		break;
	case CAreaGround::kind::cream:
		if (IsKeyPress('W') || IsKeyPress('A') || IsKeyPress('S') || IsKeyPress('D')
			|| state.Gamepad.sThumbLY != 0 || state.Gamepad.sThumbLX != 0)
		{
			if (m_pSoundMng->CheckSoundEnd(CSoundMng::PlayerSE::walkCream)) {	// 音がなってなければ(重複して鳴らさない)
				m_pSoundMng->playSound(CSoundMng::PlayerSE::walkCream);
			}
			if (IsKeyPress(VK_RSHIFT) || state.Gamepad.bLeftTrigger)
			{
				if (m_pSoundMng->CheckSoundEnd(CSoundMng::PlayerSE::runCream))
					m_pSoundMng->playSound(CSoundMng::PlayerSE::runCream);
				m_pSoundMng->StopSound(CSoundMng::PlayerSE::walkCream);
				StopSound();//吸い込み音停止
			}
		}
		if (IsKeyRelease(VK_RSHIFT) || state.dwPacketNumber != 3452816845 && state.Gamepad.bLeftTrigger == 0) {
			m_pSoundMng->StopSound(CSoundMng::PlayerSE::runCream);
		}
		if (IsKeyRelease('W') || IsKeyRelease('A') || IsKeyRelease('S') || IsKeyRelease('D')
			|| state.dwPacketNumber != 3452816845 && state.Gamepad.sThumbLY == 0
			|| state.dwPacketNumber != 3452816845 && state.Gamepad.sThumbLX == 0)
		{
			m_pSoundMng->StopSound(CSoundMng::PlayerSE::walkCream);
		}
		break;
	case CAreaGround::kind::spong:
		if (IsKeyPress('W') || IsKeyPress('A') || IsKeyPress('S') || IsKeyPress('D')
			|| state.Gamepad.sThumbLY != 0 || state.Gamepad.sThumbLX != 0)
		{
			if (m_pSoundMng->CheckSoundEnd(CSoundMng::PlayerSE::walkSponge)) {	// 音がなってなければ(重複して鳴らさない)
				m_pSoundMng->playSound(CSoundMng::PlayerSE::walkSponge);
			}
			if (IsKeyPress(VK_RSHIFT) || state.Gamepad.bLeftTrigger)
			{
				if (m_pSoundMng->CheckSoundEnd(CSoundMng::PlayerSE::runSponge))
					m_pSoundMng->playSound(CSoundMng::PlayerSE::runSponge);
				m_pSoundMng->StopSound(CSoundMng::PlayerSE::walkSponge);
				StopSound();//吸い込み音停止
			}
		}
		if (IsKeyRelease(VK_RSHIFT) || state.dwPacketNumber != 3452816845 && state.Gamepad.bLeftTrigger == 0) {
			m_pSoundMng->StopSound(CSoundMng::PlayerSE::runSponge);
		}
		if (IsKeyRelease('W') || IsKeyRelease('A') || IsKeyRelease('S') || IsKeyRelease('D')
			|| state.dwPacketNumber != 3452816845 && state.Gamepad.sThumbLY == 0
			|| state.dwPacketNumber != 3452816845 && state.Gamepad.sThumbLX == 0)
		{
			m_pSoundMng->StopSound(CSoundMng::PlayerSE::walkSponge);
		}
		break;
	default:
		break;
	}

}


void CPlayer::SetObjectMng(CObjectMng * pCObjectMng)
{
	m_pObjectMng = pCObjectMng;
}

void CPlayer::SetPos(DirectX::XMFLOAT3 pos)
{
	m_pos = pos;
}

void CPlayer::SetMoney(int money)
{
	m_nMoney += money;
}

void CPlayer::SetPosX(float posx)
{
	m_pos.x = posx;
}

void CPlayer::SetPosY(float posy)
{
	m_pos.y = posy;
}

void CPlayer::SetPosZ(float posz)
{
	m_pos.z = posz;
}

void CPlayer::SetCameraPosX(float camPosX)
{
	m_camPos.x = camPosX;
}

void CPlayer::SetCameraPosY(float camPosY)
{
	m_camPos.y = camPosY;
}

void CPlayer::SetCameraPosZ(float camPosZ)
{
	m_camPos.z = camPosZ;
}

void CPlayer::SetCamRadius(float radius)
{
	m_radius = radius;
}

void CPlayer::SetHorizon(float horizon)
{
	m_angleHorizon = horizon;
}

void CPlayer::SetTrade(bool trade)
{
	m_trade = trade;
}

void CPlayer::SetShop(bool Shop)
{
	m_bShop = Shop;
}

void CPlayer::SetRandKind(int crntGround)
{
	m_randKind = crntGround;
}

void CPlayer::SetRandHeight(int crntHeight)
{
	m_randHeight = crntHeight;
}

void CPlayer::SetRandSlope(bool slope)
{
	m_randSlope = slope;
}

void CPlayer::SetRandBiscuit(bool is)
{
	m_randBiscuit = is;
}

void CPlayer::SetSoundMng(CSoundMng * soundMng)	// サウンドの実体受け取り
{
	m_pSoundMng = soundMng;
}

void CPlayer::SetItem(int drink, int nozzle)
{
	m_nDrink = drink;
	m_nNozzle = nozzle;
}

void CPlayer::SetUI(CUI * ui)
{
	m_pUI_Money = ui;
}

void CPlayer::SetTutorial(bool is, int kind)
{
	m_tutorial = is;
	m_tutorialKind = (CTutorialSignboard::textureKind)kind;
}

void CPlayer::SetSuction(bool suction)
{
	m_suction = suction;
}

void CPlayer::SetTutorialDraw(bool draw)
{
	m_tutorialDraw = draw;
}

int CPlayer::GetTutorialNum()
{

	return m_tutorialKind;
}

bool CPlayer::IsTutorial()
{
	return m_tutorial;
}

void CPlayer::StopSound()
{
	m_pSoundMng->StopSound(CSoundMng::SuctionSE::wind);
	m_pSoundMng->StopSound(CSoundMng::SuctionSE::wind2);
	m_pSoundMng->StopSound(CSoundMng::SuctionSE::wind3);
}

void CPlayer::LoadEffect()
{
	m_pEffect = new Effect();
	m_pRunSmoke = new RunSmoke();
	m_pEffect->AddEmitter(m_pRunSmoke);//土煙エフェクト

	m_pESuction = new ESuction();
	m_pESuction->SetPlayer(this);
	m_pEStun = new EStun();
	m_pEStun->SetPlayer(this);

	m_pSuction->SetESuction(m_pESuction);
}


bool CPlayer::GetTrade()
{
	return m_trade;
}

bool CPlayer::GetTutorial()
{
	return m_tutorialDraw;
}


bool CPlayer::GetShop()	// 購入画面に移るフラグのゲット
{
	return m_bShop;
}

int * CPlayer::GetMoney()
{
	return &m_nMoney;
}

int * CPlayer::GetCustom()
{
	return m_nCustom;
}

float CPlayer::GetRadius()
{
	return m_radius;
}

Suction * CPlayer::GetSuction()
{
	return m_pSuction;
}

int CPlayer::GetRandKind()
{
	return m_randKind;
}

int CPlayer::GetRandHeight()
{
	return m_randHeight;
}

bool CPlayer::GetRandSlope()
{
	return m_randSlope;
}

bool CPlayer::GetRandBiscuit()
{
	return m_randBiscuit;
}

float CPlayer::GetRad()
{
	return  m_directRad;
}

void CPlayer::SetDrill(bool* Drill)
{
	m_bDrill = Drill;
}

void CPlayer::SetSaw(bool* Saw)
{
	m_bSaw = Saw;
}

void CPlayer::SetHammer(bool* Hammer)
{
	m_bHammer = Hammer;
}

void CPlayer::SetShopCustom(CShop * shop)
{
	m_pshop = shop;
}