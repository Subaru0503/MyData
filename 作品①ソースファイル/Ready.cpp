//////////////////////////////
//
// �X�^�[�g����UI
//
//////////////////////////////

// �C���N���[�h��
#include "Ready.h"

// �}�l�[�W���[
#include "ShaderManager.h"	// �V�F�[�_�[�}�l�[�W���[
#include "SoundManager.h"	// �T�E���h�}�l�[�W���[

// �萔�E�}�N����`
#define SPIN_NUM (5)			 // ��]��
#define DELTA_SPIN (30.0f)		 // ��]��
#define FIRST_DELAY_TIME (1.0f)  // �A�j���[�V�����J�n��x�点�鎞��
#define SECOND_DELAY_TIME (0.1f) // ��]�A�j���[�V�����`�g�k�A�j���[�V�����܂ł̎���
#define THIRD_DELAY_TIME (0.1f)  // �g�k�A�j���[�V�����`�Q�[���X�^�[�g�܂ł̎���

// �R���X�g���N�^
Ready::Ready(std::string name)
	: GameObject(name)
{
	// �R���|�[�l���g�ǉ�
	AddComponent<ModelRenderer2D>();
	AddComponent<Move>();
	AddComponent<SpinAnimation>();

	// �R���|�[�l���g�擾
	_modelRenderer2D = GetComponent<ModelRenderer2D>();
	_move = GetComponent<Move>();
	_spinAnimation = GetComponent<SpinAnimation>();

	// �����o�ϐ�������
	_modelRenderer2D_param = _modelRenderer2D->GetParam();

	_modelRenderer2D->Load("Assets/Texture/Ready.png");

	// �l�Z�b�g
	m_pos.x = 640.0f;
	m_pos.y = 120.0f;
	m_scale.x = 300.0f;
	m_scale.y = 200.0f;
	m_quat = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	animKind = AnimKind::Before;
	m_Delay = FIRST_DELAY_TIME;
	m_Start = false;
	m_ScaleAnimFlg = false;

	_move->SetMove(2.0f);
	// ��]���ݒ�
	DirectX::XMFLOAT4 axis = DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f);
	_spinAnimation->SetAxis(axis);
	_spinAnimation->SetDeltaRot(DELTA_SPIN);
	//_spinAnimation->SetSpinNum(SPIN_NUM);
}

// �f�X�g���N�^
Ready::~Ready()
{

}

// �X�V����
void Ready::Update()
{
	// �A�j���[�V��������
	switch (animKind)
	{
	// ��]�A�j���[�V�����O�ɂ�鏈��
	case AnimKind::Before:
		BeforeSpinAnimation();
		break;
	// �ړ��A�j���[�V����+�e�N�X�`���ύX
	case AnimKind::Change:
		MoveAndTextureChangeAnimation();
		break;
	// �g�k�A�j���[�V����
	case AnimKind::Scale:
		ScaleAnimation();
		break;
	case AnimKind::Start:
		m_Start = true;
		_modelRenderer2D->SetDraw(false);
		animKind = AnimKind::None;
		break;
	}
}

// ��]�ړ��A�j���[�V�����O�ɂ�鏈��
void Ready::BeforeSpinAnimation()
{
	// �f�B���C���o�ߏ���
	if (m_Delay > 0.0f)
	{
		m_Delay -= 1.0f / 60.0f;
		// 0�Ȃ��]�A�j���[�V�����J�n
		if (m_Delay <= 0.0f)
		{
			m_Delay = 0.0f;
			_spinAnimation->SetSpinNum(SPIN_NUM);
			animKind = AnimKind::Change;	// �ړ��A�j���[�V����+�e�N�X�`���ύX�Ɉڂ�
		}
	}
}

// ��]�ړ��A�j���[�V����+�e�N�X�`���ύX
void Ready::MoveAndTextureChangeAnimation()
{
	bool PlayEnd = SoundManager::GetInstance().CheckSoundEnd(SoundManager::ScrewSE::Spin);
	_move->UPMove();
	// ���X�g���]�ɂȂ�����e�N�X�`����ύX����
	int spin = _spinAnimation->GetCurrentSpinNum();	// ���݂̉�]���擾
	if (spin == SPIN_NUM - 1)
	{
		_modelRenderer2D->Load("Assets/Texture/Go.png");
		animKind = AnimKind::Scale;	// �g�k�A�j���[�V�����Ɉڂ�
		m_Delay = SECOND_DELAY_TIME;
	}

	if (PlayEnd)
	{
		// ��]SE
		SoundManager::GetInstance().playSound(SoundManager::ScrewSE::Spin);
	}
}

// �g�k�A�j���[�V����
void Ready::ScaleAnimation()
{
	int rot = _spinAnimation->GetCurrentSpinNum();	// ���݂̉�]���擾
	if (!m_ScaleAnimFlg && m_Delay <= 0.0f && rot == SPIN_NUM)
	{
		m_scale.x += 40.0f;
		m_scale.y += 26.6f;
		if (m_scale.x >= 350.0f)
		{
			m_ScaleAnimFlg = true;
			m_Delay = THIRD_DELAY_TIME;
			// �Q�[���X�^�[�gSE
			SoundManager::GetInstance().playSound(SoundManager::SystemSE::Gstart);
		}
	}

	// �f�B���C���Ԃ��Ȃ��Ȃ�����
	if (m_ScaleAnimFlg && m_Delay <= 0.0f)
	{
		m_Delay = 0.0f;
		// �Q�[���X�^�[�g
		animKind = AnimKind::Start;
	}

	if (rot == SPIN_NUM)
	{
		m_Delay -= 1.0f / 60.0f;
	}
}
