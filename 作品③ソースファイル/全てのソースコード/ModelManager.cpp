// ModelManager.cpp
#include "ModelManager.h"
#include "Defines.h"
#include "ShaderList.h"

/************************
*@brief �R���X�g���N�^
*************************/
ModelManager::ModelManager()
	: mushroom(nullptr)
	, mushroomCat(nullptr)
	, rock(nullptr)
	, tree(nullptr)
	, fenceWood(nullptr)
	, fenceStone(nullptr)
	, fenceIron(nullptr)
	, wood(nullptr)
	, koisi(nullptr)
	, board(nullptr)
	, metal(nullptr)
	, ChocolateDonuts(nullptr)
	, StrawberryChocolateDonuts(nullptr)
	, cakePiece(nullptr)
	, strawberry(nullptr)
	, apolo(nullptr)
	, cookie1(nullptr)
	, cookie2(nullptr)
	, cookie3(nullptr)
	, chocolateTree(nullptr)
	, BlueCandyRock(nullptr)
	, RedCandyRock(nullptr)
	, chocolateFence(nullptr)
	, StrawberryChocolateFence(nullptr)
	, chocolatePiece(nullptr)
	, StrawberryChocolatePiece(nullptr)
	, GreapCandyPiece(nullptr)
	, GreapFishCandyPiece(nullptr)
	, OrangeCandyPiece(nullptr)
	, OrangeFishCandyPiece(nullptr)
	, SodaCandyPiece(nullptr)
	, SodaFishCandyPiece(nullptr)
	, BigCandle(nullptr)
	, MiddleCandle(nullptr)
	, sweetsHouse(nullptr)
	, blueMushroom(nullptr)
	, blueMushroomNemoto(nullptr)
	, biscuit(nullptr)
	, biscuitPiece(nullptr)
	, tutorialSignboard(nullptr)
{
	// �S���f���ǂݍ���
	LoadModelList();
}

/*************************************
*@brief �S���f�����������f�X�g���N�^
**************************************/
ModelManager::~ModelManager()
{
	// ���
	SAFE_DELETE(mushroom);
	SAFE_DELETE(mushroomCat);
	SAFE_DELETE(rock);
	SAFE_DELETE(tree);
	SAFE_DELETE(fenceWood);
	SAFE_DELETE(fenceStone);
	SAFE_DELETE(fenceIron);
	SAFE_DELETE(wood);
	SAFE_DELETE(koisi);
	SAFE_DELETE(board);
	SAFE_DELETE(metal);
	SAFE_DELETE(ChocolateDonuts);
	SAFE_DELETE(StrawberryChocolateDonuts);
	SAFE_DELETE(cakePiece);
	SAFE_DELETE(strawberry);
	SAFE_DELETE(apolo);
	SAFE_DELETE(cookie1);
	SAFE_DELETE(cookie2);
	SAFE_DELETE(cookie3);
	SAFE_DELETE(chocolateTree);
	SAFE_DELETE(BlueCandyRock);
	SAFE_DELETE(RedCandyRock);
	SAFE_DELETE(chocolateFence);
	SAFE_DELETE(StrawberryChocolateFence);
	SAFE_DELETE(chocolatePiece);
	SAFE_DELETE(StrawberryChocolatePiece);
	SAFE_DELETE(GreapCandyPiece);
	SAFE_DELETE(GreapFishCandyPiece);
	SAFE_DELETE(OrangeCandyPiece);
	SAFE_DELETE(OrangeFishCandyPiece);
	SAFE_DELETE(SodaCandyPiece);
	SAFE_DELETE(SodaFishCandyPiece);
	SAFE_DELETE(BigCandle);
	SAFE_DELETE(MiddleCandle);
	SAFE_DELETE(sweetsHouse);
	SAFE_DELETE(blueMushroom);
	SAFE_DELETE(blueMushroomNemoto);
	SAFE_DELETE(biscuit);
	SAFE_DELETE(biscuitPiece);
	SAFE_DELETE(tutorialSignboard);
}

/*************************
*@brief �S���f����ǂݍ���
**************************/
void ModelManager::LoadModelList()
{
	//--Stage01,02
	// ���̂�
	mushroom = new Model();	// ���f���I�u�W�F�N�g�쐬
	if (!mushroom->Load("Assets/Model/Mushroom/Mushroom.fbx", 1.0f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/Mushroom/Mushroom.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	mushroom->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "���̂�", mushroom });	// ���f���f�[�^�}�b�v�ɒǉ�

	// �˂����̂�
	mushroomCat = new Model();	// ���f���I�u�W�F�N�g�쐬
	if (!mushroomCat->Load("Assets/Model/Mushroom/Mushroom.fbx", 1.0f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/Mushroom/Mushroom.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	mushroomCat->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "�˂����̂�", mushroomCat });	// ���f���f�[�^�}�b�v�ɒǉ�


	// ��
	rock = new Model();	// ���f���I�u�W�F�N�g�쐬
	if (!rock->Load("Assets/Model/Rock/Rock.fbx", 1.0f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/Rock/Rock.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	rock->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "��", rock });	// ���f���f�[�^�}�b�v�ɒǉ�

	// ��
	tree = new Model();	// ���f���I�u�W�F�N�g�쐬
	if (!tree->Load("Assets/Model/Tree/Tree.fbx", 1.0f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/Tree/Tree.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	tree->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "��", tree });	// ���f���f�[�^�}�b�v�ɒǉ�

	// �؃t�F���X
	fenceWood = new Model(); // ���f���I�u�W�F�N�g�쐬
	if (!fenceWood->Load("Assets/Model/Fence/Fence.fbx", 1.0f/*, Model::Flip::XFlip*/))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/Fence/Fence.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	fenceWood->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "�؃t�F���X", fenceWood });	// ���f���f�[�^�}�b�v�ɒǉ�

	// �΃t�F���X
	fenceStone = new Model(); // ���f���I�u�W�F�N�g�쐬
	if (!fenceStone->Load("Assets/Model/FenceStone/StoneWall.fbx", 0.52f/*, Model::Flip::XFlip*/))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/FenceStone/StoneWall.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	fenceStone->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "�΃t�F���X", fenceStone });	// ���f���f�[�^�}�b�v�ɒǉ�

	// �S�t�F���X
	fenceIron = new Model(); // ���f���I�u�W�F�N�g�쐬
	if (!fenceIron->Load("Assets/Model/FenceIron/FenceIron.fbx", 1.07f/*, Model::Flip::XFlip*/))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/FenceIron/FenceIron.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	fenceIron->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "�S�t�F���X", fenceIron });	// ���f���f�[�^�}�b�v�ɒǉ�

	// �؍�
	wood = new Model();	// ���f���I�u�W�F�N�g�쐬
	if (!wood->Load("Assets/Model/Mokuzai/wood.fbx", 1.0f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/Mokuzai/wood.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	wood->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "�؍�", wood });	// ���f���f�[�^�}�b�v�ɒǉ�

	// ����
	koisi = new Model();	// ���f���I�u�W�F�N�g�쐬
	if (!koisi->Load("Assets/Model/Koisi/stone.fbx", 1.0f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/Koisi/stone.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	koisi->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "����", koisi });	// ���f���f�[�^�}�b�v�ɒǉ�

	// �Ŕ�
	board = new Model();	// ���f���I�u�W�F�N�g�쐬
	if (!board->Load("Assets/Model/Kannbann/kannbann.fbx", 1.0f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/Kannbann/kannbann.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	board->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "�Ŕ�", board });	// ���f���f�[�^�}�b�v�ɒǉ�

	// �|��
	metal = new Model();	// ���f���I�u�W�F�N�g�쐬
	if (!metal->Load("Assets/Model/Koisi/stone.fbx", 1.0f))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/Koisi/stone.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	metal->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "�|��", metal });	// ���f���f�[�^�}�b�v�ɒǉ�

	// �`���[�g���A���Ŕ�
	tutorialSignboard = new Model();	// ���f���I�u�W�F�N�g�쐬
	if (!tutorialSignboard->Load("Assets/Model/SignboardTutrial/signbord.fbx", 0.6f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/SignboardTutrial/signbord.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	tutorialSignboard->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "�`���[�g���A���Ŕ�", tutorialSignboard });	// ���f���f�[�^�}�b�v�ɒǉ�

	//--Stage03
	// �`���R�h�[�i�c
	ChocolateDonuts = new Model();	// ���f���I�u�W�F�N�g�쐬
	if (!ChocolateDonuts->Load("Assets/Model/Donuts/donutchocolate.fbx", 0.5f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/Donuts/donutchocolate.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	ChocolateDonuts->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "�`���R�h�[�i�c", ChocolateDonuts });	// ���f���f�[�^�}�b�v�ɒǉ�

	// 䕃`���R�h�[�i�c
	StrawberryChocolateDonuts = new Model();	// ���f���I�u�W�F�N�g�쐬
	if (!StrawberryChocolateDonuts->Load("Assets/Model/Donuts/donutstrawberry.fbx", 0.5f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/Donuts/donutstrawberry.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	StrawberryChocolateDonuts->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "䕃`���R�h�[�i�c", StrawberryChocolateDonuts });	// ���f���f�[�^�}�b�v�ɒǉ�

	// �P�[�L�s�[�X
	cakePiece = new Model();	// ���f���I�u�W�F�N�g�쐬
	if (!cakePiece->Load("Assets/Model/CakePiece/BakeCake.fbx", 0.2f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/CakePiece/BakeCake.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	cakePiece->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "�P�[�L�s�[�X", cakePiece });	// ���f���f�[�^�}�b�v�ɒǉ�

	// ������
	strawberry = new Model();	// ���f���I�u�W�F�N�g�쐬
	if (!strawberry->Load("Assets/Model/StrawBerry/Stagestrawberry.fbx", 0.5f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/StrawBerry/Stagestrawberry.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	strawberry->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "������", strawberry });	// ���f���f�[�^�}�b�v�ɒǉ�

	// �A�|��
	apolo = new Model();	// ���f���I�u�W�F�N�g�쐬
	if (!apolo->Load("Assets/Model/Apolo/Apolo.fbx", 1.0f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/Apolo/Apolo.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	apolo->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "�A�|��", apolo });	// ���f���f�[�^�}�b�v�ɒ�cookie��	

	// �N�b�L�[1
	cookie1 = new Model();	// ���f���I�u�W�F�N�g�쐬
	if (!cookie1->Load("Assets/Model/Cookie/CatCookie.fbx", 1.0f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/Cookie/CatCookie.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	cookie1->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "�N�b�L�[1", cookie1 });	// ���f���f�[�^�}�b�v�ɒǉ�

	// �N�b�L�[2
	cookie2 = new Model();	// ���f���I�u�W�F�N�g�쐬
	if (!cookie2->Load("Assets/Model/Cookie/CatCookie2.fbx", 1.0f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/Cookie/CatCookie2.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	cookie2->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "�N�b�L�[2", cookie2 });	// ���f���f�[�^�}�b�v�ɒǉ�

	// �N�b�L�[3
	cookie3 = new Model();	// ���f���I�u�W�F�N�g�쐬
	if (!cookie3->Load("Assets/Model/Cookie/CatCookie3.fbx", 1.0f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/Cookie/CatCookie3.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	cookie3->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "�N�b�L�[3", cookie3 });	// ���f���f�[�^�}�b�v�ɒǉ�

	// �`���R�̖�
	chocolateTree = new Model();	// ���f���I�u�W�F�N�g�쐬
	if (!chocolateTree->Load("Assets/Model/ChocolateTree/chocoTree.fbx", 0.65f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/ChocolateTree/chocoTree.fbx.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	chocolateTree->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "�`���R�̖�", chocolateTree });	// ���f���f�[�^�}�b�v�ɒǉ�

	// �L�����f�B�[�̊�
	BlueCandyRock = new Model();	// ���f���I�u�W�F�N�g�쐬
	if (!BlueCandyRock->Load("Assets/Model/CandyRock/BlueCandyStome.fbx", 0.35f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/CandyRock/BlueCandyStome.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	BlueCandyRock->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "�L�����f�B�[�̊�", BlueCandyRock });	// ���f���f�[�^�}�b�v�ɒǉ�

	// �ԃL�����f�B�[�̊�
	RedCandyRock = new Model();	// ���f���I�u�W�F�N�g�쐬
	if (!RedCandyRock->Load("Assets/Model/CandyRock/RedCandyStome.fbx", 0.35f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/CandyRock/RedCandyStome.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	RedCandyRock->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "�ԃL�����f�B�[�̊�", RedCandyRock });	// ���f���f�[�^�}�b�v�ɒǉ�

	// �`���R�̃t�F���X
	chocolateFence = new Model();	// ���f���I�u�W�F�N�g�쐬
	if (!chocolateFence->Load("Assets/Model/ChocolatePlate/chokoita.fbx", 0.65f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/ChocolatePlate/chokoita.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	chocolateFence->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "�`���R�̃t�F���X", chocolateFence });	// ���f���f�[�^�}�b�v�ɒǉ�

	// 䕃`���R�̃t�F���X
	StrawberryChocolateFence = new Model();	// ���f���I�u�W�F�N�g�쐬
	if (!StrawberryChocolateFence->Load("Assets/Model/ChocolatePlate/strawberrychokoita.fbx", 0.65f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/ChocolatePlate/strawberrychokoita.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	StrawberryChocolateFence->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "䕃`���R�̃t�F���X", StrawberryChocolateFence });	// ���f���f�[�^�}�b�v�ɒǉ�

	// �`���R�̂�����
	chocolatePiece = new Model();	// ���f���I�u�W�F�N�g�쐬
	if (!chocolatePiece->Load("Assets/Model/ChocolatePlate/chokoBreak.fbx", 1.0f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/ChocolatePlate/chokoBreake.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	chocolatePiece->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "�`���R�̂�����", chocolatePiece });	// ���f���f�[�^�}�b�v�ɒǉ�	

	// 䕃`���R�̂�����
	StrawberryChocolatePiece = new Model();	// ���f���I�u�W�F�N�g�쐬
	if (!StrawberryChocolatePiece->Load("Assets/Model/ChocolatePlate/strawberrychokoBreak.fbx", 1.0f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/ChocolatePlate/strawberrychokoBreake.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	StrawberryChocolatePiece->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "䕃`���R�̂�����", StrawberryChocolatePiece });	// ���f���f�[�^�}�b�v�ɒǉ�

	// �O���[�v�L�����f�B�[�̂�����
	GreapCandyPiece = new Model();	// ���f���I�u�W�F�N�g�쐬
	if (!GreapCandyPiece->Load("Assets/Model/CandyRock/�j��/GreapCatDrop.fbx", 1.0f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/CandyRock/GreapCatDrop.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	GreapCandyPiece->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "�O���[�v�L�����f�B�[�̂�����", GreapCandyPiece });	// ���f���f�[�^�}�b�v�ɒǉ�

	// �O���[�v���L�����f�B�[�̂�����
	GreapFishCandyPiece = new Model();	// ���f���I�u�W�F�N�g�쐬
	if (!GreapFishCandyPiece->Load("Assets/Model/CandyRock/�j��/GreapFishDrop.fbx", 1.0f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/CandyRock/GreapFishDrop.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	GreapFishCandyPiece->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "�O���[�v���L�����f�B�[�̂�����", GreapFishCandyPiece });	// ���f���f�[�^�}�b�v�ɒǉ�

	// �I�����W�L�����f�B�[�̂�����
	OrangeCandyPiece = new Model();	// ���f���I�u�W�F�N�g�쐬
	if (!OrangeCandyPiece->Load("Assets/Model/CandyRock/�j��/OrangeCatDrop.fbx", 1.0f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/CandyRock/OrangeCatDrop.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	OrangeCandyPiece->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "�I�����W�L�����f�B�[�̂�����", OrangeCandyPiece });	// ���f���f�[�^�}�b�v�ɒǉ�

	// �I�����W���L�����f�B�[�̂�����
	OrangeFishCandyPiece = new Model();	// ���f���I�u�W�F�N�g�쐬
	if (!OrangeFishCandyPiece->Load("Assets/Model/CandyRock/�j��/OrangeFishDrop.fbx", 1.0f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/CandyRock/OrangeFishDrop.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	OrangeFishCandyPiece->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "�I�����W���L�����f�B�[�̂�����", OrangeFishCandyPiece });	// ���f���f�[�^�}�b�v�ɒǉ�

	// �\�[�_�L�����f�B�[�̂�����
	SodaCandyPiece = new Model();	// ���f���I�u�W�F�N�g�쐬
	if (!SodaCandyPiece->Load("Assets/Model/CandyRock/�j��/SodaCatDrop.fbx", 1.0f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/CandyRock/SodaCatDrop.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	SodaCandyPiece->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "�\�[�_�L�����f�B�[�̂�����", SodaCandyPiece });	// ���f���f�[�^�}�b�v�ɒǉ�

	// �\�[�_���L�����f�B�[�̂�����
	SodaFishCandyPiece = new Model();	// ���f���I�u�W�F�N�g�쐬
	if (!SodaFishCandyPiece->Load("Assets/Model/CandyRock/�j��/SodaFishDrop.fbx", 1.0f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/CandyRock/SodaFishDrop.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	SodaFishCandyPiece->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "�\�[�_���L�����f�B�[�̂�����", SodaFishCandyPiece });	// ���f���f�[�^�}�b�v�ɒǉ�

	// �낤����
	BigCandle = new Model();	// ���f���I�u�W�F�N�g�쐬
	if (!BigCandle->Load("Assets/Model/Candle/BigCandle.fbx", 1.0f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/Candle/BigCandle.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	BigCandle->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "�傫���낤����", BigCandle });	// ���f���f�[�^�}�b�v�ɒǉ�

	// �������낤����
	MiddleCandle = new Model();	// ���f���I�u�W�F�N�g�쐬
	if (!MiddleCandle->Load("Assets/Model/Candle/MiddleCandle.fbx", 1.0f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/Candle/MiddleCandle.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	MiddleCandle->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "�������낤����", MiddleCandle });	// ���f���f�[�^�}�b�v�ɒǉ�

	// ���َq�̉�
	sweetsHouse = new Model();	// ���f���I�u�W�F�N�g�쐬
	if (!sweetsHouse->Load("Assets/Model/SweetsHouse/SweetHouse.fbx", 0.088f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/SweetsHouse/SweetHouse.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	sweetsHouse->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "���َq�̉�", sweetsHouse });	// ���f���f�[�^�}�b�v�ɒǉ�

	// �L�m�R
	blueMushroom = new Model();	// ���f���I�u�W�F�N�g�쐬
	if (!blueMushroom->Load("Assets/Model/BlueMushroom/BlueMashroomKasa.fbx", 0.4f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/BlueMushroom/BlueMashroomKasa.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	blueMushroom->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "�L�m�R", blueMushroom });	// ���f���f�[�^�}�b�v�ɒǉ�

	// �L�m�R�̍��{
	blueMushroomNemoto = new Model();	// ���f���I�u�W�F�N�g�쐬
	if (!blueMushroomNemoto->Load("Assets/Model/BlueMushroom/BlueMashroomNemoto.fbx", 0.72f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/BlueMushroom/BlueMashroomNemoto.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	blueMushroomNemoto->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "�L�m�R�̍��{", blueMushroomNemoto });	// ���f���f�[�^�}�b�v�ɒǉ�

	// �r�X�P�b�g
	biscuit = new Model();	// ���f���I�u�W�F�N�g�쐬
	if (!biscuit->Load("Assets/Model/Biscuit/Biscket.fbx", 0.3f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/Biscuit/Biscket.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	biscuit->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "�r�X�P�b�g", biscuit });	// ���f���f�[�^�}�b�v�ɒǉ�

	// �r�X�P�b�g�̂�����
	biscuitPiece = new Model();	// ���f���I�u�W�F�N�g�쐬
	if (!biscuitPiece->Load("Assets/Model/Biscuit/BiscketCrush.fbx", 1.0f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/Biscuit/BiscketCrush.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
	biscuitPiece->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "�r�X�P�b�g�̂�����", biscuitPiece });	// ���f���f�[�^�}�b�v�ɒǉ�
}

/*************************************************
*@brief �^�O���ɉ��������f���f�[�^�̎Q�Ƃ�Ԃ�
**************************************************
*@param [in] modelTag	���f���̃^�O��(�L�[)
**************************************************/
Model* ModelManager::FindModel(std::string modelTag)
{
	auto it = m_models.find(modelTag);	// �I�u�W�F�N�g���Ō���
	if (it != m_models.end()) {		// �������ʂ�map�̍Ō�łȂ���΁i�������ʂȂ�����map�̍Ō��1���̗v�f������j
		return it->second;			// ���̗v�f�̃��f���f�[�^��Ԃ�
	}
	else {
		return nullptr;	// �������ʂȂ��Ȃ�Box�ŕ\������̂Ń��f���f�[�^��null�ɂ���
	}
}
