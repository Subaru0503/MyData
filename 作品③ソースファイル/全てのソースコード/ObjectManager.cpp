//----インクルード部----
#include "ObjectManager.h"
#include "Geometory.h"
#include "Player.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

const float CREATE_OBJECT_RADIUS = 0.4f;	// オブジェクトが生成される破壊したオブジェクトからの距離

CObjectMng::CObjectMng()	// コンストラクタ
	: m_sucionedObjNum(0)
	, m_totalObjNum(0)
	, m_pModelManager(nullptr)
	, m_firstSuccsion{ 0 }
{
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso")))	// シェーダ読み込み
	{
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}

	// オブジェクトにモデルを割り当てる用
	m_pModelManager = new ModelManager();
}

CObjectMng::~CObjectMng()	// デストラクタ
{
	// リスト内のすべてのオブジェクトを解放
	for (Object* pObj : m_ObjectList) {
		if (pObj != nullptr)
		{
			//pObj->Uninit();
			delete pObj;
		}
	}
	m_ObjectList.clear();// 全要素削除

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

void CObjectMng::Update(float tick)	// 更新
{
	//--吸い込まれるor破壊されるオブジェクトの処理
	for (auto it = m_ObjectList.begin(); it != m_ObjectList.end();)
	{
		Object* pObj = *it;			// オブジェクトの関数を呼び出せるように変換
		(*it)->SetPlayerPos(m_pPlayer->GetPos());	// プレイヤーの座標情報をオブジェクトに設定

		if (pObj->GetDelete()) {	// 削除フラグが立っていたら
			if (!pObj->IsMove() && !pObj->IsSuction())	// 破壊されたものであれば
			{
				CreateObject(pObj);		// 種類によって破壊後に生成するオブジェクトを作成
			}
			else
			{
				if (pObj->GetCreateNum() == 0)	// 破壊オブジェクトでなければ
					m_sucionedObjNum++;	// 吸い込みカウントを１進める
				else // 破壊オブジェクトなら
					m_sucionedObjNum += pObj->GetCreateNum();	// 生成されるはずだったオブジェクトの個数分カウントを進める	
			}

			//--吸い込みSE
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
					switch (pObj->GetLevel()){	// 何レベルを吸い込んだか
					case 1:	m_firstSuccsion.tree1++;	break;	// レベル１
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
					switch (pObj->GetLevel()) {	// 何レベルを吸い込んだか
					case 1:	m_firstSuccsion.rock1++;	break;	// レベル１
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
			case Object::FENCE:	// 木、石、鉄
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
				//ステージ3
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
			delete pObj;					// メモリを解放
			it = m_ObjectList.erase(it);	// リストから削除してイテレータを更新→次の要素へ
		}
		else {			// 削除しないので
			++it;		// イテレータを進める
		}
	}
	int i = 0;
	// オブジェクト更新処理
	for (Object* pObj : m_ObjectList)
	{
		pObj->SetTime(m_nTime);
		pObj->Update(tick);
		m_pLeaf->Play(pObj, i);
		i++;
	}

}

void CObjectMng::Draw(DirectX::XMFLOAT4X4 *mat)		// 描画
{
	// リスト内のオブジェクトの描画処理
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

void CObjectMng::CreateObject(Object* pObj)	// オブジェクト作成
{
	//===ドロップ位置の計算===
// 放射線状の配置角度の間隔
	float angleSpan = DirectX::XM_PI * 2 / pObj->GetCreateNum();	// 360度を生成個数で割る
	float angle = 0.0f;
	float random = float(rand()) / float(rand());
	float x, z;
	float radius = CREATE_OBJECT_RADIUS;
	DirectX::XMFLOAT3 dropPos;

	//----苺チョコのかけらをだすフラグ----
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

		// 苺チョコのフェンスかどうか
		if (pObj->GetModelKey() == (string)"苺チョコのフェンス")
		{
			nStrawberry = true;	// フラグ上げ
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
		pObj->SetModelManager(m_pModelManager);	// モデルマネージャーをオブジェクトにセット
		pObj->SetModelData();					// オブジェクトにモデルをセット
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