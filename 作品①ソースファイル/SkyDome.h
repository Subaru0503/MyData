///////////////////////////////////////
//
// �X�J�C�h�[���N���X
//
// �w�i���f���̏���������
//
///////////////////////////////////////

//----�C���N���[�h�K�[�h----
#ifndef __SKY_DOME_H__
#define __SKY_DOME_H__

//----�C���N���[�h��----
#include "GameObject.hpp"

//----�R���|�[�l���g----
#include "ModelRenderer3D.h"	// 3D���f���`��

// �N���X��`
class SkyDome : public GameObject
{
public:

	// �R���X�g���N�^
	SkyDome(std::string name = "SkyDome");

	// �f�X�g���N�^
	~SkyDome();

	// �X�V����
	void Update();

	// ��]
	void Rot();

	// �Z�b�g�֐�
	inline void SetCamera(GameObject* cam)
	{
		pCamObj = cam;
		SetPos(pCamObj->GetPos());	// ���W���ꏏ�ɃZ�b�g
	}

private:
	//----�R���|�[�l���g----

	// 3D�`��R���|�[�l���g
	ModelRenderer3D* _modelRenderer3D;

	// �J�����I�u�W�F�N�g
	GameObject* pCamObj;
};

#endif // __SKY_DOME_H__