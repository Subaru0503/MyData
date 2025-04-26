//----Shop.cpp----
//----�C���N���[�h��----
#include "Shop.h"
#include "Input.h"
#include "Value.h"
#include "XController.h"
#include "ObjectManager.h"
#include "SceneGame.h"

CShop::CShop()	// �R���X�g���N�^
//----�J�X�^���p�[�c----
	: m_saw(3)		// �̂�����݌ɐ�
	, m_hammer(3)	// �n���}�[�݌ɐ�
	, m_drill(3)	// �h�����݌ɐ�
	, m_Boots(1)	// �u�[�c�݌ɐ�
	//, m_hose(1)		// �z�[�X�݌ɐ�
	, m_Nozzle(2)	// �m�Y���݌ɐ�
	, m_nHeat(1)	// �ϔM�J�X�^���݌ɐ�
//----�A�C�e��----
	, m_drink(1)	// �h�����N�݌ɐ�
	, m_nozzle(1)	// �m�Y�������݌ɐ�
	, m_timer(1)	// ���ԉ����݌ɐ�
	, m_coupon(1)	// �N�[�|���݌ɐ�
	, m_fCoupon(1.0f)
	, m_bDrill(false)
	, m_bSaw(false)
	, m_bHammer(false)
{
}

CShop::~CShop()	// �f�X�g���N�^
{

}

void CShop::Buy(int* Custom, int* Money, int Cursor, int* Buy, int* Nozzle)	// �J�X�^�}�C�Y�p�[�c�w��
{
	// �̂�����
	// �݌ɐ��Ń��x���𔻒f
	if (Cursor == Custom::SAW && ((Custom[SAW] == 0 && *Money >= PRICE_SAW_LEVEL1 * m_fCoupon && m_saw == 3) ||
		(Custom[SAW] == 1 && *Money >= PRICE_SAW_LEVEL2 * m_fCoupon && m_saw == 2) ||
		(Custom[SAW] == 2 && *Money >= PRICE_SAW_LEVEL3 * m_fCoupon && m_saw == 1)))
	{
		switch (m_saw)
		{
		case 3:
			*Money -= (int)(PRICE_SAW_LEVEL1 * m_fCoupon);	// �̂����背�x��1�̒l�i������
			m_saw = 2;							// �݌ɐ������炷
			Custom[SAW] = 1;					// �J�X�^���ɃZ�b�g
			m_pUI_Money->AddMoney
			(-PRICE_SAW_LEVEL1 * m_fCoupon);	// �̂����背�x��1�̒l�i������
			*Buy = 1;							// �w���t���O�グ
			m_bSaw = true;
			break;
		case 2:
			*Money -= (int)(PRICE_SAW_LEVEL2 * m_fCoupon);	// �̂����背�x��2�̒l�i������
			m_saw = 1;							// �݌ɐ������炷
			Custom[SAW] = 2;					// �J�X�^���ɃZ�b�g
			m_pUI_Money->AddMoney
			(-PRICE_SAW_LEVEL2 * m_fCoupon);	// �̂����背�x��2�̒l�i������
			*Buy = 1;							// �w���t���O�グ
			break;
		case 1:
			*Money -= (int)(PRICE_SAW_LEVEL3 * m_fCoupon);	// �̂����背�x��3�̒l�i������
			m_saw = 0;							// �݌ɐ������炷
			Custom[SAW] = 3;					// �J�X�^���ɃZ�b�g
			m_pUI_Money->AddMoney
			(-PRICE_SAW_LEVEL3 * m_fCoupon);	// �̂����背�x��3�̒l�i������
			*Buy = 1;							// �w���t���O�グ
			break;
		}
	}
	// �h����
	// �݌ɐ��Ń��x���𔻒f
	else if (Cursor == Custom::DRILL && ((Custom[DRILL] == 0 && *Money >= PRICE_DRILL_LEVEL1 * m_fCoupon && m_drill == 3) ||
		(Custom[DRILL] == 1 && *Money >= PRICE_DRILL_LEVEL2 * m_fCoupon && m_drill == 2) ||
		(Custom[DRILL] == 2 && *Money >= PRICE_DRILL_LEVEL3 * m_fCoupon && m_drill == 1)))
	{
		switch (m_drill)
		{
		case 3:
			*Money -= PRICE_DRILL_LEVEL1 * m_fCoupon;	// �h�������x��1�̒l�i������
			m_drill = 2;									// �݌ɐ������炷
			Custom[DRILL] = 1;			// �J�X�^���Z�b�g
			m_pUI_Money->AddMoney
			(-PRICE_DRILL_LEVEL1 * m_fCoupon);			// �h�������x��1�̒l�i������
			*Buy = 1;									// �w���t���O�グ
			m_bDrill = true;
			break;
		case 2:
			*Money -= PRICE_DRILL_LEVEL2 * m_fCoupon;	// �h�������x��2�̒l�i������
			m_drill = 1;									// �݌ɐ������炷
			Custom[DRILL] = 2;			// �J�X�^���Z�b�g
			m_pUI_Money->AddMoney
			(-PRICE_DRILL_LEVEL2 * m_fCoupon);			// �h�������x��2�̒l�i������
			*Buy = 1;									// �w���t���O�グ
			break;
		case 1:
			*Money -= PRICE_DRILL_LEVEL3 * m_fCoupon;	// �h�������x��3�̒l�i������
			m_drill = 0;									// �݌ɐ������炷
			Custom[DRILL] = 3;			// �J�X�^���Z�b�g
			m_pUI_Money->AddMoney
			(-PRICE_DRILL_LEVEL3 * m_fCoupon);			// �h�������x��3�̒l�i������
			*Buy = 1;									// �w���t���O�グ
			break;
		}
		//break;
	}
	// �n���}�[
	// �݌ɐ��Ń��x���𔻒f
	else if ((Custom[HAMMER] == 0 || Custom[HAMMER] == 1 || Custom[HAMMER] == 2) &&
		Cursor == Custom::HAMMER && ((*Money >= PRICE_HAMMER_LEVEL1 * m_fCoupon && m_hammer == 3) ||
		(*Money >= PRICE_HAMMER_LEVEL2 * m_fCoupon && m_hammer == 2) ||
			(*Money >= PRICE_HAMMER_LEVEL3 * m_fCoupon && m_hammer == 1)))
	{
		switch (m_hammer)
		{
		case 3:
			*Money -= PRICE_HAMMER_LEVEL1 * m_fCoupon;	// �n���}�[���x��1�̒l�i������
			m_hammer = 2;									// �݌ɐ������炷
			Custom[HAMMER] = 1;			// �J�X�^���Z�b�g
			m_pUI_Money->AddMoney
			(-PRICE_HAMMER_LEVEL1 * m_fCoupon);			// �n���}�[���x��1�̒l�i������
			*Buy = 1;									// �w���t���O�グ
			m_bHammer = true;
			break;
		case 2:
			*Money -= PRICE_HAMMER_LEVEL2 * m_fCoupon;	// �n���}�[���x��2�̒l�i������
			m_hammer = 1;									// �݌ɐ������炷
			Custom[HAMMER] = 2;			// �J�X�^���Z�b�g
			m_pUI_Money->AddMoney
			(-PRICE_HAMMER_LEVEL2 * m_fCoupon);			// �n���}�[���x��2�̒l�i������
			*Buy = 1;									// �w���t���O�グ
			break;
		case 1:
			*Money -= PRICE_HAMMER_LEVEL3 * m_fCoupon;	// �n���}�[���x��3�̒l�i������
			m_hammer = 0;									// �݌ɐ������炷
			Custom[HAMMER] = 3;			// �J�X�^���Z�b�g
			m_pUI_Money->AddMoney
			(-PRICE_HAMMER_LEVEL3 * m_fCoupon);			// �n���}�[���x��3�̒l�i������
			*Buy = 1;									// �w���t���O�グ
			break;
		}
		//break;
	}
	else if (Custom[BOOTS] == 0 && Cursor == Custom::BOOTS && *Money >= PRICE_BOOTS * m_fCoupon &&	// �u�[�c
		m_Boots > 0)
	{
		*Money -= PRICE_BOOTS * m_fCoupon;		// �u�[�c�̒l�i������
		m_Boots--;								// �݌ɐ������炷
		Custom[BOOTS] = 1;				// �J�X�^���Z�b�g
		m_pUI_Money->AddMoney
		(-PRICE_BOOTS * m_fCoupon);				// �u�[�c�̒l�i������
		*Buy = 1;								// �w���t���O�グ
		//break;
	}
	else if (Custom[HEAT_RESISTANT] == 0 && Cursor == Custom::HEAT_RESISTANT && *Money >= PRICE_HEAT_RESISTANT * m_fCoupon &&	// �ϔM�J�X�^��
		m_nHeat > 0)
	{
		*Money -= PRICE_HEAT_RESISTANT * m_fCoupon;	// �ϔM�J�X�^���̒l�i������
		m_nHeat--;									// �݌ɐ������炷
		Custom[HEAT_RESISTANT] = 1;					// �J�X�^���Z�b�g
		m_pUI_Money->AddMoney
		(-PRICE_HEAT_RESISTANT * m_fCoupon);		// �ϔM�J�X�^���̒l�i������
		*Buy = 1;									// �w���t���O�グ
	}
	else if ((Custom[GAME_NOZZLE] == 0 || Custom[GAME_NOZZLE] == 2) &&
		Cursor == Custom::GAME_NOZZLE && ((*Money >= PRICE_NOZZLE_LEVEL2 * m_fCoupon && m_Nozzle > 1) ||
		(*Money >= PRICE_NOZZLE_LEVEL3 * m_fCoupon && m_Nozzle > 0)))
	{
		switch (m_Nozzle)
		{
		case 2:
			*Money -= PRICE_NOZZLE_LEVEL2 * m_fCoupon;	// �m�Y�����x��2�̒l�i������
			m_Nozzle--;									// �݌ɐ������炷
			Custom[GAME_NOZZLE] = 2;					// �J�X�^���Z�b�g
			m_pUI_Money->AddMoney
			(-PRICE_NOZZLE_LEVEL2 * m_fCoupon);			// �m�Y�����x��2�̒l�i������
			m_pSuction->NozzleLevelUp();				// �z�����݃��x���A�b�v
			*Buy = 1;									// �w���t���O�グ
			*Nozzle = 1;								// �m�Y�������w���t���O�グ
			break;
		case 1:
			*Money -= PRICE_NOZZLE_LEVEL3 * m_fCoupon;	// �m�Y�����x��2�̒l�i������
			m_Nozzle--;									// �݌ɐ������炷
			Custom[GAME_NOZZLE] = 3;							// �J�X�^���Z�b�g
			m_pUI_Money->AddMoney
			(-PRICE_NOZZLE_LEVEL3 * m_fCoupon);			// �m�Y�����x��2�̒l�i������
			m_pSuction->NozzleLevelUp();				// �z�����݃��x���A�b�v
			*Buy = 1;									// �w���t���O�グ
			*Nozzle = 1;								// �m�Y�������w���t���O�グ
			break;
		}
	}
}

void CShop::ItemBuy(int* Item, int* Money, int Cursor, int* Buy)
{
	for (int i = 0; i < MAX_ITEM; i++)
	{
		if (Item[i] != 0) continue;
		if (Cursor == Item::DRINK && *Money >= PRICE_DRINK &&	// �h�����N
			/*Item[i] != Item::SAW &&*/ m_drink > 0)
		{
			*Money -= PRICE_DRINK;					// �h�����N�̒l�i������
			m_drink--;								// �݌ɐ������炷
			Item[0] = Item::DRINK;					// �A�C�e���g�p�ɃZ�b�g
			m_pUI_Money->AddMoney(-PRICE_DRINK);	// �h�����N�̒l�i������
			*Buy = 1;								// �w���t���O�グ
			break;
		}
		else if (Cursor == Item::NOZZLE && *Money >= PRICE_NOZZLE &&	// �m�Y������
			m_nozzle > 0)
		{
			*Money -= PRICE_NOZZLE;					// �m�Y�������̒l�i������
			m_nozzle--;								// �݌ɐ������炷
			Item[1] = Item::NOZZLE;					// �A�C�e���g�p�ɃZ�b�g
			m_pUI_Money->AddMoney(-PRICE_NOZZLE);	// �m�Y�������̒l�i������
			*Buy = 1;								// �w���t���O�グ
			break;
		}
		else if (Cursor == Item::TIMER && *Money >= PRICE_TIMER &&	// ���ԉ���
			m_timer > 0)
		{
			*Money -= PRICE_TIMER;					// ���ԉ����A�C�e���̒l�i������
			m_timer--;								// �݌ɐ������炷
			Item[2] = Item::TIMER;					// �A�C�e���g�p�ɃZ�b�g
			m_pUI_Money->AddMoney(-PRICE_TIMER);	// ���ԉ����A�C�e���̒l�i������
			*Buy = 1;								// �w���t���O�グ
			break;
		}
		else if (Cursor == Item::COUPON && *Money >= PRICE_COUPON &&	// �N�[�|��
			m_coupon > 0)
		{
			*Money -= PRICE_COUPON;					// �N�[�|���̒l�i������
			m_coupon--;								// �݌ɐ������炷
			Item[3] = Item::COUPON;					// �A�C�e���g�p�ɃZ�b�g
			m_pUI_Money->AddMoney(-PRICE_COUPON);	// �N�[�|���̒l�i������
			*Buy = 1;								// �w���t���O�グ
			break;
		}
		break;
	}
}

void CShop::SetSuction(Suction * pSuction)							// �z�����݃N���X�Q�b�g
{
	m_pSuction = pSuction;
}

void CShop::SetItem(float coupon)									// �A�C�e�����g�p���Ă��邩
{
	m_fCoupon = coupon;
}

void CShop::SetUI(CUI * ui)
{
	m_pUI_Money = ui;
}

void CShop::StockReduse()											// �݌ɐ�����
{
	m_Nozzle--;
}

bool* CShop::GetDrill()
{
	return &m_bDrill;
}

bool* CShop::GetSaw()
{
	return &m_bSaw;
}

bool* CShop::GetHammer()
{
	return &m_bHammer;
}