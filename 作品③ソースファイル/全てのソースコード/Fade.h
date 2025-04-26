//=================================================================
//
//	Fade.h
//	�t�F�[�h�֘A
//
//=================================================================
#ifndef __FADE_H__
#define __FADE_H__

// ========== �C���N���[�h�� ==========
#include "Sprite.h"

// ========== �N���X ==========
class Fade
{
public:
	enum kind {
		WHITE = 0,
		BLACK,
		TIPS,
		PLANET,

		MAX_FADE,
		NONE,
	};

public:
	Fade();
	~Fade();
	void Update();
	void Draw();

	void Start(bool isIn, float time, kind kind);	// fade�J�n
	bool IsPlay();						// fade���s�����ۂ�
	float GetAlpha();					// Sound�t�F�[�h�̂���

private:
	float m_alpha;						// �����x(�t�F�[�h�i��)
	bool  m_isIn;						// �t�F�[�h�C���@or�@�t�F�[�h�A�E�g
	float m_time;						// �o�ߎ���
	float m_totalTime;					// �t�F�[�h�ɂ����鍇�v����
	kind  m_BGKind;						// �g�p����w�i�̎��

	Texture* m_pTexture[MAX_FADE];		// �e�N�X�`���f�[�^
};

#endif // !__FADE_H__