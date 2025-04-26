// �C���N���[�h��
#include "Player.h"

// �V�X�e��
#include "Input.h"

// �R���|�[�l���g
#include "Gravity.h"

// �I�u�W�F�N�g
#include "Screw.h"

// �萔�E�}�N����`
#define DEFAULT_SPEED (0.1f)	// �ʏ�X�s�[�h
#define DIAGONAL_SPEED (0.07f)	// �΂߃X�s�[�h

// �R���X�g���N�^
Player::Player(std::string name)
	: GameObject(name)
	, m_ResetPos{0.0f, 2.0, 0.0f}
	, m_SpinTime(0.0f)
	, m_Jump(false)
{
	// �^�O�ݒ�
	m_tag = "Player";

	m_pCollisionObj = nullptr;

	// �R���|�[�l���g�ǉ��B
	AddComponent<Gravity>();			// �d��
	AddComponent<Move>();				// �ړ�
	AddComponent<Jump>();				// �W�����v
	//AddComponent<Spin>();				// ��]
	AddComponent<BoxCollider>();		// �����蔻��
	AddComponent<Scanner>();			// �I�u�W�F�N�g�X�L���i
	AddComponent<ModelRenderer3D>();	// 3D�`��
	AddComponent<ScaleAnimation>();		// �X�P�[���A�j���[�V����

	// �R���|�[�l���g�擾
	_move = GetComponent<Move>();
	_jump = GetComponent<Jump>();
	//_spin = GetComponent<Spin>();
	_boxCollider = GetComponent<BoxCollider>();
	_scanner = GetComponent<Scanner>();
	_modelRenderer3D = GetComponent<ModelRenderer3D>();
	_scaleAnimation = GetComponent<ScaleAnimation>();

	// �V�F�[�_�[�Z�b�g
	const char* file[] = {
		"VS_Object",
		"PS_TexColor",
	};

	_modelRenderer3D->SetShader(file);

	// �l�Z�b�g
	m_quat = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	_move->SetMove(DEFAULT_SPEED);
	_scanner->SetScale(float3(0.8f, 0.5f, 0.8f));
	_scaleAnimation->SetScaleRange(0.15f);
	_scaleAnimation->SetMinScale(0.85f);

}

// �f�X�g���N�^
Player::~Player()
{

}

// ������Ԃɖ߂�
void Player::ResetState()
{
	if (m_ResetPos.x == 0.0f &&
		m_ResetPos.y == 0.0f &&
		m_ResetPos.z == 0.0f)
	{
		return;
	}
	// ���W���Z�b�g
	m_pos = m_ResetPos;
}

// �X�V����
void Player::Update()
{

	// ���͂���Ă�L�[�̐����`�F�b�N
	InputCheck();

	// �ړ�����
	if (IsKeyPress('W'))
	{
		_move->FrontMove();
	}
	if (IsKeyPress('S'))
	{
		_move->FrontMove(false);
	}
	if (IsKeyPress('A'))
	{
		_move->RightMove(false);
	}
	if (IsKeyPress('D'))
	{
		_move->RightMove(); 
	}

	// �W�����v
	if (!m_Jump && IsKeyTrigger(VK_SPACE))
	{
		_jump->SetJump();
		m_Jump = true;
	}

	// �v���C���[��]
	//Rotate();

	// �l�W���߂��ɂ��邩
	if (!m_pCollisionObj)
		return;

	// �l�W�N���X�Ƀ_�E���L���X�g
	Screw* screw = dynamic_cast<Screw*>(m_pCollisionObj);

	// ��]����
	if (IsKeyPress('E'))
	{
		screw->ObjRightSpin();		// �E��]
	}
	// ����]
	else if (IsKeyPress('Q'))
	{
		screw->ObjRightSpin(false);	// ����]
	}
	else
	{
		screw->ResetTime();			// �o�ߎ��ԃ��Z�b�g
	}

	// ������
	m_pCollisionObj = nullptr;
}

// �l�W�̕t�߂ɂ��邩����`�F�b�N
void Player::OnScanner(GameObject* obj)
{
	// ���̂Ȃ�
	if (!obj)
	{
		m_pCollisionObj = nullptr;
		return;
	}

	// �^�O�擾
	string tag = obj->GetTag();
	// �l�W�Ȃ���̎擾
	if (tag == "Screw")
	{
		// �I�u�W�F�N�g�Z�b�g
		m_pCollisionObj = obj;
	}
	else if (tag == "PlayerCheckPoint")
	{
		// ���W�ݒ�
		m_ResetPos = obj->GetPos();
	}

}

// �����蔻�蔻��`�F�b�N
void Player::OnCollision(GameObject* obj)
{
	if (!obj)
	{
		m_Jump = true;
		return;
	}

	// �^�O�擾
	string tag = obj->GetTag();
	if (_jump->GetJump() && (tag == "Ground" || tag == "Gimmick" || tag == "MoveGimmick" || tag == "CheckPointPath"))
	{
		m_Jump = false;	// �W�����v�t���O��������
	}
}

// �S�[����̈ړ�����
void Player::MoveAfterGoal(GameObject* obj)
{
	//_move->FrontMove(false);

	// �f�[�^�^��ϊ�(�v�Z���₷���悤��)
	float3 pos = float3::Tofloat3(m_pos);
	float3 goalPos = float3::Tofloat3(obj->GetPos());

	// �v���C���[�̍����ɍ��킹��
	goalPos.y = pos.y;

	// ���̃`�F�b�N�|�C���g - ���݂̍��W
	float3 N = goalPos - pos;

	// �����𐳋K��
	N = N.normalize();

	// �ړ�����
	_move->DiagonalMove(N);
}

// ���͂���Ă���L�[���`�F�b�N
void Player::InputCheck()
{
	int count = 0;

	// ��������Ă邩�m�F
	if (IsKeyPress('W'))
	{
		count++;
	}
	if (IsKeyPress('S'))
	{
		count++;
	}
	if (IsKeyPress('A'))
	{
		count++;
	}
	if (IsKeyPress('D'))
	{
		count++;
	}

	// 2�ȏ㉟����Ă���ړ����x��������
	if (count >= 2)
	{
		_move->SetMove(DIAGONAL_SPEED);
	}
	else
	{
		_move->SetMove(DEFAULT_SPEED);
	}
}

// �v���C���[��]
void Player::Rotate()
{
	DirectX::XMFLOAT3 move = m_pos;
	move.x -= m_oldpos.x;
	move.y -= m_oldpos.y;
	move.z -= m_oldpos.z;

	//---�v���C���[�̉�]�p�x���v�Z
	float rotationAngle = atan2(-move.x, -move.z);

	//---�v���C���[�̉�]�s����X�V
	//m_DirectRad = rotationAngle;

	
	// ��]�擾
	//DirectX::XMVECTOR qRotate = DirectX::XMLoadFloat4(&m_quat);
	//
	//DirectX::XMMATRIX RotMat = DirectX::XMMatrixRotationQuaternion(qRotate);
	//
	//// ���ɍ��킹�ĉ�]
	//DirectX::XMVECTOR quat = DirectX::XMQuaternionRotationAxis(
	//	DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), DirectX::XMConvertToRadians(m_DirectRad)
	//);
	//
	//// �N�H�[�^�j�I���|���Z
	//qRotate = DirectX::XMQuaternionMultiply(qRotate, quat);
	//
	//// �p�x�X�V
	//DirectX::XMStoreFloat4(&m_quat, qRotate);
}

