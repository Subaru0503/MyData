//CSceneStage2.cpp
//=====�C���N���[�h��=====
#include "SceneStage2.h"
#include "Geometory.h"
#include "Defines.h"
#include "Input.h"
#include "ShaderList.h"
#include "BlueMushroomNemoto.h"
// ----- �}�b�v�ǂݍ��� -----
#include <fstream>
#include <sstream>
#include <string>

//=====�O���[�o���錾=====

//=====�R���X�g���N�^=====
CSceneStage2::CSceneStage2(CSceneMng* pSceneMng, CSoundMng* pSoundMng)
	: CSceneStageBase(pSceneMng, pSoundMng)
{
	m_pShopMenu = new CShopMenu(2, m_pUI, m_pSoundMng);
	m_pTimer = new CTimer(210);
	// �}�b�v�ǂݍ���
	LoadMap(m_pObjectMng->GetObjectList(), m_pCollisionAreaMng->GetAreaList(), m_pPlayer, m_pObjectMng);
	m_pProgress = new CProgress(m_pObjectMng->GetTotalObjNum(), m_pSoundMng);
	m_pCollision->SetTrade(m_pTrade);
	m_pCollisionAreaMng->SetObjList(m_pObjectMng->GetObjectList());
	m_pCollision->SetTradeIcon(m_pTradeIcon);
	// �I�u�W�F�N�g�ւ̃��f�����蓖��
	m_pObjectMng->ModelSetting();
	// �I�u�W�F�N�g�}�l�[�W���[�Ƀv���C���[�����Z�b�g
	m_pObjectMng->SetPlayer(m_pPlayer);
	m_pObjectMng->Update(0.0f);		// �I�u�W�F�N�g�̍����𒲐����邽�߈�x����

	// ----- �X�e�[�W���f���ǂݍ��� -----
	m_pStageModel[0] = new Model;	// ��
	if (!m_pStageModel[0]->Load("Assets/Model/Stage/Sky/Sky.fbx", 1.0f, Model::Flip::XFlip)) {
		MessageBox(NULL, "Assets/map/Stage/sky/sky.fbx", "Error", MB_OK);
	}
	m_pStageModel[1] = new Model;	// �C
	if (!m_pStageModel[1]->Load("Assets/Model/Stage/Sea/Sea.fbx", 1.0f, Model::Flip::XFlip)) {
		MessageBox(NULL, "Assets/map/Stage/Sea.fbx", "Error", MB_OK);
	}
	m_pStageModel[2] = new Model;	// ��
	if (!m_pStageModel[2]->Load("Assets/Model/Stage/Stage2/Stage.fbx", 1.0f, Model::Flip::ZFlip)) {
		MessageBox(NULL, "Assets/Model/Stage/Stage/stage2/Stage2.fbx", "Error", MB_OK);
	}
	//m_pStageModel[1]->SetPixelShader(ShaderList::GetPS(ShaderList::PS_FOG));
	m_pStageModel[2]->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_pPlayer->SetShopCustom(m_pShopMenu->GetShopCustom());
}

//=====�f�X�g���N�^=====
CSceneStage2::~CSceneStage2()
{
	//ShaderList::Uninit();
	for (int i = 0; i < 3; i++)
	{
		SAFE_DELETE(m_pStageModel[i]);
	}
}


//=====�X�V����=====
void CSceneStage2::Update(float tick)
{
#if DEBUG_KEY
	// ----- �����V�[���J�� -----
	if (IsKeyTrigger('R'))	m_pSceneMng->SetNextScene(CSceneMng::SceneKind::SCENE_RESULT);
	else if (IsKeyTrigger('C')) {
		m_pProgress->SetClear();
		m_pSceneMng->SetNextScene(CSceneMng::SceneKind::SCENE_RESULT);
		return;
	}

	// ----- �������₵ -----
	if (IsKeyTrigger('Q')) {
		m_pUI->AddMoney(50000);
		m_pPlayer->SetMoney(50000);
	}
#endif

	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	// ===== �Q�[���̏󋵂ɂ���ď����𕪊� =====
	m_pCountDown->Update();
	// =-=-= �Q�[���J�n�O =-=-=
	if (!m_start) {
		if (!m_count) {	// ��x��������
			m_pSoundMng->playSound(CSoundMng::TimeSE::countDown1);			// �J�E���g�_�E���Đ�
			m_pPlayer->Update(tick);											// �J�����Ȃǂ𐳂����Z�b�g
			m_pCustomEquipment->SetCustom(m_pPlayer->GetCustom());			// �J�X�^����ԃZ�b�g
			m_count = true;
		}
		if (time < 2) {														// �^�C�}�[�𐳂����Z�b�g
			m_pTimer->Update();
			time++;
		}

		// ----- �J�n�J�������[�N -----
		StartCameraWork();

		if (m_pSoundMng->CheckSoundEnd(CSoundMng::TimeSE::countDown1))		// �J�E���g�_�E�������񂾂�
		{
			Sleep(300);														// �����̂Œ���
			m_start = true;													// �Q�[���X�^�[�g
			m_pSoundMng->playSound(CSoundMng::BGM::game2);					// BGM�Đ�
			m_pSoundMng->playSound(CSoundMng::TimeSE::countDown1_pi);		// �J�n���Đ�
		}

		return;	// �Q�[�����n�܂��ĂȂ��̂ňȉ����������Ȃ�(����q�h�~)
	}
	// =-=-= �|�[�Y��� =-=-=
	XINPUT_STATE state;
	XInputGetState(0, &state);

	if (m_pause) {
		XINPUT_KEYSTROKE stroke;
		XInputGetKeystroke(0, 0, &stroke);
		if ((state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
			(state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
		{
			state.Gamepad.sThumbLX = 0;
			state.Gamepad.sThumbLY = 0;
		}
		LibEffekseer::GetManager().Get()->StopAllEffects();
		// ----- ���j���[�I�� -----
		if ((IsKeyTrigger('W') || IsKeyTrigger(VK_UP))
			|| (state.dwPacketNumber != 3435973836 && state.Gamepad.sThumbLY > 0 &&
				state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
				state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && stroke.Flags == 0x0001
				|| state.Gamepad.wButtons&XINPUT_GAMEPAD_DPAD_UP&&stroke.Flags == 0x0001) && (m_pauseSelect > 0)) {			// ��ړ�
			m_pauseSelect--;
			if (m_pauseSelect < 0)
			{
				m_pauseSelect = 0;
			}
			m_pSoundMng->playSound(CSoundMng::SystemSE::select);
		}
		else if ((IsKeyTrigger('S') || IsKeyTrigger(VK_DOWN)) ||
			(state.dwPacketNumber != 3435973836 && state.Gamepad.sThumbLY < 0 &&
				state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
				state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && stroke.Flags == 0x0001
				|| state.Gamepad.wButtons&XINPUT_GAMEPAD_DPAD_DOWN&&stroke.Flags == 0x0001) && (m_pauseSelect < MAX_PAUSEMENU - 1)) {	// ���ړ�
			m_pauseSelect++;
			if (m_pauseSelect > 2)
			{
				m_pauseSelect = 2;
			}
			m_pSoundMng->playSound(CSoundMng::SystemSE::select);
		}
		m_pPause->Update(m_pauseSelect);

		// ----- ���� -----
		if (IsKeyTrigger(VK_RETURN) || IsKeyTrigger(VK_SPACE)
			|| state.Gamepad.wButtons&XINPUT_GAMEPAD_A&&stroke.Flags == 0x0001) {
			switch (m_pauseSelect)
			{
			case 0:	// �߂�
				m_pause = false;
				m_pSoundMng->playSound(CSoundMng::SystemSE::decision);
				break;
			case 1:	// ���X�^�[�g
				m_pSoundMng->playSound(CSoundMng::SystemSE::decision);
				m_pSceneMng->GameRestart();
				break;
			case 2:	// �Z���N�g��
				m_pSoundMng->playSound(CSoundMng::SystemSE::decision);
				m_pSceneMng->SetNextScene(CSceneMng::SceneKind::SCENE_SELECT);
				break;
			}
		}

		return;	// �ȉ����������Ȃ�
	}
	// =-=-= �ʏ�v���C��� =-=-=
	if (!m_pPlayer->GetShop()) {
		m_pObjectMng->Update(tick);
		m_pCollision->Update();
		m_pCollisionAreaMng->Update();
		m_pDust->Update();

		if (!m_pProgress->GetEndFlg()) {// ���U���g�Ɉڂ鎞�ɃI�u�W�F�N�g�ȊO�̏������~�߂�(�z�����ݎ��̊������c�����߃I�u�W�F�N�g�͏���)
			m_pPlayer->Update(tick);

			m_pCollisionAreaMng->Update();
			for (auto pTrade : m_pTrade) {
				if (pTrade) {
					pTrade->Update(tick);	// ���l�X�V
				}
			}
			m_pCustomEquipment->SetCustom(m_pPlayer->GetCustom());	// �J�X�^����ԃZ�b�g

			m_pTimer->Update();
			m_pProgress->Update(m_pObjectMng->GetSuctionedObjNum(), m_pTimer->GetTime(), m_pTimer->GetMaxTime());
			m_pPlayerText->Update();

			// �|�[�Y��ʊJ������
			if (IsKeyTrigger(VK_ESCAPE) || state.Gamepad.wButtons&XINPUT_GAMEPAD_START)	m_pause = true;
		}
	}
	// =-=-= �V���b�v��� =-=-=
	else {

		m_pShopMenu->SetShopSuction(m_pPlayer->GetSuction());	// �z�����݃N���X�Z�b�g
		m_pShopMenu->SetMoney(m_pPlayer->GetMoney());			// �������Z�b�g
		m_pShopMenu->SetCustom(m_pPlayer->GetCustom());			// �J�X�^���Z�b�g
		m_pShopMenu->Update(tick);									// �V���b�v���j���[�X�V
		m_pShopMenu->SetMoney(m_pPlayer->GetMoney());			// �������Z�b�g
		m_pPlayer->SetShop(m_pShopMenu->GetShop());				// �V���b�v��ʂ���邩
		m_pCustomEquipment->SetCustom(m_pPlayer->GetCustom());	// �J�X�^����Ԋm�F
	}

	// =-=-= �Q�[���I����`�J�ڑO =-=-=
	if (m_pProgress->GetEndFlg()) {
		// �Q�[���I��SE�����񂾂�
		if (m_pSoundMng->CheckSoundEnd(CSoundMng::TimeSE::timeUp1) && m_pSoundMng->CheckSoundEnd(CSoundMng::TimeSE::timeUp2)) {
			m_pSceneMng->SetNextScene(CSceneMng::SceneKind::SCENE_RESULT);	// (��)���񂾂炷���J��
			m_pSoundMng->AllDeleteSpeaker();								// SE���Ƃ߂�
		}
		//�Q�[���I��UI
		m_pEndUI->Update(400.0f, 400.0f);
		LibEffekseer::GetManager().Get()->StopAllEffects();
	}
}

//=====�`�揈��=====
void CSceneStage2::Draw()
{
	DirectX::XMFLOAT4X4 mat[3];

	mat[0] = m_pPlayer->GetWorldMatrix();
	mat[1] = m_pPlayer->GetViewMatrix();
	mat[2] = m_pPlayer->GetProjectionMatrix();

	m_pVS->WriteBuffer(0, mat);
	RenderTarget* pRTV = GetDefaultRTV();
	DepthStencil* pDSV = GetDefaultDSV();
	SetRenderTargets(1, &pRTV, pDSV);

	// ----- �X�e�[�W -----
	DrawStage(mat, m_pVS);	// ���E�C�E��

	//----- �I�u�W�F�N�g -----
	m_pPlayer->Draw();
	for (auto pTrade : m_pTrade) {
		if (pTrade) {
			pTrade->Draw();	// ���l�X�V
		}
	}
	m_pObjectMng->Draw(mat);

#if DEBUG	//** �G���A����m�F�p
	Geometory::SetWorld(mat[0]);
	Geometory::SetView(mat[1]);
	Geometory::SetProjection(mat[2]);

	m_pCollisionAreaMng->Draw(mat);
#endif

	SetRenderTargets(1, &pRTV, nullptr);

	// ----- UI -----
	m_pUI->Draw();				// �����`��
	m_pTimer->Draw();			// ���ԕ`��
	m_pCustomEquipment->Draw();	// �����A�C�R���`��
	m_pProgress->Draw();		// �m���}�`��
	m_pCountDown->Draw();		// �J�E���g�_�E��
	m_pPlayerText->Draw();		// �v���C���[�����o��

	//���lUI
	if (m_pPlayer->GetTrade())
	{
		m_pTradeIcon->Draw();
	}

	// -----�G�t�F�N�g-----
	m_pDust->Draw();
	m_pLeaf->Draw();
	m_pEBag->Draw();
	if (m_pUI->GetAdd())
	{
		m_pUI->DrawAdd();
		Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	}

	if (m_pPlayer->GetShop())	// �V���b�v��ʂȂ�`��
	{
		m_pShopBG->Draw();
		Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		m_pShopMenu->Draw();
		m_pUI->Draw();				// �����`��
		if (m_pUI->GetAdd())
		{
			m_pUI->DrawAdd();
			Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}

	//�|�[�Y���
	if (m_pause)
	{
		m_pPause->Draw();
	}

	//�Q�[���I��UI	if (m_pProgress->GetEndFlg())
	{
		if (m_pProgress->GetProgressNum() >= 100)
		{
			m_pEndUI->DrawClear();
			
		}
		else
		{
			m_pEndUI->DrawTimeUp();
		}
	}
}

void CSceneStage2::DrawStage(DirectX::XMFLOAT4X4 *mat, VertexShader* vs)
{
	DirectX::XMMATRIX world;
	RenderTarget* pRTV = GetDefaultRTV();
	DepthStencil* pDSV = GetDefaultDSV();

	SetRenderTargets(1, &pRTV, nullptr);

	for (int i = 0; i < 3; i++)
	{
		switch (i)
		{
		case 0:	// ��
			world = DirectX::XMMatrixTranspose(DirectX::XMMatrixScaling(0.05f, 0.02f, 0.05f));
			break;
		case 1:	// �C
			//SetRenderTargets(1, &pRTV, pDSV);
			world = DirectX::XMMatrixTranspose(DirectX::XMMatrixScaling(0.1f, 0.15f, 0.1f) *
				DirectX::XMMatrixTranslation(0.0f, -1.0f, 0.0f));
			break;
		case 2:	// ��
			SetRenderTargets(1, &pRTV, pDSV);

			//---�ϊ��s����v�Z
			world = DirectX::XMMatrixTranspose(DirectX::XMMatrixScaling(0.57, 1.0, 0.63)*
				DirectX::XMMatrixTranslation(0.0f, -2.13f, 0.0f));
			break;
		}

		DirectX::XMStoreFloat4x4(&mat[0], world);

		//---�ϊ��s���ݒ�
		vs->WriteBuffer(0, mat);
		m_pStageModel[i]->SetVertexShader(vs);
		m_pStageModel[i]->Draw();
	}

}

// ========== �}�b�v���ǂݍ��� ==========
// ���@���F
// (int ���݂̃X�e�[�W��)
// list<Object*>*	obj���X�g�|�C���^
// ColArea*			CollisionArea���X�g�|�C���^
// CPlayer*			Player�|�C���^
// �߂�l�F�Ȃ�
// �`�֐��T�v�`
// �}�b�v2��ǂݍ���Ńf�[�^���e�I�u�W�F�N�g�ɐݒ肷��
// ======================================
void CSceneStage2::LoadMap(list<Object*>* pObjList, list<CCollisionArea*>* pAreaList, CPlayer* pPlayer, CObjectMng* pObjMng)
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
	ifstream file("Assets/map/STAGE2.csv");
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
			switch (height) {
			case 0: y = STAGE2_HT0;	break;
			case 1: y = STAGE2_HT1;	break;
			case 2: y = STAGE2_HT2;	break;
			}
			pPlayer->SetPos(DirectX::XMFLOAT3(x, y, z));
			pPlayer->SetRandHeight(y);
			break;
		case 2:		// ���l
			switch (height)	{
			case 0: y = STAGE2_HT0;	break;
			case 1: y = STAGE2_HT1;	break;
			case 2: y = STAGE2_HT2;	break;
			}
			m_pTrade.push_back(new CTrade(x, y, z, 90.0f * (direct - 1)));
			m_pTrade[tradeNum]->SetPlayer(m_pPlayer);
			m_pTradeIcon->SetPlayer(m_pPlayer);
			tradeNum++;
			break;
		case 3:		// �}�b�g ���폜
			break;
		case 4:		// �Ŕ�
			pObjList->push_back(new CSignboard(x, y, z, sx, sy, sz, 90.0f * (direct - 1)));
			break;
		case 5:		// �C
			pAreaList->push_back(new CAreaSea(x, y, z, sx, sy, sz));
			break;
		case 6:		// �n��
			pAreaList->push_back(new CAreaGround(x, y, z, sx, sy, sz, attr));
			break;
		case 7:		// ����
			pAreaList->push_back(new CAreaHill(x, y, z, sx, sy, sz, attr, 2));
			break;
		case 8:		// ��
			pAreaList->push_front(new CAreaSlope(height, x, y, z, sx, sy, sz, direct, attr, 2));
			break;
		case 9:		// ��
			pObjList->push_back(new CTree(x, y - 0.2f, z, sx, sy - 0.4f, sz, level));
			break;
		case 10:	// ��
			pObjList->push_back(new CRock(x, y, z, sx, sy, sz, level));
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
			pObjList->push_back(new CFence(x, y, z, sx, sy, sz, 90.0f * (direct - 1), level));
			break;
		case 15:	// ���̂�
			pObjList->push_back(new Mushroom(x, y, z, sx, sy, sz, level));
			break;
		case 16:	// �������̂��M�~�b�N
			pObjList->push_back(new BlueMushroom(x, y, z, sx, sy, sz));
			// ���{�̍��W�Z�b�g
			for (int i = 0; i < 5; i++)
			{
				pObjList->push_back(new BlueMushroomNemoto(x, y - 0.8f, z, 1.0f, 1.0f, 1.0f));
			}
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

void CSceneStage2::StartCameraWork()
{
	if (m_flg)
	{
		// ----- �ϐ��錾 -----
		m_wait = 0;													// �J�[�u�v�Z�ҋ@�t���[��
		m_camRad = m_pPlayer->GetRadius();							// �J�����������a
		//m_camRad = CAM_RAD_BEFORE;
		m_camPosY = m_pPlayer->GetCameraPos().y;					// �J���������ʒuY
		m_horizon = START_HORIZON;									// ���s���W�A���ϊ��O
		m_horizonRad = DirectX::XMConvertToRadians(START_HORIZON);	// �J�������s�ʒu
		m_vertical = DirectX::XMConvertToRadians(START_VERTICAL);	// �J�����c�ʒu
		m_factor = 0.0f;											// �t���[���v�Z�p
		m_value = 0.0f;												// �J�[�u�l

		m_frame = 0;			// �t���[���p
		m_flg = true;
		m_zoomFlg = true;

		// ----- �J�������W�v�Z -----

		m_pPlayer->SetHorizon(m_horizon);
		m_pPlayer->SetCameraPosX(m_camRad * sin((float)m_vertical) * cos((float)m_horizonRad));
		m_pPlayer->SetCameraPosZ(m_camRad * sin((float)m_vertical) * sin((float)m_horizonRad));
		m_flg = false;
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
	if (m_wait > WAIT_FRAME && m_zoomFlg)
	{
		// ----- �J�[�u�v�Z -----
		if (m_frame < MAX_FRAME) m_frame++;
		else m_zoomFlg = false;
		m_factor = static_cast<float>(m_frame) / static_cast<float>(MAX_FRAME);
		m_value = m_factor * m_factor * (3.0f - 2.0f * m_factor);

		// ----- �J�������s�ʒu�ϓ� -----
		if (m_camRad < CAMERA_RAD)
		{
			m_camRad += CAL_CAMERA * m_value;

			m_pPlayer->SetCamRadius(m_camRad);
		}
		else m_pPlayer->SetCamRadius(CAMERA_RAD);

		// ----- �J������]�v�Z -----
		if (m_horizon < HORIZON)
		{
			m_horizon += CAL_CAMERA * m_value * ((HORIZON - START_HORIZON) / (CAMERA_RAD - START_CAM_RAD));
		}
		else m_horizon = HORIZON;

		m_horizonRad = DirectX::XMConvertToRadians(m_horizon);

		// ----- �J�������W�v�Z -----
		m_pPlayer->SetHorizon(m_horizon);
		m_pPlayer->SetCameraPosX(m_camRad * sin((float)m_vertical) * cos((float)m_horizonRad));
		m_pPlayer->SetCameraPosZ(m_camRad * sin((float)m_vertical) * sin((float)m_horizonRad));

		// ----- �J�����̍����ϓ� -----
		if (m_camPosY < CAMERA_POS_Y)
		{
			m_camPosY += (CAL_CAMERA * m_value * (CAMERA_POS_Y - START_CAM_POS_Y / (CAMERA_RAD - START_CAM_RAD)));
			m_pPlayer->SetCameraPosY(m_camPosY);
		}
		else m_pPlayer->SetCameraPosY(CAMERA_POS_Y);
	}
	else m_wait++;
}