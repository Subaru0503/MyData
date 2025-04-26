// �|�[�Y���b�Z�[�W�N���X

// �C���N���[�h�K�[�h
#ifndef __PAUSE_MOZI_H__
#define __PAUSE_MOZI_H__

// �C���N���[�h��
#include "GameObject.hpp"
// �R���|�[�l���g
#include "ModelRenderer2D.h"
#include "OpacityController.h"

// �N���X��`
class PauseMozi : public GameObject
{
public:
	PauseMozi(std::string name = "PauseMozi");	// �R���X�g���N�^
	~PauseMozi();							// �f�X�g���N�^

	void Update();						// �X�V����

private:
	// �R���|�[�l���g
	ModelRenderer2D* _modelRenderer2D;
	Opacity* _opacity;

	// ���f�������_���[2D�`��p�����[�^
	ModelRenderer2D::Param* _modelRenderer2D_param;
};

#endif // __GAME_OVER_H__