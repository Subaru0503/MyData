// ��]�A�j���[�V�����@�\�N���X

// �C���N���[�h�K�[�h
#ifndef __SPIN_ANIMATION_H__
#define __SPIN_ANIMATION_H__

// �C���N���[�h��
#include "Component.h"

// �N���X��`
class SpinAnimation : public Component
{
public:
	SpinAnimation();	// �R���X�g���N�^
	~SpinAnimation();	// �f�X�g���N�^

	void Execute();		// �X�V����

	void Spin();		// ��]�A�j���[�V����

	// �Z�b�g�֐�
	// ��]���Z�b�g
	void SetSpinNum(int num);

	// ��]���ݒ�
	void SetAxis(DirectX::XMFLOAT4 axis);

	// ��]�ʐݒ�
	void SetDeltaRot(float rot);


	// �Q�b�g�֐�
	// ��]���擾
	int GetSpinNum();
	// ���݂̉�]���擾
	int GetCurrentSpinNum();

	// ��]���~�܂��Ă邩�擾
	bool GetStop();
	
private:
	int m_CurrentSpinNum;		// ���݉�]��
	int m_SpinNum;				// ��]��
	float m_Rot;				// ���v��]��
	float m_DeltaRot;			// ��]��
	DirectX::XMFLOAT4 m_Axis;	// ��]��
	bool m_SpinStop;			// ��]�X�g�b�v
};

#endif // __SPIN_ANIMATION_H__