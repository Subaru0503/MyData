///////////////////////////////////////
//
// ���߂Ă���l�W���i�X�ɂ�ł����N���X
//
///////////////////////////////////////

// �C���N���[�h��
#include "LoosenRate.h"

// �R���X�g���N�^
LoosenRate::LoosenRate(std::string name)
	: Screw(name)
{

}

// �f�X�g���N�^
LoosenRate::~LoosenRate()
{
}

// �X�V����
void LoosenRate::Update()
{
	// �l�W���ɂޕ���
	// �v���C���[���񂵂Ă�Œ�����Ȃ���
	// �l�W���ő�܂Ŋɂ�łȂ�������
	if (!m_SpinFlg &&
		m_Nut->GetPos().y + 0.5f > m_pos.y)
	{
		LoosenRateLoosenRate();
	}


}

// �ɂޏ���
void LoosenRate::LoosenRateLoosenRate()
{
	_spin->YSpin(false, 0.3f);					// Y������]
	_move->SetMove(_spin->GetScrewTravel());	// �ړ��ʃZ�b�g
	_move->UPMove();							// ������ړ�
}
