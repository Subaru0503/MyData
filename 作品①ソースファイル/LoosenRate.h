///////////////////////////////////////
//
// ���߂Ă���l�W���i�X�ɂ�ł����N���X
//
///////////////////////////////////////

// �C���N���[�h�K�[�h
#ifndef __LOOSENRATE_H__
#define __LOOSENRATE_H__

// �C���N���[�h��
#include "Screw.h"


// �N���X��`
class LoosenRate : public Screw
{
public:

	// �R���X�g���N�^
	LoosenRate(std::string name = "LoosenRate");

	// �f�X�g���N�^
	~LoosenRate();

	// �X�V����
	void Update();

	// �ɂޏ���
	void LoosenRateLoosenRate();


};

#endif // __LOOSENRATE_H__