#include "Object.h"
#include <math.h>
#include "Player.h"
#include "Geometory.h"
#include "Input.h"

//=====マクロ定義=====
#define PI (3.14159)
#define GRAVITY (0.02f)
#define UP_GRAVITY (5.5f)	// ジャンプ時の重力減衰計算用
#define DOWN_GRAVITY (0.4f)	// 落下時の重力減衰計算用

float m_BoxMoveX;
float m_BoxMoveY;
float m_BoxMoveZ;

float m_SphereMoveX;
float m_SphereMoveY;
float m_SphereMoveZ;

const float STOP_SECONDS = 0.6f;		// オブジェクトの慣性を静止させるまでの秒数
const float SHAKE_SWING_WIDTH = 0.04f;	// 揺れの振れ幅
const float SHAKE_FREQUENCY = 10.0f;		// 揺れの頻度
const float SCALE_SMALLER = 0.95f;		// サイズを小さくする値
const float SUCTION_MOVEY = 0.07f;		// 吸い込まれるときに動くY値

const float DROP_SECONDS = 0.2f;			// ドロップ動作が完了するまでの秒数
const float DROP_VELOCITY = 3.5f;		// ドロップ動作の移動速度
const float DROP_GRAVITY = 7.6f;		// 1秒当たりの重力（ドロップ中）
const float DROP_JUMP_HEIGHT = 3.5f;	// ドロップ時どれだけ跳ねるか
const float DROP_JUMP_POWER = 12.0f;		// ドロップ時の1秒当たりのジャンプ量

const int	MELT_TIME = 30;				// ロウソクが溶ける時間
const float BISCUIT_BREAK_TIME = 1.5f;	// ビスケットに乗ると破壊される時間
const float TUTORIAL_DISTANCE = 2.0f;	// チュートリアル看板を作動させられる距離

float shakeTime;	// 揺れ

/**
*@brief	描画初期情報設定付きコンストラクタ
*@param [in] posX,posY,posZ				描画初期座標
*@param [in] scaleX,scaleY,scaleZ		描画初期スケール
*@param [in] rotateX,rotateY,rotateZ	描画初期アングル
*/
Object::Object(float posX, float posY, float posZ)
	: m_pos(posX, posY, posZ)
	, m_scale(1.0f, 1.0f, 1.0f)
	, m_rotate(0.0f, 0.0f, 0.0f)
	, m_oldPos(0.0f, 0.0f, 0.0f)
	, m_oldSize(0.0f, 0.0f, 0.0f)
	, m_oldScale(1.0f, 1.0f, 1.0f)
	, m_velocity(0)
	, m_gravity(0.0f)
	, m_moveDirection{ 0.0f,0.0f,0.0f,0.0f }
	, m_bSuction(false)
	, m_bGimmickSuction(false)
	, m_nKind(NONE)
	, m_bDelete(false)
	, m_nMoney(0)
	, m_mass(1.0f)
	, m_pModel(nullptr)
	, m_modelRatio(1.0)
	, m_pModelManager(nullptr)
	, m_bShake(false)
	, m_bMove(false)
	, m_draw(true)
	, m_bDrop(false)
	, dropTime(0.0f), dropJump(0.0f)
	, m_EfkDestory(false)
	, m_bDropJump(true)
	, m_nLevelDown(0)
	, m_nDefCnt(-1)
	, m_fOnTime(0.0f)
	, m_bTouch(false)
	, m_bOldTouch(false)
	, m_bGetMoney(false)
	, m_shakePos(0.0f, 0.0f, 0.0f)
	, m_bTutorial(false)
	, m_bTutorialTrigger(false)
	, m_randHeight(0.0f)
	, m_randSlope(false)
	, m_bGimmick(false)
	, m_bPlayGimmick(false)
	, m_amplitude(0.5f)
	, m_time(0.0f)
	, m_weight(1.0f)
	, m_suctionDis(0.0f)
	, m_pTrail(nullptr)
	, m_bTrailSet(false)
	, m_pTexture(nullptr)
	, m_nMaxRatio(0)
	, m_fRatio(1.0f)
	, m_fallTime(0.0f)
{
	m_gimmickOldPos = m_pos;
	m_pTrail = new TrailEffect(this);
	m_pTrail->AddLine(20);

	
	
		m_pTexture = new Texture();
	

	if (FAILED(m_pTexture->Create("Assets/Texture/custom.png"))) {
		MessageBox(NULL, "custom.png", "Error", MB_OK);
	}
}

Object::~Object()
{
	Uninit();
	if (m_pTrail)
	{
		delete m_pTrail;
		m_pTrail = nullptr;
	}
	SAFE_DELETE(m_pTexture);
}

void Object::Init()
{
	for (int i = 0; i < 3; ++i)
		DirectX::XMStoreFloat4x4(&m_WVP[i], DirectX::XMMatrixIdentity());
	//MakeBox();
	////MakeCylinder();
	////MakeSphere();
	//MakeVS();
	//MakePS();
	//MakeLineShader();
	//MakeLine();
	/*SetBoxMove();*/
}
void Object::Uninit()
{
	/*SAFE_DELETE_ARRAY(m_pLineVtx);*/
	//SAFE_DELETE(m_pLineShader[1]);
	//SAFE_DELETE(m_pLineShader[0]);
	//SAFE_DELETE(m_pPS);
	//SAFE_DELETE(m_pVS);
	/*SAFE_DELETE(m_pLines);*/
	//SAFE_DELETE(m_pSphere);
	//SAFE_DELETE(m_pCylinder);
	/*SAFE_DELETE(m_pBox);*/
}

void Object::Update(float tick)
{
	// オブジェクト過去座標
	m_oldPos = m_pos;
	if (m_oldSize.x == 0.0f &&
		m_oldSize.y == 0.0f &&
		m_oldSize.z == 0.0f)
	{
		m_oldSize = m_scale;
	}

	// ドロップアニメーション中なら
	if (m_bDrop)
	{
		m_gravity = DROP_JUMP_POWER - (dropTime * UP_GRAVITY);	// 重力計算

		m_fallTime = dropTime += 0.1f;		// ドロップ時間更新
		dropJump += DROP_JUMP_POWER * tick;	// 総ジャンプ量に加算
		// ジャンプの高さで判定
		if (dropJump <= DROP_JUMP_HEIGHT)
		{
			//m_pos.y += DROP_JUMP_POWER * tick;		// ジャンプを反映
			m_pos.y += m_gravity * tick;
		}
		else
		{
			if (m_pos.y <= m_randHeight + m_scale.y / 2.0f)
			{
				m_pos.y = m_randHeight + m_scale.y / 2.0f;
				m_bDrop = false;
				m_gravity = 0.0f;
			}
			else
			{
				m_bDrop = false;
				//m_pos.y -= DROP_GRAVITY * tick;
				m_pos.y += m_gravity * tick;
			}
		}
		// 現在の座標を計算用に変換
		DirectX::XMVECTOR currentPos = DirectX::XMLoadFloat3(&m_pos);
		// 方向と加速度に応じて移動								(移動方向ベクトル * 加速度 + 現在座標)
		DirectX::XMVECTOR newPos = DirectX::XMVectorMultiplyAdd(m_dropDirection, DirectX::XMVectorReplicate(DROP_VELOCITY * tick), currentPos);
		
		// 座標を更新
		DirectX::XMStoreFloat3(&m_pos, newPos);
		if (!m_bTrailSet) {
			m_pTrail->Init();
			m_bTrailSet = true;
		}
		m_pTrail->Update();
		return;
	}

	// 揺れフラグが立っていたら
	if (m_bShake)
	{
		shakeTime += tick;

		float offsetX = SHAKE_SWING_WIDTH * sin(SHAKE_FREQUENCY * shakeTime * rand());

		m_shakePos.x += offsetX;
	}
	else
	{
		m_shakePos.x = m_pos.x;
		shakeTime = 0.0f;
	}

	if (!m_bSuction)// 吸い込まれ中でないなら
	{
		// 指定した秒数で静止するような減速の実装
		m_velocity = m_velocity - m_lastVel * tick * (1 / STOP_SECONDS);

		// 元のサイズに戻す
		m_oldScale = { 1.0f, 1.0f, 1.0f };
		if (m_oldSize.x != m_scale.x &&
			m_oldSize.y != m_scale.y &&
			m_oldSize.z != m_scale.z)
		{
			m_scale = m_oldSize;
		}
	}
	else
	{
		m_bMove = true;	// 移動フラグを立てる
	}
	// 速さに経過時間を掛ける
	float speedFrame = m_velocity * tick;

	if (speedFrame > 0.35f) { speedFrame = 0.35f; }
	if (speedFrame < 0.0f)
	{
		m_velocity = m_lastVel = speedFrame = 0.0f;
		m_bMove = false;	// 停止したので移動フラグをおろす
	}
	// 現在の座標を計算用に変換
	DirectX::XMVECTOR currentPos = DirectX::XMLoadFloat3(&m_pos);
	// 方向と加速度に応じて移動								(移動方向ベクトル * 加速度 + 現在座標)
	DirectX::XMVECTOR newPos = DirectX::XMVectorMultiplyAdd(m_moveDirection, DirectX::XMVectorReplicate(speedFrame), currentPos);
	// 座標を更新
	DirectX::XMStoreFloat3(&m_pos, newPos);

	if (m_bSuction)	// 吸い込んでいたら
	{
		// 座標更新
		if (m_PlayerPosY + 0.5f > m_pos.y)	// オブジェクトがプレイヤーより下の位置か
		{
			m_pos.y += SUCTION_MOVEY;				// 段々上に吸い込まれる
		}
		else if (m_PlayerPosY + 0.5f < m_pos.y)		// オブジェクトがプレイヤーより上の位置か
		{
			m_pos.y -= SUCTION_MOVEY;				// 段々下に吸い込まれる
		}

		// 3Dモデルサイズを更新
		m_oldScale.x = m_oldScale.x * SCALE_SMALLER;
		m_oldScale.y = m_oldScale.y * SCALE_SMALLER;
		m_oldScale.z = m_oldScale.z * SCALE_SMALLER;

		// Boxサイズを更新
		m_scale.x = m_scale.x * SCALE_SMALLER;
		m_scale.y = m_scale.y * SCALE_SMALLER;
		m_scale.z = m_scale.z * SCALE_SMALLER;
	}

	//if (Kind::CANDLE == m_nKind && m_noldTime - m_nTime >= MELT_TIME)
	//{
	//	m_scale.y -= m_modelRatio;
	//	m_noldTime = m_nTime;
	//	m_nLevelDown++;
	//	if (m_nLevelDown == 2 && m_nLevel != 0)
	//	{
	//		m_nLevel -= 1;
	//		switch (m_nLevel)
	//		{
	//		case 2:
	//			m_nMoney = 250;
	//			break;
	//		case 1:
	//			m_nMoney = 50;
	//			break;
	//		case 0:
	//			m_nMoney = 0;
	//			break;
	//		}
	//	}

	//if (m_nKind == Kind::BISCUIT)
	//{
	//	m_nKind = Kind::BISCUIT;
	//}
	//--ビスケットの処理--
	if (m_bTouch && m_nKind == Kind::BISCUIT)	// プレイヤーと接触中であれば
	{
		if (!m_bOldTouch && m_bTouch)			// プレイヤーと接触し始めた時なら
		{
			if (m_nDefCnt != 0)
			{
				m_nDefCnt--;	// 耐久回数を減らす
			}
		}
	}
	if (m_nKind == Object::BISCUIT && m_nDefCnt == 0)	// 3回目振れていたら
	{
		m_fOnTime += tick;	// 経過時間を加算
	}
	if (m_fOnTime >= BISCUIT_BREAK_TIME)
	{
		m_bDelete = true;
	}
	// 接触フラグを退避
	m_bOldTouch = m_bTouch;

	//--チュートリアル看板の処理--
	if (m_nKind == Object::TUTORIALSIGNBOARD)	// チュートリアル看板の場合
	{
		// プレイヤーとの距離を計算
		float distance;
		distance = sqrt((m_pos.x - m_playerPos.x)*(m_pos.x - m_playerPos.x) +
			(m_pos.y - m_scale.y / 2.0f - m_playerPos.y)*(m_pos.y - m_scale.y / 2.0f - m_playerPos.y) +
			(m_pos.z - m_playerPos.z)*(m_pos.z - m_playerPos.z)
		);
		// プレイヤーとの距離が一定以内であれば
		if (distance < TUTORIAL_DISTANCE)
		{
			m_bTutorial = true;	// 会話UIを表示
		}
		// 一定距離外なら
		else
		{
			m_bTutorial = false; // 会話UIを非表示
		}
		// 会話UIが表示されているかつEキー入力されたら
		if (m_bTutorial && IsKeyTrigger('E'))
		{
			m_bTutorialTrigger = true;
		}
		// チュートリアル中にBキー入力されたら
		if (m_bTutorialTrigger && IsKeyTrigger('B'))
		{
			m_bTutorialTrigger = false;
		}
	}

	// 重力処理
	if (!m_randSlope && m_nKind != Object::Kind::BISCUIT && m_nKind != Object::Kind::BLUE_MUSHROOM_NEMOTO) {	// 坂に乗ってないときに重力有効　& ビスケットは重力がかからない
		DirectX::XMFLOAT3 objDown = GetDownVector();
		//m_gravity -= objDown.y;
		//// 正規化
		//float length = sqrt(m_gravity);
		//if (length > 0)
		//{
		//	m_gravity /= length;
		//}
		// 重力値計算
		//m_gravity *= GRAVITY;
		
		// 地面座標を下回れば地面に着地させる
		if (m_pos.y <= m_randHeight + m_scale.y / 2.0f)
		{
			m_pos.y = m_randHeight + m_scale.y / 2.0f;	// 地面に着地
			m_gravity = 0.0f;							// 重力リセット
			m_fallTime = 0.0f;							// 落下時間リセット
		}
		else
		{// 重力を加える
			m_gravity -= (m_fallTime * DOWN_GRAVITY);	// 重力を増加させる
			m_pos.y += m_gravity * tick;		// 座標を更新
			m_fallTime += 0.1f;					// 落下時間を加える
		}
	}
}

void Object::SetWorld(DirectX::XMFLOAT4X4 world)
{
	m_WVP[0] = world;
}
void Object::SetView(DirectX::XMFLOAT4X4 view)
{
	m_WVP[1] = view;
}
void Object::SetProjection(DirectX::XMFLOAT4X4 proj)
{
	m_WVP[2] = proj;
}

void Object::SetBoxMove(float x, float y, float z)
{
	m_BoxMoveX = x;
	m_BoxMoveY = y;
	m_BoxMoveZ = z;
}

void Object::SetSphereMove(float x, float y, float z)
{
	m_SphereMoveX = x;
	m_SphereMoveY = y;
	m_SphereMoveZ = z;
}

void Object::AddLine(DirectX::XMFLOAT3 start, DirectX::XMFLOAT3 end, DirectX::XMFLOAT4 color)
{
	if (m_lineCnt < MAX_LINE_NUM)
	{
		LineVertex* pVtx = reinterpret_cast<LineVertex*>(m_pLineVtx);
		pVtx[m_lineCnt * 2 + 0] = { start.x, start.y, start.z, color.x, color.y, color.z, color.w };
		pVtx[m_lineCnt * 2 + 1] = { end.x, end.y, end.z, color.x, color.y, color.z, color.w };
		++m_lineCnt;
	}
}
void Object::DrawLines()
{
	m_pLineShader[0]->WriteBuffer(0, m_WVP);
	m_pLineShader[0]->Bind();
	m_pLineShader[1]->Bind();
	m_pLines->Write(m_pLineVtx);
	m_pLines->Draw(m_lineCnt * 2);
	m_lineCnt = 0;
}

void Object::DrawBox(DirectX::XMFLOAT4X4* mat)
{
	DirectX::XMMATRIX world;
	//---変換行列を計算
	world = DirectX::XMMatrixScaling(1.0f * m_scale.x, 1.0f * m_scale.y, 1.0f * m_scale.z) *
		DirectX::XMMatrixRotationX(m_rotate.x) *
		DirectX::XMMatrixRotationY(m_rotate.y) *
		DirectX::XMMatrixRotationZ(m_rotate.z) *
		DirectX::XMMatrixTranslation(m_pos.x + m_BoxMoveX, m_pos.y + m_BoxMoveY, m_pos.z + m_BoxMoveZ);

	world = DirectX::XMMatrixTranspose(world);
	DirectX::XMStoreFloat4x4(&mat[0], world);

	//---変換行列を設定
	Geometory::SetWorld(mat[0]);
	Geometory::SetView(mat[1]);
	Geometory::SetProjection(mat[2]);

	Geometory::DrawBox();

	//SetWorld(mat[0]);
	//SetView(mat[1]);
	//SetProjection(mat[2]);

	//if (m_pBox == nullptr)
	//	return;
	//m_pVS->WriteBuffer(0, m_WVP);
	//m_pVS->Bind();
	//m_pPS->Bind();
	//m_pBox->Draw();
}
void Object::DrawCylinder(DirectX::XMFLOAT4X4* mat)
{
	DirectX::XMMATRIX world;
	//---変換行列を計算
	world = DirectX::XMMatrixScaling(1.0f * m_scale.x, 1.0f * m_scale.y, 1.0f * m_scale.z) *
		DirectX::XMMatrixRotationX(m_rotate.x) *
		DirectX::XMMatrixRotationY(m_rotate.y) *
		DirectX::XMMatrixRotationZ(m_rotate.z) *
		DirectX::XMMatrixTranslation(m_pos.x + m_BoxMoveX, m_pos.y + m_BoxMoveY, m_pos.z + m_BoxMoveZ);

	world = DirectX::XMMatrixTranspose(world);
	DirectX::XMStoreFloat4x4(&mat[0], world);

	//---変換行列を設定
	SetWorld(mat[0]);
	SetView(mat[1]);
	SetProjection(mat[2]);


	if (m_pCylinder == nullptr)
		return;
	m_pVS->WriteBuffer(0, m_WVP);
	m_pVS->Bind();
	m_pPS->Bind();
	m_pCylinder->Draw();
}
void Object::DrawSphere(DirectX::XMFLOAT4X4* mat)
{
	DirectX::XMMATRIX world;
	//---変換行列を計算
	world = DirectX::XMMatrixScaling(1.0f * m_scale.x, 1.0f * m_scale.y, 1.0f * m_scale.z) *
		DirectX::XMMatrixRotationX(m_rotate.x) *
		DirectX::XMMatrixRotationY(m_rotate.y) *
		DirectX::XMMatrixRotationZ(m_rotate.z) *
		DirectX::XMMatrixTranslation(m_pos.x + m_BoxMoveX, m_pos.y + m_BoxMoveY, m_pos.z + m_BoxMoveZ);

	world = DirectX::XMMatrixTranspose(world);
	DirectX::XMStoreFloat4x4(&mat[0], world);

	//---変換行列を設定
	SetWorld(mat[0]);
	SetView(mat[1]);
	SetProjection(mat[2]);

	if (m_pSphere == nullptr)
		return;
	m_pVS->WriteBuffer(0, m_WVP);
	m_pVS->Bind();
	m_pPS->Bind();
	m_pSphere->Draw();
}

int Object::GetKind()
{
	return m_nKind;
}

DirectX::XMFLOAT3 Object::GetScale()
{
	return m_scale;
}

bool Object::GetDelete()
{
	return m_bDelete;
}

void Object::SetDelete()
{
	m_bDelete = true;
}

int Object::GetMoney()
{
	return m_nMoney;
}
bool Object::IsDrop()
{
	return m_bDrop;
}

void Object::SetDropFlg(bool isDrop)
{
	m_bDrop = isDrop;
}

DirectX::XMFLOAT3 Object::GetAngle()
{
	return m_rotate;
}

void Object::SetSound(CSoundMng * sound)
{
	m_pSoundMng = sound;
}

void Object::MakeVS()
{
	const char* VSCode = R"EOT(
struct VS_IN {
	float3 pos : POSITION0;
	float2 uv : TEXCOORD0;
};
struct VS_OUT {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
};
cbuffer Matrix : register(b0) {
	float4x4 world;
	float4x4 view;
	float4x4 proj;
};
VS_OUT main(VS_IN vin) {
	VS_OUT vout;
	vout.pos = float4(vin.pos, 1.0f);
	vout.pos = mul(vout.pos, world);
	vout.pos = mul(vout.pos, view);
	vout.pos = mul(vout.pos, proj);
	vout.uv = vin.uv;
	return vout;
})EOT";

	m_pVS = new VertexShader();
	m_pVS->Compile(VSCode);
}

void Object::MakePS()
{
#ifdef _DEBUG
	const char* PSCode = R"EOT(
struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
};
float4 main(PS_IN pin) : SV_TARGET0 {
	float4 color = float4(1,1,1,1);
	float2 halfGrid = floor(abs(pin.uv) * 2.0f);
	float2 quatGrid = floor(abs(pin.uv) * 8.0f);

	float half = fmod(halfGrid.x + halfGrid.y, 2.0f);
	float quat = fmod(quatGrid.x + quatGrid.y, 2.0f);

	color.rgb = ((half * 0.1f) * quat + 0.45f) + (1 - quat) * 0.05f;
	return color;
})EOT";
#else
	const char* PSCode = R"EOT(
struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
};
float4 main(PS_IN pin) : SV_TARGET0 {
	return float4(1.0f, 0.0f, 1.0f, 1.0f);
})EOT";
#endif

	m_pPS = new PixelShader();
	m_pPS->Compile(PSCode);
}
void Object::MakeLineShader()
{
	const char* VSCode = R"EOT(
struct VS_IN {
	float3 pos : POSITION0;
	float4 color : COLOR0;
};
struct VS_OUT {
	float4 pos : SV_POSITION;
	float4 color : COLOR0;
};
cbuffer Matrix : register(b0) {
	float4x4 world;
	float4x4 view;
	float4x4 proj;
};
VS_OUT main(VS_IN vin) {
	VS_OUT vout;
	vout.pos = float4(vin.pos, 1.0f);
	vout.pos = mul(vout.pos, view);
	vout.pos = mul(vout.pos, proj);
	vout.color = vin.color;
	return vout;
})EOT";

	const char* PSCode = R"EOT(
struct PS_IN {
	float4 pos : SV_POSITION;
	float4 color : COLOR0;
};
float4 main(PS_IN pin) : SV_TARGET0 {
	return pin.color;
})EOT";

	m_pLineShader[0] = new VertexShader();
	m_pLineShader[0]->Compile(VSCode);
	m_pLineShader[1] = new PixelShader();
	m_pLineShader[1]->Compile(PSCode);
}
void Object::MakeLine()
{
	m_pLineVtx = new LineVertex[MAX_LINE_NUM * 2];
	m_lineCnt = 0;
	MeshBuffer::Description desc = {};
	desc.pVtx = m_pLineVtx;
	desc.vtxCount = MAX_LINE_NUM * 2;
	desc.vtxSize = sizeof(LineVertex);
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
	desc.isWrite = true;
	m_pLines = new MeshBuffer(desc);
}

void Object::MakeBox()
{
	// 元データの作成
	Vertex vtx[] =
	{
		// -X面
		{ {-0.5f, 0.5f,  0.5f}, {0.0f, 0.0f} },
		{ {-0.5f, 0.5f, -0.5f}, {1.0f, 0.0f} },
		{ {-0.5f,-0.5f,  0.5f}, {0.0f, 1.0f} },
		{ {-0.5f,-0.5f, -0.5f}, {1.0f, 1.0f} },

		// -Y面
		{ { 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f} },
		{ {-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f} },
		{ { 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f} },
		{ {-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f} },

		// -Z面
		{ {-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f} },
		{ { 0.5f, 0.5f, -0.5f}, {1.0f, 0.0f} },
		{ {-0.5f,-0.5f, -0.5f}, {0.0f, 1.0f} },
		{ { 0.5f,-0.5f, -0.5f}, {1.0f, 1.0f} },

		// X面
		{ { 0.5f, 0.5f, -0.5f}, {0.0f, 0.0f} },
		{ { 0.5f, 0.5f,  0.5f}, {1.0f, 0.0f} },
		{ { 0.5f,-0.5f, -0.5f}, {0.0f, 1.0f} },
		{ { 0.5f,-0.5f,  0.5f}, {1.0f, 1.0f} },

		// Y面
		{ {-0.5f, 0.5f,  0.5f}, {0.0f, 0.0f} },
		{ { 0.5f, 0.5f,  0.5f}, {1.0f, 0.0f} },
		{ {-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f} },
		{ { 0.5f, 0.5f, -0.5f}, {1.0f, 1.0f} },

		// Z面
		{ { 0.5f, 0.5f, 0.5f}, {0.0f, 0.0f} },
		{ {-0.5f, 0.5f, 0.5f}, {1.0f, 0.0f} },
		{ { 0.5f,-0.5f, 0.5f}, {0.0f, 1.0f} },
		{ {-0.5f,-0.5f, 0.5f}, {1.0f, 1.0f} },
	};
	int idx[] = {
		 0,  1,  2,  1,  3,  2,	// -X面
		 4,  5,  6,  5,  7,  6,	// -Y面
		 8,  9, 10,  9, 11, 10,	// -Z面
		12, 13, 14, 13, 15, 14,	//  X面
		16, 17, 18, 17, 19, 18,	//  Y面
		20, 21, 22, 21, 23, 22,	//  Z面
	};
	// バッファの作成
	MeshBuffer::Description desc = {};
	desc.pVtx = vtx;
	desc.vtxCount = _countof(vtx);//sizeof(vtx) / sizeof(vtx[0]); 配列のサイズを返す //24;	// 頂点の数
	desc.vtxSize = sizeof(Vertex); // 20;	// 頂点一つ当たりのデータサイズ
	desc.pIdx = idx;
	desc.idxCount = _countof(idx);	// インデックスの数
	desc.idxSize = sizeof(int); //4;	// インデックス一つ当たりのデータサイズ
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	m_pBox = new MeshBuffer(desc);
}

void Object::MakeCylinder()
{
	float r;      //作る円柱の半径
	float radian; //ラジアン角
	float uv;
	float height; //高さ

	radian = 2 * PI / 8;  //八角形のラジアンの角度
	uv = 1.0f / 8.0f;

	r = 1.5f;
	height = 1.5f;

	Vertex vtx[]
	{
		//上面
		{{cosf((float)radian * 0) * r,  height, sinf((float)radian * 0) * r}, {cosf((float)radian * 0), sinf((float)radian * 0)}},
		{{cosf((float)radian * 1) * r,  height, sinf((float)radian * 1) * r}, {cosf((float)radian * 1), sinf((float)radian * 1)}},
		{{cosf((float)radian * 2) * r,  height, sinf((float)radian * 2) * r}, {cosf((float)radian * 2), sinf((float)radian * 2)}},
		{{cosf((float)radian * 3) * r,  height, sinf((float)radian * 3) * r}, {cosf((float)radian * 3), sinf((float)radian * 3)}},
		{{cosf((float)radian * 4) * r,  height, sinf((float)radian * 4) * r}, {cosf((float)radian * 4), sinf((float)radian * 4)}},
		{{cosf((float)radian * 5) * r,  height, sinf((float)radian * 5) * r}, {cosf((float)radian * 5), sinf((float)radian * 5)}},
		{{cosf((float)radian * 6) * r,  height, sinf((float)radian * 6) * r}, {cosf((float)radian * 6), sinf((float)radian * 6)}},
		{{cosf((float)radian * 7) * r,  height, sinf((float)radian * 7) * r}, {cosf((float)radian * 7), sinf((float)radian * 7)}},

		//側面
		{{cosf((float)radian * 0) * r,  height, sinf((float)radian * 0) * r}, {uv * 0, 0.0f}},
		{{cosf((float)radian * 1) * r,  height, sinf((float)radian * 1) * r}, {uv * 1, 0.0f}},
		{{cosf((float)radian * 0) * r, -height, sinf((float)radian * 0) * r}, {uv * 0, 1.0f}},
		{{cosf((float)radian * 1) * r, -height, sinf((float)radian * 1) * r}, {uv * 1, 1.0f}},

		{{cosf((float)radian * 1) * r,  height, sinf((float)radian * 1) * r}, {uv * 1, 0.0f}},
		{{cosf((float)radian * 2) * r,  height, sinf((float)radian * 2) * r}, {uv * 2, 0.0f}},
		{{cosf((float)radian * 1) * r, -height, sinf((float)radian * 1) * r}, {uv * 1, 1.0f}},
		{{cosf((float)radian * 2) * r, -height, sinf((float)radian * 2) * r}, {uv * 2, 1.0f}},

		{{cosf((float)radian * 2) * r,  height, sinf((float)radian * 2) * r}, {uv * 2, 0.0f}},
		{{cosf((float)radian * 3) * r,  height, sinf((float)radian * 3) * r}, {uv * 3, 0.0f}},
		{{cosf((float)radian * 2) * r, -height, sinf((float)radian * 2) * r}, {uv * 2, 1.0f}},
		{{cosf((float)radian * 3) * r, -height, sinf((float)radian * 3) * r}, {uv * 3, 1.0f}},

		{{cosf((float)radian * 3) * r,  height, sinf((float)radian * 3) * r}, {uv * 3, 0.0f}},
		{{cosf((float)radian * 4) * r,  height, sinf((float)radian * 4) * r}, {uv * 4, 0.0f}},
		{{cosf((float)radian * 3) * r, -height, sinf((float)radian * 3) * r}, {uv * 3, 1.0f}},
		{{cosf((float)radian * 4) * r, -height, sinf((float)radian * 4) * r}, {uv * 4, 1.0f}},

		{{cosf((float)radian * 4) * r,  height, sinf((float)radian * 4) * r}, {uv * 4, 0.0f}},
		{{cosf((float)radian * 5) * r,  height, sinf((float)radian * 5) * r}, {uv * 5, 0.0f}},
		{{cosf((float)radian * 4) * r, -height, sinf((float)radian * 4) * r}, {uv * 4, 1.0f}},
		{{cosf((float)radian * 5) * r, -height, sinf((float)radian * 5) * r}, {uv * 5, 1.0f}},

		{{cosf((float)radian * 5) * r,  height, sinf((float)radian * 5) * r}, {uv * 5, 0.0f}},
		{{cosf((float)radian * 6) * r,  height, sinf((float)radian * 6) * r}, {uv * 6, 0.0f}},
		{{cosf((float)radian * 5) * r, -height, sinf((float)radian * 5) * r}, {uv * 5, 1.0f}},
		{{cosf((float)radian * 6) * r, -height, sinf((float)radian * 6) * r}, {uv * 6, 1.0f}},

		{{cosf((float)radian * 6) * r,  height, sinf((float)radian * 6) * r}, {uv * 6, 0.0f}},
		{{cosf((float)radian * 7) * r,  height, sinf((float)radian * 7) * r}, {uv * 7, 0.0f}},
		{{cosf((float)radian * 6) * r, -height, sinf((float)radian * 6) * r}, {uv * 6, 1.0f}},
		{{cosf((float)radian * 7) * r, -height, sinf((float)radian * 7) * r}, {uv * 7, 1.0f}},

		{{cosf((float)radian * 7) * r,  height, sinf((float)radian * 7) * r}, {uv * 7, 0.0f}},
		{{cosf((float)radian * 0) * r,  height, sinf((float)radian * 0) * r}, {uv * 8, 0.0f}},
		{{cosf((float)radian * 7) * r, -height, sinf((float)radian * 7) * r}, {uv * 7, 1.0f}},
		{{cosf((float)radian * 0) * r, -height, sinf((float)radian * 0) * r}, {uv * 8, 1.0f}},

		//裏面
		{{cosf((float)radian * 0) * r, -height, sinf((float)radian * 0) * r}, {cosf((float)radian * 0),sinf((float)radian * 0)}},
		{{cosf((float)radian * 1) * r, -height, sinf((float)radian * 1) * r}, {cosf((float)radian * 1),sinf((float)radian * 1)}},
		{{cosf((float)radian * 2) * r, -height, sinf((float)radian * 2) * r}, {cosf((float)radian * 2),sinf((float)radian * 2)}},
		{{cosf((float)radian * 3) * r, -height, sinf((float)radian * 3) * r}, {cosf((float)radian * 3),sinf((float)radian * 3)}},
		{{cosf((float)radian * 4) * r, -height, sinf((float)radian * 4) * r}, {cosf((float)radian * 4),sinf((float)radian * 4)}},
		{{cosf((float)radian * 5) * r, -height, sinf((float)radian * 5) * r}, {cosf((float)radian * 5),sinf((float)radian * 5)}},
		{{cosf((float)radian * 6) * r, -height, sinf((float)radian * 6) * r}, {cosf((float)radian * 6),sinf((float)radian * 6)}},
		{{cosf((float)radian * 7) * r, -height, sinf((float)radian * 7) * r}, {cosf((float)radian * 7),sinf((float)radian * 7)}},


	};

	//インデックスの作成
	int idx[] = {
		//上面
		2,1,0,2,0,3,
		3,0,4,4,0,5,
		5,0,6,6,0,7,

		//側面
		 8, 9,10,10, 9,11,
		12,13,14,14,13,15,
		16,17,18,18,17,19,
		20,21,22,22,21,23,
		24,25,26,26,25,27,
		28,29,30,30,29,31,
		32,33,34,34,33,35,
		36,37,38,38,37,39,

		//裏面
		40,41,42,40,42,43,
		40,43,44,40,44,45,
		40,45,46,40,46,47,
	};

	//--- バッファの作成
	MeshBuffer::Description desc = {};
	desc.pVtx = vtx;
	desc.vtxCount = _countof(vtx);
	desc.vtxSize = sizeof(Vertex);
	desc.pIdx = idx;
	desc.idxCount = _countof(idx);
	desc.idxSize = sizeof(int);
	desc.topology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	m_pCylinder = new MeshBuffer(desc);
}

void Object::MakeSphere()
{
	//--- 頂点の作成
		// 元データの作成
	Vertex vtx[] =
	{
		//--------------X面--------------
		// -X面(天面)
		{ {0.0f, 1.0f,  0.0f}, {0.0f, 0.0f} },
		{ {0.0f, 1.0f, -0.0f}, {1.0f, 0.0f} },
		{ {-0.3f, 0.9f,  0.25f}, {0.0f, 1.0f} },
		{ {-0.3f, 0.9f, -0.25f}, {1.0f, 1.0f} },

		// -X面(上側斜めの天面側)
		{ {-0.3f,0.9f,  0.25f}, {0.0f, 0.0f} },
		{ {-0.3f,0.9f, -0.25f}, {1.0f, 0.0f} },
		{ {-0.7f,0.7f,  0.5f}, {0.0f, 1.0f} },
		{ {-0.7f,0.7f, -0.5f}, {1.0f, 1.0f} },

		// -X面(上側斜めの側面側)
		{ {-0.7f, 0.7f,  0.5f}, {0.0f, 0.0f} },
		{ {-0.7f, 0.7f, -0.5f}, {1.0f, 0.0f} },
		{ {-0.9f,0.3f,  0.5f}, {0.0f, 1.0f} },
		{ {-0.9f,0.3f, -0.5f}, {1.0f, 1.0f} },

		// -X面(上側側面)
		{ {-0.9f, 0.3f,  0.5f}, {0.0f, 0.0f} },
		{ {-0.9f, 0.3f, -0.5f}, {1.0f, 0.0f} },
		{ {-1.0f,0.0f,  0.5f}, {0.0f, 1.0f} },
		{ {-1.0f,0.0f, -0.5f}, {1.0f, 1.0f} },

		// -X面(下側側面)
		{ {-1.0f,0.0f,  0.5f}, {0.0f, 0.0f} },
		{ {-1.0f,0.0f, -0.5f}, {1.0f, 0.0f} },
		{ {-0.9f,-0.3f,  0.5f}, {0.0f, 1.0f} },
		{ {-0.9f,-0.3f, -0.5f}, {1.0f, 1.0f} },

		// -X面(下側斜めの側面側)
		{ {-0.9f,-0.3f,  0.5f}, {0.0f, 0.0f} },
		{ {-0.9f,-0.3f, -0.5f}, {1.0f, 0.0f} },
		{ {-0.7f,-0.7f,  0.5f}, {0.0f, 1.0f} },
		{ {-0.7f,-0.7f, -0.5f}, {1.0f, 1.0f} },

		// -X面(下側斜めの底面側)
		{ {-0.7f,-0.7f,  0.5f}, {0.0f, 0.0f} },
		{ {-0.7f,-0.7f, -0.5f}, {1.0f, 0.0f} },
		{ {-0.3f,-0.9f,  0.25f}, {0.0f, 1.0f} },
		{ {-0.3f,-0.9f, -0.25f}, {1.0f, 1.0f} },

		// -X面(底面)
		{ {-0.3f, -0.9f,0.25f}, {0.0f, 0.0f} },
		{ {-0.3f, -0.9f,-0.25f}, {1.0f, 0.0f} },
		{ {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f} },
		{ {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f} },

		// X面(天面)
		{ {0.3f, 0.9f,  0.25f}, {0.0f, 0.0f} },
		{ {0.3f, 0.9f, -0.25f}, {1.0f, 0.0f} },
		{ {0.0f, 1.0f,  0.0f}, {0.0f, 1.0f} },
		{ {0.0f, 1.0f, -0.0f}, {1.0f, 1.0f} },

		// X面(上側斜めの天面側)
		{ {0.7f, 0.7f,  0.5f}, {0.0f, 0.0f} },
		{ {0.7f, 0.7f, -0.5f}, {1.0f, 0.0f} },
		{ {0.3f, 0.9f,  0.25f}, {0.0f, 1.0f} },
		{ {0.3f, 0.9f, -0.25f}, {1.0f, 1.0f} },

		// X面(上側斜めの側面側)
		{ {0.9f,0.3f,  0.5f}, {0.0f, 0.0f} },
		{ {0.9f,0.3f, -0.5f}, {1.0f, 0.0f} },
		{ {0.7f,0.7f,  0.5f}, {0.0f, 1.0f} },
		{ {0.7f,0.7f, -0.5f}, {1.0f, 1.0f} },

		// X面(上側側面)
		{ {1.0f, 0.0f,  0.5f}, {0.0f, 0.0f} },
		{ {1.0f, 0.0f, -0.5f}, {1.0f, 0.0f} },
		{ {0.9f,0.3f,  0.5f}, {0.0f, 1.0f} },
		{ {0.9f,0.3f, -0.5f}, {1.0f, 1.0f} },

		// X面(下側側面)
		{ {0.9f,-0.3f,  0.5f}, {0.0f, 0.0f} },
		{ {0.9f,-0.3f, -0.5f}, {1.0f, 0.0f} },
		{ {1.0f,0.0f,  0.5f}, {0.0f, 1.0f} },
		{ {1.0f,0.0f, -0.5f}, {1.0f, 1.0f} },

		// X面(下側斜めの側面側)
		{ {0.7f, -0.7f,  0.5f}, {0.0f, 0.0f} },
		{ {0.7f, -0.7f, -0.5f}, {1.0f, 0.0f} },
		{ {0.9f, -0.3f,  0.5f}, {0.0f, 1.0f} },
		{ {0.9f, -0.3f, -0.5f}, {1.0f, 1.0f} },

		// X面(下側斜めの底面側)
		{ {0.3f, -0.9f,  0.25f}, {0.0f, 0.0f} },
		{ {0.3f, -0.9f, -0.25f}, {1.0f, 0.0f} },
		{ {0.7f, -0.7f,  0.5f}, {0.0f, 1.0f} },
		{ {0.7f, -0.7f, -0.5f}, {1.0f, 1.0f} },

		// X面(底面)
		{ {0.0f, -1.0f,  0.0f}, {0.0f, 0.0f} },
		{ {0.0f, -1.0f, -0.0f}, {1.0f, 0.0f} },
		{ {0.3f, -0.9f,  0.25f}, {0.0f, 1.0f} },
		{ {0.3f, -0.9f, -0.25f}, {1.0f, 1.0f} },
		////--------------X面--------------

		//--------------Z面--------------
		// Z面(天面)
		{ {0.0f,1.0f, 0.0f}, {0.0f, 0.0f} },
		{ {0.0f,1.0f, 0.0f}, {1.0f, 0.0f} },
		{ {0.25f,0.9f, 0.3f}, {0.0f, 1.0f} },
		{ {-0.25f,0.9f,0.3f}, {1.0f, 1.0f} },

		// Z面(上側斜めの天面側)
		{ { 0.25f,0.9f, 0.3f}, {0.0f, 0.0f} },
		{ {-0.25f,0.9f, 0.3f}, {1.0f, 0.0f} },
		{ { 0.5f,0.7f, 0.7f}, {0.0f, 1.0f} },
		{ {-0.5f,0.7f, 0.7f}, {1.0f, 1.0f} },

		// Z面(上側斜めの側面側)
		{ { 0.5f,0.7f,0.7f}, {0.0f, 0.0f} },
		{ {-0.5f,0.7f,0.7f}, {1.0f, 0.0f} },
		{ { 0.5f,0.3f,0.9f}, {0.0f, 1.0f} },
		{ {-0.5f,0.3f,0.9f}, {1.0f, 1.0f} },

		// Z面(上側側面)
		{ { 0.5f,0.3f,0.9f}, {0.0f, 0.0f} },
		{ {-0.5f,0.3f,0.9f}, {1.0f, 0.0f} },
		{ { 0.5f,0.0f,1.0f}, {0.0f, 1.0f} },
		{ {-0.5f,0.0f,1.0f}, {1.0f, 1.0f} },

		// Z面(下側側面)
		{ { 0.5f, 0.0f,1.0f}, {0.0f, 0.0f} },
		{ {-0.5f, 0.0f,1.0f}, {1.0f, 0.0f} },
		{ { 0.5f,-0.3f,0.9f}, {0.0f, 1.0f} },
		{ {-0.5f,-0.3f,0.9f}, {1.0f, 1.0f} },

		// Z面(下側斜めの側面側)
		{ { 0.5f,-0.3f,0.9f}, {0.0f, 0.0f} },
		{ {-0.5f,-0.3f,0.9f}, {1.0f, 0.0f} },
		{ { 0.5f,-0.7f,0.7f}, {0.0f, 1.0f} },
		{ {-0.5f,-0.7f,0.7f}, {1.0f, 1.0f} },

		// Z面(下側斜めの底面側)
		{ { 0.5f,-0.7f, 0.7f}, {0.0f, 0.0f} },
		{ {-0.5f,-0.7f, 0.7f}, {1.0f, 0.0f} },
		{ { 0.25f,-0.9f,0.3f}, {0.0f, 1.0f} },
		{ {-0.25f,-0.9f,0.3f}, {1.0f, 1.0f} },

		// Z面(底面)
		{ { 0.25f,-0.9f,0.3f}, {0.0f, 0.0f} },
		{ {-0.25f,-0.9f,0.3f}, {1.0f, 0.0f} },
		{ { 0.0f,-1.0f, 0.0f}, {0.0f, 1.0f} },
		{ { 0.0f,-1.0f, 0.0f}, {1.0f, 1.0f} },

		// -Z面(天面)
		{ { 0.25f,0.9f,-0.3f}, {0.0f, 0.0f} },
		{ {-0.25f,0.9f,-0.3f}, {1.0f, 0.0f} },
		{ { 0.0f,1.0f, 0.0f}, {0.0f, 1.0f} },
		{ { 0.0f,1.0f, 0.0f}, {1.0f, 1.0f} },

		// -Z面(上側斜めの天面側)
		{ { 0.5f,0.7f,-0.7f}, {0.0f, 0.0f} },
		{ {-0.5f,0.7f,-0.7f}, {1.0f, 0.0f} },
		{ { 0.25f,0.9f,-0.3f}, {0.0f, 1.0f} },
		{ {-0.25f,0.9f,-0.3f}, {1.0f, 1.0f} },

		// -Z面(上側斜めの側面側)
		{ { 0.5f,0.3f,-0.9f}, {0.0f, 0.0f} },
		{ {-0.5f,0.3f,-0.9f}, {1.0f, 0.0f} },
		{ { 0.5f,0.7f,-0.7f}, {0.0f, 1.0f} },
		{ {-0.5f,0.7f,-0.7f}, {1.0f, 1.0f} },

		// -Z面(上側側面)
		{ { 0.5f,0.0f,-1.0f}, {0.0f, 0.0f} },
		{ {-0.5f,0.0f,-1.0f}, {1.0f, 0.0f} },
		{ { 0.5f,0.3f,-0.9f}, {0.0f, 1.0f} },
		{ {-0.5f,0.3f,-0.9f}, {1.0f, 1.0f} },

		// -Z面(下側側面)
		{ { 0.5f,-0.3f,-0.9f}, {0.0f, 0.0f} },
		{ {-0.5f,-0.3f,-0.9f}, {1.0f, 0.0f} },
		{ { 0.5f,0.0f,-1.0f}, {0.0f, 1.0f} },
		{ {-0.5f,0.0f,-1.0f}, {1.0f, 1.0f} },

		// -Z面(下側斜めの側面側)
		{ { 0.5f,-0.7f,-0.7f}, {0.0f, 0.0f} },
		{ {-0.5f,-0.7f,-0.7f}, {1.0f, 0.0f} },
		{ { 0.5f,-0.3f,-0.9f}, {0.0f, 1.0f} },
		{ {-0.5f,-0.3f,-0.9f}, {1.0f, 1.0f} },

		// -Z面(下側斜めの底面側)
		{ { 0.25f,-0.9f,-0.3f}, {0.0f, 0.0f} },
		{ {-0.25f,-0.9f,-0.3f}, {1.0f, 0.0f} },
		{ { 0.5f,-0.7f,-0.7f}, {0.0f, 1.0f} },
		{ {-0.5f,-0.7f,-0.7f}, {1.0f, 1.0f} },

		// -Z面(底面)
		{ { 0.0f,-1.0f,0.0f}, {0.0f, 0.0f} },
		{ { 0.0f,-1.0f,0.0f}, {1.0f, 0.0f} },
		{ { 0.25f,-0.9f,-0.3f}, {0.0f, 1.0f} },
		{ {-0.25f,-0.9f,-0.3f}, {1.0f, 1.0f} },
		////--------------Z面--------------

		//-------------- -XZ面 --------------
		// -XZ面(天面)
		{ {0.0f, 1.0f,0.0f}, {0.0f, 0.0f} },
		{ {0.0f, 1.0f,0.0f}, {1.0f, 0.0f} },
		{ {-0.25f,0.9f,0.3f}, {0.0f, 1.0f} },
		{ {-0.3f, 0.9f,0.25f}, {1.0f, 1.0f} },

		// -XZ面(上側斜めの天面側)
		{ {-0.25f,0.9f,0.3f}, {0.0f, 0.0f} },
		{ {-0.3f,0.9f,0.25f}, {1.0f, 0.0f} },
		{ {-0.5f,0.7f,0.7f}, {0.0f, 1.0f} },
		{ {-0.7f,0.7f,0.5f}, {1.0f, 1.0f} },

		// -XZ面(上側斜めの側面側)
		{ {-0.5f,0.7f,0.7f}, {0.0f, 0.0f} },
		{ {-0.7f,0.7f,0.5f}, {1.0f, 0.0f} },
		{ {-0.5f,0.3f,0.9f}, {0.0f, 1.0f} },
		{ {-0.9f,0.3f,0.5f}, {1.0f, 1.0f} },

		// -XZ面(上側側面)
		{ {-0.5f,0.3f,0.9f}, {0.0f, 0.0f} },
		{ {-0.9f,0.3f,0.5f}, {1.0f, 0.0f} },
		{ {-0.5f,0.0f,1.0f}, {0.0f, 1.0f} },
		{ {-1.0f,0.0f,0.5f}, {1.0f, 1.0f} },

		// -XZ面(下側側面)
		{ {-0.5f,0.0f,1.0f}, {0.0f, 0.0f} },
		{ {-1.0f,0.0f,0.5f}, {1.0f, 0.0f} },
		{ {-0.5f,-0.3f,0.9f}, {0.0f, 1.0f} },
		{ {-0.9f,-0.3f,0.5f}, {1.0f, 1.0f} },

		// -XZ面(下側斜めの側面側)
		{ {-0.5f,-0.3f,0.9f}, {0.0f, 0.0f} },
		{ {-0.9f,-0.3f,0.5f}, {1.0f, 0.0f} },
		{ {-0.5f,-0.7f,0.7f}, {0.0f, 1.0f} },
		{ {-0.7f,-0.7f,0.5f}, {1.0f, 1.0f} },

		// -XZ面(下側斜めの底面側)
		{ {-0.5f,-0.7f,0.7f}, {0.0f, 0.0f} },
		{ {-0.7f,-0.7f,0.5f}, {1.0f, 0.0f} },
		{ {-0.25f,-0.9f,0.3f}, {0.0f, 1.0f} },
		{ {-0.3f,-0.9f,0.25f}, {1.0f, 1.0f} },

		// -XZ面(底面)
		{ {-0.25f,-0.9f,0.3f}, {0.0f, 0.0f} },
		{ {-0.3f,-0.9f,0.25f}, {1.0f, 0.0f} },
		{ { 0.0f,-1.0f,0.0f}, {0.0f, 1.0f} },
		{ { 0.0f,-1.0f,0.0f}, {1.0f, 1.0f} },
		//-------------- -XZ面 --------------

		//-------------- X-Z面 --------------
		// X-Z面(天面)
		{ {0.0f, 1.0f,0.0f}, {0.0f, 0.0f} },
		{ {0.0f, 1.0f,0.0f}, {1.0f, 0.0f} },
		{ {0.25f,0.9f,-0.3f}, {0.0f, 1.0f} },
		{ {0.3f, 0.9f,-0.25f}, {1.0f, 1.0f} },

		// X-Z面(上側斜めの天面側)
		{ {0.25f,0.9f,-0.3f}, {0.0f, 0.0f} },
		{ {0.3f,0.9f,-0.25f}, {1.0f, 0.0f} },
		{ {0.5f,0.7f,-0.7f}, {0.0f, 1.0f} },
		{ {0.7f,0.7f,-0.5f}, {1.0f, 1.0f} },

		// X-Z面(上側斜めの側面側)
		{ {0.5f,0.7f,-0.7f}, {0.0f, 0.0f} },
		{ {0.7f,0.7f,-0.5f}, {1.0f, 0.0f} },
		{ {0.5f,0.3f,-0.9f}, {0.0f, 1.0f} },
		{ {0.9f,0.3f,-0.5f}, {1.0f, 1.0f} },

		// -XZ面(上側側面)
		{ {0.5f,0.3f,-0.9f}, {0.0f, 0.0f} },
		{ {0.9f,0.3f,-0.5f}, {1.0f, 0.0f} },
		{ {0.5f,0.0f,-1.0f}, {0.0f, 1.0f} },
		{ {1.0f,0.0f,-0.5f}, {1.0f, 1.0f} },

		// X-Z面(下側側面)
		{ {0.5f,0.0f,-1.0f}, {0.0f, 0.0f} },
		{ {1.0f,0.0f,-0.5f}, {1.0f, 0.0f} },
		{ {0.5f,-0.3f,-0.9f}, {0.0f, 1.0f} },
		{ {0.9f,-0.3f,-0.5f}, {1.0f, 1.0f} },

		// X-Z面(下側斜めの側面側)
		{ {0.5f,-0.3f,-0.9f}, {0.0f, 0.0f} },
		{ {0.9f,-0.3f,-0.5f}, {1.0f, 0.0f} },
		{ {0.5f,-0.7f,-0.7f}, {0.0f, 1.0f} },
		{ {0.7f,-0.7f,-0.5f}, {1.0f, 1.0f} },

		// X-Z面(下側斜めの底面側)
		{ {0.5f,-0.7f,-0.7f}, {0.0f, 0.0f} },
		{ {0.7f,-0.7f,-0.5f}, {1.0f, 0.0f} },
		{ {0.25f,-0.9f,-0.3f}, {0.0f, 1.0f} },
		{ {0.3f,-0.9f,-0.25f}, {1.0f, 1.0f} },

		// X-Z面(底面)
		{ {0.25f,-0.9f,-0.3f}, {0.0f, 0.0f} },
		{ {0.3f,-0.9f,-0.25f}, {1.0f, 0.0f} },
		{ {0.0f,-1.0f,0.0f}, {0.0f, 1.0f} },
		{ {0.0f,-1.0f,0.0f}, {1.0f, 1.0f} },
		//-------------- X-Z面 --------------

		//-------------- XZ面 --------------
		// XZ面(天面)
		{ {0.0f, 1.0f,0.0f}, {0.0f, 0.0f} },
		{ {0.0f, 1.0f,0.0f}, {1.0f, 0.0f} },
		{ {0.3f, 0.9f,0.25f}, {0.0f, 1.0f} },
		{ {0.25f,0.9f,0.3f}, {1.0f, 1.0f} },

		// XZ面(上側斜めの天面側)
		{ {0.3f,0.9f,0.25f}, {0.0f, 0.0f} },
		{ {0.25f,0.9f,0.3f}, {1.0f, 0.0f} },
		{ {0.7f,0.7f,0.5f}, {0.0f, 1.0f} },
		{ {0.5f,0.7f,0.7f}, {1.0f, 1.0f} },

		// XZ面(上側斜めの側面側)
		{ {0.7f,0.7f,0.5f}, {0.0f, 0.0f} },
		{ {0.5f,0.7f,0.7f}, {1.0f, 0.0f} },
		{ {0.9f,0.3f,0.5f}, {0.0f, 1.0f} },
		{ {0.5f,0.3f,0.9f}, {1.0f, 1.0f} },

		// XZ面(上側側面)
		{ {0.9f,0.3f,0.5f}, {0.0f, 0.0f} },
		{ {0.5f,0.3f,0.9f}, {1.0f, 0.0f} },
		{ {1.0f,0.0f,0.5f}, {0.0f, 1.0f} },
		{ {0.5f,0.0f,1.0f}, {1.0f, 1.0f} },

		// XZ面(下側側面)
		{ {1.0f,0.0f,0.5f}, {0.0f, 0.0f} },
		{ {0.5f,0.0f,1.0f}, {1.0f, 0.0f} },
		{ {0.9f,-0.3f,0.5f}, {0.0f, 1.0f} },
		{ {0.5f,-0.3f,0.9f}, {1.0f, 1.0f} },

		// XZ面(下側斜めの側面側)
		{ {0.9f,-0.3f,0.5f}, {0.0f, 0.0f} },
		{ {0.5f,-0.3f,0.9f}, {1.0f, 0.0f} },
		{ {0.7f,-0.7f,0.5f}, {0.0f, 1.0f} },
		{ {0.5f,-0.7f,0.7f}, {1.0f, 1.0f} },

		// XZ面(下側斜めの底面側)
		{ {0.7f,-0.7f,0.5f}, {0.0f, 0.0f} },
		{ {0.5f,-0.7f,0.7f}, {1.0f, 0.0f} },
		{ {0.3f,-0.9f,0.25f}, {0.0f, 1.0f} },
		{ {0.25f,-0.9f,0.3f}, {1.0f, 1.0f} },

		// XZ面(底面)
		{ {0.3f,-0.9f,0.25f}, {0.0f, 0.0f} },
		{ {0.25f,-0.9f,0.3f}, {1.0f, 0.0f} },
		{ {0.0f,-1.0f,0.0f}, {0.0f, 1.0f} },
		{ {0.0f,-1.0f,0.0f}, {1.0f, 1.0f} },
		//-------------- XZ面 --------------

		//-------------- -X-Z面 --------------
		// -X-Z面(天面)
		{ {0.0f, 1.0f,0.0f}, {0.0f, 0.0f} },
		{ {0.0f, 1.0f,0.0f}, {1.0f, 0.0f} },
		{ {-0.3f, 0.9f,-0.25f}, {0.0f, 1.0f} },
		{ {-0.25f,0.9f,-0.3f}, {1.0f, 1.0f} },

		// -X-Z面(上側斜めの天面側)
		{ {-0.3f,0.9f,-0.25f}, {0.0f, 0.0f} },
		{ {-0.25f,0.9f,-0.3f}, {1.0f, 0.0f} },
		{ {-0.7f,0.7f,-0.5f}, {0.0f, 1.0f} },
		{ {-0.5f,0.7f,-0.7f}, {1.0f, 1.0f} },

		// -X-Z面(上側斜めの側面側)
		{ {-0.7f,0.7f,-0.5f}, {0.0f, 0.0f} },
		{ {-0.5f,0.7f,-0.7f}, {1.0f, 0.0f} },
		{ {-0.9f,0.3f,-0.5f}, {0.0f, 1.0f} },
		{ {-0.5f,0.3f,-0.9f}, {1.0f, 1.0f} },

		// -X-Z面(上側側面)
		{ {-0.9f,0.3f,-0.5f}, {0.0f, 0.0f} },
		{ {-0.5f,0.3f,-0.9f}, {1.0f, 0.0f} },
		{ {-1.0f,0.0f,-0.5f}, {0.0f, 1.0f} },
		{ {-0.5f,0.0f,-1.0f}, {1.0f, 1.0f} },

		// -X-Z面(下側側面)
		{ {-1.0f,0.0f,-0.5f}, {0.0f, 0.0f} },
		{ {-0.5f,0.0f,-1.0f}, {1.0f, 0.0f} },
		{ {-0.9f,-0.3f,-0.5f}, {0.0f, 1.0f} },
		{ {-0.5f,-0.3f,-0.9f}, {1.0f, 1.0f} },

		// -X-Z面(下側斜めの側面側)
		{ {-0.9f,-0.3f,-0.5f}, {0.0f, 0.0f} },
		{ {-0.5f,-0.3f,-0.9f}, {1.0f, 0.0f} },
		{ {-0.7f,-0.7f,-0.5f}, {0.0f, 1.0f} },
		{ {-0.5f,-0.7f,-0.7f}, {1.0f, 1.0f} },

		// -X-Z面(下側斜めの底面側)
		{ {-0.7f,-0.7f,-0.5f}, {0.0f, 0.0f} },
		{ {-0.5f,-0.7f,-0.7f}, {1.0f, 0.0f} },
		{ {-0.3f,-0.9f,-0.25f}, {0.0f, 1.0f} },
		{ {-0.25f,-0.9f,-0.3f}, {1.0f, 1.0f} },

		// -X-Z面(底面)
		{ {-0.3f,-0.9f,-0.25f}, {0.0f, 0.0f} },
		{ {-0.25f,-0.9f,-0.3f}, {1.0f, 0.0f} },
		{ {-0.0f,-1.0f,0.0f}, {0.0f, 1.0f} },
		{ {-0.0f,-1.0f,0.0f}, {1.0f, 1.0f} },
		//-------------- -X-Z面 --------------
	};

	//--- インデックスの作成

	int idx[] = {
		//--------------X面--------------
		 0,  1,  2,  1,  3,  2,		// -X面(天面)
		 4,  5,  6,  5,  7,  6,		// -X面(上側斜めの天面側)
		 8,  9, 10,  9, 11, 10,		// -X面(上側斜めの側面側)
		 12, 13, 14, 13, 15, 14,	// -X面(上側側面)
		 16, 17, 18, 17, 19, 18,	// -X面(下側側面)
		 20, 21, 22, 21, 23, 22,	// -X面(下側斜めの側面側)
		 24, 25, 26, 25, 27, 26,	// -X面(下側斜めの底面側)
		 28, 29, 30, 29, 31, 30,	// -X面(底面)
		 32, 33, 34, 33, 35, 34,	//  X面(天面)
		 36, 37, 38, 37, 39, 38,	//  X面(上側斜めの天面側)
		 40, 41, 42, 41, 43, 42,	//  X面(上側斜めの側面側)
		 44, 45, 46, 45, 47, 46,	//  X面(上側側面)
		 48, 49, 50, 49, 51, 50,	//  X面(下側側面)
		 52, 53, 54, 53, 55, 54,	//  X面(下側斜めの側面側)
		 56, 57, 58, 57, 59, 58,	//  X面(下側斜めの底面側)
		 60, 61, 62, 61, 63, 62,	//  X面(底面)
		 //--------------X面--------------

		 //--------------Z面--------------
		 64, 65, 66, 65, 67, 66,	//  Z面(天面)
		 68, 69, 70, 69, 71, 70,	//  Z面(上側斜めの天面側)
		 72, 73, 74, 73, 75, 74,	//  Z面(上側斜めの側面側)
		 76, 77, 78, 77, 79, 78,	//  Z面(上側側面)
		 80, 81, 82, 81, 83, 82,	//  Z面(下側側面)
		 84, 85, 86, 85, 87, 86,	//  Z面(下側斜めの側面側)
		 88, 89, 90, 89, 91, 90,	//  Z面(下側斜めの底面側)
		 92, 93, 94, 93, 95, 94,	//  Z面(底面)
		 96, 97, 98, 97, 99, 98,	// -Z面(天面)
		 100,101,102,101,103,102,	// -Z面(上側斜めの天面側)
		 104,105,106,105,107,106,	// -Z面(上側斜めの側面側)
		 108,109,110,109,111,110,	// -Z面(上側側面)
		 112,113,114,113,115,114,	// -Z面(下側側面)
		 116,117,118,117,119,118,	// -Z面(下側斜めの側面側)
		 120,121,122,121,123,122,	// -Z面(下側斜めの底面側)
		 124,125,126,125,127,126,	// -Z面(底面)
		 //--------------Z面--------------

		 //-------------- -XZ面 --------------
		 128,129,130,129,131,130,	// -XZ面(天面)
		 132,133,134,133,135,134,	// -XZ面(上側斜めの天面側)
		 136,137,138,137,139,138,	// -XZ面(上側斜めの側面側)
		 140,141,142,141,143,142,	// -XZ面(上側側面)
		 144,145,146,145,147,146,	// -XZ面(下側側面)
		 148,149,150,149,151,150,	// -XZ面(下側斜めの側面側)
		 152,153,154,153,155,154,	// -XZ面(下側斜めの底面側)
		 156,157,158,157,159,158,	// -XZ面(底面)
		 //-------------- -XZ面 --------------

		 //-------------- X-Z面 --------------
		 160,161,162,161,163,162,	// X-Z面(天面)
		 164,165,166,165,167,166,	// X-Z面(上側斜めの天面側)
		 168,169,170,169,171,170,	// X-Z面(上側斜めの側面側)
		 172,173,174,173,175,174,	// X-Z面(上側側面)
		 176,177,178,177,179,178,	// X-Z面(下側側面)
		 180,181,182,181,183,182,	// X-Z面(下側斜めの側面側)
		 184,185,186,185,187,186,	// X-Z面(下側斜めの底面側)
		 188,189,190,189,191,190,	// X-Z面(底面)
		 //-------------- X-Z面 --------------

		 //-------------- XZ面 --------------
		 192,193,194,193,195,194,	// XZ面(天面)
		 196,197,198,197,199,198,	// XZ面(上側斜めの天面側)
		 200,201,202,201,203,202,	// XZ面(上側斜めの側面側)
		 204,205,206,205,207,206,	// XZ面(上側側面)
		 208,209,210,209,211,210,	// XZ面(下側側面)
		 212,213,214,213,215,214,	// XZ面(下側斜めの側面側)
		 216,217,218,217,219,218,	// XZ面(下側斜めの底面側)
		 220,221,222,221,223,222,	// XZ面(底面)
		 //-------------- XZ面 --------------

		 //-------------- -X-Z面 --------------
		 224,225,126,225,227,226,	// -X-Z面(天面)
		 228,229,230,229,231,230,	// -X-Z面(上側斜めの天面側)
		 232,233,234,233,235,234,	// -X-Z面(上側斜めの側面側)
		 236,237,238,237,239,238,	// -X-Z面(上側側面)
		 240,241,242,241,243,242,	// -X-Z面(下側側面)
		 244,245,246,245,247,246,	// -X-Z面(下側斜めの側面側)
		 248,249,250,249,251,250,	// -X-Z面(下側斜めの底面側)
		 252,253,254,253,255,254,	// -X-Z面(底面)
		 //-------------- -X-Z面 --------------
	};

	// バッファの作成
	MeshBuffer::Description desc = {};
	desc.pVtx = vtx;
	desc.vtxCount = _countof(vtx);//sizeof(vtx) / sizeof(vtx[0]); 配列のサイズを返す //24;	// 頂点の数
	desc.vtxSize = sizeof(Vertex); // 20;	// 頂点一つ当たりのデータサイズ
	desc.pIdx = idx;
	desc.idxCount = _countof(idx);	// インデックスの数
	desc.idxSize = sizeof(int); //4;	// インデックス一つ当たりのデータサイズ
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	m_pSphere = new MeshBuffer(desc);
}

/**
*@brief	オブジェクトの座標を返す
*/
DirectX::XMFLOAT3 Object::GetPos()
{
	return m_pos;
}

DirectX::XMFLOAT3 Object::GetOldPos()
{
	return m_oldPos;
}

DirectX::XMFLOAT3 Object::GetDownVector()
{
	DirectX::XMFLOAT3 downVector;

	// オブジェクトの位置 (pos)
	DirectX::XMFLOAT3 pos = { m_pos.x, m_pos.y , m_pos.z };

	// オブジェクトの下方向点 (focus)
	DirectX::XMFLOAT3 focus = { m_pos.x, m_pos.y * 2.0f, m_pos.z };

	// 注視点からカメラ位置へのベクトルを計算
	DirectX::XMFLOAT3 lookDirection;
	lookDirection.x = focus.x - pos.x;
	lookDirection.y = focus.y - pos.y;
	lookDirection.z = focus.z - pos.z;

	// このベクトルを正規化 (長さを1にする) して下方ベクトルを得る
	float length = sqrt(lookDirection.x * lookDirection.x + lookDirection.y * lookDirection.y + lookDirection.z * lookDirection.z);
	downVector.x = lookDirection.x / length;
	downVector.y = lookDirection.y / length;
	downVector.z = lookDirection.z / length;

	return downVector;
}

/**
*@brief	オブジェクトの座標を引数の値に設定する
*@param [in] newObjectPos	設定する座標
*/
void Object::SetPos(DirectX::XMFLOAT3 newObjectPos)
{
	m_pos = newObjectPos;
}

void Object::SetAngle(DirectX::XMFLOAT3 angle)
{
	m_rotate = angle;
}

void Object::SetScale(DirectX::XMFLOAT3 scale)
{
	m_scale = scale;
}

/**
*@brief	定数バッファのポインタを引数の値に設定する
*@param [in] mat	定数バッファへの先頭アドレス
*/
void Object::SetMat(DirectX::XMFLOAT4X4* mat)
{
	m_mat = mat;
}

void Object::SetVelocity(float accel)
{
	m_lastVel = m_velocity = accel;
}

void Object::SetDirection(DirectX::XMVECTOR ToPlayer)
{
	m_moveDirection = ToPlayer;
}

/**
*@brief	オブジェクトが吸い込まれ中か確認
*/
bool Object::IsSuction()
{
	return m_bSuction;
}

/**
*@brief	オブジェクトの吸い込まれ中フラグを設定
*@param [in] suctionFlg	設定する真偽
*/
void Object::SetSuctionFlg(bool suctionFlg)
{
	m_bSuction = suctionFlg;
}

int Object::GetCreateNum()
{
	return	m_createNum;
}

void Object::SetPosX(float posx)
{
	m_pos.x = posx;
}

void Object::SetPosY(float posy)
{
	m_pos.y = posy;
}

void Object::SetPosZ(float posz)
{
	m_pos.z = posz;
}

void Object::SetPlayerPosY(float posY)
{
	m_PlayerPosY = posY;
}

float Object::GetMass()
{
	return m_mass;
}

/*****************************************************
*@brief	モデルマネージャーをメンバにセットする
******************************************************
*@param [in] modelManager モデルマネージャーのポインタ
******************************************************/
void Object::SetModelManager(ModelManager * modelManager)
{
	m_pModelManager = modelManager;
}

/*******************************************************
*@brief	オブジェクトのモデルキーに応じてモデルを取得する
********************************************************/
void Object::SetModelData()
{
	m_pModel = m_pModelManager->FindModel(m_modelKey);
}

void Object::SetRandHeight(int crntHeight)
{
	m_randHeight = crntHeight;
}

void Object::SetRandSlope(bool slope)
{
	m_randSlope = slope;
}

bool Object::GetGimmick()
{
	return m_bGimmick;
}

bool Object::GetPlayGimmick()
{
	return m_bPlayGimmick;
}

void Object::SetPlayGimmick(bool play)
{
	m_bPlayGimmick = play;
}

bool Object::GetSuctionGimmick()
{
	return m_bGimmickSuction;
}

void Object::SetSuctionGimmick(bool suction)
{
	m_bGimmickSuction = suction;
}

float Object::GetAmplitude()
{
	return m_amplitude;
}

void Object::SetAmplitude(float amplitude)
{
	m_amplitude = amplitude;
}

float Object::GetTime()
{
	return m_time;
}

void Object::SetTime(float time)
{
	m_time = time;
}

float Object::GetWeight()
{
	return m_weight;
}

void Object::SetWeight(float weight)
{
	m_weight = weight;
}

float Object::GetRadius()
{
	return m_radius;
}

void Object::SetRadius(float radius)
{
	m_radius = radius;
}

float Object::GetSuctionDis()
{
	return m_suctionDis;
}

void Object::SetSuctionDis(float dis)
{
	m_suctionDis = dis;
}

DirectX::XMFLOAT3 Object::GetEndPos()
{
	return m_endPos;
}

void Object::SetEndPos(DirectX::XMFLOAT3 endPos)
{
	m_endPos = endPos;
}

DirectX::XMFLOAT3 Object::GetGimmickOldPos()
{
	return m_gimmickOldPos;
}

/****************************************************
*@brief	モデルデータに基づいて描画を行う
*****************************************************
*@param [in] mat 座標を書き込む定数バッファのポインタ
*@param [in] vs	 使う頂点シェーダのポインタ
*****************************************************/
void Object::DrawModel(DirectX::XMFLOAT4X4 *mat, VertexShader* vs)
{
	DirectX::XMMATRIX world;
	//---変換行列を計算
	if (!m_bShake)	// 通常時
	{

		world = DirectX::XMMatrixScaling(m_modelRatio *m_oldScale.x, m_modelRatio * m_oldScale.y, m_modelRatio * m_oldScale.z) *
			DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_rotate.x)) *
			DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_rotate.y)) *
			DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_rotate.z)) *
			DirectX::XMMatrixTranslation(m_pos.x + m_BoxMoveX, m_pos.y + m_BoxMoveY, m_pos.z + m_BoxMoveZ);
	}
	else// 揺れ中なら見た目だけ揺らして判定はそのままに
	{
		world = DirectX::XMMatrixScaling(m_modelRatio *m_oldScale.x, m_modelRatio * m_oldScale.y, m_modelRatio * m_oldScale.z) *
			DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_rotate.x)) *
			DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_rotate.y)) *
			DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_rotate.z)) *
			DirectX::XMMatrixTranslation(m_shakePos.x + m_BoxMoveX, m_pos.y + m_BoxMoveY, m_pos.z + m_BoxMoveZ);
	}

	world = DirectX::XMMatrixTranspose(world);	// シェーダーに渡す用に転置
	DirectX::XMStoreFloat4x4(&mat[0], world);	// ワールド変換行列を設定

	//---変換行列をメンバに設定
	SetWorld(mat[0]);
	SetView(mat[1]);
	SetProjection(mat[2]);

	// デプスバッファ有りのレンダーターゲットビューを作成
	RenderTarget* pRTV = GetDefaultRTV();
	DepthStencil* pDSV = GetDefaultDSV();
	SetRenderTargets(1, &pRTV, pDSV);

	// 変換行列をGPUの定数バッファにコピー
	vs->WriteBuffer(0, m_WVP);
	// モデル描画で使う頂点シェーダーをセット
	m_pModel->SetVertexShader(vs);
	// モデル描画
	m_pModel->Draw();

	//ドロップ中の軌跡表示
	if (m_bDrop) {
		m_pTrail->SetView(mat[1]);
		m_pTrail->SetProjection(mat[2]);
	//	m_pTrail->Draw();
	}
}

/***********************************
*@brief	モデルデータのポインタを返す
***********************************/
Model * Object::GetModel()
{
	return m_pModel;
}

int Object::GetLevel()
{
	return m_nLevel;
}

bool Object::IsShake()
{
	return m_bShake;
}

void Object::SetShake(bool OnOff)
{
	m_bShake = OnOff;
}

bool Object::IsMove()
{
	return m_bMove;
}

void Object::SetAngleToPlayer(float angle)
{
	m_angleToPlayer = angle;
}

float Object::GetAngleToPlayer()
{
	return m_angleToPlayer;
}

bool Object::GetDraw()
{
	return m_draw;
}

void Object::SetDraw(bool draw)
{
	m_draw = draw;
}

void Object::SetTime(int time)
{
	m_nTime = time;
	if (m_noldTime < 0)
	{
		m_noldTime = time;
	}
}

std::string Object::GetModelKey()
{
	return m_modelKey;
}

void Object::SetTouch(bool touch)
{
	m_bTouch = touch;
}

bool Object::IsGetMoney()
{
	return m_bGetMoney;
}

void Object::SetGetMoney(bool getMoney)
{
	m_bGetMoney = getMoney;
}

void Object::SetPlayerPos(DirectX::XMFLOAT3 playerPos)
{
	m_playerPos = playerPos;
}

int Object::GetTutorialKind()
{
	return m_nTuturoalKind;
}

void Object::SetDust(Dust * pDust)
{
}

bool Object::GetEfkDestory()
{
	return m_EfkDestory;
}

void Object::SetEfkDestory(bool pEDestoy)
{
	m_EfkDestory = pEDestoy;
}

int Object::GetRandHeight()
{
	return m_randHeight;
}

bool Object::GetRandSlope()
{
	return m_randSlope;
}

void Object::DrawIcon(DirectX::XMFLOAT3 pos, int kind, int level, CPlayer* pPlayer)
{
	CPlayer* m_pPlayer;
	 m_pPlayer = pPlayer;

	DirectX::XMFLOAT2 UVPos;
	switch (kind)
	{
	case Object::NONE:	break;
	case Object::TREE:				// 木
		UVPos.y = 0.0f; break;
	case Object::ROCK:				// 岩
		UVPos.y = (1.0f / 6) * 2; break;
	case Object::HOUSE:				// 家
		UVPos.y = (1.0f / 6); break;
	case Object::FENCE:				// フェンス
		UVPos.y = (1.0f / 6); break;
	case Object::SIGNBOARD:			// 看板
		UVPos.y = 0.0f; break;
	case Object::CHOCOLATETREE:		// チョコ木
		UVPos.y = 0.0f; break;
	case Object::CANDYROCK:			// 飴岩
		UVPos.y = (1.0f / 6) * 2; break;
	case Object::CHOCOLATEFENCE:	// チョコフェンス
		UVPos.y = (1.0f / 6); break;
	case Object::SWEETSHOUSE:		// お菓子の家
		UVPos.y = (1.0f / 6); break;

	default:
		UVPos.y = (1.0f / 6) * 4;
		break;
	}

	switch (level)
	{
	case 2:
		UVPos.x = 0.0f; break;
		
		break;
	case 3:
		UVPos.x = (1.0f / 3); 
		break;
	case 4:
		UVPos.x = (1.0f / 3) * 2; break;
	default:
		break;
	}

	if (UVPos.y == (1.0f / 6) * 4)
	{
		UVPos.x += (1.0f / 3);
	}



	if (!m_nMaxRatio)
	{
		m_fRatio += 0.01f;
		if (m_fRatio >= 1.1f)
		{
			m_nMaxRatio ^= 1;
		}
	}
	else
	{
		m_fRatio -= 0.01f;
		if (m_fRatio <= 0.9f)
		{
			m_nMaxRatio ^= 1;
		}
	}




	DirectX::XMFLOAT4X4 mat[3];
	//吹き出し表示
	DirectX::XMFLOAT4X4 inv;
	inv = m_pPlayer->GetViewMatrix();
	DirectX::XMMATRIX matinv = DirectX::XMLoadFloat4x4(&inv);
	matinv = DirectX::XMMatrixTranspose(matinv);

	DirectX::XMStoreFloat4x4(&inv, matinv);
	inv._41 = inv._42 = inv._43 = 0.0f;
	matinv = DirectX::XMLoadFloat4x4(&inv);
	matinv = DirectX::XMMatrixInverse(nullptr, matinv);

	DirectX::XMMATRIX ObjectIcon = DirectX::XMMatrixTranslation(pos.x, pos.y + 2.5f, pos.z);
	DirectX::XMMATRIX IconWorld = matinv * ObjectIcon;
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(IconWorld));
	Sprite::SetWorld(mat[0]);
	Sprite::SetView(m_pPlayer->GetViewMatrix());
	Sprite::SetProjection(m_pPlayer->GetProjectionMatrix());
	Sprite::SetSize(DirectX::XMFLOAT2(1.5f * m_fRatio, 1.5f * m_fRatio));
	Sprite::SetUVPos(DirectX::XMFLOAT2(UVPos.x, UVPos.y));
	Sprite::SetUVScale(DirectX::XMFLOAT2((1.0f/ 3), (1.0f / 6)));
	Sprite::SetTexture(m_pTexture);
	Sprite::Draw();

}

int Object::GetDefCnt()
{
	return m_nDefCnt;
}
