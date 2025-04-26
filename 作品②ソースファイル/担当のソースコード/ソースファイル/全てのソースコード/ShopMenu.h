// ShopMenu.h

//----�C���N���[�h�K�[�h----
#ifndef ___SHOP_MENU_H___
#define ___SHOP_MENU_H___

//----�C���N���[�h��----
#include <DirectXMath.h>
#include "Value.h"
#include "Sprite.h"
#include "Texture.h"
#include "ShopIcon.h"
#include "ShopText.h"
#include "Shop.h"
#include "Price.h"
#include "Suction.h"
#include "XController.h"
#include "SoundManager.h"
#include "UI.h"

//----�萔�E�}�N����`----
#define MAX_BASE_SHOP_MENU (8)										// �V���b�v��ʃx�[�X�e�N�X�`���̍ő吔
#define LEFT_ICON_POSX (222.5f)										// �V���b�v�̍���̍��WX
#define LEFT_ICON_POSY (260.0f)										// �V���b�v�̍���̍��WY
#define ICON_WIDTHX (260.0f)										// �A�C�R���ƃA�C�R���̕�X
#define ICON_WIDTHY (210.0f)										// �A�C�R���ƃA�C�R���̕�Y
#define LEFT_PRICE_POSX (174.5f)									// �����̍���̍��WX
#define LEFT_PRICE_POSY (331.0f)									// �����̍���̍��WY
#define PRICE_WIDTHX (283.0f)										// �A�C�R���ƃA�C�R���̕�X
#define PRICE_WIDTHY (210.0f)										// �A�C�R���ƃA�C�R���̕�Y

//----�N���X��`----
class CShopMenu
{

public:
	typedef struct
	{
		DirectX::XMFLOAT3 pos;										// ���S���W
		DirectX::XMFLOAT2 size;										// ���c�T�C�Y
		DirectX::XMFLOAT2 posTexCoord;								// �e�N�X�`�����W�i����j
		DirectX::XMFLOAT2 sizeTexCoord;								// �e�N�X�`���T�C�Y�i�E���j
		Texture* pTexture;											// �e�N�X�`��
	}ST_SHOP_MENU_PARAM;											// �V���b�v�̉�ʂ��Ǘ�����p�����[�^�̍\����

public:
	CShopMenu(int scene, CUI* ui,CSoundMng *sound);									// �R���X�g���N�^
	~CShopMenu();													// �f�X�g���N�^
	void Update(float tick);													// �X�V
	void Draw();													// �`��
	void Animetion(float tick);												// �A�j���[�V�����֐�
	void LineSet();													// �Z���t�Z�b�g
	void MoneyEnough();												// ����������Ă��邩��������
	void IconDraw();												// �J�X�^���A�C�R���`��
	void PageSetDraw();												// �y�[�W�`��
	void ALLCoupon();												// ���Z�b�g����Ă�S�ẴJ�X�^���p�[�c�̒l�i�\���ɓK�p
	void OneCoupon(int element);									// �w�肳�ꂽ��̃J�X�^���p�[�c�̒l�i�\���ɓK�p
	bool GetShop();													// �w����ʂ��I���t���O
	void SetMoney(int* Money);										// �������Z�b�g
	void SetCustom(int* Custom);									// �����J�X�^�}�C�Y�p�[�c�Z�b�g
	void SetItem(int* Item);										// �A�C�e���g�p�i�[�ϐ��Z�b�g
	void SetShopSuction(Suction* pSuction);							// �z�����݃N���X�Z�b�g
	void SetItemUse(int coupon);									// �A�C�e�����g�p���ꂽ��
	CShop* GetShopCustom();

private:
	//----�A�C�e���g�p�m�F�p----
	int m_nCoupon;		// �N�[�|���t���O
	int m_nFirst;		// �ŏ��̃��j���[�ɓK�p���ꂽ��
	//----���i�[----
	ST_SHOP_MENU_PARAM m_BaseShopMenu[MAX_BASE_SHOP_MENU];			// �x�[�X�V���b�v���j���[
	int m_nMaxCustom;												// �X�e�[�W���Ƃ̃J�X�^���ő吔
	int m_nStage;													// �X�e�[�W
	CShopIcon* m_pShopIcon[MAX_CUSTOM * 6];							// �A�C�R���N���X
	CShopIcon::ST_SHOP_ICON_PARAM* pShopIcon[MAX_CUSTOM * 6];		// �A�C�R���p�����[�^�i�[�p�ϐ�
	CShopText* m_pShopText;								// �p�[�c�������̓N���X
	CShopText::ST_SHOP_TEXT_PARAM* pShopText;			// �p�[�c�������̓p�����[�^�i�[�p�ϐ�
	bool m_bShop;													// �w����ʂ��I���t���O
	int m_nShopCustom[MAX_CUSTOM];									// �w����ʂɂ���J�X�^�}�C�Y�p�[�c�̏��
	CPrice* m_pPrice[MAX_CUSTOM];									// ���i�N���X
	//----���N���X�̏��----
	int* m_pnMoney;													// ������
	int* m_pnCustom;												// �����J�X�^�}�C�Y�p�[�c
	int* m_pnItem;													// �g�p�A�C�e��
	CShop* m_pShop;													// �V���b�v�@�\�N���X
	//----��������p----
	DirectX::XMFLOAT2 m_anPricePos[MAX_CUSTOM];						// ���i���W�ޔ�p
	int m_nCursor;													// �J�[�\���̍��W����
	int m_noldCursor;												// �J�[�\���̑O���W����
	int m_nTotalPage;												// �S���y�[�W��
	int m_nPage;													// ���݂̃y�[�W
	int m_nBuy;														// �������t���O
	int m_anBuy[MAX_CUSTOM];										// �w���ς݃t���O
	int m_anBuyCustom;												// �w�������J�X�^�����i�[�p
	int m_nLines;													// �Z���t�������؂�����
	int m_nMove;													// �J�[�\���𓮂�����
	int m_nNozzle;													// �m�Y��������������
	int m_nEnough[MAX_CUSTOM];										// ����������Ă���t���O
	//----�A�j���[�V�����p----
	float m_time;													// �A�j���[�V�����p�̌o�ߕb��
	int m_nOpenAnimetion;											// �V���b�v���J�������̃A�j���[�V�����t���O
	float m_fAnimeMoveX;											// �A�j���[�V�����p�ړ���X
	int m_nAnimeMoved;												// �������t���O
	int m_nFrame;													// �t���[���J�E���g�p�ϐ�
	float m_fRatio;													// �{��
	int m_nMAXRatio;												// �ő�{���t���O
	float m_fSizeRatio[MAX_CUSTOM];									// �T�C�Y�g�k
	int m_naMinRatio[MAX_CUSTOM];									// �Œ�{���t���O	
	//----��----
	CSoundMng* m_pSoundMng;
	bool m_SoundOne;
};


#endif // ___SHOP_MENU_H___

