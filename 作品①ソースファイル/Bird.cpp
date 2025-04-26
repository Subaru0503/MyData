//////////////////////////////
//
// ��
//
//////////////////////////////

// �C���N���[�h��
#include "Bird.h"

// �R���X�g���N�^
Bird::Bird(std::string name)
	: GameObject(name)
{
	// �R���|�[�l���g�ǉ�
	AddComponent<ModelRenderer2D>();

	// �R���|�[�l���g�擾
	_modelRenderer2D = GetComponent<ModelRenderer2D>();

	// �e�N�X�`���ǂݍ���
	//_modelRenderer2D->Load("Assets/Texture/Bird.png");

	// �����o�ϐ�������
	m_Time = 0.0f;
	m_Velocity = 0.0f;
	m_Acceleration = 0.0f;

}

// �f�X�g���N�^
Bird::~Bird()
{
}

// �X�V����
void Bird::Update()
{
	fly();

	m_Time += 1.0f / 60.0f;
}

// ��s
void Bird::fly()
{
	m_pos.x += m_Velocity + (m_Acceleration *(m_Time * m_Time)) / 2.0f;				// ���W�ω�
	m_pos.y -= (m_Velocity / 16) + (m_Acceleration *(m_Time * m_Time)) / 2.0f;		// ���W�ω�

	if (m_pos.x >= 1500.0f)
	{
		m_pos.x = -300.0f;
		m_pos.y = 600.0f;
		m_Time = 0.0f;
	}
}

// ���x�ݒ�
void Bird::SetVelocity(float velocity)
{
	m_Velocity = velocity;
}

// �����x�ݒ�
void Bird::SetAcceleration(float acceleration)
{
	m_Acceleration = acceleration;
}
