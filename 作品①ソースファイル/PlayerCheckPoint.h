///////////////////////////////////////
//
// �v���C���[�`�F�b�N�|�C���g�N���X
//
// ���̈ʒu�ɗ����烊�Z�b�g���Ƀv���C���[�������Ɉړ�������
//
///////////////////////////////////////

//----�C���N���[�h�K�[�h----
#ifndef __PLAYER_CHECKPOINT_H__
#define __PLAYER_CHECKPOINT_H__

//----�C���N���[�h��----
#include "GameObject.hpp"

// �N���X��`
class PlayerCheckPoint : public GameObject
{
public:

	// �R���X�g���N�^
	PlayerCheckPoint(std::string name = "PlayerCheckPoint");

	// �f�X�g���N�^
	~PlayerCheckPoint();

private:

};

#endif // __PLAYER_CHECKPOINT_H__