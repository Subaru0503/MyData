//----�C���N���[�h��----
#include "ObjectManager.h"
#include "Geometory.h"
#include "Player.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

const float CREATE_OBJECT_RADIUS = 0.4f;	// �I�u�W�F�N�g�����������j�󂵂��I�u�W�F�N�g����̋���

CObjectMng::CObjectMng()	// �R���X�g���N�^
	: m_sucionedObjNum(0)
	, m_totalObjNum(0)
	, m_pModelManager(nullptr)
	, m_firstSuccsion{ 0 }
{
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso")))	// �V�F�[�_�ǂݍ���
	{
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}

	// �I�u�W�F�N�g�Ƀ��f�������蓖�Ă�p
	m_pModelManager = new ModelManager();
}

CObjectMng::~CObjectMng()	// �f�X�g���N�^
{
	// ���X�g���̂��ׂẴI�u�W�F�N�g�����
	for (Object* pObj : m_ObjectList) {
		if (pObj != nullptr)
		{
			//pObj->Uninit();
			delete pObj;
		}
	}
	m_ObjectList.clear();// �S�v�f�폜

	if (m_pVS)
	{
		delete m_pVS;
		m_pVS = nullptr;
	}

	if (m_pModelManager)
	{
		delete m_pModelManager;
		m_pModelManager = nullptr;
	}
}

void CObjectMng::Update(float tick)	// �X�V
{
	//--�z�����܂��or�j�󂳂��I�u�W�F�N�g�̏���
	for (auto it = m_ObjectList.begin(); it != m_ObjectList.end();)
	{
		Object* pObj = *it;			// �I�u�W�F�N�g�̊֐����Ăяo����悤�ɕϊ�
		(*it)->SetPlayerPos(m_pPlayer->GetPos());	// �v���C���[�̍��W�����I�u�W�F�N�g�ɐݒ�

		if (pObj->GetDelete()) {	// �폜�t���O�������Ă�����
			if (!pObj->IsMove() && !pObj->IsSuction())	// �j�󂳂ꂽ���̂ł����
			{
				CreateObject(pObj);		// ��ނɂ���Ĕj���ɐ�������I�u�W�F�N�g���쐬
			}
			else
			{
				if (pObj->GetCreateNum() == 0)	// �j��I�u�W�F�N�g�łȂ����
					m_sucionedObjNum++;	// �z�����݃J�E���g���P�i�߂�
				else // �j��I�u�W�F�N�g�Ȃ�
					m_sucionedObjNum += pObj->GetCreateNum();	// ���������͂��������I�u�W�F�N�g�̌����J�E���g��i�߂�	
			}

			//--�z������SE
			switch (pObj->GetKind())
			{
			case Object::MUSHROOM:
				m_pSoundMng->playSound(CSoundMng::SuctionSE::suctionHigh);
				m_pSoundMng->playSound(CSoundMng::SuctionSE::money);
				break;
			case Object::STONE:
				m_pSoundMng->playSound(CSoundMng::SuctionSE::suctionHigh);
				m_pSoundMng->playSound(CSoundMng::SuctionSE::money);
				break;
			case Object::WOOD:
				m_pSoundMng->playSound(CSoundMng::SuctionSE::suctionHigh);
				m_pSoundMng->playSound(CSoundMng::SuctionSE::money);
				break;
			case Object::TREE:
				if (m_pSuction->GetNozzleLevel() >= pObj->GetLevel())
				{
					m_pSoundMng->playSound(CSoundMng::SuctionSE::suctionLow);
					m_pSoundMng->playSound(CSoundMng::SuctionSE::money);
					switch (pObj->GetLevel()){	// �����x�����z�����񂾂�
					case 1:	m_firstSuccsion.tree1++;	break;	// ���x���P
					case 2:	m_firstSuccsion.tree2++;	break;
					case 3:	m_firstSuccsion.tree3++;	break;
					}
				}
				else
				{
					m_pSoundMng->playSound(CSoundMng::DestroySE::woodBreak);
					m_pDust->Play();
				}
				break;
			case Object::ROCK:
				if (m_pSuction->GetNozzleLevel() >= pObj->GetLevel())
				{
					m_pSoundMng->playSound(CSoundMng::SuctionSE::suctionLow);
					m_pSoundMng->playSound(CSoundMng::SuctionSE::money);
										m_pSoundMng->playSound(CSoundMng::SuctionSE::suctionLow);
					switch (pObj->GetLevel()) {	// �����x�����z�����񂾂�
					case 1:	m_firstSuccsion.rock1++;	break;	// ���x���P
					case 2:	m_firstSuccsion.rock2++;	break;
					case 3:	m_firstSuccsion.rock3++;	break;
					}
				}
				else
				{
					m_pSoundMng->playSound(CSoundMng::DestroySE::rockBreak);
					m_pDust->Play();
				}
				break;
			case Object::FENCE:	// �؁A�΁A�S
				if (m_pSuction->GetNozzleLevel() >= pObj->GetLevel())
				{
					m_pSoundMng->playSound(CSoundMng::SuctionSE::suctionHigh);
					m_pSoundMng->playSound(CSoundMng::SuctionSE::money);
					m_firstSuccsion.fence++;
				}
				else
				{
					if (pObj->GetLevel() == 2)
					{
						m_pSoundMng->playSound(CSoundMng::DestroySE::woodBreak);
						m_pDust->Play();
					}
					if (pObj->GetLevel() == 3)
					{
						m_pSoundMng->playSound(CSoundMng::DestroySE::rockBreak);
						m_pDust->Play();
					}
					if (pObj->GetLevel() == 4)
					{
						m_pSoundMng->playSound(CSoundMng::DestroySE::rocklHouseBreak);
						m_pDust->Play();
					}
				}
				break;
			case Object::HOUSE:
				m_pSoundMng->playSound(CSoundMng::DestroySE::woodHouseBreak);
				break;
			case Object::SIGNBOARD:
				if (m_pSuction->GetNozzleLevel() >= pObj->GetLevel())
				{
					m_pSoundMng->playSound(CSoundMng::SuctionSE::suctionHigh);
					m_pSoundMng->playSound(CSoundMng::SuctionSE::money);
					m_firstSuccsion.signBoard++;
				}
				else
				{
					m_pSoundMng->playSound(CSoundMng::DestroySE::woodBreak);
					m_pDust->Play();
				}
				break;
			case Object::TUTORIALSIGNBOARD:
				m_pSoundMng->playSound(CSoundMng::SuctionSE::suctionHigh);
				m_pSoundMng->playSound(CSoundMng::SuctionSE::money);
				break;
				//�X�e�[�W3
			case Object::DONUTS:
				m_pSoundMng->playSound(CSoundMng::SuctionSE::suctionHigh);
				m_pSoundMng->playSound(CSoundMng::SuctionSE::money);
				break;
			case Object::CAKEPIECE:
				m_pSoundMng->playSound(CSoundMng::SuctionSE::suctionHigh);
				m_pSoundMng->playSound(CSoundMng::SuctionSE::money);
				break;
			case Object::STRAWBERRY:
				m_pSoundMng->playSound(CSoundMng::SuctionSE::suctionHigh);
				m_pSoundMng->playSound(CSoundMng::SuctionSE::money);
				break;
			case Object::APOLO:
				m_pSoundMng->playSound(CSoundMng::SuctionSE::suctionHigh);
				m_pSoundMng->playSound(CSoundMng::SuctionSE::money);
				break;
			case Object::COOKIE:
				m_pSoundMng->playSound(CSoundMng::SuctionSE::suctionHigh);
				m_pSoundMng->playSound(CSoundMng::SuctionSE::money);
				break;
			case Object::CHOCOLATETREE:
				if (m_pSuction->GetNozzleLevel() >= pObj->GetLevel())
				{
					m_pSoundMng->playSound(CSoundMng::SuctionSE::suctionHigh);
					m_pSoundMng->playSound(CSoundMng::SuctionSE::money);
				}
				else
				{
					m_pSoundMng->playSound(CSoundMng::DestroySE::wood);
					m_pDust->Play();
				}
				break;
			case Object::CHOCOLATEPIECE:
				m_pSoundMng->playSound(CSoundMng::SuctionSE::suctionHigh);
				m_pSoundMng->playSound(CSoundMng::SuctionSE::money);
				break;
			case Object::CHOCOLATEFENCE:
				if (m_pSuction->GetNozzleLevel() >= pObj->GetLevel())
				{
					m_pSoundMng->playSound(CSoundMng::SuctionSE::suctionHigh);
					m_pSoundMng->playSound(CSoundMng::SuctionSE::money);
				}
				else
				{
					m_pSoundMng->playSound(CSoundMng::DestroySE::wood);
					m_pDust->Play();
				}
				break;
			case Object::CANDYROCK:
				if (m_pSuction->GetNozzleLevel() >= pObj->GetLevel())
				{
					m_pSoundMng->playSound(CSoundMng::SuctionSE::suctionHigh);
					m_pSoundMng->playSound(CSoundMng::SuctionSE::money);
				}
				else
				{
					m_pSoundMng->playSound(CSoundMng::DestroySE::rock);
					m_pDust->Play();
				}
				break;
			case Object::CANDYPIECE:
				m_pSoundMng->playSound(CSoundMng::SuctionSE::suctionHigh);
				m_pSoundMng->playSound(CSoundMng::SuctionSE::money);
			case Object::CANDLE:
			{
				m_pSoundMng->playSound(CSoundMng::SuctionSE::suctionHigh);
				m_pSoundMng->playSound(CSoundMng::SuctionSE::money);
			}
			break;
			case Object::SWEETSHOUSE:
				if (m_pSuction->GetNozzleLevel() >= pObj->GetLevel())
				{
					m_pSoundMng->playSound(CSoundMng::SuctionSE::suctionHigh);
					m_pSoundMng->playSound(CSoundMng::SuctionSE::money);
				}
				else
				{
					m_pSoundMng->playSound(CSoundMng::DestroySE::woodHouseBreak);
					m_pDust->Play();
				}
				break;
			case Object::BISCUIT:
				if (pObj->GetDefCnt() <= 0)
				{
					m_pSoundMng->playSound(CSoundMng::GimmickSE::cookieBreak);
				}
				else
				{
					m_pSoundMng->playSound(CSoundMng::SuctionSE::suctionLow);
				}
				break;
			case Object::BISCUITPIECE:
				m_pSoundMng->playSound(CSoundMng::SuctionSE::suctionHigh);
				m_pSoundMng->playSound(CSoundMng::SuctionSE::money);
				break;
			}
			m_pEBag->Play(pObj);
			delete pObj;					// �����������
			it = m_ObjectList.erase(it);	// ���X�g����폜���ăC�e���[�^���X�V�����̗v�f��
		}
		else {			// �폜���Ȃ��̂�
			++it;		// �C�e���[�^��i�߂�
		}
	}
	int i = 0;
	// �I�u�W�F�N�g�X�V����
	for (Object* pObj : m_ObjectList)
	{
		pObj->SetTime(m_nTime);
		pObj->Update(tick);
		m_pLeaf->Play(pObj, i);
		i++;
	}

}

void CObjectMng::Draw(DirectX::XMFLOAT4X4 *mat)		// �`��
{
	// ���X�g���̃I�u�W�F�N�g�̕`�揈��
	for (Object* pObj : m_ObjectList)
	{
		bool draw = pObj->GetDraw();
		if (pObj->GetModel() != nullptr)
		{
			RenderTarget* pRTV = GetDefaultRTV();
			DepthStencil* pDSV = GetDefaultDSV();
			SetRenderTargets(1, &pRTV, pDSV);
			if (draw)
				pObj->DrawModel(mat, m_pVS);
		}
		else
		{
			if (draw)
				pObj->DrawBox(mat);
		}	
	}
	for (Object* pObj : m_ObjectList) {
		if (pObj->IsShake())
		{
			if (pObj->GetKind() != Object::BLUE_MUSHROOM_NEMOTO)
			{
				RenderTarget* pRTV = GetDefaultRTV();
				SetRenderTargets(1, &pRTV, nullptr);
				pObj->DrawIcon(pObj->GetPos(), pObj->GetKind(), pObj->GetLevel(), m_pPlayer);
			}
		}
	}

}

void CObjectMng::CreateObject(Object* pObj)	// �I�u�W�F�N�g�쐬
{
	//===�h���b�v�ʒu�̌v�Z===
// ���ː���̔z�u�p�x�̊Ԋu
	float angleSpan = DirectX::XM_PI * 2 / pObj->GetCreateNum();	// 360�x�𐶐����Ŋ���
	float angle = 0.0f;
	float random = float(rand()) / float(rand());
	float x, z;
	float radius = CREATE_OBJECT_RADIUS;
	DirectX::XMFLOAT3 dropPos;

	//----䕃`���R�̂�����������t���O----
	int nStrawberry = false;

	switch (pObj->GetKind())
	{
	case Object::TREE:
		for (int i = 0; i < pObj->GetCreateNum(); i++)
		{
			angle = angleSpan * i + random;
			x = pObj->GetOldPos().x + cos(angle) * radius;
			z = pObj->GetOldPos().z + sin(angle) * radius;
			dropPos = { x, pObj->GetOldPos().y - (pObj->GetScale().y / 7.0f), z };
			DirectX::XMVECTOR dropDirection = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&dropPos), DirectX::XMLoadFloat3(&pObj->GetOldPos()));
			dropDirection = DirectX::XMVector3Normalize(dropDirection);
			if (pObj->GetLevel() == 4) {
				m_ObjectList.push_back(new CWoodRoyal(x, pObj->GetOldPos().y - (pObj->GetScale().y / 3.0f), z, dropDirection, m_pModelManager));
			}
			else {
				m_ObjectList.push_back(new CWood(x, pObj->GetOldPos().y - (pObj->GetScale().y / 3.0f), z, dropDirection, m_pModelManager));
			}
		}
		break;
	case Object::ROCK:
		for (int i = 0; i < pObj->GetCreateNum(); i++)
		{
			angle = angleSpan * i + random;
			x = pObj->GetOldPos().x + cos(angle) * radius;
			z = pObj->GetOldPos().z + sin(angle) * radius;
			dropPos = { x, pObj->GetOldPos().y - (pObj->GetScale().y / 3.0f), z };
			DirectX::XMVECTOR dropDirection = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&dropPos), DirectX::XMLoadFloat3(&pObj->GetOldPos()));
			dropDirection = DirectX::XMVector3Normalize(dropDirection);
			if (pObj->GetLevel() == 4) {
				m_ObjectList.push_back(new CStoneRoyal(x, pObj->GetOldPos().y - (pObj->GetScale().y / 3.0f), z, dropDirection, m_pModelManager));
			}
			else {
				m_ObjectList.push_back(new CStone(x, pObj->GetOldPos().y - (pObj->GetScale().y / 3.0f), z, dropDirection, m_pModelManager));
			}
			
		}
		break;
	case Object::HOUSE:
		for (int i = 0; i < pObj->GetCreateNum(); i++)
		{
			angle = angleSpan * i + random;
			x = pObj->GetOldPos().x + cos(angle) * radius;
			z = pObj->GetOldPos().z + sin(angle) * radius;
			dropPos = { x, pObj->GetOldPos().y - (pObj->GetScale().y / 3.0f), z };
			DirectX::XMVECTOR dropDirection = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&dropPos), DirectX::XMLoadFloat3(&pObj->GetOldPos()));
			dropDirection = DirectX::XMVector3Normalize(dropDirection);
			m_ObjectList.push_back(new CWood(x, pObj->GetOldPos().y - (pObj->GetScale().y / 3.0f), z, dropDirection, m_pModelManager));
		}
		break;
	case Object::BURNINGOBJECT:
		for (int i = 0; i < pObj->GetCreateNum(); i++)
		{
			angle = angleSpan * i + random;
			x = pObj->GetOldPos().x + cos(angle) * radius;
			z = pObj->GetOldPos().z + sin(angle) * radius;
			dropPos = { x, pObj->GetOldPos().y - (pObj->GetScale().y / 3.0f), z };
			DirectX::XMVECTOR dropDirection = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&dropPos), DirectX::XMLoadFloat3(&pObj->GetOldPos()));
			dropDirection = DirectX::XMVector3Normalize(dropDirection);
			m_ObjectList.push_back(new CWood(x, pObj->GetOldPos().y - (pObj->GetScale().y / 3.0f), z, dropDirection, m_pModelManager));
		}
		break;
	case Object::FENCE:
		for (int i = 0; i < pObj->GetCreateNum(); i++)
		{

			angle = angleSpan * i + random;
			x = pObj->GetOldPos().x + cos(angle) * radius;
			z = pObj->GetOldPos().z + sin(angle) * radius;
			dropPos = { x, pObj->GetOldPos().y - (pObj->GetScale().y / 3.0f), z };
			DirectX::XMVECTOR dropDirection = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&dropPos), DirectX::XMLoadFloat3(&pObj->GetOldPos()));
			dropDirection = DirectX::XMVector3Normalize(dropDirection);
			if (pObj->GetLevel() == 2) {
				m_ObjectList.push_back(new CWood(x, pObj->GetOldPos().y - (pObj->GetScale().y / 3.0f), z, dropDirection, m_pModelManager));
			}
			if (pObj->GetLevel() == 3) {
				m_ObjectList.push_back(new CStone(x, pObj->GetOldPos().y - (pObj->GetScale().y / 3.0f), z, dropDirection, m_pModelManager));
			}
			if (pObj->GetLevel() == 4) {
				m_ObjectList.push_back(new CStoneRoyal(x, pObj->GetOldPos().y - (pObj->GetScale().y / 3.0f), z, dropDirection, m_pModelManager));
			}
		}
		break;
	case Object::SIGNBOARD:
		for (int i = 0; i < pObj->GetCreateNum(); i++)
		{
			angle = angleSpan * i + random;
			x = pObj->GetOldPos().x + cos(angle) * radius;
			z = pObj->GetOldPos().z + sin(angle) * radius;
			dropPos = { x, pObj->GetOldPos().y - (pObj->GetScale().y / 3.0f), z };
			DirectX::XMVECTOR dropDirection = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&dropPos), DirectX::XMLoadFloat3(&pObj->GetOldPos()));
			dropDirection = DirectX::XMVector3Normalize(dropDirection);
			m_ObjectList.push_back(new CWood(x, pObj->GetOldPos().y - (pObj->GetScale().y / 3.0f), z, dropDirection, m_pModelManager));
		}
		break;
	case Object::CHOCOLATETREE:
		for (int i = 0; i < pObj->GetCreateNum(); i++)
		{
			angle = angleSpan * i + random;
			x = pObj->GetOldPos().x + cos(angle) * radius;
			z = pObj->GetOldPos().z + sin(angle) * radius;
			dropPos = { x, pObj->GetOldPos().y - (pObj->GetScale().y / 3.0f), z };
			DirectX::XMVECTOR dropDirection = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&dropPos), DirectX::XMLoadFloat3(&pObj->GetOldPos()));
			dropDirection = DirectX::XMVector3Normalize(dropDirection);
			if (pObj->GetLevel() == 4) {
				m_ObjectList.push_back(new ChocolatePieceRoyal(x, pObj->GetOldPos().y - (pObj->GetScale().y / 3.0f), z, 1.0f, 1.0f, 1.0f, dropDirection, m_pModelManager));
			}
			else {
				m_ObjectList.push_back(new ChocolatePiece(x, pObj->GetOldPos().y - (pObj->GetScale().y / 3.0f), z, 1.0f, 1.0f, 1.0f, dropDirection, m_pModelManager));
			}
		}
		break;
	case Object::CHOCOLATEFENCE:

		// 䕃`���R�̃t�F���X���ǂ���
		if (pObj->GetModelKey() == (string)"䕃`���R�̃t�F���X")
		{
			nStrawberry = true;	// �t���O�グ
		}

		for (int i = 0; i < pObj->GetCreateNum(); i++)
		{

			angle = angleSpan * i + random;
			x = pObj->GetOldPos().x + cos(angle) * radius;
			z = pObj->GetOldPos().z + sin(angle) * radius;
			dropPos = { x, pObj->GetOldPos().y - (pObj->GetScale().y / 3.0f), z };
			DirectX::XMVECTOR dropDirection = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&dropPos), DirectX::XMLoadFloat3(&pObj->GetOldPos()));
			dropDirection = DirectX::XMVector3Normalize(dropDirection);
			m_ObjectList.push_back(new ChocolatePiece(x, pObj->GetOldPos().y - (pObj->GetScale().y / 3.0f), z, 1.0f, 1.0f, 1.0f, dropDirection, m_pModelManager, nStrawberry));
		}
		break;
	case Object::CANDYROCK:
		for (int i = 0; i < pObj->GetCreateNum(); i++)
		{
			angle = angleSpan * i + random;
			x = pObj->GetOldPos().x + cos(angle) * radius;
			z = pObj->GetOldPos().z + sin(angle) * radius;
			dropPos = { x, pObj->GetOldPos().y - (pObj->GetScale().y / 3.0f), z };
			DirectX::XMVECTOR dropDirection = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&dropPos), DirectX::XMLoadFloat3(&pObj->GetOldPos()));
			dropDirection = DirectX::XMVector3Normalize(dropDirection);
			if (pObj->GetLevel() == 4) {
				m_ObjectList.push_back(new CandyPieceRoyal(x, pObj->GetOldPos().y - (pObj->GetScale().y / 3.0f), z, 1.0f, 1.0f, 1.0f, dropDirection, m_pModelManager));
			}
			else {
				m_ObjectList.push_back(new CandyPiece(x, pObj->GetOldPos().y - (pObj->GetScale().y / 3.0f), z, 1.0f, 1.0f, 1.0f, dropDirection, m_pModelManager));
			}
			
		}
		break;
	case Object::SWEETSHOUSE:
		for (int i = 0; i < pObj->GetCreateNum(); i++)
		{
			angle = angleSpan * i + random;
			x = pObj->GetOldPos().x + cos(angle) * radius;
			z = pObj->GetOldPos().z + sin(angle) * radius;
			dropPos = { x, pObj->GetOldPos().y - (pObj->GetScale().y / 3.0f), z };
			DirectX::XMVECTOR dropDirection = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&dropPos), DirectX::XMLoadFloat3(&pObj->GetOldPos()));
			dropDirection = DirectX::XMVector3Normalize(dropDirection);
			m_ObjectList.push_back(new ChocolatePieceRoyal(x, pObj->GetOldPos().y - (pObj->GetScale().y / 3.0f), z, 1.0f, 1.0f, 1.0f, dropDirection, m_pModelManager));
		}
		break;
	case Object::BISCUIT:
		for (int i = 0; i < pObj->GetCreateNum(); i++)
		{
			angle = angleSpan * i + random;
			x = pObj->GetOldPos().x + cos(angle) * radius;
			z = pObj->GetOldPos().z + sin(angle) * radius;
			dropPos = { x, pObj->GetOldPos().y - (pObj->GetScale().y / 3.0f), z };
			DirectX::XMVECTOR dropDirection = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&dropPos), DirectX::XMLoadFloat3(&pObj->GetOldPos()));
			dropDirection = DirectX::XMVector3Normalize(dropDirection);
			m_ObjectList.push_back(new CBiscuitPiece(x, pObj->GetOldPos().y - (pObj->GetScale().y / 3.0f), z, 0.5f, 0.5f, 0.5f, dropDirection, m_pModelManager));
		}
		break;
	}
}

list<Object*>* CObjectMng::GetObjectList()
{
	return &m_ObjectList;
}

int CObjectMng::GetTotalObjNum()
{
	return m_totalObjNum;
}

int CObjectMng::GetSuctionedObjNum()
{
	return m_sucionedObjNum;
}

CObjectMng::FirstSuction* CObjectMng::GetFirstSuctionFlg()
{
	return &m_firstSuccsion;
}

void CObjectMng::SetTotalObjNum(int totalObjNum)
{
	m_totalObjNum = totalObjNum;
}

void CObjectMng::ModelSetting()
{
	for (Object* pObj : m_ObjectList) {
		pObj->SetModelManager(m_pModelManager);	// ���f���}�l�[�W���[���I�u�W�F�N�g�ɃZ�b�g
		pObj->SetModelData();					// �I�u�W�F�N�g�Ƀ��f�����Z�b�g
	}
}

void CObjectMng::SetSuction(Suction * suction)
{
	m_pSuction = suction;
}

void CObjectMng::SetSound(CSoundMng * sound)
{
	m_pSoundMng = sound;
}

void CObjectMng::SetTime(int time)
{
	m_nTime = time;
}

void CObjectMng::SetPlayer(CPlayer * pPlayer)
{
	m_pPlayer = pPlayer;
}

void CObjectMng::SetDust(Dust * pDust)
{
	m_pDust = pDust;
}

void CObjectMng::SetLeaf(Leaf * pLeaf)
{
	m_pLeaf = pLeaf;
}

void CObjectMng::SetBag(EBag * pBag)
{
	m_pEBag = pBag;
}