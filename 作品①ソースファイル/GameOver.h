// �Q�[���I�[�o�[UI�N���X

// �C���N���[�h�K�[�h
#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__

// �C���N���[�h��
#include "GameObject.hpp"
#include "ModelRenderer2D.h"

// �N���X��`
class GameOver : public GameObject
{
public:
	GameOver(std::string name = "GameOver");	// �R���X�g���N�^
	~GameOver();									// �f�X�g���N�^

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