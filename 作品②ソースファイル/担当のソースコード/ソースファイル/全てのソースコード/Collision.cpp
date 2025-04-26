//=================================================================
//
//	Collision.cpp
//	�����蔻��֘A
//
//=================================================================

// ========== �C���N���[�h�� ==========
#include "Collision.h"
#include <cmath>
using namespace std;	// List�p

//=====�}�N����`=====
#define REVISION_POS (1.05f)		// �ђʖh�~�̍��W�␳
#define CLIMB_STAIRS (0.0f)			// ����i���̍���
#define REVISION_HIDE_X (2.5f)		// �I�u�W�F�N�g���ߔ͈�X
#define REVISION_HIDE_Y (1.5f)		// �I�u�W�F�N�g���ߔ͈�Y
#define REVISION_HIDE_Z (2.5f)		// �I�u�W�F�N�g���ߔ͈�Z
#define TUTORIAL_RADIUS	(3.0f)		// �`���[�g���A���Ŕ��苗��

// ========== �R���X�g���N�^ ==========
CCollision::CCollision()
	: m_pPlayer(nullptr)
	, m_pObjMng(nullptr)
	, m_pShop(nullptr)
	, m_pTrade{ nullptr, nullptr, nullptr }
	, m_pTradeIcon(nullptr)
	, m_pTutorial(nullptr)
{
}

// ========== �X�V���� ==========
// �v���C���[�ƃI�u�W�F�N�g�̓����蔻����Ƃ�
// =============================
void CCollision::Update()
{
	bool tutorial = false;
	bool isBiscuit = false;	// �r�X�P�b�g�ɓ���������

	m_pPlayer->SetTutorial(false, 1);

	// =-=-= ������ =-=-=
	// ----- �I�u�W�F�N�g�̃|�C���^���X�g���擾 -----
	list<Object*>*  ObjectList = m_pObjMng->GetObjectList();

	// =-=-= �����蔻�� =-=-=
	for (Object* pObj : *ObjectList)	// �S�ẴI�u�W�F�N�g�Ɠ����蔻������
	{
		switch (pObj->GetKind())		// �I�u�W�F�N�g�̎�ނɉ������`�œ����蔻������
		{
			// ----- ��`�@�΁@��` -----
		case Object::NONE:	break;
		case Object::TREE:				// ��
		case Object::ROCK:				// ��
		//case Object::HOUSE:			// ��
		case Object::BURNINGOBJECT:		// �R���Ă�I�u�W�F�N�g
		case Object::FENCE:				// �t�F���X
		case Object::SIGNBOARD:			// �Ŕ�
		case Object::MUSHROOM:			// �L�m�R
		case Object::RUBBISH:			// �S�~
		case Object::STONE:				// ��
		case Object::WOOD:				// ��
		//case Object::BLUE_MUSHROOM:	// ���̂�
		case Object::DONUTS:			// �h�[�i�c
		case Object::CAKEPIECE:			// �P�[�L
		case Object::STRAWBERRY:		// �C�`�S
		case Object::APOLO:				// �A�|��
		case Object::COOKIE:			// �N�b�L�[
		case Object::CHOCOLATETREE:		// �`���R��
		case Object::CANDYROCK:			// ����
		case Object::CHOCOLATEFENCE:	// �`���R�t�F���X
		case Object::CHOCOLATEPIECE:	// �`���R���Ёi�؍ށj
		case Object::CANDYPIECE:		// �����Ёi�΂���j
		case Object::CANDLE:			// �낤����
		case Object::SWEETSHOUSE:		// ���َq�̉�
		case Object::BISCUIT:			// �r�X�P�b�g�M�~�b�N
		case Object::BISCUITPIECE:		// �r�X�P�b�g�M�~�b�N�J�X
		case Object::Kind::TUTORIALSIGNBOARD:	// �`���[�g���A���Ŕ�

			//if (pObj->GetKind() == Object::Kind::COOKIE)
			//{
			//	if (CheckCollisionRectToRect(m_pPlayer->GetPos(),
			//		pObj->GetPos(), m_pPlayer->GetScale(), pObj->GetScale()))
			//	{
			//		//---�������Ă�����I�u�W�F�N�g�̊O�Ɉړ�
			//		SetPlayerPos(m_pPlayer->GetPos(), pObj->GetPos(), m_pPlayer->GetScale(), pObj->GetScale());
			//		//---�I�u�W�F�N�g�̑��x��␳
			//		pObj->SetVelocity(0.0f);
			//		//---�I�u�W�F�N�g���g�ɐڐG��m�点��
			//		pObj->SetTouch(true);

			//		// ---�r�X�P�b�g�̏ꍇ�͏�ɏ��
			//		if (pObj->GetKind() == Object::Kind::BISCUIT) {
			//			m_pPlayer->SetRandHeight(pObj->GetRandHeight());
			//			isBiscuit = true;
			//		}
			//	}
			//}
			//---�����蔻������
			if (CheckCollisionRectToRect(m_pPlayer->GetPos(),
				pObj->GetPos(), m_pPlayer->GetScale(), pObj->GetScale()))
			{
				// ---�r�X�P�b�g�̏ꍇ�͏�ɏ��
				if (pObj->GetKind() == Object::Kind::BISCUIT) {
					if (m_pPlayer->GetPos().y >= pObj->GetPos().y) {	// �r�X�P�b�g�̉��ł͔��肵�Ȃ�
						pObj->SetTouch(true);
						m_pPlayer->SetRandHeight(pObj->GetRandHeight());
						isBiscuit = true;
					}
					break;
				}

				//---�������Ă�����I�u�W�F�N�g�̊O�Ɉړ�
				SetPlayerPos(m_pPlayer->GetPos(), pObj->GetPos(), m_pPlayer->GetScale(), pObj->GetScale());
				//---�I�u�W�F�N�g�̑��x��␳
				pObj->SetVelocity(0.0f);
				//---�I�u�W�F�N�g���g�ɐڐG��m�点��
				pObj->SetTouch(true);
			}
			else
			{
				//---�I�u�W�F�N�g���g�ɐڐG���Ă��Ȃ������n��
				pObj->SetTouch(false);
			}
			//---�v���C���[�ƃJ�����̒�����̓����蔻��
			if (IsObjectOnCameraLine(m_pPlayer->GetPos(),
				m_pPlayer->GetCameraPos(), pObj->GetPos(), pObj->GetScale()))
			{
				//---�������Ă�����`���~
				pObj->SetDraw(false);
			}
			//---�`��
			else pObj->SetDraw(true);

			if (pObj->GetKind() == Object::TUTORIALSIGNBOARD) {
				//---�`���[�g���A��
				if (CheckCollisionCircleToCircleWithAngle(m_pPlayer->GetPos(),
					pObj->GetPos(), m_pPlayer->GetScale().x / 2.5, TUTORIAL_RADIUS, pObj->GetAngle()))
				{
					m_pPlayer->SetTutorial(true, pObj->GetTutorialKind());
					tutorial = true;
					m_pTutorial->SetPos(pObj->GetPos());
					break;
				}
				else if (!tutorial) {
					m_pPlayer->SetTutorial(false, pObj->GetTutorialKind());
				}
			}

			break;

			//---�L�m�R�@�M�~�b�N�̔���
		case Object::BLUE_MUSHROOM:
			//---�����蔻������
			if (CheckCollisionRectToRect(m_pPlayer->GetPos(),
				pObj->GetPos(), m_pPlayer->GetScale(), pObj->GetScale()))
			{
				//---�������Ă�����I�u�W�F�N�g�̊O�Ɉړ�
				SetPlayerPos(m_pPlayer->GetPos(), pObj->GetPos(), m_pPlayer->GetScale(), pObj->GetScale());
				//---�I�u�W�F�N�g�̑��x��␳
				pObj->SetVelocity(0.0f);
				//---�I�u�W�F�N�g���g�ɐڐG��m�点��
				pObj->SetTouch(true);
			}
			else
			{
				//---�I�u�W�F�N�g���g�ɐڐG���Ă��Ȃ������n��
				pObj->SetTouch(false);
			}

			//---�M�~�b�N�Ɖ󂹂�I�u�W�F�N�g�̓����蔻��
			for (Object* pDelObj : *ObjectList)
			{
				// �M�~�b�N�ȊO�A�L�m�R�ȊO�A���x��2�ȏ�
				if (!pDelObj->GetGimmick() && pDelObj->GetKind() != Object::MUSHROOM && pDelObj->GetLevel() > 1)
				{
					if (CheckCollisionRectToRect(pDelObj->GetPos(),
						pObj->GetPos(), pDelObj->GetScale(), pObj->GetScale()))
					{
						pDelObj->SetGetMoney(false);	// �����͓��肵�Ȃ�
						pDelObj->SetDelete();			// �j��
					}
				}
			}

			//---�v���C���[�ƃJ�����̒�����̓����蔻��
			if (IsObjectOnCameraLine(m_pPlayer->GetPos(),
				m_pPlayer->GetCameraPos(), pObj->GetPos(), pObj->GetScale()))
			{
				//---�������Ă�����`���~
				pObj->SetDraw(false);
			}
			//---�`��
			else pObj->SetDraw(true);
			break;

			break;

			// ----- �~�@�΁@��` -----
		case Object::HOUSE:	// ��
			// *** ������ ***
			break;
		default:
			break;
		}
	}
	m_pPlayer->SetRandBiscuit(isBiscuit);	// �r�X�P�b�g�ɏ�������ǂ���

	// ----- �v���C���[�@�΁@���l -----
	for (auto pTrade : m_pTrade) {
		if (pTrade) {
			if (CheckCollisionCircleToCircleWithAngle(m_pPlayer->GetPos(),
				pTrade->GetPos(), m_pPlayer->GetScale().x / 2.5, pTrade->GetRadius(), pTrade->GetAngle()))
			{
				m_pPlayer->SetTrade(true);
				//pTrade->SetPos(pTrade->GetPos());
				m_pTradeIcon->SetPos(pTrade->GetPos());
				break;
			}
			else { m_pPlayer->SetTrade(false); }
		}
	}	
}

// ========== ��` �� ��`�̓����蔻�� ==========
// ���@���F
// XMFLOAT3 Pos1	�ΏۂP�̒��S���W
// XMFLOAT3 Pos2	�ΏۂQ�̒��S���W
// XMFLOAT3 Scale1	�ΏۂP�̃T�C�Y
// XMFLOAT3 Scale2	�ΏۂQ�̃T�C�Y
// �߂�l�Fbool �������Ă�����true
// �w�肳�ꂽ��`�Ƌ�`�̓����蔻����Ƃ�
// ========================================
bool CCollision::CheckCollisionRectToRect(DirectX::XMFLOAT3 Pos1, DirectX::XMFLOAT3 Pos2,
	DirectX::XMFLOAT3 Scale1, DirectX::XMFLOAT3 Scale2)
{
	//---�X�P�[���̔��a����
	DirectX::XMFLOAT3 SizeHalf1;
	SizeHalf1.x = Scale1.x / 2.0f;
	SizeHalf1.y = Scale1.y / 2.0f;
	SizeHalf1.z = Scale1.z / 2.0f;
	DirectX::XMFLOAT3 SizeHalf2;
	SizeHalf2.x = Scale2.x / 2.0f;
	SizeHalf2.y = Scale2.y / 2.0f;
	SizeHalf2.z = Scale2.z / 2.0f;

	//---�����蔻��
	if ((Pos2.x - SizeHalf2.x <= Pos1.x + SizeHalf1.x) &&		// 2�̍��[ < 1�̉E�[
		(Pos1.x - SizeHalf1.x <= Pos2.x + SizeHalf2.x))			// 1�̍��[ < 2�̉E�[
	{
		if ((Pos2.z - SizeHalf2.z <= Pos1.z + SizeHalf1.z) &&	// 2�̏�[ < 1�̉��[
			(Pos1.z - SizeHalf1.z <= Pos2.z + SizeHalf2.z))		// 1�̏�[ < 2�̉��[
		{

			//if ((Pos2.y - SizeHalf2.y < Pos1.y + SizeHalf1.y) &&
			//	(Pos1.y < Pos2.y + SizeHalf2.y))
			//{
			return true;
			//}
		}
	}
	return false;
}

// ========== ��` �� �_�̓����蔻�� ==========
// ���@���F
// XMFLOAT3 Pos1	�ΏۂP�̒��S���W
// XMFLOAT3 Pos2	�ΏۂQ�̒��S���W
// XMFLOAT3 Scale1	�ΏۂP�̃T�C�Y
// �߂�l�Fbool �������Ă�����true
// �w�肳�ꂽ��`�Ɠ_�̓����蔻����Ƃ�
// ========================================
bool CCollision::CheckCollisionRectToPoint(DirectX::XMFLOAT3 Pos1, DirectX::XMFLOAT3 Pos2, DirectX::XMFLOAT3 Scale1)
{
	//---�X�P�[���̔��a����
	DirectX::XMFLOAT3 SizeHalf1;
	SizeHalf1.x = Scale1.x / 2.0f;
	SizeHalf1.y = Scale1.y / 2.0f;
	SizeHalf1.z = Scale1.z / 2.0f;

	//---�����蔻��
	if ((Pos2.x <= Pos1.x + SizeHalf1.x) &&			// 2 < 1�̉E�[
		(Pos1.x - SizeHalf1.x <= Pos2.x))			// 1�̍��[ < 2
	{
		if ((Pos2.z <= Pos1.z + SizeHalf1.z) &&		// 2 < 1�̉��[
			(Pos1.z - SizeHalf1.z <= Pos2.z))		// 1�̏�[ < 2
		{
			//if ((Pos2.y <= Pos1.y + SizeHalf1.y) &&
			//	(Pos1.y <= Pos2.y))
			//{
			return true;
			//}
		}
	}
	return false;
}


// ========== �~ �� �~�̓����蔻�� ==========
// ���@���F
//	XMFLOAT3 �ΏۂP�̒��S���W
//	XMFLOAT3 �ΏۂQ�̒��S���W
//	float	�ΏۂP�̔��a
//	float	�ΏۂQ�̔��a
// �߂�l�Fbool �������Ă�����true
// �w�肳�ꂽ�~�Ɖ~�̓����蔻����Ƃ�
// ========================================
bool CCollision::CheckCollisionCircleToCircle(DirectX::XMFLOAT3 centerPos1, DirectX::XMFLOAT3 centerPos2, float radius1, float radius2)
{
	if ((centerPos1.x - centerPos2.x) * (centerPos1.x - centerPos2.x) + (centerPos1.z - centerPos2.z) * (centerPos1.z - centerPos2.z) <=		// (�~1�̒��S���WX - �~2�̒��S���WX)��2�� + (�~1�̒��S���WY - �~2�̒��S���WY)��2��
		(radius1 + radius2) * (radius1 + radius2))	// (�~1�̔��a+�~2�̔��a)��2��
	{
		return true;
	}
	return false;
}

bool CCollision::CheckCollisionCircleToCircleWithAngle(DirectX::XMFLOAT3 centerPos1, DirectX::XMFLOAT3 centerPos2, float radius1, float radius2, DirectX::XMFLOAT3 angle2)
{
	// �~�Ή~�̓����蔻��
	if ((centerPos1.x - centerPos2.x) * (centerPos1.x - centerPos2.x) + (centerPos1.z - centerPos2.z) * (centerPos1.z - centerPos2.z) > (radius1 + radius2) * (radius1 + radius2)) {
		return false; // �~���d�Ȃ��Ă��Ȃ�
	}

	// 2�ڂ̃I�u�W�F�N�g�̑O���x�N�g�����v�Z
	DirectX::XMVECTOR forwardVec2 = DirectX::XMVectorSet(
		sin(DirectX::XMConvertToRadians(angle2.y)), // Y����]���l���A���̒l�Ōv�Z
		0.0f,
		cos(DirectX::XMConvertToRadians(angle2.y)),
		0.0f
	);

	// 1�ڂ̃I�u�W�F�N�g��2�ڂ̃I�u�W�F�N�g�̈ʒu�֌W�x�N�g��
	DirectX::XMVECTOR toPos1Vec = DirectX::XMVectorSet(
		centerPos1.x - centerPos2.x,
		0.0f,
		centerPos1.z - centerPos2.z,
		0.0f
	);
	toPos1Vec = DirectX::XMVector3Normalize(toPos1Vec); // �x�N�g���𐳋K��

	// 2�ڂ̃I�u�W�F�N�g���猩��1�ڂ̃I�u�W�F�N�g�̕����ƁA2�ڂ̃I�u�W�F�N�g�̑O���x�N�g���Ƃ̊p�x���v�Z
	float dotProduct = DirectX::XMVectorGetX(DirectX::XMVector3Dot(forwardVec2, toPos1Vec));
	float angleBetween = DirectX::XMConvertToDegrees(acos(dotProduct));

	// �p�x��90�x�ȓ�������
	if (angleBetween >= 90.0f) {
		return true; // �O��180�x�ȓ�
	}

	return false; // �O��180�x�O
}

// ========== IsObjectOnCameraLine ==========
// ���@���F
// XMFLOAT3 playerPos	�v���C���[�̒��S���W
// XMFLOAT3 cameraPos	�J�����̒��S���W
// XMFLOAT3	objectpos	�I�u�W�F�N�g�̒��S���W
// XMFLOAT3	objectSize	�I�u�W�F�N�g�̑傫��
// �߂�l�Fbool �������Ă�����true
// �v���C���[�ƃJ�����̒�����ɃI�u�W�F�N�g�����邩�̔���
// =========================================
bool CCollision::IsObjectOnCameraLine(DirectX::XMFLOAT3 playerPos, DirectX::XMFLOAT3 cameraPos, DirectX::XMFLOAT3 objectPos, DirectX::XMFLOAT3 objectSize)
{
	//---�������`
	DirectX::XMFLOAT3 focus = playerPos;
	DirectX::XMFLOAT3 objSize = objectSize;
	focus.y += 2.0f;	//�œ_�̕␳
	objSize.x = objSize.x / 2.5f;	//��������T�C�Y�␳
	objSize.y = objSize.y / 1.5f;	//Y
	objSize.z = objSize.z / 2.5f;	//Z
	DirectX::XMVECTOR lineStartVec = DirectX::XMLoadFloat3(&cameraPos);
	DirectX::XMVECTOR lineEndVec = DirectX::XMLoadFloat3(&focus);
	DirectX::XMVECTOR lineDirVec = DirectX::XMVectorSubtract(lineEndVec, lineStartVec);

	DirectX::XMVECTOR boxCenterVec = DirectX::XMLoadFloat3(&objectPos);
	DirectX::XMVECTOR boxSizeVec = DirectX::XMLoadFloat3(&objSize);
	DirectX::XMVECTOR boxMinVec = DirectX::XMVectorSubtract(boxCenterVec, boxSizeVec);
	DirectX::XMVECTOR boxMaxVec = DirectX::XMVectorAdd(boxCenterVec, boxSizeVec);

	// tMin��tMax���v�Z
	float tMin = 0.0f, tMax = 1.0f;
	for (int i = 0; i < 3; ++i) {
		float invD = 1.0f / DirectX::XMVectorGetByIndex(lineDirVec, i);
		float t0 = (DirectX::XMVectorGetByIndex(boxMinVec, i) - DirectX::XMVectorGetByIndex(lineStartVec, i)) * invD;
		float t1 = (DirectX::XMVectorGetByIndex(boxMaxVec, i) - DirectX::XMVectorGetByIndex(lineStartVec, i)) * invD;
		if (invD < 0.0f) std::swap(t0, t1);
		tMin = t0 > tMin ? t0 : tMin;
		tMax = t1 < tMax ? t1 : tMax;
		if (tMax <= tMin) return false;
	}
	return true;
}

// ========== SetPlayer ==========
// ���@���FCPlayer*	�v���C���[�̎��̂̃|�C���^
// �߂�l�F�Ȃ�
// Player����ݒ肷��
// ==============================
void CCollision::SetPlayer(CPlayer* player)
{
	m_pPlayer = player;
}

// ========== SetObjectManager ==========
// ���@���FCObjectMng*	�I�u�W�F�N�gMng�̎��̂̃|�C���^
// �߂�l�F�Ȃ�
// ObjectMng����ݒ肷��
// ======================================
void CCollision::SetObjectManager(CObjectMng* objMng)
{
	m_pObjMng = objMng;
}

void CCollision::SetTrade(vector<CTrade*> trade)
{
	m_pTrade = trade;
}

// ========== SetPlayerPos ==========
// ���@���F
// XMFLOAT3 Pos1	�ΏۂP�̒��S���W
// XMFLOAT3 Pos2	�ΏۂQ�̒��S���W
// XMFLOAT3	Scale1	�ΏۂP�̑傫��
// XMFLOAT3	Scale2	�ΏۂQ�̑傫��
// �߂�l�F�Ȃ�
// �v���C���[�̍��W��XYZ�e�v�f���ݒ�
// ==================================
void CCollision::SetPlayerPos(DirectX::XMFLOAT3 Pos1, DirectX::XMFLOAT3 Pos2,
	DirectX::XMFLOAT3 Scale1, DirectX::XMFLOAT3 Scale2)
{
	//---�X�P�[���̔��a����
	DirectX::XMFLOAT3 SizeHalf1;
	SizeHalf1.x = Scale1.x / 2.0f;
	SizeHalf1.y = Scale1.y / 2.0f;
	SizeHalf1.z = Scale1.z / 2.0f;
	DirectX::XMFLOAT3 SizeHalf2;
	SizeHalf2.x = Scale2.x / 2.0f;
	SizeHalf2.y = Scale2.y / 2.0f;
	SizeHalf2.z = Scale2.z / 2.0f;

	//---Y���A�����̊ђʖh�~
	if (Pos1.y < Pos2.y + SizeHalf2.y && m_pPlayer->GetOldPos().y > Pos2.y + SizeHalf2.y)
	{
		m_pPlayer->SetPosY(Pos2.y + SizeHalf2.y + SizeHalf1.y * REVISION_POS);
	}

	//---���Ȃ����XZ���̊ђʖh�~
	if (Pos1.x - SizeHalf1.x < Pos2.x + SizeHalf2.x && m_pPlayer->GetOldPos().x - SizeHalf1.x > Pos2.x + SizeHalf2.x)
	{
		m_pPlayer->SetPosX(Pos2.x + SizeHalf2.x + SizeHalf1.x * REVISION_POS);
	}
	if (Pos1.x + SizeHalf1.x > Pos2.x - SizeHalf2.x && m_pPlayer->GetOldPos().x + SizeHalf1.x < Pos2.x - SizeHalf2.x)
	{
		m_pPlayer->SetPosX(Pos2.x - SizeHalf2.x - SizeHalf1.x * REVISION_POS);
	}
	if (Pos1.z - SizeHalf1.z < Pos2.z + SizeHalf2.z && m_pPlayer->GetOldPos().z - SizeHalf1.z > Pos2.z + SizeHalf2.z)
	{
		m_pPlayer->SetPosZ(Pos2.z + SizeHalf2.z + SizeHalf1.z * REVISION_POS);
	}
	if (Pos1.z + SizeHalf1.z > Pos2.z - SizeHalf2.z && m_pPlayer->GetOldPos().z + SizeHalf1.z < Pos2.z - SizeHalf2.z)
	{
		m_pPlayer->SetPosZ(Pos2.z - SizeHalf2.z - SizeHalf1.z * REVISION_POS);
	}
	

	//---�I�u�W�F�N�g����
	list<Object*>*  ObjectList = m_pObjMng->GetObjectList();

	for (Object* pObj : *ObjectList)
	{
		if (Pos2.x > Pos1.x + SizeHalf1.x)
		{
			pObj->SetPosX(pObj->GetOldPos().x);
		}
		else if (Pos2.x < Pos1.x - SizeHalf1.x)
		{
			pObj->SetPosX(pObj->GetOldPos().x);
		}
		if (Pos2.z > Pos1.z + SizeHalf1.z)
		{
			pObj->SetPosZ(pObj->GetOldPos().z);
		}
		else if (Pos2.z < Pos1.z - SizeHalf1.z)
		{
			pObj->SetPosZ(pObj->GetOldPos().z);
		}
	}
}

void CCollision::SetTradeIcon(TradeIcon * tIcon)
{
	m_pTradeIcon = tIcon;
}

void CCollision::SetTutorialIcon(Tutorial * TutorialIcon)
{
	m_pTutorial = TutorialIcon;
}
