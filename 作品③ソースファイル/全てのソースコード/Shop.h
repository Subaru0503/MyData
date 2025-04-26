#// Shop.h

//----�C���N���[�h�K�[�h----
#ifndef __SHOP_H__
#define __SHOP_H__

//----�C���N���[�h��----
#include "UI.h"
#include "Suction.h"

//----�}�N����`----
//----�J�X�^���A�C�R��----
#define MAX_LEVEL (3)
#define HAVE (1)
//----�̂�����----
#define PRICE_SAW_LEVEL1 (1500)		// �̂����背�x��1���i
#define PRICE_SAW_LEVEL2 (3000)		// �̂����背�x��2���i
#define PRICE_SAW_LEVEL3 (7000)	// �̂����背�x��3���i
//----�n���}�[----
#define PRICE_HAMMER_LEVEL1 (1500)		// �n���}�[���i
#define PRICE_HAMMER_LEVEL2 (3000)		// �n���}�[���i
#define PRICE_HAMMER_LEVEL3 (7000)		// �n���}�[���i
//----�h����----
#define PRICE_DRILL_LEVEL1 (1500)		// �h�������i
#define PRICE_DRILL_LEVEL2 (3000)		// �h�������i
#define PRICE_DRILL_LEVEL3 (7000)		// �h�������i
//----�u�[�c----
#define PRICE_BOOTS (1500)		// �u�[�c���i
//----�m�Y��----
#define PRICE_NOZZLE_LEVEL2 (8000)		// �m�Y��Lv.2���i
#define PRICE_NOZZLE_LEVEL3 (12000)		// �m�Y��Lv.3���i
//----�ϔM----
#define PRICE_HEAT_RESISTANT (3000)	// �ϔM�J�X�^��

//----�������A�C�e��----
#define PRICE_DRINK (30000)			// �X�s�[�h�A�b�v�h�����N���i
#define PRICE_NOZZLE (30000)		// �m�Y���������i
#define PRICE_TIMER (50000)		// ���ԉ������i
#define PRICE_COUPON (50000)		// �V���b�v���������i

// �񋓌^
enum Custom
{
	//----�̂�����----
	SAW,		// �̂�����
	//----�n���}�[----
	HAMMER,	// �n���}�[
	//----�h����----
	DRILL,	// �h����
	//----�u�[�c----
	BOOTS,			// �u�[�c
	//----�m�Y��----
	GAME_NOZZLE,	// �m�Y��
	//----�ϔM�J�X�^��----
	HEAT_RESISTANT,	// �ϔM�J�X�^��	
};

enum Item
{
	ITEM_NONE,
	DRINK,			// �X�s�[�h�A�b�v�h�����N
	NOZZLE,			// �m�Y������
	TIMER,			// ���ԉ���
	COUPON,			// �V���b�v������
};

class CShop
{
public:
	CShop();	// �R���X�g���N�^
	~CShop();	// �f�X�g���N�^
	void Buy(int* Custom, int* Money, int Cursor, int* Buy, int* Nozzle);	// �J�X�^�}�C�Y�p�[�c�w��
	void ItemBuy(int* Item, int* Money, int Cursor, int* Buy);	// �A�C�e���w��
	void SetSuction(Suction* pSuction);							// �z�����݃N���X�Q�b�g
	void SetItem(float coupon);									// �A�C�e�����g�p���Ă��邩
	void SetUI(CUI* ui);										// �������f�[�^�擾
	void StockReduse();								// �݌ɐ�����
	bool* GetDrill();
	bool* GetSaw();
	bool* GetHammer();
private:
	int m_saw, m_hammer, m_drill, m_Boots, m_hose, m_Nozzle,	// �p�[�c�݌ɐ�
		m_nHeat;
	int m_drink, m_nozzle, m_timer, m_coupon;					// �A�C�e���݌ɐ�
	CUI* m_pUI_Money;											// ����UI
	Suction* m_pSuction;										// �z�����݋@�\�N���X�|�C���^

	//----�A�C�e�����g�p���ꂽ��----
	float m_fCoupon;// �N�[�|���g�p�t���O
	bool m_bDrill;
	bool m_bSaw;
	bool m_bHammer;
};

#endif	// _SHOP_H__