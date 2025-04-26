// ModelManager.cpp
#include "ModelManager.h"
#include "Defines.h"
#include "ShaderList.h"

/************************
*@brief コンストラクタ
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
	// 全モデル読み込み
	LoadModelList();
}

/*************************************
*@brief 全モデルを解放するデストラクタ
**************************************/
ModelManager::~ModelManager()
{
	// 解放
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
*@brief 全モデルを読み込む
**************************/
void ModelManager::LoadModelList()
{
	//--Stage01,02
	// きのこ
	mushroom = new Model();	// モデルオブジェクト作成
	if (!mushroom->Load("Assets/Model/Mushroom/Mushroom.fbx", 1.0f, Model::Flip::XFlip))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/Mushroom/Mushroom.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	mushroom->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "きのこ", mushroom });	// モデルデータマップに追加

	// ねこきのこ
	mushroomCat = new Model();	// モデルオブジェクト作成
	if (!mushroomCat->Load("Assets/Model/Mushroom/Mushroom.fbx", 1.0f, Model::Flip::XFlip))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/Mushroom/Mushroom.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	mushroomCat->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "ねこきのこ", mushroomCat });	// モデルデータマップに追加


	// 岩
	rock = new Model();	// モデルオブジェクト作成
	if (!rock->Load("Assets/Model/Rock/Rock.fbx", 1.0f, Model::Flip::XFlip))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/Rock/Rock.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	rock->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "岩", rock });	// モデルデータマップに追加

	// 木
	tree = new Model();	// モデルオブジェクト作成
	if (!tree->Load("Assets/Model/Tree/Tree.fbx", 1.0f, Model::Flip::XFlip))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/Tree/Tree.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	tree->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "木", tree });	// モデルデータマップに追加

	// 木フェンス
	fenceWood = new Model(); // モデルオブジェクト作成
	if (!fenceWood->Load("Assets/Model/Fence/Fence.fbx", 1.0f/*, Model::Flip::XFlip*/))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/Fence/Fence.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	fenceWood->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "木フェンス", fenceWood });	// モデルデータマップに追加

	// 石フェンス
	fenceStone = new Model(); // モデルオブジェクト作成
	if (!fenceStone->Load("Assets/Model/FenceStone/StoneWall.fbx", 0.52f/*, Model::Flip::XFlip*/))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/FenceStone/StoneWall.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	fenceStone->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "石フェンス", fenceStone });	// モデルデータマップに追加

	// 鉄フェンス
	fenceIron = new Model(); // モデルオブジェクト作成
	if (!fenceIron->Load("Assets/Model/FenceIron/FenceIron.fbx", 1.07f/*, Model::Flip::XFlip*/))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/FenceIron/FenceIron.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	fenceIron->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "鉄フェンス", fenceIron });	// モデルデータマップに追加

	// 木材
	wood = new Model();	// モデルオブジェクト作成
	if (!wood->Load("Assets/Model/Mokuzai/wood.fbx", 1.0f, Model::Flip::XFlip))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/Mokuzai/wood.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	wood->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "木材", wood });	// モデルデータマップに追加

	// 小石
	koisi = new Model();	// モデルオブジェクト作成
	if (!koisi->Load("Assets/Model/Koisi/stone.fbx", 1.0f, Model::Flip::XFlip))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/Koisi/stone.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	koisi->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "小石", koisi });	// モデルデータマップに追加

	// 看板
	board = new Model();	// モデルオブジェクト作成
	if (!board->Load("Assets/Model/Kannbann/kannbann.fbx", 1.0f, Model::Flip::XFlip))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/Kannbann/kannbann.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	board->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "看板", board });	// モデルデータマップに追加

	// 鋼材
	metal = new Model();	// モデルオブジェクト作成
	if (!metal->Load("Assets/Model/Koisi/stone.fbx", 1.0f))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/Koisi/stone.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	metal->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "鋼材", metal });	// モデルデータマップに追加

	// チュートリアル看板
	tutorialSignboard = new Model();	// モデルオブジェクト作成
	if (!tutorialSignboard->Load("Assets/Model/SignboardTutrial/signbord.fbx", 0.6f, Model::Flip::XFlip))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/SignboardTutrial/signbord.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	tutorialSignboard->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "チュートリアル看板", tutorialSignboard });	// モデルデータマップに追加

	//--Stage03
	// チョコドーナツ
	ChocolateDonuts = new Model();	// モデルオブジェクト作成
	if (!ChocolateDonuts->Load("Assets/Model/Donuts/donutchocolate.fbx", 0.5f, Model::Flip::XFlip))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/Donuts/donutchocolate.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	ChocolateDonuts->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "チョコドーナツ", ChocolateDonuts });	// モデルデータマップに追加

	// 苺チョコドーナツ
	StrawberryChocolateDonuts = new Model();	// モデルオブジェクト作成
	if (!StrawberryChocolateDonuts->Load("Assets/Model/Donuts/donutstrawberry.fbx", 0.5f, Model::Flip::XFlip))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/Donuts/donutstrawberry.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	StrawberryChocolateDonuts->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "苺チョコドーナツ", StrawberryChocolateDonuts });	// モデルデータマップに追加

	// ケーキピース
	cakePiece = new Model();	// モデルオブジェクト作成
	if (!cakePiece->Load("Assets/Model/CakePiece/BakeCake.fbx", 0.2f, Model::Flip::XFlip))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/CakePiece/BakeCake.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	cakePiece->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "ケーキピース", cakePiece });	// モデルデータマップに追加

	// いちご
	strawberry = new Model();	// モデルオブジェクト作成
	if (!strawberry->Load("Assets/Model/StrawBerry/Stagestrawberry.fbx", 0.5f, Model::Flip::XFlip))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/StrawBerry/Stagestrawberry.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	strawberry->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "いちご", strawberry });	// モデルデータマップに追加

	// アポロ
	apolo = new Model();	// モデルオブジェクト作成
	if (!apolo->Load("Assets/Model/Apolo/Apolo.fbx", 1.0f, Model::Flip::XFlip))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/Apolo/Apolo.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	apolo->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "アポロ", apolo });	// モデルデータマップに追cookie加	

	// クッキー1
	cookie1 = new Model();	// モデルオブジェクト作成
	if (!cookie1->Load("Assets/Model/Cookie/CatCookie.fbx", 1.0f, Model::Flip::XFlip))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/Cookie/CatCookie.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	cookie1->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "クッキー1", cookie1 });	// モデルデータマップに追加

	// クッキー2
	cookie2 = new Model();	// モデルオブジェクト作成
	if (!cookie2->Load("Assets/Model/Cookie/CatCookie2.fbx", 1.0f, Model::Flip::XFlip))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/Cookie/CatCookie2.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	cookie2->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "クッキー2", cookie2 });	// モデルデータマップに追加

	// クッキー3
	cookie3 = new Model();	// モデルオブジェクト作成
	if (!cookie3->Load("Assets/Model/Cookie/CatCookie3.fbx", 1.0f, Model::Flip::XFlip))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/Cookie/CatCookie3.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	cookie3->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "クッキー3", cookie3 });	// モデルデータマップに追加

	// チョコの木
	chocolateTree = new Model();	// モデルオブジェクト作成
	if (!chocolateTree->Load("Assets/Model/ChocolateTree/chocoTree.fbx", 0.65f, Model::Flip::XFlip))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/ChocolateTree/chocoTree.fbx.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	chocolateTree->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "チョコの木", chocolateTree });	// モデルデータマップに追加

	// 青キャンディーの岩
	BlueCandyRock = new Model();	// モデルオブジェクト作成
	if (!BlueCandyRock->Load("Assets/Model/CandyRock/BlueCandyStome.fbx", 0.35f, Model::Flip::XFlip))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/CandyRock/BlueCandyStome.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	BlueCandyRock->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "青キャンディーの岩", BlueCandyRock });	// モデルデータマップに追加

	// 赤キャンディーの岩
	RedCandyRock = new Model();	// モデルオブジェクト作成
	if (!RedCandyRock->Load("Assets/Model/CandyRock/RedCandyStome.fbx", 0.35f, Model::Flip::XFlip))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/CandyRock/RedCandyStome.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	RedCandyRock->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "赤キャンディーの岩", RedCandyRock });	// モデルデータマップに追加

	// チョコのフェンス
	chocolateFence = new Model();	// モデルオブジェクト作成
	if (!chocolateFence->Load("Assets/Model/ChocolatePlate/chokoita.fbx", 0.65f, Model::Flip::XFlip))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/ChocolatePlate/chokoita.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	chocolateFence->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "チョコのフェンス", chocolateFence });	// モデルデータマップに追加

	// 苺チョコのフェンス
	StrawberryChocolateFence = new Model();	// モデルオブジェクト作成
	if (!StrawberryChocolateFence->Load("Assets/Model/ChocolatePlate/strawberrychokoita.fbx", 0.65f, Model::Flip::XFlip))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/ChocolatePlate/strawberrychokoita.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	StrawberryChocolateFence->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "苺チョコのフェンス", StrawberryChocolateFence });	// モデルデータマップに追加

	// チョコのかけら
	chocolatePiece = new Model();	// モデルオブジェクト作成
	if (!chocolatePiece->Load("Assets/Model/ChocolatePlate/chokoBreak.fbx", 1.0f, Model::Flip::XFlip))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/ChocolatePlate/chokoBreake.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	chocolatePiece->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "チョコのかけら", chocolatePiece });	// モデルデータマップに追加	

	// 苺チョコのかけら
	StrawberryChocolatePiece = new Model();	// モデルオブジェクト作成
	if (!StrawberryChocolatePiece->Load("Assets/Model/ChocolatePlate/strawberrychokoBreak.fbx", 1.0f, Model::Flip::XFlip))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/ChocolatePlate/strawberrychokoBreake.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	StrawberryChocolatePiece->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "苺チョコのかけら", StrawberryChocolatePiece });	// モデルデータマップに追加

	// グレープキャンディーのかけら
	GreapCandyPiece = new Model();	// モデルオブジェクト作成
	if (!GreapCandyPiece->Load("Assets/Model/CandyRock/破片/GreapCatDrop.fbx", 1.0f, Model::Flip::XFlip))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/CandyRock/GreapCatDrop.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	GreapCandyPiece->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "グレープキャンディーのかけら", GreapCandyPiece });	// モデルデータマップに追加

	// グレープ魚キャンディーのかけら
	GreapFishCandyPiece = new Model();	// モデルオブジェクト作成
	if (!GreapFishCandyPiece->Load("Assets/Model/CandyRock/破片/GreapFishDrop.fbx", 1.0f, Model::Flip::XFlip))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/CandyRock/GreapFishDrop.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	GreapFishCandyPiece->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "グレープ魚キャンディーのかけら", GreapFishCandyPiece });	// モデルデータマップに追加

	// オレンジキャンディーのかけら
	OrangeCandyPiece = new Model();	// モデルオブジェクト作成
	if (!OrangeCandyPiece->Load("Assets/Model/CandyRock/破片/OrangeCatDrop.fbx", 1.0f, Model::Flip::XFlip))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/CandyRock/OrangeCatDrop.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	OrangeCandyPiece->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "オレンジキャンディーのかけら", OrangeCandyPiece });	// モデルデータマップに追加

	// オレンジ魚キャンディーのかけら
	OrangeFishCandyPiece = new Model();	// モデルオブジェクト作成
	if (!OrangeFishCandyPiece->Load("Assets/Model/CandyRock/破片/OrangeFishDrop.fbx", 1.0f, Model::Flip::XFlip))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/CandyRock/OrangeFishDrop.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	OrangeFishCandyPiece->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "オレンジ魚キャンディーのかけら", OrangeFishCandyPiece });	// モデルデータマップに追加

	// ソーダキャンディーのかけら
	SodaCandyPiece = new Model();	// モデルオブジェクト作成
	if (!SodaCandyPiece->Load("Assets/Model/CandyRock/破片/SodaCatDrop.fbx", 1.0f, Model::Flip::XFlip))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/CandyRock/SodaCatDrop.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	SodaCandyPiece->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "ソーダキャンディーのかけら", SodaCandyPiece });	// モデルデータマップに追加

	// ソーダ魚キャンディーのかけら
	SodaFishCandyPiece = new Model();	// モデルオブジェクト作成
	if (!SodaFishCandyPiece->Load("Assets/Model/CandyRock/破片/SodaFishDrop.fbx", 1.0f, Model::Flip::XFlip))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/CandyRock/SodaFishDrop.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	SodaFishCandyPiece->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "ソーダ魚キャンディーのかけら", SodaFishCandyPiece });	// モデルデータマップに追加

	// ろうそく
	BigCandle = new Model();	// モデルオブジェクト作成
	if (!BigCandle->Load("Assets/Model/Candle/BigCandle.fbx", 1.0f, Model::Flip::XFlip))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/Candle/BigCandle.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	BigCandle->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "大きいろうそく", BigCandle });	// モデルデータマップに追加

	// 小さいろうそく
	MiddleCandle = new Model();	// モデルオブジェクト作成
	if (!MiddleCandle->Load("Assets/Model/Candle/MiddleCandle.fbx", 1.0f, Model::Flip::XFlip))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/Candle/MiddleCandle.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	MiddleCandle->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "小さいろうそく", MiddleCandle });	// モデルデータマップに追加

	// お菓子の家
	sweetsHouse = new Model();	// モデルオブジェクト作成
	if (!sweetsHouse->Load("Assets/Model/SweetsHouse/SweetHouse.fbx", 0.088f, Model::Flip::XFlip))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/SweetsHouse/SweetHouse.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	sweetsHouse->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "お菓子の家", sweetsHouse });	// モデルデータマップに追加

	// 青キノコ
	blueMushroom = new Model();	// モデルオブジェクト作成
	if (!blueMushroom->Load("Assets/Model/BlueMushroom/BlueMashroomKasa.fbx", 0.4f, Model::Flip::XFlip))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/BlueMushroom/BlueMashroomKasa.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	blueMushroom->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "青キノコ", blueMushroom });	// モデルデータマップに追加

	// 青キノコの根本
	blueMushroomNemoto = new Model();	// モデルオブジェクト作成
	if (!blueMushroomNemoto->Load("Assets/Model/BlueMushroom/BlueMashroomNemoto.fbx", 0.72f, Model::Flip::XFlip))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/BlueMushroom/BlueMashroomNemoto.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	blueMushroomNemoto->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "青キノコの根本", blueMushroomNemoto });	// モデルデータマップに追加

	// ビスケット
	biscuit = new Model();	// モデルオブジェクト作成
	if (!biscuit->Load("Assets/Model/Biscuit/Biscket.fbx", 0.3f, Model::Flip::XFlip))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/Biscuit/Biscket.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	biscuit->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "ビスケット", biscuit });	// モデルデータマップに追加

	// ビスケットのかけら
	biscuitPiece = new Model();	// モデルオブジェクト作成
	if (!biscuitPiece->Load("Assets/Model/Biscuit/BiscketCrush.fbx", 1.0f, Model::Flip::XFlip))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/Biscuit/BiscketCrush.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
	biscuitPiece->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));
	m_models.insert({ "ビスケットのかけら", biscuitPiece });	// モデルデータマップに追加
}

/*************************************************
*@brief タグ名に応じたモデルデータの参照を返す
**************************************************
*@param [in] modelTag	モデルのタグ名(キー)
**************************************************/
Model* ModelManager::FindModel(std::string modelTag)
{
	auto it = m_models.find(modelTag);	// オブジェクト名で検索
	if (it != m_models.end()) {		// 検索結果がmapの最後でなければ（検索結果なしだとmapの最後の1つ後ろの要素が入る）
		return it->second;			// その要素のモデルデータを返す
	}
	else {
		return nullptr;	// 検索結果なしならBoxで表示するのでモデルデータはnullにする
	}
}
