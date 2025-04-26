//=================================================================
//
//	SceneSelect.cpp
//	�X�e�[�W�I���V�[��
//
//=================================================================

// ========== �C���N���[�h�� ==========
#include "SceneSelect.h"
#include "MushroomPlanet.h"
#include "GreenPlanet.h"
#include "WholeCakePlanet.h"
#include "Input.h"
#include "XController.h"
#include "Value.h"

#define DRAW_UI_FRAME	(240)	//�u�V�����˗��vUI�\���t���[���i�����͉��j


CSceneSelect::CSceneSelect(CSceneMng* pSceneMng, CSoundMng* pSoundMng, Fade* pFade, int OldPlayStage)
	: m_pSceneMng(pSceneMng)
	, m_pSoundMng(pSoundMng)
	, m_pFade(pFade)
	, m_bShop(false)
	, m_camMove(false)
	, m_select(OldPlayStage)
	, m_openFrame(0)
	, m_nItem{ 0 }
	, m_nMoney(0)
	, m_openStage(false)
	, m_openUI(false)
	, m_sceneSwap(false)
{
	// ----- ���_�V�F�[�_�[�ǂݍ��� -----
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}

	m_pCamera = new CCameraSelect();
	

	m_pSelect = new Select();
	m_pShopBG = new ShopBG();
	m_pScore = new SelectScore();
	m_pMoney = new CUI(m_pSceneMng->GetMoney());
	m_pShopMenu = new CShopMenu(0, m_pMoney, m_pSoundMng);
	m_nMoney = m_pSceneMng->GetMoney();

	m_pPlanets[CSceneMng::SceneKind::SCENE_STAGE1] = new GreenPlanet();		// �X�e�[�W�P�̘f���ǉ�
	m_pPlanets[CSceneMng::SceneKind::SCENE_STAGE2] = new MushroomPlanet();	// ���̂��f���ǉ�
	m_pPlanets[CSceneMng::SceneKind::SCENE_STAGE3] = new WholeCakePlanet();	// �z�[���P�[�L�A�C�����h�ǉ�
	m_pPlanets[OldPlayStage]->StartFocus();		// �I�𒆂̘f�������]

	m_pCamera->SetGreen(m_pPlanets[CSceneMng::SceneKind::SCENE_STAGE1]);
	m_pCamera->SetMushroom(m_pPlanets[CSceneMng::SceneKind::SCENE_STAGE2]);
	m_pCamera->SetWholeCake(m_pPlanets[CSceneMng::SceneKind::SCENE_STAGE3]);
	
	m_openStage = m_pSceneMng->GetOpenStage();								// �X�e�[�W�J���������ǂ������擾
	m_pCamera->Init(m_select);

	m_pSelectModel = new Model;	// �F��
	if (!m_pSelectModel->Load("Assets/Model/Univers/Univers.fbx", 1.0f, Model::Flip::XFlip)) {
		MessageBox(NULL, "Assets/Model/Univers/Univers.fbx", "Error", MB_OK);
	}
}

CSceneSelect::~CSceneSelect()
{
	SAFE_DELETE(m_pShopMenu);
	SAFE_DELETE(m_pSelect);
	SAFE_DELETE(m_pShopBG);
	SAFE_DELETE(m_pScore);
	for (int i = 0; i < CSceneMng::MAX_STAGE; ++i)
	{
		SAFE_DELETE(m_pPlanets[i]);
	}
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pMoney);
	SAFE_DELETE(m_pSelectModel);
	SAFE_DELETE(m_pVS);
}

void CSceneSelect::Update(float tick)
{
	// =-=-= �X�V =-=-=
	for (int i = 0; i < CSceneMng::MAX_STAGE; ++i)		// �f���X�V����
	{
		m_pPlanets[i]->Update(tick);
	}
	m_pCamera->Update();
	
	// ===== �f���J����� =====
	if (m_openStage) {		// �����
		// ----- �J�����ړ��O -----
		if (!m_camMove) {
			m_camMove = true;
			m_select++;
			m_pPlanets[m_select]->StartFocus();	// ���]�n��
			m_pCamera->SetMoveRight(m_select);			// �J�����ړ��������Z�b�g(�E)
		}
		// ----- �J�����ړ��� -----
		if (!m_pCamera->GetMove()) {	
			m_openUI = true;			// �u�V�����˗��vUI�\��
			m_pSelect->UpdateNewRequest();
			if (m_openFrame > DRAW_UI_FRAME) {	// ��莞�Ԍo�߂�����
				m_openStage = false;	// �f���J�����o���I������
				m_openUI = false;		// UI��\��
			}
			m_openFrame++;				// �t���[���J�E���g
		}
		return; // �ȉ����������Ȃ�
	}

	// ===== �V���b�v��� =====
	if (m_bShop) {
		//----����----
		m_pShopMenu->SetItem(m_nItem);							// �A�C�e���g�p�i�[�ϐ��Z�b�g
		m_pShopMenu->SetMoney(&m_nMoney);						// �������Z�b�g
		
		//----�X�V����----
		m_pShopMenu->Update(tick);					// �V���b�v���j���[�X�V
		m_bShop = m_pShopMenu->GetShop();		// �V���b�v����邩

		return;	// �ȉ����������Ȃ��i����q�h�~�j
	}

	// ===== �f���I����� =====
	// =-=-= �L�[���� =-=-=
	XINPUT_STATE state;
	XInputGetState(0, &state);		
	if ((state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
			(state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
		{
			state.Gamepad.sThumbLX = 0;
			state.Gamepad.sThumbLY = 0;
		}
	// ----- �f���؂�ւ� -----
	if (!m_pCamera->GetMove()) {

#if DEBUG_KEY	// �X�e�[�W���ړ�
		if (IsKeyTrigger('1')) m_pSceneMng->SetNextScene(CSceneMng::SCENE_STAGE1);
		else if (IsKeyTrigger('2')) m_pSceneMng->SetNextScene(CSceneMng::SCENE_STAGE2);
		else if (IsKeyTrigger('3')) m_pSceneMng->SetNextScene(CSceneMng::SCENE_STAGE3);
#endif // !DEBUG
		XINPUT_KEYSTROKE stroke;
		XInputGetKeystroke(0, 0, &stroke);
		if (state.dwPacketNumber != 3435973836)
		{
			if (state.Gamepad.sThumbLX < 0 &&
				state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
				state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
				|| state.Gamepad.wButtons&XINPUT_GAMEPAD_DPAD_LEFT)
			{
				StageSawpLeft();
			}
			else if (state.Gamepad.sThumbLX > 0 &&
				state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
				state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
				|| state.Gamepad.wButtons&XINPUT_GAMEPAD_DPAD_RIGHT)	// �E�ړ�
			{
				StageSawpRight();
			}
			// ----- �f������ -----
			else if (state.Gamepad.wButtons&XINPUT_GAMEPAD_A) {
				if (m_select <= m_pSceneMng->GetOpenStageNum() && !m_sceneSwap && !m_pFade->IsPlay()) {	// ����ς݂����񂩂t�F�[�h���łȂ����
					m_sceneSwap = true;
					m_pSceneMng->SetNextScene((CSceneMng::SceneKind)m_select);	// �I�𒆂̘f���X�e�[�W�V�[���֑J��
					if (m_pSoundMng->CheckSoundEnd(CSoundMng::SystemSE::decision)) {
						m_pSoundMng->playSound(CSoundMng::SystemSE::decision);
					}
				}
			}
			else if (state.Gamepad.wButtons&XINPUT_GAMEPAD_Y) {
				m_bShop = true;
			}
			// ----- �߂�{�^�� -----
			else if (state.Gamepad.wButtons&XINPUT_GAMEPAD_B&&stroke.Flags==0x0001) {
				m_pSceneMng->SetNextScene(CSceneMng::SCENE_TITLE); // �^�C�g���֑J��
				if (m_pSoundMng->CheckSoundEnd(CSoundMng::SystemSE::cancel))
					m_pSoundMng->playSound(CSoundMng::SystemSE::cancel);//se

			}
		}
		if ((IsKeyTrigger('A') || IsKeyTrigger(VK_LEFT)))	// ���ړ�
		{
			StageSawpLeft();
		}
		else if ((IsKeyTrigger('D') || IsKeyTrigger(VK_RIGHT)))	// �E�ړ�
		{
			StageSawpRight();
		}
		// ----- �f������ -----
		else if (IsKeyTrigger(VK_RETURN) || IsKeyTrigger(VK_SPACE)) {
			if (m_select <= m_pSceneMng->GetOpenStageNum() && !m_sceneSwap && !m_pFade->IsPlay()) {	// ����ς݂����񂩂t�F�[�h���łȂ����
				m_sceneSwap = true;
				m_pSceneMng->SetNextScene((CSceneMng::SceneKind)m_select);	// �I�𒆂̘f���X�e�[�W�V�[���֑J��
				m_pSoundMng->playSound(CSoundMng::SystemSE::decision);
			}
		}
		// ----- �V���b�v�J�� -----
		else if (IsKeyTrigger('E')) {
			m_bShop = true;
		}
		// ----- �߂�{�^�� -----
		else if (IsKeyTrigger(VK_ESCAPE)) {
			m_pSceneMng->SetNextScene(CSceneMng::SCENE_TITLE); // �^�C�g���֑J��
			if(m_pSoundMng->CheckSoundEnd(CSoundMng::SystemSE::cancel))
			m_pSoundMng->playSound(CSoundMng::SystemSE::cancel);//se
		}
	}

	m_pSelect->Update(m_select);
	m_pScore->Update(m_pSceneMng->GetScore(), m_pSceneMng->GetClearTime(), m_select);
	m_pSoundMng->StopSound(CSoundMng::SystemSE::Fpon);
}

void CSceneSelect::Draw()
{
	//=====�f���`��=====
	DirectX::XMFLOAT4X4 mat[3];	// �ϊ��s��i�[�ꏊ

	// ----- �e��s��ݒ� -----
	mat[1] = m_pCamera->GetViewMatrix();
	mat[2] = m_pCamera->GetProjectionMatrix();

	m_pVS->WriteBuffer(0, mat);
	RenderTarget* ModelpRTV = GetDefaultRTV();
	DepthStencil* ModelpDSV = GetDefaultDSV();
	SetRenderTargets(1, &ModelpRTV, ModelpDSV);

	// ----- �X�e�[�W -----
	DrawSelect(mat, m_pVS);	// �F��

	// �f���`�揈��
	for (int i = 0; i < CSceneMng::MAX_STAGE; ++i)
	{
		m_pPlanets[i]->Draw(mat);
	}

	RenderTarget* pRTV = GetDefaultRTV();
	DepthStencil* pDSV = GetDefaultDSV();
	SetRenderTargets(1, &pRTV, nullptr);

	// ===== �˗��� =====
	if (!m_pCamera->GetMove()) {	// �J�����ړ����͔�\��
		m_pSelect->Draw();
		m_pScore->Draw();
	}

	// ===== �u�V�����˗����`�vUI =====
	if (m_openUI) {					// ����̃^�C�~���O�̂ݕ\��
		m_pSelect->DrawNewRequest();
	}

	// ===== �V���b�v =====
	if (m_bShop)
	{
		m_pShopBG->Draw();
		m_pShopMenu->Draw();
		m_pMoney->Draw();
	}
}

void CSceneSelect::DrawSelect(DirectX::XMFLOAT4X4 * mat, VertexShader * vs)
{
	DirectX::XMMATRIX world;
	RenderTarget* pRTV = GetDefaultRTV();
	DepthStencil* pDSV = GetDefaultDSV();

	SetRenderTargets(1, &pRTV, nullptr);

	world = DirectX::XMMatrixTranspose(DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f));

	DirectX::XMStoreFloat4x4(&mat[0], world);

	//---�ϊ��s���ݒ�
	vs->WriteBuffer(0, mat);
	m_pSelectModel->SetVertexShader(vs);
	m_pSelectModel->Draw();

}

int * CSceneSelect::GetItem()			// �A�C�e���g�p���Q�b�g
{
	return m_nItem;
}

Planet * CSceneSelect::GetPlanet(int num)
{
	return m_pPlanets[num];
}

void CSceneSelect::StageSawpLeft()
{
	// ----- ����ς݂��`�F�b�N -----
	int CheckSelect = m_select;		// ��Ɨp�ϐ��ɂ���

	CheckSelect--;
	if (CheckSelect < CSceneMng::SCENE_STAGE1) {			// �I��͈͂𒴂��Ă�����␳
		CheckSelect = CSceneMng::MAX_STAGE - 1;
	}
	if (CheckSelect > m_pSceneMng->GetOpenStageNum()) {
		return;												// �J�����Ă��Ȃ���΃J�����ړ����Ȃ�
	}

	// ----- �l�X�V -----
	m_pPlanets[m_select]->EndFocus();	// ���]�~��
	m_select--;

	if (m_select < CSceneMng::SCENE_STAGE1) {		// �I��͈͂𒴂��Ă�����␳
		m_select = CSceneMng::MAX_STAGE - 1;
	}

	// ----- �J�����ړ� -----
	m_pPlanets[m_select]->StartFocus();	// ���]�n��
	m_pCamera->SetMoveLeft(m_select);

	//SE
	if (m_pSoundMng->CheckSoundEnd(CSoundMng::SystemSE::swap))
	{
		m_pSoundMng->playSound(CSoundMng::SystemSE::swap);
	}
}

void CSceneSelect::StageSawpRight()
{
	// ----- ����ς݂��`�F�b�N -----
	int CheckSelect = m_select;		// ��Ɨp�ϐ��ɂ���

	CheckSelect++;
	if (CheckSelect > CSceneMng::MAX_STAGE - 1) {		// �I��͈͂𒴂��Ă�����␳
		CheckSelect = CSceneMng::SCENE_STAGE1;
	}
	if (CheckSelect > m_pSceneMng->GetOpenStageNum()) {
		return;												// �J�����Ă��Ȃ���΃J�����ړ����Ȃ�
	}

	// ----- �l�X�V -----
	m_pPlanets[m_select]->EndFocus();	// ���]�~��
	m_select++;

	if (m_select > CSceneMng::MAX_STAGE - 1) {			// �I��͈͂𒴂��Ă�����␳
		m_select = CSceneMng::SCENE_STAGE1;
	}

	// ----- �J�����ړ� -----
	m_pCamera->SetMoveRight(m_select);
	m_pPlanets[m_select]->StartFocus();	// ���]�n��

	//SE
	if (m_pSoundMng->CheckSoundEnd(CSoundMng::SystemSE::swap))
	{
		m_pSoundMng->playSound(CSoundMng::SystemSE::swap);
	}
}
