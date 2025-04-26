///////////////////////////////////////
//
// �`�F�b�N�|�C���g�����Ɉړ�����M�~�b�N�N���X
//
// �o�^�����`�F�b�N�|�C���g��H���Ă���
//
///////////////////////////////////////

// �C���N���[�h��
#include "CheckPointPath.h"

// �V�X�e��
#include "Input.h"
#include <math.h>

// �R���X�g���N�^
CheckPointPath::CheckPointPath(std::string name)
	: GimmickBase(name)
{
	m_tag = "CheckPointPath";

	//----�R���|�[�l���g�ǉ�----

	// �ړ�
	AddComponent<Move>();

	//----�R���|�[�l���g�擾----
	_move = GetComponent<Move>();
}

// �f�X�g���N�^
CheckPointPath::~CheckPointPath()
{
	// ���������폜
	std::vector<MovePath>().swap(m_CheckPoint);
}

// ������Ԃɖ߂�
// �I�u�W�F�N�g���V�[�����n�܂����Ƃ��̏�Ԃɖ߂�
void CheckPointPath::ResetState()
{
	// �������W�ɖ߂�
	m_pos = m_InitPos;

	// �����̖ڎw���`�F�b�N�|�C���g�ɐݒ�
	m_TargetCheckpoint = &m_CheckPoint[0];
}

// �^�[�Q�b�g�I�u�W�F�N�g�̏���
void CheckPointPath::Gimmick(int index, float rotY)
{
	// �`�F�b�N�|�C���g���ݒ肳��Ă��Ȃ������珈�����Ȃ�
	if (!m_TargetCheckpoint) return;

	// �ړ��ʃZ�b�g
	_move->SetMove(0.1f);

	// �ړ��M�~�b�N
	MoveGimmick();
}

// �ʏ�̃l�W���񂷕����Ƌt�����ɉ񂳂ꂽ�Ƃ��ɌĂ�
void CheckPointPath::InvertGimmick(int index, float rotY)
{
	// �`�F�b�N�|�C���g���ݒ肳��ĂȂ������珈�����Ȃ�
	if (!m_TargetCheckpoint) return;

	// �ړ��ʃZ�b�g
	_move->SetMove(0.1f);

	// �t�����Ɉړ��M�~�b�N
	ReverseMoveGimmick();
}

// �ړ��M�~�b�N
void CheckPointPath::MoveGimmick()
{
	// �f�[�^�^��ϊ�(�v�Z���₷���悤��)
	float3 pos = float3::Tofloat3(m_pos);

	// ���̃`�F�b�N�|�C���g - ���݂̍��W
	float3 N = m_TargetCheckpoint->pos - pos;

	// �`�F�b�N�|�C���g�܂ł̋������v�Z
	float distance = float3::distance(m_TargetCheckpoint->pos, pos);

	// �����𐳋K��
	N = N.normalize();

	// �ړ�����
	_move->DiagonalMove(N);

	if (distance <= 0.1f)
	{
		m_pos = float3::ToXMFLOAT3(m_TargetCheckpoint->pos);
		m_TargetCheckpoint = m_TargetCheckpoint->nextPoint;
	}
}

// �t�����ړ��M�~�b�N
void CheckPointPath::ReverseMoveGimmick()
{
	// �f�[�^�^��ϊ�(�v�Z���₷���悤��)
	float3 pos = float3::Tofloat3(m_pos);

	// ��O�̃`�F�b�N�|�C���g - ���݂̍��W
	float3 N = m_TargetCheckpoint->prePoint->pos - pos;

	// �`�F�b�N�|�C���g�܂ł̋������v�Z
	float distance = float3::distance(m_TargetCheckpoint->prePoint->pos, pos);

	// �����𐳋K��
	N = N.normalize();

	// �ړ�����
	_move->DiagonalMove(N);

	if (distance <= 0.1f)
	{
		m_pos = float3::ToXMFLOAT3(m_TargetCheckpoint->prePoint->pos);
		m_TargetCheckpoint = m_TargetCheckpoint->prePoint;
	}
}
