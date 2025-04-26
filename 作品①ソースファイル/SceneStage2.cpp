//----�C���N���[�h��----
#include "SceneStage2.h"
#include "Model.h"
#include "Camera.h"
#include "Light.h"
#include "Input.h"
#include "Sprite.h"

#include "CameraDCC.h"

//----�w�i----
#include "SkyDome.h"			// �X�J�C�h�[��

//----�I�u�W�F�N�g----
#include "Player.h"				// �v���C���[
#include "Ground.h"				// �n��
#include "Goal.h"				// �S�[��
#include "PlayerCheckPoint.h"	// �v���C���[�`�F�b�N�|�C���g

//----�l�W----
#include "Screw.h"				// �l�W
#include "LoosenRate.h"			// �ɂ�ł����l�W
#include "EndLess.h"			// �ꐶ�񂹂�l�W

//----�M�~�b�N----
#include "MoveFloor.h"			// �ړ��I�u�W�F�N�g
#include "SpinFloor.h"			// ��]�I�u�W�F�N�g
#include "CheckPointPath.h"		// �`�F�b�N�|�C���g���ړ�����M�~�b�N
#include "TemporaryFloor.h"		// �ꎞ�I�ɏo�����鏰

//----UI----
//----�C���Q�[��UI----
#include "Time.h"				// ����UI
#include "PauseMozi.h"			// �|�[�Y����UI

#include "Clear.h"				// �N���AUI
#include "GameOver.h"			// �Q�[���I�[�o�[UI

//----�`���[�g���A��UI----
#include "Left.h"				// �����
#include "Right.h"				// �E���
#include "Start.h"				// �Q�[���X�^�[�g����
//----�Q�[���J�n�OUI----
#include "Ready.h"				// ���f�B�[�S�[����

//---�R���|�[�l���g----
#include "ModelRenderer2D.h"	// 2D�`��

//----�}�l�[�W���[----
#include "ShaderManager.h"		// �V�F�[�_�[�}�l�[�W���[
#include "CollisionManager.h"	// �����蔻��Ǘ��}�l�[�W���[
#include "GameOverManager.h"	// �Q�[���I�[�o�[�}�l�[�W���[
#include  "TimeManager.h"		// �^�C���}�l�[�W���[
#include "AfterGameOverManager.h"	// �A�t�^�[�Q�[���I�[�o�[�}�l�[�W���[
#include "AfterGoalManager.h"	// �A�t�^�[�S�[���}�l�[�W���[
#include "TutorialManager.h"	// �`���[�g���A���}�l�[�W���[
#include "StartSetUpManager.h"	// �Q�[���X�^�[�g�����}�l�[�W���[
#include "PauseManager.h"		// �|�[�Y��ʃ}�l�[�W���[
#include "SoundManager.h"		// �T�E���h�}�l�[�W���[
#include "ResetManager.h"		// ���Z�b�g�}�l�[�W���[

//----�V�X�e��----
#include <vector>

using namespace std;

// �R���X�g���N�^
void SceneStage2::Init()
{
	// �����o�ϐ�������

	// ���v2D�I�u�W�F�N�g
	m_Total2DObjNo = 0;

	// ���v3D�I�u�W�F�N�g
	m_Total3DObjNo = 0;

	// ���v����UI
	m_TotalTimeUINo = 0;

	// �w�i
	CreateSceneObj<SkyDome>("SkyDome");	// �X�J�C�h�[��

	Load();	// �t�@�C���ǂݍ���

	// ���f�B�[�S�[�A�j���[�V����
	CreateSceneObj<Ready>("Ready");
	Ready* obj = GetObj<Ready>("Ready");
	m_Total2DObjNo++;
	obj->Set2DObjNo(m_Total2DObjNo);
	StartSetUpManager::GetInstance().SetStartSetUpUI(obj);

	// �J�������擾
	CameraDCC* pCamObj = GetObj<CameraDCC>("Camera");
	// �v���C���[���擾
	Player* player = GetObj<Player>("Player1");

	// �Q�[���I�[�o�[�Ǘ��N���X�Ƀv���C���[�̏���n��
	GameOverManager::GetInstance().SetPlyer(player);

	// �J�������Ǐ]����^�[�Q�b�g�ݒ�
	pCamObj->SetTarget(player);

	// �X�J�C�h�[�����J�������W�ɍ��킹��
	SkyDome* skydome = GetObj<SkyDome>("SkyDome");
	skydome->SetCamera(pCamObj);

}
void SceneStage2::Uninit()
{

	// �Q�[���I�[�o�[���胊�Z�b�g
	GameOverManager::GetInstance().Reset();

	// �Q�[���I�[�o�[��I�u�W�F�N�g�폜
	AfterGameOverManager::GetInstance().Reset();

	// �S�[����I�u�W�F�N�g�폜
	AfterGoalManager::GetInstance().Reset();

	// �`���[�g���A���I�u�W�F�N�g�폜
	TutorialManager::GetInstance().RemoveALLObj();

	// �|�[�Y��ʃI�u�W�F�N�g�폜
	PauseManager::GetInstance().RemoveALLObj();
	PauseManager::GetInstance().Reset();

	// ���Z�b�g�ΏۃI�u�W�F�N�g�폜
	ResetManager::GetInstance().RemoveALLObj();
}
void SceneStage2::Update(float tick)
{
	// �`���[�g���A�����̓`���[�g���A���̂ݍX�V
	if (TutorialManager::GetInstance().GetTutorial())
	{
		SkyDome* skydome = GetObj<SkyDome>("SkyDome");
		TutorialManager::GetInstance().Update();
		skydome->Update();
		return;
	}
	// ���f�B�[�S�[�A�j���[�V����
	if (!StartSetUpManager::GetInstance().GetStartSetUp())
	{
		SkyDome* skydome = GetObj<SkyDome>("SkyDome");
		StartSetUpManager::GetInstance().Update();
		skydome->Update();
		return;
	}

	// �I�u�W�F�N�g�擾
	Goal* goal = GetObj<Goal>("Goal1");					// �S�[��

	// NULL�Ȃ珈�����Ȃ�
	if (!goal) return;

	// �S�[�����ĂȂ����`�F�b�N
	if ((!goal->GetGoalFlg() &&
		!GameOverManager::GetInstance().GetGameOverFlg()))
	{
		// �|�[�Y��ʂ������炱��ȍ~�������Ȃ�
		if (ProcessNotGoal())	return; // �S�[�������ĂȂ��Ƃ��������鏈�����܂Ƃ߂��֐�
	}


	// �Q�[���I�[�o�[�t���O���オ���Ă���
	if (GameOverManager::GetInstance().GetGameOverFlg())
	{
		// nullptr���m�F
		if (AfterGameOverManager::GetInstance().GetObj())
		{
			GameOverUICreate();	// �Q�[���I�[�o�[���UI�쐬
		}

		// �Q�[���I�[�o�[��X�V����
		AfterGameOverManager::GetInstance().Update();
	}
	// �S�[���t���O���オ���Ă���
	else if (goal->GetGoalFlg())
	{
		// nullptr���m�F
		if (AfterGoalManager::GetInstance().GetObj())
		{
			GoalUICreate();		// �S�[�����UI�쐬
		}

		// �S�[����X�V����
		AfterGoalManager::GetInstance().Update();
	}

}

// �`��
void SceneStage2::Draw()
{
	// �J�����A���C�g�擾
	GameObject* pObjs[] = {
		GetObj<GameObject>("Camera"),
	};

	// �J�����R���|�[�l���g�擾
	Camera* pCamera = pObjs[0]->GetComponent<Camera>();

	// �`��O����
	RenderTarget* pRTV = GetObj<RenderTarget>("RTV");

	// �[�x�o�b�t�@�擾
	DepthStencil* pDSV = GetObj<DepthStencil>("DSV");

	// �X�J�C�h�[���`��
	SetRenderTargets(1, &pRTV, nullptr);

	GameObject* skyDome = GetObj<GameObject>("SkyDome");
	ModelRenderer3D* _modelRenderer3D = skyDome->GetComponent<ModelRenderer3D>();
	// �Z�b�g
	_modelRenderer3D->SetCamera(pCamera);
	// �`��
	_modelRenderer3D->Draw();

	// 3D�`��p�̃����_�[�^�[�Q�b�g�ɂ���
	SetRenderTargets(1, &pRTV, pDSV);

	// �I�u�W�F�N�g�ԍ���o�^����3D�I�u�W�F�N�g�����[�v����
	for (int j = 1; j <= m_Total3DObjNo; j++)
	{
		// 3D���f�������_���[�R���|�[�l���g�擾
		_modelRenderer3D = Get3DObj(j)->GetComponent<ModelRenderer3D>();

		// 3D���f�������_���[�������Ă��珈������
		if (_modelRenderer3D)
		{
			// �Z�b�g
			_modelRenderer3D->SetCamera(pCamera);

			// �`��
			_modelRenderer3D->Draw();
		}
	}

	// 2D�`��悤�ɐݒ肷��
	SetRenderTargets(1, &pRTV, nullptr);

	// �I�u�W�F�N�g�ԍ���o�^����2D�I�u�W�F�N�g�����[�v����
	for (int j = 1; j <= m_Total2DObjNo; j++)
	{
		// 2D���f�������_���[�R���|�[�l���g�擾
		ModelRenderer2D*  _modelRenderer2D = Get2DObj(j)->GetComponent<ModelRenderer2D>();

		// 2D���f�������_���[�������Ă��珈������
		if (_modelRenderer2D)
		{
			// �Z�b�g
			_modelRenderer2D->SetCamera(pObjs[0], pCamera);

			// �`��
			_modelRenderer2D->Draw();
		}
	}

}

// �S�[�����ĂȂ��Ƃ��������鏈��
bool SceneStage2::ProcessNotGoal()
{
	// ���Z�b�g�{�^���������ꂽ���`�F�b�N
	ResetManager::GetInstance().Update();

	// �����蔻��`�F�b�N
	CollisionManager::GetInstance().Update();

	// �Q�[���I�[�o�[�`�F�b�N
	GameOverManager::GetInstance().Update();

	// ����UI����
	TimeManager::GetInstance().Update();

	// �|�[�Y��ʂ��J��
	if (!PauseManager::GetInstance().GetPause() && IsKeyTrigger(VK_ESCAPE))
	{
		// �|�[�Y��ʃt���O���グ��
		PauseManager::GetInstance().PauseOpen();

		// �|�[�Y��ʂ��J��SE
		SoundManager::GetInstance().playSound(SoundManager::SystemSE::Pause);
		return true;
	}
	// �|�[�Y��ʂ��J���Ă���
	else if (PauseManager::GetInstance().GetPause())
	{
		// �X�J�C�h�[���擾
		SkyDome* skydome = GetObj<SkyDome>("SkyDome");

		// �|�[�Y��ʍX�V��������
		PauseManager::GetInstance().Update();

		// �X�J�C�h�[���X�V����
		skydome->Update();

		return true;
	}

	return false;
}

// �X�e�[�W�쐬
void SceneStage2::Load()
{
	//----�X�e�[�W����----

	// �t�@�C���ǂݍ���
	ifstream file("Assets/Map/Stage2.csv");

	// �Z���̓ǂݍ��ݗp
	string cell;

	// �s���i�[�p
	int MaxLine;		
	
	// ��������
	float time;

	// �`�F�b�N�|�C���g
	vector<float3> checkPoint;

	// �t�@�C�����ǂݍ��߂Ă邩
	if (!file)
	{
		MessageBox(NULL, "Stage2.csv�t�@�C�����ǂݍ��߂܂���ł���", "SceneStage2.cpp", MB_OK);
		return;
	}

	// �s�����擾
	getline(file, cell, ',');

	// �s���i�[
	MaxLine = stoi(cell);

	// 3�s�ڂ܂ňړ�
	getline(file, cell);
	getline(file, cell);

	// �t�@�C������f�[�^��ǂݍ���
	for (int i = 0; i < MaxLine; i++)
	{
		// �I�u�W�F�N�g�Ɏ�ގ擾
		getline(file, cell, ',');

		// �I�u�W�F�N�g���Ƃɏ������킯��
		if (cell == "Player")
		{
			// �v���C���[�쐬
			PlayerCreate(file, cell);
		}
		else if (cell == "Ground")
		{
			// �n�ʍ쐬
			GroundCreate(file, cell);
		}
		else if (cell == "Goal")
		{
			// �S�[���쐬
			GoalCreate(file, cell);
		}
		else if (cell == "Screw")
		{
			// �l�W�쐬
			ScrewCreate(file, cell);
		}
		else if (cell == "Gimmick")
		{
			// �M�~�b�N�쐬
			GimmickCreate(file, cell);
		}
		else if (cell == "CheckPoint")
		{
			float3 pos;

			// �ԍ��擾
			getline(file, cell, ',');

			// ���W

			// X���W�擾
			getline(file, cell, ',');

			// float�^�ɕϊ����Đݒ�
			pos.x = stof(cell);

			// Z���W�擾
			getline(file, cell, ',');

			// float�^�ɕϊ����Đݒ�
			pos.z = stof(cell);

			// Y���W�擾
			getline(file, cell, ',');

			// float�^�ɕϊ�
			pos.y = stof(cell);

			// �`�F�b�N�|�C���g�ǉ�
			checkPoint.push_back(pos);
		}
		else if (cell == "PlayerCheckPoint")
		{
			// �v���C���[�`�F�b�N�|�C���g�쐬
			PlayerCheckPointCreate(file, cell);
		}

		// ���̍s��
		getline(file, cell);
	}

	// �t�@�C�������
	file.close();


	//----�M�~�b�N�ɑΉ�����l�W�̐ݒ�----

	// �t�@�C���ǂݍ���
	file.open("Assets/TargetScrew/Stage2TargetScrew.csv");

	// �t�@�C�����ǂݍ��߂Ă邩
	if (!file)
	{
		MessageBox(NULL, "Stage2TargetScrew.csv�t�@�C�����ǂݍ��߂܂���ł���", "SceneGame.cpp", MB_OK);
		return;
	}

	// �s�����擾
	getline(file, cell, ',');

	// �s���i�[
	MaxLine = stoi(cell);

	// 3�s�ڂ܂ňړ�
	getline(file, cell);
	getline(file, cell);

	// �t�@�C������f�[�^��ǂݍ���
	for (int i = 0; i < MaxLine; i++)
	{
		// �M�~�b�N�ɑΏۂ̃l�W��ݒ肷��
		SetTargetScrew(file, cell);

		// ���̍s��
		getline(file, cell);
	}

	// �t�@�C�������
	file.close();


	//----�`�F�b�N�|�C���g�ݒ�----

	// �t�@�C���ǂݍ���
	file.open("Assets/CheckPoint/Stage2CheckPoint.csv");

	// �t�@�C�����ǂݍ��߂Ă邩
	if (!file)
	{
		MessageBox(NULL, "Stage2CheckPoint.csv�t�@�C�����ǂݍ��߂܂���ł���", "SceneGame.cpp", MB_OK);
		return;
	}

	// �s�����擾
	getline(file, cell, ',');

	// �s���i�[
	MaxLine = stoi(cell);

	// 3�s�ڂ܂ňړ�
	getline(file, cell);
	getline(file, cell);

	// �t�@�C������f�[�^��ǂݍ���
	for (int i = 0; i < MaxLine; i++)
	{
		// �M�~�b�N�̃`�F�b�N�|�C���g�ݒ�
		SetCheckPoint(file, cell, checkPoint);

		// ���̍s��
		getline(file, cell);
	}

	// �t�@�C�������
	file.close();


	//----�`�F�b�N�|�C���g�ݒ�----

// �t�@�C���ǂݍ���
	file.open("Assets/Temporary/Stage2TemporaryFloor.csv");

	// �t�@�C�����ǂݍ��߂Ă邩
	if (!file)
	{
		MessageBox(NULL, "Stage2TemporaryFloor.csv�t�@�C�����ǂݍ��߂܂���ł���", "SceneGame.cpp", MB_OK);
		return;
	}

	// �s�����擾
	getline(file, cell, ',');

	// �s���i�[
	MaxLine = stoi(cell);

	// 3�s�ڂ܂ňړ�
	getline(file, cell);
	getline(file, cell);

	// �t�@�C������f�[�^��ǂݍ���
	for (int i = 0; i < MaxLine; i++)
	{
		// �ꎞ�I�ɏo�����鏰�̏��ݒ�
		SetTemporaryInfo(file, cell);

		// ���̍s��
		getline(file, cell);
	}

	// �t�@�C�������
	file.close();


	//----�X�e�[�WUI����----

	// �t�@�C���ǂݍ���
	file.open("Assets/UI/InGame/UI.csv");	// �t�@�C���I�[�v��

	// �t�@�C�����ǂݍ��߂Ă邩
	if (!file)
	{
		MessageBox(NULL, "UI.csv�t�@�C�����ǂݍ��߂܂���ł���", "SceneStage2.cpp", MB_OK);
		return;
	}

	// �s�����擾
	getline(file, cell, ',');

	// �s���i�[
	MaxLine = stoi(cell);

	// 3�s�ڂ܂ňړ�
	getline(file, cell);
	getline(file, cell);

	// �t�@�C������f�[�^��ǂݍ���
	for (int i = 0; i < MaxLine; i++)
	{
		// UI��ގ擾
		getline(file, cell, ',');

		// �I�u�W�F�N�g���Ƃɏ������킯��
		if (cell == "Time")
		{
			// ����UI�쐬
			TimeCreate(file, cell);
		}
		else if (cell == "PauseMozi")
		{
			// �|�[�Y����UI�쐬
			PauseMoziUICreate(file, cell);
		}
		else
		{
			// �S�[��UI�쐬
			InGameNormalUICreate(file, cell);
		}

		// ���̍s��
		getline(file, cell);
	}

	// �t�@�C�������
	file.close();


	//----�������Ԑݒ�----

	// �t�@�C���ǂݍ���
	file.open("Assets/Time/TimeParam.csv");

	// �t�@�C�����ǂݍ��߂Ă邩
	if (!file)
	{
		MessageBox(NULL, "TimeParam.csv�t�@�C�����ǂݍ��߂܂���ł���", "SceneStage2.cpp", MB_OK);
		return;
	}

	// 2�s�ڂ܂ňړ�
	getline(file, cell);
	getline(file, cell);

	// �X�e�[�W���擾
	getline(file, cell, ',');	// �Z��(1���)
	getline(file, cell, ',');	// �Z��(2���)

	// �������Ԏ擾
	time = stof(cell);

	// �������Ԑݒ�
	TimeManager::GetInstance().SetTime(time);

	// �t�@�C�������
	file.close();


	//----�`���[�g���A��UI����----

	// �t�@�C���ǂݍ���
	file.open("Assets/UI/Tutorial/Tutorial.csv");	// �t�@�C���I�[�v��

	// �t�@�C�����ǂݍ��߂Ă邩
	if (!file)
	{
		MessageBox(NULL, "Tutorial.csv�t�@�C�����ǂݍ��߂܂���ł���", "SceneStage2.cpp", MB_OK);
		return;
	}

	// �s�����擾
	getline(file, cell, ',');

	// �s���i�[
	MaxLine = stoi(cell);

	// 3�s�ڂ܂ňړ�
	getline(file, cell);
	getline(file, cell);

	// �t�@�C������f�[�^��ǂݍ���
	for (int i = 0; i < MaxLine; i++)
	{
		// UI��ގ擾
		getline(file, cell, ',');

		// UI���Ƃɏ������킯��
		if (cell == "Right")
		{
			// �E���UI�쐬
			RightUICreate(file, cell);
		}
		else if (cell == "Left")
		{
			// �����UI�쐬
			LeftUICreate(file, cell);
		}
		else if (cell == "Start")
		{
			// �Q�[���X�^�[�g����UI�쐬
			StartUICreate(file, cell);
		}
		else
		{
			// �`���[�g���A�����UI�쐬
			MenuNormalUICreate(file, cell);
		}

		// ���̍s��
		getline(file, cell);
	}

	// �t�@�C�������
	file.close();


	//----�|�[�Y���UI����----

	// �t�@�C���ǂݍ���
	file.open("Assets/UI/Pause/Pause.csv");

	// �t�@�C�����ǂݍ��߂Ă邩
	if (!file)
	{
		MessageBox(NULL, "Pause.csv�t�@�C�����ǂݍ��߂܂���ł���", "SceneStage2.cpp", MB_OK);
		return;
	}

	// �s�����擾
	getline(file, cell, ',');

	// �s���i�[
	MaxLine = stoi(cell);

	// 3�s�ڂ܂ňړ�
	getline(file, cell);
	getline(file, cell);

	// �t�@�C������f�[�^��ǂݍ���
	for (int i = 0; i < MaxLine; i++)
	{
		// UI�̎�ގ擾
		getline(file, cell, ',');

		// UI���Ƃɏ������킯��
		if (cell == "Right")
		{
			// �E���UI�쐬
			RightUICreate(file, cell);
		}
		else if (cell == "Left")
		{
			// �����UI�쐬
			LeftUICreate(file, cell);
		}
		else
		{
			// �|�[�Y���UI�쐬
			MenuNormalUICreate(file, cell);
		}

		// ���̍s��
		getline(file, cell);
	}

	// �t�@�C�������
	file.close();
}

// �v���C���[�쐬
void SceneStage2::PlayerCreate(ifstream& file, string cell)
{
	//----�ϐ��錾----

	// �v���C���[
	Player* player;

	// Box�R���C�_�[�R���|�[�l���g
	BoxCollider* _boxCollider;

	// ���f�������_���[�R���|�[�l���g
	ModelRenderer3D* _modelRenderer3D;

	// ���W
	DirectX::XMFLOAT3 pos;

	// �T�C�Y
	DirectX::XMFLOAT3 scale;

	// �����蔻��T�C�Y
	float3 colliderScale;

	// �p�X
	string path;

	// �I�u�W�F�N�g�Ɋ֘A�Â��閼�O
	string objName = cell;

	// ���Z�b�g�L��
	string reset;


	//----�f�[�^�擾----

	// �I�u�W�F�N�gNo�擾
	getline(file, cell, ',');

	// �I�u�W�F�N�g�J�E���g�A�b�v
	m_Total3DObjNo++;

	// ���O�쐬
	objName += cell;


	// X���W�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	pos.x = stof(cell);

	// Z���W�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	pos.z = stof(cell);

	// Y���W�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	pos.y = stof(cell);


	// X�T�C�Y�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	scale.x = stof(cell);

	// Z�T�C�Y�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	scale.z = stof(cell);

	// Y�T�C�Y�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	scale.y = stof(cell);


	// ���f�����擾
	getline(file, cell, ',');

	// �p�X�쐬
	path = "Assets/Model/" + cell + "/" + cell + ".fbx";

	// �Ώۍ��ڂ܂ł��炷
	// �l�W�̎��
	getline(file, cell, ',');
	// �l�W�ƃi�b�g�̋���
	getline(file, cell, ',');
	// �l�W�ƃi�b�g�̍Œ�����
	getline(file, cell, ',');
	// �g���N
	getline(file, cell, ',');
	// ���[�����g
	getline(file, cell, ',');
	// �l�W���ʔ{��
	getline(file, cell, ',');
	// ���ʔ��]
	getline(file, cell, ',');

	// ���Z�b�g�@�\�L���擾
	getline(file, cell, ',');
	reset = cell;


	//----�ݒ�----

	// �v���C���[�쐬
	CreateSceneObj<Player>(objName.c_str());

	// �v���C���[�擾
	player = GetObj<Player>(objName.c_str());

	// �I�u�W�F�N�g�i���o�[�Z�b�g
	player->Set3DObjNo(m_Total3DObjNo);

	// ���W�Z�b�g
	player->SetPos(pos);

	// �T�C�Y�Z�b�g
	player->SetScale(scale);

	// �{�b�N�X�R���C�_�[�R���|�[�l���g�擾
	_boxCollider = player->GetComponent<BoxCollider>();

	// 3D���f�������_���[�R���|�[�l���g�擾
	_modelRenderer3D = player->GetComponent<ModelRenderer3D>();

	// �T�C�Y���擾
	colliderScale = float3::Tofloat3(scale);

	// �����蔻��p�ɒ���
	colliderScale /= 2;

	// �T�C�Y�ݒ�
	_boxCollider->SetScale(colliderScale);

	// ���f���ǂݍ���
	_modelRenderer3D->SetPath(path);

	// ���Z�b�g�@�\����Ȃ�
	if (reset == "TRUE")
	{
		// �I�u�W�F�N�g�ݒ�
		ResetManager::GetInstance().SetObj(player);
	}

	// �����蔻�菈���̃}�l�[�W���[�ɒǉ�
	CollisionManager::GetInstance().AddObj(player);
}

// �n�ʍ쐬
void SceneStage2::GroundCreate(ifstream & file, string cell)
{
	//----�ϐ��錾----

	// �n��
	Ground* ground;

	// Box�R���C�_�[�R���|�[�l���g
	BoxCollider* _boxCollider;

	// ���f�������_���[�R���|�[�l���g
	ModelRenderer3D* _modelRenderer3D;

	// ���W
	DirectX::XMFLOAT3 pos;

	// �T�C�Y
	DirectX::XMFLOAT3 scale;

	// �����蔻��T�C�Y
	float3 colliderScale;

	// �p�X
	string path;

	// �I�u�W�F�N�g�Ɋ֘A�Â��閼�O
	string objName = cell;


	//----�f�[�^�擾----

	// �I�u�W�F�N�gNo�擾
	getline(file, cell, ',');

	// �I�u�W�F�N�g�J�E���g�A�b�v
	m_Total3DObjNo++;

	// ���O�쐬
	objName += cell;


	// X���W�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	pos.x = stof(cell);

	// Z���W�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	pos.z = stof(cell);

	// Y���W�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	pos.y = stof(cell);


	// X�T�C�Y�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	scale.x = stof(cell);

	// Z�T�C�Y�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	scale.z = stof(cell);

	// Y�T�C�Y�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	scale.y = stof(cell);


	// ���f�����擾
	getline(file, cell, ',');

	// �p�X�쐬
	path = "Assets/Model/" + cell + "/" + cell + ".fbx";


	//----�ݒ�----

	// �n�ʍ쐬
	CreateSceneObj<Ground>(objName.c_str());

	// �n�ʎ擾
	ground = GetObj<Ground>(objName.c_str());

	// �I�u�W�F�N�g�i���o�[�Z�b�g
	ground->Set3DObjNo(m_Total3DObjNo);

	// ���W�Z�b�g
	ground->SetPos(pos);

	// �T�C�Y�Z�b�g
	ground->SetScale(scale);

	// �{�b�N�X�R���C�_�[�R���|�[�l���g�擾
	_boxCollider = ground->GetComponent<BoxCollider>();

	// 3D���f�������_���[�R���|�[�l���g�擾
	_modelRenderer3D = ground->GetComponent<ModelRenderer3D>();

	// �����蔻��擾
	colliderScale = float3::Tofloat3(scale);

	// �����蔻��p�ɒ���
	colliderScale /= 2;

	// �T�C�Y�ݒ�
	_boxCollider->SetScale(colliderScale);

	// ���f���ǂݍ���
	_modelRenderer3D->SetPath(path);

	// �����蔻�菈���̃}�l�[�W���[�ɒǉ�
	CollisionManager::GetInstance().AddObj(ground);
}

// �S�[���쐬
void SceneStage2::GoalCreate(ifstream & file, string cell)
{
	//----�ϐ��錾----

	// �S�[��
	Goal* goal;

	// Box�R���C�_�[�R���|�[�l���g
	BoxCollider* _boxCollider;

	// ���f�������_���[�R���|�[�l���g
	ModelRenderer3D* _modelRenderer3D;

	// ���W
	DirectX::XMFLOAT3 pos;

	// �T�C�Y
	DirectX::XMFLOAT3 scale;

	// �����蔻��T�C�Y
	float3 colliderScale;

	// �p�X
	string path;

	// �I�u�W�F�N�g�Ɋ֘A�Â��閼�O
	string objName = cell;

	
	//----�f�[�^�擾----

	// �I�u�W�F�N�gNo�擾
	getline(file, cell, ',');
	// �I�u�W�F�N�g�J�E���g�A�b�v
	m_Total3DObjNo++;

	// ���O�쐬
	objName += cell;

	// X���W�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	pos.x = stof(cell);

	// Z���W�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	pos.z = stof(cell);

	// Y���W�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	pos.y = stof(cell);


	// X�T�C�Y�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	scale.x = stof(cell);

	// Z�T�C�Y�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	scale.z = stof(cell);

	// Y�T�C�Y�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	scale.y = stof(cell);

	// ���f�����擾
	getline(file, cell, ',');

	// �p�X�쐬
	path = "Assets/Model/" + cell + "/" + cell + ".fbx";


	//----�ݒ�----

	// �S�[���쐬
	CreateSceneObj<Goal>(objName.c_str());

	// �S�[���̎擾
	goal = GetObj<Goal>(objName.c_str());

	// �I�u�W�F�N�g�i���o�[�Z�b�g
	goal->Set3DObjNo(m_Total3DObjNo);

	// ���W�Z�b�g
	goal->SetPos(pos);

	// �T�C�Y�Z�b�g
	goal->SetScale(scale);

	// �{�b�N�X�R���C�_�[�R���|�[�l���g�擾
	_boxCollider = goal->GetComponent<BoxCollider>();

	// 3D���f�������_���[�R���|�[�l���g�擾
	_modelRenderer3D = goal->GetComponent<ModelRenderer3D>();

	// ���f���ǂݍ���
	_modelRenderer3D->SetPath(path);

	// �T�C�Y�擾
	colliderScale = float3::Tofloat3(scale);

	// �����蔻��p�ɒ���
	colliderScale /= 2.0f;

	// �T�C�Y�Z�b�g
	_boxCollider->SetScale(colliderScale);

	// �����蔻�菈���̃}�l�[�W���[�ɒǉ�
	CollisionManager::GetInstance().AddObj(goal);
}

// �l�W�쐬
void SceneStage2::ScrewCreate(ifstream & file, string cell)
{
	//----�ϐ��錾----

	// �l�W
	Screw* screw;

	// �i�b�g
	GameObject* nut;

	// Box�R���C�_�[�R���|�[�l���g
	BoxCollider* _boxCollider;

	// ���f�������_���[�R���|�[�l���g
	ModelRenderer3D* _modelRenderer3D;

	// �l�W�ԍ�
	int screwNo;

	// ���W
	DirectX::XMFLOAT3 pos;

	// �T�C�Y
	DirectX::XMFLOAT3 scale;

	// �����蔻��T�C�Y
	float3 colliderScale;

	// �p�X
	string path;

	// �p�X���ꕔ�ύX�̑Ώ�
	string targetName = "Screw";

	// �u�������閼�O
	string NutName = "Nut";

	// �l�W�̎��
	string screwType;

	// �i�b�g�Ƃ̋���
	float nutDistance;

	// �i�b�g�Ƃ̍Œ�����
	float nutMaxDistance;

	// �g���N
	float torque;

	// ���[�����g
	float moment;

	// �l�W���񂵂��Ƃ��̌��ʔ{��
	float mul;

	// �I�u�W�F�N�g�Ɋ֘A�Â��閼�O
	string objName = cell;

	// ���Z�b�g�L��
	string reset;


	//----�f�[�^�擾----

	// �I�u�W�F�N�gNo�擾
	getline(file, cell, ',');

	// �I�u�W�F�N�g�J�E���g�A�b�v
	m_Total3DObjNo++;	

	// �l�W�ԍ�
	screwNo = stoi(cell) + (stoi(cell) - 1);

	// ���O�쐬
	objName += cell;


	// X���W�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	pos.x = stof(cell);

	// Z���W�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	pos.z = stof(cell);

	// Y���W�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	pos.y = stof(cell);


	// X�T�C�Y�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	scale.x = stof(cell);

	// Z�T�C�Y�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	scale.z = stof(cell);

	// Y�T�C�Y�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	scale.y = stof(cell);


	// ���f�����擾
	getline(file, cell, ',');

	// �p�X�쐬
	path = "Assets/Model/" + cell + "/" + cell + ".fbx";


	// �l�W�̎�ގ擾
	getline(file, cell, ',');

	// �l�W�̎�ސݒ�
	screwType = cell;

	// �i�b�g�Ƃ̋���
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	nutDistance = stof(cell);

	// �i�b�g�Ƃ̍Œ������擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	nutMaxDistance = stof(cell);

	// �g���N�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	torque = stof(cell);


	// ���[�����g�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	moment = stof(cell);

	// �l�W���ʔ{���擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	mul = stof(cell);

	// �Ώۍ��ڂ܂ł��炷
	// ���ʔ��]
	getline(file, cell, ',');

	// ���Z�b�g�@�\�L���擾
	getline(file, cell, ',');
	reset = cell;


	//----�ݒ�----
	// �l�W�쐬
	if (screwType == "LoosenRate")
	{
		// ���߂���ɂ�ł����l�W�쐬
		CreateSceneObj<LoosenRate>(objName.c_str());

		// ���߂���ɂ�ł����l�W�擾
		screw = GetObj<LoosenRate>(objName.c_str());
	}
	else if (screwType == "EndLess")
	{
		// �ꐶ�񂹂�l�W�쐬
		CreateSceneObj<EndLess>(objName.c_str());

		// �ꐶ�񂹂�l�W�擾
		screw = GetObj<EndLess>(objName.c_str());
	}
	else
	{
		// �ʏ�l�W�쐬
		CreateSceneObj<Screw>(objName.c_str());

		// �ʏ�l�W�擾
		screw = GetObj<Screw>(objName.c_str());
	}

	// �I�u�W�F�N�g�i���o�[�Z�b�g
	screw->Set3DObjNo(m_Total3DObjNo);

	// ���W�Z�b�g
	screw->SetPos(pos);

	// �T�C�Y�Z�b�g
	screw->SetScale(scale);

	// �p�x������
	screw->SetQuat(DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	// 3D���f�������_���[�R���|�[�l���g�擾
	_modelRenderer3D = screw->GetComponent<ModelRenderer3D>();

	// ���f���ǂݍ���
	_modelRenderer3D->SetPath(path);

	// �i�b�g�Ƃ̍Œ������ݒ�
	screw->SetNutMaxDistance(nutMaxDistance);

	// �g���N�A���[�����g�ݒ�
	screw->SetSpinParam(torque, moment);

	// ���ʔ{���ݒ�
	screw->SetMultiplier(mul);

	// ���Z�b�g�@�\����Ȃ�
	if (reset == "TRUE")
	{
		// ���W�ێ�
		screw->SetInitePos(pos);

		// �I�u�W�F�N�g�ݒ�
		ResetManager::GetInstance().SetObj(screw);
	}

	// �����蔻�菈���̃}�l�[�W���[�ɒǉ�
	CollisionManager::GetInstance().AddObj(screw);


	//----�i�b�g�̍쐬�A�ݒ�----
	// �ԍ�����
	m_Total3DObjNo++;

	// ���O�쐬
	objName = "Nut" + to_string(screwNo);

	// �T�C�Y�ݒ�
	scale = DirectX::XMFLOAT3(1.1f, 1.1f, 1.1f);

	// �i�b�g�쐬
	CreateSceneObj<GameObject>(objName.c_str());

	// �i�b�g�擾
	nut = GetObj<GameObject>(objName.c_str());

	// �I�u�W�F�N�g�ԍ��Z�b�g
	nut->Set3DObjNo(m_Total3DObjNo);

	// �i�b�g�̈ʒu
	pos.y -= nutDistance;

	// ���W�Z�b�g
	nut->SetPos(pos);

	// �T�C�Y�Z�b�g
	nut->SetScale(scale);

	// �^�O�ݒ�
	nut->SetTag("Nut");

	// �{�b�N�X�R���C�_�[�R���|�[�l���g�ǉ�
	nut->AddComponent<BoxCollider>();

	// 3D���f�������_���[�R���|�[�l���g�ǉ�
	nut->AddComponent<ModelRenderer3D>();

	// �{�b�N�X�R���C�_�[�R���|�[�l���g�擾
	_boxCollider = nut->GetComponent<BoxCollider>();

	// 3D���f�������_���[�R���|�[�l���g�擾
	_modelRenderer3D = nut->GetComponent<ModelRenderer3D>();

	// �T�C�Y�擾
	colliderScale = float3::Tofloat3(scale);

	// �����蔻��p�ɒ���
	colliderScale /= 2.0f;

	// �����蔻��T�C�Y�Z�b�g
	_boxCollider->SetScale(colliderScale);


	// Screw��Nut�ɒu��
	size_t namePos = path.find(targetName);
	while (namePos != string::npos)
	{
		// Nut�ɒu��
		path.replace(namePos, targetName.length(), "Nut");

		// ���̈ʒu������
		namePos = path.find(targetName, namePos + NutName.length());
	}

	// ���f���ǂݍ���
	_modelRenderer3D->SetPath(path);

	// �V�F�[�_�[�t�@�C��
	const char* Shaderfile[] = {
		"VS_Object",
		"PS_TexColor",
	};

	// �V�F�[�_�[�Z�b�g
	_modelRenderer3D->SetShader(Shaderfile);

	// �i�b�g�Z�b�g
	screw->SetNut(nut);

	// �����蔻�菈���̃}�l�[�W���[�ɒǉ�
	CollisionManager::GetInstance().AddObj(nut);
}

// �M�~�b�N�쐬
void SceneStage2::GimmickCreate(ifstream & file, string cell)
{
	//----�ϐ��錾----

	// �M�~�b�N
	GimmickBase* gimmick;

	// Box�R���C�_�[�R���|�[�l���g
	BoxCollider* _boxCollider;

	// ���f�������_���[�R���|�[�l���g
	ModelRenderer3D* _modelRenderer3D;

	// ���W
	DirectX::XMFLOAT3 pos;

	// �T�C�Y
	DirectX::XMFLOAT3 scale;

	// �����蔻��T�C�Y
	float3 colliderScale;

	// �p�X
	string path;

	// ���ʔ��]�t���O
	string InvertFrg;

	// �N���X��
	string className;

	// �y�A�M�~�b�N
	string pairName = "";

	// �ړ���
	float move = 1.0f;
    
	// �I�u�W�F�N�g�Ɋ֘A�Â��閼�O
	string objName = cell;

	// ���Z�b�g�L��
	string reset;


	//----�f�[�^�擾----

	// �I�u�W�F�N�gNo�擾
	getline(file, cell, ',');

	// �I�u�W�F�N�g�J�E���g�A�b�v
	m_Total3DObjNo++;

	// ���O
	objName += cell;

	// X���W�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	pos.x = stof(cell);

	// Z���W�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	pos.z = stof(cell);

	// Y���W�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	pos.y = stof(cell);


	// X�T�C�Y�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	scale.x = stof(cell);

	// Z�T�C�Y�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	scale.z = stof(cell);

	// Y�T�C�Y
	getline(file, cell, ',');

	// float�^�ɕϊ�
	scale.y = stof(cell);


	// ���f�����擾
	getline(file, cell, ',');

	// �p�X�쐬
	path = "Assets/Model/" + cell + "/" + cell + ".fbx";


	// �Ώۍ��ڂ܂ł��炷
	getline(file, cell, ',');		// ��]�L��
	getline(file, cell, ',');		// �i�b�g�Ƃ̋���
	getline(file, cell, ',');		// �i�b�g�Ƃ̍Œ�����
	getline(file, cell, ',');		// �g���N
	getline(file, cell, ',');		// ���[�����g
	getline(file, cell, ',');		// ���ʔ{��


	// ���ʔ��]�t���O�擾
	getline(file, cell, ',');
	// �t���O�ݒ�
	InvertFrg = cell;

	// ���Z�b�g�@�\�L��
	getline(file, cell, ',');
	reset = cell;

	// �M�~�b�N��ގ擾
	getline(file, cell, ',');

	// �N���X���ݒ�
	className = cell;


	// �y�A�M�~�b�N�擾
	getline(file, cell, ',');

	// �����Ă���Ƃ���������
	if (cell != "")
	{
		// �y�A�̃M�~�b�N��
		pairName = "Gimmick" + cell;
	}

	// �M�~�b�N�ړ��ʎ擾
	getline(file, cell, ',');

	// �����Ă���Ƃ���������
	if (cell != "")
	{
		// float�^�ɕϊ�
		move = stof(cell);
	}


	//----�ݒ�----

	// �N���X�쐬
	// �^�C�v�ݒ�
	if (className == "UpDownFloor")
	{
		// �M�~�b�N�쐬
		CreateSceneObj<MoveFloor>(objName.c_str());

		// �M�~�b�N�擾
		gimmick = GetObj<MoveFloor>(objName.c_str());

		// �q�N���X�ɃL���X�g
		MoveFloor* moveFloor = dynamic_cast<MoveFloor*>(gimmick);

		// �ړ��ʃZ�b�g
		moveFloor->SetMove(move);

		// �ړ��^�C�v�Z�b�g
		moveFloor->SetType(MoveFloor::MoveType::UpDown);
	}
	else if (className == "LeftRightFloor")
	{
		// �M�~�b�N�쐬
		CreateSceneObj<MoveFloor>(objName.c_str());

		// �M�~�b�N�擾
		gimmick = GetObj<MoveFloor>(objName.c_str());

		// �q�N���X�ɃL���X�g
		MoveFloor* moveFloor = dynamic_cast<MoveFloor*>(gimmick);

		// �ړ��ʃZ�b�g
		moveFloor->SetMove(move);

		// �ړ��^�C�v�Z�b�g
		moveFloor->SetType(MoveFloor::MoveType::LeftRight);
	}
	else if (className == "YSpin")
	{
		// �M�~�b�N�쐬
		CreateSceneObj<SpinFloor>(objName.c_str());

		// �M�~�b�N�擾
		gimmick = GetObj<SpinFloor>(objName.c_str());

		// �q�N���X�ɃL���X�g
		SpinFloor* spinFloor = dynamic_cast<SpinFloor*>(gimmick);

		// ��]�^�C�v�Z�b�g
		spinFloor->SetType(SpinFloor::SpinType::YSpin);
	}
	else if (className == "CheckPointPath")
	{
		// �M�~�b�N�쐬
		CreateSceneObj<CheckPointPath>(objName.c_str());

		// �M�~�b�N�擾
		gimmick = GetObj<CheckPointPath>(objName.c_str());

		// �q�N���X�ɃL���X�g
		CheckPointPath* checkPointPath = dynamic_cast<CheckPointPath*>(gimmick);

		// �ړ��ʃZ�b�g
		checkPointPath->SetMove(move);
	}
	else if(className == "TemporaryFloor")
	{
		// �M�~�b�N�쐬
		CreateSceneObj<TemporaryFloor>(objName.c_str());

		// �M�~�b�N�擾
		gimmick = GetObj<TemporaryFloor>(objName.c_str());
	}

	// �y�A�M�~�b�N�ݒ�
	if (pairName != "")
	{
		// �M�~�b�N�擾
		GameObject* pairGimmick = GetObj<GameObject>(pairName.c_str());

		// ���ݒ�
		gimmick->SetPair(pairGimmick);
	}

	// �I�u�W�F�N�g�i���o�[�Z�b�g
	gimmick->Set3DObjNo(m_Total3DObjNo);

	// ���W�Z�b�g
	gimmick->SetPos(pos);

	// �T�C�Y�Z�b�g
	gimmick->SetScale(scale);

	// �p�x������
	gimmick->SetQuat(DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	// �{�b�N�X�R���C�_�[�R���|�[�l���g�擾
	_boxCollider = gimmick->GetComponent<BoxCollider>();

	// 3D���f�������_���[�R���|�[�l���g�擾
	_modelRenderer3D = gimmick->GetComponent<ModelRenderer3D>();

	// �T�C�Y�擾
	colliderScale = float3::Tofloat3(scale);

	// �����蔻��p�ɒ���
	colliderScale /= 2.0f;

	// �T�C�Y�ݒ�
	_boxCollider->SetScale(colliderScale);

	// ���f���ǂݍ���
	_modelRenderer3D->SetPath(path);

	// �l�W�̉񂵂��Ƃ��̌��ʔ��]
	if (InvertFrg == "TRUE")
	{
		gimmick->SetInvertEffect(true);
	}

	// ���Z�b�g�@�\����Ȃ�
	if (reset == "TRUE")
	{
		// ���W�ێ�
		gimmick->SetInitePos(pos);

		// �I�u�W�F�N�g�ݒ�
		ResetManager::GetInstance().SetObj(gimmick);
	}

	// �����蔻�菈���̃}�l�[�W���[�ɒǉ�
	CollisionManager::GetInstance().AddObj(gimmick);
}

// �v���C���[�`�F�b�N�|�C���g�쐬
void SceneStage2::PlayerCheckPointCreate(ifstream & file, string cell)
{
	//----�ϐ��錾----

	// �v���C���[
	PlayerCheckPoint* playerCheckPoint;

	// ���W
	DirectX::XMFLOAT3 pos;

	// �T�C�Y
	DirectX::XMFLOAT3 scale;

	// �I�u�W�F�N�g�Ɋ֘A�Â��閼�O
	string objName = cell;


	//----�f�[�^�擾----

	// �I�u�W�F�N�gNo�擾
	getline(file, cell, ',');

	// �I�u�W�F�N�g�J�E���g�A�b�v
	m_Total3DObjNo++;

	// ���O�쐬
	objName += cell;


	// X���W�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	pos.x = stof(cell);

	// Z���W�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	pos.z = stof(cell);

	// Y���W�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	pos.y = stof(cell);


	// X�T�C�Y�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	scale.x = stof(cell);

	// Z�T�C�Y�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	scale.z = stof(cell);

	// Y�T�C�Y�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	scale.y = stof(cell);


	//----�ݒ�----

	// �v���C���[�`�F�b�N�|�C���g�쐬
	CreateSceneObj<PlayerCheckPoint>(objName.c_str());

	// �v���C���[�擾
	playerCheckPoint = GetObj<PlayerCheckPoint>(objName.c_str());

	// �I�u�W�F�N�g�i���o�[�Z�b�g
	playerCheckPoint->Set3DObjNo(m_Total3DObjNo);

	// ���W�Z�b�g
	playerCheckPoint->SetPos(pos);

	// �T�C�Y�Z�b�g
	playerCheckPoint->SetScale(scale);

	// �����蔻�菈���̃}�l�[�W���[�ɒǉ�
	CollisionManager::GetInstance().AddObj(playerCheckPoint);
}

// �M�~�b�N�ɑΏۂ̃l�W��ݒ�
void SceneStage2::SetTargetScrew(ifstream & file, string cell)
{
	//----�ϐ��錾----

	// �M�~�b�N
	GimmickBase* gimmick;

	// �Ώۃl�W�ԍ�
	//std::vector<int> targetScrewNo;

	// �I�u�W�F�N�g�Ɋ֘A�Â��閼�O
	string objName;

	// �l�W�̖��O
	string screwName;

	// �N���X��
	string className;


	//----�f�[�^�擾�A�ݒ�----

	// �I�u�W�F�N�g���擾
	getline(file, cell, ',');

	// �I�u�W�F�N�g���ݒ�
	objName = cell;

	// �M�~�b�N�I�u�W�F�N�g�ԍ�
	getline(file, cell, ',');

	// ���O
	objName += cell;

	// �M�~�b�N�擾
	gimmick = GetObj<GimmickBase>(objName.c_str());

	// �M�~�b�N�̎�ގ擾
	getline(file, cell, ',');
	className = cell;

	// �ݒ肪�I���܂Ń��[�v
	while (true)
	{
		// �l�W�ԍ��擾
		getline(file, cell, ',');

		// �����Ă������珈��
		if (cell != "")
		{
			// ���O�쐬
			screwName = "Screw" + cell;

			// �Ώۃl�W�Z�b�g
			gimmick->SetScrew(GetObj<Screw>(screwName.c_str()));
		}
		else
		{
			break;
		}
	}

	// Y����]�̎�ނ̂�
	if (className == "YSpin")
	{
		// �q�N���X�ɃL���X�g
		SpinFloor* spinfloor = dynamic_cast<SpinFloor*>(GetObj<GimmickBase>(objName.c_str()));

		// �����p�x�ݒ�
		spinfloor->SetInitAngle();
	}
}

// �M�~�b�N�̃`�F�b�N�|�C���g�ݒ�
void SceneStage2::SetCheckPoint(ifstream & file, string cell, vector<float3> checkPoint)
{
	//----�ϐ��錾----

	// �M�~�b�N
	CheckPointPath* gimmick;

	// �I�u�W�F�N�g�Ɋ֘A�Â��閼�O
	string objName;


	//----�f�[�^�擾�A�ݒ�----

	// �I�u�W�F�N�g���擾
	getline(file, cell, ',');
	objName = cell;

	// �M�~�b�N�I�u�W�F�N�g�ԍ��擾
	getline(file, cell, ',');
	objName += cell;

	// �q�N���X�ɃL���X�g
	gimmick = dynamic_cast<CheckPointPath*>(GetObj<GimmickBase>(objName.c_str()));

	// �ݒ肪�I���܂Ń��[�v
	while (true)
	{
		// �`�F�b�N�|�C���g�ԍ��̎擾
		getline(file, cell, ',');

		// �����Ă������珈��
		if (cell != "")
		{
			// �`�F�b�N�|�C���g�̍��W�ݒ�
			gimmick->SetCheckPointPos(checkPoint[stoi(cell) - 1]);
		}
		else
		{
			break;
		}
	}

	// �`�F�b�N�|�C���g�̏���ݒ�
	gimmick->SetCheckPointInfo();
}

// �ꎞ�I�ɏo�����鏰�ɕK�v�ȏ���ݒ�
void SceneStage2::SetTemporaryInfo(ifstream & file, string cell)
{
	//----�ϐ��錾----

	// �M�~�b�N
	TemporaryFloor* gimmick;

	// �O�̏�
	TemporaryFloor* preGimmick = nullptr;

	// ���̏�
	TemporaryFloor* nextGimmick = nullptr;

	// �O�̏��̏��
	TemporaryFloor::TemporaryFloorData* preGimmickData = nullptr;

	// ���̏��̏��
	TemporaryFloor::TemporaryFloorData* nextGimmickData = nullptr;

	// �I�u�W�F�N�g�Ɋ֘A�Â��閼�O
	string objName;

	// ����ւ��鐔��
	string targetName;

	// �����̔ԍ�(���X�g�֌W�̂���M�~�b�N�̒��ł̔ԍ�)
	int myNo;

	// ���v��(���X�g�֌W�̂���M�~�b�N�̍��v��)
	int totalNo;

	//----�f�[�^�擾�A�ݒ�----

	// �I�u�W�F�N�g���擾
	getline(file, cell, ',');
	objName = cell;

	// �M�~�b�N�I�u�W�F�N�g�ԍ��擾
	getline(file, cell, ',');
	objName += cell;
	targetName = cell;

	// �q�N���X�ɃL���X�g
	gimmick = dynamic_cast<TemporaryFloor*>(GetObj<GimmickBase>(objName.c_str()));

	// �Ώۍ��ڂ܂ňړ�
	// �M�~�b�N�̎��
	getline(file, cell, ',');

	// Gimmick�̌��̐������폜
	size_t pos;
	while ((pos = objName.find(targetName)) != std::string::npos)
	{
		objName.erase(pos, targetName.length()); // �������폜
	}

	// ��O�̃M�~�b�N�ԍ�
	getline(file, cell, ',');
	if (cell != "")
	{
		// �ԍ��擾
		targetName = cell;

		// ���O�쐬
		objName += targetName;

		// ��O�̃M�~�b�N�擾
		preGimmick = dynamic_cast<TemporaryFloor*>(GetObj<GimmickBase>(objName.c_str()));

		// ���擾
		preGimmickData = preGimmick->GetTemporaryData();
	}

	// Gimmick�̌��̐������폜
	while ((pos = objName.find(targetName)) != std::string::npos)
	{
		objName.erase(pos, targetName.length()); // �������폜
	}

	// ���̃M�~�b�N�ԍ�
	getline(file, cell, ',');
	if (cell != "")
	{
		// �ԍ��擾
		targetName = cell;

		// ���O�쐬
		objName += targetName;

		// ���̃M�~�b�N�擾
		nextGimmick = dynamic_cast<TemporaryFloor*>(GetObj<GimmickBase>(objName.c_str()));

		// ���擾
		nextGimmickData = nextGimmick->GetTemporaryData();
	}

	// �����̔ԍ�
	getline(file, cell, ',');
	myNo = stoi(cell);

	// ���v��
	getline(file, cell, ',');
	totalNo = stoi(cell);

	// ���ݒ�
	gimmick->SetTemporaryFloorInfo(preGimmickData, nextGimmickData, myNo, totalNo);
}

// ����UI�쐬
void SceneStage2::TimeCreate(ifstream & file, string cell)
{
	//----�ϐ��錾----

	// ����
	Time* time;

	// 2D���f�������_���[�R���|�[�l���g
	ModelRenderer2D* _modelRenderer2D;

	// ���W
	DirectX::XMFLOAT3 pos;

	// �T�C�Y
	DirectX::XMFLOAT3 scale;

	// �p�X
	string path;

	// �I�u�W�F�N�g�Ɋ֘A�Â��閼�O
	string objName = cell;


	//----�f�[�^�擾----

	// �I�u�W�F�N�gNo�擾
	getline(file, cell, ',');

	// �I�u�W�F�N�g�J�E���g�A�b�v
	m_Total2DObjNo++;

	// ����UI�ԍ��J�E���g�A�b�v
	m_TotalTimeUINo++;

	// ���O
	objName += "UI" + std::to_string(m_TotalTimeUINo);

	// X���W�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	pos.x = stof(cell);

	// Y���W�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����ĕϊ�
	pos.y = stof(cell);

	// Z�l������
	pos.z = 0.0f;

	// X�T�C�Y�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	scale.x = stof(cell);

	// Y�T�C�Y�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	scale.y = stof(cell);

	// Z�l������
	scale.z = 0.0f;


	// �e�N�X�`�����擾
	getline(file, cell, ',');

	// �p�X�쐬
	path = "Assets/Texture/InGame/" + cell + ".png";


	//----�ݒ�----

	// ����UI�쐬
	CreateSceneObj<Time>(objName.c_str());

	// ����UI�擾
	time = GetObj<Time>(objName.c_str());

	// �I�u�W�F�N�g�i���o�[�Z�b�g
	time->Set2DObjNo(m_Total2DObjNo);

	// ���W�Z�b�g
	time->SetPos(pos);

	// �T�C�Y�Z�b�g
	time->SetScale(scale);

	// �R���|�[�l���g�擾
	_modelRenderer2D = time->GetComponent<ModelRenderer2D>();

	// �p�X�ݒ�	
	_modelRenderer2D->Load(path.c_str());


	// �X�e�[�WUI���N���AUI�̏��Ɏ���UI�𐶐�����
	// �X�e�[�WUI�̎��Ԃ�4��
	// �������Ȃ�X�e�[�WUI�̍쐬�Ɣ��f���ď�����ς���
	if (m_TotalTimeUINo < 5)
	{
		// �}�l�[�W���[�ɏ���n��
		TimeManager::GetInstance().SetTimeObj(time);
	}
	else
	{
		// �S�[����}�l�[�W���[�ɏ���n��
		AfterGoalManager::GetInstance().SetTimeObj(time);
		_modelRenderer2D->GetParam()->color.w = 0.5f;
		_modelRenderer2D->SetDraw(false);
	}
}

// �ʏ�UI�쐬(���ɓ��L�̓������Ȃ�UI)
void SceneStage2::InGameNormalUICreate(ifstream & file, string cell)
{
	//----�ϐ��錾----

	// �ʏ�UI(�X�e�[�WUI)
	GameObject* normalUI;

	// 2D���f�������_���[�R���|�[�l���g
	ModelRenderer2D* _modelRenderer2D;

	// ���W
	DirectX::XMFLOAT3 pos;

	// �T�C�Y
	DirectX::XMFLOAT3 scale;

	// �p�X
	string path;

	// �I�u�W�F�N�g�Ɋ֘A�Â��閼�O
	string objName = cell;


	//----�f�[�^�擾----

	// �I�u�W�F�N�gNo�擾
	getline(file, cell, ',');

	// �I�u�W�F�N�g�J�E���g�A�b�v
	m_Total2DObjNo++;

	// ���O
	objName += "UI" + cell;

	// X���W�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	pos.x = stof(cell);

	// Y���W�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	pos.y = stof(cell);

	// Z�l������
	pos.z = 0.0f;

	// X�T�C�Y�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	scale.x = stof(cell);

	// Y�T�C�Y�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	scale.y = stof(cell);

	// Z�l������
	scale.z = 0.0f;


	// �e�N�X�`�����擾
	getline(file, cell, ',');

	// �p�X�쐬
	path = "Assets/Texture/InGame/" + cell + ".png";


	//----�ݒ�----

	// �ʏ�UI�쐬
	CreateSceneObj<GameObject>(objName.c_str());

	// �ʏ�UI�擾
	normalUI = GetObj<GameObject>(objName.c_str());

	// �I�u�W�F�N�g�i���o�[�Z�b�g
	normalUI->Set2DObjNo(m_Total2DObjNo);

	// ���W�Z�b�g
	normalUI->SetPos(pos);

	// �T�C�Y�Z�b�g
	normalUI->SetScale(scale);

	// 2D���f�������_���[�R���|�[�l���g�Z�b�g
	normalUI->AddComponent<ModelRenderer2D>();

	// 2D���f�������_���[�R���|�[�l���g�擾
	_modelRenderer2D = normalUI->GetComponent<ModelRenderer2D>();

	// �p�X�ݒ�
	_modelRenderer2D->Load(path.c_str());
}

// �|�[�YUI�쐬
void SceneStage2::PauseMoziUICreate(ifstream & file, string cell)
{
	//----�ϐ��錾----

	// �|�[�Y��ʕ���
	PauseMozi* pauseMozi;

	// 2D���f�������_���[�R���|�[�l���g
	ModelRenderer2D* _modelRenderer2D;

	// ���W
	DirectX::XMFLOAT3 pos;

	// �T�C�Y
	DirectX::XMFLOAT3 scale;

	// �p�X
	string path;

	// �I�u�W�F�N�g�Ɋ֘A�Â��閼�O
	string objName = cell;


	//----�f�[�^�擾----

	// �I�u�W�F�N�gNo�擾
	getline(file, cell, ',');

	// �I�u�W�F�N�g�J�E���g�A�b�v
	m_Total2DObjNo++;

	// ���O
	objName += "UI" + cell;

	// X���W�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	pos.x = stof(cell);

	// Y���W�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	pos.y = stof(cell);

	// Z�l������
	pos.z = 0.0f;

	// X�T�C�Y�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	scale.x = stof(cell);

	// Y�T�C�Y�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	scale.y = stof(cell);

	// Z�l������
	scale.z = 0.0f;


	// �e�N�X�`�����擾
	getline(file, cell, ',');

	// �p�X�쐬
	path = "Assets/Texture/InGame/" + cell + ".png";


	//----�ݒ�----

	// �|�[�Y��ʕ���UI�쐬
	CreateSceneObj<PauseMozi>(objName.c_str());

	// �|�[�Y��ʕ���UI�擾
	pauseMozi = GetObj<PauseMozi>(objName.c_str());

	// �I�u�W�F�N�g�i���o�[�Z�b�g
	pauseMozi->Set2DObjNo(m_Total2DObjNo);

	// ���W�Z�b�g
	pauseMozi->SetPos(pos);

	// �T�C�Y�Z�b�g
	pauseMozi->SetScale(scale);

	// 2D�R���|�[�l���g�擾
	_modelRenderer2D = pauseMozi->GetComponent<ModelRenderer2D>();

	// �p�X�ݒ�	
	_modelRenderer2D->Load(path.c_str());

}

// �ʏ�UI�쐬(�`���[�g���A�����
void SceneStage2::MenuNormalUICreate(ifstream & file, string cell)
{
	//----�ϐ��錾----

	// �ʏ�UI(�`���[�g���A�����)
	GameObject* normalUI;

	// 2D���f�������_���[�R���|�[�l���g
	ModelRenderer2D* _modelRenderer2D;

	// ���W
	DirectX::XMFLOAT3 pos;

	// �T�C�Y
	DirectX::XMFLOAT3 scale;

	// �p�X
	string path;

	// �I�u�W�F�N�g�Ɋ֘A�Â��閼�O
	string objName = cell;

	// �y�[�W�ԍ�
	int page = 0;

	// �I�u�W�F�N�gNo�擾
	getline(file, cell, ',');

	// �I�u�W�F�N�g�J�E���g�A�b�v
	m_Total2DObjNo++;

	// ����󂯂�|�[�Y��ʔw�i�p��
	if (objName == "BackGround")
	{
		m_Total2DObjNo++;
	}

	// ���O
	objName += "UI" + cell;

	// X���W�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	pos.x = stof(cell);

	// Y���W�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	pos.y = stof(cell);

	// Z�l������
	pos.z = 0.0f;

	// X�T�C�Y�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	scale.x = stof(cell);

	// Y�T�C�Y�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	scale.y = stof(cell);

	// Z�l������
	scale.z = 0.0f;


	// �e�N�X�`�����擾
	getline(file, cell, ',');

	// �p�X�쐬
	path = "Assets/Texture/Menu/" + cell + ".png";

	// �y�[�W���ǂݍ���
	getline(file, cell, ',');	// �y�[�W��
	if (cell != "")
	{
		page = stoi(cell);		// �y�[�W���ݒ�
	}

	// ���Ƀ`���[�g���A����ʂō쐬����Ă�����̂��m�F�{�|�[�Y��ʔw�i�͂������ŏ�������
	normalUI = GetObj<GameObject>(objName.c_str());	// ���̎擾
	
	// ����Ă�����̂Ȃ�
	if (normalUI)
	{
		// �I�u�W�F�N�g�ԍ��擾
		int no = normalUI->Get2DObjNo();

		// �J�E���g��߂�
		m_Total2DObjNo--;

		// UI�A�I�u�W�F�N�g�ԍ��A���W�A�T�C�Y�ݒ�
		if (page)
		{
			PauseManager::GetInstance().SetPauseUI(page, normalUI);
		}
		else
		{
			PauseManager::GetInstance().SetNormalUI(normalUI);
		}
		PauseManager::GetInstance().SetPosScale(no, pos, scale);
		return;
	}


	//----�ݒ�----

	// �ʏ�UI�쐬
	CreateSceneObj<GameObject>(objName.c_str());

	// �ʏ�UI�擾
	normalUI = GetObj<GameObject>(objName.c_str());

	// �I�u�W�F�N�g�i���o�[�Z�b�g
	normalUI->Set2DObjNo(m_Total2DObjNo);

	// ���W�Z�b�g
	normalUI->SetPos(pos);

	// �T�C�Y�Z�b�g
	normalUI->SetScale(scale);

	// 2D���f�������_���[�R���|�[�l���g�Z�b�g
	normalUI->AddComponent<ModelRenderer2D>();

	// 2D���f�������_���[�R���|�[�l���g�擾
	_modelRenderer2D = normalUI->GetComponent<ModelRenderer2D>();

	// �p�X�ݒ�
	_modelRenderer2D->Load(path.c_str());

	// �|�[�Y��ʔw�i�p����
	if (objName == "PauseBackGroundUI1")
	{
		GameObject* obj = GetObj<GameObject>("BackGroundUI1");
		// �`���[�g���A���w�i�̈�O�ɗ���悤�ɒ���
		int objNo = obj->Get2DObjNo() - 1;
		m_Total2DObjNo--;

		// �I�u�W�F�N�g�ԍ��ݒ肵����
		normalUI->Set2DObjNo(objNo);
		// UI�A�I�u�W�F�N�g�ԍ��A���W�A�T�C�Y�ݒ�
		PauseManager::GetInstance().SetNormalUI(normalUI);
		PauseManager::GetInstance().SetPosScale(objNo, pos, scale);
		return;
	}

	// �`���[�g���A���}�l�[�W���[�ݒ�
	if (page)
	{
		TutorialManager::GetInstance().SetTutorialUI(page, normalUI);
	}
	else
	{
		TutorialManager::GetInstance().SetNormalUI(normalUI);
	}
}

// �����UI�쐬
void SceneStage2::LeftUICreate(ifstream & file, string cell)
{
	//----�ϐ��錾----

	// �����
	Left* leftUI;

	// �m�F�p
	GameObject* checkLeftUI;

	// 2D���f�������_���[�R���|�[�l���g
	ModelRenderer2D* _modelRenderer2D;

	// ���W
	DirectX::XMFLOAT3 pos;

	// �T�C�Y
	DirectX::XMFLOAT3 scale;

	// �p�X
	string path;

	// �I�u�W�F�N�g�Ɋ֘A�Â��閼�O
	string objName = cell;

	// �y�[�W�ԍ�
	int page = 0;


	//----�f�[�^�擾----

	// �I�u�W�F�N�gNo�擾
	getline(file, cell, ',');

	// �I�u�W�F�N�g�J�E���g�A�b�v
	m_Total2DObjNo++;

	// ���O
	objName += "UI" + cell;

	// X���W�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	pos.x = stof(cell);

	// Y���W�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	pos.y = stof(cell);

	// Z�l������
	pos.z = 0.0f;

	// X�T�C�Y�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	scale.x = stof(cell);

	// Y�T�C�Y�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	scale.y = stof(cell);

	// Z�l������
	scale.z = 0.0f;


	// �e�N�X�`�����擾
	getline(file, cell, ',');

	// �p�X�쐬
	path = "Assets/Texture/Menu/" + cell + ".png";

	// �y�[�W���擾
	getline(file, cell, ',');
	page = stoi(cell);


	// ���ɍ쐬����Ă�����̂��m�F
	checkLeftUI = GetObj<GameObject>(objName.c_str());
	if (checkLeftUI)
	{
		// �I�u�W�F�N�g�ԍ��擾
		int no = checkLeftUI->Get2DObjNo();

		// �J�E���g��߂�
		m_Total2DObjNo--;

		// UI�A�I�u�W�F�N�g�ԍ��A���W�A�T�C�Y�ݒ�
		PauseManager::GetInstance().SetPauseUI(page, checkLeftUI);
		PauseManager::GetInstance().SetPosScale(no, pos, scale);
		return;
	}


	//----�ݒ�----

	// �����UI�쐬
	CreateSceneObj<Left>(objName.c_str());

	// �����擾
	leftUI = GetObj<Left>(objName.c_str());

	// �I�u�W�F�N�g�i���o�[�Z�b�g
	leftUI->Set2DObjNo(m_Total2DObjNo);

	// ���W�Z�b�g
	leftUI->SetPos(pos);

	// �T�C�Y�Z�b�g
	leftUI->SetScale(scale);

	// 2D���f�������_���[�R���|�[�l���g�擾
	_modelRenderer2D = leftUI->GetComponent<ModelRenderer2D>();

	// �p�X�ݒ�
	_modelRenderer2D->Load(path.c_str());

	// �`���[�g���A���ɐݒ�
	TutorialManager::GetInstance().SetTutorialUI(page, leftUI);
}

// �E���UI�쐬
void SceneStage2::RightUICreate(ifstream & file, string cell)
{
	//----�ϐ��錾----

	// �E���
	Right* rightUI;
	GameObject* checkRightUI;

	// 2D���f�������_���[�R���|�[�l���g
	ModelRenderer2D* _modelRenderer2D;

	// ���W
	DirectX::XMFLOAT3 pos;

	// �T�C�Y
	DirectX::XMFLOAT3 scale;

	// �p�X
	string path;

	// �I�u�W�F�N�g�Ɋ֘A�Â��閼�O
	string objName = cell;

	// �y�[�W�ԍ�
	int page = 0;

	// �I�u�W�F�N�gNo�擾
	getline(file, cell, ',');

	// �I�u�W�F�N�g�J�E���g�A�b�v
	m_Total2DObjNo++;

	// ���O
	objName += "UI" + cell;

	// X���W�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	pos.x = stof(cell);

	// Y���W�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	pos.y = stof(cell);

	// Z�l������
	pos.z = 0.0f;

	// X�T�C�Y�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	scale.x = stof(cell);

	// Y�T�C�Y�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	scale.y = stof(cell);

	// Z�l������
	scale.z = 0.0f;


	// �e�N�X�`�����擾
	getline(file, cell, ',');

	// �p�X�쐬
	path = "Assets/Texture/Menu/" + cell + ".png";

	// �y�[�W���擾
	getline(file, cell, ',');
	page = stoi(cell);


	// ���ɍ쐬����Ă�����̂��m�F
	checkRightUI = GetObj<GameObject>(objName.c_str());	// ���̎擾
	if (checkRightUI)
	{
		// �I�u�W�F�N�g�ԍ��擾
		int no = checkRightUI->Get2DObjNo();

		// �J�E���g��߂�
		m_Total2DObjNo--;

		// UI�A�I�u�W�F�N�g�ԍ��A���W�A�T�C�Y�ݒ�
		PauseManager::GetInstance().SetPauseUI(page, checkRightUI);
		PauseManager::GetInstance().SetPosScale(no, pos, scale);
		return;
	}

	//----�ݒ�----

	// �E���UI�쐬
	CreateSceneObj<Right>(objName.c_str());

	// �E���擾
	rightUI = GetObj<Right>(objName.c_str());

	// �I�u�W�F�N�g�i���o�[�Z�b�g
	rightUI->Set2DObjNo(m_Total2DObjNo);

	// ���W�Z�b�g
	rightUI->SetPos(pos);

	// �T�C�Y�Z�b�g
	rightUI->SetScale(scale);

	// 2D���f�������_���[�R���|�[�l���g�擾
	_modelRenderer2D = rightUI->GetComponent<ModelRenderer2D>();

	// �p�X�ݒ�
	_modelRenderer2D->Load(path.c_str());

	// �`���[�g���A���ݒ�
	TutorialManager::GetInstance().SetTutorialUI(page, rightUI);
}

// �Q�[���X�^�[�gUI�쐬
void SceneStage2::StartUICreate(ifstream & file, string cell)
{
	//----�ϐ��錾----

	// �Q�[���X�^�[�gUI
	Start* startUI;

	// 2D���f�������_���[�R���|�[�l���g
	ModelRenderer2D* _modelRenderer2D;

	// ���W
	DirectX::XMFLOAT3 pos;

	// �T�C�Y
	DirectX::XMFLOAT3 scale;

	// �p�X
	string path;

	// �I�u�W�F�N�g�Ɋ֘A�Â��閼�O
	string objName = cell;

	// �y�[�W�ԍ�
	int page = 0;

	// �I�u�W�F�N�gNo�擾
	getline(file, cell, ',');

	// �I�u�W�F�N�g�J�E���g�A�b�v
	m_Total2DObjNo++;

	// ���O
	objName += "UI" + cell;

	// X���W�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	pos.x = stof(cell);

	// Y���W�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	pos.y = stof(cell);

	// Z�l������
	pos.z = 0.0f;

	// X�T�C�Y�擾
	getline(file, cell, ',');

	// float�^�ɕϊ��ݒ�
	scale.x = stof(cell);

	// Y�T�C�Y�擾
	getline(file, cell, ',');

	// float�^�ɕϊ����Đݒ�
	scale.y = stof(cell);

	// Z�l������
	scale.z = 0.0f;


	// �e�N�X�`�����擾
	getline(file, cell, ',');

	// �p�X�쐬
	path = "Assets/Texture/Menu/" + cell + ".png";

	// �y�[�W���ǂݍ���
	getline(file, cell, ',');
	page = stoi(cell);


	//----�ݒ�----

	// �Q�[���X�^�[�gUI�쐬
	CreateSceneObj<Start>(objName.c_str());

	// �Q�[���X�^�[�gUI�擾
	startUI = GetObj<Start>(objName.c_str());

	// �I�u�W�F�N�g�i���o�[�Z�b�g
	startUI->Set2DObjNo(m_Total2DObjNo);

	// ���W�Z�b�g
	startUI->SetPos(pos);

	// �T�C�Y�Z�b�g
	startUI->SetScale(scale);

	// 2D���f�������_���[�R���|�[�l���g�擾
	_modelRenderer2D = startUI->GetComponent<ModelRenderer2D>();

	// �p�X�ݒ�
	_modelRenderer2D->Load(path.c_str());

	// �`���[�g���A���ݒ�
	TutorialManager::GetInstance().SetTutorialUI(page, startUI);
}

// �Q�[���I�[�o�[��ɕ\������UI���쐬
void SceneStage2::GameOverUICreate()
{
	// �X�J�C�h�[���擾
	SkyDome* skydome = GetObj<SkyDome>("SkyDome");

	// �Q�[���I�[�o�[UI�쐬
	CreateSceneObj<GameOver>("GameOver1");

	// �Q�[���I�[�o�[UI�C��
	GameOver* obj = GetObj<GameOver>("GameOver1");

	// �I�u�W�F�N�gNo����
	m_Total2DObjNo++;

	// �I�u�W�F�N�g�ԍ��Z�b�g
	obj->Set2DObjNo(m_Total2DObjNo);

	// �I�u�W�F�N�g�Z�b�g
	AfterGameOverManager::GetInstance().SetObj(obj, skydome);

}

// �S�[����ɕ\������UI���쐬
void SceneStage2::GoalUICreate()
{
	// �v���C���[�擾
	Player* player = GetObj<Player>("Player1");

	// �S�[���擾
	Goal* goal = GetObj<Goal>("Goal1");

	// �J�����擾
	GameObject* camera = GetObj<GameObject>("Camera");

	// �X�J�C�h�[���擾
	SkyDome* skyDome = GetObj<SkyDome>("SkyDome");

	// �N���AUI�쐬
	CreateSceneObj<Clear>("Clear1");

	// �N���AUI�擾
	Clear*	obj = GetObj<Clear>("Clear1");

	// �ԍ�����
	m_Total2DObjNo++;

	// �I�u�W�F�N�g�ԍ��Z�b�g
	obj->Set2DObjNo(m_Total2DObjNo);

	// �I�u�W�F�N�g�Z�b�g
	AfterGoalManager::GetInstance().SetObj(obj, player, goal);
	AfterGoalManager::GetInstance().AddObj(camera);
	AfterGoalManager::GetInstance().AddObj(skyDome);

	// �N���A�^�C��UI�쐬
	ClearTimeUICreate();
	AfterGoalManager::GetInstance().DrawON();
	std::vector<Time*> time = AfterGoalManager::GetInstance().GetTimeObj();
	// �N���A�^�C���v�Z
	TimeManager::GetInstance().CreateClearTime(time);
}

// �N���A�^�C����\������UI���쐬
void SceneStage2::ClearTimeUICreate()
{
	//----�N���AUI����----

	// �t�@�C���ǂݍ���
	ifstream file("Assets/UI/Clear/Clear.csv");

	// �Z�����Ƃ̓ǂݍ��ݐ�
	string cell;

	// �s���i�[�p
	int MaxLine;

	// �t�@�C���ǂݍ��݂��ł�����
	if (!file)
	{
		MessageBox(NULL, "Clear.csv�t�@�C�����ǂݍ��߂܂���ł���", "SceneStage2.cpp", MB_OK);
		return;
	}

	// �s�����擾
	getline(file, cell, ',');

	// �s���i�[
	MaxLine = stoi(cell);

	// 3�s�ڂ܂ňړ�
	getline(file, cell);
	getline(file, cell);

	// �t�@�C������f�[�^��ǂݍ���
	for (int i = 0; i < MaxLine; i++)
	{
		// UI�̎�ނŕ�����
		getline(file, cell, ',');

		// UI���Ƃɏ������킯��
		if (cell == "Time")
		{
			// ����UI�쐬
			TimeCreate(file, cell);
		}

		// ���̍s��
		getline(file, cell);
	}

	// �t�@�C�������
	file.close();
}