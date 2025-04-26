//////////////////////////////
//
// �^�C�g�����b�Z�[�W
//
//////////////////////////////

// �C���N���[�h��
#include "TitleScrew.h"
#include "Input.h"

// �}�l�[�W���[
#include "SoundManager.h"	// �T�E���h�}�l�[�W���[

// �R���X�g���N�^
TitleScrew::TitleScrew(std::string name)
	: GameObject(name)
{
	// �R���|�[�l���g�ǉ�
	AddComponent<ModelRenderer2D>();
	AddComponent<Move>();
	AddComponent<Move2DAnimation>();
	AddComponent<SpinAnimation>();

	// �R���|�[�l���g�擾
	_modelRenderer2D = GetComponent<ModelRenderer2D>();
	_move = GetComponent<Move>();
	_move2DAnimation = GetComponent<Move2DAnimation>();
	_spinAnimation = GetComponent<SpinAnimation>();

	// ������
	m_TargetPos = float3(0.0f, 0.0f, 0.0f);
	m_SpinMaxPlayingSE = SoundState::CanPlay;

	// �l�Z�b�g
	_move->SetMove(0.4f);
}

// �f�X�g���N�^
TitleScrew::~TitleScrew()
{
}

// �X�V����
void TitleScrew::Update()
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

		// �l�W��]
		ScrewSpin();

		return;
	}

	// ��]�A�j���[�V�������̏���
	ApplyRotationSettings();
}

// �l�W���񂷏���
void TitleScrew::ScrewSpin()
{
	// �l�W����߂鏈��
	if (IsKeyPress('E') &&
		m_SpinMaxPlayingSE != SoundState::NotPlayMaxSE)
	{
		// �Đ��I���t���O���擾
		bool PlayEnd = SoundManager::GetInstance().CheckSoundEnd(SoundManager::ScrewSE::SpinMax);

		// �V�����ړ��͈�
		DirectX::XMFLOAT2 newMinPos = _move2DAnimation->GetMinPos();
		DirectX::XMFLOAT2 newMaxPos = _move2DAnimation->GetMaxPos();

		// �ړ���
		DirectX::XMFLOAT3 movePos;

		// �f�[�^�^��ϊ�(�v�Z���₷���悤��)
		float3 pos = float3::Tofloat3(m_pos);

		// �^�[�Q�b�g���W - ���݂̍��W
		float3 N = m_TargetPos - pos;

		// �^�[�Q�b�g���W�܂ł̋������v�Z
		float distance = float3::distance(m_TargetPos, pos);

		// ���ȉ��Ȃ珈�����Ȃ�
		if (distance <= 5.0f)
		{
			// �ő�܂ŉ񂵂�SE
			SoundManager::GetInstance().playSound(SoundManager::ScrewSE::SpinMax);

			// �ő�܂Œ��߂�SE���Đ��ł��Ȃ���Ԃɂ���
			m_SpinMaxPlayingSE = SoundState::NotPlayMaxSE;
			return;
		}

		// �����𐳋K��
		N = N.normalize();

		// �ړ�����
		_move->DiagonalMove(N);

		// �V�����ړ��͈͂��v�Z
		movePos = float3::ToXMFLOAT3(N * _move->GetMove());

		newMinPos.y += movePos.y;
		newMaxPos.y += movePos.y;

		// �ړ��͈͐ݒ�
		_move2DAnimation->SetMoveArea(newMinPos, newMaxPos);

		// �Đ��I�����Ă邩�m�F
		PlayEnd = SoundManager::GetInstance().CheckSoundEnd(SoundManager::ScrewSE::Spin);

		// �Đ��I�����Ă�����
		if (PlayEnd)
		{
			// ��]SE
			SoundManager::GetInstance().playSound(SoundManager::ScrewSE::Spin);
		}

		// �����Đ��ł����Ԃɂ���
		m_SpinMaxPlayingSE = SoundState::CanPlay;
	}
	// �l�W���ɂ߂�
	else if (IsKeyPress('Q') &&
		m_SpinMaxPlayingSE != SoundState::NotPlayMinSE)
	{
		// �Đ��I���t���O���擾
		bool PlayEnd = SoundManager::GetInstance().CheckSoundEnd(SoundManager::ScrewSE::SpinMax);

		// �V�����ړ��͈�
		DirectX::XMFLOAT2 newMinPos = _move2DAnimation->GetMinPos();
		DirectX::XMFLOAT2 newMaxPos = _move2DAnimation->GetMaxPos();

		// �ړ���
		DirectX::XMFLOAT3 movePos;

		// �f�[�^�^��ϊ�(�v�Z���₷���悤��)
		float3 pos = float3::Tofloat3(m_pos);

		// �^�[�Q�b�g���W - ���݂̍��W
		float3 N = m_TargetPos - pos;

		// �^�[�Q�b�g���W�܂ł̋������v�Z
		float distance = float3::distance(m_TargetPos, pos);

		// ���ȉ��Ȃ珈�����Ȃ�
		if (distance >= 20.0f)
		{
			// �ő�܂ŉ񂵂�SE
			SoundManager::GetInstance().playSound(SoundManager::ScrewSE::SpinMax);

			// �ő�܂Ŋɂ߂�SE���Đ��ł��Ȃ���Ԃɂ���
			m_SpinMaxPlayingSE = SoundState::NotPlayMinSE;
			return;
		}

		// �����𐳋K��
		N = N.normalize() * -1.0f;

		// �ړ�����
		_move->UPMove(false);

		// �V�����ړ��͈͂��v�Z
		movePos = float3::ToXMFLOAT3(N * _move->GetMove());

		newMinPos.y += movePos.y;
		newMaxPos.y += movePos.y;

		// �ړ��͈͐ݒ�
		_move2DAnimation->SetMoveArea(newMinPos, newMaxPos);

		// �Đ��I�����Ă邩�m�F
		PlayEnd = SoundManager::GetInstance().CheckSoundEnd(SoundManager::ScrewSE::Spin);

		// �Đ��I�����Ă�����
		if (PlayEnd)
		{
			// ��]SE
			SoundManager::GetInstance().playSound(SoundManager::ScrewSE::Spin);
		}

		// �����Đ��ł����Ԃɂ���
		m_SpinMaxPlayingSE = SoundState::CanPlay;
	}
}

// �A�j���[�V�����X�s�[�h�ݒ�
void TitleScrew::SetAnimationSpeed(DirectX::XMFLOAT2 speed)
{
	m_AnimationSpeed = speed;
}

// �l�W�����߂��Ƃ��Ɍ������ʒu��ݒ�
void TitleScrew::SetTargetPos(DirectX::XMFLOAT3 pos)
{
	m_TargetPos = float3::Tofloat3(pos);
}

// ��]�A�j���[�V�������ɂ�鏈��
void TitleScrew::ApplyRotationSettings()
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
