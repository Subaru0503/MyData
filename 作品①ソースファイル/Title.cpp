//////////////////////////////
//
// �^�C�g�����b�Z�[�W
//
//////////////////////////////

// �C���N���[�h��
#include "Title.h"
#include "Input.h"

// �}�l�[�W���[
#include "ShaderManager.h"	// �V�F�[�_�[�}�l�[�W���[
#include "SoundManager.h"	// �T�E���h�}�l�[�W���[

// �R���X�g���N�^
Title::Title(std::string name)
	: GameObject(name)
{
	// �R���|�[�l���g�ǉ�
	AddComponent<ModelRenderer2D>();
	AddComponent<Move2DAnimation>();
	AddComponent<SpinAnimation>();

	// �R���|�[�l���g�擾
	_modelRenderer2D = GetComponent<ModelRenderer2D>();
	_move2DAnimation = GetComponent<Move2DAnimation>();
	_spinAnimation = GetComponent<SpinAnimation>();
}

// �f�X�g���N�^
Title::~Title()
{
}

// �X�V����
void Title::Update()
{
	DirectX::XMFLOAT2 speed = _move2DAnimation->GetSpeed();

	// ��]�A�j���[�V�������I����Ă���
	if (_spinAnimation->GetStop())
	{
		// �ړ��X�s�[�h���ς���ĂȂ�������ς���
		if (speed.y != m_AnimationSpeed.y)
		{
			speed = m_AnimationSpeed;
			_move2DAnimation->SetSpeed(speed);
		}
		return;
	}

	// ��]�A�j���[�V�������̏���
	ApplyRotationSettings();
}

// �A�j���[�V�����X�s�[�h�ݒ�
void Title::SetAnimationSpeed(DirectX::XMFLOAT2 speed)
{
	m_AnimationSpeed = speed;
}

// ��]�A�j���[�V�������ɂ�鏈��
void Title::ApplyRotationSettings()
{
	// ���݂̉�]���擾
	float spin = _spinAnimation->GetCurrentSpinNum();
	// �ݒ肵����]���擾
	float spinNum = _spinAnimation->GetSpinNum();
	// �Đ��󋵎擾(true�Ȃ�Đ����ĂȂ�)
	bool PlayEnd = SoundManager::GetInstance().CheckSoundEnd(SoundManager::ScrewSE::Spin);

	// ��]���ōĐ�������Ȃ��Ƃ�
	if (spin < spinNum && PlayEnd)
	{
		// ��]SE�Đ�
		SoundManager::GetInstance().playSound(SoundManager::ScrewSE::Spin);
	}
}
