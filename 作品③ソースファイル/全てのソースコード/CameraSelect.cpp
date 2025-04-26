//=================================================================
//
//	CameraSelect.h
//	惑星セレクトシーンのカメラ
//
//=================================================================

// ========== インクルード部 ==========
#include "CameraSelect.h"
#include "Input.h"
#include "XController.h"

// ========== マクロ定義 ==========
#define CAMERA_MOVE_SPEED (0.2f)		// カメラ移動速度
#define PI (180.0f / 3.14f)				// ラジアン変換用
#define MAX_FRAME (70)					// カメラ移動計算最大フレーム
#define FACTOR_FRAME (60)				// 計算用フレーム
#define START_HORIZON (270.0f)			// 初期平行角度
#define START_VERTICAL (50.0f)			// 初期縦角度
#define START_RADIUS (3.8f)				// 惑星からカメラまでの距離初期値
#define END_RADIUS (10.0f)				// カメラワーク用
#define START_LOOK_RADIUS (1.6f)		// 惑星から焦点までの距離初期値
#define REVISION_SPEED (4.0f)			// スピード調整用
#define ROTATION_SPEED (3.0f)			// 回転速度
#define PLANET_ROTATION (360.0f / CSceneMng::MAX_STAGE)	// 回転する角度

//=====コンストラクタ=====
CCameraSelect::CCameraSelect()
	: m_radius(START_RADIUS)				// プレイヤーとの距離
	, m_lookRadius(START_LOOK_RADIUS)
	, m_horizon(0.0f)						// 平行方向ラジアン角
	, m_vertical(0.0f)						// 縦方向ラジアン角
	, m_angleHorizon(START_HORIZON)			// 平行角度
	, m_angleVertical(START_VERTICAL)		// 縦角度
	, m_factor(0.0f)
	, m_value(0.0f)
	, m_cnt(0.0f)
	, m_frame(0)
	, m_up(0.0f, 1.0f, 0.0f)
	, m_lookPlanet(0.0f, 0.0f, 0.0f)
	, m_startPlanet(0.0f, 0.0f, 0.0f)
	, m_endPlanet(0.0f, 0.0f, 0.0f)
	, m_oldSelectPlanet(CSceneMng::SCENE_STAGE1)
	, m_moveLeft(false)
	, m_moveRight(false)
	, m_flg(true)
{
	m_pos = DirectX::XMFLOAT3(1.0f, 1.0f, -2.0f);
	m_look = DirectX::XMFLOAT3(1.0f, 1.0f, 0.0f);
}

//=====デストラクタ=====
CCameraSelect::~CCameraSelect()
{
}

void CCameraSelect::Init(int num)
{
	m_oldSelectPlanet = num;
	m_angleHorizon = START_HORIZON + PLANET_ROTATION * num;
	m_angleVertical = START_VERTICAL;
	m_lookPlanet = m_pPlanet[num]->GetPos();
	
	m_moveLeft = false;
	m_moveRight = false;
}

//=====更新処理=====
void CCameraSelect::Update()
{
	//---焦点位置角度計算
	float lookHorizon = (m_angleHorizon + 30.0f) / PI;
	//---カメラ移動処理
	MoveCamera();

	//---ラジアン角変換
	m_horizon = m_angleHorizon / PI;
	m_vertical = m_angleVertical / PI;

	//---カメラ操作計算
	m_pos.x = m_radius * sin((float)m_vertical) * cos((float)m_horizon);
	m_pos.z = m_radius * sin((float)m_vertical) * sin((float)m_horizon);
	//---焦点計算
	m_look.x = m_lookRadius * sin((float)m_vertical) * cos((float)lookHorizon);
	m_look.z = m_lookRadius * sin((float)m_vertical) * sin((float)lookHorizon);
}

//=====ビュー情報受け渡し=====
DirectX::XMFLOAT4X4 CCameraSelect::GetViewMatrix()
{
	//---格納場所準備
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMMATRIX view;
	//---要素準備
	// カメラ位置 惑星座標 + 座標補正
	DirectX::XMVECTOR eye = DirectX::XMVectorSet
	(m_lookPlanet.x + m_pos.x, m_lookPlanet.y + m_pos.y, m_lookPlanet.z + m_pos.z, 0.0f);
	// 焦点 惑星座標 + 座標補正
	DirectX::XMVECTOR focus = DirectX::XMVectorSet
	(m_lookPlanet.x + m_look.x, m_lookPlanet.y + m_look.y, m_lookPlanet.z + m_look.z, 0.0f);
	// カメラの向き
	DirectX::XMVECTOR up = DirectX::XMVectorSet(m_up.x, m_up.y, m_up.z, 0.0f);
	//---格納
	view = DirectX::XMMatrixLookAtLH(eye, focus, up);
	//---転置
	view = DirectX::XMMatrixTranspose(view);
	DirectX::XMStoreFloat4x4(&mat, view);

	return mat;
}

//=====ステージ1ポインタ受け取り=====
void CCameraSelect::SetGreen(Planet* green)
{
	m_pPlanet[CSceneMng::SCENE_STAGE1] = green;
}

//=====ステージ2ポインタ受け取り=====
void CCameraSelect::SetMushroom(Planet* mushroom)
{
	m_pPlanet[CSceneMng::SCENE_STAGE2] = mushroom;
}

//=====ステージ3ポインタ受け取り=====
void CCameraSelect::SetWholeCake(Planet* wholecake)
{
	m_pPlanet[CSceneMng::SCENE_STAGE3] = wholecake;
}

//=====カメラ移動処理=====
void CCameraSelect::MoveCamera()
{
	//---変数宣言
	m_horizon = m_angleHorizon;		// 角度格納

	//---カメラ移動処理
	if (m_moveLeft || m_moveRight)
	{
		// 変数宣言
		float startRadius = START_RADIUS;
		float endRadius = END_RADIUS;
		float subRadius = 0.0f;

		// 速度計算用
		if (m_frame < MAX_FRAME) m_frame++;
		m_factor = static_cast<float>(m_frame) / static_cast<float>(FACTOR_FRAME);
		m_value = m_factor * m_factor * (3.0f - 2.0f * m_factor);

		// ベクトルの差分を計算
		DirectX::XMVECTOR startVec = DirectX::XMLoadFloat3(&m_startPlanet);
		DirectX::XMVECTOR endVec = DirectX::XMLoadFloat3(&m_endPlanet);
		DirectX::XMVECTOR direction = DirectX::XMVectorSubtract(endVec, startVec);
		direction = DirectX::XMVector3Normalize(direction); // 正規化

		// ズーム計算用
		if (m_flg)
			subRadius = endRadius - m_radius;
		else
			subRadius = m_radius - startRadius;

		// 速度に基づいて移動距離を計算
		float speed = CAMERA_MOVE_SPEED * m_value;
		DirectX::XMVECTOR velocity = DirectX::XMVectorScale(direction, speed);

		// 現在の位置を更新
		DirectX::XMVECTOR currentVec = DirectX::XMLoadFloat3(&m_lookPlanet);
		currentVec = DirectX::XMVectorAdd(currentVec, velocity);
		DirectX::XMStoreFloat3(&m_lookPlanet, currentVec);

		// ズームインアウト処理
		if (m_flg)
			m_radius += subRadius * (speed * REVISION_SPEED);
		else
			m_radius -= speed;

		if (m_radius >= END_RADIUS && m_flg)
		{
			m_flg = false;
			m_radius = 10.0f;
		}
		if (m_radius <= START_RADIUS && !m_flg)
			m_radius = START_RADIUS;

		// 左方向移動時
		if (m_moveLeft)
		{
			if (m_cnt <= PLANET_ROTATION)
			{
				m_cnt += ROTATION_SPEED * m_value;
				m_angleHorizon -= ROTATION_SPEED * m_value;
			}
		}
		// 右方向移動時
		if (m_moveRight)
		{
			if (m_cnt >= -PLANET_ROTATION)
			{
				m_cnt -= ROTATION_SPEED * m_value;
				m_angleHorizon += ROTATION_SPEED * m_value;
			}
		}

		// 到達判定用の距離の閾値
		const float arrivalThreshold = speed * 1.5f; // 十分に近いとみなす距離

		// 目的座標との距離を計算
		DirectX::XMVECTOR diffVec = DirectX::XMVectorSubtract(currentVec, endVec);
		float distanceSquared = DirectX::XMVectorGetX(DirectX::XMVector3LengthSq(diffVec));

		// 距離が閾値以下かどうかで判定
		if (distanceSquared <= arrivalThreshold * arrivalThreshold)
		{
			m_lookPlanet = m_endPlanet; // 目的座標に到達
			m_frame = 0;					// フレームリセット
			m_radius = START_RADIUS;	// カメラと惑星の距離リセット
			m_flg = true;				// フラグリセット
			m_cnt = 0.0f;					// 回転角度リセット

			// 移動フラグリセット
			if (m_moveLeft)	m_moveLeft = false;
			if (m_moveRight) m_moveRight = false;
		}
	}
}

// 左移動フラグをたて、必要情報を設定する
void CCameraSelect::SetMoveLeft(int select)
{
	m_moveLeft = true;
	m_startPlanet = m_pPlanet[m_oldSelectPlanet]->GetPos();	// 移動開始地点設定
	m_endPlanet = m_pPlanet[select]->GetPos();			// 移動先地点設定

	m_oldSelectPlanet = select;	// 移動先を次の移動開始地点に
}

// 右移動フラグを立て、必要情報を設定する
void CCameraSelect::SetMoveRight(int select)
{
	m_moveRight = true;
	m_startPlanet = m_pPlanet[m_oldSelectPlanet]->GetPos();
	m_endPlanet = m_pPlanet[select]->GetPos();

	m_oldSelectPlanet = select;	// 移動先を次の移動開始地点に
}

// カメラが移動中かどうかをかえす
bool CCameraSelect::GetMove()
{
	if (m_moveLeft || m_moveRight) {
		return true;
	}
	else {
		return false;
	}
}
