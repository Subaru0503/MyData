///////////////////////////////////////
//
// �ꐶ�񂹂�l�W�N���X
//
///////////////////////////////////////

// �C���N���[�h�K�[�h
#ifndef __ENDLESS_H__
#define __ENDLESS_H__

// �C���N���[�h��
#include "Screw.h"


// �N���X��`
class EndLess : public Screw
{
public:

	// �R���X�g���N�^
	EndLess(std::string name = "EndLess");

	// �f�X�g���N�^
	~EndLess();

	// ��]�֐�
	virtual void ObjRightSpin(bool Right = true);


};

#endif // __ENDLESS_H__