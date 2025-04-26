// �E���UI�N���X

// �C���N���[�h�K�[�h
#ifndef __RIGHT_H__
#define __RIGHT_H__

// �C���N���[�h��
#include "GameObject.hpp"
#include "ModelRenderer2D.h"

// �N���X��`
class Right : public GameObject
{
public:
	Right(std::string name = "Right");	// �R���X�g���N�^
	~Right();							// �f�X�g���N�^

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