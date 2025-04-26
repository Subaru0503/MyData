// �Q�[���X�^�[�g�����N���X

// �C���N���[�h�K�[�h
#ifndef __START_H__
#define __START_H__

// �C���N���[�h��
#include "GameObject.hpp"
// �R���|�[�l���g
#include "ModelRenderer2D.h"
#include "OpacityController.h"

// �N���X��`
class Start : public GameObject
{
public:
	Start(std::string name = "Start");	// �R���X�g���N�^
	~Start();							// �f�X�g���N�^

	void Update();						// �X�V����

private:
	// �R���|�[�l���g
	ModelRenderer2D* _modelRenderer2D;
	Opacity* _opacity;

	// ���f�������_���[2D�`��p�����[�^
	ModelRenderer2D::Param* _modelRenderer2D_param;
};

#endif // __GAME_OVER_H__