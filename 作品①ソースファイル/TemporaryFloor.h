///////////////////////////////////////
//
// �ꎞ�I�ɏo�����鏰�M�~�b�N�N���X
//
// �l�W�̉񂵗ʂɂ���Ĉꎞ�I�ɏo������
// �񂵗ʂ������Ȃ������������
//
///////////////////////////////////////

// �C���N���[�h�K�[�h
#ifndef __TEMPORARY_FLOOR_H__
#define __TEMPORARY_FLOOR_H__

// �C���N���[�h��
#include "GimmickBase.h"
#include <vector>
#include "float3.h"

// �N���X��`
class TemporaryFloor : public GimmickBase
{
public:

	// �ꎞ�I�ɏo�����鏰������������̂ɕK�v�ȏ��
	struct TemporaryFloorData
	{
		// �����̏o�����
		bool draw;

		// ���̏�
		TemporaryFloorData* nextObj;

		// ��O�̏�
		TemporaryFloorData* preObj;

		// �����̔ԍ�
		int myNo;

		// ���v��
		int totalNo;
	};

public:

	// �R���X�g���N�^
	TemporaryFloor(std::string name = "TemporaryFloor");

	// �f�X�g���N�^
	~TemporaryFloor();

	// �^�[�Q�b�g�I�u�W�F�N�g�̏���
	void Gimmick(int index, float rotY);

	// �ʏ�̃l�W���񂷕����Ƌt�����ɉ񂳂ꂽ�Ƃ��ɌĂ�
	void InvertGimmick(int index, float rotY);

	// �ꎞ�I�ɏo�����鏰������������̂ɕK�v�ȏ���ݒ肷��
	inline void SetTemporaryFloorInfo(TemporaryFloorData* pre, TemporaryFloorData* next, int no, int totalno)
	{
		// ��O�̏���ݒ肷��
		m_TemporaryFloorData.preObj = pre;

		// ���̏���ݒ肷��
		m_TemporaryFloorData.nextObj = next;

		// �����̔ԍ�
		m_TemporaryFloorData.myNo = no;

		// ���v��
		m_TemporaryFloorData.totalNo = totalno;
	}

	//----�Q�b�g�֐�----

	// �ꎞ�I�ɏo�����鏰������������̂ɕK�v�ȏ���Ԃ�
	inline TemporaryFloorData* GetTemporaryData()
	{
		return &m_TemporaryFloorData;
	}

private:

	// �ꎞ�I�ɏo�����鏰�ɕK�v�ȏ��
	TemporaryFloorData  m_TemporaryFloorData;

};

#endif // __TEMPORARY_FLOOR_H__