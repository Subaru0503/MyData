///////////////////////////////////////
//
// �v���C���[�`�F�b�N�|�C���g�N���X
//
// ���̈ʒu�ɗ����烊�Z�b�g���Ƀv���C���[�������Ɉړ�������
//
///////////////////////////////////////

//----�C���N���[�h��----
#include "PlayerCheckPoint.h"

#include "Player.h"

// �R���X�g���N�^
PlayerCheckPoint::PlayerCheckPoint(std::string name)
	: GameObject(name)
{
	m_tag = "PlayerCheckPoint";
}

// �f�X�g���N�^
PlayerCheckPoint::~PlayerCheckPoint()
{
}
