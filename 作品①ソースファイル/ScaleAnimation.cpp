// �C���N���[�h��
#include "ScaleAnimation.h"

// �R���X�g���N�^
ScaleAnimation::ScaleAnimation()
	: m_Frame(0)
{
}

// �f�X�g���N�^
ScaleAnimation::~ScaleAnimation()
{
}

void ScaleAnimation::Execute()
{
	Scale();

	// �t���[���J�E���g
	m_Frame++;
}

void ScaleAnimation::Scale()
{
	float rate = (float)m_Frame / 120;
	float angle = 360.0f * rate;
	float radian = angle * 3.141592f / 180.0f;
	// 1�`-1�͈̔͂Ŋg�k����Ɖ摜�����]���Ă��܂��̂ŁA
	// 0�`1�͈̔͂Ɏ��܂�悤�ɕϊ�����(*0.5+0.5)

	// 1����-1�͈̔͂�-���Ȃ������߂ɂ�*0.5f��+0.5������΁|���Ȃ��Ȃ�1*0.5+0.5=1, -1*0.5+0.5=0
	float sinScaleX = sinf(radian)  * 0.5f + 0.5f;
	float sinScaleZ = sinf(radian + 3.14f)  * 0.5f + 0.5f;	// 180����(3.14f)sin�̔g�����炵��x��y���ł̓��������炵�Ă���															// -�ɂ��Ă��������ʂ͓�����


	m_Scale.x = sinScaleX * m_ScaleRange + m_MinScale;
	m_Scale.z = sinScaleZ * m_ScaleRange + m_MinScale;

	// �T�C�Y�Z�b�g
	transform->SetScale(m_Scale);
}
