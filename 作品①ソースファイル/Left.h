// �����UI�N���X

// �C���N���[�h�K�[�h
#ifndef __LEFT_H__
#define __LEFT_H__

// �C���N���[�h��
#include "GameObject.hpp"
#include "ModelRenderer2D.h"

// �N���X��`
class Left : public GameObject
{
public:
	Left(std::string name = "Left");	// �R���X�g���N�^
	~Left();							// �f�X�g���N�^

	void Update();						// �X�V����

	void Blink();						// �F�����ω�
private:
	// �R���|�[�l���g
	ModelRenderer2D* _modelRenderer2D;

	// ���f�������_���[2D�`��p�����[�^
	ModelRenderer2D::Param* _modelRenderer2D_param;

	bool m_MaxFlg;
};

#endif // __GAME_OVER_H__