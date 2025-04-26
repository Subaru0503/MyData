// �X�^�[�g���b�Z�[�W�N���X

// �C���N���[�h�K�[�h
#ifndef __START_MESSAGE_H__
#define __START_MESSAGE_H__

// �C���N���[�h��
#include "GameObject.hpp"
// �R���|�[�l���g
#include "ModelRenderer2D.h"
#include "OpacityController.h"

// �N���X��`
class StartMessage : public GameObject
{
public:
	StartMessage(std::string name = "StartMessage");	// �R���X�g���N�^
	~StartMessage();									// �f�X�g���N�^

	void Update();										// �X�V����

private:
	// �R���|�[�l���g
	ModelRenderer2D* _modelRenderer2D;
	Opacity* _opacity;

	// ���f�������_���[2D�`��p�����[�^
	ModelRenderer2D::Param* _modelRenderer2D_param;
};

#endif // __START_MESSAGE_H__