#include "Object.h"
#include <math.h>
#include "Player.h"
#include "Geometory.h"
#include "Input.h"

//=====�}�N����`=====
#define PI (3.14159)
#define GRAVITY (0.02f)
#define UP_GRAVITY (5.5f)	// �W�����v���̏d�͌����v�Z�p
#define DOWN_GRAVITY (0.4f)	// �������̏d�͌����v�Z�p

float m_BoxMoveX;
float m_BoxMoveY;
float m_BoxMoveZ;

float m_SphereMoveX;
float m_SphereMoveY;
float m_SphereMoveZ;

const float STOP_SECONDS = 0.6f;		// �I�u�W�F�N�g�̊�����Î~������܂ł̕b��
const float SHAKE_SWING_WIDTH = 0.04f;	// �h��̐U�ꕝ
const float SHAKE_FREQUENCY = 10.0f;		// �h��̕p�x
const float SCALE_SMALLER = 0.95f;		// �T�C�Y������������l
const float SUCTION_MOVEY = 0.07f;		// �z�����܂��Ƃ��ɓ���Y�l

const float DROP_SECONDS = 0.2f;			// �h���b�v���삪��������܂ł̕b��
const float DROP_VELOCITY = 3.5f;		// �h���b�v����̈ړ����x
const float DROP_GRAVITY = 7.6f;		// 1�b������̏d�́i�h���b�v���j
const float DROP_JUMP_HEIGHT = 3.5f;	// �h���b�v���ǂꂾ�����˂邩
const float DROP_JUMP_POWER = 12.0f;		// �h���b�v����1�b������̃W�����v��

const int	MELT_TIME = 30;				// ���E�\�N���n���鎞��
const float BISCUIT_BREAK_TIME = 1.5f;	// �r�X�P�b�g�ɏ��Ɣj�󂳂�鎞��
const float TUTORIAL_DISTANCE = 2.0f;	// �`���[�g���A���Ŕ��쓮�������鋗��

float shakeTime;	// �h��

/**
*@brief	�`�揉�����ݒ�t���R���X�g���N�^
*@param [in] posX,posY,posZ				�`�揉�����W
*@param [in] scaleX,scaleY,scaleZ		�`�揉���X�P�[��
*@param [in] rotateX,rotateY,rotateZ	�`�揉���A���O��
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
	// �I�u�W�F�N�g�ߋ����W
	m_oldPos = m_pos;
	if (m_oldSize.x == 0.0f &&
		m_oldSize.y == 0.0f &&
		m_oldSize.z == 0.0f)
	{
		m_oldSize = m_scale;
	}

	// �h���b�v�A�j���[�V�������Ȃ�
	if (m_bDrop)
	{
		m_gravity = DROP_JUMP_POWER - (dropTime * UP_GRAVITY);	// �d�͌v�Z

		m_fallTime = dropTime += 0.1f;		// �h���b�v���ԍX�V
		dropJump += DROP_JUMP_POWER * tick;	// ���W�����v�ʂɉ��Z
		// �W�����v�̍����Ŕ���
		if (dropJump <= DROP_JUMP_HEIGHT)
		{
			//m_pos.y += DROP_JUMP_POWER * tick;		// �W�����v�𔽉f
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
		// ���݂̍��W���v�Z�p�ɕϊ�
		DirectX::XMVECTOR currentPos = DirectX::XMLoadFloat3(&m_pos);
		// �����Ɖ����x�ɉ����Ĉړ�								(�ړ������x�N�g�� * �����x + ���ݍ��W)
		DirectX::XMVECTOR newPos = DirectX::XMVectorMultiplyAdd(m_dropDirection, DirectX::XMVectorReplicate(DROP_VELOCITY * tick), currentPos);
		
		// ���W���X�V
		DirectX::XMStoreFloat3(&m_pos, newPos);
		if (!m_bTrailSet) {
			m_pTrail->Init();
			m_bTrailSet = true;
		}
		m_pTrail->Update();
		return;
	}

	// �h��t���O�������Ă�����
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

	if (!m_bSuction)// �z�����܂ꒆ�łȂ��Ȃ�
	{
		// �w�肵���b���ŐÎ~����悤�Ȍ����̎���
		m_velocity = m_velocity - m_lastVel * tick * (1 / STOP_SECONDS);

		// ���̃T�C�Y�ɖ߂�
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
		m_bMove = true;	// �ړ��t���O�𗧂Ă�
	}
	// �����Ɍo�ߎ��Ԃ��|����
	float speedFrame = m_velocity * tick;

	if (speedFrame > 0.35f) { speedFrame = 0.35f; }
	if (speedFrame < 0.0f)
	{
		m_velocity = m_lastVel = speedFrame = 0.0f;
		m_bMove = false;	// ��~�����̂ňړ��t���O�����낷
	}
	// ���݂̍��W���v�Z�p�ɕϊ�
	DirectX::XMVECTOR currentPos = DirectX::XMLoadFloat3(&m_pos);
	// �����Ɖ����x�ɉ����Ĉړ�								(�ړ������x�N�g�� * �����x + ���ݍ��W)
	DirectX::XMVECTOR newPos = DirectX::XMVectorMultiplyAdd(m_moveDirection, DirectX::XMVectorReplicate(speedFrame), currentPos);
	// ���W���X�V
	DirectX::XMStoreFloat3(&m_pos, newPos);

	if (m_bSuction)	// �z������ł�����
	{
		// ���W�X�V
		if (m_PlayerPosY + 0.5f > m_pos.y)	// �I�u�W�F�N�g���v���C���[��艺�̈ʒu��
		{
			m_pos.y += SUCTION_MOVEY;				// �i�X��ɋz�����܂��
		}
		else if (m_PlayerPosY + 0.5f < m_pos.y)		// �I�u�W�F�N�g���v���C���[����̈ʒu��
		{
			m_pos.y -= SUCTION_MOVEY;				// �i�X���ɋz�����܂��
		}

		// 3D���f���T�C�Y���X�V
		m_oldScale.x = m_oldScale.x * SCALE_SMALLER;
		m_oldScale.y = m_oldScale.y * SCALE_SMALLER;
		m_oldScale.z = m_oldScale.z * SCALE_SMALLER;

		// Box�T�C�Y���X�V
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
	//--�r�X�P�b�g�̏���--
	if (m_bTouch && m_nKind == Kind::BISCUIT)	// �v���C���[�ƐڐG���ł����
	{
		if (!m_bOldTouch && m_bTouch)			// �v���C���[�ƐڐG���n�߂����Ȃ�
		{
			if (m_nDefCnt != 0)
			{
				m_nDefCnt--;	// �ϋv�񐔂����炷
			}
		}
	}
	if (m_nKind == Object::BISCUIT && m_nDefCnt == 0)	// 3��ڐU��Ă�����
	{
		m_fOnTime += tick;	// �o�ߎ��Ԃ����Z
	}
	if (m_fOnTime >= BISCUIT_BREAK_TIME)
	{
		m_bDelete = true;
	}
	// �ڐG�t���O��ޔ�
	m_bOldTouch = m_bTouch;

	//--�`���[�g���A���Ŕ̏���--
	if (m_nKind == Object::TUTORIALSIGNBOARD)	// �`���[�g���A���Ŕ̏ꍇ
	{
		// �v���C���[�Ƃ̋������v�Z
		float distance;
		distance = sqrt((m_pos.x - m_playerPos.x)*(m_pos.x - m_playerPos.x) +
			(m_pos.y - m_scale.y / 2.0f - m_playerPos.y)*(m_pos.y - m_scale.y / 2.0f - m_playerPos.y) +
			(m_pos.z - m_playerPos.z)*(m_pos.z - m_playerPos.z)
		);
		// �v���C���[�Ƃ̋��������ȓ��ł����
		if (distance < TUTORIAL_DISTANCE)
		{
			m_bTutorial = true;	// ��bUI��\��
		}
		// ��苗���O�Ȃ�
		else
		{
			m_bTutorial = false; // ��bUI���\��
		}
		// ��bUI���\������Ă��邩��E�L�[���͂��ꂽ��
		if (m_bTutorial && IsKeyTrigger('E'))
		{
			m_bTutorialTrigger = true;
		}
		// �`���[�g���A������B�L�[���͂��ꂽ��
		if (m_bTutorialTrigger && IsKeyTrigger('B'))
		{
			m_bTutorialTrigger = false;
		}
	}

	// �d�͏���
	if (!m_randSlope && m_nKind != Object::Kind::BISCUIT && m_nKind != Object::Kind::BLUE_MUSHROOM_NEMOTO) {	// ��ɏ���ĂȂ��Ƃ��ɏd�͗L���@& �r�X�P�b�g�͏d�͂�������Ȃ�
		DirectX::XMFLOAT3 objDown = GetDownVector();
		//m_gravity -= objDown.y;
		//// ���K��
		//float length = sqrt(m_gravity);
		//if (length > 0)
		//{
		//	m_gravity /= length;
		//}
		// �d�͒l�v�Z
		//m_gravity *= GRAVITY;
		
		// �n�ʍ��W�������Βn�ʂɒ��n������
		if (m_pos.y <= m_randHeight + m_scale.y / 2.0f)
		{
			m_pos.y = m_randHeight + m_scale.y / 2.0f;	// �n�ʂɒ��n
			m_gravity = 0.0f;							// �d�̓��Z�b�g
			m_fallTime = 0.0f;							// �������ԃ��Z�b�g
		}
		else
		{// �d�͂�������
			m_gravity -= (m_fallTime * DOWN_GRAVITY);	// �d�͂𑝉�������
			m_pos.y += m_gravity * tick;		// ���W���X�V
			m_fallTime += 0.1f;					// �������Ԃ�������
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
	//---�ϊ��s����v�Z
	world = DirectX::XMMatrixScaling(1.0f * m_scale.x, 1.0f * m_scale.y, 1.0f * m_scale.z) *
		DirectX::XMMatrixRotationX(m_rotate.x) *
		DirectX::XMMatrixRotationY(m_rotate.y) *
		DirectX::XMMatrixRotationZ(m_rotate.z) *
		DirectX::XMMatrixTranslation(m_pos.x + m_BoxMoveX, m_pos.y + m_BoxMoveY, m_pos.z + m_BoxMoveZ);

	world = DirectX::XMMatrixTranspose(world);
	DirectX::XMStoreFloat4x4(&mat[0], world);

	//---�ϊ��s���ݒ�
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
	//---�ϊ��s����v�Z
	world = DirectX::XMMatrixScaling(1.0f * m_scale.x, 1.0f * m_scale.y, 1.0f * m_scale.z) *
		DirectX::XMMatrixRotationX(m_rotate.x) *
		DirectX::XMMatrixRotationY(m_rotate.y) *
		DirectX::XMMatrixRotationZ(m_rotate.z) *
		DirectX::XMMatrixTranslation(m_pos.x + m_BoxMoveX, m_pos.y + m_BoxMoveY, m_pos.z + m_BoxMoveZ);

	world = DirectX::XMMatrixTranspose(world);
	DirectX::XMStoreFloat4x4(&mat[0], world);

	//---�ϊ��s���ݒ�
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
	//---�ϊ��s����v�Z
	world = DirectX::XMMatrixScaling(1.0f * m_scale.x, 1.0f * m_scale.y, 1.0f * m_scale.z) *
		DirectX::XMMatrixRotationX(m_rotate.x) *
		DirectX::XMMatrixRotationY(m_rotate.y) *
		DirectX::XMMatrixRotationZ(m_rotate.z) *
		DirectX::XMMatrixTranslation(m_pos.x + m_BoxMoveX, m_pos.y + m_BoxMoveY, m_pos.z + m_BoxMoveZ);

	world = DirectX::XMMatrixTranspose(world);
	DirectX::XMStoreFloat4x4(&mat[0], world);

	//---�ϊ��s���ݒ�
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
	// ���f�[�^�̍쐬
	Vertex vtx[] =
	{
		// -X��
		{ {-0.5f, 0.5f,  0.5f}, {0.0f, 0.0f} },
		{ {-0.5f, 0.5f, -0.5f}, {1.0f, 0.0f} },
		{ {-0.5f,-0.5f,  0.5f}, {0.0f, 1.0f} },
		{ {-0.5f,-0.5f, -0.5f}, {1.0f, 1.0f} },

		// -Y��
		{ { 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f} },
		{ {-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f} },
		{ { 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f} },
		{ {-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f} },

		// -Z��
		{ {-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f} },
		{ { 0.5f, 0.5f, -0.5f}, {1.0f, 0.0f} },
		{ {-0.5f,-0.5f, -0.5f}, {0.0f, 1.0f} },
		{ { 0.5f,-0.5f, -0.5f}, {1.0f, 1.0f} },

		// X��
		{ { 0.5f, 0.5f, -0.5f}, {0.0f, 0.0f} },
		{ { 0.5f, 0.5f,  0.5f}, {1.0f, 0.0f} },
		{ { 0.5f,-0.5f, -0.5f}, {0.0f, 1.0f} },
		{ { 0.5f,-0.5f,  0.5f}, {1.0f, 1.0f} },

		// Y��
		{ {-0.5f, 0.5f,  0.5f}, {0.0f, 0.0f} },
		{ { 0.5f, 0.5f,  0.5f}, {1.0f, 0.0f} },
		{ {-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f} },
		{ { 0.5f, 0.5f, -0.5f}, {1.0f, 1.0f} },

		// Z��
		{ { 0.5f, 0.5f, 0.5f}, {0.0f, 0.0f} },
		{ {-0.5f, 0.5f, 0.5f}, {1.0f, 0.0f} },
		{ { 0.5f,-0.5f, 0.5f}, {0.0f, 1.0f} },
		{ {-0.5f,-0.5f, 0.5f}, {1.0f, 1.0f} },
	};
	int idx[] = {
		 0,  1,  2,  1,  3,  2,	// -X��
		 4,  5,  6,  5,  7,  6,	// -Y��
		 8,  9, 10,  9, 11, 10,	// -Z��
		12, 13, 14, 13, 15, 14,	//  X��
		16, 17, 18, 17, 19, 18,	//  Y��
		20, 21, 22, 21, 23, 22,	//  Z��
	};
	// �o�b�t�@�̍쐬
	MeshBuffer::Description desc = {};
	desc.pVtx = vtx;
	desc.vtxCount = _countof(vtx);//sizeof(vtx) / sizeof(vtx[0]); �z��̃T�C�Y��Ԃ� //24;	// ���_�̐�
	desc.vtxSize = sizeof(Vertex); // 20;	// ���_�������̃f�[�^�T�C�Y
	desc.pIdx = idx;
	desc.idxCount = _countof(idx);	// �C���f�b�N�X�̐�
	desc.idxSize = sizeof(int); //4;	// �C���f�b�N�X�������̃f�[�^�T�C�Y
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	m_pBox = new MeshBuffer(desc);
}

void Object::MakeCylinder()
{
	float r;      //���~���̔��a
	float radian; //���W�A���p
	float uv;
	float height; //����

	radian = 2 * PI / 8;  //���p�`�̃��W�A���̊p�x
	uv = 1.0f / 8.0f;

	r = 1.5f;
	height = 1.5f;

	Vertex vtx[]
	{
		//���
		{{cosf((float)radian * 0) * r,  height, sinf((float)radian * 0) * r}, {cosf((float)radian * 0), sinf((float)radian * 0)}},
		{{cosf((float)radian * 1) * r,  height, sinf((float)radian * 1) * r}, {cosf((float)radian * 1), sinf((float)radian * 1)}},
		{{cosf((float)radian * 2) * r,  height, sinf((float)radian * 2) * r}, {cosf((float)radian * 2), sinf((float)radian * 2)}},
		{{cosf((float)radian * 3) * r,  height, sinf((float)radian * 3) * r}, {cosf((float)radian * 3), sinf((float)radian * 3)}},
		{{cosf((float)radian * 4) * r,  height, sinf((float)radian * 4) * r}, {cosf((float)radian * 4), sinf((float)radian * 4)}},
		{{cosf((float)radian * 5) * r,  height, sinf((float)radian * 5) * r}, {cosf((float)radian * 5), sinf((float)radian * 5)}},
		{{cosf((float)radian * 6) * r,  height, sinf((float)radian * 6) * r}, {cosf((float)radian * 6), sinf((float)radian * 6)}},
		{{cosf((float)radian * 7) * r,  height, sinf((float)radian * 7) * r}, {cosf((float)radian * 7), sinf((float)radian * 7)}},

		//����
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

		//����
		{{cosf((float)radian * 0) * r, -height, sinf((float)radian * 0) * r}, {cosf((float)radian * 0),sinf((float)radian * 0)}},
		{{cosf((float)radian * 1) * r, -height, sinf((float)radian * 1) * r}, {cosf((float)radian * 1),sinf((float)radian * 1)}},
		{{cosf((float)radian * 2) * r, -height, sinf((float)radian * 2) * r}, {cosf((float)radian * 2),sinf((float)radian * 2)}},
		{{cosf((float)radian * 3) * r, -height, sinf((float)radian * 3) * r}, {cosf((float)radian * 3),sinf((float)radian * 3)}},
		{{cosf((float)radian * 4) * r, -height, sinf((float)radian * 4) * r}, {cosf((float)radian * 4),sinf((float)radian * 4)}},
		{{cosf((float)radian * 5) * r, -height, sinf((float)radian * 5) * r}, {cosf((float)radian * 5),sinf((float)radian * 5)}},
		{{cosf((float)radian * 6) * r, -height, sinf((float)radian * 6) * r}, {cosf((float)radian * 6),sinf((float)radian * 6)}},
		{{cosf((float)radian * 7) * r, -height, sinf((float)radian * 7) * r}, {cosf((float)radian * 7),sinf((float)radian * 7)}},


	};

	//�C���f�b�N�X�̍쐬
	int idx[] = {
		//���
		2,1,0,2,0,3,
		3,0,4,4,0,5,
		5,0,6,6,0,7,

		//����
		 8, 9,10,10, 9,11,
		12,13,14,14,13,15,
		16,17,18,18,17,19,
		20,21,22,22,21,23,
		24,25,26,26,25,27,
		28,29,30,30,29,31,
		32,33,34,34,33,35,
		36,37,38,38,37,39,

		//����
		40,41,42,40,42,43,
		40,43,44,40,44,45,
		40,45,46,40,46,47,
	};

	//--- �o�b�t�@�̍쐬
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
	//--- ���_�̍쐬
		// ���f�[�^�̍쐬
	Vertex vtx[] =
	{
		//--------------X��--------------
		// -X��(�V��)
		{ {0.0f, 1.0f,  0.0f}, {0.0f, 0.0f} },
		{ {0.0f, 1.0f, -0.0f}, {1.0f, 0.0f} },
		{ {-0.3f, 0.9f,  0.25f}, {0.0f, 1.0f} },
		{ {-0.3f, 0.9f, -0.25f}, {1.0f, 1.0f} },

		// -X��(�㑤�΂߂̓V�ʑ�)
		{ {-0.3f,0.9f,  0.25f}, {0.0f, 0.0f} },
		{ {-0.3f,0.9f, -0.25f}, {1.0f, 0.0f} },
		{ {-0.7f,0.7f,  0.5f}, {0.0f, 1.0f} },
		{ {-0.7f,0.7f, -0.5f}, {1.0f, 1.0f} },

		// -X��(�㑤�΂߂̑��ʑ�)
		{ {-0.7f, 0.7f,  0.5f}, {0.0f, 0.0f} },
		{ {-0.7f, 0.7f, -0.5f}, {1.0f, 0.0f} },
		{ {-0.9f,0.3f,  0.5f}, {0.0f, 1.0f} },
		{ {-0.9f,0.3f, -0.5f}, {1.0f, 1.0f} },

		// -X��(�㑤����)
		{ {-0.9f, 0.3f,  0.5f}, {0.0f, 0.0f} },
		{ {-0.9f, 0.3f, -0.5f}, {1.0f, 0.0f} },
		{ {-1.0f,0.0f,  0.5f}, {0.0f, 1.0f} },
		{ {-1.0f,0.0f, -0.5f}, {1.0f, 1.0f} },

		// -X��(��������)
		{ {-1.0f,0.0f,  0.5f}, {0.0f, 0.0f} },
		{ {-1.0f,0.0f, -0.5f}, {1.0f, 0.0f} },
		{ {-0.9f,-0.3f,  0.5f}, {0.0f, 1.0f} },
		{ {-0.9f,-0.3f, -0.5f}, {1.0f, 1.0f} },

		// -X��(�����΂߂̑��ʑ�)
		{ {-0.9f,-0.3f,  0.5f}, {0.0f, 0.0f} },
		{ {-0.9f,-0.3f, -0.5f}, {1.0f, 0.0f} },
		{ {-0.7f,-0.7f,  0.5f}, {0.0f, 1.0f} },
		{ {-0.7f,-0.7f, -0.5f}, {1.0f, 1.0f} },

		// -X��(�����΂߂̒�ʑ�)
		{ {-0.7f,-0.7f,  0.5f}, {0.0f, 0.0f} },
		{ {-0.7f,-0.7f, -0.5f}, {1.0f, 0.0f} },
		{ {-0.3f,-0.9f,  0.25f}, {0.0f, 1.0f} },
		{ {-0.3f,-0.9f, -0.25f}, {1.0f, 1.0f} },

		// -X��(���)
		{ {-0.3f, -0.9f,0.25f}, {0.0f, 0.0f} },
		{ {-0.3f, -0.9f,-0.25f}, {1.0f, 0.0f} },
		{ {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f} },
		{ {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f} },

		// X��(�V��)
		{ {0.3f, 0.9f,  0.25f}, {0.0f, 0.0f} },
		{ {0.3f, 0.9f, -0.25f}, {1.0f, 0.0f} },
		{ {0.0f, 1.0f,  0.0f}, {0.0f, 1.0f} },
		{ {0.0f, 1.0f, -0.0f}, {1.0f, 1.0f} },

		// X��(�㑤�΂߂̓V�ʑ�)
		{ {0.7f, 0.7f,  0.5f}, {0.0f, 0.0f} },
		{ {0.7f, 0.7f, -0.5f}, {1.0f, 0.0f} },
		{ {0.3f, 0.9f,  0.25f}, {0.0f, 1.0f} },
		{ {0.3f, 0.9f, -0.25f}, {1.0f, 1.0f} },

		// X��(�㑤�΂߂̑��ʑ�)
		{ {0.9f,0.3f,  0.5f}, {0.0f, 0.0f} },
		{ {0.9f,0.3f, -0.5f}, {1.0f, 0.0f} },
		{ {0.7f,0.7f,  0.5f}, {0.0f, 1.0f} },
		{ {0.7f,0.7f, -0.5f}, {1.0f, 1.0f} },

		// X��(�㑤����)
		{ {1.0f, 0.0f,  0.5f}, {0.0f, 0.0f} },
		{ {1.0f, 0.0f, -0.5f}, {1.0f, 0.0f} },
		{ {0.9f,0.3f,  0.5f}, {0.0f, 1.0f} },
		{ {0.9f,0.3f, -0.5f}, {1.0f, 1.0f} },

		// X��(��������)
		{ {0.9f,-0.3f,  0.5f}, {0.0f, 0.0f} },
		{ {0.9f,-0.3f, -0.5f}, {1.0f, 0.0f} },
		{ {1.0f,0.0f,  0.5f}, {0.0f, 1.0f} },
		{ {1.0f,0.0f, -0.5f}, {1.0f, 1.0f} },

		// X��(�����΂߂̑��ʑ�)
		{ {0.7f, -0.7f,  0.5f}, {0.0f, 0.0f} },
		{ {0.7f, -0.7f, -0.5f}, {1.0f, 0.0f} },
		{ {0.9f, -0.3f,  0.5f}, {0.0f, 1.0f} },
		{ {0.9f, -0.3f, -0.5f}, {1.0f, 1.0f} },

		// X��(�����΂߂̒�ʑ�)
		{ {0.3f, -0.9f,  0.25f}, {0.0f, 0.0f} },
		{ {0.3f, -0.9f, -0.25f}, {1.0f, 0.0f} },
		{ {0.7f, -0.7f,  0.5f}, {0.0f, 1.0f} },
		{ {0.7f, -0.7f, -0.5f}, {1.0f, 1.0f} },

		// X��(���)
		{ {0.0f, -1.0f,  0.0f}, {0.0f, 0.0f} },
		{ {0.0f, -1.0f, -0.0f}, {1.0f, 0.0f} },
		{ {0.3f, -0.9f,  0.25f}, {0.0f, 1.0f} },
		{ {0.3f, -0.9f, -0.25f}, {1.0f, 1.0f} },
		////--------------X��--------------

		//--------------Z��--------------
		// Z��(�V��)
		{ {0.0f,1.0f, 0.0f}, {0.0f, 0.0f} },
		{ {0.0f,1.0f, 0.0f}, {1.0f, 0.0f} },
		{ {0.25f,0.9f, 0.3f}, {0.0f, 1.0f} },
		{ {-0.25f,0.9f,0.3f}, {1.0f, 1.0f} },

		// Z��(�㑤�΂߂̓V�ʑ�)
		{ { 0.25f,0.9f, 0.3f}, {0.0f, 0.0f} },
		{ {-0.25f,0.9f, 0.3f}, {1.0f, 0.0f} },
		{ { 0.5f,0.7f, 0.7f}, {0.0f, 1.0f} },
		{ {-0.5f,0.7f, 0.7f}, {1.0f, 1.0f} },

		// Z��(�㑤�΂߂̑��ʑ�)
		{ { 0.5f,0.7f,0.7f}, {0.0f, 0.0f} },
		{ {-0.5f,0.7f,0.7f}, {1.0f, 0.0f} },
		{ { 0.5f,0.3f,0.9f}, {0.0f, 1.0f} },
		{ {-0.5f,0.3f,0.9f}, {1.0f, 1.0f} },

		// Z��(�㑤����)
		{ { 0.5f,0.3f,0.9f}, {0.0f, 0.0f} },
		{ {-0.5f,0.3f,0.9f}, {1.0f, 0.0f} },
		{ { 0.5f,0.0f,1.0f}, {0.0f, 1.0f} },
		{ {-0.5f,0.0f,1.0f}, {1.0f, 1.0f} },

		// Z��(��������)
		{ { 0.5f, 0.0f,1.0f}, {0.0f, 0.0f} },
		{ {-0.5f, 0.0f,1.0f}, {1.0f, 0.0f} },
		{ { 0.5f,-0.3f,0.9f}, {0.0f, 1.0f} },
		{ {-0.5f,-0.3f,0.9f}, {1.0f, 1.0f} },

		// Z��(�����΂߂̑��ʑ�)
		{ { 0.5f,-0.3f,0.9f}, {0.0f, 0.0f} },
		{ {-0.5f,-0.3f,0.9f}, {1.0f, 0.0f} },
		{ { 0.5f,-0.7f,0.7f}, {0.0f, 1.0f} },
		{ {-0.5f,-0.7f,0.7f}, {1.0f, 1.0f} },

		// Z��(�����΂߂̒�ʑ�)
		{ { 0.5f,-0.7f, 0.7f}, {0.0f, 0.0f} },
		{ {-0.5f,-0.7f, 0.7f}, {1.0f, 0.0f} },
		{ { 0.25f,-0.9f,0.3f}, {0.0f, 1.0f} },
		{ {-0.25f,-0.9f,0.3f}, {1.0f, 1.0f} },

		// Z��(���)
		{ { 0.25f,-0.9f,0.3f}, {0.0f, 0.0f} },
		{ {-0.25f,-0.9f,0.3f}, {1.0f, 0.0f} },
		{ { 0.0f,-1.0f, 0.0f}, {0.0f, 1.0f} },
		{ { 0.0f,-1.0f, 0.0f}, {1.0f, 1.0f} },

		// -Z��(�V��)
		{ { 0.25f,0.9f,-0.3f}, {0.0f, 0.0f} },
		{ {-0.25f,0.9f,-0.3f}, {1.0f, 0.0f} },
		{ { 0.0f,1.0f, 0.0f}, {0.0f, 1.0f} },
		{ { 0.0f,1.0f, 0.0f}, {1.0f, 1.0f} },

		// -Z��(�㑤�΂߂̓V�ʑ�)
		{ { 0.5f,0.7f,-0.7f}, {0.0f, 0.0f} },
		{ {-0.5f,0.7f,-0.7f}, {1.0f, 0.0f} },
		{ { 0.25f,0.9f,-0.3f}, {0.0f, 1.0f} },
		{ {-0.25f,0.9f,-0.3f}, {1.0f, 1.0f} },

		// -Z��(�㑤�΂߂̑��ʑ�)
		{ { 0.5f,0.3f,-0.9f}, {0.0f, 0.0f} },
		{ {-0.5f,0.3f,-0.9f}, {1.0f, 0.0f} },
		{ { 0.5f,0.7f,-0.7f}, {0.0f, 1.0f} },
		{ {-0.5f,0.7f,-0.7f}, {1.0f, 1.0f} },

		// -Z��(�㑤����)
		{ { 0.5f,0.0f,-1.0f}, {0.0f, 0.0f} },
		{ {-0.5f,0.0f,-1.0f}, {1.0f, 0.0f} },
		{ { 0.5f,0.3f,-0.9f}, {0.0f, 1.0f} },
		{ {-0.5f,0.3f,-0.9f}, {1.0f, 1.0f} },

		// -Z��(��������)
		{ { 0.5f,-0.3f,-0.9f}, {0.0f, 0.0f} },
		{ {-0.5f,-0.3f,-0.9f}, {1.0f, 0.0f} },
		{ { 0.5f,0.0f,-1.0f}, {0.0f, 1.0f} },
		{ {-0.5f,0.0f,-1.0f}, {1.0f, 1.0f} },

		// -Z��(�����΂߂̑��ʑ�)
		{ { 0.5f,-0.7f,-0.7f}, {0.0f, 0.0f} },
		{ {-0.5f,-0.7f,-0.7f}, {1.0f, 0.0f} },
		{ { 0.5f,-0.3f,-0.9f}, {0.0f, 1.0f} },
		{ {-0.5f,-0.3f,-0.9f}, {1.0f, 1.0f} },

		// -Z��(�����΂߂̒�ʑ�)
		{ { 0.25f,-0.9f,-0.3f}, {0.0f, 0.0f} },
		{ {-0.25f,-0.9f,-0.3f}, {1.0f, 0.0f} },
		{ { 0.5f,-0.7f,-0.7f}, {0.0f, 1.0f} },
		{ {-0.5f,-0.7f,-0.7f}, {1.0f, 1.0f} },

		// -Z��(���)
		{ { 0.0f,-1.0f,0.0f}, {0.0f, 0.0f} },
		{ { 0.0f,-1.0f,0.0f}, {1.0f, 0.0f} },
		{ { 0.25f,-0.9f,-0.3f}, {0.0f, 1.0f} },
		{ {-0.25f,-0.9f,-0.3f}, {1.0f, 1.0f} },
		////--------------Z��--------------

		//-------------- -XZ�� --------------
		// -XZ��(�V��)
		{ {0.0f, 1.0f,0.0f}, {0.0f, 0.0f} },
		{ {0.0f, 1.0f,0.0f}, {1.0f, 0.0f} },
		{ {-0.25f,0.9f,0.3f}, {0.0f, 1.0f} },
		{ {-0.3f, 0.9f,0.25f}, {1.0f, 1.0f} },

		// -XZ��(�㑤�΂߂̓V�ʑ�)
		{ {-0.25f,0.9f,0.3f}, {0.0f, 0.0f} },
		{ {-0.3f,0.9f,0.25f}, {1.0f, 0.0f} },
		{ {-0.5f,0.7f,0.7f}, {0.0f, 1.0f} },
		{ {-0.7f,0.7f,0.5f}, {1.0f, 1.0f} },

		// -XZ��(�㑤�΂߂̑��ʑ�)
		{ {-0.5f,0.7f,0.7f}, {0.0f, 0.0f} },
		{ {-0.7f,0.7f,0.5f}, {1.0f, 0.0f} },
		{ {-0.5f,0.3f,0.9f}, {0.0f, 1.0f} },
		{ {-0.9f,0.3f,0.5f}, {1.0f, 1.0f} },

		// -XZ��(�㑤����)
		{ {-0.5f,0.3f,0.9f}, {0.0f, 0.0f} },
		{ {-0.9f,0.3f,0.5f}, {1.0f, 0.0f} },
		{ {-0.5f,0.0f,1.0f}, {0.0f, 1.0f} },
		{ {-1.0f,0.0f,0.5f}, {1.0f, 1.0f} },

		// -XZ��(��������)
		{ {-0.5f,0.0f,1.0f}, {0.0f, 0.0f} },
		{ {-1.0f,0.0f,0.5f}, {1.0f, 0.0f} },
		{ {-0.5f,-0.3f,0.9f}, {0.0f, 1.0f} },
		{ {-0.9f,-0.3f,0.5f}, {1.0f, 1.0f} },

		// -XZ��(�����΂߂̑��ʑ�)
		{ {-0.5f,-0.3f,0.9f}, {0.0f, 0.0f} },
		{ {-0.9f,-0.3f,0.5f}, {1.0f, 0.0f} },
		{ {-0.5f,-0.7f,0.7f}, {0.0f, 1.0f} },
		{ {-0.7f,-0.7f,0.5f}, {1.0f, 1.0f} },

		// -XZ��(�����΂߂̒�ʑ�)
		{ {-0.5f,-0.7f,0.7f}, {0.0f, 0.0f} },
		{ {-0.7f,-0.7f,0.5f}, {1.0f, 0.0f} },
		{ {-0.25f,-0.9f,0.3f}, {0.0f, 1.0f} },
		{ {-0.3f,-0.9f,0.25f}, {1.0f, 1.0f} },

		// -XZ��(���)
		{ {-0.25f,-0.9f,0.3f}, {0.0f, 0.0f} },
		{ {-0.3f,-0.9f,0.25f}, {1.0f, 0.0f} },
		{ { 0.0f,-1.0f,0.0f}, {0.0f, 1.0f} },
		{ { 0.0f,-1.0f,0.0f}, {1.0f, 1.0f} },
		//-------------- -XZ�� --------------

		//-------------- X-Z�� --------------
		// X-Z��(�V��)
		{ {0.0f, 1.0f,0.0f}, {0.0f, 0.0f} },
		{ {0.0f, 1.0f,0.0f}, {1.0f, 0.0f} },
		{ {0.25f,0.9f,-0.3f}, {0.0f, 1.0f} },
		{ {0.3f, 0.9f,-0.25f}, {1.0f, 1.0f} },

		// X-Z��(�㑤�΂߂̓V�ʑ�)
		{ {0.25f,0.9f,-0.3f}, {0.0f, 0.0f} },
		{ {0.3f,0.9f,-0.25f}, {1.0f, 0.0f} },
		{ {0.5f,0.7f,-0.7f}, {0.0f, 1.0f} },
		{ {0.7f,0.7f,-0.5f}, {1.0f, 1.0f} },

		// X-Z��(�㑤�΂߂̑��ʑ�)
		{ {0.5f,0.7f,-0.7f}, {0.0f, 0.0f} },
		{ {0.7f,0.7f,-0.5f}, {1.0f, 0.0f} },
		{ {0.5f,0.3f,-0.9f}, {0.0f, 1.0f} },
		{ {0.9f,0.3f,-0.5f}, {1.0f, 1.0f} },

		// -XZ��(�㑤����)
		{ {0.5f,0.3f,-0.9f}, {0.0f, 0.0f} },
		{ {0.9f,0.3f,-0.5f}, {1.0f, 0.0f} },
		{ {0.5f,0.0f,-1.0f}, {0.0f, 1.0f} },
		{ {1.0f,0.0f,-0.5f}, {1.0f, 1.0f} },

		// X-Z��(��������)
		{ {0.5f,0.0f,-1.0f}, {0.0f, 0.0f} },
		{ {1.0f,0.0f,-0.5f}, {1.0f, 0.0f} },
		{ {0.5f,-0.3f,-0.9f}, {0.0f, 1.0f} },
		{ {0.9f,-0.3f,-0.5f}, {1.0f, 1.0f} },

		// X-Z��(�����΂߂̑��ʑ�)
		{ {0.5f,-0.3f,-0.9f}, {0.0f, 0.0f} },
		{ {0.9f,-0.3f,-0.5f}, {1.0f, 0.0f} },
		{ {0.5f,-0.7f,-0.7f}, {0.0f, 1.0f} },
		{ {0.7f,-0.7f,-0.5f}, {1.0f, 1.0f} },

		// X-Z��(�����΂߂̒�ʑ�)
		{ {0.5f,-0.7f,-0.7f}, {0.0f, 0.0f} },
		{ {0.7f,-0.7f,-0.5f}, {1.0f, 0.0f} },
		{ {0.25f,-0.9f,-0.3f}, {0.0f, 1.0f} },
		{ {0.3f,-0.9f,-0.25f}, {1.0f, 1.0f} },

		// X-Z��(���)
		{ {0.25f,-0.9f,-0.3f}, {0.0f, 0.0f} },
		{ {0.3f,-0.9f,-0.25f}, {1.0f, 0.0f} },
		{ {0.0f,-1.0f,0.0f}, {0.0f, 1.0f} },
		{ {0.0f,-1.0f,0.0f}, {1.0f, 1.0f} },
		//-------------- X-Z�� --------------

		//-------------- XZ�� --------------
		// XZ��(�V��)
		{ {0.0f, 1.0f,0.0f}, {0.0f, 0.0f} },
		{ {0.0f, 1.0f,0.0f}, {1.0f, 0.0f} },
		{ {0.3f, 0.9f,0.25f}, {0.0f, 1.0f} },
		{ {0.25f,0.9f,0.3f}, {1.0f, 1.0f} },

		// XZ��(�㑤�΂߂̓V�ʑ�)
		{ {0.3f,0.9f,0.25f}, {0.0f, 0.0f} },
		{ {0.25f,0.9f,0.3f}, {1.0f, 0.0f} },
		{ {0.7f,0.7f,0.5f}, {0.0f, 1.0f} },
		{ {0.5f,0.7f,0.7f}, {1.0f, 1.0f} },

		// XZ��(�㑤�΂߂̑��ʑ�)
		{ {0.7f,0.7f,0.5f}, {0.0f, 0.0f} },
		{ {0.5f,0.7f,0.7f}, {1.0f, 0.0f} },
		{ {0.9f,0.3f,0.5f}, {0.0f, 1.0f} },
		{ {0.5f,0.3f,0.9f}, {1.0f, 1.0f} },

		// XZ��(�㑤����)
		{ {0.9f,0.3f,0.5f}, {0.0f, 0.0f} },
		{ {0.5f,0.3f,0.9f}, {1.0f, 0.0f} },
		{ {1.0f,0.0f,0.5f}, {0.0f, 1.0f} },
		{ {0.5f,0.0f,1.0f}, {1.0f, 1.0f} },

		// XZ��(��������)
		{ {1.0f,0.0f,0.5f}, {0.0f, 0.0f} },
		{ {0.5f,0.0f,1.0f}, {1.0f, 0.0f} },
		{ {0.9f,-0.3f,0.5f}, {0.0f, 1.0f} },
		{ {0.5f,-0.3f,0.9f}, {1.0f, 1.0f} },

		// XZ��(�����΂߂̑��ʑ�)
		{ {0.9f,-0.3f,0.5f}, {0.0f, 0.0f} },
		{ {0.5f,-0.3f,0.9f}, {1.0f, 0.0f} },
		{ {0.7f,-0.7f,0.5f}, {0.0f, 1.0f} },
		{ {0.5f,-0.7f,0.7f}, {1.0f, 1.0f} },

		// XZ��(�����΂߂̒�ʑ�)
		{ {0.7f,-0.7f,0.5f}, {0.0f, 0.0f} },
		{ {0.5f,-0.7f,0.7f}, {1.0f, 0.0f} },
		{ {0.3f,-0.9f,0.25f}, {0.0f, 1.0f} },
		{ {0.25f,-0.9f,0.3f}, {1.0f, 1.0f} },

		// XZ��(���)
		{ {0.3f,-0.9f,0.25f}, {0.0f, 0.0f} },
		{ {0.25f,-0.9f,0.3f}, {1.0f, 0.0f} },
		{ {0.0f,-1.0f,0.0f}, {0.0f, 1.0f} },
		{ {0.0f,-1.0f,0.0f}, {1.0f, 1.0f} },
		//-------------- XZ�� --------------

		//-------------- -X-Z�� --------------
		// -X-Z��(�V��)
		{ {0.0f, 1.0f,0.0f}, {0.0f, 0.0f} },
		{ {0.0f, 1.0f,0.0f}, {1.0f, 0.0f} },
		{ {-0.3f, 0.9f,-0.25f}, {0.0f, 1.0f} },
		{ {-0.25f,0.9f,-0.3f}, {1.0f, 1.0f} },

		// -X-Z��(�㑤�΂߂̓V�ʑ�)
		{ {-0.3f,0.9f,-0.25f}, {0.0f, 0.0f} },
		{ {-0.25f,0.9f,-0.3f}, {1.0f, 0.0f} },
		{ {-0.7f,0.7f,-0.5f}, {0.0f, 1.0f} },
		{ {-0.5f,0.7f,-0.7f}, {1.0f, 1.0f} },

		// -X-Z��(�㑤�΂߂̑��ʑ�)
		{ {-0.7f,0.7f,-0.5f}, {0.0f, 0.0f} },
		{ {-0.5f,0.7f,-0.7f}, {1.0f, 0.0f} },
		{ {-0.9f,0.3f,-0.5f}, {0.0f, 1.0f} },
		{ {-0.5f,0.3f,-0.9f}, {1.0f, 1.0f} },

		// -X-Z��(�㑤����)
		{ {-0.9f,0.3f,-0.5f}, {0.0f, 0.0f} },
		{ {-0.5f,0.3f,-0.9f}, {1.0f, 0.0f} },
		{ {-1.0f,0.0f,-0.5f}, {0.0f, 1.0f} },
		{ {-0.5f,0.0f,-1.0f}, {1.0f, 1.0f} },

		// -X-Z��(��������)
		{ {-1.0f,0.0f,-0.5f}, {0.0f, 0.0f} },
		{ {-0.5f,0.0f,-1.0f}, {1.0f, 0.0f} },
		{ {-0.9f,-0.3f,-0.5f}, {0.0f, 1.0f} },
		{ {-0.5f,-0.3f,-0.9f}, {1.0f, 1.0f} },

		// -X-Z��(�����΂߂̑��ʑ�)
		{ {-0.9f,-0.3f,-0.5f}, {0.0f, 0.0f} },
		{ {-0.5f,-0.3f,-0.9f}, {1.0f, 0.0f} },
		{ {-0.7f,-0.7f,-0.5f}, {0.0f, 1.0f} },
		{ {-0.5f,-0.7f,-0.7f}, {1.0f, 1.0f} },

		// -X-Z��(�����΂߂̒�ʑ�)
		{ {-0.7f,-0.7f,-0.5f}, {0.0f, 0.0f} },
		{ {-0.5f,-0.7f,-0.7f}, {1.0f, 0.0f} },
		{ {-0.3f,-0.9f,-0.25f}, {0.0f, 1.0f} },
		{ {-0.25f,-0.9f,-0.3f}, {1.0f, 1.0f} },

		// -X-Z��(���)
		{ {-0.3f,-0.9f,-0.25f}, {0.0f, 0.0f} },
		{ {-0.25f,-0.9f,-0.3f}, {1.0f, 0.0f} },
		{ {-0.0f,-1.0f,0.0f}, {0.0f, 1.0f} },
		{ {-0.0f,-1.0f,0.0f}, {1.0f, 1.0f} },
		//-------------- -X-Z�� --------------
	};

	//--- �C���f�b�N�X�̍쐬

	int idx[] = {
		//--------------X��--------------
		 0,  1,  2,  1,  3,  2,		// -X��(�V��)
		 4,  5,  6,  5,  7,  6,		// -X��(�㑤�΂߂̓V�ʑ�)
		 8,  9, 10,  9, 11, 10,		// -X��(�㑤�΂߂̑��ʑ�)
		 12, 13, 14, 13, 15, 14,	// -X��(�㑤����)
		 16, 17, 18, 17, 19, 18,	// -X��(��������)
		 20, 21, 22, 21, 23, 22,	// -X��(�����΂߂̑��ʑ�)
		 24, 25, 26, 25, 27, 26,	// -X��(�����΂߂̒�ʑ�)
		 28, 29, 30, 29, 31, 30,	// -X��(���)
		 32, 33, 34, 33, 35, 34,	//  X��(�V��)
		 36, 37, 38, 37, 39, 38,	//  X��(�㑤�΂߂̓V�ʑ�)
		 40, 41, 42, 41, 43, 42,	//  X��(�㑤�΂߂̑��ʑ�)
		 44, 45, 46, 45, 47, 46,	//  X��(�㑤����)
		 48, 49, 50, 49, 51, 50,	//  X��(��������)
		 52, 53, 54, 53, 55, 54,	//  X��(�����΂߂̑��ʑ�)
		 56, 57, 58, 57, 59, 58,	//  X��(�����΂߂̒�ʑ�)
		 60, 61, 62, 61, 63, 62,	//  X��(���)
		 //--------------X��--------------

		 //--------------Z��--------------
		 64, 65, 66, 65, 67, 66,	//  Z��(�V��)
		 68, 69, 70, 69, 71, 70,	//  Z��(�㑤�΂߂̓V�ʑ�)
		 72, 73, 74, 73, 75, 74,	//  Z��(�㑤�΂߂̑��ʑ�)
		 76, 77, 78, 77, 79, 78,	//  Z��(�㑤����)
		 80, 81, 82, 81, 83, 82,	//  Z��(��������)
		 84, 85, 86, 85, 87, 86,	//  Z��(�����΂߂̑��ʑ�)
		 88, 89, 90, 89, 91, 90,	//  Z��(�����΂߂̒�ʑ�)
		 92, 93, 94, 93, 95, 94,	//  Z��(���)
		 96, 97, 98, 97, 99, 98,	// -Z��(�V��)
		 100,101,102,101,103,102,	// -Z��(�㑤�΂߂̓V�ʑ�)
		 104,105,106,105,107,106,	// -Z��(�㑤�΂߂̑��ʑ�)
		 108,109,110,109,111,110,	// -Z��(�㑤����)
		 112,113,114,113,115,114,	// -Z��(��������)
		 116,117,118,117,119,118,	// -Z��(�����΂߂̑��ʑ�)
		 120,121,122,121,123,122,	// -Z��(�����΂߂̒�ʑ�)
		 124,125,126,125,127,126,	// -Z��(���)
		 //--------------Z��--------------

		 //-------------- -XZ�� --------------
		 128,129,130,129,131,130,	// -XZ��(�V��)
		 132,133,134,133,135,134,	// -XZ��(�㑤�΂߂̓V�ʑ�)
		 136,137,138,137,139,138,	// -XZ��(�㑤�΂߂̑��ʑ�)
		 140,141,142,141,143,142,	// -XZ��(�㑤����)
		 144,145,146,145,147,146,	// -XZ��(��������)
		 148,149,150,149,151,150,	// -XZ��(�����΂߂̑��ʑ�)
		 152,153,154,153,155,154,	// -XZ��(�����΂߂̒�ʑ�)
		 156,157,158,157,159,158,	// -XZ��(���)
		 //-------------- -XZ�� --------------

		 //-------------- X-Z�� --------------
		 160,161,162,161,163,162,	// X-Z��(�V��)
		 164,165,166,165,167,166,	// X-Z��(�㑤�΂߂̓V�ʑ�)
		 168,169,170,169,171,170,	// X-Z��(�㑤�΂߂̑��ʑ�)
		 172,173,174,173,175,174,	// X-Z��(�㑤����)
		 176,177,178,177,179,178,	// X-Z��(��������)
		 180,181,182,181,183,182,	// X-Z��(�����΂߂̑��ʑ�)
		 184,185,186,185,187,186,	// X-Z��(�����΂߂̒�ʑ�)
		 188,189,190,189,191,190,	// X-Z��(���)
		 //-------------- X-Z�� --------------

		 //-------------- XZ�� --------------
		 192,193,194,193,195,194,	// XZ��(�V��)
		 196,197,198,197,199,198,	// XZ��(�㑤�΂߂̓V�ʑ�)
		 200,201,202,201,203,202,	// XZ��(�㑤�΂߂̑��ʑ�)
		 204,205,206,205,207,206,	// XZ��(�㑤����)
		 208,209,210,209,211,210,	// XZ��(��������)
		 212,213,214,213,215,214,	// XZ��(�����΂߂̑��ʑ�)
		 216,217,218,217,219,218,	// XZ��(�����΂߂̒�ʑ�)
		 220,221,222,221,223,222,	// XZ��(���)
		 //-------------- XZ�� --------------

		 //-------------- -X-Z�� --------------
		 224,225,126,225,227,226,	// -X-Z��(�V��)
		 228,229,230,229,231,230,	// -X-Z��(�㑤�΂߂̓V�ʑ�)
		 232,233,234,233,235,234,	// -X-Z��(�㑤�΂߂̑��ʑ�)
		 236,237,238,237,239,238,	// -X-Z��(�㑤����)
		 240,241,242,241,243,242,	// -X-Z��(��������)
		 244,245,246,245,247,246,	// -X-Z��(�����΂߂̑��ʑ�)
		 248,249,250,249,251,250,	// -X-Z��(�����΂߂̒�ʑ�)
		 252,253,254,253,255,254,	// -X-Z��(���)
		 //-------------- -X-Z�� --------------
	};

	// �o�b�t�@�̍쐬
	MeshBuffer::Description desc = {};
	desc.pVtx = vtx;
	desc.vtxCount = _countof(vtx);//sizeof(vtx) / sizeof(vtx[0]); �z��̃T�C�Y��Ԃ� //24;	// ���_�̐�
	desc.vtxSize = sizeof(Vertex); // 20;	// ���_�������̃f�[�^�T�C�Y
	desc.pIdx = idx;
	desc.idxCount = _countof(idx);	// �C���f�b�N�X�̐�
	desc.idxSize = sizeof(int); //4;	// �C���f�b�N�X�������̃f�[�^�T�C�Y
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	m_pSphere = new MeshBuffer(desc);
}

/**
*@brief	�I�u�W�F�N�g�̍��W��Ԃ�
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

	// �I�u�W�F�N�g�̈ʒu (pos)
	DirectX::XMFLOAT3 pos = { m_pos.x, m_pos.y , m_pos.z };

	// �I�u�W�F�N�g�̉������_ (focus)
	DirectX::XMFLOAT3 focus = { m_pos.x, m_pos.y * 2.0f, m_pos.z };

	// �����_����J�����ʒu�ւ̃x�N�g�����v�Z
	DirectX::XMFLOAT3 lookDirection;
	lookDirection.x = focus.x - pos.x;
	lookDirection.y = focus.y - pos.y;
	lookDirection.z = focus.z - pos.z;

	// ���̃x�N�g���𐳋K�� (������1�ɂ���) ���ĉ����x�N�g���𓾂�
	float length = sqrt(lookDirection.x * lookDirection.x + lookDirection.y * lookDirection.y + lookDirection.z * lookDirection.z);
	downVector.x = lookDirection.x / length;
	downVector.y = lookDirection.y / length;
	downVector.z = lookDirection.z / length;

	return downVector;
}

/**
*@brief	�I�u�W�F�N�g�̍��W�������̒l�ɐݒ肷��
*@param [in] newObjectPos	�ݒ肷����W
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
*@brief	�萔�o�b�t�@�̃|�C���^�������̒l�ɐݒ肷��
*@param [in] mat	�萔�o�b�t�@�ւ̐擪�A�h���X
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
*@brief	�I�u�W�F�N�g���z�����܂ꒆ���m�F
*/
bool Object::IsSuction()
{
	return m_bSuction;
}

/**
*@brief	�I�u�W�F�N�g�̋z�����܂ꒆ�t���O��ݒ�
*@param [in] suctionFlg	�ݒ肷��^�U
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
*@brief	���f���}�l�[�W���[�������o�ɃZ�b�g����
******************************************************
*@param [in] modelManager ���f���}�l�[�W���[�̃|�C���^
******************************************************/
void Object::SetModelManager(ModelManager * modelManager)
{
	m_pModelManager = modelManager;
}

/*******************************************************
*@brief	�I�u�W�F�N�g�̃��f���L�[�ɉ����ă��f�����擾����
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
*@brief	���f���f�[�^�Ɋ�Â��ĕ`����s��
*****************************************************
*@param [in] mat ���W���������ޒ萔�o�b�t�@�̃|�C���^
*@param [in] vs	 �g�����_�V�F�[�_�̃|�C���^
*****************************************************/
void Object::DrawModel(DirectX::XMFLOAT4X4 *mat, VertexShader* vs)
{
	DirectX::XMMATRIX world;
	//---�ϊ��s����v�Z
	if (!m_bShake)	// �ʏ펞
	{

		world = DirectX::XMMatrixScaling(m_modelRatio *m_oldScale.x, m_modelRatio * m_oldScale.y, m_modelRatio * m_oldScale.z) *
			DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_rotate.x)) *
			DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_rotate.y)) *
			DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_rotate.z)) *
			DirectX::XMMatrixTranslation(m_pos.x + m_BoxMoveX, m_pos.y + m_BoxMoveY, m_pos.z + m_BoxMoveZ);
	}
	else// �h�ꒆ�Ȃ猩���ڂ����h�炵�Ĕ���͂��̂܂܂�
	{
		world = DirectX::XMMatrixScaling(m_modelRatio *m_oldScale.x, m_modelRatio * m_oldScale.y, m_modelRatio * m_oldScale.z) *
			DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_rotate.x)) *
			DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_rotate.y)) *
			DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_rotate.z)) *
			DirectX::XMMatrixTranslation(m_shakePos.x + m_BoxMoveX, m_pos.y + m_BoxMoveY, m_pos.z + m_BoxMoveZ);
	}

	world = DirectX::XMMatrixTranspose(world);	// �V�F�[�_�[�ɓn���p�ɓ]�u
	DirectX::XMStoreFloat4x4(&mat[0], world);	// ���[���h�ϊ��s���ݒ�

	//---�ϊ��s��������o�ɐݒ�
	SetWorld(mat[0]);
	SetView(mat[1]);
	SetProjection(mat[2]);

	// �f�v�X�o�b�t�@�L��̃����_�[�^�[�Q�b�g�r���[���쐬
	RenderTarget* pRTV = GetDefaultRTV();
	DepthStencil* pDSV = GetDefaultDSV();
	SetRenderTargets(1, &pRTV, pDSV);

	// �ϊ��s���GPU�̒萔�o�b�t�@�ɃR�s�[
	vs->WriteBuffer(0, m_WVP);
	// ���f���`��Ŏg�����_�V�F�[�_�[���Z�b�g
	m_pModel->SetVertexShader(vs);
	// ���f���`��
	m_pModel->Draw();

	//�h���b�v���̋O�Օ\��
	if (m_bDrop) {
		m_pTrail->SetView(mat[1]);
		m_pTrail->SetProjection(mat[2]);
	//	m_pTrail->Draw();
	}
}

/***********************************
*@brief	���f���f�[�^�̃|�C���^��Ԃ�
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
	case Object::TREE:				// ��
		UVPos.y = 0.0f; break;
	case Object::ROCK:				// ��
		UVPos.y = (1.0f / 6) * 2; break;
	case Object::HOUSE:				// ��
		UVPos.y = (1.0f / 6); break;
	case Object::FENCE:				// �t�F���X
		UVPos.y = (1.0f / 6); break;
	case Object::SIGNBOARD:			// �Ŕ�
		UVPos.y = 0.0f; break;
	case Object::CHOCOLATETREE:		// �`���R��
		UVPos.y = 0.0f; break;
	case Object::CANDYROCK:			// ����
		UVPos.y = (1.0f / 6) * 2; break;
	case Object::CHOCOLATEFENCE:	// �`���R�t�F���X
		UVPos.y = (1.0f / 6); break;
	case Object::SWEETSHOUSE:		// ���َq�̉�
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
	//�����o���\��
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
