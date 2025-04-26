#ifndef COLLISION_AREA_MNG
#define COLLISION_AREA_MNG

// ========== �C���N���[�h�� ==========
#include "Player.h"
#include "CollisionArea.h"
#include "AreaGround.h"
#include "AreaSea.h"
#include "AreaHill.h"
#include "AreaSlope.h"
#include "ObjectManager.h"

// --- ���X�g�p ---
#include <list>
using namespace std;

class CCollisionAreaMng
{
public:
	CCollisionAreaMng();
	~CCollisionAreaMng();
	void Update();
	void Draw(DirectX::XMFLOAT4X4* mat);

	void SetPlayer(CPlayer* pPlayer);		// �v���C���[���̎擾
	void SetObjList(list<Object*>* pObj);	// �I�u�W�F�N�g���X�g���̎擾
	list<CCollisionArea*>* GetAreaList();   // AreaList�̃|�C���^�n��

	bool isRandSlope();						// ��ɏ���Ă��邩
	bool isHtCheck();						// ���䔻��ς݂�
	void SethtCheck(bool is);				// ���䔻��ς݃Z�b�g

	void SetRandSlepe(bool rand);			// ��ɏ���Ă邩�t���O���Z�b�g
	static float CheckHeight(int stage, int height);	// ������ݒ�

private:
	list<CCollisionArea*> m_areaList;       // ��Ԕ��胊�X�g
	CPlayer* m_pPlayer;						// �v���C���[�̃|�C���^
	list<Object*>* m_pObjList;				// �I�u�W�F�N�g���X�g�̃|�C���^
	bool m_randSlope;						// ��ɏ���Ă���
	bool m_ht;								// ���䔻��ς݂�
};
#endif