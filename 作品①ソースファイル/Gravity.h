// �d�̓N���X

// �C���N���[�h�K�[�h
#ifndef __GRAVITY_H__
#define __GRAVITY_H__

// �C���N���[�h��
#include "Component.h"

// �N���X��`
class Gravity : public Component
{
public:
	
	void Execute();			// �X�V
private:
	float m_Gravity;		// �d��
};

#endif // __GRAVITY_H__