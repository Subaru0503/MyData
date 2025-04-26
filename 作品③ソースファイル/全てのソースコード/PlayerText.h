//=================================================================
//
//	PlayerText.h
//	�z�����ݎ��̃v���C���[�e�L�X�g�֘A
//
//=================================================================
#ifndef __PLAYER_TEXT_H__
#define __PLAYER_TEXT_H__

// ========== �C���N���[�h�� ==========
#include "Sprite.h"
#include <DirectXMath.h>
#include "ObjectManager.h"

// ========== �N���X ==========
class CPlayerText
{
public:
	enum kind {
		barabara,
		suikometa
	};

public:
	CPlayerText();
	~CPlayerText();
	void Update();
	void Draw();

	void SetDraw(kind kind);
	void SetObjMng(CObjectMng* pObjMng);

private:
	void Animation();
	void PopAnimation();

private:
	// ��x�����\���t���O
	int m_tree1;
	int m_tree2;
	int m_tree3;
	int m_rock1;
	int m_rock2;
	int m_rock3;
	int m_fence;
	int m_signBord;

	// �摜���
	DirectX::XMFLOAT2 m_pos;				// ���W
	DirectX::XMFLOAT2 m_size;				// ���c�T�C�Y
	DirectX::XMFLOAT2 m_posTexCoord;		// �e�N�X�`�����W
	DirectX::XMFLOAT2 m_sizeTexCoord;		// �e�N�X�`���T�C�Y
	Texture* m_pTexture;					// �e�N�X�`��
	DirectX::XMFLOAT2 m_TextureSize;		// �e�N�X�`���T�C�Y

	// �A�j���[�V�������
	int m_animeNo;							// UV�w��
	int m_animePhase;						// �A�j���[�V�����i�K
	int m_waitFrame;						// �\���I���܂ł̑҂�����

	CObjectMng* m_pObjMng;					// ���z�����݃t���O�EObjList�擾�p
	list<Object*> m_pObjList;				// �I�u�W�F�N�g���X�g�|�C���^
};

#endif // !__PLAYER_TEXT_H__


// �Z�ӂ�����
// �����o�����o������A�j���[�V����
// �����̂�݂����ɁA�E�[�̃v���C���[����݂����ďo�Ă���B������Ƒ傫���Ȃ��Ė߂�B�ՂɂՂɊ����o
// ���Ɉ��ʈړ�����A�j���[�V����
// ���ړ��ʂ������x�I�ɑ��₷�B������ƍs���߂��Ė߂�B�ՂɂՂɊ��B(�ł���΁A�߂�O�ɐi�s�����ɌX��(����)�A�j���[�V����)
// ���ł���A�j���[�V����
// �����̂�݂����ɁA������Ƒ傫���Ȃ��Ă��̂܂܂��̏�ŏ������Ȃ���ŁB

// �Z�e�L�X�g���A�j���[�V����
// �ΏۃI�u�W�F�N�g�C���X�g(�؂Ƃ���Ƃ�)�����A�j���[�V����
// �����S�����_�Ƃ���-45,45�x���炢�Ԃ��X��������B