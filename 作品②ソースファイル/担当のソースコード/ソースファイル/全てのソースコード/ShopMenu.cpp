// ShopMenu.cpp

//----�C���N���[�h��----
#include "ShopMenu.h"
#include "SceneGame.h"
#include "Input.h"
#include "EasingFunction.h"

//----�萔�E�}�N����`----
//----����----
#define TEXT_ANIM_SHOP_MENU_NO	(19)								// �A�j���[�V�����i���o�[
#define SELECT_TEXT_ANIM_SHOP_MENU_NO	(18)						// �A�j���[�V�����i���o�[
#define ENTERING_LINE (1)											// ���X�Z���t
#define FIRST_LINE (1)												// 1�s��
#define SECOND_LINE (2)												// 2�s��
#define THIRD_LINE (3)												// 3�s��
#define FORCE_LINE (4)												// 4�s��
//----���ʃV�[��----
#define WINDOW_POSX (372.5f)										// �V���b�v�E�B���h�E���WX
#define WINDOW_POSY (350.0f)										// �V���b�v�E�B���h�E���WY
#define WINDOW_START_POSY (-420.0f)									// �V���b�v�E�B���h�E�ŏ��̍��WY
#define WINDOW_START_POSY (-420.0f)									// �V���b�v�E�B���h�E�ŏ��̍��WY
#define MERCHANT_START_POSX (1700.0f)										// ���l�̗����G���WX
#define MERCHANT_START_POSY (-450.0f)										// ���l�̗����G���WX
#define MERCHANT_POSX (935.0f)										// ���l�̗����G���WX
#define MERCHANT_POSY (323.0f)										// ���l�̗����G���WY
//#define Merchant_START_POSY (-130.0f)								// ���͘g�ŏ��̍��WY
#define LINE_FRAME_POSX (980.0f)									// ���͘g���WX
#define LINE_FRAME_POSY (624.0f)									// ���͘g���WY
#define LINE_FRAME_START_POSY (-130.0f)								// ���͘g�ŏ��̍��WY
#define LINE_FRAME_START_POSX (1400.0f)								// ���͘g�ŏ��̍��WY
#define DOWN_ARROW_POSX (1225.0f)									// �������WX
#define DOWN_ARROW_POSY (665.0f)									// �������WY
#define DOWN_ARROW_START_POSY (-80.0f)								// �����ŏ��̍��WY
#define RIGHT_ARROW_POSX (610.0f)									// �E���������WX
#define LEFT_ARROW_POSX (80.0f)										// �����������WX
#define ARROW_POSY (370.0f)											// �����WY
//----�Z���N�g�V�[��----
#define SELECT_LEFT_ICON_POSX (222.5f)										// �V���b�v�̍���̍��WX
#define SELECT_LEFT_ICON_POSY (255.0f)										// �V���b�v�̍���̍��WY
#define SELECT_ICON_WIDTHX (260.0f)									// �A�C�R���ƃA�C�R���̕�X
#define SELECT_ICON_WIDTHY (230.0f)									// �A�C�R���ƃA�C�R���̕�Y
#define SELECT_ICON_SiZEX (245.0f)											// �A�C�R���T�C�YX
#define SELECT_ICON_SiZEY (225.0f)											// �A�C�R���T�C�YY
#define SELECT_SHOP (0)												// �Z���N�g�V���b�v
#define SELECT_ICON_KIND (3)										// �Z���N�g�V�[���A�C�R���̎��
#define DRINK_KOMA_NO (0)											// �h�����N�̃R�}
#define SELECT_NOZZLE_KOMA_NO (3)									// �m�Y�������̃R�}
#define TIMER_KOMA_NO (6)											// �^�C�}�[�̃R�}
#define COUPON_KOMA_NO (9)											// �N�[�|���̃R�}
#define DRINK_LINE (6)												// �h�����N�̃Z���t
#define NOZZLE_STRONG_LINE (9)										// �m�Y�������A�C�e���̃Z���t
#define TIMER_LINE (12)												// ���ԉ����A�C�e���̃Z���t
#define COUPON_LINE (14)											// �N�[�|���A�C�e���̃Z���t
#define SELECT_BUY_LINE (18)										// �w��
//----�Q�[���V�[��----
#define ICON_SiZEX (245.0f)											// �A�C�R���T�C�YX
#define ICON_SiZEY (235.0f)											// �A�C�R���T�C�YY
#define GAME_SHOP (1)												// �Q�[�����V���b�v
#define ICON_KIND (5)												// �A�C�R���̎�ސ�
#define DRILL_KOMA_NO (9)											// �h�����̃R�}
#define SAW_KOMA_NO (12)											// �̂�����̃R�}
#define HAMMER_KOMA_NO (15)											// �n���}�[�̃R�}
#define BOOTS_KOMA_NO (0)											// �u�[�c�̃R�}
#define NOZZLE_KOMA_NO (3)											// �m�Y���̃R�}
#define HEAT_RESISTANT_KOMA_NO (6)									// �ϔM�J�X�^���̃R�}
#define SAW_LINE (11)												// �̂�����̃Z���t
#define DRILL_LINE (5)												// �h�����̃Z���t
#define HAMMER_LINE (8)												// �h�����̃Z���t
#define NOZZLE_LINE (20)											// �m�Y���̃Z���t
#define BOOTS_LINE (17)												// �u�[�c�̃Z���t
#define HEAT_RESISTANT_LINE (23)									// �ωΑ��u�̃Z���t
#define BUY_LINE (27)												// �w���̃Z���t
#define BUY_CHECK_LINE (26)											// �w���m�F�̃Z���t
//----����----
#define PAGE_SPLIT_X (4)											// ��
#define PAGE_SPLIT_Y (4)											// �c
//----�A�j���[�V�����p----
#define ANIMETION_SECONDS (0.5f)									// �Z�b�����ăA�j���[�V����
#define DOWN_SPEED (30.0f)											// �~��Ă���X�s�[�h
#define SHOP_RATIO (0.004f)											// �g�k�X�s�[�h
#define ENOUGH_MAX_RATIO (1.08f)									// ������������Ă��鎞�̍ő�{��
#define NOT_ENOUGH_MAX_RATIO (1.04f)								// ������������Ă��Ȃ����̍ő�{��
#define ENOUGH_MIN_RATIO (0.92)									// ������������Ă��鎞�̍ŏ��{��
#define NOT_ENOUGH_MIN_RATIO (0.96)								// ������������Ă��Ȃ����̍ŏ��{��
#define SIZE_RATIO (0.5f)											// �T�C�Y�����p
#define ICON_RATIO (0.09f)											// �A�C�R���{��
#define SOLD_OUT_RATIO (0.7f)										// ����؂�A�C�R���̔{��

//----�A�C�e���g�p����----
#define SHOP_COUPON (0.8f)											// ������

CShopMenu::CShopMenu(int scene, CUI* ui, CSoundMng *sound)	// �R���X�g���N�^
	: m_pShopIcon{ nullptr }
	, pShopIcon{ nullptr }
	, m_pShopText{ nullptr }
	, m_bShop(true)
	, m_nShopCustom{ 0, 0, 0, 0, 0, 0 }
	, m_nCursor(1)
	, m_noldCursor(1)
	, m_pnMoney(nullptr)
	, m_pnCustom(nullptr)
	, m_pShop(nullptr)
	, m_pPrice{ nullptr }
	, m_nTotalPage(1)
	, m_nPage(1)
	, m_nBuy(0)
	, m_anBuy{ 0, 0, 0, 0, 0, 0, }
	, m_nLines(0)
	, m_nMove(0)
	, m_nNozzle(0)
	, m_fRatio(1.0f)
	, m_nMAXRatio(0)
	, m_fSizeRatio{ 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f }
	, m_naMinRatio{ 0, 0, 0, 0, 0, 0 }
	, m_nEnough{ 0 }
	, m_nCoupon(0)
	, m_nFirst(0)
	, m_nOpenAnimetion(1)
	, m_fAnimeMoveX(0.1f)
	, m_nAnimeMoved(0)
	, m_nFrame(0)
	, m_time(0.0f)
{
	m_pShop = new CShop();
	m_pShop->SetUI(ui);

	m_pSoundMng = sound;
	//----�x�[�X�e�N�X�`���p�����[�^�ݒ�----
	for (int i = 0; i < MAX_BASE_SHOP_MENU; i++)
	{
		m_BaseShopMenu[i].posTexCoord = DirectX::XMFLOAT2(0.0f, 0.0f);	// �e�N�X�`�����W�ݒ�
		m_BaseShopMenu[i].sizeTexCoord = DirectX::XMFLOAT2(1.0f, 1.0f);	// �e�N�X�`���T�C�Y�ݒ�
		m_BaseShopMenu[i].pTexture = nullptr;							// �e�N�X�`��������
	}

	//----�x�[�X�e�N�X�`���𓮓I�m��----
	for (int i = 0; i < MAX_BASE_SHOP_MENU; ++i)
	{
		m_BaseShopMenu[i].pTexture = new Texture();
	}

	//----�x�[�X�e�N�X�`���ǂݍ���----
	//----���l�̗����G----
	if (FAILED(m_BaseShopMenu[0].pTexture->Create("Assets/Texture/Merchant.png")))
	{
		MessageBox(NULL, "ShopMenu.cpp Merchant.png", "Error", MB_OK);
	}
	//----���----
	if (FAILED(m_BaseShopMenu[1].pTexture->Create("Assets/Texture/�V���b�v�E�B���h�E.png")))
	{
		MessageBox(NULL, "ShopMenu.cpp �V���b�v�E�B���h�E.png", "Error", MB_OK);
	}
	//----���͘g----
	if (FAILED(m_BaseShopMenu[2].pTexture->Create("Assets/Texture/LineWindow.png")))
	{
		MessageBox(NULL, "ShopMenu.cpp LineWindow.png", "Error", MB_OK);
	}
	//----���----
	if (FAILED(m_BaseShopMenu[3].pTexture->Create("Assets/Texture/nikukyu.png")))
	{
		MessageBox(NULL, "ShopMenu.cpp nikukyu.png", "Error", MB_OK);
	}
	//----�E���----
	if (FAILED(m_BaseShopMenu[4].pTexture->Create("Assets/Texture/Right.png")))
	{
		MessageBox(NULL, "ShopMenu.cpp Right.png", "Error", MB_OK);
	}
	//----����----
	if (FAILED(m_BaseShopMenu[5].pTexture->Create("Assets/Texture/UI_number4.png")))
	{
		MessageBox(NULL, "ShopMenu.cpp UI_number4.png", "Error", MB_OK);
	}
	//----�����----
	if (FAILED(m_BaseShopMenu[6].pTexture->Create("Assets/Texture/Left.png")))
	{
		MessageBox(NULL, "ShopMenu.cpp Left.png", "Error", MB_OK);
	}
	//----���l�̗����G----
	m_BaseShopMenu[0].size = DirectX::XMFLOAT2(m_BaseShopMenu[0].pTexture->GetWidth(),
		m_BaseShopMenu[0].pTexture->GetHeight());				// �T�C�Y�ݒ�
	m_BaseShopMenu[0].pos = DirectX::XMFLOAT3(MERCHANT_POSX, MERCHANT_POSY, 0.0f);	// ���W�ݒ�

	//----���----
	m_BaseShopMenu[1].size = DirectX::XMFLOAT2(m_BaseShopMenu[1].pTexture->GetWidth() * 0.625f
		, m_BaseShopMenu[1].pTexture->GetHeight() * 0.625f);			// �T�C�Y�ݒ�
	m_BaseShopMenu[1].pos = DirectX::XMFLOAT3(WINDOW_POSX, WINDOW_START_POSY, 0.0f);	// ���W�ݒ�

	//----���͘g----
	m_BaseShopMenu[2].size = DirectX::XMFLOAT2(m_BaseShopMenu[2].pTexture->GetWidth() * 0.99f,
		m_BaseShopMenu[2].pTexture->GetHeight() * 0.99f);				// �T�C�Y�ݒ�
	m_BaseShopMenu[2].pos = DirectX::XMFLOAT3(LINE_FRAME_POSX,LINE_FRAME_POSY, 0.0f);	// ���W�ݒ�

	//----�����----
	m_BaseShopMenu[3].size = DirectX::XMFLOAT2(m_BaseShopMenu[3].pTexture->GetWidth() * 0.2f
		, m_BaseShopMenu[3].pTexture->GetHeight() * 0.2f);
	m_BaseShopMenu[3].pos = DirectX::XMFLOAT3(DOWN_ARROW_POSX, DOWN_ARROW_START_POSY, 0.0f);

	//----�X���b�V��---
	m_BaseShopMenu[5].size = DirectX::XMFLOAT2(m_BaseShopMenu[5].pTexture->GetWidth() * 0.12f,
		m_BaseShopMenu[5].pTexture->GetHeight() * 0.12f);
	m_BaseShopMenu[5].sizeTexCoord = DirectX::XMFLOAT2(1.0f / PAGE_SPLIT_X, 1.0f / PAGE_SPLIT_Y);	// �e�N�X�`���T�C�Y�ݒ�
	m_BaseShopMenu[5].posTexCoord = DirectX::XMFLOAT2(m_BaseShopMenu[5].sizeTexCoord.x * (13 % PAGE_SPLIT_X)
		, m_BaseShopMenu[5].sizeTexCoord.y * (13 / PAGE_SPLIT_X));	// �e�N�X�`�����W�ݒ�

	m_nStage = scene;



	//----�X�e�[�W���Ƃ̃J�X�^���������p��----
	switch (m_nStage)
	{
	case 0:
		// �X�e�[�W�ő�J�X�^���ő吔���
		m_nMaxCustom = 4;
		m_nTotalPage = 1;

		//----���̓e�N�X�`���𓮓I�m��----
		m_pShopText = new CShopText(SELECT_SHOP, m_pSoundMng);
		pShopText = m_pShopText->GetText();	// �p�����[�^���
		pShopText->pTexture = new Texture();
		//m_pShopText->SetSound(m_pSoundMng);

		//----���̓e�N�X�`���ǂݍ���----
		// �e�L�X�g
		if (FAILED(pShopText->pTexture->Create("Assets/Texture/SelectShopText.png")))
		{
			MessageBox(NULL, "ShopMenu.cpp SelectShopText.png", "Error", MB_OK);
		}
		m_pShopText->SetSize(pShopText->pTexture->GetWidth(), pShopText->pTexture->GetHeight());	// �T�C�Y�ݒ�

		//----����̃A�C�R��----
		// �h�����N
		for (int i = 0; i < SELECT_ICON_KIND; i++)
		{
			// �ʏ�A�I���A�A�C�R���̏��ɓ���
			m_pShopIcon[i] = new CShopIcon(SELECT_LEFT_ICON_POSX, SELECT_LEFT_ICON_POSY, 0.0f, DRINK_KOMA_NO + i, m_nStage);
			pShopIcon[i] = m_pShopIcon[i]->GetIcon();												// �p�����[�^���
			pShopIcon[i]->pTexture = new Texture();
			if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/�Z���N�g�A�C�e��.png")))	// �J�X�^���A�C�R��
			{
				MessageBox(NULL, "ShopMenu.cpp �Z���N�g�A�C�e��.png", "Error", MB_OK);
			}
			m_pShopIcon[i]->SetSize(SELECT_ICON_SiZEX,			// �T�C�Y�ݒ�
				SELECT_ICON_SiZEY);
		}

		m_nShopCustom[0] = Item::DRINK;													// �V���b�v�ɂ���A�C�e�����
		m_pPrice[0] = new CPrice(LEFT_PRICE_POSX - 10.0f, LEFT_PRICE_POSY, 0.0f, PRICE_DRINK);// ���i���

		//----�E��̃A�C�R��----
		//	�m�Y������
		for (int i = SELECT_ICON_KIND; i < SELECT_ICON_KIND * 2; i++)
		{
			// �ʏ�A�I���A�A�C�R���̏��ɓ���
			m_pShopIcon[i] = new CShopIcon(SELECT_LEFT_ICON_POSX + SELECT_ICON_WIDTHX,
				SELECT_LEFT_ICON_POSY, 0.0f, SELECT_NOZZLE_KOMA_NO + i - SELECT_ICON_KIND, m_nStage);
			pShopIcon[i] = m_pShopIcon[i]->GetIcon();									// �p�����[�^���
			pShopIcon[i]->pTexture = new Texture();
			if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/�Z���N�g�A�C�e��.png")))	// �J�X�^���A�C�R��
			{
				MessageBox(NULL, "ShopMenu.cpp �Z���N�g�A�C�e��.png", "Error", MB_OK);
			}
			m_pShopIcon[i]->SetSize(SELECT_ICON_SiZEX,			// �T�C�Y�ݒ�
				SELECT_ICON_SiZEY);
		}
		m_nShopCustom[1] = Item::NOZZLE;														// �V���b�v�ɂ���A�C�e�����
		m_pPrice[1] = new CPrice(LEFT_PRICE_POSX + PRICE_WIDTHX - 35.0f,						// ���i���
			LEFT_PRICE_POSY, 0.0f, PRICE_NOZZLE);

		//----�����̃A�C�R��----
		// ���ԉ���
		for (int i = SELECT_ICON_KIND * 2; i < SELECT_ICON_KIND * 3; i++)
		{
			// �ʏ�A�I���A�A�C�R���̏��ɓ���
			m_pShopIcon[i] = new CShopIcon(SELECT_LEFT_ICON_POSX,
				SELECT_LEFT_ICON_POSY + SELECT_ICON_WIDTHY - 5.0f, 0.0f, TIMER_KOMA_NO + i - SELECT_ICON_KIND * 2, m_nStage);
			pShopIcon[i] = m_pShopIcon[i]->GetIcon();												// �p�����[�^���
			pShopIcon[i]->pTexture = new Texture();
			if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/�Z���N�g�A�C�e��.png")))	// �J�X�^���A�C�R��
			{
				MessageBox(NULL, "ShopMenu.cpp �Z���N�g�A�C�e��.png", "Error", MB_OK);
			}
			m_pShopIcon[i]->SetSize(SELECT_ICON_SiZEX,			// �T�C�Y�ݒ�
				SELECT_ICON_SiZEY);
		}

		m_nShopCustom[2] = Item::TIMER;											// �V���b�v�ɂ���A�C�e�����
		m_pPrice[2] = new CPrice(LEFT_PRICE_POSX, LEFT_PRICE_POSY + PRICE_WIDTHY + 15.0f,	// ���i���
			0.0f, PRICE_TIMER);

		//----�E���̃A�C�R��----
		// �N�[�|��
		for (int i = SELECT_ICON_KIND * 3; i < SELECT_ICON_KIND * 4; i++)
		{
			// �ʏ�A�I���A�A�C�R���̏��ɓ���
			m_pShopIcon[i] = new CShopIcon(SELECT_LEFT_ICON_POSX + SELECT_ICON_WIDTHX,
				SELECT_LEFT_ICON_POSY + SELECT_ICON_WIDTHY, 0.0f, COUPON_KOMA_NO + i - SELECT_ICON_KIND * 3, m_nStage);
			pShopIcon[i] = m_pShopIcon[i]->GetIcon();									// �p�����[�^���
			pShopIcon[i]->pTexture = new Texture();
			if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/�Z���N�g�A�C�e��.png")))	// �J�X�^���A�C�R��
			{
				MessageBox(NULL, "ShopMenu.cpp �Z���N�g�A�C�e��.png", "Error", MB_OK);
			}
			m_pShopIcon[i]->SetSize(SELECT_ICON_SiZEX,			// �T�C�Y�ݒ�
				SELECT_ICON_SiZEY);
		}
		m_nShopCustom[3] = Item::COUPON;												// �V���b�v�ɂ���A�C�e�����
		m_pPrice[3] = new CPrice(LEFT_PRICE_POSX + PRICE_WIDTHX - 20.0f,						// ���i���
			LEFT_PRICE_POSY + PRICE_WIDTHY + 15.0f,
			0.0f, PRICE_COUPON);
		break;
	case 1:
	case 2:
	case 3:
		// �X�e�[�W�ő�J�X�^���ő吔���
		if (m_nStage != 3)
		{
			m_nMaxCustom = 5;
		}
		else
		{
			m_nMaxCustom = 6;
		}
		// ���y�[�W��
		m_nTotalPage = 2;

		//----���----
		m_BaseShopMenu[4].size = DirectX::XMFLOAT2(m_BaseShopMenu[4].pTexture->GetWidth()
			, m_BaseShopMenu[4].pTexture->GetHeight());
		m_BaseShopMenu[4].pos = DirectX::XMFLOAT3(RIGHT_ARROW_POSX, ARROW_POSY, 0.0f);

		//----�A�C�R���A���̓e�N�X�`���𓮓I�m��----
		m_pShopText = new CShopText(GAME_SHOP, m_pSoundMng);
		pShopText = m_pShopText->GetText();	// �p�����[�^���
		pShopText->pTexture = new Texture();

		//----���̓e�N�X�`���ǂݍ���----
		// �e�L�X�g
		if (FAILED(pShopText->pTexture->Create("Assets/Texture/ShopText.png")))
		{
			MessageBox(NULL, "ShopMenu.cpp ShopText.png", "Error", MB_OK);
		}
		m_pShopText->SetSize(pShopText->pTexture->GetWidth(), pShopText->pTexture->GetHeight());	// �T�C�Y�ݒ�

		//----����̃A�C�R��----
		// �̂�����
		for (int i = 0; i < ICON_KIND; i++)
		{
			// �ʏ�A�I���A�A�C�R���A����؂�A����؂�I���̏��ɓ���
			if (i != 2)
			{
				m_pShopIcon[i] = new CShopIcon(LEFT_ICON_POSX, LEFT_ICON_POSY, 0.0f, SAW_KOMA_NO + i, m_nStage);
			}
			else
			{
				m_pShopIcon[i] = new CShopIcon(LEFT_ICON_POSX, LEFT_ICON_POSY - 5.0f, 0.0f, SAW_KOMA_NO + i, m_nStage);
			}
			pShopIcon[i] = m_pShopIcon[i]->GetIcon();												// �p�����[�^���
			pShopIcon[i]->pTexture = new Texture();
			if ((i - 3) % 5 == 0)	// 4��ޖڂȂ�
			{
				if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/UI_Urikire.png")))	// �ʏ�A�C�R��
				{
					MessageBox(NULL, "ShopMenu.cpp UI_Urikire.png", "Error", MB_OK);
				}
			}
			else if ((i - 4) % 5 == 0)	// 5��ޖڂȂ�
			{
				if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/UI_Urikire2.png")))	// �I���A�C�R��
				{
					MessageBox(NULL, "ShopMenu.cpp UI_Urikire2.png", "Error", MB_OK);
				}
			}
			else
			{
				if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/UI_Icon.png")))	// �J�X�^���A�C�R��
				{
					MessageBox(NULL, "ShopMenu.cpp UI_Icon.png", "Error", MB_OK);
				}
			}
			m_pShopIcon[i]->SetSize(ICON_SiZEX,			// �T�C�Y�ݒ�
				ICON_SiZEY);
		}

		m_nShopCustom[0] = Custom::SAW;																// �V���b�v�ɂ���J�X�^�����
		m_pPrice[0] = new CPrice(LEFT_PRICE_POSX - 20.0f, LEFT_PRICE_POSY, 0.0f, PRICE_SAW_LEVEL1);			// ���i���
		//----���W�ޔ�----
		m_anPricePos[0].x = LEFT_PRICE_POSX - 20.0f;
		m_anPricePos[0].y = LEFT_PRICE_POSY;
		for (int i = ICON_KIND - 2; i < ICON_KIND; i++)
		{
			m_pShopIcon[i]->SetTexCoord(0.0f, 1.0f);												// ����؂�T�C�Y����
			m_pShopIcon[i]->SetPos(LEFT_ICON_POSX - 5.0f, LEFT_ICON_POSY + 5.0f);					// ���W�ݒ�
			m_pShopIcon[i]->SetSize(pShopIcon[i]->pTexture->GetWidth() * SOLD_OUT_RATIO				// �T�C�Y�ݒ�
				, pShopIcon[i]->pTexture->GetHeight() * SOLD_OUT_RATIO);
		}

		//----�E��̃A�C�R��----
		// �n���}�[
		for (int i = ICON_KIND; i < ICON_KIND * 2; i++)
		{
			// �ʏ�A�I���A�A�C�R���A����؂�A����؂�I���̏��ɓ���
			if (i != 7)
			{
				m_pShopIcon[i] = new CShopIcon(LEFT_ICON_POSX + ICON_WIDTHX,
					LEFT_ICON_POSY, 0.0f, HAMMER_KOMA_NO + i - ICON_KIND, m_nStage);
			}
			else
			{
				m_pShopIcon[i] = new CShopIcon(LEFT_ICON_POSX + ICON_WIDTHX,
					LEFT_ICON_POSY - 5.0f, 0.0f, HAMMER_KOMA_NO + i - ICON_KIND, m_nStage);
			}
			pShopIcon[i] = m_pShopIcon[i]->GetIcon();											// �p�����[�^���
			pShopIcon[i]->pTexture = new Texture();
			if ((i - 3) % 5 == 0)	// 4��ޖڂȂ�
			{
				if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/UI_Urikire.png")))	// �ʏ�A�C�R��
				{
					MessageBox(NULL, "ShopMenu.cpp UI_Urikire.png", "Error", MB_OK);
				}
			}
			else if ((i - 4) % 5 == 0)	// 5��ޖڂȂ�
			{
				if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/UI_Urikire2.png")))	// �I���A�C�R��
				{
					MessageBox(NULL, "ShopMenu.cpp UI_Urikire2.png", "Error", MB_OK);
				}
			}
			else
			{
				if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/UI_Icon.png")))	// �J�X�^���A�C�R��
				{
					MessageBox(NULL, "ShopMenu.cpp UI_Icon.png", "Error", MB_OK);
				}
			}
			m_pShopIcon[i]->SetSize(ICON_SiZEX,			// �T�C�Y�ݒ�
				ICON_SiZEY);
		}
		m_nShopCustom[1] = Custom::HAMMER;														// �V���b�v�ɂ���J�X�^�����
		m_pPrice[1] = new CPrice(LEFT_PRICE_POSX + PRICE_WIDTHX - 35.0f,						// ���i���
			LEFT_PRICE_POSY - 2.0f, 0.0f, PRICE_HAMMER_LEVEL1);
		//----���W�ޔ�----
		m_anPricePos[1].x = LEFT_PRICE_POSX + PRICE_WIDTHX - 35.0f;
		m_anPricePos[1].y = LEFT_PRICE_POSY - 2.0f;
		for (int i = ICON_KIND * 2 - 2; i < ICON_KIND * 2; i++)
		{
			m_pShopIcon[i]->SetTexCoord(0.0f, 1.0f);											// ����؂�T�C�Y����
			m_pShopIcon[i]->SetPos(LEFT_ICON_POSX + ICON_WIDTHX - 5.0f,								// ���W�ݒ�
				LEFT_ICON_POSY + 6.0f);
			m_pShopIcon[i]->SetSize(pShopIcon[i]->pTexture->GetWidth() * SOLD_OUT_RATIO			// �T�C�Y�ݒ�
				, pShopIcon[i]->pTexture->GetHeight() * SOLD_OUT_RATIO);
		}

		//----�����̃A�C�R��----
		// �h����
		for (int i = ICON_KIND * 2; i < ICON_KIND * 3; i++)
		{
			// �ʏ�A�I���A�A�C�R���A����؂�A����؂�I���̏��ɓ���
			if (i != 12)
			{
				m_pShopIcon[i] = new CShopIcon(LEFT_ICON_POSX,
					LEFT_ICON_POSY + ICON_WIDTHY, 0.0f, DRILL_KOMA_NO + i - ICON_KIND * 2, m_nStage);
			}
			else
			{
				m_pShopIcon[i] = new CShopIcon(LEFT_ICON_POSX + 15.0f,
					LEFT_ICON_POSY + ICON_WIDTHY - 8.0f, 0.0f, DRILL_KOMA_NO + i - ICON_KIND * 2, m_nStage);
			}
			pShopIcon[i] = m_pShopIcon[i]->GetIcon();												// �p�����[�^���
			pShopIcon[i]->pTexture = new Texture();
			if ((i - 3) % 5 == 0)	// 4��ޖڂȂ�
			{
				if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/UI_Urikire.png")))	// �ʏ�A�C�R��
				{
					MessageBox(NULL, "ShopMenu.cpp UI_Urikire.png", "Error", MB_OK);
				}
			}
			else if ((i - 4) % 5 == 0)	// 5��ޖڂȂ�
			{
				if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/UI_Urikire2.png")))	// �I���A�C�R��
				{
					MessageBox(NULL, "ShopMenu.cpp UI_Urikire2.png", "Error", MB_OK);
				}
			}
			else
			{
				if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/UI_Icon.png")))	// �J�X�^���A�C�R��
				{
					MessageBox(NULL, "ShopMenu.cpp UI_Icon.png", "Error", MB_OK);
				}
			}
			if (i != 12)
			{
				m_pShopIcon[i]->SetSize(ICON_SiZEX,			// �T�C�Y�ݒ�
					ICON_SiZEY);
			}
			else
			{
				m_pShopIcon[i]->SetSize(ICON_SiZEX - 10.0f,			// �T�C�Y�ݒ�
					ICON_SiZEY - 10.0f);
			}
		}

		m_nShopCustom[2] = Custom::DRILL;													// �V���b�v�ɂ���J�X�^�����
		m_pPrice[2] = new CPrice(LEFT_PRICE_POSX - 20.0f, LEFT_PRICE_POSY + PRICE_WIDTHY/* + 3.0f*/,	// ���i���
			0.0f, PRICE_DRILL_LEVEL1);
		//----���W�ޔ�----
		m_anPricePos[2].x = LEFT_PRICE_POSX - 20.0f;
		m_anPricePos[2].y = LEFT_PRICE_POSY + PRICE_WIDTHY/* + 3.0f*/;
		for (int i = ICON_KIND * 3 - 2; i < ICON_KIND * 3; i++)
		{
			m_pShopIcon[i]->SetTexCoord(0.0f, 1.0f);												// ����؂�T�C�Y����
			m_pShopIcon[i]->SetPos(LEFT_ICON_POSX - 5.0f,													// ���W�ݒ�
				LEFT_ICON_POSY + ICON_WIDTHY + 14.0f);
			m_pShopIcon[i]->SetSize(pShopIcon[i]->pTexture->GetWidth() * SOLD_OUT_RATIO				// �T�C�Y�ݒ�
				, pShopIcon[i]->pTexture->GetHeight() * SOLD_OUT_RATIO);
		}

		//----�E���̃A�C�R��----
		// �m�Y������
		for (int i = ICON_KIND * 3; i < ICON_KIND * 4; i++)
		{
			// �ʏ�A�I���A�A�C�R���A����؂�A����؂�I���ɓ���
			if (i != 17)
			{
				m_pShopIcon[i] = new CShopIcon(LEFT_ICON_POSX + ICON_WIDTHX,
					LEFT_ICON_POSY + ICON_WIDTHY, 0.0f, NOZZLE_KOMA_NO + i - ICON_KIND * 3, m_nStage);
			}
			else
			{
				m_pShopIcon[i] = new CShopIcon(LEFT_ICON_POSX + ICON_WIDTHX,
					LEFT_ICON_POSY + ICON_WIDTHY - 7.0f, 0.0f, NOZZLE_KOMA_NO + i - ICON_KIND * 3, m_nStage);
			}
			pShopIcon[i] = m_pShopIcon[i]->GetIcon();												// �p�����[�^���
			pShopIcon[i]->pTexture = new Texture();
			if ((i - 3) % 5 == 0)	// 4��ޖڂȂ�
			{
				if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/UI_Urikire.png")))	// �ʏ�A�C�R��
				{
					MessageBox(NULL, "ShopMenu.cpp UI_Urikire.png", "Error", MB_OK);
				}
			}
			else if ((i - 4) % 5 == 0)	// 5��ޖڂȂ�
			{
				if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/UI_Urikire2.png")))	// �I���A�C�R��
				{
					MessageBox(NULL, "ShopMenu.cpp UI_Urikire2.png", "Error", MB_OK);
				}
			}
			else
			{
				if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/UI_Icon.png")))	// �J�X�^���A�C�R��
				{
					MessageBox(NULL, "ShopMenu.cpp UI_Icon.png", "Error", MB_OK);
				}
			}
			m_pShopIcon[i]->SetSize(ICON_SiZEX,			// �T�C�Y�ݒ�
				ICON_SiZEY);
		}
		m_nShopCustom[3] = Custom::GAME_NOZZLE;														// �V���b�v�ɂ���J�X�^�����
		m_pPrice[3] = new CPrice(LEFT_PRICE_POSX + PRICE_WIDTHX - 40.0f,							// ���i���
			LEFT_PRICE_POSY + PRICE_WIDTHY,
			0.0f, PRICE_NOZZLE_LEVEL2);
		//----���W�ޔ�----
		m_anPricePos[3].x = LEFT_PRICE_POSX + PRICE_WIDTHX - 40.0f;
		m_anPricePos[3].y = LEFT_PRICE_POSY + PRICE_WIDTHY;
		for (int i = ICON_KIND * 4 - 2; i < ICON_KIND * 4; i++)
		{
			m_pShopIcon[i]->SetTexCoord(0.0f, 1.0f);												// ����؂�T�C�Y����
			m_pShopIcon[i]->SetPos(LEFT_ICON_POSX + ICON_WIDTHX - 5.0f,								// ���W�ݒ�
				LEFT_ICON_POSY + ICON_WIDTHY + 16.0f);
			m_pShopIcon[i]->SetSize(pShopIcon[i]->pTexture->GetWidth() * SOLD_OUT_RATIO				// �T�C�Y�ݒ�
				, pShopIcon[i]->pTexture->GetHeight() * SOLD_OUT_RATIO);
		}

		//----2�y�[�W��----
		// ����
		for (int i = ICON_KIND * 4; i < ICON_KIND * 5; i++)
		{
			// �ʏ�A�I���A�A�C�R���A����؂�A����؂�I���̏��ɓ���
			m_pShopIcon[i] = new CShopIcon(LEFT_ICON_POSX, LEFT_ICON_POSY,
				0.0f, BOOTS_KOMA_NO + i - ICON_KIND * 4, m_nStage);
			pShopIcon[i] = m_pShopIcon[i]->GetIcon();												// �p�����[�^���
			pShopIcon[i]->pTexture = new Texture();
			if ((i - 3) % 5 == 0)	// 4��ޖڂȂ�
			{
				if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/UI_Urikire.png")))	// �ʏ�A�C�R��
				{
					MessageBox(NULL, "ShopMenu.cpp UI_Urikire.png", "Error", MB_OK);
				}
			}
			else if ((i - 4) % 5 == 0)	// 5��ޖڂȂ�
			{
				if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/UI_Urikire2.png")))	// �I���A�C�R��
				{
					MessageBox(NULL, "ShopMenu.cpp UI_Urikire2.png", "Error", MB_OK);
				}
			}
			else
			{
				if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/UI_Icon.png")))	// �J�X�^���A�C�R��
				{
					MessageBox(NULL, "ShopMenu.cpp UI_Icon.png", "Error", MB_OK);
				}
			}
			m_pShopIcon[i]->SetSize(ICON_SiZEX,			// �T�C�Y�ݒ�
				ICON_SiZEY);
		}

		m_nShopCustom[4] = Custom::BOOTS;																// �V���b�v�ɂ���J�X�^�����
		m_pPrice[4] = new CPrice(LEFT_PRICE_POSX - 20.0f, LEFT_PRICE_POSY, 0.0f, PRICE_BOOTS);			// ���i���
		//----���W�ޔ�----
		m_anPricePos[4].x = LEFT_PRICE_POSX - 20.0f;
		m_anPricePos[4].y = LEFT_PRICE_POSY;
		for (int i = ICON_KIND * 5 - 2; i < ICON_KIND * 5; i++)
		{
			m_pShopIcon[i]->SetTexCoord(0.0f, 1.0f);												// ����؂�T�C�Y����
			m_pShopIcon[i]->SetPos(LEFT_ICON_POSX - 5.0f, LEFT_ICON_POSY + 5.0f);					// ���W�ݒ�
			m_pShopIcon[i]->SetSize(pShopIcon[i]->pTexture->GetWidth() * SOLD_OUT_RATIO				// �T�C�Y�ݒ�
				, pShopIcon[i]->pTexture->GetHeight() * SOLD_OUT_RATIO);
		}

		if (m_nStage == 3)
		{
			//----�E��̃A�C�R��----
			// �ϔM�J�X�^��
			for (int i = ICON_KIND * 5; i < ICON_KIND * 6; i++)
			{
				// �ʏ�A�I���A�A�C�R���A����؂�A����؂�I���̏��ɓ���
				if (i != 27 && i != 26)
				{
					m_pShopIcon[i] = new CShopIcon(LEFT_ICON_POSX + ICON_WIDTHX,
						LEFT_ICON_POSY, 0.0f, HEAT_RESISTANT_KOMA_NO + i - ICON_KIND * 5, m_nStage);
				}
				else if (i == 26)
				{
					m_pShopIcon[i] = new CShopIcon(LEFT_ICON_POSX + ICON_WIDTHX + 5.0f,
						LEFT_ICON_POSY - 5.0f, 0.0f, HEAT_RESISTANT_KOMA_NO + i - ICON_KIND * 5, m_nStage);
				}
				else
				{
					m_pShopIcon[i] = new CShopIcon(LEFT_ICON_POSX + ICON_WIDTHX + 10.0f,
						LEFT_ICON_POSY - 15.0f, 0.0f, HEAT_RESISTANT_KOMA_NO + i - ICON_KIND * 5, m_nStage);
				}
				pShopIcon[i] = m_pShopIcon[i]->GetIcon();											// �p�����[�^���
				pShopIcon[i]->pTexture = new Texture();
				if ((i - 3) % 5 == 0)	// 4��ޖڂȂ�
				{
					if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/UI_Urikire.png")))	// �ʏ�A�C�R��
					{
						MessageBox(NULL, "ShopMenu.cpp UI_Urikire.png", "Error", MB_OK);
					}
				}
				else if ((i - 4) % 5 == 0)	// 5��ޖڂȂ�
				{
					if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/UI_Urikire2.png")))	// �I���A�C�R��
					{
						MessageBox(NULL, "ShopMenu.cpp UI_Urikire2.png", "Error", MB_OK);
					}
				}
				else
				{
					if (FAILED(pShopIcon[i]->pTexture->Create("Assets/Texture/UI_Icon.png")))	// �J�X�^���A�C�R��
					{
						MessageBox(NULL, "ShopMenu.cpp UI_Icon.png", "Error", MB_OK);
					}
				}
				m_pShopIcon[i]->SetSize(ICON_SiZEX,			// �T�C�Y�ݒ�
					ICON_SiZEY);
			}
			m_nShopCustom[5] = Custom::HEAT_RESISTANT;														// �V���b�v�ɂ���J�X�^�����
			m_pPrice[5] = new CPrice(LEFT_PRICE_POSX + PRICE_WIDTHX - 35.0f,						// ���i���
				LEFT_PRICE_POSY - 2.0f, 0.0f, PRICE_HEAT_RESISTANT);
			//----���W�ޔ�----
			m_anPricePos[5].x = LEFT_PRICE_POSX + PRICE_WIDTHX - 35.0f;
			m_anPricePos[5].y = LEFT_PRICE_POSY - 2.0f;
			for (int i = ICON_KIND * 6 - 2; i < ICON_KIND * 6; i++)
			{
				m_pShopIcon[i]->SetTexCoord(0.0f, 1.0f);											// ����؂�T�C�Y����
				m_pShopIcon[i]->SetPos(LEFT_ICON_POSX + ICON_WIDTHX - 5.0f,								// ���W�ݒ�
					LEFT_ICON_POSY + 6.0f);
				m_pShopIcon[i]->SetSize(pShopIcon[i]->pTexture->GetWidth() * SOLD_OUT_RATIO			// �T�C�Y�ݒ�
					, pShopIcon[i]->pTexture->GetHeight() * SOLD_OUT_RATIO);
			}
		}
		break;
	}
}


CShopMenu::~CShopMenu()	// �f�X�g���N�^
{
	//----�V���b�v���������----
	if (m_pShop)
	{
		delete m_pShop;
		m_pShop = nullptr;
	}

	//----�x�[�X���������----
	for (int i = 0; i < MAX_BASE_SHOP_MENU; ++i)
	{
		if (m_BaseShopMenu[i].pTexture)
		{
			delete m_BaseShopMenu[i].pTexture;
			m_BaseShopMenu[i].pTexture = nullptr;
		}
	}

	//----�A�C�R�����������----
	for (int i = 0; i < MAX_CUSTOM * ICON_KIND; ++i)
	{
		if (m_pShopIcon[i])
		{
			if (pShopIcon[i]->pTexture)
			{
				delete pShopIcon[i]->pTexture;
				pShopIcon[i]->pTexture = nullptr;
			}
			delete m_pShopIcon[i];
			m_pShopIcon[i] = nullptr;
		}
	}

	//----���̓��������----
	SAFE_DELETE(m_pShopText);

	// ���i���������
	for (int i = 0; i < MAX_CUSTOM; ++i)
	{
		if (m_pPrice[i])
		{
			delete m_pPrice[i];
			m_pPrice[i] = nullptr;
		}
	}
}

void CShopMenu::Update(float tick)	// �X�V
{
	Animetion(tick);	// �A�j���[�V��������

	//----�A�C�e�����g�p���ꂽ��----
	if (m_nCoupon && !m_nFirst)
	{
		// ����
		m_pShop->SetItem(SHOP_COUPON);
		ALLCoupon();		// �l�i�\�������֐�
		m_nFirst = 1;
	}

	m_bShop = true;
	if (m_nOpenAnimetion)
	{
		return;
	}
	//�R���g���[���[����
	XINPUT_STATE state;
	XINPUT_KEYSTROKE stroke;
	XInputGetState(0, &state);
	XInputGetKeystroke(0, 0, &stroke);
	if ((state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		state.Gamepad.sThumbLX = 0;
		state.Gamepad.sThumbLY = 0;

	}
	if (state.dwPacketNumber != 3435973836)
	{
		if (state.Gamepad.sThumbLY > 0 &&
			state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && stroke.Flags == 0x0001
			|| state.Gamepad.wButtons&XINPUT_GAMEPAD_DPAD_UP&&stroke.Flags == 0x0001)
		{
			if (m_nCursor > 2)	// �J�[�\���ʒu������
			{
				m_nCursor -= 2;	// �J�[�\���ʒu�����
			}
			m_nLines = 0;	// �Z���t�t���O����
			m_nBuy = 0;		// �����t���O����
			m_nMove = 1;	// �ړ��t���O�グ
			m_fRatio = 1.0f;	// �䗦���Z�b�g
			m_pSoundMng->playSound(CSoundMng::SystemSE::select);//�I��se
		}
		else if (state.Gamepad.sThumbLX < 0 &&
			state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && stroke.Flags == 0x0001
			|| state.Gamepad.wButtons&XINPUT_GAMEPAD_DPAD_LEFT&&stroke.Flags == 0x0001)
		{
			if (m_nCursor % 2 == 1 && m_nPage > 1)	// ���[�ŕ����y�[�W��
			{
				m_nPage -= 1;	// �O�̃y�[�W��
				m_nCursor = 2;	// �J�[�\���ʒu����
				// �A�j���[�V�����֌W
				// ���̈ʒu��ς���
				m_BaseShopMenu[4].pos.x = RIGHT_ARROW_POSX;
				m_fAnimeMoveX = 0.1f;	// �ړ��ʃ��Z�b�g
				m_nAnimeMoved = 0;		// �t���O���Z�b�g
				m_nFrame = 0;			// �t���[���J�E���g���Z�b�g
			}
			else if (m_nCursor % 2 == 0)	// �J�[�\���ʒu���E��
			{
				m_nCursor -= 1;				// �J�[�\���ʒu������
			}
			m_nLines = 0;	// �Z���t�t���O����
			m_nBuy = 0;		// �����t���O����
			m_nMove = 1;	// �ړ��t���O�グ
			m_fRatio = 1.0f;	// �䗦���Z�b�g
			m_pSoundMng->playSound(CSoundMng::SystemSE::select);//�I��se
		}
		else if (state.Gamepad.sThumbLY < 0 &&
			state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && stroke.Flags == 0x0001
			|| state.Gamepad.wButtons&XINPUT_GAMEPAD_DPAD_DOWN&&stroke.Flags == 0x0001)
		{
			if (m_nCursor <= 2)	// �J�[�\���ʒu���ォ
			{
				m_nCursor += 2;	// �J�[�\���ʒu������
			}
			m_nLines = 0;	// �Z���t�t���O����
			m_nBuy = 0;		// �����t���O����
			m_nMove = 1;	// �ړ��t���O�グ
			m_fRatio = 1.0f;	// �䗦���Z�b�g
			m_pSoundMng->playSound(CSoundMng::SystemSE::select);//�I��se
		}
		else if (state.Gamepad.sThumbLX > 0 &&
			state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && stroke.Flags == 0x0001
			|| state.Gamepad.wButtons&XINPUT_GAMEPAD_DPAD_RIGHT&&stroke.Flags == 0x0001)
		{
			if (m_nCursor % 2 == 0 && m_nPage < m_nTotalPage)	// �E�[�ŕ����y�[�W��
			{
				m_nPage += 1;	// ���̃y�[�W��
				m_nCursor = 1;	// �J�[�\���ʒu����
				// �A�j���[�V�����֌W
				// ���̈ʒu��ς���
				m_BaseShopMenu[4].pos.x = LEFT_ARROW_POSX;
				m_fAnimeMoveX = 0.1f;	// �ړ��ʃ��Z�b�g
				m_nAnimeMoved = 0;		// �t���O���Z�b�g
				m_nFrame = 0;			// �t���[���J�E���g���Z�b�g
			}
			else if (m_nCursor % 2 == 1)	// �J�[�\���ʒu���E��
			{
				m_nCursor += 1;
			}
			m_nLines = 0;	// �Z���t�t���O����
			m_nBuy = 0;		// �����t���O����
			m_nMove = 1;	// �ړ��t���O�グ
			m_fRatio = 1.0f;	// �䗦���Z�b�g
			m_pSoundMng->playSound(CSoundMng::SystemSE::select);//�I��se
		}
	}
	if (state.Gamepad.wButtons&XINPUT_GAMEPAD_A&&stroke.Flags == 0x0001)
	{
		// �w���ł��邩
		// 1�y�[�W�ڂ�������
		if (m_nPage == 1)
		{
			// �X�e�[�W����
			if (m_nStage != 0)
			{
				// �J�X�^�}�C�Y�p�[�c�w��
				m_pShop->Buy(m_pnCustom, m_pnMoney, m_nShopCustom[m_nCursor - 1],
					&m_nBuy, &m_nNozzle);
			}
			// �Z���N�g��������
			else
			{
				// �A�C�e���w��
				m_pShop->ItemBuy(m_pnItem, m_pnMoney, m_nShopCustom[m_nCursor - 1],
					&m_nBuy);
			}
			if (m_nBuy == 1)	// �w�����ꂽ��
			{
				m_nLines = 0;	// �Z���t�t���O����
				m_anBuyCustom = m_nShopCustom[m_nCursor - 1];
			}
		}
		// 2�y�[�W�ڂ�������
		else if (m_nPage == 2)
		{
			m_pShop->Buy(m_pnCustom, m_pnMoney, m_nShopCustom[m_nCursor + 3],
				&m_nBuy, &m_nNozzle);
			if (m_nBuy == 1)	// �w�����ꂽ��
			{
				m_nLines = 0;	// �Z���t�t���O����
				m_anBuyCustom = m_nShopCustom[m_nCursor + 3];
			}
		}
		if (m_nBuy == 1) m_pSoundMng->playSound(CSoundMng::ShopSE::buy);//���W��
	}
	if (state.Gamepad.wButtons&XINPUT_GAMEPAD_B&&stroke.Flags == XINPUT_KEYSTROKE_KEYDOWN)
	{
		m_bShop = false;// �V���b�v��ʕ���
		m_nLines = 0;	// �Z���t�t���O����
		m_pShopText->SetTextNo(0, FIRST_LINE, FIRST_LINE);
		m_nBuy = 0;		// �����t���O����
		m_nMove = 0;	// �J�[�\���ړ��t���O����
		m_fRatio = 1.0f;	// �䗦���Z�b�g
		//----���W���Z�b�g----
		//----���W���Z�b�g----
		m_time = 0.0f;
		m_BaseShopMenu[0].pos.x = MERCHANT_START_POSX;
		//		m_BaseShopMenu[0].pos.y = MERCHANT_START_POSY;
		m_BaseShopMenu[1].pos.y = WINDOW_START_POSY;
		//		m_BaseShopMenu[2].pos.y = LINE_FRAME_START_POSY;
		m_BaseShopMenu[2].pos.x = LINE_FRAME_START_POSX;
		//m_BaseShopMenu[3].pos.y = DOWN_ARROW_START_POSY;
		//m_BaseShopMenu[4].pos.y = ARROW_START_POSY;
		for (int i = 5; i < 8; i++)
		{
			m_BaseShopMenu[i].pos.y = -100.0f;	// ��ʊO�ֈړ�������
		}
		m_nOpenAnimetion = 1;	// �A�j���[�V�����t���O�グ
		m_pSoundMng->playSound(CSoundMng::SystemSE::cancel);//�L�����Z��se
	}

	//----���͏���----
	if (IsKeyTrigger('W'))	// ��
	{
		if (m_nCursor > 2)	// �J�[�\���ʒu������
		{
			m_nCursor -= 2;	// �J�[�\���ʒu�����
		}
		m_nLines = 0;	// �Z���t�t���O����
		m_nBuy = 0;		// �����t���O����
		m_nMove = 1;	// �ړ��t���O�グ
		m_fRatio = 1.0f;	// �䗦���Z�b�g
		m_pSoundMng->playSound(CSoundMng::SystemSE::select);//�I��se
	}
	else if (IsKeyTrigger('A'))	// ��
	{
		if (m_nCursor % 2 == 1 && m_nPage > 1)	// ���[�ŕ����y�[�W��
		{
			m_nPage -= 1;	// �O�̃y�[�W��
			m_nCursor = 2;	// �J�[�\���ʒu����
			// �A�j���[�V�����֌W
			// ���̈ʒu��ς���
			m_BaseShopMenu[4].pos.x = RIGHT_ARROW_POSX;
			m_fAnimeMoveX = 0.1f;	// �ړ��ʃ��Z�b�g
			m_nAnimeMoved = 0;		// �t���O���Z�b�g
			m_nFrame = 0;			// �t���[���J�E���g���Z�b�g
		}
		else if (m_nCursor % 2 == 0)	// �J�[�\���ʒu���E��
		{
			m_nCursor -= 1;				// �J�[�\���ʒu������
		}
		m_nLines = 0;	// �Z���t�t���O����
		m_nBuy = 0;		// �����t���O����
		m_nMove = 1;	// �ړ��t���O�グ
		m_fRatio = 1.0f;	// �䗦���Z�b�g
		m_pSoundMng->playSound(CSoundMng::SystemSE::select);//�I��se
	}
	else if (IsKeyTrigger('S'))	// ��
	{
		if (m_nCursor <= 2)	// �J�[�\���ʒu���ォ
		{
			m_nCursor += 2;	// �J�[�\���ʒu������
		}
		m_nLines = 0;	// �Z���t�t���O����
		m_nBuy = 0;		// �����t���O����
		m_nMove = 1;	// �ړ��t���O�グ
		m_fRatio = 1.0f;	// �䗦���Z�b�g
		m_pSoundMng->playSound(CSoundMng::SystemSE::select);//�I��se
	}
	else if (IsKeyTrigger('D'))	// �E
	{
		if (m_nCursor % 2 == 0 && m_nPage < m_nTotalPage)	// �E�[�ŕ����y�[�W��
		{
			m_nPage += 1;	// ���̃y�[�W��
			m_nCursor = 1;	// �J�[�\���ʒu����
			// �A�j���[�V�����֌W
			// ���̈ʒu��ς���
			m_BaseShopMenu[4].pos.x = LEFT_ARROW_POSX;
			m_fAnimeMoveX = 0.1f;	// �ړ��ʃ��Z�b�g
			m_nAnimeMoved = 0;		// �t���O���Z�b�g
			m_nFrame = 0;			// �t���[���J�E���g���Z�b�g
		}
		else if (m_nCursor % 2 == 1)	// �J�[�\���ʒu���E��
		{
			m_nCursor += 1;
		}
		m_nLines = 0;	// �Z���t�t���O����
		m_nBuy = 0;		// �����t���O����
		m_nMove = 1;	// �ړ��t���O�グ
		m_fRatio = 1.0f;	// �䗦���Z�b�g
		m_pSoundMng->playSound(CSoundMng::SystemSE::select);//�I��se
	}
	if (IsKeyTrigger(VK_RETURN))	// �w��
	{
		// �w���ł��邩
		// 1�y�[�W�ڂ�������
		if (m_nPage == 1)
		{
			// �X�e�[�W����
			if (m_nStage != 0)
			{
				// �J�X�^�}�C�Y�p�[�c�w��
				m_pShop->Buy(m_pnCustom, m_pnMoney, m_nShopCustom[m_nCursor - 1],
					&m_nBuy, &m_nNozzle);
			}
			// �Z���N�g��������
			else
			{
				// �A�C�e���w��
				m_pShop->ItemBuy(m_pnItem, m_pnMoney, m_nShopCustom[m_nCursor - 1],
					&m_nBuy);
			}
			if (m_nBuy == 1)	// �w�����ꂽ��
			{
				m_nLines = 0;	// �Z���t�t���O����
				m_anBuyCustom = m_nShopCustom[m_nCursor - 1];
			}
		}
		// 2�y�[�W�ڂ�������
		else if (m_nPage == 2)
		{
			m_pShop->Buy(m_pnCustom, m_pnMoney, m_nShopCustom[m_nCursor + 3],
				&m_nBuy, &m_nNozzle);
			if (m_nBuy == 1)	// �w�����ꂽ��
			{
				m_nLines = 0;	// �Z���t�t���O����
				m_anBuyCustom = m_nShopCustom[m_nCursor + 3];
			}
		}
		if (m_nBuy == 1) m_pSoundMng->playSound(CSoundMng::ShopSE::buy);//���W��

	}
	if (IsKeyTrigger('E'))	// ����
	{
		m_bShop = false;// �V���b�v��ʕ���
		m_nLines = 0;	// �Z���t�t���O����
		m_pShopText->SetTextNo(0, FIRST_LINE, FIRST_LINE);
		m_nBuy = 0;		// �����t���O����
		m_nMove = 0;	// �J�[�\���ړ��t���O����
		m_fRatio = 1.0f;	// �䗦���Z�b�g
		//----���W���Z�b�g----
		m_time = 0.0f;
		m_BaseShopMenu[0].pos.x = MERCHANT_START_POSX;
//		m_BaseShopMenu[0].pos.y = MERCHANT_START_POSY;
		m_BaseShopMenu[1].pos.y = WINDOW_START_POSY;	
//		m_BaseShopMenu[2].pos.y = LINE_FRAME_START_POSY;
		m_BaseShopMenu[2].pos.x = LINE_FRAME_START_POSX;
		//m_BaseShopMenu[3].pos.y = DOWN_ARROW_START_POSY;
		//m_BaseShopMenu[4].pos.y = ARROW_START_POSY;
		for (int i = 5; i < 8; i++)
		{
			m_BaseShopMenu[i].pos.y = -100.0f;	// ��ʊO�ֈړ�������
		}
		m_nOpenAnimetion = 1;	// �A�j���[�V�����t���O�グ
		m_pSoundMng->playSound(CSoundMng::SystemSE::cancel);//�L�����Z��se
	}

	LineSet();	// �Z���t�`��
}

void CShopMenu::Draw()	// �`��
{
	DirectX::XMFLOAT4X4 mat[3][MAX_BASE_SHOP_MENU];		// ��ԑ����������X�e�[�W�̕��g�����

	DirectX::XMMATRIX world[MAX_BASE_SHOP_MENU];		// ��ԑ����������X�e�[�W�̕��g�����

	if (!m_nOpenAnimetion)
	{
		PageSetDraw();	// �y�[�W�\�L�̐ݒ�
	}

	//----�x�[�X�V���b�v��ʂ̃��[���h�s��ݒ�----
	for (int i = 0; i < MAX_BASE_SHOP_MENU; ++i)
	{
		if (!m_BaseShopMenu[i].pTexture) continue;

		//���[���h�s���X,Y�݂̂��l�����č쐬
		world[i] = DirectX::XMMatrixTranslation(m_BaseShopMenu[i].pos.x, m_BaseShopMenu[i].pos.y, m_BaseShopMenu[i].pos.z);
		DirectX::XMStoreFloat4x4(&mat[0][i], DirectX::XMMatrixTranspose(world[i]));
	}

	//�r���[�s���2d���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��
	DirectX::XMStoreFloat4x4(&mat[1][0], DirectX::XMMatrixIdentity());

	//�v���W�F�N�V�����s���2d�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
	//���̍s���2d�X�N���[���̑傫�������܂�
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(ICON_LEFT, ICON_RIGHT, ICON_BOTTOM,
		ICON_TOP, ICON_NEAR, ICON_FAR);
	DirectX::XMStoreFloat4x4(&mat[2][0], DirectX::XMMatrixTranspose(proj));

	//�x�[�X�V���b�v��ʃX�v���C�g�̐ݒ�
	for (int i = 0; i < MAX_BASE_SHOP_MENU; ++i)
	{
		// �ŏ��̓A�j���[�V�����̂�����̂����`��
		if (m_nOpenAnimetion && i >= 4/* || i == 0)*/)
		{
			continue;	// ���X���̃A�j���[�V�������Ȃ����̂������玟��
		}
		Sprite::SetWorld(mat[0][i]);												// ���[���h�Z�b�g
		Sprite::SetView(mat[1][0]);													// �r���[�Z�b�g
		Sprite::SetProjection(mat[2][0]);											// �v���W�F�N�V�����Z�b�g
		Sprite::SetSize(DirectX::XMFLOAT2(m_BaseShopMenu[i].size.x,					// �T�C�Y�Z�b�g
			-m_BaseShopMenu[i].size.y));
		Sprite::SetUVPos(DirectX::XMFLOAT2(m_BaseShopMenu[i].posTexCoord.x,			// UV���W�Z�b�g
			m_BaseShopMenu[i].posTexCoord.y));
		Sprite::SetUVScale(DirectX::XMFLOAT2(m_BaseShopMenu[i].sizeTexCoord.x,		// UV�T�C�Y�Z�b�g
			m_BaseShopMenu[i].sizeTexCoord.y));
		Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		if (m_nPage == 2 && i == 4)
		{
			Sprite::SetTexture(m_BaseShopMenu[6].pTexture);								// �����e�N�X�`���Z�b�g	
		}
		else if (i < 5)
		{
			Sprite::SetTexture(m_BaseShopMenu[i].pTexture);								// �e�N�X�`���Z�b�g	
		}
		else
		{
			Sprite::SetTexture(m_BaseShopMenu[5].pTexture);								// �����e�N�X�`���Z�b�g	
		}
		Sprite::Draw();																// �`��
	}

	if (m_nOpenAnimetion)	// �I�[�v���A�j���[�V�������������Ă�����
	{
		return;
	}

	//----�V���b�v���----
	if (!m_nMove && !m_nBuy)
	{
		m_pShopText->Draw();	// ���X�Z���t��`��
	}

	// ����������Ă��邩��������
	MoneyEnough();

	// �A�C�R���`��
	IconDraw();

	if (m_nBuy == 2)													// �w��������
	{
		m_pShopText->Draw();									// �w���������̃Z���t��`��
	}
}

void CShopMenu::Animetion(float tick)	// �A�j���[�V�����p�֐�
{
	// ��Ԓl = (�I�����̒l - �J�n���̒l) * �C�[�W���O�֐�(���݂̎��� / ������) + �J�n���̒l
	if (m_nOpenAnimetion)	// �J�������̃A�j���[�V����
	{
		m_time += tick;	// ���ݎ��ԍX�V
		
		if (m_time > ANIMETION_SECONDS) { m_nOpenAnimetion = false; }
		float param = m_time / ANIMETION_SECONDS;	// ���ݎ��ԁ@���@������

		m_BaseShopMenu[0].pos.x = (MERCHANT_POSX - MERCHANT_START_POSX) * EaseOutExpo(param) + MERCHANT_START_POSX;
//		m_BaseShopMenu[0].pos.y = (MERCHANT_POSY - MERCHANT_START_POSY) * EaseOutExpo(param) + MERCHANT_START_POSY;
		m_BaseShopMenu[1].pos.y = (WINDOW_POSY - WINDOW_START_POSY) * EaseOutExpo(param) + WINDOW_START_POSY;
//		m_BaseShopMenu[2].pos.y = (LINE_FRAME_POSY - LINE_FRAME_START_POSY) * EaseOutExpo(param) + LINE_FRAME_START_POSY;
		m_BaseShopMenu[2].pos.x = (LINE_FRAME_POSX - LINE_FRAME_START_POSX) * EaseOutExpo(param) + LINE_FRAME_START_POSX;
		//m_BaseShopMenu[3].pos.y = (DOWN_ARROW_POSY - DOWN_ARROW_START_POSY) * EaseOutExpo(param) + DOWN_ARROW_START_POSY;
		
		//if (m_BaseShopMenu[1].pos.y < WINDOW_POSY)		// �w��ʒu���ゾ������
		//{
		//	m_BaseShopMenu[1].pos.y += DOWN_SPEED;		// �`��ʒu��������
		//}


		////else if ()
		////{

		////}
		//else
		//{
		//	m_BaseShopMenu[1].pos.y = WINDOW_POSY;		// �`��ʒu�Œ�
		//	m_nOpenAnimetion = 0;
		//}
	//	if (m_BaseShopMenu[2].pos.y < LINE_FRAME_POSY)	// �w��ʒu���ゾ������
	//	{
	//		m_BaseShopMenu[2].pos.y += DOWN_SPEED;		// �`��ʒu��������
	//	}
	//	else
	//	{
	//		m_BaseShopMenu[2].pos.y = LINE_FRAME_POSY;	// �`��ʒu�Œ�
	//		//m_nOpenAnimetion = 0;
	//	}
	//	if (m_BaseShopMenu[3].pos.y < DOWN_ARROW_POSY)	// �w��ʒu���ゾ������
	//	{
	//		m_BaseShopMenu[3].pos.y += DOWN_SPEED;		// �`��ʒu��������
	//	}
	//	else
	//	{
	//		m_BaseShopMenu[3].pos.y = DOWN_ARROW_POSY;	// �`��ʒu�Œ�
	//	}
	}
	else if (m_nPage == 1)
	{
		if (!m_nAnimeMoved)		// �w��ʒu���ゾ������
		{
			m_fAnimeMoveX *= 1.2f;
			m_BaseShopMenu[4].pos.x += m_fAnimeMoveX;		// �`��ʒu��������
			if (m_BaseShopMenu[4].pos.x >= RIGHT_ARROW_POSX + 15.0f)
			{
				m_nAnimeMoved = 1;
			}
		}
		else if (m_nAnimeMoved && m_nFrame != 0)
		{
			m_nFrame--;
			if (m_nFrame <= 0)
			{
				m_nFrame = 0;
				m_nAnimeMoved = 0;
			}
		}
		else if (m_nAnimeMoved)
		{
			m_fAnimeMoveX *= 0.9f;
			m_BaseShopMenu[4].pos.x -= m_fAnimeMoveX;		// �`��ʒu��������
			if (m_BaseShopMenu[4].pos.x <= RIGHT_ARROW_POSX)
			{
				m_nFrame = 40;
				m_fAnimeMoveX = 0.1f;
			}
		}
	}
	else if (m_nPage == 2)
	{
		if (!m_nAnimeMoved)		// �w��ʒu���ゾ������
		{
			m_fAnimeMoveX *= 1.2f;
			m_BaseShopMenu[4].pos.x -= m_fAnimeMoveX;		// �`��ʒu��������
			if (m_BaseShopMenu[4].pos.x <= LEFT_ARROW_POSX - 15.0f)
			{
				m_nAnimeMoved = 1;
			}
		}
		else if (m_nAnimeMoved && m_nFrame != 0)
		{
			m_nFrame--;
			if (m_nFrame <= 0)
			{
				m_nFrame = 0;
				m_nAnimeMoved = 0;
			}
		}
		else if (m_nAnimeMoved)
		{
			m_fAnimeMoveX *= 0.9f;
			m_BaseShopMenu[4].pos.x += m_fAnimeMoveX;		// �`��ʒu��������
			if (m_BaseShopMenu[4].pos.x >= LEFT_ARROW_POSX)
			{
				m_nFrame = 40;
				m_fAnimeMoveX = 0.1f;
			}
		}
	}
}

void CShopMenu::LineSet()	// �������̓Z�b�g
{
	// 2�y�[�W�ڂ̃A�C�R���ƕ��͂������悤��
	if (m_nPage == 2)	// 2�y�[�W�ڂ�������
	{
		// �A�C�R�������邩�ǂ���
		if (m_nCursor > m_nMaxCustom - 4)
		{
			m_nCursor = m_noldCursor;	// �ړ��ł��Ȃ������猳�̈ʒu�ɖ߂�
		}
	}
	//----�Z���t�Z�b�g----
	if (!m_nMove && !m_nBuy)	// ���X���̃Z���t
	{
		switch (m_nStage)
		{
		case 0:
			if (m_nLines && m_pShopText->GetLineNum() == FIRST_LINE &&
				m_pShopText->GetTextNo(FIRST_LINE) == ENTERING_LINE &&
				m_pShopText->GetAnimeNo(FIRST_LINE) >= SELECT_TEXT_ANIM_SHOP_MENU_NO)	// ��s�ڂ��`�悳��Ă�����
			{
				m_pShopText->SetTextNo(ENTERING_LINE + 1, SECOND_LINE, SECOND_LINE);					// ��s��
			}
			else if (m_nLines && m_pShopText->GetLineNum() == SECOND_LINE &&
				m_pShopText->GetTextNo(SECOND_LINE) == ENTERING_LINE + 1 &&
				m_pShopText->GetAnimeNo(SECOND_LINE) >= SELECT_TEXT_ANIM_SHOP_MENU_NO)	// ��s�ڂ��`�悳��Ă�����
			{
				m_pShopText->SetTextNo(ENTERING_LINE + 2, THIRD_LINE, THIRD_LINE);					// �O�s��
			}
			else if (m_nLines && m_pShopText->GetLineNum() == THIRD_LINE &&
				m_pShopText->GetTextNo(THIRD_LINE) == ENTERING_LINE + 2 &&
				m_pShopText->GetAnimeNo(THIRD_LINE) >= SELECT_TEXT_ANIM_SHOP_MENU_NO)	// �O�s�ڂ��`�悳��Ă�����
			{
				m_pShopText->SetTextNo(ENTERING_LINE + 3, FIRST_LINE, FORCE_LINE);					// �l�s��
			}
			else if (m_nLines && m_pShopText->GetLineNum() == FORCE_LINE &&
				m_pShopText->GetTextNo(FIRST_LINE) == ENTERING_LINE + 3 &&
				m_pShopText->GetAnimeNo(FIRST_LINE) >= SELECT_TEXT_ANIM_SHOP_MENU_NO)	// �l�s�ڂ��`�悳��Ă�����
			{
				m_pShopText->SetTextNo(ENTERING_LINE + 4, SECOND_LINE, 5);					// �܍s��
			}
			else if (!m_nLines && m_pShopText->GetTextNo(FIRST_LINE) != ENTERING_LINE/* &&
				pShopText->currentAnimNo >= TEXT_ANIM_SHOP_MENU_NO*/)		// �`�悳��Ă��Ȃ�������
			{
				m_pShopText->SetTextNo(ENTERING_LINE, FIRST_LINE, FIRST_LINE);				// ��s��
				m_nLines = 1;													// ���[�v�}��
			}
			break;
		case 2:
		case 3:
			if (m_nLines && m_pShopText->GetLineNum() == FIRST_LINE &&
				m_pShopText->GetTextNo(FIRST_LINE) == ENTERING_LINE &&
				m_pShopText->GetAnimeNo(FIRST_LINE) >= TEXT_ANIM_SHOP_MENU_NO)			// ��s�ڂ��`�悳��Ă�����
			{
				m_pShopText->SetTextNo(ENTERING_LINE + 1, SECOND_LINE, SECOND_LINE);					// ��s��
			}
			else if (m_nLines && m_pShopText->GetLineNum() == SECOND_LINE &&
				m_pShopText->GetTextNo(SECOND_LINE) == ENTERING_LINE + 1 &&
				m_pShopText->GetAnimeNo(SECOND_LINE) >= TEXT_ANIM_SHOP_MENU_NO)			// ��s�ڂ��`�悳��Ă�����
			{
				m_pShopText->SetTextNo(ENTERING_LINE + 2, THIRD_LINE, THIRD_LINE);					// �O�s��
			}
			else if (!m_nLines && m_pShopText->GetTextNo(FIRST_LINE) != ENTERING_LINE/* &&
				pShopText->currentAnimNo >= TEXT_ANIM_SHOP_MENU_NO*/)		// �`�悳��Ă��Ȃ�������
			{
				m_pShopText->SetTextNo(ENTERING_LINE, FIRST_LINE, FIRST_LINE);						// ��s��
				m_nLines = 1;													// ���[�v�}��
			}
			break;
		}
	}
	else if (!m_nBuy)	// �J�X�^�}�C�Y�p�[�c�̃Z���t
	{
		switch (m_nStage)
		{
		case 0:
			switch (m_nCursor)
			{
			case 1:	// �h�����N�̃Z���t
				if (m_nLines && m_pShopText->GetLineNum() == FIRST_LINE &&
					m_pShopText->GetTextNo(FIRST_LINE) == DRINK_LINE &&
					m_pShopText->GetAnimeNo(FIRST_LINE) >= SELECT_TEXT_ANIM_SHOP_MENU_NO)	// ��s�ڂ��`�悳��Ă�����
				{
					m_pShopText->SetTextNo(DRINK_LINE + 1, SECOND_LINE, SECOND_LINE);				// ��s��
				}
				else if (m_nLines && m_pShopText->GetLineNum() == SECOND_LINE &&
					m_pShopText->GetTextNo(SECOND_LINE) == DRINK_LINE + 1 &&
					m_pShopText->GetAnimeNo(SECOND_LINE) > SELECT_TEXT_ANIM_SHOP_MENU_NO + 1)	// ��s�ڂ��`�悳��Ă�����
				{
					m_pShopText->SetTextNo(DRINK_LINE + 2, THIRD_LINE, THIRD_LINE);				// �O�s��
				}
				else if (!m_nLines && m_pShopText->GetTextNo(FIRST_LINE) != DRINK_LINE /*&&
					pShopText->currentAnimNo >= TEXT_ANIM_SHOP_MENU_NO*/)// �`�悳��Ă��Ȃ�������
				{
					m_pShopText->SetTextNo(DRINK_LINE, FIRST_LINE, FIRST_LINE);					// ��s��
					m_nLines = 1;											// ���[�v�}��
				}
				break;
			case 2:	// �m�Y�������̃Z���t
				if (m_nLines && m_pShopText->GetLineNum() == FIRST_LINE &&
					m_pShopText->GetTextNo(FIRST_LINE) == NOZZLE_STRONG_LINE &&
					m_pShopText->GetAnimeNo(FIRST_LINE) >= SELECT_TEXT_ANIM_SHOP_MENU_NO)// ��s�ڂ��`�悳��Ă�����
				{
					m_pShopText->SetTextNo(NOZZLE_STRONG_LINE + 1, SECOND_LINE, SECOND_LINE);					// ��s��
				}
				else if (m_nLines && m_pShopText->GetLineNum() == SECOND_LINE &&
					m_pShopText->GetTextNo(SECOND_LINE) == NOZZLE_STRONG_LINE + 1 &&
					m_pShopText->GetAnimeNo(SECOND_LINE) > SELECT_TEXT_ANIM_SHOP_MENU_NO + 1)// ��s�ڂ��`�悳��Ă�����
				{
					m_pShopText->SetTextNo(NOZZLE_STRONG_LINE + 2, THIRD_LINE, THIRD_LINE);					// �O�s��
				}
				else if (!m_nLines && m_pShopText->GetTextNo(FIRST_LINE) != NOZZLE_STRONG_LINE /*&&
					pShopText->currentAnimNo >= TEXT_ANIM_SHOP_MENU_NO*/)	// �`�悳��Ă��Ȃ�������
				{
					m_pShopText->SetTextNo(NOZZLE_STRONG_LINE, FIRST_LINE, FIRST_LINE);						// ��s��
					m_nLines = 1;												// ���[�v�}��
				}
				break;
			case 3:	// ���ԉ���
				if (m_nLines && m_pShopText->GetLineNum() == FIRST_LINE &&
					m_pShopText->GetTextNo(FIRST_LINE) == TIMER_LINE &&
					m_pShopText->GetAnimeNo(FIRST_LINE) >= SELECT_TEXT_ANIM_SHOP_MENU_NO)		// ��s�ڂ��`�悳��Ă�����
				{
					m_pShopText->SetTextNo(TIMER_LINE + 1, SECOND_LINE, SECOND_LINE);					// ��s��
				}
				else if (!m_nLines && m_pShopText->GetTextNo(FIRST_LINE) != TIMER_LINE /*&&
					pShopText->currentAnimNo >= TEXT_ANIM_SHOP_MENU_NO*/)	// �`�悳��Ă��Ȃ�������
				{
					m_pShopText->SetTextNo(TIMER_LINE, FIRST_LINE, FIRST_LINE);						// ��s��
					m_nLines = 1;												// ���[�v�}��
				}
				break;
			case 4:// �N�[�|��
				if (m_nLines && m_pShopText->GetLineNum() == FIRST_LINE &&
					m_pShopText->GetTextNo(FIRST_LINE) == COUPON_LINE &&
					m_pShopText->GetAnimeNo(FIRST_LINE) >= SELECT_TEXT_ANIM_SHOP_MENU_NO)		// ��s�ڂ��`�悳��Ă�����
				{
					m_pShopText->SetTextNo(COUPON_LINE + 1, SECOND_LINE, SECOND_LINE);					// ��s��
				}
				else if (m_nLines && m_pShopText->GetLineNum() == SECOND_LINE &&
					m_pShopText->GetTextNo(SECOND_LINE) == COUPON_LINE + 1 &&
					m_pShopText->GetAnimeNo(SECOND_LINE) > SELECT_TEXT_ANIM_SHOP_MENU_NO + 1)		// ��s�ڂ��`�悳��Ă�����
				{
					m_pShopText->SetTextNo(COUPON_LINE + 2, THIRD_LINE, THIRD_LINE);					// �O�s��
				}
				else if (!m_nLines && m_pShopText->GetTextNo(FIRST_LINE) != COUPON_LINE /*&&
					pShopText->currentAnimNo >= TEXT_ANIM_SHOP_MENU_NO*/)	// �`�悳��Ă��Ȃ�������
				{
					m_pShopText->SetTextNo(COUPON_LINE, FIRST_LINE, FIRST_LINE);						// ��s��
					m_nLines = 1;												// ���[�v�}��
				}
				break;

			}
			break;
		case 2:
		case 3:
			switch (m_nCursor)
			{
			case 1:	// �̂�����̃Z���t
				if (m_nPage == 1 && m_nLines && m_pShopText->GetLineNum() == FIRST_LINE &&
					m_pShopText->GetTextNo(FIRST_LINE) == SAW_LINE &&
					m_pShopText->GetAnimeNo(FIRST_LINE) >= TEXT_ANIM_SHOP_MENU_NO)	// ��s�ڂ��`�悳��Ă�����
				{
					m_pShopText->SetTextNo(SAW_LINE + 1, SECOND_LINE, SECOND_LINE);				// ��s��
				}
				else if (m_nPage == 1 && m_pShopText->GetLineNum() == SECOND_LINE &&
					m_nLines && m_pShopText->GetTextNo(SECOND_LINE) == SAW_LINE + 1 &&
					m_pShopText->GetAnimeNo(SECOND_LINE) >= TEXT_ANIM_SHOP_MENU_NO)	// ��s�ڂ��`�悳��Ă�����
				{
					m_pShopText->SetTextNo(SAW_LINE + 2, THIRD_LINE, THIRD_LINE);				// �O�s��
				}
				// �w���m�F
				else if (m_nPage == 1 && m_pShopText->GetLineNum() == THIRD_LINE &&
					m_nLines && m_pShopText->GetTextNo(THIRD_LINE) == SAW_LINE + 2 &&
					m_pShopText->GetAnimeNo(THIRD_LINE) >= TEXT_ANIM_SHOP_MENU_NO)	// �O�s�ڂ��`�悳��Ă�����
				{
					m_pShopText->SetTextNo(BUY_CHECK_LINE, FIRST_LINE, FORCE_LINE);				// �l�s��
				}
				else if (m_nPage == 1 && !m_nLines && m_pShopText->GetTextNo(FIRST_LINE) != SAW_LINE /*&&
					pShopText->currentAnimNo >= TEXT_ANIM_SHOP_MENU_NO*/)// �`�悳��Ă��Ȃ�������
				{
					m_pShopText->SetTextNo(SAW_LINE, FIRST_LINE, FIRST_LINE);					// ��s��
					m_nLines = 1;											// ���[�v�}��
				}

				// �u�[�c
				if (m_nPage == 2 && m_nLines && m_pShopText->GetLineNum() == FIRST_LINE &&
					m_pShopText->GetTextNo(FIRST_LINE) == BOOTS_LINE &&
					m_pShopText->GetAnimeNo(FIRST_LINE) >= TEXT_ANIM_SHOP_MENU_NO)		// ��s�ڂ��`�悳��Ă�����
				{
					m_pShopText->SetTextNo(BOOTS_LINE + 1, SECOND_LINE, SECOND_LINE);					// ��s��
				}
				else if (m_nPage == 2 && m_nLines && m_pShopText->GetLineNum() == SECOND_LINE &&
					m_pShopText->GetTextNo(SECOND_LINE) == BOOTS_LINE + 1 &&
					m_pShopText->GetAnimeNo(SECOND_LINE) >= TEXT_ANIM_SHOP_MENU_NO)		// ��s�ڂ��`�悳��Ă�����
				{
					m_pShopText->SetTextNo(BOOTS_LINE + 2, THIRD_LINE, THIRD_LINE);					// �O�s��
				}
				else if (m_nPage == 2 && !m_nLines && m_pShopText->GetTextNo(FIRST_LINE) != BOOTS_LINE /*&&
					pShopText->currentAnimNo >= TEXT_ANIM_SHOP_MENU_NO*/)	// �`�悳��Ă��Ȃ�������
				{
					m_pShopText->SetTextNo(BOOTS_LINE, FIRST_LINE, FIRST_LINE);						// ��s��
					m_nLines = 1;												// ���[�v�}��
				}
				break;
			case 2:	// �n���}�[�Z���t
				if (m_nPage == 1 && m_nLines && m_pShopText->GetLineNum() == FIRST_LINE &&
					m_pShopText->GetTextNo(FIRST_LINE) == HAMMER_LINE &&
					m_pShopText->GetAnimeNo(FIRST_LINE) >= TEXT_ANIM_SHOP_MENU_NO)		// ��s�ڂ��`�悳��Ă�����
				{
					m_pShopText->SetTextNo(HAMMER_LINE + 1, SECOND_LINE, SECOND_LINE);					// ��s��
				}
				else if (m_nPage == 1 && m_pShopText->GetLineNum() == SECOND_LINE &&
					m_nLines && m_pShopText->GetTextNo(SECOND_LINE) == HAMMER_LINE + 1 &&
					m_pShopText->GetAnimeNo(SECOND_LINE) >= TEXT_ANIM_SHOP_MENU_NO)		// ��s�ڂ��`�悳��Ă�����
				{
					m_pShopText->SetTextNo(HAMMER_LINE + 2, THIRD_LINE, THIRD_LINE);					// �O�s��
				}
				// �w���m�F
				else if (m_nPage == 1 && m_nLines && m_pShopText->GetLineNum() == THIRD_LINE &&
					m_pShopText->GetTextNo(THIRD_LINE) == HAMMER_LINE + 2 &&
					m_pShopText->GetAnimeNo(THIRD_LINE) >= TEXT_ANIM_SHOP_MENU_NO)	// �O�s�ڂ��`�悳��Ă�����
				{
					m_pShopText->SetTextNo(BUY_CHECK_LINE, FIRST_LINE, FORCE_LINE);				// �l�s��
				}
				else if (m_nPage == 1 && !m_nLines && m_pShopText->GetTextNo(FIRST_LINE) != HAMMER_LINE /*&&
					pShopText->currentAnimNo >= TEXT_ANIM_SHOP_MENU_NO*/)	// �`�悳��Ă��Ȃ�������
				{
					m_pShopText->SetTextNo(HAMMER_LINE, FIRST_LINE, FIRST_LINE);						// ��s��
					m_nLines = 1;												// ���[�v�}��
				}
				// �ϔM�J�X�^��
				if (m_nPage == 2 && m_nLines && m_pShopText->GetLineNum() == FIRST_LINE &&
					m_pShopText->GetTextNo(FIRST_LINE) == HEAT_RESISTANT_LINE &&
					m_pShopText->GetAnimeNo(FIRST_LINE) >= TEXT_ANIM_SHOP_MENU_NO)		// ��s�ڂ��`�悳��Ă�����
				{
					m_pShopText->SetTextNo(HEAT_RESISTANT_LINE + 1, SECOND_LINE, SECOND_LINE);					// ��s��
				}
				else if (m_nPage == 2 && m_nLines && m_pShopText->GetLineNum() == SECOND_LINE &&
					m_pShopText->GetTextNo(SECOND_LINE) == HEAT_RESISTANT_LINE + 1 &&
					m_pShopText->GetAnimeNo(SECOND_LINE) >= TEXT_ANIM_SHOP_MENU_NO)		// ��s�ڂ��`�悳��Ă�����
				{
					m_pShopText->SetTextNo(HEAT_RESISTANT_LINE + 2, THIRD_LINE, THIRD_LINE);					// �O�s��
				}
				// �w���m�F
				else if (m_nPage == 2 && m_nLines && m_pShopText->GetLineNum() == THIRD_LINE &&
					m_pShopText->GetTextNo(THIRD_LINE) == HEAT_RESISTANT_LINE + 2 &&
					m_pShopText->GetAnimeNo(THIRD_LINE) >= TEXT_ANIM_SHOP_MENU_NO)	// �O�s�ڂ��`�悳��Ă�����
				{
					m_pShopText->SetTextNo(BUY_CHECK_LINE, FIRST_LINE, FORCE_LINE);				// �l�s��
				}
				else if (m_nPage == 2 && !m_nLines && m_pShopText->GetTextNo(FIRST_LINE) != HEAT_RESISTANT_LINE /*&&
					pShopText->currentAnimNo >= TEXT_ANIM_SHOP_MENU_NO*/)	// �`�悳��Ă��Ȃ�������
				{
					m_pShopText->SetTextNo(HEAT_RESISTANT_LINE, FIRST_LINE, FIRST_LINE);						// ��s��
					m_nLines = 1;												// ���[�v�}��
				}
				break;
			case 3:	// �h�����Z���t
				if (m_nLines && m_pShopText->GetLineNum() == FIRST_LINE &&
					m_pShopText->GetTextNo(FIRST_LINE) == DRILL_LINE &&
					m_pShopText->GetAnimeNo(FIRST_LINE) >= TEXT_ANIM_SHOP_MENU_NO)		// ��s�ڂ��`�悳��Ă�����
				{
					m_pShopText->SetTextNo(DRILL_LINE + 1, SECOND_LINE, SECOND_LINE);					// ��s��
				}
				else if (m_nLines && m_pShopText->GetLineNum() == SECOND_LINE &&
					m_pShopText->GetTextNo(SECOND_LINE) == DRILL_LINE + 1 &&
					m_pShopText->GetAnimeNo(SECOND_LINE) > TEXT_ANIM_SHOP_MENU_NO)		// ��s�ڂ��`�悳��Ă�����
				{
					m_pShopText->SetTextNo(DRILL_LINE + 2, THIRD_LINE, THIRD_LINE);					// �O�s��
				}
				// �w���m�F
				else if (m_nPage == 1 && m_nLines && m_pShopText->GetLineNum() == THIRD_LINE &&
					m_pShopText->GetTextNo(THIRD_LINE) == DRILL_LINE + 2 &&
					m_pShopText->GetAnimeNo(THIRD_LINE) >= TEXT_ANIM_SHOP_MENU_NO)	// �O�s�ڂ��`�悳��Ă�����
				{
					m_pShopText->SetTextNo(BUY_CHECK_LINE, FIRST_LINE, FORCE_LINE);				// �l�s��
				}
				else if (!m_nLines && m_pShopText->GetTextNo(FIRST_LINE) != DRILL_LINE /*&&
					pShopText->currentAnimNo >= TEXT_ANIM_SHOP_MENU_NO*/)	// �`�悳��Ă��Ȃ�������
				{
					m_pShopText->SetTextNo(DRILL_LINE, FIRST_LINE, FIRST_LINE);						// ��s��
					m_nLines = 1;												// ���[�v�}��
				}
				break;
			case 4:	//�m�Y��
				if (m_nLines && m_pShopText->GetLineNum() == FIRST_LINE &&
					m_pShopText->GetTextNo(FIRST_LINE) == NOZZLE_LINE &&
					m_pShopText->GetAnimeNo(FIRST_LINE) >= TEXT_ANIM_SHOP_MENU_NO)		// ��s�ڂ��`�悳��Ă�����
				{
					m_pShopText->SetTextNo(NOZZLE_LINE + 1, SECOND_LINE, SECOND_LINE);					// ��s��
				}
				else if (m_nLines && m_pShopText->GetLineNum() == SECOND_LINE &&
					m_pShopText->GetTextNo(SECOND_LINE) == NOZZLE_LINE + 1 &&
					m_pShopText->GetAnimeNo(SECOND_LINE) >= TEXT_ANIM_SHOP_MENU_NO)		// ��s�ڂ��`�悳��Ă�����
				{
					m_pShopText->SetTextNo(NOZZLE_LINE + 2, THIRD_LINE, THIRD_LINE);					// �O�s��
				}
				else if (!m_nLines && m_pShopText->GetTextNo(FIRST_LINE) != NOZZLE_LINE /*&&
					pShopText->currentAnimNo >= TEXT_ANIM_SHOP_MENU_NO*/)	// �`�悳��Ă��Ȃ�������
				{
					m_pShopText->SetTextNo(NOZZLE_LINE, FIRST_LINE, FIRST_LINE);						// ��s��
					m_nLines = 1;												// ���[�v�}��
				}
				break;

			}
			break;
		}
	}
	else	// �w�����̃Z���t
	{
		switch (m_nStage)
		{
		case 0:
			if (m_nLines && m_pShopText->GetLineNum() == FIRST_LINE &&
				m_pShopText->GetTextNo(FIRST_LINE) == SELECT_BUY_LINE &&
				m_pShopText->GetAnimeNo(FIRST_LINE) >= TEXT_ANIM_SHOP_MENU_NO)		// ��s�ڂ��`�悳��Ă�����
			{
				m_pShopText->SetTextNo(SELECT_BUY_LINE + 1, SECOND_LINE, SECOND_LINE);	// ��s��
			}
			else if (!m_nLines && m_pShopText->GetTextNo(FIRST_LINE) != SELECT_BUY_LINE/* &&
				pShopText->currentAnimNo >= TEXT_ANIM_SHOP_MENU_NO*/)// �`�悳��Ă��Ȃ�������
			{
				m_pShopText->SetTextNo(SELECT_BUY_LINE, FIRST_LINE, FIRST_LINE);	// ��s��
				m_nLines = 1;					// ���[�v�}��
			}
			break;
		case 2:
		case 3:
			if (m_nLines && m_pShopText->GetLineNum() == FIRST_LINE &&
				m_pShopText->GetTextNo(FIRST_LINE) == BUY_LINE &&
				m_pShopText->GetAnimeNo(FIRST_LINE) >= TEXT_ANIM_SHOP_MENU_NO)		// ��s�ڂ��`�悳��Ă�����
			{
				m_pShopText->SetTextNo(BUY_LINE + 1, SECOND_LINE, SECOND_LINE);	// ��s��
			}
			else if (!m_nLines && m_pShopText->GetTextNo(FIRST_LINE) != BUY_LINE/* &&
				pShopText->currentAnimNo >= TEXT_ANIM_SHOP_MENU_NO*/)// �`�悳��Ă��Ȃ�������
			{
				m_pShopText->SetTextNo(BUY_LINE, FIRST_LINE, FIRST_LINE);	// ��s��
				m_nLines = 1;					// ���[�v�}��
			}
			break;
		}
	}

	m_pShopText->Update();	// �e�L�X�g�X�V
}

void CShopMenu::MoneyEnough()									// ����������Ă��邩��������
{
	//----�J�[�\���Ƃ����̔�������----
	if (m_nPage == 1)	// 1�y�[�W�ڂ�������
	{
		// �A�C�R�������邩�ǂ���
		if (m_nCursor > m_nMaxCustom)
		{
			m_nCursor = m_noldCursor;	// �ړ��ł��Ȃ������猳�̈ʒu�ɖ߂�
		}

		//----������������Ă��邩----
		for (int i = 0; i < m_nMaxCustom; i++)
		{
			if (i >= 4)
			{
				break;
			}
			if (m_nStage != 0)
			{
				if (m_pnMoney && m_pPrice[i]->GetPrice() > *m_pnMoney)	// ������������Ȃ�
				{
					m_pShopIcon[i * 4 + i]->SetColor(0.5f, 0.5f, 0.5f, 1.0f);	// �F�ݒ�
					m_pShopIcon[i * 4 + i + 1]->SetColor(0.5f, 0.5f, 0.5f, 1.0f);	// �F�ݒ�
					m_pShopIcon[i * 4 + i + 2]->SetColor(0.5f, 0.5f, 0.5f, 1.0f);	// �F�ݒ�
					m_nEnough[i] = 0;											// ����Ă��Ȃ��ӂ炮
				}
				else if (m_pnMoney)										// ������������Ă���
				{
					m_pShopIcon[i * 4 + i]->SetColor(1.0f, 1.0f, 1.0f, 1.0f);	// �F�ݒ�
					m_pShopIcon[i * 4 + i + 1]->SetColor(1.0f, 1.0f, 1.0f, 1.0f);	// �F�ݒ�
					m_pShopIcon[i * 4 + i + 2]->SetColor(1.0f, 1.0f, 1.0f, 1.0f);	// �F�ݒ�
					m_nEnough[i] = 1;											// ����Ă���t���O
				}
			}
			else
			{
				if (m_pnMoney && m_pPrice[i]->GetPrice() > *m_pnMoney)	// ������������Ȃ�
				{
					m_pShopIcon[i * 2 + i]->SetColor(0.5f, 0.5f, 0.5f, 1.0f);	// �F�ݒ�
					m_pShopIcon[i * 2 + i + 1]->SetColor(0.5f, 0.5f, 0.5f, 1.0f);	// �F�ݒ�
					m_pShopIcon[i * 2 + i + 2]->SetColor(0.5f, 0.5f, 0.5f, 1.0f);	// �F�ݒ�
					m_nEnough[i] = 0;											// ����Ă��Ȃ��ӂ炮
				}
				else if (m_pnMoney)										// ������������Ă���
				{
					m_pShopIcon[i * 2 + i]->SetColor(1.0f, 1.0f, 1.0f, 1.0f);	// �F�ݒ�
					m_pShopIcon[i * 2 + i + 1]->SetColor(1.0f, 1.0f, 1.0f, 1.0f);	// �F�ݒ�
					m_pShopIcon[i * 2 + i + 2]->SetColor(1.0f, 1.0f, 1.0f, 1.0f);	// �F�ݒ�
					m_nEnough[i] = 1;											// ����Ă���t���O
				}
			}
		}
	}
	else if (m_nPage == 2)	// 1�y�[�W�ڂ�������
	{
		// �A�C�R�������邩�ǂ���
		if (m_nCursor > m_nMaxCustom - 4)
		{
			m_nCursor = m_noldCursor;	// �ړ��ł��Ȃ������猳�̈ʒu�ɖ߂�
		}

		//----������������Ă��邩----
		for (int i = 4; i < m_nMaxCustom; i++)
		{
			if (i >= 8)
			{
				break;
			}
			if (m_nStage != 0)
			{
				if (m_pnMoney && m_pPrice[i]->GetPrice() > *m_pnMoney)	// ������������Ȃ�
				{
					m_pShopIcon[i * 4 + i]->SetColor(0.5f, 0.5f, 0.5f, 1.0f);	// �F�ݒ�
					m_pShopIcon[i * 4 + i + 1]->SetColor(0.5f, 0.5f, 0.5f, 1.0f);	// �F�ݒ�
					m_pShopIcon[i * 4 + i + 2]->SetColor(0.5f, 0.5f, 0.5f, 1.0f);	// �F�ݒ�
					m_nEnough[i] = 0;											// ����Ă��Ȃ��ӂ炮
				}
				else if (m_pnMoney)										// ������������Ă���
				{
					m_pShopIcon[i * 4 + i]->SetColor(1.0f, 1.0f, 1.0f, 1.0f);	// �F�ݒ�
					m_pShopIcon[i * 4 + i + 1]->SetColor(1.0f, 1.0f, 1.0f, 1.0f);	// �F�ݒ�
					m_pShopIcon[i * 4 + i + 2]->SetColor(1.0f, 1.0f, 1.0f, 1.0f);	// �F�ݒ�
					m_nEnough[i] = 1;											// ����Ă���t���O
				}
			}
			else
			{
				if (m_pnMoney && m_pPrice[i]->GetPrice() > *m_pnMoney)	// ������������Ȃ�
				{
					m_pShopIcon[i * 2 + i]->SetColor(0.5f, 0.5f, 0.5f, 1.0f);	// �F�ݒ�
					m_pShopIcon[i * 2 + i + 1]->SetColor(0.5f, 0.5f, 0.5f, 1.0f);	// �F�ݒ�
					m_pShopIcon[i * 2 + i + 2]->SetColor(0.5f, 0.5f, 0.5f, 1.0f);	// �F�ݒ�
					m_nEnough[i] = 0;											// ����Ă��Ȃ��ӂ炮
				}
				else if (m_pnMoney)										// ������������Ă���
				{
					m_pShopIcon[i * 2 + i]->SetColor(1.0f, 1.0f, 1.0f, 1.0f);	// �F�ݒ�
					m_pShopIcon[i * 2 + i + 1]->SetColor(1.0f, 1.0f, 1.0f, 1.0f);	// �F�ݒ�
					m_pShopIcon[i * 2 + i + 2]->SetColor(1.0f, 1.0f, 1.0f, 1.0f);	// �F�ݒ�
					m_nEnough[i] = 1;											// ����Ă���t���O
				}
			}
		}
	}
}

void CShopMenu::IconDraw()										// �V���b�v�A�C�R���̕`��
{
	int ntemp = 0;	// �z��Q�Ɨp
	int nRoop = m_nMaxCustom;	// ���[�v�p
	int nPrice = 0;
	// �A�C�R���d�����p
	int nNozzle = -1;
	int nBoots = -1;
	int nHeat = -1;
	switch (m_nStage)
	{
	case 0:
		nBoots = 0;
		break;
		//case 1:
	case 2:
	case 3:
		nNozzle = 4;	// �m�Y�������̈ʒu
		break;
	}

	switch (m_nPage)
	{
	case 2:
		ntemp = 20;
		nRoop -= 4;
		nPrice = 4;
		nBoots = 5;		// �u�[�c�̈ʒu
		nHeat = 6;		// �ϔM�J�X�^���̈ʒu
		break;
	}

	if (m_nStage != 0)
	{
		for (int i = 0; i < nRoop; i++)
		{
			if (i > 3) break;	// 1�y�[�W���ȏ�ɂȂ�����I��
			// 1�y�[�W���̃A�C�R���`��
			// ���x��3�i�K������̂̐�p����
			if ((m_nCursor == i + 1 && m_anBuy[i] <= 2 && m_nBuy && (m_anBuyCustom == Custom::SAW ||
				m_anBuyCustom == Custom::DRILL || m_anBuyCustom == Custom::HAMMER)) ||
				m_anBuy[i + (4 * (m_nPage - 1))] == 3 && m_nPage == 1)	// ������or����؂ꂩ
			{
				// ���ɔ����Ă�����
				if (m_nCursor == i + 1 && m_anBuy[i] == 3)			// �J�[�\����������
				{
					if (m_fSizeRatio[i] > SIZE_RATIO && !m_naMinRatio[i])	// �k���d�؂�����
					{
						m_fSizeRatio[i] -= 0.06f;	// �k��
					}
					else
					{
						m_pShopIcon[ntemp + i * ICON_KIND]->SetColor(0.3f, 0.3f, 0.3f, 1.0f);	// �F�ݒ�
						m_pShopIcon[ntemp + 2 + i * ICON_KIND]->SetColor(0.3f, 0.3f, 0.3f, 1.0f);	// �F�ݒ�
						m_fSizeRatio[i] = SIZE_RATIO;	// �ŏ��{��
						m_pShopIcon[ntemp + 3 + i * ICON_KIND]->SetSizeRatio(m_fSizeRatio[i]);	// �{���ݒ�
						m_naMinRatio[i] = 1;			// �t���O�グ
					}
					m_pShopIcon[ntemp + i * ICON_KIND]->Draw();	// �A�C�R���`��
					m_pShopIcon[ntemp + 2 + i * ICON_KIND]->Draw();	// �J�X�^�}�C�Y�p�[�c�`��
					m_pShopIcon[ntemp + 4 + i * ICON_KIND]->SetSizeRatio(m_fSizeRatio[i]);	// �{���ݒ�
					m_pShopIcon[ntemp + 4 + i * ICON_KIND]->Draw();	// �I������Ă���F�̃A�C�R����`��
				}
				else if (m_anBuy[i] == 3)
				{
					m_fSizeRatio[i] = SIZE_RATIO;	// �ŏ��{��
					m_pShopIcon[ntemp + 3 + i * ICON_KIND]->SetSizeRatio(m_fSizeRatio[i]);	// �{���ݒ�
					m_pShopIcon[ntemp + i * ICON_KIND]->SetColor(0.3f, 0.3f, 0.3f, 1.0f);	// �F�ݒ�
					m_pShopIcon[ntemp + 2 + i * ICON_KIND]->SetColor(0.3f, 0.3f, 0.3f, 1.0f);	// �F�ݒ�
					m_pShopIcon[ntemp + i * ICON_KIND]->Draw();	// �A�C�R���`��
					m_pShopIcon[ntemp + 2 + i * ICON_KIND]->Draw();	// �J�X�^�}�C�Y�p�[�c�`��
					m_pShopIcon[ntemp + 3 + i * ICON_KIND]->Draw();	// ����؂�A�C�R���`��
				}
				if (!m_anBuy[i] && m_anBuyCustom >= 0)			// ���߂Ĕ���ꂽ��
				{
					m_anBuy[i] = m_nBuy;	// ����������ޔ�
					m_nBuy = 2;
					delete m_pPrice[nPrice + i];
					m_pPrice[nPrice + i] = nullptr;
					switch (m_anBuyCustom)
					{
					case Custom::SAW:
						m_pPrice[nPrice + i] = new CPrice(m_anPricePos[nPrice + i].x, m_anPricePos[nPrice + i].y,
							0.0f, PRICE_SAW_LEVEL2);
						OneCoupon(nPrice + i);	// �l�i����
						break;
					case Custom::DRILL:
						m_pPrice[nPrice + i] = new CPrice(m_anPricePos[nPrice + i].x, m_anPricePos[nPrice + i].y,
							0.0f, PRICE_DRILL_LEVEL2);
						OneCoupon(nPrice + i);	// �l�i����
						break;
					case Custom::HAMMER:
						m_pPrice[nPrice + i] = new CPrice(m_anPricePos[nPrice + i].x, m_anPricePos[nPrice + i].y,
							0.0f, PRICE_HAMMER_LEVEL2);
						OneCoupon(nPrice + i);	// �l�i����
						break;
					}
					m_anBuyCustom = -1;
				}
				else if (m_anBuy[i] == 1 && m_anBuyCustom >= 0)
				{
					m_anBuy[i] += m_nBuy;	// ����������ޔ�
					m_nBuy = 2;
					delete m_pPrice[nPrice + i];
					m_pPrice[nPrice + i] = nullptr;
					switch (m_anBuyCustom)
					{
					case Custom::SAW:
						m_pPrice[nPrice + i] = new CPrice(m_anPricePos[nPrice + i].x, m_anPricePos[nPrice + i].y,
							0.0f, PRICE_SAW_LEVEL3);
						OneCoupon(nPrice + i);	// �l�i����
						break;
					case Custom::DRILL:
						m_pPrice[nPrice + i] = new CPrice(m_anPricePos[nPrice + i].x, m_anPricePos[nPrice + i].y,
							0.0f, PRICE_DRILL_LEVEL3);
						OneCoupon(nPrice + i);	// �l�i����
						break;
					case Custom::HAMMER:
						m_pPrice[nPrice + i] = new CPrice(m_anPricePos[nPrice + i].x, m_anPricePos[nPrice + i].y,
							0.0f, PRICE_HAMMER_LEVEL3);
						OneCoupon(nPrice + i);	// �l�i����
						break;
					}
					m_anBuyCustom = -1;
				}
				else if (m_anBuy[i] == 2 && m_anBuyCustom >= 0)
				{
					m_anBuy[i] += m_nBuy;	// ����������ޔ�
					m_nBuy = 2;
					m_anBuyCustom = -1;
				}
			}
			// ���x��2�i�K������̂̐�p����
			else if ((m_nCursor == i + 1 && m_anBuy[i] <= 1 && m_nBuy && m_nNozzle) ||
				m_anBuy[i + (4 * (m_nPage - 1))] == 2 && i + 1 == nNozzle)	// ������or����؂ꂩ
			{
				// ���ɔ����Ă�����
				if (m_nCursor == i + 1 && m_anBuy[i] == 2)			// �J�[�\����������
				{
					if (m_fSizeRatio[i] > SIZE_RATIO && !m_naMinRatio[i])	// �k���d�؂�����
					{
						m_fSizeRatio[i] -= 0.06f;	// �k��
					}
					else
					{
						m_pShopIcon[ntemp + i * ICON_KIND]->SetColor(0.3f, 0.3f, 0.3f, 1.0f);	// �F�ݒ�
						m_pShopIcon[ntemp + 2 + i * ICON_KIND]->SetColor(0.3f, 0.3f, 0.3f, 1.0f);	// �F�ݒ�
						m_fSizeRatio[i] = SIZE_RATIO;	// �ŏ��{��
						m_pShopIcon[ntemp + 3 + i * ICON_KIND]->SetSizeRatio(m_fSizeRatio[i]);	// �{���ݒ�
						m_naMinRatio[i] = 1;			// �t���O�グ
					}
					m_pShopIcon[ntemp + i * ICON_KIND]->Draw();	// �A�C�R���`��
					m_pShopIcon[ntemp + 2 + i * ICON_KIND]->Draw();	// �J�X�^�}�C�Y�p�[�c�`��
					m_pShopIcon[ntemp + 4 + i * ICON_KIND]->SetSizeRatio(m_fSizeRatio[i]);	// �{���ݒ�
					m_pShopIcon[ntemp + 4 + i * ICON_KIND]->Draw();	// �I������Ă���F�̃A�C�R����`��
				}
				else if (m_anBuy[i] == 2)
				{
					m_fSizeRatio[i] = SIZE_RATIO;	// �ŏ��{��
					m_pShopIcon[ntemp + 3 + i * ICON_KIND]->SetSizeRatio(m_fSizeRatio[i]);	// �{���ݒ�
					m_pShopIcon[ntemp + i * ICON_KIND]->SetColor(0.3f, 0.3f, 0.3f, 1.0f);	// �F�ݒ�
					m_pShopIcon[ntemp + 2 + i * ICON_KIND]->SetColor(0.3f, 0.3f, 0.3f, 1.0f);	// �F�ݒ�
					m_pShopIcon[ntemp + i * ICON_KIND]->Draw();	// �A�C�R���`��
					m_pShopIcon[ntemp + 2 + i * ICON_KIND]->Draw();	// �J�X�^�}�C�Y�p�[�c�`��
					m_pShopIcon[ntemp + 3 + i * ICON_KIND]->Draw();	// ����؂�A�C�R���`��
				}
				if (!m_anBuy[i] && m_nNozzle)			// ���߂Ĕ���ꂽ��
				{
					m_anBuy[i] = m_nBuy;	// ����������ޔ�
					m_nBuy = 2;
					m_nNozzle = 0;
					delete m_pPrice[nPrice + i];
					m_pPrice[nPrice + i] = nullptr;
					m_pPrice[nPrice + i] = new CPrice(LEFT_PRICE_POSX + PRICE_WIDTHX - 40.0f,					// ���i���
						LEFT_PRICE_POSY + PRICE_WIDTHY,
						0.0f, PRICE_NOZZLE_LEVEL3);
					OneCoupon(nPrice + i);	// �l�i����
				}
				else if (m_anBuy[i] == 1 && m_nNozzle)
				{
					m_anBuy[i] += m_nBuy;	// ����������ޔ�
					m_nBuy = 2;
					m_nNozzle = 0;
				}
			}
			else if ((m_nCursor == i + 1 && !m_anBuy[i + (4 * (m_nPage - 1))] && m_nBuy && (m_anBuyCustom == Custom::BOOTS ||
				m_anBuyCustom == Custom::HEAT_RESISTANT)) ||
				(m_anBuy[i + (4 * (m_nPage - 1))] && (i == nBoots - 5 || i == nHeat - 5)))	// �J�[�\�������蔃����or����؂ꂩ
			{
				// ���̑�
				// ���ɔ����Ă��ăJ�[�\���������ɂ�������
				if (m_nCursor == i + 1 && (i == nBoots - 5 || i == nHeat - 5))
				{
					if (m_fSizeRatio[i + (4 * (m_nPage - 1))] > SIZE_RATIO && !m_naMinRatio[i + (4 * (m_nPage - 1))])	// �k���d�؂�����
					{
						m_fSizeRatio[i + (4 * (m_nPage - 1))] -= 0.06f;	// �k��
					}
					else
					{
						m_pShopIcon[ntemp + i * ICON_KIND]->SetColor(0.3f, 0.3f, 0.3f, 1.0f);	// �F�ݒ�
						m_pShopIcon[ntemp + 2 + i * ICON_KIND]->SetColor(0.3f, 0.3f, 0.3f, 1.0f);	// �F�ݒ�
						m_fSizeRatio[i + (4 * (m_nPage - 1))] = SIZE_RATIO;	// �ŏ��{��
						m_pShopIcon[ntemp + 3 + i * ICON_KIND]->SetSizeRatio(m_fSizeRatio[i + (4 * (m_nPage - 1))]);	// �{���ݒ�
						m_naMinRatio[i + (4 * (m_nPage - 1))] = 1;			// �t���O�グ
					}
					m_pShopIcon[ntemp + i * ICON_KIND]->Draw();	// �A�C�R���`��
					m_pShopIcon[ntemp + 2 + i * ICON_KIND]->Draw();	// �J�X�^�}�C�Y�p�[�c�`��
					m_pShopIcon[ntemp + 4 + i * ICON_KIND]->SetSizeRatio(m_fSizeRatio[i + (4 * (m_nPage - 1))]);	// �{���ݒ�
					m_pShopIcon[ntemp + 4 + i * ICON_KIND]->Draw();	// �I������Ă���F�̃A�C�R����`��
				}
				// �J�[�\�����Ȃ�������
				// ���̑��̃J�X�^���A�C�R��
				else if (i == nBoots - 5 || i == nHeat - 5)
				{
					m_fSizeRatio[i + (4 * (m_nPage - 1))] = SIZE_RATIO;	// �ŏ��{��
					m_pShopIcon[ntemp + 3 + i * ICON_KIND]->SetSizeRatio(m_fSizeRatio[i + (4 * (m_nPage - 1))]);	// �{���ݒ�
					m_pShopIcon[ntemp + i * ICON_KIND]->SetColor(0.3f, 0.3f, 0.3f, 1.0f);	// �F�ݒ�
					m_pShopIcon[ntemp + 2 + i * ICON_KIND]->SetColor(0.3f, 0.3f, 0.3f, 1.0f);	// �F�ݒ�
					m_pShopIcon[ntemp + i * ICON_KIND]->Draw();	// �A�C�R���`��
					m_pShopIcon[ntemp + 2 + i * ICON_KIND]->Draw();	// �J�X�^�}�C�Y�p�[�c�`��
					m_pShopIcon[ntemp + 3 + i * ICON_KIND]->Draw();	// ����؂�A�C�R���`��
				}
				// ���̑������߂Ĕ���ꂽ��
				if (!m_anBuy[i + (4 * (m_nPage - 1))])
				{
					m_anBuy[i + (4 * (m_nPage - 1))] = m_nBuy;	// ����������ޔ�
					m_nBuy = 2;
				}

			}
			// �܂������ĂȂ���
			// �J�[�\�������邩
			else if (m_nCursor == i + 1)
			{
				// �J�X�^���p�[�c�g�k
				if (!m_nMAXRatio)	// �ő�{������Ȃ�������
				{
					m_fRatio += SHOP_RATIO;		// �{���ݒ�
					if (m_fRatio >= ENOUGH_MAX_RATIO && m_nEnough[i])	// ������������čő�{���𒴂�����
					{
						m_nMAXRatio ^= 1;	// �t���O�グ
					}
					else if (m_fRatio >= NOT_ENOUGH_MAX_RATIO && !m_nEnough[i])	// ������������Ȃ��čő�{���𒴂�����
					{
						m_nMAXRatio ^= 1;	// �t���O�グ
					}
				}
				// ������������Ă�����
				else
				{
					m_fRatio -= SHOP_RATIO;		// �{���ݒ�
					if (m_fRatio <= ENOUGH_MIN_RATIO && m_nEnough[i])	// ������������čŏ��{����菬�����Ȃ�����
					{
						m_nMAXRatio ^= 1;	// �t���O�グ
					}
					else if (m_fRatio <= NOT_ENOUGH_MIN_RATIO && !m_nEnough[i])	// ������������Ȃ��čŏ��{���𒴂�����
					{
						m_nMAXRatio ^= 1;	// �t���O�グ
					}
				}
				m_pShopIcon[ntemp + 1 + i * ICON_KIND]->Draw();		// �I������Ă���F�̃A�C�R����`��
				m_pShopIcon[ntemp + 2 + i * ICON_KIND]->SetSizeRatio(m_fRatio);	// �{���ݒ�
				m_pShopIcon[ntemp + 2 + i * ICON_KIND]->Draw();		// �J�X�^�}�C�Y�p�[�c�`��
				m_pShopText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);	// �e�L�X�g�F�ݒ�
				m_pShopText->Draw();		// �J�X�^���̐����̃Z���t��`��
			}
			else
			{
				m_pShopIcon[ntemp + i * ICON_KIND]->Draw();		// �A�C�R���`��
				m_pShopIcon[ntemp + 2 + i * ICON_KIND]->ResetSize();	// �T�C�Y���Z�b�g
				m_pShopIcon[ntemp + 2 + i * ICON_KIND]->Draw();		// �J�X�^�}�C�Y�p�[�c�`��
			}
			m_pPrice[nPrice + i]->SetColor(1.0f, 1.0f, 1.0f, 1.0f);		// �l�i�̐F�ݒ�
			m_pPrice[nPrice + i]->Draw();							// �l�i���F�ŕ`��
		}
	}
	// �Z���N�g�V�[���V���b�v
	else
	{
		for (int i = 0; i < nRoop; i++)
		{
			if (i > 3) break;	// 1�y�[�W���ȏ�ɂȂ�����I��
			// �A�C�e��
			// 1�y�[�W���̃A�C�R���`��
			if ((m_nCursor == i + 1 && !m_anBuy[i] && m_nBuy) ||
				m_anBuy[i])	// �J�[�\�������蔃����or����؂ꂩ
			{
				// ���ɔ����Ă��ăJ�[�\���������ɂ�������
				if (m_nCursor == i + 1)
				{
					m_pShopIcon[ntemp + 1 + i * SELECT_ICON_KIND]->SetColor(0.3f, 0.3f, 0.3f, 1.0f);	// �F�ݒ�
					m_pShopIcon[ntemp + 2 + i * SELECT_ICON_KIND]->SetColor(0.3f, 0.3f, 0.3f, 1.0f);	// �F�ݒ�
					m_pShopIcon[ntemp + 1 + i * SELECT_ICON_KIND]->Draw();	// �A�C�R���`��
					m_pShopIcon[ntemp + 2 + i * SELECT_ICON_KIND]->Draw();	// �J�X�^�}�C�Y�p�[�c�`��
				}
				// �J�[�\�����Ȃ�������
				else
				{
					m_pShopIcon[ntemp + i * SELECT_ICON_KIND]->SetColor(0.3f, 0.3f, 0.3f, 1.0f);	// �F�ݒ�
					m_pShopIcon[ntemp + 2 + i * SELECT_ICON_KIND]->SetColor(0.3f, 0.3f, 0.3f, 1.0f);	// �F�ݒ�
					m_pShopIcon[ntemp + i * SELECT_ICON_KIND]->Draw();	// �A�C�R���`��
					m_pShopIcon[ntemp + 2 + i * SELECT_ICON_KIND]->Draw();	// �J�X�^�}�C�Y�p�[�c�`��
				}
				// �A�C�e�������߂Ĕ���ꂽ��
				if (!m_anBuy[i])
				{
					m_anBuy[i] = m_nBuy;	// ����������ޔ�
					m_nBuy = 2;
				}

			}
			// �܂������ĂȂ�����
			// �J�[�\�������邩
			else if (m_nCursor == i + 1)
			{
				// �A�C�e���g�k
				if (!m_nMAXRatio)	// �ő�{������Ȃ�������
				{
					m_fRatio += SHOP_RATIO;		// �{���ݒ�
					if (m_fRatio >= ENOUGH_MAX_RATIO && m_nEnough[i])	// ������������čő�{���𒴂�����
					{
						m_nMAXRatio ^= 1;	// �t���O�グ
					}
					else if (m_fRatio >= NOT_ENOUGH_MAX_RATIO && !m_nEnough[i])	// ������������Ȃ��čő�{���𒴂�����
					{
						m_nMAXRatio ^= 1;	// �t���O�グ
					}
				}
				// ������������Ă�����
				else
				{
					m_fRatio -= SHOP_RATIO;		// �{���ݒ�
					if (m_fRatio <= ENOUGH_MIN_RATIO && m_nEnough[i])	// ������������čŏ��{����菬�����Ȃ�����
					{
						m_nMAXRatio ^= 1;	// �t���O�グ
					}
					else if (m_fRatio <= NOT_ENOUGH_MIN_RATIO && !m_nEnough[i])	// ������������Ȃ��čŏ��{���𒴂�����
					{
						m_nMAXRatio ^= 1;	// �t���O�グ
					}
				}
				m_pShopIcon[ntemp + 1 + i * SELECT_ICON_KIND]->Draw();		// �I������Ă���F�̃A�C�R����`��
				m_pShopIcon[ntemp + 2 + i * SELECT_ICON_KIND]->SetSizeRatio(m_fRatio);	// �{���ݒ�
				m_pShopIcon[ntemp + 2 + i * SELECT_ICON_KIND]->Draw();		// �J�X�^�}�C�Y�p�[�c�`��
				m_pShopText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);			// �e�L�X�g�F�ݒ�
				m_pShopText->Draw();		// �J�X�^���̐����̃Z���t��`��
			}
			// �����ĂȂ��ăJ�[�\���������Ă��Ȃ�������
			else
			{
				m_pShopIcon[ntemp + i * SELECT_ICON_KIND]->Draw();		// �A�C�R���`��
				m_pShopIcon[ntemp + 2 + i * SELECT_ICON_KIND]->ResetSize();	// �T�C�Y���Z�b�g
				m_pShopIcon[ntemp + 2 + i * SELECT_ICON_KIND]->Draw();		// �J�X�^�}�C�Y�p�[�c�`��
			}
			m_pPrice[nPrice + i]->SetColor(1.0f, 1.0f, 1.0f, 1.0f);		// �l�i�̐F�ݒ�
			m_pPrice[nPrice + i]->Draw();							// �l�i���F�ŕ`��
		}
	}
}

void CShopMenu::PageSetDraw()
{
	//----�X���b�V��---
	m_BaseShopMenu[5].pos = DirectX::XMFLOAT3(590.0f, 160.0f, 0.0f);	// �y�[�W�\�L�̋�؂蕔��

	for (int i = 1; i < 3; i++)
	{
		switch (i)
		{
		case 1:
			switch (m_nPage)	// ���݂̊J���Ă���y�[�W
			{
			case 1:				// 1�y�[�W��
				//----1----
				m_BaseShopMenu[6].size = DirectX::XMFLOAT2(m_BaseShopMenu[5].pTexture->GetWidth() * 0.07f,
					m_BaseShopMenu[5].pTexture->GetHeight() * 0.07f);						// �T�C�Y
				m_BaseShopMenu[6].pos = DirectX::XMFLOAT3(575.0f, 152.0f, 0.0f);				// ���W
				m_BaseShopMenu[6].sizeTexCoord = DirectX::XMFLOAT2(1.0f / PAGE_SPLIT_X,
					1.0f / PAGE_SPLIT_Y);													// �e�N�X�`���T�C�Y�ݒ�
				m_BaseShopMenu[6].posTexCoord = DirectX::XMFLOAT2(m_BaseShopMenu[6].sizeTexCoord.x * (1 % PAGE_SPLIT_X)
					, m_BaseShopMenu[6].sizeTexCoord.y * (1 / PAGE_SPLIT_X));				// �e�N�X�`�����W�ݒ�
				break;

			case 2:				// 2�y�[�W��
				//----2----
				m_BaseShopMenu[6].size = DirectX::XMFLOAT2(m_BaseShopMenu[5].pTexture->GetWidth() * 0.07f,
					m_BaseShopMenu[5].pTexture->GetHeight() * 0.07f);						// �T�C�Y
				m_BaseShopMenu[6].pos = DirectX::XMFLOAT3(575.0f, 152.0f, 0.0f);				// ���W
				m_BaseShopMenu[6].sizeTexCoord = DirectX::XMFLOAT2(1.0f / PAGE_SPLIT_X,
					1.0f / PAGE_SPLIT_Y);													// �e�N�X�`���T�C�Y�ݒ�
				m_BaseShopMenu[6].posTexCoord = DirectX::XMFLOAT2(m_BaseShopMenu[6].sizeTexCoord.x * (2 % PAGE_SPLIT_X)
					, m_BaseShopMenu[6].sizeTexCoord.y * (2 / PAGE_SPLIT_X));				// �e�N�X�`�����W�ݒ�
				break;
			}
			break;
		case 2:
			switch (m_nTotalPage)	// �ő�y�[�W��
			{
			case 1:
				//----1----		// �ő�1�y�[�W
				m_BaseShopMenu[7].size = DirectX::XMFLOAT2(m_BaseShopMenu[5].pTexture->GetWidth() * 0.07f,
					m_BaseShopMenu[5].pTexture->GetHeight() * 0.07f);						// �T�C�Y
				m_BaseShopMenu[7].pos = DirectX::XMFLOAT3(613.0f, 176.0f, 0.0f);			// ���W
				m_BaseShopMenu[7].sizeTexCoord = DirectX::XMFLOAT2(1.0f / PAGE_SPLIT_X,
					1.0f / PAGE_SPLIT_Y);													// �e�N�X�`���T�C�Y�ݒ�
				m_BaseShopMenu[7].posTexCoord = DirectX::XMFLOAT2(m_BaseShopMenu[7].sizeTexCoord.x * (1 % PAGE_SPLIT_X)
					, m_BaseShopMenu[7].sizeTexCoord.y * (1 / PAGE_SPLIT_X));				// �e�N�X�`�����W�ݒ�
				break;
			case 2:
				//----2----		// �ő�2�y�[�W
				m_BaseShopMenu[7].size = DirectX::XMFLOAT2(m_BaseShopMenu[5].pTexture->GetWidth() * 0.07f,
					m_BaseShopMenu[5].pTexture->GetWidth() * 0.07f);						// �T�C�Y
				m_BaseShopMenu[7].pos = DirectX::XMFLOAT3(613.0f, 176.0f, 0.0f);			// ���W
				m_BaseShopMenu[7].sizeTexCoord = DirectX::XMFLOAT2(1.0f / PAGE_SPLIT_X,
					1.0f / PAGE_SPLIT_Y);													// �e�N�X�`���T�C�Y�ݒ�
				m_BaseShopMenu[7].posTexCoord = DirectX::XMFLOAT2(m_BaseShopMenu[7].sizeTexCoord.x * (2 % PAGE_SPLIT_X)
					, m_BaseShopMenu[7].sizeTexCoord.y * (2 / PAGE_SPLIT_X));				// �e�N�X�`�����W�ݒ�
				break;
			}
			break;
		}
	}
}

// �����p
void CShopMenu::ALLCoupon()			// �l�i�\�������֐�
{
	// �X�e�[�W���Ƃɏ�������
	switch (m_nStage)
	{
	case 2:	// 2�X�e�[�W
		for (int i = 0; i < m_nMaxCustom; i++)	// �X�e�[�W���ő吔��
		{
			// �l�i�̕\����ύX
			m_pPrice[i]->PriceSale(SHOP_COUPON);

		}
		break;
	}
}

// �P�̗p
void CShopMenu::OneCoupon(int element)		// �l�i�\�������֐�
{
	if (m_nCoupon)
	{
		m_pPrice[element]->PriceSale(SHOP_COUPON);
	}
}

bool CShopMenu::GetShop()							// �V���b�v��ʂ���邩
{
	return m_bShop;
}

void CShopMenu::SetMoney(int * Money)				// �������Z�b�g
{
	m_pnMoney = Money;
}

void CShopMenu::SetCustom(int * Custom)				// �J�X�^���Z�b�g
{
	m_pnCustom = Custom;
}

void CShopMenu::SetItem(int * Item)
{
	m_pnItem = Item;
}


void CShopMenu::SetShopSuction(Suction * pSuction)	// �z�����݃N���X�Z�b�g
{
	m_pShop->SetSuction(pSuction);	// Shop��Suction�N���X�Z�b�g
}


void CShopMenu::SetItemUse(int coupon)	// �A�C�e�����g�p���ꂽ��
{
	m_nCoupon = coupon;
}

CShop * CShopMenu::GetShopCustom()
{
	return m_pShop;
}