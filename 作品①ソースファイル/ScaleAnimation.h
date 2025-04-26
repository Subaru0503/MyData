// �g�k�A�j���[�V�����@�\�N���X

// �C���N���[�h�K�[�h
#ifndef __SCALE_ANIMATION_H__
#define __SCALE_ANIMATION_H__

// �C���N���[�h��
#include "Component.h"

// �N���X��`
class ScaleAnimation : public Component
{
public:
	ScaleAnimation();	// �R���X�g���N�^
	~ScaleAnimation();	// �f�X�g���N�^

	void Execute();		// �X�V����

	void Scale();		// �g�k�A�j���[�V����

	// �Z�b�g�֐�
	inline void SetScaleRange(float range)
	{
		m_Scale = transform->GetScale();
		m_ScaleRange = range;
	}
	inline void SetMinScale(float min)
	{
		m_MinScale = min;
	}
private:
	DirectX::XMFLOAT3 m_Scale;
	float m_ScaleRange;		// �g�k�̕�
	float m_MinScale;		// �ŏ��X�P�[��
	int m_Frame;			// �t���[���J�E���g
};

#endif // __SCALE_ANIMATION_H__