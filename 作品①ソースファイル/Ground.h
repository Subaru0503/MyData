///////////////////////////////////////
//
// �n�ʃN���X
//
// �X�e�[�W�̏�
//
///////////////////////////////////////

//----�C���N���[�h�K�[�h----
#ifndef __GROUND_H__
#define __GROUND_H__

//----�C���N���[�h��----
#include "GameObject.hpp"

//----�R���|�[�l���g----
#include "BoxCollider.h"		// �����蔻��
#include "ModelRenderer3D.h"	// 3D���f���`��

// �N���X��`
class Ground : public GameObject
{
public:

	// �R���X�g���N�^
	Ground(std::string name = "Ground");

	// �f�X�g���N�^
	~Ground();


	// �X�V����
	void Update();

private:
	//----�R���|�[�l���g----

	// �{�b�N�X�R���C�_�[�R���|�[�l���g
	BoxCollider* _boxCollider;

	// 3D�`��R���|�[�l���g
	ModelRenderer3D* _modelRenderer3D;

};

#endif // __GROUND_H__