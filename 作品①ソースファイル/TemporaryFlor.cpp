///////////////////////////////////////
//
// �ꎞ�I�ɏo�����鏰�M�~�b�N�N���X
//
// �l�W�̉񂵗ʂɂ���Ĉꎞ�I�ɏo������
// �񂵗ʂ������Ȃ������������
//
///////////////////////////////////////

// �C���N���[�h��
#include "TemporaryFloor.h"

// �R���X�g���N�^
TemporaryFloor::TemporaryFloor(std::string name)
	: GimmickBase(name)
{
	// �^�O�ݒ�
	m_tag = "TemporaryFloor";

	// �`��t���O��������
	_modelRenderer3D->SetDrawFlg(false);

	// �\���̏�񏉊���
	m_TemporaryFloorData.draw = false;
	m_TemporaryFloorData.nextObj = nullptr;
	m_TemporaryFloorData.preObj = nullptr;
}

// �f�X�g���N�^
TemporaryFloor::~TemporaryFloor()
{
}

// �^�[�Q�b�g�I�u�W�F�N�g�̏���
void TemporaryFloor::Gimmick(int index, float rotY)
{
	//----�ϐ��錾----

	// �l�W�̒��ߊ���
	float ratio;
	
	// �ڕW����
	float targetRatio;


	//----�����v�Z----

	// �l�W�̊����擾
	ratio = m_TargetScrew[index]->GetRatio();

	// �ڕW�����v�Z
	// �]�T����邽�߂Ɉ�O�Ƃ̊Ԋu�������󂯂�悤�Ɍv�Z����
	if (m_TemporaryFloorData.preObj)
	{
		targetRatio = 1.0f - 1.0f / ((float)m_TemporaryFloorData.totalNo * 2) * (m_TemporaryFloorData.myNo + m_TemporaryFloorData.preObj->myNo);
	}
	else
	{
		targetRatio = 1.0f - 1.0f / ((float)m_TemporaryFloorData.totalNo * 2) * m_TemporaryFloorData.myNo;
	}

	//----�S�[�������珇�ɏ��ƂȂ�I�u�W�F�N�g��`�悵�Ă���----

	// �ڕW�����ɒB���ĂȂ������珈�����Ȃ�
	if (targetRatio > ratio) return;

	// ��̏��̐ݒ肪����ĂȂ��Ƃ�
	// �������͐�̏����`�悳��Ă�����
	if (!m_TemporaryFloorData.nextObj || m_TemporaryFloorData.nextObj->draw)
	{
		// �`��t���O���グ��
		_modelRenderer3D->SetDrawFlg(true);
		m_TemporaryFloorData.draw = true;
	}
}

// �ʏ�̃l�W���񂷕����Ƌt�����ɉ񂳂ꂽ�Ƃ��ɌĂ�
void TemporaryFloor::InvertGimmick(int index, float rotY)
{
	//----�ϐ��錾----

	// �l�W�̒��ߊ���
	float ratio;

	// �ڕW����
	float targetRatio;


	//----�����v�Z----

	// �l�W�̊����擾
	ratio = m_TargetScrew[index]->GetRatio();

	// �ڕW�����v�Z
	// �]�T����邽�߂Ɉ�O�Ƃ̊Ԋu�������󂯂�悤�Ɍv�Z����
	if (m_TemporaryFloorData.preObj)
	{
		targetRatio = 1.0f - 1.0f / ((float)m_TemporaryFloorData.totalNo * 2) * (m_TemporaryFloorData.myNo + m_TemporaryFloorData.preObj->myNo);
	}
	else
	{
		targetRatio = 1.0f - 1.0f / ((float)m_TemporaryFloorData.totalNo * 2) * m_TemporaryFloorData.myNo;
	}


	//----�X�^�[�g�����珇�ɏ��ƂȂ�I�u�W�F�N�g�������Ă���----

	// �ڕW������؂��ĂȂ������珈�����Ȃ�
	if (targetRatio < ratio) return;

	// ��O�̏��̐ݒ肪����ĂȂ��Ƃ�
	// �������͈�O�̏���������Ă�����
	if (!m_TemporaryFloorData.preObj || !m_TemporaryFloorData.preObj->draw)
	{
		// �`��t���O��������
		_modelRenderer3D->SetDrawFlg(false);
		m_TemporaryFloorData.draw = false;
	}
}