//=================================================================
//
//	CountDown.h
//	�J�E���g�_�E��UI
//
//=================================================================

#ifndef __COUNT_DOWN_H__
#define __COUNT_DOWN_H__
#include "Sprite.h"
#include <DirectXMath.h>

// ========== �N���X ==========
class CCountDown
{
public:
	CCountDown();
	~CCountDown();
	void Update();
	void Draw();

private:
	typedef struct {
		int AnimeNo;						// UV�w��
		DirectX::XMFLOAT2 pos;				// ���W
		DirectX::XMFLOAT2 size;				// ���c�T�C�Y
		DirectX::XMFLOAT2 posTexCoord;		// �e�N�X�`�����W
		DirectX::XMFLOAT2 sizeTexCoord;		// �e�N�X�`���T�C�Y
		Texture* pTexture;					// �e�N�X�`��
		DirectX::XMFLOAT2 TextuerSize;		// �e�N�X�`���T�C�Y
		int phase;							// �A�j���[�V�����i�K
	}COUNT_UI;

private:
	COUNT_UI m_Count[2];					// UI
	int m_kind;								// �e�N�X�`���̎��
	int m_waitFrame;						// �҂�����
	DirectX::XMFLOAT2 m_textureSize;		// �e�N�X�`���̖{���T�C�Y
};

#endif // !__COUNT_DOWN_H__