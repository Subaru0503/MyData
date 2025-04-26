//=================================================================
//
//	CameraSelect.h
//	�f���Z���N�g�V�[���̃J����
//
//=================================================================

// ========== �C���N���[�h�� ==========
#include "CameraSelect.h"
#include "Input.h"
#include "XController.h"

// ========== �}�N����` ==========
#define CAMERA_MOVE_SPEED (0.2f)		// �J�����ړ����x
#define PI (180.0f / 3.14f)				// ���W�A���ϊ��p
#define MAX_FRAME (70)					// �J�����ړ��v�Z�ő�t���[��
#define FACTOR_FRAME (60)				// �v�Z�p�t���[��
#define START_HORIZON (270.0f)			// �������s�p�x
#define START_VERTICAL (50.0f)			// �����c�p�x
#define START_RADIUS (3.8f)				// �f������J�����܂ł̋��������l
#define END_RADIUS (10.0f)				// �J�������[�N�p
#define START_LOOK_RADIUS (1.6f)		// �f������œ_�܂ł̋��������l
#define REVISION_SPEED (4.0f)			// �X�s�[�h�����p
#define ROTATION_SPEED (3.0f)			// ��]���x
#define PLANET_ROTATION (360.0f / CSceneMng::MAX_STAGE)	// ��]����p�x

//=====�R���X�g���N�^=====
CCameraSelect::CCameraSelect()
	: m_radius(START_RADIUS)				// �v���C���[�Ƃ̋���
	, m_lookRadius(START_LOOK_RADIUS)
	, m_horizon(0.0f)						// ���s�������W�A���p
	, m_vertical(0.0f)						// �c�������W�A���p
	, m_angleHorizon(START_HORIZON)			// ���s�p�x
	, m_angleVertical(START_VERTICAL)		// �c�p�x
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

//=====�f�X�g���N�^=====
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

//=====�X�V����=====
void CCameraSelect::Update()
{
	//---�œ_�ʒu�p�x�v�Z
	float lookHorizon = (m_angleHorizon + 30.0f) / PI;
	//---�J�����ړ�����
	MoveCamera();

	//---���W�A���p�ϊ�
	m_horizon = m_angleHorizon / PI;
	m_vertical = m_angleVertical / PI;

	//---�J��������v�Z
	m_pos.x = m_radius * sin((float)m_vertical) * cos((float)m_horizon);
	m_pos.z = m_radius * sin((float)m_vertical) * sin((float)m_horizon);
	//---�œ_�v�Z
	m_look.x = m_lookRadius * sin((float)m_vertical) * cos((float)lookHorizon);
	m_look.z = m_lookRadius * sin((float)m_vertical) * sin((float)lookHorizon);
}

//=====�r���[���󂯓n��=====
DirectX::XMFLOAT4X4 CCameraSelect::GetViewMatrix()
{
	//---�i�[�ꏊ����
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMMATRIX view;
	//---�v�f����
	// �J�����ʒu �f�����W + ���W�␳
	DirectX::XMVECTOR eye = DirectX::XMVectorSet
	(m_lookPlanet.x + m_pos.x, m_lookPlanet.y + m_pos.y, m_lookPlanet.z + m_pos.z, 0.0f);
	// �œ_ �f�����W + ���W�␳
	DirectX::XMVECTOR focus = DirectX::XMVectorSet
	(m_lookPlanet.x + m_look.x, m_lookPlanet.y + m_look.y, m_lookPlanet.z + m_look.z, 0.0f);
	// �J�����̌���
	DirectX::XMVECTOR up = DirectX::XMVectorSet(m_up.x, m_up.y, m_up.z, 0.0f);
	//---�i�[
	view = DirectX::XMMatrixLookAtLH(eye, focus, up);
	//---�]�u
	view = DirectX::XMMatrixTranspose(view);
	DirectX::XMStoreFloat4x4(&mat, view);

	return mat;
}

//=====�X�e�[�W1�|�C���^�󂯎��=====
void CCameraSelect::SetGreen(Planet* green)
{
	m_pPlanet[CSceneMng::SCENE_STAGE1] = green;
}

//=====�X�e�[�W2�|�C���^�󂯎��=====
void CCameraSelect::SetMushroom(Planet* mushroom)
{
	m_pPlanet[CSceneMng::SCENE_STAGE2] = mushroom;
}

//=====�X�e�[�W3�|�C���^�󂯎��=====
void CCameraSelect::SetWholeCake(Planet* wholecake)
{
	m_pPlanet[CSceneMng::SCENE_STAGE3] = wholecake;
}

//=====�J�����ړ�����=====
void CCameraSelect::MoveCamera()
{
	//---�ϐ��錾
	m_horizon = m_angleHorizon;		// �p�x�i�[

	//---�J�����ړ�����
	if (m_moveLeft || m_moveRight)
	{
		// �ϐ��錾
		float startRadius = START_RADIUS;
		float endRadius = END_RADIUS;
		float subRadius = 0.0f;

		// ���x�v�Z�p
		if (m_frame < MAX_FRAME) m_frame++;
		m_factor = static_cast<float>(m_frame) / static_cast<float>(FACTOR_FRAME);
		m_value = m_factor * m_factor * (3.0f - 2.0f * m_factor);

		// �x�N�g���̍������v�Z
		DirectX::XMVECTOR startVec = DirectX::XMLoadFloat3(&m_startPlanet);
		DirectX::XMVECTOR endVec = DirectX::XMLoadFloat3(&m_endPlanet);
		DirectX::XMVECTOR direction = DirectX::XMVectorSubtract(endVec, startVec);
		direction = DirectX::XMVector3Normalize(direction); // ���K��

		// �Y�[���v�Z�p
		if (m_flg)
			subRadius = endRadius - m_radius;
		else
			subRadius = m_radius - startRadius;

		// ���x�Ɋ�Â��Ĉړ��������v�Z
		float speed = CAMERA_MOVE_SPEED * m_value;
		DirectX::XMVECTOR velocity = DirectX::XMVectorScale(direction, speed);

		// ���݂̈ʒu���X�V
		DirectX::XMVECTOR currentVec = DirectX::XMLoadFloat3(&m_lookPlanet);
		currentVec = DirectX::XMVectorAdd(currentVec, velocity);
		DirectX::XMStoreFloat3(&m_lookPlanet, currentVec);

		// �Y�[���C���A�E�g����
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

		// �������ړ���
		if (m_moveLeft)
		{
			if (m_cnt <= PLANET_ROTATION)
			{
				m_cnt += ROTATION_SPEED * m_value;
				m_angleHorizon -= ROTATION_SPEED * m_value;
			}
		}
		// �E�����ړ���
		if (m_moveRight)
		{
			if (m_cnt >= -PLANET_ROTATION)
			{
				m_cnt -= ROTATION_SPEED * m_value;
				m_angleHorizon += ROTATION_SPEED * m_value;
			}
		}

		// ���B����p�̋�����臒l
		const float arrivalThreshold = speed * 1.5f; // �\���ɋ߂��Ƃ݂Ȃ�����

		// �ړI���W�Ƃ̋������v�Z
		DirectX::XMVECTOR diffVec = DirectX::XMVectorSubtract(currentVec, endVec);
		float distanceSquared = DirectX::XMVectorGetX(DirectX::XMVector3LengthSq(diffVec));

		// ������臒l�ȉ����ǂ����Ŕ���
		if (distanceSquared <= arrivalThreshold * arrivalThreshold)
		{
			m_lookPlanet = m_endPlanet; // �ړI���W�ɓ��B
			m_frame = 0;					// �t���[�����Z�b�g
			m_radius = START_RADIUS;	// �J�����Ƙf���̋������Z�b�g
			m_flg = true;				// �t���O���Z�b�g
			m_cnt = 0.0f;					// ��]�p�x���Z�b�g

			// �ړ��t���O���Z�b�g
			if (m_moveLeft)	m_moveLeft = false;
			if (m_moveRight) m_moveRight = false;
		}
	}
}

// ���ړ��t���O�����āA�K�v����ݒ肷��
void CCameraSelect::SetMoveLeft(int select)
{
	m_moveLeft = true;
	m_startPlanet = m_pPlanet[m_oldSelectPlanet]->GetPos();	// �ړ��J�n�n�_�ݒ�
	m_endPlanet = m_pPlanet[select]->GetPos();			// �ړ���n�_�ݒ�

	m_oldSelectPlanet = select;	// �ړ�������̈ړ��J�n�n�_��
}

// �E�ړ��t���O�𗧂āA�K�v����ݒ肷��
void CCameraSelect::SetMoveRight(int select)
{
	m_moveRight = true;
	m_startPlanet = m_pPlanet[m_oldSelectPlanet]->GetPos();
	m_endPlanet = m_pPlanet[select]->GetPos();

	m_oldSelectPlanet = select;	// �ړ�������̈ړ��J�n�n�_��
}

// �J�������ړ������ǂ�����������
bool CCameraSelect::GetMove()
{
	if (m_moveLeft || m_moveRight) {
		return true;
	}
	else {
		return false;
	}
}
