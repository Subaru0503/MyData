///////////////////////////////////////
//
// �`�F�b�N�|�C���g�����Ɉړ�����M�~�b�N�N���X
//
// �o�^�����`�F�b�N�|�C���g��H���Ă���
//
///////////////////////////////////////

// �C���N���[�h�K�[�h
#ifndef __CHECK_POINT_PATH_H__
#define __CHECK_POINT_PATH_H__

// �C���N���[�h��
#include "GimmickBase.h"
#include <vector>
#include "float3.h"

// �R���|�[�l���g
#include "Move.h"	// �ړ�

// �N���X��`
class CheckPointPath : public GimmickBase
{
public:

	// �`�F�b�N�|�C���g�ɕK�v�ȏ����܂Ƃ߂�����
	struct MovePath
	{
		// �`�F�b�N�|�C���g���W
		float3 pos;

		// ���̃`�F�b�N�|�C���g
		MovePath* nextPoint;

		// ��O�̃`�F�b�N�|�C���g
		MovePath* prePoint;
	};

public:

	// �R���X�g���N�^
	CheckPointPath(std::string name = "CheckPointPath");

	// �f�X�g���N�^
	~CheckPointPath();

	// ������Ԃɖ߂�
	void ResetState();

	// �^�[�Q�b�g�I�u�W�F�N�g�̏���
	void Gimmick(int index, float rotY);

	// �ʏ�̃l�W���񂷕����Ƌt�����ɉ񂳂ꂽ�Ƃ��ɌĂ�
	void InvertGimmick(int index, float rotY);

	// �^�[�Q�b�g�̃`�F�b�N�|�C���g������
	inline void AllDeleteCheckPoint()
	{
		m_TargetCheckpoint = nullptr;
	}

	// �Z�b�g�֐�
	// �ړ��ʃZ�b�g
	inline void SetMove(float move)
	{
		m_Move = move;
	}

	// �`�F�b�N�|�C���g�̍��W��ݒ肷��
	inline void SetCheckPointPos(float3 pos)
	{
		MovePath movePath;

		// ���W�ݒ�
		movePath.pos = pos;

		// �`�F�b�N�|�C���g�Ƃ��ēo�^
		m_CheckPoint.push_back(movePath);
	}

	// �`�F�b�N�|�C���g�ɕK�v�ȏ���ݒ肷��
	inline void SetCheckPointInfo()
	{
		// �ڎw���`�F�b�N�|�C���g�ݒ�
		m_TargetCheckpoint = &m_CheckPoint[0];

		// int�^�Ƀf�[�^�^�ϊ�
		int index = (int)m_CheckPoint.size();

		for (int i = 0; i < index; i++)
		{
			// ���̃`�F�b�N�|�C���g�̃|�C���^��ݒ肷��
			m_CheckPoint[i].nextPoint = &m_CheckPoint[(i + 1) % index];

			// ��O�̃`�F�b�N�|�C���g�̃|�C���^��ݒ肷��
			m_CheckPoint[i].prePoint = &m_CheckPoint[(i + index - 1) % index];
		}
	}

private:

	// �ړ��M�~�b�N
	void MoveGimmick();

	// �t�����ړ��M�~�b�N
	void ReverseMoveGimmick();

private:
	//----�R���|�[�l���g----

	// �ړ��R���|�[�l���g
	Move* _move;

	// �H��`�F�b�N�|�C���g�̐�
	std::vector<MovePath>  m_CheckPoint;

	// ���ڎw���Ă���`�F�b�N�|�C���g
	MovePath* m_TargetCheckpoint;

	// �ړ���
	float m_Move;
};

#endif // __CHECK_POINT_PATH_H__