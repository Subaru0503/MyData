//SceneGame.cpp
//=====�C���N���[�h��=====
#include "SceneGame.h"
#include "Geometory.h"
#include "Defines.h"
#include "Input.h"
#include "CameraDebug.h"
// ----- �}�b�v�ǂݍ��� -----
#include <fstream>
#include <sstream>
#include <string>

//=====�萔�E�}�N����`=====
#define DEBUG	(1)
#define MAX_FRAME (53)
#define WAIT_FRAME (53)
#define CAL_CAMERA (0.79f)
#define CAM_RAD_BEFORE (10.0f)
#define START_CAM_RAD (2.0f)
#define CAMERA_RAD (20.0f)
#define START_CAM_POS_Y (1.5f)
#define CAMERA_POS_Y (6.0f)
#define HORIZON (50.0f)
#define VERTICAL (45.0f)
#define START_HORIZON (-270.0f)
#define START_VERTICAL (45.0f)


//=====�O���[�o���錾=====
CUI* g_pUI;

//=====�R���X�g���N�^=====
SceneGame::SceneGame(CSceneMng* pSceneMng, CSoundMng* pSoundMng)
	: m_pSceneMng(pSceneMng)
	, m_pSoundMng(pSoundMng)
	, m_pTrade{ nullptr }
	, m_start(false)
	, m_count(false)
	, time(0)
	, addtime(0)
	, Alpha(1.0f)
{
	// ----- ���_�V�F�[�_�[�ǂݍ��� -----
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}

	m_pSkyModel = new Model;
	if (!m_pSkyModel->Load("Assets/Model/sky/sky.fbx", 1.0f, Model::Flip::XFlip)) {
		MessageBox(NULL, "Assets/map/sky/sky.fbx", "Error", MB_OK);
	}

	m_pSeaModel = new Model;
	if (!m_pSeaModel->Load("Assets/Model/Stage/Sea/Sea.fbx", 1.0f, Model::Flip::XFlip)) {
		MessageBox(NULL, "Assets/map/Stage/Sea.fbx", "Error", MB_OK);
	}

	// ----- �f�[�^�쐬 -----
	g_pUI = new CUI();
	m_pTimer = new CTimer();
	m_pCamera = new CameraDebug;
	m_pObjectMng = new CObjectMng;
	m_pPlayer = new CPlayer;
	m_pPlayer->SetObjectMng(m_pObjectMng);
	m_pPlayer->SetSoundMng(m_pSoundMng);
	m_pCollisionAreaMng = new CCollisionAreaMng;
	m_pCollisionAreaMng->SetPlayer(m_pPlayer);
	m_pCollision = new CCollision;
	m_pCollision->SetPlayer(m_pPlayer);
	m_pCollision->SetObjectManager(m_pObjectMng);
	m_pObjectMng->SetSound(m_pSoundMng);
	m_pObjectMng->SetSuction(m_pPlayer->GetSuction());
	m_pShopMenu = new CShopMenu();
	m_pShopMenu->SetSound(m_pSoundMng);
	m_pShopText = new CShopText();
	m_pShopText->SetSound(m_pSoundMng);
	m_pCountDown = new CCountDown();
	m_pShopBG = new ShopBG();
	m_pPlayerText = new CPlayerText();
	m_pPlayerText->SetObjMng(m_pObjectMng);
	m_pEndUI = new GameEndUI(640.0f, 360.0f, 0.0f);
	// �}�b�v�ǂݍ���
	LoadMap(/*int �ǂݍ��ރX�e�[�W�ԍ�, */m_pObjectMng->GetObjectList(), m_pCollisionAreaMng->GetAreaList(), m_pPlayer, m_pObjectMng);
	m_pProgress = new CProgress(m_pObjectMng->GetTotalObjNum(), m_pSoundMng);
	m_pCustomEquipment = new CCustomEquipment();
	// �I�u�W�F�N�g�ւ̃��f�����蓖��
	m_pObjectMng->ModelSetting();
}

//=====�f�X�g���N�^=====
SceneGame::~SceneGame()
{
	// ----- �f�[�^�����݂�����폜 -----
	SAFE_DELETE(m_pVS);
	SAFE_DELETE(g_pUI);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pObjectMng);
	SAFE_DELETE(m_pCollisionAreaMng);
	SAFE_DELETE(m_pCollision);
	SAFE_DELETE(m_pTimer);
	SAFE_DELETE(m_pCustomEquipment);
	for (int i = 0; i < MAX_TRADE; i++) {
		SAFE_DELETE(m_pTrade[i]);
	}
	SAFE_DELETE(m_pShopMenu);
	SAFE_DELETE(m_pShopText);
	SAFE_DELETE(m_pProgress);
	SAFE_DELETE(m_pCountDown);
	SAFE_DELETE(m_pEndUI);
	SAFE_DELETE(m_pShopBG);
	SAFE_DELETE(m_pPlayerText);
	SAFE_DELETE(m_pSkyModel);
	SAFE_DELETE(m_pSeaModel);
}

//=====�X�V����=====
void SceneGame::Update(float tick)
{
	// ----- �ϐ��錾 -----
	static int wait = 0;											// �T�C���J�[�u�v�Z�ҋ@�t���[��
	static float camRad = m_pPlayer->GetRadius();					// �J�����������a
	//static float camRad = CAM_RAD_BEFORE;
	static float camPosY = m_pPlayer->GetCameraPos().y;				// �J���������ʒuY
	static float horizon = START_HORIZON;							// ���s���W�A���ϊ��O
	float  horizonRad = DirectX::XMConvertToRadians(START_HORIZON);	// �J�������s�ʒu
	float  vertical = DirectX::XMConvertToRadians(START_VERTICAL);	// �J�����c�ʒu
	static float factor = 0.0f;										// �t���[���v�Z�p
	static float value = 0.0f;										// �T�C���J�[�u�l

	static int frame = 0;			// �t���[���p
	static int frame2 = 0;
	static bool flg = true;
	static bool zoomFlg = true;

	// ----- �J�������W�v�Z -----
	if (flg)
	{
		m_pPlayer->SetHorizon(horizon);
		m_pPlayer->SetCameraPosX(camRad * sin((float)vertical) * cos((float)horizonRad));
		m_pPlayer->SetCameraPosZ(camRad * sin((float)vertical) * sin((float)horizonRad));
		flg = false;
	}
	//// ----- �Y�[���C�� -----
	//if (frame2 < MAX_FRAME) frame2++;
	//factor = static_cast<float>(frame2) / static_cast<float>(MAX_FRAME);
	//value = factor * factor * (3.0f - 2.0f * factor);

	//// ----- �J�������s�ʒu�ϓ� -----
	//if (camRad > START_CAM_RAD && flg)
	//{
	//	camRad -= CAL_CAMERA * value;

	//	m_pPlayer->SetCamRadius(camRad);
	//}
	//else
	//{
	//	flg = false;
	//	m_pPlayer->SetCamRadius(START_CAM_RAD);
	//}

	// ----- ��]�Y�[���A�E�g -----
	if (wait > WAIT_FRAME && zoomFlg)
	{
		// ----- �T�C���J�[�u�v�Z -----
		if (frame < MAX_FRAME) frame++;
		else zoomFlg = false;
		factor = static_cast<float>(frame) / static_cast<float>(MAX_FRAME);
		value = factor * factor * (3.0f - 2.0f * factor);

		// ----- �J�������s�ʒu�ϓ� -----
		if (camRad < CAMERA_RAD)
		{
			camRad += CAL_CAMERA * value;

			m_pPlayer->SetCamRadius(camRad);
		}
		else m_pPlayer->SetCamRadius(CAMERA_RAD);

		// ----- �J������]�v�Z -----
		if (horizon < HORIZON)
		{
			horizon += CAL_CAMERA * value * ((HORIZON - START_HORIZON) / (CAMERA_RAD - START_CAM_RAD));
		}
		else horizon = HORIZON;

		horizonRad = DirectX::XMConvertToRadians(horizon);

		// ----- �J�������W�v�Z -----
		m_pPlayer->SetHorizon(horizon);
		m_pPlayer->SetCameraPosX(camRad * sin((float)vertical) * cos((float)horizonRad));
		m_pPlayer->SetCameraPosZ(camRad * sin((float)vertical) * sin((float)horizonRad));

		// ----- �J�����̍����ϓ� -----
		if (camPosY < CAMERA_POS_Y)
		{
			camPosY += (CAL_CAMERA * value * (CAMERA_POS_Y - START_CAM_POS_Y / (CAMERA_RAD - START_CAM_RAD)));
			m_pPlayer->SetCameraPosY(camPosY);
		}
		else m_pPlayer->SetCameraPosY(CAMERA_POS_Y);
	}
	else wait++;

	Sprite::SetColor(DirectX::XMFLOAT4( 1.0f, 1.0f, 1.0f, 1.0f));
	// =-=-= �Q�[���̏󋵂ɂ���ď����𕪊� =-=-=
	m_pCountDown->Update();
	// ----- �Q�[���J�n�O -----
	if (!m_start) {
		if (!m_count) {	// ��x��������
			m_pSoundMng->playSound(CSoundMng::TimeSE::countDown1);			// �J�E���g�_�E���Đ�
			m_pPlayer->Update();											// �J�����Ȃǂ𐳂����Z�b�g
			m_pCustomEquipment->SetCustom(m_pPlayer->GetCustom());			// �J�X�^����ԃZ�b�g
			m_count = true;
		}

		if (time < 2) {														// �^�C�}�[�𐳂����Z�b�g
			m_pTimer->Update();
			time++;
		}
		if (m_pSoundMng->CheckSoundEnd(CSoundMng::TimeSE::countDown1))		// �J�E���g�_�E�������񂾂�
		{
			Sleep(300);														// �����̂Œ���
			m_start = true;													// �Q�[���X�^�[�g
			m_pSoundMng->playSound(CSoundMng::BGM::game);					// BGM�Đ�
			m_pSoundMng->playSound(CSoundMng::TimeSE::countDown1_pi);		// �J�n���Đ�
		}

		return;	// �Q�[�����n�܂��ĂȂ��̂ňȉ����������Ȃ�(����q�h�~)
	}
	// ----- �ʏ�v���C��� -----
	if (!m_pPlayer->GetShop()) {
		m_pObjectMng->Update(tick);
		m_pCollision->Update();

		if (!m_pProgress->GetEndFlg()) {// ���U���g�Ɉڂ鎞�ɃI�u�W�F�N�g�ȊO�̏������~�߂�(�z�����ݎ��̊������c�����߃I�u�W�F�N�g�͏���)
			m_pPlayer->Update();

			m_pCollisionAreaMng->Update();
			for (int i = 0; i < MAX_TRADE; i++)
			{
				if (m_pTrade[i])
				{
					m_pTrade[i]->Update();	// ���l�X�V
				}
			}
			m_pCustomEquipment->SetCustom(m_pPlayer->GetCustom());	// �J�X�^����ԃZ�b�g

			m_pTimer->Update();
			m_pProgress->Update(m_pObjectMng->GetSuctionedObjNum(), m_pTimer->GetTime());
			m_pPlayerText->Update();
		}
	}
	// ----- �V���b�v��� -----
	else {
		
		m_pShopMenu->SetShopSuction(m_pPlayer->GetSuction());	// �z�����݃N���X�Z�b�g
		m_pShopMenu->SetMoney(m_pPlayer->GetMoney());			// �������Z�b�g
		m_pShopMenu->SetCustom(m_pPlayer->GetCustom());			// �J�X�^���Z�b�g
		m_pShopMenu->Update();									// �V���b�v���j���[�X�V
		m_pShopMenu->SetMoney(m_pPlayer->GetMoney());			// �������Z�b�g
		m_pPlayer->SetShop(m_pShopMenu->GetShop());				// �V���b�v��ʂ���邩
		m_pCustomEquipment->SetCustom(m_pPlayer->GetCustom());	// �J�X�^����Ԋm�F
	}

	// ----- �Q�[���I����`�J�ڑO -----
	if (m_pProgress->GetEndFlg()) {
		// �Q�[���I��SE�����񂾂�
		if (m_pSoundMng->CheckSoundEnd(CSoundMng::TimeSE::timeUp1) && m_pSoundMng->CheckSoundEnd(CSoundMng::TimeSE::timeUp2)) {
			m_pSceneMng->SetNextScene(CSceneMng::SceneKind::SCENE_RESULT);	// (��)���񂾂炷���J��
			// �����Q�[���I��UI�����\��
			m_pSoundMng->AllDeleteSpeaker();								// SE���Ƃ߂�
		}
		//�Q�[���I��UI
		m_pEndUI->Update(400.0f, 400.0f);
	}
}

//=====�`�揈��=====
void SceneGame::Draw()
{
	DirectX::XMFLOAT4X4 mat[3];

	mat[0] = m_pPlayer->GetWorldMatrix();
	mat[1] = m_pPlayer->GetViewMatrix();
	mat[2] = m_pPlayer->GetProjectionMatrix();

	Geometory::SetWorld(mat[0]);
	Geometory::SetView(mat[1]);
	Geometory::SetProjection(mat[2]);

	m_pVS->WriteBuffer(0, mat);

	DrawSky(mat, m_pVS);
	DrawSea(mat, m_pVS);

	RenderTarget* pRTV = GetDefaultRTV();
	DepthStencil* pDSV = GetDefaultDSV();
	SetRenderTargets(1, &pRTV, pDSV);

	//----- �I�u�W�F�N�g -----
	for (int i = 0; i < MAX_TRADE; i++)	{
		if (m_pTrade[i])		{
			m_pTrade[i]->Draw();
		}
	}

	m_pPlayer->Draw();
	m_pObjectMng->Draw(mat);

#if DEBUG	//** �G���A����m�F�p
	m_pCollisionAreaMng->Draw(mat);
#endif

	// ----- UI -----
	SetRenderTargets(1, &pRTV, nullptr);
	g_pUI->Draw();				// �����`��
	m_pTimer->Draw();			// ���ԕ`��
	m_pCustomEquipment->Draw();	// �����A�C�R���`��
	m_pProgress->Draw();		// �m���}�`��
	m_pCountDown->Draw();		// �J�E���g�_�E��
	m_pPlayerText->Draw();		// �v���C���[�����o��

	if (g_pUI->GetAdd())
	{
		g_pUI->DrawAdd();
		Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		
	}

	if (m_pPlayer->GetShop())	// �V���b�v��ʂȂ�`��
	{
		m_pShopBG->Draw();
		Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		m_pShopMenu->Draw();
		g_pUI->Draw();				// �����`��
		if (g_pUI->GetAdd())
		{
			g_pUI->DrawAdd();
			Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}

	//�Q�[���I��UI
	if (m_pProgress->GetEndFlg())
	{
		if (*m_pProgress->GetTime() <= 0)
		{
			m_pEndUI->DrawTimeUp();
		}
		else
		{
			m_pEndUI->DrawClear();
		}
	}
}

int * SceneGame::getMoney()
{
	return g_pUI->GetMoney();
}

int * SceneGame::getPer()
{
	return m_pProgress->GetProgressNum();
}

int * SceneGame::getTime()
{
	return m_pProgress->GetTime();
}

CUI * GetUI()
{
	return g_pUI;
}

// ========== �}�b�v���ǂݍ��� ==========
// ���@���F
// (int ���݂̃X�e�[�W��)
// list<Object*>*	obj���X�g�|�C���^
// ColArea*			CollisionArea���X�g�|�C���^
// CPlayer*			Player�|�C���^
// �߂�l�F�Ȃ�
// �`�֐��T�v�`
// �}�b�v��ǂݍ���Ńf�[�^���e�I�u�W�F�N�g�ɐݒ肷��
// ======================================
void SceneGame::LoadMap(/*enum crntStage, */list<Object*>* pObjList, list<CCollisionArea*>* pAreaList, CPlayer* pPlayer, CObjectMng* pObjMng)
{
	// =-=-= ���� =-=-=
	// ----- �ϐ��錾 -----
	string line;		// �s���Ƃ̕�����
	string cell;		// �Z�����Ƃ̕�����
	char ch;			// �ꕶ�����ǂݍ��ލۂ̕�����
	int comma = 0;		// �J���}�J�E���g
	int numLine = 0;	// �s�J�E���g
	int numColumn = 0;	// ��J�E���g
	int maxLine;		// �ő�s��
	int maxColumn;		// �ő��
	float halfWidth;	// �}�b�v�ő啝
	float halfHeight;	// �}�b�v�ő卂��
	int objKind;		// �I�u�W�F�N�g�̎��
	int height;			// �I�u�W�F�N�g�ݒu���鍂��(�n�ʁ`�i��)
	float x, y, z;		// ���S���W
	float sx, sy, sz;	// �X�P�[��
	int direct;			// ���ʕ����B�P�F���@�Q�F�E�@�R�F��O�@�S�F��
	int attr;			// ����
	int level;			// �I�u�W�F�N�g���x��

	int tradeNum = 0;	// ���l��ǂݍ��񂾉�
	int totalObjNum = 0;// �z�����߂�I�u�W�F�N�g�̑���

	// ----- �}�b�v�f�[�^�ǂݍ��� -----
	ifstream file("Assets/map/STAGEa.csv");
	if (!file.is_open()) {
		MessageBox(NULL, "Stage���ǂݍ��߂Ȃ�", "Error", MB_OK);
	}

	// =-=-= �I�u�W�F�N�g�f�[�^�ǂݍ��� =-=-=
	// ----- �S�̏��ǂݍ��� -----
	getline(file, cell, ',');								// �s���𕶎���Ƃ��Ď擾
	maxLine = stoi(cell);									// ������𐮐��ɕϊ����Ċi�[
	getline(file, cell, ',');	maxColumn = stoi(cell);		// ��
	getline(file, cell, ',');	halfWidth = stof(cell) / 2;	// �}�b�v�� / 2
	getline(file, cell, ',');	halfHeight = stof(cell) / 2;// �}�b�v���� / 2

	getline(file, cell);			// ���ݍs�̖����Ɉړ�

	// ----- �e�I�u�W�F�N�g�f�[�^�ǂݍ��� -----
	for (int i = 0; i < maxLine; i++)	// �S�Ă̍s��ǂݍ���
	{
		// ----- ���� -----
		getline(file, cell);		// ���ݍs�̖����Ɉړ�
		getline(file, cell, ',');	// ���̍s��2��ڂ�
		comma = 0;					// �O����
		while (comma != 2) {		// �f�[�^�ǂݍ��ݐ擪��܂ŃX�L�b�v
			file.get(ch);
			if (ch == ',') {
				++comma;
			}
		}

		// ----- �e��p�����[�^�ǂݍ��� -----
		getline(file, cell, ',');	objKind = stoi(cell);	// ���
		getline(file, cell, ',');	height = stoi(cell);	// ����
		getline(file, cell, ',');	x = stof(cell) * -1;	// ���S���W
		x += halfWidth;
		getline(file, cell, ',');	y = stof(cell);
		getline(file, cell, ',');	z = stof(cell);
		z -= halfHeight;
		getline(file, cell, ',');	sx = stof(cell);		// �X�P�[��
		getline(file, cell, ',');	sy = stof(cell);
		getline(file, cell, ',');	sz = stof(cell);
		getline(file, cell, ',');							// ���ʕ���
		if (!cell.empty()) {	// ��łȂ����
			direct = stoi(cell);
		}
		getline(file, cell, ',');							// ����
		if (!cell.empty()) {	// ��łȂ����
			attr = stoi(cell);
		}
		getline(file, cell, ',');							// �I�u�W�F�N�g���x��
		if (!cell.empty()) {	// ��łȂ����
			level = stoi(cell);
		}

		// ----- �I�u�W�F�N�g�ɐݒ� -----
		switch (objKind) {
		case 1:	// �v���C���[
			pPlayer->SetPos(DirectX::XMFLOAT3(x, y, z));
			break;
		case 2:		// ���l
			m_pTrade[tradeNum] = new CTrade(x, y, z, 90.0f * (direct - 1));
			m_pTrade[tradeNum]->SetPlayer(m_pPlayer);
			m_pCollision->SetTrade(m_pTrade[tradeNum]);
			tradeNum++;
			break;
		case 3:		// �}�b�g ���폜
			break;
		case 4:		// �Ŕ�
			pObjList->push_back(new CSignboard(x, y, z, sx, sy, sz));
			break;
		case 5:		// �C
			pAreaList->push_back(new CAreaSea(x, y, z, sx, sy, sz));
			break;
		case 6:		// �n��
			pAreaList->push_back(new CAreaGround(x, y, z, sx, sy, sz, attr));
			break;
		case 7:		// ����
			pAreaList->push_back(new CAreaHill(x, y, z, sx, sy, sz, attr));
			break;
		case 8:		// ��
			pAreaList->push_back(new CAreaSlope(x, y, z, sx, sy, sz, direct, attr));
			break;
		case 9:		// ��
			if (level == 2)
				pObjList->push_back(new CTreeSmall(x, y, z, sx, sy, sz, m_pSoundMng));
			else if (level == 3)
				pObjList->push_back(new CTree(x, y, z, sx, sy, sz, m_pSoundMng));
			break;
		case 10:	// ��
			if (level == 2) {
				pObjList->push_back(new CRockSmall(x, y, z, sx, sy, sz, m_pSoundMng));
			}
			else if (level == 3) {
				pObjList->push_back(new CRock(x, y, z, sx, sy, sz, m_pSoundMng));
			}
			break;
		case 11:	// ��
			//pObjList->push_back(new CHouse(x, y, z, sx, sy, sz,m_pSoundMng));
			break;
		case 12:	// �؍�
			pObjList->push_back(new CWood(x, y, z));
			break;
		case 13:	// ��
			pObjList->push_back(new CStone(x, y, z));
			break;
		case 14:	// �t�F���X
			pObjList->push_back(new CFence(x, y, z, sx, sy, sz, 90.0f * (direct - 1), m_pSoundMng));
			break;
		case 15:	// ���̂�
			if (level == 1)
				pObjList->push_back(new Mushroom(x, y, z, sx, sy, sz));
			else if (level == 2)
				pObjList->push_back(new MushroomMedium(x, y, z, sx, sy, sz));
			break;
		}
	}

	// ----- �z�����߂�I�u�W�F�N�g�̑������J�E���g -----
	for (Object* pObj : *pObjList) {
		if (pObj->GetCreateNum() == 0) {
			totalObjNum += 1;
		}
		else {
			totalObjNum += pObj->GetCreateNum();
		}
	}
	pObjMng->SetTotalObjNum(totalObjNum);	// ������n��
}

void SceneGame::DrawSky(DirectX::XMFLOAT4X4 * mat, VertexShader * vs)
{

	DirectX::XMMATRIX world;
	//---�ϊ��s����v�Z
	world = DirectX::XMMatrixScaling(1.0f, 0.2f, 1.0f) *
		DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);

	world = DirectX::XMMatrixTranspose(world);
	DirectX::XMStoreFloat4x4(&mat[0], world);

	//---�ϊ��s���ݒ�
	Geometory::SetWorld(mat[0]);
	Geometory::SetView(mat[1]);
	Geometory::SetProjection(mat[2]);

	RenderTarget* pRTV = GetDefaultRTV();
	DepthStencil* pDSV = GetDefaultDSV();
	SetRenderTargets(1, &pRTV, nullptr);

	//	m_pVertexShader = vs;
	vs->WriteBuffer(0, mat);
	m_pSkyModel->SetVertexShader(vs);
	m_pSkyModel->Draw();
}

void SceneGame::DrawSea(DirectX::XMFLOAT4X4 * mat, VertexShader * vs)
{

	DirectX::XMMATRIX world;
	//---�ϊ��s����v�Z
	world = DirectX::XMMatrixScaling(0.15f, 0.45f, 0.15f) *
		DirectX::XMMatrixTranslation(0.0f, -3.0f, 0.0f);

	world = DirectX::XMMatrixTranspose(world);
	DirectX::XMStoreFloat4x4(&mat[0], world);

	//---�ϊ��s���ݒ�
	Geometory::SetWorld(mat[0]);
	Geometory::SetView(mat[1]);
	Geometory::SetProjection(mat[2]);

	RenderTarget* pRTV = GetDefaultRTV();
	DepthStencil* pDSV = GetDefaultDSV();
	SetRenderTargets(1, &pRTV, nullptr);

	//	m_pVertexShader = vs;
	vs->WriteBuffer(0, mat);
	m_pSeaModel->SetVertexShader(vs);
	m_pSeaModel->Draw();
}