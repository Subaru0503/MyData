// �����x�ω��N���X

// �C���N���[�h�K�[�h
#ifndef __OPACITY_H__
#define __OPACITY_H__

// �C���N���[�h��
#include "Component.h"

#include "ModelRenderer2D.h"

// �N���X��`
class Opacity : public Component
{
public:
	Opacity();
	~Opacity();

	void Execute();		// �X�V

	// �Z�b�g�֐�
	inline void SetChangeValue(float value)
	{
		m_Value = value;
	}
	inline void SetParam(ModelRenderer2D::Param* param)
	{
		m_Param = param;
	}

private:
	void Blink();		// �����x�ω�
private:
	ModelRenderer2D::Param* m_Param;	// �p�����[�^
	float m_Value;		// �����x�ω���

	float m_Alpha;		// �����x
	bool m_ClearFlg;	// �����x�t���O
};

#endif // __OPACITY_H__