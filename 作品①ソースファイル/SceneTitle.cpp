//----�C���N���[�h��----
#include "SceneTitle.h"
#include "Model.h"
#include "Camera.h"
#include "Light.h"
#include "Input.h"
#include "Sprite.h"
#include "Defines.h"
#include "CameraDCC.h"

//----�w�i----
#include "SkyDome.h"			// �X�J�C�h�[��

//----�V�[��----
#include "SceneRoot.h"
#include "SceneGame.h"	// �Q�[���V�[��

#include "ModelRenderer3D.h"

//----�}�l�[�W���[----
#include "TutorialManager.h"	// �`���[�g���A���}�l�[�W���[
#include "SoundManager.h"		// �T�E���h�}�l�[�W���[

//----UI----
#include "Title.h"			// �^�C�g����
#include "TitleScrew.h"		// �l�WUI
#include "StartMessage.h"	// �Q�[���X�^�[�g����
#include "Bird.h"			// ��

// �R���|�[�l���g
#include "Move2DAnimation.h"	// �ړ��A�j���[�V�����R���|�[�l���g
#include "SpinAnimation.h"		// ��]�A�j���[�V�����R���|�[�l���g
#include "OpacityController.h"	// �_�ŏ����R���|�[�l���g

// ������
void SceneTitle::Init()
{
	// �����o�ϐ�������
	m_Total2DObjNo = 0;
	m_Total3DObjNo = 0;
	m_Change = false;

	// �w�i
	CreateSceneObj<SkyDome>("SkyDome");	// �X�J�C�h�[��

	// UI����
	Load();	// �t�@�C���ǂݍ���

	// �J�������擾
	CameraDCC* pCamObj = GetObj<CameraDCC>("Camera");

	// �X�J�C�h�[�����J�������W�ɍ��킹��
	SkyDome* skydome = GetObj<SkyDome>("SkyDome");
	skydome->SetCamera(pCamObj);

}

// �f�X�g���N�^
void SceneTitle::Uninit()
{
	// �`���[�g���A�����s���t���O�𗧂Ă�
	TutorialManager::GetInstance().Reset();
}
void SceneTitle::Update(float tick)
{
	// ���̃V�[�����擾
	SceneBase::Scene nextScene = SceneRoot::GetNextScene();

	// ���̃V�[�����Z�b�g����ĂȂ�
	// �L�[�������ꂽ��
	if (nextScene == SceneBase::Scene::None &&
		(IsKeyTrigger(VK_RETURN) || IsKeyTrigger(VK_SPACE)))
	{
		SceneRoot::SetNextScene(SceneBase::Scene::GAME);

		// ���̃V�[�����擾
		nextScene = SceneRoot::GetNextScene();

		// �Z�b�g�o���ĂȂ�������SE�Đ����Ȃ�
		if (nextScene != SceneBase::Scene::GAME)
		{
			return;
		}

		// �X�^�[�gSE�Đ�
		SoundManager::GetInstance().playSound(SoundManager::SystemSE::Tstrat);
	}

}
void SceneTitle::Draw()
{
	// �e��f�[�^�̏���
	GameObject* pObjs[] = {
		GetObj<GameObject>("Camera"),
	};
	Camera* pCamera = pObjs[0]->GetComponent<Camera>();

	// �`��O����
	RenderTarget* pRTV = GetObj<RenderTarget>("RTV");
	DepthStencil* pDSV = GetObj<DepthStencil>("DSV");

	// �X�J�C�h�[���`��
	SetRenderTargets(1, &pRTV, nullptr);

	GameObject* skyDome = GetObj<GameObject>("SkyDome");
	ModelRenderer3D* _modelRenderer3D = skyDome->GetComponent<ModelRenderer3D>();
	// �Z�b�g
	_modelRenderer3D->SetCamera(pCamera);
	// �`��
	_modelRenderer3D->Draw();

	// �����_�[�^�[�Q�b�g�̕ύX
	// ���`�����ݐ�̕ύX
	SetRenderTargets(1, &pRTV, pDSV);	// ���A�`�����ݐ�̏��A�[�x�o�b�t�@

	// 3D�`��
	// �V�[�����������Ă���I�u�W�F�N�g�̕`��
	for (int j = 1; j <= m_Total3DObjNo; j++)
	{
		ModelRenderer3D*  _modelRenderer3D = Get3DObj(j)->GetComponent<ModelRenderer3D>();

		if (_modelRenderer3D)
		{
			// �Z�b�g
			_modelRenderer3D->SetCamera(pCamera);

			// �`��
			_modelRenderer3D->Draw();
		}
	}

	// ���̃f�B�X�v���C�\���ɖ߂�
	// �����_�[�^�[�Q�b�g�ɕ`�����܂ꂽ���e��
	// 2D�摜�ƂȂ�̂ŁA2D�摜�����߂�
	// �f�B�X�v���C�ɕ\������Ƃ��A�[�x�o�b�t�@��
	// �s�v�ƂȂ�(�Ăяo�����ŉ�ʂɕ`��)
	SetRenderTargets(1, &pRTV, nullptr);

	// 2D�`��
	// �V�[�����������Ă���I�u�W�F�N�g�̕`��
	for (int j = 1; j <= m_Total2DObjNo; j++)
	{

		ModelRenderer2D*  _modelRenderer2D = Get2DObj(j)->GetComponent<ModelRenderer2D>();

		if (_modelRenderer2D)
		{
			// �Z�b�g
			_modelRenderer2D->SetCamera(pObjs[0], pCamera);

			// �`��
			_modelRenderer2D->Draw();
		}
	}
}

// �t�@�C���ǂݍ���
void SceneTitle::Load()
{
	ifstream file("Assets/UI/Title/TitleUI.csv");	// �t�@�C���I�[�v��
	string cell;	// �Z�����Ƃ̓ǂݍ��ݐ�
	int MaxLine;	// �s���i�[�p

	if (!file)
	{
		MessageBox(NULL, "TitleUI.csv�t�@�C�����ǂݍ��߂܂���ł���", "SceneGame.cpp", MB_OK);
		return;
	}

	getline(file, cell, ',');	// �s�����o
	MaxLine = stoi(cell);		// �s���i�[

	// 3�s�ڂ܂ňړ�
	getline(file, cell);
	getline(file, cell);

	// �t�@�C������f�[�^��ǂݍ���
	for (int i = 0; i < MaxLine; i++)
	{
		getline(file, cell, ',');	// �Z�����o(1���)

		// UI���Ƃɏ������킯��
		if (cell == "TitleName")
		{
			TitleNameCreate(file, cell);	// �^�C�g����UI�쐬
		}
		else if (cell == "TitleLeftScrew" ||
			cell == "TitleRightScrew")
		{
			// �l�WUI�쐬
			TitleScrewCreate(file, cell);
		}
		else if (cell == "GameStart")
		{
			GameStartCreate(file, cell);	// �Q�[���X�^�[�gUI�쐬
		}
		else if (cell == "Bird")
		{
			BirdCreate(file, cell);			// ��UI�쐬
		}
		else
		{
			NormalUICreate(file, cell);		// �ʏ�UI�쐬
		}

		getline(file, cell);		// ���̍s��
	}
	file.close();	// �t�@�C�������
}

// �^�C�g����UI�쐬
void SceneTitle::TitleNameCreate(ifstream & file, string cell)
{
	// �ϐ��錾
	Title* titleUI;
	ModelRenderer2D* _modelRenderer2D;	// ���f�������_���[�R���|�[�l���g
	Move2DAnimation* _move2DAnimation;	// 2D�A�j���[�V�����R���|�[�l���g
	SpinAnimation* _spinAnimation;		// ��]�A�j���[�V�����R���|�[�l���g
	DirectX::XMFLOAT3 pos;				// ���W
	DirectX::XMFLOAT3 scale;			// �T�C�Y
	string path;						// �p�X
	string objName = cell;				// �I�u�W�F�N�g�Ɋ֘A�Â��閼�O
	DirectX::XMFLOAT2 normalSpeed;		// �ړ����x
	DirectX::XMFLOAT2 animationSpeed;	// �A�j���[�V�����X�s�[�h
	Move2DAnimation::MoveKind kind;		// �A�j���[�V��������
	DirectX::XMFLOAT2 min;				// �ŏ����W
	DirectX::XMFLOAT2 max;				// �ő���W
	int spinNum;						// ��]��
	int deltaSpin;						// ��]��
	DirectX::XMFLOAT4 axis;				// ��]��
	size_t commaPos;					// ,�̈ʒu
	
	// �I�u�W�F�N�g�i���o�[
	getline(file, cell, ',');		// �I�u�W�F�N�gNo�擾
	m_Total2DObjNo++;				// �I�u�W�F�N�g�J�E���g�A�b�v

	objName += "UI" + cell;			// ���O

	// ���W
	getline(file, cell, ',');		// X���W
	pos.x = stof(cell);				// float�^�ɕ�
	getline(file, cell, ',');		// Y���W
	pos.y = stof(cell);				// float�^�ɕϊ�
	pos.z = 0.0f;					// Z�l������

	// �T�C�Y
	getline(file, cell, ',');		// X�T�C�Y
	scale.x = stof(cell);			// float�^�ɕϊ�
	getline(file, cell, ',');		// Y�T�C�Y
	scale.y = stof(cell);			// float�^�ɕϊ�
	scale.z = 0.0f;					// Z�l������


	// �e�N�X�`�����ǂݍ���
	getline(file, cell, ',');		// �e�N�X�`����
	path = "Assets/Texture/Title/" + cell + ".png";		// �p�X�쐬

	// �ړ����x
	getline(file, cell, ',');		// �ړ����x�擾
	commaPos = cell.find(' ');
	// ,���O���������o����float�^�ɕϊ����Đݒ�
	normalSpeed.x = stof(cell.substr(0, commaPos));
	normalSpeed.y = stof(cell.substr(commaPos + 1));

	// �Ώۍ��ڂ܂ł��炷
	getline(file, cell, ',');		// �����x

	// �A�j���[�V�����X�s�[�h
	getline(file, cell, ',');		// �A�j���[�V�����X�s�[�h�擾
	commaPos = cell.find(' ');
	// ,���O���������o����float�^�ɕϊ����ăA�j���[�V�����X�s�[�h�ݒ�
	animationSpeed.x = stof(cell.substr(0, commaPos));
	animationSpeed.y = stof(cell.substr(commaPos + 1));

	// �A�j���[�V��������
	getline(file, cell, ',');
	if (cell == "X")
	{
		kind = Move2DAnimation::MoveKind::Left_Right;
	}
	else
	{
		kind = Move2DAnimation::MoveKind::Up_Down;
	}

	// �ŏ����W
	getline(file, cell, ',');
	commaPos = cell.find(' ');
	// ,���O���������o����float�^�ɕϊ����čŏ����W�ݒ�
	min.x = stof(cell.substr(0, commaPos));
	min.y = stof(cell.substr(commaPos + 1));

	// �ő���W
	getline(file, cell, ',');
	commaPos = cell.find(' ');
	// ,���O���������o����float�^�ɕϊ����čŏ����W�ݒ�
	max.x = stof(cell.substr(0, commaPos));
	max.y = stof(cell.substr(commaPos + 1));

	// ��]��
	getline(file, cell, ',');		// ��]���擾
	spinNum = stoi(cell);			// int�^�ɕϊ����ĉ�]���ݒ�

	// ��]��
	getline(file, cell, ',');		// ��]�ʎ擾
	deltaSpin = stoi(cell);			// int�^�ɕϊ����ĉ�]�ʐݒ�

	// ��]��
	getline(file, cell, ',');
	if (cell == "X")
	{
		axis = DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 0.0f);
	}
	else if(cell == "Y")
	{
		axis = DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f);
	}
	else
	{
		axis = DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 0.0f);
	}

	CreateSceneObj<Title>(objName.c_str());		// �ʏ�UI�쐬
	titleUI = GetObj<Title>(objName.c_str());	// ���̎擾
	titleUI->Set2DObjNo(m_Total2DObjNo);		// �I�u�W�F�N�g�i���o�[�Z�b�g
	titleUI->SetPos(pos);						// ���W�Z�b�g
	titleUI->SetScale(scale);					// �T�C�Y�Z�b�g
	// �R���|�[�l���g�擾
	_modelRenderer2D = titleUI->GetComponent<ModelRenderer2D>();
	_move2DAnimation = titleUI->GetComponent<Move2DAnimation>();
	_spinAnimation = titleUI->GetComponent<SpinAnimation>();
	_modelRenderer2D->Load(path.c_str());		// �p�X�ݒ�

	_move2DAnimation->SetSpeed(normalSpeed);	// �ړ����x�ݒ�
	titleUI->SetAnimationSpeed(animationSpeed);	// �A�j���[�V�������x�ݒ�
	_move2DAnimation->SetMoveKind(kind);		// �ړ������ݒ�
	_move2DAnimation->SetMoveArea(min, max);	// �ړ��͈͐ݒ�
	_spinAnimation->SetSpinNum(spinNum);		// ��]���ݒ�
	_spinAnimation->SetDeltaRot(deltaSpin);		// ��]�ʐݒ�
	_spinAnimation->SetAxis(axis);				// ��]���ݒ�
}

// �l�WUI�쐬
void SceneTitle::TitleScrewCreate(ifstream & file, string cell)
{
	//----�ϐ��錾----
	TitleScrew* titleScrewUI;

	// ���f�������_���[�R���|�[�l���g
	ModelRenderer2D* _modelRenderer2D;

	// 2D�A�j���[�V�����R���|�[�l���g
	Move2DAnimation* _move2DAnimation;

	// ��]�A�j���[�V�����R���|�[�l���g
	SpinAnimation* _spinAnimation;

	// ���W
	DirectX::XMFLOAT3 pos;

	// �T�C�Y
	DirectX::XMFLOAT3 scale;

	// �p�X
	string path;

	// �I�u�W�F�N�g�Ɋ֘A�Â��閼�O
	string objName = cell;

	// �ړ����x
	DirectX::XMFLOAT2 normalSpeed;

	// �A�j���[�V�����X�s�[�h
	DirectX::XMFLOAT2 animationSpeed;

	// �A�j���[�V��������
	Move2DAnimation::MoveKind kind;

	// �ŏ����W
	DirectX::XMFLOAT2 min;

	// �ő���W
	DirectX::XMFLOAT2 max;

	// ��]��
	int spinNum;

	// ��]��
	int deltaSpin;

	// ��]��
	DirectX::XMFLOAT4 axis;

	// ,�̈ʒu
	size_t commaPos;

	// �^�[�Q�b�g���W
	DirectX::XMFLOAT3 targetPos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);


	//----�f�[�^�擾----

	// �I�u�W�F�N�g�i���o�[
	getline(file, cell, ',');		// �I�u�W�F�N�gNo�擾

	// �I�u�W�F�N�g�J�E���g�A�b�v
	m_Total2DObjNo++;

	// ���O�쐬
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


	// �e�N�X�`�����ǂݍ���

	// �e�N�X�`����
	getline(file, cell, ',');

	// �p�X�쐬
	path = "Assets/Texture/Title/" + cell + ".png";

	// �ړ����x

	// �ړ����x�擾
	getline(file, cell, ',');
	commaPos = cell.find(' ');
	// ,���O���������o����float�^�ɕϊ����Đݒ�
	normalSpeed.x = stof(cell.substr(0, commaPos));
	normalSpeed.y = stof(cell.substr(commaPos + 1));

	// �Ώۍ��ڂ܂ł��炷
	getline(file, cell, ',');		// �����x

	// �A�j���[�V�����X�s�[�h
	getline(file, cell, ',');		// �A�j���[�V�����X�s�[�h�擾
	commaPos = cell.find(' ');
	// ,���O���������o����float�^�ɕϊ����ăA�j���[�V�����X�s�[�h�ݒ�
	animationSpeed.x = stof(cell.substr(0, commaPos));
	animationSpeed.y = stof(cell.substr(commaPos + 1));

	// �A�j���[�V��������
	getline(file, cell, ',');
	if (cell == "X")
	{
		kind = Move2DAnimation::MoveKind::Left_Right;
	}
	else
	{
		kind = Move2DAnimation::MoveKind::Up_Down;
	}

	// �ŏ����W
	getline(file, cell, ',');
	commaPos = cell.find(' ');
	// ,���O���������o����float�^�ɕϊ����čŏ����W�ݒ�
	min.x = stof(cell.substr(0, commaPos));
	min.y = stof(cell.substr(commaPos + 1));

	// �ő���W
	getline(file, cell, ',');
	commaPos = cell.find(' ');
	// ,���O���������o����float�^�ɕϊ����čŏ����W�ݒ�
	max.x = stof(cell.substr(0, commaPos));
	max.y = stof(cell.substr(commaPos + 1));

	// ��]��
	getline(file, cell, ',');		// ��]���擾
	spinNum = stoi(cell);			// int�^�ɕϊ����ĉ�]���ݒ�

	// ��]��
	getline(file, cell, ',');		// ��]�ʎ擾
	deltaSpin = stoi(cell);			// int�^�ɕϊ����ĉ�]�ʐݒ�

	// ��]��
	getline(file, cell, ',');
	if (cell == "X")
	{
		axis = DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 0.0f);
	}
	else if (cell == "Y")
	{
		axis = DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f);
	}
	else
	{
		axis = DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 0.0f);
	}

	// �^�[�Q�b�g���WY�擾
	getline(file, cell, ',');
	targetPos.x = pos.x;
	targetPos.y = stof(cell);

	//----�ݒ�----

	// �l�WUI�쐬
	CreateSceneObj<TitleScrew>(objName.c_str());

	// ���̎擾
	titleScrewUI = GetObj<TitleScrew>(objName.c_str());

	// �I�u�W�F�N�g�i���o�[�Z�b�g
	titleScrewUI->Set2DObjNo(m_Total2DObjNo);

	// ���W�Z�b�g
	titleScrewUI->SetPos(pos);

	// �T�C�Y�Z�b�g
	titleScrewUI->SetScale(scale);

	// �R���|�[�l���g�擾

	// 2D���f�������_���[�R���|�[�l���g
	_modelRenderer2D = titleScrewUI->GetComponent<ModelRenderer2D>();

	// �ړ��A�j���[�V�����R���|�[�l���g
	_move2DAnimation = titleScrewUI->GetComponent<Move2DAnimation>();

	// ��]�A�j���[�V�����R���|�[�l���g
	_spinAnimation = titleScrewUI->GetComponent<SpinAnimation>();

	// �p�X�ݒ�
	_modelRenderer2D->Load(path.c_str());

	// �ړ����x�ݒ�
	_move2DAnimation->SetSpeed(normalSpeed);

	// �A�j���[�V�������x�ݒ�
	titleScrewUI->SetAnimationSpeed(animationSpeed);

	// �ړ������ݒ�
	_move2DAnimation->SetMoveKind(kind);

	// �ړ��͈͐ݒ�
	_move2DAnimation->SetMoveArea(min, max);

	// ��]���ݒ�
	_spinAnimation->SetSpinNum(spinNum);

	// ��]�ʐݒ�
	_spinAnimation->SetDeltaRot(deltaSpin);

	// ��]���ݒ�
	_spinAnimation->SetAxis(axis);

	// �^�[�Q�b�g���W�ݒ�
	titleScrewUI->SetTargetPos(targetPos);
}

// �Q�[���X�^�[�gUI�쐬
void SceneTitle::GameStartCreate(ifstream & file, string cell)
{
	// �ϐ��錾
	StartMessage* startMessageUI;
	ModelRenderer2D* _modelRenderer2D;	// ���f�������_���[�R���|�[�l���g
	Opacity* _opacity;					// �I�p�V�e�B�R���|�[�l���g
	DirectX::XMFLOAT3 pos;				// ���W
	DirectX::XMFLOAT3 scale;			// �T�C�Y
	string path;						// �p�X
	string objName = cell;				// �I�u�W�F�N�g�Ɋ֘A�Â��閼�O
	float animationSpeed;				// �A�j���[�V�����X�s�[�h

	// �I�u�W�F�N�g�i���o�[
	getline(file, cell, ',');		// �I�u�W�F�N�gNo�擾
	m_Total2DObjNo++;				// �I�u�W�F�N�g�J�E���g�A�b�v

	objName += "UI" + cell;			// ���O

	// ���W
	getline(file, cell, ',');		// X���W
	pos.x = stof(cell);				// float�^�ɕ�
	getline(file, cell, ',');		// Y���W
	pos.y = stof(cell);				// float�^�ɕϊ�
	pos.z = 0.0f;					// Z�l������

	// �T�C�Y
	getline(file, cell, ',');		// X�T�C�Y
	scale.x = stof(cell);			// float�^�ɕϊ�
	getline(file, cell, ',');		// Y�T�C�Y
	scale.y = stof(cell);			// float�^�ɕϊ�
	scale.z = 0.0f;					// Z�l������


	// �e�N�X�`�����ǂݍ���
	getline(file, cell, ',');		// �e�N�X�`����
	path = "Assets/Texture/Title/" + cell + ".png";		// �p�X�쐬

	// �Ώۍ��ڂ܂ł��炷
	getline(file, cell, ',');		// �ړ����x�擾
	getline(file, cell, ',');		// �����x

	// �A�j���[�V�����X�s�[�h
	getline(file, cell, ',');		// �A�j���[�V�����X�s�[�h�擾
	animationSpeed = stof(cell);	// �A�j���[�V�����X�s�[�h�ݒ�


	CreateSceneObj<StartMessage>(objName.c_str());			// �ʏ�UI�쐬
	startMessageUI = GetObj<StartMessage>(objName.c_str());	// ���̎擾
	startMessageUI->Set2DObjNo(m_Total2DObjNo);				// �I�u�W�F�N�g�i���o�[�Z�b�g
	startMessageUI->SetPos(pos);							// ���W�Z�b�g
	startMessageUI->SetScale(scale);						// �T�C�Y�Z�b�g
	// �R���|�[�l���g�擾
	_modelRenderer2D = startMessageUI->GetComponent<ModelRenderer2D>();
	_opacity = startMessageUI->GetComponent<Opacity>();
	_modelRenderer2D->Load(path.c_str());					// �p�X�ݒ�

	_opacity->SetChangeValue(animationSpeed);				// �A�j���[�V�����X�s�[�h�ݒ�
}

// ��UI�쐬
void SceneTitle::BirdCreate(ifstream & file, string cell)
{
	// �ϐ��錾
	Bird* birdUI;
	ModelRenderer2D* _modelRenderer2D;	// ���f�������_���[�R���|�[�l���g
	DirectX::XMFLOAT3 pos;				// ���W
	DirectX::XMFLOAT3 scale;			// �T�C�Y
	string path;						// �p�X
	string objName = cell;				// �I�u�W�F�N�g�Ɋ֘A�Â��閼�O
	float speed;						// �ʏ�X�s�[�h
	float acceleration;					// �����x

	// �I�u�W�F�N�g�i���o�[
	getline(file, cell, ',');		// �I�u�W�F�N�gNo�擾
	m_Total2DObjNo++;				// �I�u�W�F�N�g�J�E���g�A�b�v

	objName += "UI" + cell;			// ���O

	// ���W
	getline(file, cell, ',');		// X���W
	pos.x = stof(cell);				// float�^�ɕ�
	getline(file, cell, ',');		// Y���W
	pos.y = stof(cell);				// float�^�ɕϊ�
	pos.z = 0.0f;					// Z�l������

	// �T�C�Y
	getline(file, cell, ',');		// X�T�C�Y
	scale.x = stof(cell);			// float�^�ɕϊ�
	getline(file, cell, ',');		// Y�T�C�Y
	scale.y = stof(cell);			// float�^�ɕϊ�
	scale.z = 0.0f;					// Z�l������


	// �e�N�X�`�����ǂݍ���
	getline(file, cell, ',');		// �e�N�X�`����
	path = "Assets/Texture/Title/" + cell + ".png";		// �p�X�쐬

	// �ړ����x
	getline(file, cell, ',');		// �ړ����x�擾
	speed = stof(cell);				// �ړ����x�ݒ�

	// �����x
	getline(file, cell, ',');		// �����x�擾
	acceleration = stof(cell);		// �����x�ݒ�


	CreateSceneObj<Bird>(objName.c_str());	// �ʏ�UI�쐬
	birdUI = GetObj<Bird>(objName.c_str());	// ���̎擾
	birdUI->Set2DObjNo(m_Total2DObjNo);		// �I�u�W�F�N�g�i���o�[�Z�b�g
	birdUI->SetPos(pos);					// ���W�Z�b�g
	birdUI->SetScale(scale);				// �T�C�Y�Z�b�g
	// �R���|�[�l���g�擾
	_modelRenderer2D = birdUI->GetComponent<ModelRenderer2D>();
	_modelRenderer2D->Load(path.c_str());	// �p�X�ݒ�

	birdUI->SetVelocity(speed);				// �ړ����x�ݒ�
	birdUI->SetAcceleration(acceleration);	// �����x�ݒ�
}

// �ʏ�UI�쐬
void SceneTitle::NormalUICreate(ifstream & file, string cell)
{
	// �ϐ��錾
	GameObject* normalUI;
	ModelRenderer2D* _modelRenderer2D;	// ���f�������_���[�R���|�[�l���g
	DirectX::XMFLOAT3 pos;				// ���W
	DirectX::XMFLOAT3 scale;			// �T�C�Y
	string path;						// �p�X
	string objName = cell;				// �I�u�W�F�N�g�Ɋ֘A�Â��閼�O

	// �I�u�W�F�N�g�i���o�[
	getline(file, cell, ',');	// �I�u�W�F�N�gNo�擾
	m_Total2DObjNo++;			// �I�u�W�F�N�g�J�E���g�A�b�v

	objName += "UI" + cell;		// ���O

	// ���W
	getline(file, cell, ',');	// X���W
	pos.x = stof(cell);			// float�^�ɕ�
	getline(file, cell, ',');	// Y���W
	pos.y = stof(cell);			// float�^�ɕϊ�
	pos.z = 0.0f;				// Z�l������

	// �T�C�Y
	getline(file, cell, ',');	// X�T�C�Y
	scale.x = stof(cell);		// float�^�ɕϊ�
	getline(file, cell, ',');	// Y�T�C�Y
	scale.y = stof(cell);		// float�^�ɕϊ�
	scale.z = 0.0f;				// Z�l������


	// �e�N�X�`�����ǂݍ���
	getline(file, cell, ',');	// �e�N�X�`����
	path = "Assets/Texture/Title/" + cell + ".png";		// �p�X�쐬


	CreateSceneObj<GameObject>(objName.c_str());	// �ʏ�UI�쐬
	normalUI = GetObj<GameObject>(objName.c_str());	// ���̎擾
	normalUI->Set2DObjNo(m_Total2DObjNo);			// �I�u�W�F�N�g�i���o�[�Z�b�g
	normalUI->SetPos(pos);							// ���W�Z�b�g
	normalUI->SetScale(scale);						// �T�C�Y�Z�b�g
	normalUI->AddComponent<ModelRenderer2D>();		// �R���|�[�l���g�Z�b�g
	_modelRenderer2D = normalUI->GetComponent<ModelRenderer2D>();	// �R���|�[�l���g�擾
	_modelRenderer2D->Load(path.c_str());			// �p�X�ݒ�

}
