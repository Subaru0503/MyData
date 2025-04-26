// ���ԃN���X

// �C���N���[�h�K�[�h
#ifndef __TIME_H__
#define __TIME_H__

// �C���N���[�h��
#include "GameObject.hpp"
// �R���|�[�l���g
#include "ModelRenderer2D.h"

#include "float3.h"

// �N���X��`
class Time : public GameObject
{
public:
	Time(std::string name = "Time");		// �R���X�g���N�^
	~Time();								// �f�X�g���N�^

	void Update();							// �X�V����

	void AlphaUpdate();						// �����x����

	// �Z�b�g�֐�
	inline void SetAnimeNo(int no)
	{
		_modelRenderer2D_param->animeNo = no;
	}

private:
	// �R���|�[�l���g
	ModelRenderer2D* _modelRenderer2D;

	// ���f�������_���[2D�`��p�����[�^
	ModelRenderer2D::Param* _modelRenderer2D_param;

	float m_Time;				// �o�ߎ���
	float m_Alpha;				// �A���t�@�l
};

#endif // __TIME_H__