// ���N���X

// �C���N���[�h�K�[�h
#ifndef __BIRD_H__
#define __BIRD_H__

// �C���N���[�h��
#include "GameObject.hpp"
// �R���|�[�l���g
#include "ModelRenderer2D.h"

#include "float3.h"

// �N���X��`
class Bird : public GameObject
{
public:
	Bird(std::string name = "Bird");			// �R���X�g���N�^
	~Bird();									// �f�X�g���N�^

	void Update();								// �X�V����

	void fly();									// ��s

	// �Z�b�g�֐�
	void SetVelocity(float velocity);			// ���x�ݒ�

	void SetAcceleration(float acceleration);	// �����x�ݒ�
private:
	// �R���|�[�l���g
	ModelRenderer2D* _modelRenderer2D;

	float m_Velocity;		// ���x
	float m_Acceleration;	// �����x
	float m_Time;			// ����
};

#endif // __BIRD_H__