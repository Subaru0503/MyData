// ShopText.h

//----�C���N���[�h�K�[�h----
#ifndef ___SHOP_TEXT_H___
#define ___SHOP_TEXT_H___

//----�C���N���[�h��----
#include <DirectXMath.h>
#include "Defines.h"
#include "Sprite.h"
#include "Texture.h"
#include "SoundManager.h"

#define MAX_LINE (3)	// �\���ő�s��

//----�N���X��`----
class CShopText
{

public:
	typedef struct
	{
		DirectX::XMFLOAT3 pos;										// ���S���W
		DirectX::XMFLOAT2 size;										// ���c�T�C�Y
		DirectX::XMFLOAT2 posTexCoord;								// �e�N�X�`�����W�i����j
		DirectX::XMFLOAT2 sizeTexCoord;								// �e�N�X�`���T�C�Y�i�E���j
		int	frame;													// �A�j���[�V�����Ǘ��t���[��
		int	currentAnimNo;											// �A�j���[�V�����R�}�ԍ��i���ォ��O�`�j
		int textNo;													// �e�L�X�g�R�}�ԍ�
		DirectX::XMFLOAT4 color;									// �J���[
		Texture* pTexture;											// �e�N�X�`��
	}ST_SHOP_TEXT_PARAM;											// �V���b�v�̉�ʂ��Ǘ�����p�����[�^�̍\����

public:
	CShopText(int text, CSoundMng *sound);													// �R���X�g���N�^
	~CShopText();													// �f�X�g���N�^
	void Update();													// �X�V
	void Draw();													// �`��
	void SetSize(float sizex, float sizey);							// �T�C�Y�Z�b�g
	void SetColor(float r, float g, float b, float a);				// �J���[�ݒ�
	void SetTextNo(int next, int element, int line);				// �e�L�X�g�i���o�[�Z�b�g
	ST_SHOP_TEXT_PARAM* GetText();									// �A�C�R���p�����[�^�Q�b�g�֐�
	void SetSound(CSoundMng* sound);

	int GetTextNo(int No);											// �e�L�X�g�R�}�ԍ�����
	int GetAnimeNo(int No);											// �A�j���[�V�����R�}�ԍ�����
	int GetLineNum();												// �s��������
private:
	ST_SHOP_TEXT_PARAM ShopText[3];
	CSoundMng* m_pSoundMng;

	// �e�L�X�g����p
	int m_nShopText;												// �e�L�X�g�t���O
	int m_nLineNum;													// ���s�ڂ��i�[����ϐ�
	int m_nLineNumElement;											// �z��̗v�f�w��p
};


#endif // ___SHOP_TEXT_H___

