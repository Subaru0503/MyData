///////////////////////////////////////
//
// �l�W���N���X
//
///////////////////////////////////////

// �C���N���[�h��
#include "Screw.h"

//----�}�l�[�W���[----
#include "SoundManager.h"	// �T�E���h�}�l�[�W���[

// �R���X�g���N�^
Screw::Screw(std::string name)
	: GameObject(name)
	, m_Multiplier(1)
	, m_SpinFlg(false)
	, m_SpinMaxPlayingSE(false)
{

	// �^�O�ݒ�
	m_tag = "Screw";

	// �����o�ϐ�������
	m_Nut = nullptr;

	//----�R���|�[�l���g�ǉ�----

	// �ړ�
	AddComponent<Move>();

	// ��]
	AddComponent<Spin>();

	// �����蔻��
	AddComponent<BoxCollider>();

	// 3D�`��
	AddComponent<ModelRenderer3D>();

	//----�R���|�[�l���g�擾----

	// �ړ�
	_move = GetComponent<Move>();

	// ��]
	_spin = GetComponent<Spin>();

	// �����蔻��
	_boxCollider = GetComponent<BoxCollider>();

	// 3D�`��
	_modelRenderer3D = GetComponent<ModelRenderer3D>();

	// �V�F�[�_�[�t�@�C��
	const char* file[] = {
		"VS_Object",
		"PS_TexColor",
	};

	// �V�F�[�_�[�Z�b�g
	_modelRenderer3D->SetShader(file);
	
	// �l�Z�b�g
	_boxCollider->SetScale(float3(0.4f, 0.4f, 0.4f));
}

// �f�X�g���N�^
Screw::~Screw()
{
}

// �X�V����
void Screw::Update()
{

}

// ������Ԃɖ߂�
// �I�u�W�F�N�g���V�[�����n�܂����Ƃ��̏�Ԃɖ߂�
void Screw::ResetState()
{
	// �������W�ɖ߂�
	m_pos = m_InitPos;

	// �p�x������
	m_quat = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
}

// ��]�֐�
void Screw::ObjRightSpin(bool Right)
{
	//----�ϐ��錾----

	// �Đ��I���t���O
	bool PlayEnd;

	// ���Ԋm�F
	if (!m_Nut)
	{
		MessageBox(NULL, "�i�b�g�̐ݒ肪����ĂȂ�", "Screw.cpp", MB_OK);
	}

	// ��]�t���O�グ
	m_SpinFlg = true;

	// �Đ��I���t���O���擾
	PlayEnd = SoundManager::GetInstance().CheckSoundEnd(SoundManager::ScrewSE::Spin);

	// �E��]
	if (m_Nut->GetPos().y <= m_pos.y && Right)
	{
		// Y���E��]
		_spin->YSpin();

		// �ړ��ʃZ�b�g
		_move->SetMove(_spin->GetScrewTravel());

		// �������ړ�
		_move->UPMove(false);
		
		// �Đ����ĂȂ�������
		if (PlayEnd)
		{
			// ��]SE
			SoundManager::GetInstance().playSound(SoundManager::ScrewSE::Spin);
		}

		// �񂵐؂���SE�Đ��σt���O��������
		m_SpinMaxPlayingSE = false;
	}
	// ����]
	else if(m_Nut->GetPos().y + 0.5f >= m_pos.y && !Right)
	{
		// Y������]
		_spin->YSpin(false);

		// �ړ��ʃZ�b�g
		_move->SetMove(_spin->GetScrewTravel());

		// ������ړ�
		_move->UPMove();

		// �Đ����ĂȂ�������
		if (PlayEnd)
		{
			// ��]SE
			SoundManager::GetInstance().playSound(SoundManager::ScrewSE::Spin);
		}

		// �񂵐؂���SE�Đ��σt���O��������
		m_SpinMaxPlayingSE = false;
	}
	// �Đ��t���O���������Ă���
	else if (!m_SpinMaxPlayingSE)
	{
		// �ő�܂ŉ񂵂�SE
		SoundManager::GetInstance().playSound(SoundManager::ScrewSE::SpinMax);

		// �񂵐؂���SE�Đ��σt���O���グ��
		m_SpinMaxPlayingSE = true;
	}
}
