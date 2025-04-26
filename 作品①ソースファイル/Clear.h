// �N���AUI�N���X

// �C���N���[�h�K�[�h
#ifndef __CLEAR_H__
#define __CLEAR_H__

// �C���N���[�h��
#include "GameObject.hpp"
#include "ModelRenderer2D.h"

// �N���X��`
class Clear : public GameObject
{
public:
	Clear(std::string name = "Clear");	// �R���X�g���N�^
	~Clear();									// �f�X�g���N�^

	void Update();										// �X�V����

	// �Q�b�g�֐�
	// �����x�̕ω����Ȃ��Ȃ��ĕ`��ł����t���O��Ԃ�
	inline bool GetDraw()
	{
		return m_Alpha >= 1.0f;
	}

private:
	// �R���|�[�l���g
	ModelRenderer2D* _modelRenderer2D;

	// ���f�������_���[2D�`��p�����[�^
	ModelRenderer2D::Param* _modelRenderer2D_param;

	float m_Time;				// �o�ߎ���
	float m_Alpha;				// �A���t�@�l
};

#endif // __GAME_OVER_H__