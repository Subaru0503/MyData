// Suction.cpp

//====�C���N���[�h=====
#include "Suction.h"
#include <math.h>
#include "Shop.h"
#include "Input.h"
#include "Player.h"

//=====�萔�E�}�N����`=====
static const float INITIAL_SUCTION_RANGE = 4.0f;		// ��{�z�����ݗL������
static const float INITIAL_SUCTION_ANGLE = 50.0f;		// ��{�z�����ݗL���z�����݊p�x�i���ʂ��獶�E�ɉ��x�����j
static const float INITIAL_SUCTION_SECONDS = 1.0f;		// �z�����ނ܂łɍŒ����b��
static const float DELETE_ANGLE = 90.0f;				// ���S�z�����ݔ͈͂̊p�x�i���ʂ��獶�E�ɉ��x�����j
static const float SUCTION_INTO_MATER = 2.0f;			// ���S�ɋz�����܂�郂�[�h�ɓ���I�u�W�F�N�g�Ƃ̋���
static const float LEVEL_SPEED = 0.5f;					// �P���x�������Ƃ̋z�����݃X�s�[�h�{��
#define PLAY_GIMMICK (3.0f)								// �L�m�R�����������͈͐���
#define RELEASE_GIMMICK (9.0f)							// �L�m�R���L�т�͈͐���
#define WEIGHT_MINUS (0.007f)							// �͈͐������a���Z�p
#define VEC_OFFSETX (5.0f)								// �x�N�g������邽�߂̈ړ���
#define PLAY_GIMMICK_DELTA_POS (0.8f)					// �v���C�M�~�b�N�Ŏg�����W�̕ω���
#define INIT_DELTA_POS (0.95f)							// ���W�����p�̕ω��ʂ̏����l
#define DELTA_POS (0.9f)								// ���W�����p�̕ω��ʂ�ς���

// �R���X�g���N�^
Suction::Suction()
	: m_suctionRange(INITIAL_SUCTION_RANGE)
	, m_suctionAngle(INITIAL_SUCTION_ANGLE)
	, m_suctionSeconds(INITIAL_SUCTION_SECONDS)
	, m_pObjectList(nullptr)
	, m_playerForward{ 0.0f,0.0f,0.0f,0.0f }
	, m_playerPos{ 0.0f,0.0f,0.0f }
	, m_nozzleLevel(1)
	, m_fPower(1.0f)
	, m_pPlayer(nullptr)
	, m_start(false)
	, m_fAngle(90.0f)
	, m_pDrill(nullptr)
	, m_pSaw(nullptr)
	, m_pHammer(nullptr)
{
}

Suction::~Suction()
{
}

/**************************************************************************
*@brief �I�u�W�F�N�g���z�����ݔ͈͓��ɂ��邩���肵�I�u�W�F�N�g�Ɍ��ʂ��i�[
***************************************************************************
*@param [in] pObject		�I�u�W�F�N�g���X�g�̎Q��
*@param [in] playerPos		�v���C���[�̍��W
*@param [in] playerForward	�v���C���[�������Ă�������̃x�N�g��
*@param [in] Custom			�J�X�^���̏����󋵏��
****************************************************************************/
void Suction::IsObjectInSuctionRange(std::list<Object*>* pObjectList, DirectX::XMFLOAT3 playerPos,
	DirectX::XMFLOAT3 playerForward, int* Custom)
{
	m_start = true;	// player.cpp�Ŋ֐����Ăяo����悤��
	if (IsKeyPress('0'))
	{
		m_nozzleLevel = 3;
		m_suctionRange = 20.0f;
		m_suctionAngle = 90.0f;
	}

	// �m�Y�����x���ɉ����ėL�������𒲐�
	m_suctionRange = INITIAL_SUCTION_RANGE * m_fPower *(1.0f + (m_nozzleLevel - 1) * 0.5f);

	// �v���C���[�̌������󂯎���Čv�Z�p�ɕϊ�
	DirectX::XMFLOAT3 playerForwardXZ = playerForward;
	m_playerForward = DirectX::XMLoadFloat3(&playerForwardXZ);

	// �J�����̌������g�����v���C���[�����x�N�g���̂��߁AY�����𖳂�����X���ƕ��s�ȃx�N�g���ɒ���
	m_playerForward = DirectX::XMVectorMultiply(m_playerForward, DirectX::XMVectorSet(1.0f, 0.0f, 1.0f, 0.0f));
	// �v���C���[�̕����x�N�g���𐳋K��
	m_playerForward = DirectX::XMVector3Normalize(m_playerForward);
	// �����o�Ƀv���C���[���W���Z�b�g
	m_playerPos = playerPos;
	// �����o�ɃI�u�W�F�N�g���X�g���Z�b�g
	m_pObjectList = pObjectList;


	// �I�u�W�F�N�g���X�g�̑S�v�f
	for (Object* pObj : *m_pObjectList)
	{
		if (pObj->IsDrop()) { continue; }
		if (!CheckHeightLink(pObj) && !pObj->GetRandSlope()) { continue; }	// 

		//--�v���C���[�A�I�u�W�F�N�g�Ԃ̋����ɂ�锻��
		// �v���C���[���W�ƃI�u�W�F�N�g���W�����_�Ԃ̋������v�Z
		float distance = 0.0f;
		DirectX::XMFLOAT3 objSize = pObj->GetScale();	// �I�u�W�F�N�g�̃T�C�Y
		if (pObj->GetKind() == Object::TREE && pObj->GetLevel() == 3)
		{
			distance = sqrt((pObj->GetPos().x - m_playerPos.x)*(pObj->GetPos().x - m_playerPos.x) +
				(pObj->GetPos().y - objSize.y / 2.0f - m_playerPos.y)*(pObj->GetPos().y - objSize.y / 2.0f - m_playerPos.y) +
				(pObj->GetPos().z - m_playerPos.z)*(pObj->GetPos().z - m_playerPos.z)
			);
		}
		else
		{
			distance = sqrt((pObj->GetPos().x - m_playerPos.x)*(pObj->GetPos().x - m_playerPos.x) +
				(pObj->GetPos().y - objSize.y / 2.0f - m_playerPos.y)*(pObj->GetPos().y - objSize.y / 2.0f - m_playerPos.y) +
				(pObj->GetPos().z - m_playerPos.z)*(pObj->GetPos().z - m_playerPos.z)
			);
		}
		// �z�����݋����O�Ȃ�false�ŏI��
		if (m_suctionRange < distance)
		{
			pObj->SetSuctionFlg(false); continue; 
		}

		// �������l�������ɑ����悤�ɒ���
		DirectX::XMFLOAT3 objPos = pObj->GetPos();		// �I�u�W�F�N�g�̍��W
		objPos.y = objPos.y - objSize.y / 2.0f;			// ���S���W���v���C���[�Ɠ����ʒu��

		//--�v���C���[�������Ă����������Ƃ����p�x�ɂ�锻��
		// �v���C���[����I�u�W�F�N�g�ւ̃x�N�g�����擾
		DirectX::XMVECTOR difference = DirectX::XMVectorSubtract(	// ���Z��(����1 - ����2)
			DirectX::XMLoadFloat3(&objPos),		// �I�u�W�F�N�g�̍��W�̃|�C���^
			DirectX::XMLoadFloat3(&m_playerPos)			// �v���C���[�̍��W���i�[����Ă���ϐ��A�h���X
		);
		// �I�u�W�F�N�g�ւ̃x�N�g���𐳋K��
		difference = DirectX::XMVector3Normalize(difference);

		// �I�u�W�F�N�g�ւ̕����x�N�g���ƃv���C���[�̌����̃x�N�g���̊Ԃ̃��W�A���p���擾
		float angle;
		DirectX::XMStoreFloat(&angle, DirectX::XMVector3AngleBetweenNormals(
			difference,			// �v���C���[����I�u�W�F�N�g�ւ̕����x�N�g��
			m_playerForward		// �v���C���[�̕����x�N�g�� 
		));

		// ���W�A������Degrees�Ɋp�x��ϊ�
		float angleToObject = DirectX::XMConvertToDegrees(angle);

		pObj->SetAngleToPlayer(angleToObject);

		int nJudge = 0;

		// �I�u�W�F�N�g�ւ̊p�x���L���͈͓������肵�I�u�W�F�N�g�̃t���O��؂�ւ���
		if (angleToObject <= m_suctionAngle)
		{
			int objLevel = pObj->GetLevel();	// �I�u�W�F�N�g�̃��x�����擾

			//	�m�Y�����x�����I�u�W�F�N�g�̃��x���ȏ�ł����
			if (m_nozzleLevel >= objLevel)
			{
				pObj->SetSuctionFlg(true);	// �z�����݃t���O�𗧂Ă�
				pObj->SetPlayerPosY(playerPos.y);	// �v���C���[���WY�̏���n��
				nJudge = 1;
			}
			// �m�Y�����x���ƃI�u�W�F�N�g�̃��x�������P
			else if ((m_nozzleLevel + 1) == objLevel) {
				pObj->SetShake(true);	// �h��t���O�𗧂Ă�
			}
			// �m�Y�����x��������Ă��Ȃ�������
			if (!nJudge)
			{
				// �M�~�b�N�ł����
				if (pObj->GetGimmick())
				{
					pObj->SetPlayGimmick(true);		// �M�~�b�N���J�n
					pObj->SetSuctionGimmick(true);	// �M�~�b�N���z�����܂�Ă���
					m_pPlayer->SetSuction(true);	// �v���C���[���z�����݂����Ă���
				}
				// ���̃I�u�W�F�N�g��j��ł���J�X�^���p�[�c���������Ă����
				for (int i = 0; i < MAX_CUSTOM; i++)
				{
					// �������ĂȂ������玟��
					if (Custom[i] == 0) continue;
					switch (i)
					{
						// �̂�����
					case Custom::SAW:
						// ���x��������Ă��邩
						if ((Custom[i] + 1 >= objLevel && pObj->GetKind() == Object::TREE) ||
							(Custom[i] + 1 >= objLevel && pObj->GetKind() == Object::SIGNBOARD) ||
							(Custom[i] + 1 >= objLevel && pObj->GetKind() == Object::CHOCOLATETREE))
						{
							if (INITIAL_SUCTION_RANGE > distance && !pObj->IsDrop())	// �j��L��������������
							{
								pObj->SetGetMoney(false);
								pObj->SetDelete();	// �j��t���O�𗧂Ă�
								m_pSaw->SawAnimetion();
							}
						}
						// ���x������1�Ȃ�
						else if ((objLevel - (Custom[i] + 1) == 1 && pObj->GetKind() == Object::TREE) ||
							(objLevel - (Custom[i] + 1) == 1 && pObj->GetKind() == Object::SIGNBOARD) ||
							(objLevel - (Custom[i] + 1) == 1 && pObj->GetKind() == Object::CHOCOLATETREE))
						{
							pObj->SetShake(true);	// �h��t���O�𗧂Ă�
						}
						break;
					case Custom::HAMMER:
						// ���x��������Ă��邩
						if ((Custom[i] + 1 >= objLevel && pObj->GetKind() == Object::HOUSE) ||
							(Custom[i] + 1 >= objLevel && pObj->GetKind() == Object::SWEETSHOUSE) ||
							(Custom[i] + 1 >= objLevel && pObj->GetKind() == Object::FENCE) ||
							(Custom[i] + 1 >= objLevel && pObj->GetKind() == Object::CHOCOLATEFENCE))
						{
							if (INITIAL_SUCTION_RANGE > distance && !pObj->IsDrop())	// �j��L��������������
							{
								pObj->SetGetMoney(false);
								pObj->SetDelete();	// �j��t���O�𗧂Ă�
								m_pHammer->HammerAnimetion();
							}
						}
						// ���x������1�Ȃ�
						else if ((objLevel - (Custom[i] + 1) == 1 && pObj->GetKind() == Object::HOUSE) ||
							(objLevel - (Custom[i] + 1) == 1 && pObj->GetKind() == Object::SWEETSHOUSE) ||
							(objLevel - (Custom[i] + 1) == 1 && pObj->GetKind() == Object::FENCE) ||
							(objLevel - (Custom[i] + 1) == 1 && pObj->GetKind() == Object::CHOCOLATEFENCE))
						{
							pObj->SetShake(true);	// �h��t���O�𗧂Ă�
						}
						break;
					case Custom::DRILL:
						// ���x��������Ă��邩
						if ((Custom[i] + 1 >= objLevel && pObj->GetKind() == Object::ROCK) ||
							(Custom[i] + 1 >= objLevel && pObj->GetKind() == Object::CANDYROCK))
						{
							if (INITIAL_SUCTION_RANGE > distance && !pObj->IsDrop())	// �j��L��������������
							{
								pObj->SetGetMoney(false);
								pObj->SetDelete();	// �j��t���O�𗧂Ă�
								m_pDrill->DrillAnimetion();
							}
						}
						// ���x������1�Ȃ�
						else if ((objLevel - (Custom[i] + 1) == 1 && pObj->GetKind() == Object::ROCK) ||
							(objLevel - (Custom[i] + 1) == 1 && pObj->GetKind() == Object::CANDYROCK))
						{
							pObj->SetShake(true);	// �h��t���O�𗧂Ă�
						}
						break;
					}
					//if ((Custom[i] + 1 >= objLevel && pObj->GetKind() == Object::TREE) ||
					//	(Custom[i] - 2 >= objLevel && pObj->GetKind() == Object::HOUSE) ||
					//	(Custom[i] - 5 >= objLevel && pObj->GetKind() == Object::ROCK) ||
					//	(Custom[i] + 1 >= objLevel && pObj->GetKind() == Object::FENCE) ||
					//	(Custom[i] + 1 >= objLevel && pObj->GetKind() == Object::SIGNBOARD))
					//{
					//	if (INITIAL_SUCTION_RANGE > distance && !pObj->IsDrop())	// �j��L��������������
					//	{
					//		pObj->SetDelete();	// �j��t���O�𗧂Ă�
					//	}
					//}
					//else if ((objLevel - Custom[i] + 1 == 1 && pObj->GetKind() == Object::TREE) ||
					//	(objLevel - Custom[i] - 2 == 1 && pObj->GetKind() == Object::HOUSE) ||
					//	(objLevel - Custom[i] - 5 == 1 && pObj->GetKind() == Object::ROCK) ||
					//	(objLevel - Custom[i] + 1 >= objLevel && pObj->GetKind() == Object::FENCE) ||
					//	(objLevel - Custom[i] + 1 >= objLevel && pObj->GetKind() == Object::SIGNBOARD))
					//{
					//	pObj->SetShake(true);	// �h��t���O�𗧂Ă�
					//}
				}
			}
			//if (pObj->GetKind() == Object::MUSHROOM ||
			//	pObj->GetKind() == Object::RUBBISH ||
			//	pObj->GetKind() == Object::STONE ||
			//	pObj->GetKind() == Object::WOOD) {
			//	pObj->SetSuctionFlg(true);
			//}
			//else
			//{
			//	for (int i = 0; i < MAX_CUSTOM; i++)
			//	{
			//		if ((Custom[i] == SAW && pObj->GetKind() == Object::TREE) || 
			//			(Custom[i] == HAMMER && pObj->GetKind() == Object::HOUSE) ||
			//			(Custom[i] == DRILL && pObj->GetKind() == Object::ROCK) || 
			//			(Custom[i] == HOSE && pObj->GetKind() == Object::BURNINGOBJECT) ||
			//			(Custom[i] == SAW && pObj->GetKind() == Object::FENCE) ||
			//			(Custom[i] == SAW && pObj->GetKind() == Object::SIGNBOARD))
			//		{
			//			pObj->SetDelete();
			//		}
			//	}
			//}
		}
		else {
			pObj->SetSuctionFlg(false);
			pObj->SetGetMoney(false);		// ��������ɓ���Ȃ��悤��
			pObj->SetShake(false);
			pObj->SetSuctionGimmick(false);	// �M�~�b�N���z�����܂�Ă��Ȃ����
			//m_pPlayer->SetSuction(false);	// �v���C���[���z������ł��Ȃ����
		}
	}
}

/***********************************************************
*@brief �����A���ʂɉ����ăI�u�W�F�N�g�ɑ��x���Z�b�g
*@brief ���S�z�����ݔ͈͓��̃I�u�W�F�N�g�̍폜�t���O�𗧂Ă�
***********************************************************/
void Suction::SuctionObject(int *CandleDemelit, int *Custom)
{
	// ���X�g�̑S�v�f
	for (Object* pObj : *m_pObjectList)
	{
		// �z�����ݒ��łȂ��������ňړ����łȂ���Ύ��̃I�u�W�F�N�g��
		if (!pObj->IsSuction() && !pObj->IsMove()) { continue; }

		// �I�u�W�F�N�g�̍��W���擾
		DirectX::XMFLOAT3 objPos = pObj->GetPos();

		// �v���C���[���W�ƃI�u�W�F�N�g���W�����_�Ԃ̋������v�Z
		float distance = sqrt((objPos.x - m_playerPos.x)*(objPos.x - m_playerPos.x) +
			0.0f +
			(objPos.z - m_playerPos.z)*(objPos.z - m_playerPos.z)
		);

		// ���S�z�����݊p�x���Ȃ�
		if (pObj->GetAngleToPlayer() < DELETE_ANGLE)
		{
			// ���������S�z�����݋������Ȃ�
			if (distance <= SUCTION_INTO_MATER) {
				pObj->SetDelete();			// �I�u�W�F�N�g�̍폜�t���O�𗧂Ă�
				pObj->SetGetMoney(true);
				// �낤�������z������őϔM�J�X�^������������Ă��Ȃ�������
				if (pObj->GetKind() == Object::CANDLE && Custom[5] == 0)
				{
					*CandleDemelit = 1;	// �t���O�グ
				}
				continue;
			}
		}

		// �����œ����Ă��邾���̃I�u�W�F�N�g�͂����܂Ł`
		if (!pObj->IsSuction() && pObj->IsMove()) { continue; }
		
		// �I�u�W�F�N�g����v���C���[�ւ̃x�N�g�����擾
		DirectX::XMVECTOR objToPlayer = DirectX::XMVectorSubtract(	// ���Z��(����1 - ����2)
			DirectX::XMLoadFloat3(&m_playerPos),			// �v���C���[�̍��W���i�[����Ă���ϐ��A�h���X
			DirectX::XMLoadFloat3(&objPos)		// �I�u�W�F�N�g�̍��W�̃|�C���^
		);
		// ���̃x�N�g���𐳋K��
		objToPlayer = DirectX::XMVector3Normalize(objToPlayer);

		// �ړ������x�N�g�����I�u�W�F�N�g�ɃZ�b�g
		pObj->SetDirection(objToPlayer);

		//--�����A���ʂɉ����đ��x�����߂鏈��
		// 1�b�Ԃɉ����[�g�������񂹂邩�v�Z
		float speed = m_suctionRange / m_suctionSeconds;
		float rotate = 0.0f;
		// �������߂Â��������Ȃ�悤�Ɍv�Z
		speed = speed * (m_suctionRange / distance);
		rotate = 180.0f * (m_suctionRange / distance);
		// ���ʂ��傫���قǒx���Ȃ�悤�Ɍv�Z
		speed = speed / pObj->GetMass();
		rotate = rotate / pObj->GetMass();
		// �m�Y���ƃI�u�W�F�N�g�̃��x�������擾
		int levelDifference = m_nozzleLevel - pObj->GetLevel();
		// �m�Y���̃��x���ƃI�u�W�F�N�g�̃��x�����l�����ċz�����ݑ��x�𒲐�
		if (levelDifference > 0)
		{
			speed *= 1.0f + (levelDifference * LEVEL_SPEED);
		}
		DirectX::XMFLOAT3 angle(rotate, rotate, rotate);
		// ���x���I�u�W�F�N�g�ɃZ�b�g
		pObj->SetVelocity(speed);
		pObj->SetAngle(angle);
	}
}

void Suction::NozzleLevelUp()				// �m�Y�����x���A�b�v
{
	if (m_nozzleLevel < 3)
	{
		m_nozzleLevel++;
		m_pESuction->SetScale();
	}
}

void Suction::PowerUP()						// �p���[�A�b�v
{
	m_fPower = 1.5f;
}

int Suction::GetNozzleLevel()				// �m�Y�����x���Q�b�g
{
	return m_nozzleLevel;
}

bool Suction::GetStart()
{
	return m_start;
}

// �I�u�W�F�N�g�ƃv���C���[�̍���������������
bool Suction::CheckHeightLink(Object * pObj)
{
	return m_pPlayer->GetRandHeight() == pObj->GetRandHeight();
}

// ���f������]������
void Suction::ModelRotate(Object* pObj, DirectX::XMFLOAT3 playerPos, DirectX::XMFLOAT3 pos)
{
	// �v���C���[�̕���or�P�̕����ɐL�m�R���{���X����
	if (pos.x < playerPos.x && pos.z < playerPos.z)	// �v���C���[or�P�������̕��ɂ�����
	{
		// Y���ŉ�]������p�x�����p
		DirectX::XMFLOAT3 workPos = pos;	// �L�m�R���{
		workPos.z += VEC_OFFSETX;	// �x�N�g������邽�߂ɐL�m�R���{�̍��W���班�����炷

		// X���ŉ�]������p�x�����p
		DirectX::XMFLOAT3 workPos2 = playerPos;
		workPos2.y = pos.y;

		// y���ŉ�]������
		// �p�x����邽�߂Ƀx�N�g�������
		DirectX::XMVECTOR difference = DirectX::XMVectorSubtract(	// ���Z��(����1 - ����2)
			DirectX::XMLoadFloat3(&workPos),		// �L�m�R���{�̍��W���炸�炵�����W
			DirectX::XMLoadFloat3(&pos)				// �L�m�R���{�̍��W
		);
		// �I�u�W�F�N�g�ւ̃x�N�g���𐳋K��
		difference = DirectX::XMVector3Normalize(difference);

		DirectX::XMVECTOR difference2 = DirectX::XMVectorSubtract(	// ���Z��(����1 - ����2)
			DirectX::XMLoadFloat3(&playerPos),		// �v���C���[or�P���W
			DirectX::XMLoadFloat3(&pos)				// �L�m�R���{�̍��W
		);
		// �I�u�W�F�N�g�ւ̃x�N�g���𐳋K��
		difference2 = DirectX::XMVector3Normalize(difference2);

		// �v���C���[or�P�̕��Ɍ����邽�߂̃��W�A���p���擾
		float angleY;
		DirectX::XMStoreFloat(&angleY, DirectX::XMVector3AngleBetweenNormals(
			difference,			// �v���C���[or�P����I�u�W�F�N�g�ւ̕����x�N�g��
			difference2			// �L�m�R���{�ƃv���C���[or�P�̋����x�N�g�� 
		));

		// ���W�A������Degrees�Ɋp�x��ϊ�
		float angleToObjectY = DirectX::XMConvertToDegrees(angleY);

		//pObj->SetAngleToPlayer(angleToObjectY);

		// x���ŉ�]������
		// �p�x����邽�߂Ƀx�N�g�������
		difference = DirectX::XMVectorSubtract(	// ���Z��(����1 - ����2)
			DirectX::XMLoadFloat3(&workPos2),		// �L�m�R���{�̍��W���炸�炵�����W
			DirectX::XMLoadFloat3(&pos)				// �L�m�R���{�̍��W
		);
		// �I�u�W�F�N�g�ւ̃x�N�g���𐳋K��
		difference = DirectX::XMVector3Normalize(difference);

		// �v���C���[or�P�̕��Ɍ����邽�߂̃��W�A���p���擾
		float angleX;
		DirectX::XMStoreFloat(&angleX, DirectX::XMVector3AngleBetweenNormals(
			difference,			// �v���C���[or�P����I�u�W�F�N�g�ւ̕����x�N�g��
			difference2			// �L�m�R���{�ƃv���C���[or�P�̋����x�N�g�� 
		));

		// ���W�A������Degrees�Ɋp�x��ϊ�
		float angleToObjectX = DirectX::XMConvertToDegrees(angleX);

		//pObj->SetAngleToPlayer(angleToObjectX);

		// �p�x�Z�b�g
		DirectX::XMFLOAT3 objangle;
		objangle.x = m_fAngle - angleToObjectX;
		objangle.y = angleToObjectY;
		objangle.z = 0.0f;

		pObj->SetAngle(objangle);
	}
	// �v���C���[or�P���E���̕��ɂ�����
	else if (pos.x > playerPos.x && pos.z < playerPos.z)
	{
		// Y���ŉ�]������p�x�����p
		DirectX::XMFLOAT3 workPos = pos;	// �L�m�R���{
		workPos.z += VEC_OFFSETX;	// �x�N�g������邽�߂ɐL�m�R���{�̍��W���班�����炷	

		// X���ŉ�]������p�x�����p
		DirectX::XMFLOAT3 workPos2 = playerPos;
		workPos2.y = pos.y;

		// y���ŉ�]������
		// �p�x����邽�߂Ƀx�N�g�������
		DirectX::XMVECTOR difference = DirectX::XMVectorSubtract(	// ���Z��(����1 - ����2)
			DirectX::XMLoadFloat3(&pos),				// �L�m�R���{�̍��W
			DirectX::XMLoadFloat3(&workPos)				// �L�m�R���{�̍��W���炸�炵�����W
		);
		// �I�u�W�F�N�g�ւ̃x�N�g���𐳋K��
		difference = DirectX::XMVector3Normalize(difference);

		DirectX::XMVECTOR difference2 = DirectX::XMVectorSubtract(	// ���Z��(����1 - ����2)
			DirectX::XMLoadFloat3(&playerPos),		// �v���C���[or�P���W
			DirectX::XMLoadFloat3(&pos)				// �L�m�R���{�̍��W
		);
		// �I�u�W�F�N�g�ւ̃x�N�g���𐳋K��
		difference2 = DirectX::XMVector3Normalize(difference2);

		// �v���C���[or�P�̕��Ɍ����邽�߂̃��W�A���p���擾
		float angleY;
		DirectX::XMStoreFloat(&angleY, DirectX::XMVector3AngleBetweenNormals(
			difference,			// �v���C���[or�P����I�u�W�F�N�g�ւ̕����x�N�g��
			difference2			// �L�m�R���{�ƃv���C���[or�P�̋����x�N�g�� 
		));

		// ���W�A������Degrees�Ɋp�x��ϊ�
		float angleToObjectY = DirectX::XMConvertToDegrees(angleY);

		// x���ŉ�]������
		// �p�x����邽�߂Ƀx�N�g�������
		difference = DirectX::XMVectorSubtract(	// ���Z��(����1 - ����2)
			DirectX::XMLoadFloat3(&workPos2),	// �L�m�R���{�̍��W���炸�炵�����W			
			DirectX::XMLoadFloat3(&pos)			// �L�m�R���{�̍��W
		);
		// �I�u�W�F�N�g�ւ̃x�N�g���𐳋K��
		difference = DirectX::XMVector3Normalize(difference);

		// �v���C���[or�P�̕��Ɍ����邽�߂̃��W�A���p���擾
		float angleX;
		DirectX::XMStoreFloat(&angleX, DirectX::XMVector3AngleBetweenNormals(
			difference,			// �v���C���[or�P����I�u�W�F�N�g�ւ̕����x�N�g��
			difference2			// �L�m�R���{�ƃv���C���[or�P�̋����x�N�g�� 
		));

		// ���W�A������Degrees�Ɋp�x��ϊ�
		float angleToObjectX = DirectX::XMConvertToDegrees(angleX);

		// �p�x�Z�b�g
		DirectX::XMFLOAT3 objangle;
		objangle.x = -m_fAngle + angleToObjectX;
		objangle.y = angleToObjectY;
		objangle.z = 0.0f;

		pObj->SetAngle(objangle);
	}
	// �v���C���[or�P������̕��ɂ�����
	else if (pos.x < playerPos.x && pos.z > playerPos.z)
	{
		// Y���ŉ�]������p�x�����p
		DirectX::XMFLOAT3 workPos = pos;	// �L�m�R���{
		workPos.z -= VEC_OFFSETX;	// �x�N�g������邽�߂ɐL�m�R���{�̍��W���班�����炷	

		// X���ŉ�]������p�x�����p
		DirectX::XMFLOAT3 workPos2 = playerPos;
		workPos2.y = pos.y;

		// y���ŉ�]������
		// �p�x����邽�߂Ƀx�N�g�������
		DirectX::XMVECTOR difference = DirectX::XMVectorSubtract(	// ���Z��(����1 - ����2)
			DirectX::XMLoadFloat3(&pos),				// �L�m�R���{�̍��W
			DirectX::XMLoadFloat3(&workPos)				// �L�m�R���{�̍��W���炸�炵�����W
		);
		// �I�u�W�F�N�g�ւ̃x�N�g���𐳋K��
		difference = DirectX::XMVector3Normalize(difference);

		DirectX::XMVECTOR difference2 = DirectX::XMVectorSubtract(	// ���Z��(����1 - ����2)
			DirectX::XMLoadFloat3(&playerPos),		// �v���C���[or�P���W
			DirectX::XMLoadFloat3(&pos)				// �L�m�R���{�̍��W
		);
		// �I�u�W�F�N�g�ւ̃x�N�g���𐳋K��
		difference2 = DirectX::XMVector3Normalize(difference2);

		// �v���C���[or�P�̕��Ɍ����邽�߂̃��W�A���p���擾
		float angleY;
		DirectX::XMStoreFloat(&angleY, DirectX::XMVector3AngleBetweenNormals(
			difference,			// �v���C���[or�P����I�u�W�F�N�g�ւ̕����x�N�g��
			difference2			// �L�m�R���{�ƃv���C���[or�P�̋����x�N�g�� 
		));

		// ���W�A������Degrees�Ɋp�x��ϊ�
		float angleToObjectY = DirectX::XMConvertToDegrees(angleY);


		// x���ŉ�]������
		// �p�x����邽�߂Ƀx�N�g�������
		difference = DirectX::XMVectorSubtract(	// ���Z��(����1 - ����2)
			DirectX::XMLoadFloat3(&workPos2),			// �L�m�R���{�̍��W���炸�炵�����W
			DirectX::XMLoadFloat3(&pos)					// �L�m�R���{�̍��W
		);
		// �I�u�W�F�N�g�ւ̃x�N�g���𐳋K��
		difference = DirectX::XMVector3Normalize(difference);

		// �v���C���[or�P�̕��Ɍ����邽�߂̃��W�A���p���擾
		float angleX;
		DirectX::XMStoreFloat(&angleX, DirectX::XMVector3AngleBetweenNormals(
			difference,			// �v���C���[or�P����I�u�W�F�N�g�ւ̕����x�N�g��
			difference2			// �L�m�R���{�ƃv���C���[or�P�̋����x�N�g�� 
		));

		// ���W�A������Degrees�Ɋp�x��ϊ�
		float angleToObjectX = DirectX::XMConvertToDegrees(angleX);

		// �p�x�Z�b�g
		DirectX::XMFLOAT3 objangle;
		objangle.x = m_fAngle - angleToObjectX;
		objangle.y = angleToObjectY;
		objangle.z = 0.0f;

		pObj->SetAngle(objangle);
	}
	// �v���C���[or�P���E��̕��ɂ�����
	else if (pos.x > playerPos.x && pos.z > playerPos.z)
	{
		// Y���ŉ�]������p�x�����p
		DirectX::XMFLOAT3 workPos = pos;	// �L�m�R���{
		workPos.z -= VEC_OFFSETX;	// �x�N�g������邽�߂ɐL�m�R���{�̍��W���班�����炷	

		// X���ŉ�]������p�x�����p
		DirectX::XMFLOAT3 workPos2 = playerPos;
		workPos2.y = pos.y;

		// y���ŉ�]������
		// �p�x����邽�߂Ƀx�N�g�������
		DirectX::XMVECTOR difference = DirectX::XMVectorSubtract(	// ���Z��(����1 - ����2)
			DirectX::XMLoadFloat3(&workPos),		// �L�m�R���{�̍��W���炸�炵�����W
			DirectX::XMLoadFloat3(&pos)				// �L�m�R���{�̍��W
		);
		// �I�u�W�F�N�g�ւ̃x�N�g���𐳋K��
		difference = DirectX::XMVector3Normalize(difference);

		DirectX::XMVECTOR difference2 = DirectX::XMVectorSubtract(	// ���Z��(����1 - ����2)
			DirectX::XMLoadFloat3(&playerPos),		// �v���C���[or�P���W
			DirectX::XMLoadFloat3(&pos)				// �L�m�R���{�̍��W
		);
		// �I�u�W�F�N�g�ւ̃x�N�g���𐳋K��
		difference2 = DirectX::XMVector3Normalize(difference2);

		// �v���C���[or�P�̕��Ɍ����邽�߂̃��W�A���p���擾
		float angleY;
		DirectX::XMStoreFloat(&angleY, DirectX::XMVector3AngleBetweenNormals(
			difference,			// �v���C���[or�P����I�u�W�F�N�g�ւ̕����x�N�g��
			difference2			// �L�m�R���{�ƃv���C���[or�P�̋����x�N�g�� 
		));

		// ���W�A������Degrees�Ɋp�x��ϊ�
		float angleToObjectY = DirectX::XMConvertToDegrees(angleY);

		// x���ŉ�]������
		// �p�x����邽�߂Ƀx�N�g�������
		difference = DirectX::XMVectorSubtract(	// ���Z��(����1 - ����2)
			DirectX::XMLoadFloat3(&workPos2),		// �L�m�R���{�̍��W���炸�炵�����W
			DirectX::XMLoadFloat3(&pos)				// �L�m�R���{�̍��W
		);
		// �I�u�W�F�N�g�ւ̃x�N�g���𐳋K��
		difference = DirectX::XMVector3Normalize(difference);

		// �v���C���[or�P�̕��Ɍ����邽�߂̃��W�A���p���擾
		float angleX;
		DirectX::XMStoreFloat(&angleX, DirectX::XMVector3AngleBetweenNormals(
			difference,			// �v���C���[or�P����I�u�W�F�N�g�ւ̕����x�N�g��
			difference2			// �L�m�R���{�ƃv���C���[or�P�̋����x�N�g�� 
		));

		// ���W�A������Degrees�Ɋp�x��ϊ�
		float angleToObjectX = DirectX::XMConvertToDegrees(angleX);

		// �p�x�Z�b�g
		DirectX::XMFLOAT3 objangle;
		objangle.x = -m_fAngle + angleToObjectX;
		objangle.y = angleToObjectY;
		objangle.z = 0.0f;

		pObj->SetAngle(objangle);
	}
}


void Suction::SetESuction(ESuction * pEsuction)
{
	m_pESuction = pEsuction;
}

//=====�M�~�b�N�z�����ݏ���=====
void Suction::PlayGimmick()
{
	float deltaMove = 1.0f;			// �ړ��̕ω���
	int NemotoNum = 0;				// ���{�̌��J�E���g�p
	m_fAngle = 90.0f;				// �p�x�Z�b�g
	prevObjPos = m_playerPos;		// �v���C���[���W�Z�b�g
	int KasaSuction = false;	// �P���������t���O
	// ���X�g�̑S�v�f
	for (Object* pObj : *m_pObjectList)
	{
		if (pObj->GetGimmick() && !pObj->IsSuction() && pObj->GetTime() < 0.1f && pObj->GetSuctionGimmick())
		{

			// �`��t���O���������Ă�����
			if (!pObj->GetDraw())
			{
				pObj->SetDraw(true);			// �t���O�グ
				pObj->SetPlayGimmick(true);		// �M�~�b�N�t���O�グ
			}
			DirectX::XMFLOAT3 pos = pObj->GetPos();					// �M�~�b�N�I�u�W�F�N�g���W
			if (pObj->GetKind() == Object::Kind::BLUE_MUSHROOM_NEMOTO)	// ���{��������
			{
				// �����ĂȂ�������I���
				if (!KasaSuction) return;
				NemotoNum++;										// �J�E���g�A�b�v
				pos.y = prevObjPos.y - 0.2f;						// ��������
				for (int j = 0; j < NemotoNum; j++)
				{
					deltaMove *= PLAY_GIMMICK_DELTA_POS;						// �ω��ʂ̒l��ς��Ă���
				}
			}
			else
			{
				KasaSuction = true;	// �����Ă���t���O�グ
			}

			DirectX::XMFLOAT3 origin = pObj->GetGimmickOldPos();	// �I�u�W�F�N�g�̏����ʒu
			float radius = PLAY_GIMMICK * deltaMove;				// �ړ��\�͈͂̔��a
			pObj->SetSuctionGimmick(true);							// �M�~�b�N�z�����ݒ�
			DirectX::XMFLOAT3 playerPos;							// �v���C���[���W
			pObj->SetTime(0.0f);									// ���Ԍo�߃��Z�b�g
			pObj->SetWeight(1.0f);									// �����ʃ��Z�b�g
			//pObj->SetRadius(RELEASE_GIMMICK);						// �L�т�͈̓��Z�b�g

			// �v���C���[�̑O��(�J�����̌���)���W
			playerPos.x = m_playerPos.x;
			playerPos.y = m_playerPos.y;
			playerPos.z = m_playerPos.z;

			// ���{�����p�x��ς���(�v���C���[�̕����Ɍ����悤��)
			if (pObj->GetKind() == Object::Kind::BLUE_MUSHROOM_NEMOTO)
			{
				// �v���C���[�̕��Ɍ�����
				ModelRotate(pObj, prevObjPos, pos);
			}

			// �x�N�g���̍������v�Z
			DirectX::XMVECTOR startVec = DirectX::XMLoadFloat3(&pos);
			DirectX::XMVECTOR endVec = DirectX::XMLoadFloat3(&playerPos);
			DirectX::XMVECTOR direction = DirectX::XMVectorSubtract(endVec, startVec);
			direction = DirectX::XMVector3Normalize(direction); // ���K��

			// ���x�Ɋ�Â��Ĉړ��������v�Z
			float speed = 0.1f * deltaMove;
			DirectX::XMVECTOR velocity = DirectX::XMVectorScale(direction, speed);

			// ���݂̈ʒu���X�V
			DirectX::XMVECTOR currentVec = DirectX::XMLoadFloat3(&pos);
			currentVec = DirectX::XMVectorAdd(currentVec, velocity);
			DirectX::XMStoreFloat3(&pos, currentVec);

			// ���_����̐V�����ʒu�܂ł̋������v�Z
			DirectX::XMVECTOR originVec = DirectX::XMLoadFloat3(&origin);
			DirectX::XMVECTOR diffVecFromOrigin = DirectX::XMVectorSubtract(currentVec, originVec);
			float distanceFromOrigin = DirectX::XMVectorGetX(DirectX::XMVector3Length(diffVecFromOrigin));
			float distanceFromOriginSquared = DirectX::XMVectorGetX(DirectX::XMVector3LengthSq(diffVecFromOrigin));

			// �����𔼌a�Ŋ����Ĕ䗦���v�Z�i0.0f ���� 1.0f �͈̔͂ɃN�����v�j
			float ratio = min(distanceFromOrigin / (radius * 0.5f), 1.0f);
			pObj->SetSuctionDis(ratio);

			DirectX::XMFLOAT3 relese;

			// ���������a�͈͓̔����ǂ������m�F
			if (distanceFromOriginSquared > radius * radius)
			{
				// ���B�\�ȍł��߂��_��ݒ�
				DirectX::XMVECTOR limitedVec = DirectX::XMVectorAdd(originVec, DirectX::XMVectorScale(DirectX::XMVector3Normalize(diffVecFromOrigin), radius));
				currentVec = limitedVec;
			}

			// �X�V���ꂽ�ʒu��ݒ�
			DirectX::XMStoreFloat3(&pos, currentVec);
			relese.x = (pos.x) * 2.0f;
			relese.y = -pos.y;
			relese.z = (pos.z) * 2.0f;
			pObj->SetPos(pos);
			prevObjPos = pos;						// ��O�̃I�u�W�F�N�g�̍��W������Ă���
			pObj->SetRadius(RELEASE_GIMMICK);

			//// ���B����p�̋�����臒l
			//const float arrivalThreshold = speed * 1.5f; // �\���ɋ߂��Ƃ݂Ȃ�����

			//// �ړI���W�Ƃ̋������v�Z
			//DirectX::XMVECTOR diffVec = DirectX::XMVectorSubtract(currentVec, endVec);
			//float distanceSquared = DirectX::XMVectorGetX(DirectX::XMVector3LengthSq(diffVec));

			//// ������臒l�ȉ����ǂ����Ŕ���
			//if (distanceSquared <= arrivalThreshold * arrivalThreshold)
			//{
			//	//pObj->SetPos(playerPos);
			//}
		}
	}
}

//=====�M�~�b�N���쏈��=====
void Suction::ReleaseGimmick()
{
	float speed;		// �ړ����x
	int nCnt = 0;		// ���{�̌��J�E���g�p
	float deltaPos;		// �ړ��͈͂𒲐����邽�߂̕ω���
	m_fAngle = 90.0f;	// �p�x����
	int firstNemoto = 0;
	int KasaSuction = false;	// �P���������t���O
	for (Object* pObj : *m_pObjectList)
	{
		if (pObj->GetGimmick() && !pObj->GetSuctionGimmick() && pObj->GetPlayGimmick())
		{
			DirectX::XMFLOAT3 origin = pObj->GetGimmickOldPos(); // �I�u�W�F�N�g�̏����ʒu
			DirectX::XMFLOAT3 pos = pObj->GetPos();

			// ���{��������
			if (pObj->GetKind() == Object::Kind::BLUE_MUSHROOM_NEMOTO)
			{
				// �����ĂȂ�������I���
				if (!KasaSuction) return;

				pos.y = prevObjPos.y - 0.2f;		// ��������
				deltaPos = INIT_DELTA_POS;			// �ړ��͈͂𒲐�
				nCnt += 1;
				for (int i = 1; i < nCnt; i++)
				{
					deltaPos *= DELTA_POS;			// �O�̍��{�����ړ��͈͂������Ȃ�悤��
				}
				// ���{�����p�x��ς���
				// �P�̕��Ɍ�����
				ModelRotate(pObj, prevObjPos, pos);
			}
			else
			{
				KasaSuction = true;	// �����Ă���t���O�グ
			}

			// �ŏ��������B���W��ݒ�
			if (pObj->GetTime() < 0.1f)
			{
				pObj->SetEndPos(DirectX::XMFLOAT3(m_playerPos.x, pObj->GetPos().y, m_playerPos.z));
			}

			// �x�N�g���̍������v�Z
			DirectX::XMVECTOR startVec = DirectX::XMLoadFloat3(&pos);
			DirectX::XMVECTOR endVec = DirectX::XMLoadFloat3(&pObj->GetEndPos());
			DirectX::XMVECTOR direction = DirectX::XMVectorSubtract(endVec, startVec);
			direction = DirectX::XMVector3Normalize(direction); // ���K��

			// ���x�Ɋ�Â��Ĉړ��������v�Z
			float frequency = 1.0f; // ���g���i�ω��̑����j
			float radMinus;			// �͈͐������a���Z�p

			// ���{�̃J�E���g���n�܂��Ă�����
			if (nCnt)
			{
				// �T�C���J�[�u���g�������x�̌v�Z
				speed = -(((pObj->GetAmplitude() * deltaPos) * pObj->GetSuctionDis()) * sin(frequency * pObj->GetTime()));
				speed *= (pObj->GetWeight() * deltaPos);
			}
			// �n�܂��Ă��Ȃ�������
			else
			{
				// �T�C���J�[�u���g�������x�̌v�Z
				speed = -((pObj->GetAmplitude() * pObj->GetSuctionDis()) * sin(frequency * pObj->GetTime()));
				speed *= pObj->GetWeight();
			}

			// ��������
			if (pObj->GetWeight() > 0.1f)
			{
				pObj->SetWeight(pObj->GetWeight() - WEIGHT_MINUS);
			}
			else
			{
				pObj->SetWeight(0.1f);
			}

			DirectX::XMVECTOR velocity = DirectX::XMVectorScale(direction, speed);
			// ���ԁi�܂��̓t���[�����j���X�V
			pObj->SetTime(pObj->GetTime() + 0.1f);
			radMinus = pObj->GetTime() * 0.01f;

			// ���݂̈ʒu���X�V
			DirectX::XMVECTOR currentVec = DirectX::XMLoadFloat3(&pos);
			currentVec = DirectX::XMVectorAdd(currentVec, velocity);
			DirectX::XMStoreFloat3(&pos, currentVec);

			// ���_����̐V�����ʒu�܂ł̋������v�Z
			DirectX::XMVECTOR originVec = DirectX::XMLoadFloat3(&origin);
			DirectX::XMVECTOR diffVecFromOrigin = DirectX::XMVectorSubtract(currentVec, originVec);

			// ���_(���̈ʒu)����̋����𑪂�
			DirectX::XMFLOAT3 diffF3;									// �����𑪂�p
			DirectX::XMStoreFloat3(&diffF3, diffVecFromOrigin);			// Float3�ɕϊ�

			// ���_���痣�ꂷ���Ă��Ȃ��Ȃ�`�悵�Ȃ�
			if (pObj->GetKind() == Object::Kind::BLUE_MUSHROOM_NEMOTO &&
				((diffF3.x > -0.02f && diffF3.x < 0.02f) && (diffF3.z > -0.02f && diffF3.z < 0.02f)))
			{
				pObj->SetDraw(false);	// �`��t���O����
			}

			float distanceFromOriginSquared = DirectX::XMVectorGetX(DirectX::XMVector3LengthSq(diffVecFromOrigin));

			if (pObj->GetRadius() > 0.1f)
			{
				pObj->SetRadius(pObj->GetRadius() - radMinus);
			}
			if (pObj->GetRadius() <= 0.1f)
			{
				m_pPlayer->SetSuction(false);
				pObj->SetPlayGimmick(false);
				pObj->SetTime(0.0f);
				pObj->SetWeight(1.0f);
				pObj->SetRadius(0.0f);

				// �p�x���Z�b�g
				m_fAngle = 0.0f;
				DirectX::XMFLOAT3 objangle;
				objangle.x = 0.0f;
				objangle.y = 0.0f;
				objangle.z = 0.0f;

				pObj->SetAngle(objangle);
				if (firstNemoto == 0 && pObj->GetKind() == Object::Kind::BLUE_MUSHROOM_NEMOTO)
				{
					firstNemoto++;
					pObj->SetDraw(true);	// �擪�̍��{�͕`�悷��
				}
			}

			// ���������a�͈͓̔����ǂ������m�F
			if (distanceFromOriginSquared > pObj->GetRadius() * pObj->GetRadius())
			{
				// ���B�\�ȍł��߂��_��ݒ�
				DirectX::XMVECTOR limitedVec = DirectX::XMVectorAdd(originVec, DirectX::XMVectorScale(DirectX::XMVector3Normalize(diffVecFromOrigin), pObj->GetRadius()));
				currentVec = limitedVec;
			}

			// �X�V���ꂽ�ʒu��ݒ�
			DirectX::XMStoreFloat3(&pos, currentVec);
			pObj->SetPos(pos);
			prevObjPos = pos;				// ��O�̃I�u�W�F�N�g�̍��W�Ƃ��Ď���Ă���		
			
		}
	}
}

void Suction::SetPlayer(CPlayer * player)
{
	m_pPlayer = player;
}

void Suction::SetDrill(CDrill * drill)
{
	m_pDrill = drill;
}

void Suction::SetHammer(CHammer * hammer)
{
	m_pHammer = hammer;
}

void Suction::SetSaw(CSaw * saw)
{
	m_pSaw = saw;
}
