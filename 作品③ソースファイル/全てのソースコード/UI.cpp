#include "UI.h"
#include "SceneGame.h"
#include "Input.h"

//**********定数宣言**********




//グローバル変数


CUI::CUI()
	: m_Left(0.0f)
	, m_Right((float)SCREEN_WIDTH)
	, m_Bottom((float)SCREEN_HEIGHT)
	, m_Top(0.0f)
	, m_near(1.0f)
	, m_far(10.0f)
	, m_pTexture{ nullptr, nullptr, nullptr,nullptr,nullptr }
	, m_bAdd(false)
	, m_fAlpha(1.0f)
	
{

	

	for (int i = 0; i < MAX_UI; ++i)
	{
		m_pTexture[i] = new Texture();
	}

	if (FAILED(m_pTexture[0]->Create("Assets/Texture/UI_number4.png")))
	{
		MessageBox(NULL, "UI UI_number4.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[1]->Create("Assets/Texture/UI_Money2.png")))
	{
		MessageBox(NULL, "UI UI_Money2.png", "Error", MB_OK);
	}


	m_basePosX = 1050.0f;
	m_basePosY = 70.0f;
	m_nScore = 0;

	//数字
	for (int i = 0; i < DIGIT_SCORE; ++i)
	{
		m_score[i].size = DirectX::XMFLOAT2(m_pTexture[0]->GetWidth() / 6.5f, m_pTexture[0]->GetHeight() / 6.5f);
		m_score[i].pos = DirectX::XMFLOAT3(m_basePosX + i * m_score[i].size.x - (i *30.0f), m_basePosY + 5.0f, 0.0f);
		m_score[i].posTexCoord = DirectX::XMFLOAT2(0.0f, 0.0f);
		m_score[i].sizeTexCoord = DirectX::XMFLOAT2(1.0f / (float)ANIM_SCORE_SPLIT_X, 1.0f / (float)ANIM_SCORE_SPLIT_Y);

		m_score[i].frame = 0;
		m_score[i].currentAnimNo = 0;
	}

	//フレーム
	m_score[DIGIT_SCORE].size = DirectX::XMFLOAT2((float)m_pTexture[1]->GetWidth(), (float)m_pTexture[1]->GetHeight());
	//m_score[DIGIT_SCORE].size = DirectX::XMFLOAT2(330.0f, 150.0f);
	m_score[DIGIT_SCORE].pos = DirectX::XMFLOAT3(m_basePosX + 50.0f, m_basePosY + 5.0f, 0.0f);
	m_score[DIGIT_SCORE].posTexCoord = DirectX::XMFLOAT2(0.0f, 0.0f);
	m_score[DIGIT_SCORE].sizeTexCoord = DirectX::XMFLOAT2(1.0f, 1.0f);

	for (int i = 0; i < DIGIT_SCORE + 1; ++i)
	{
		m_add[i].size = DirectX::XMFLOAT2(m_pTexture[0]->GetWidth() / 6.5f, m_pTexture[0]->GetHeight() / 6.5f);
		m_add[i].pos = DirectX::XMFLOAT3(m_basePosX + i * m_add[i].size.x - (i *30.0f) - 30.0f, m_basePosY + 80.0f, 0.0f);
		m_add[i].posTexCoord = DirectX::XMFLOAT2(0.0f, 0.0f);
		m_add[i].sizeTexCoord = DirectX::XMFLOAT2(1.0f / (float)ANIM_SCORE_SPLIT_X, 1.0f / (float)ANIM_SCORE_SPLIT_Y);

		m_add[i].currentAnimNo = 0;
	}
	m_add[0].size = DirectX::XMFLOAT2(m_pTexture[0]->GetWidth() / 4.0f, m_pTexture[0]->GetHeight() / 4.0f);
	m_add[0].pos = DirectX::XMFLOAT3(m_basePosX - 40.0f, m_basePosY + 80.0f, 0.0f);
	






}


CUI::~CUI()
{
	for (int i = 0; i < MAX_UI; ++i)
	{
		if (m_pTexture)
		{
			delete m_pTexture[i];
			m_pTexture[i] = nullptr;
		}
	}

}

void CUI::Update()
{
	
}

void CUI::Draw()
{
	int Number = m_nScore;
	int Digit = 6;
	
	if (Number <= 0)
	{
		Digit = 5;
	}
		while (Number != 0)
		{
			Number = Number / 10;
			Digit--;
		}
		

	





	DirectX::XMFLOAT4X4 mat[3][DIGIT_SCORE + 1];

	DirectX::XMMATRIX world[DIGIT_SCORE + 1];

	for (int i = 0; i <= DIGIT_SCORE; ++i)
	{
		//ワールド行列はX,Yのみを考慮して作成

		world[i] = DirectX::XMMatrixTranslation(m_score[i].pos.x, m_score[i].pos.y, m_score[i].pos.z);
		DirectX::XMStoreFloat4x4(&mat[0][i], DirectX::XMMatrixTranspose(world[i]));

	}

	//ビュー行列は2dだとカメラの位置があまり関係ないので、単位行列を設定する
	DirectX::XMStoreFloat4x4(&mat[1][0], DirectX::XMMatrixIdentity());

	//プロジェクション行列は2dとして表示するための行列を設定する
	//この行列で2dスクリーンの大きさが決まる
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat[2][0], DirectX::XMMatrixTranspose(proj));






	//スプライトの設定

	Sprite::SetWorld(mat[0][6]);
	Sprite::SetView(mat[1][0]);
	Sprite::SetProjection(mat[2][0]);
	Sprite::SetSize(DirectX::XMFLOAT2(m_score[6].size.x * 0.70f, -m_score[6].size.y * 0.70f));
	Sprite::SetUVPos(DirectX::XMFLOAT2(m_score[6].posTexCoord.x, m_score[6].posTexCoord.y));
	Sprite::SetUVScale(DirectX::XMFLOAT2(m_score[6].sizeTexCoord.x, m_score[6].sizeTexCoord.y));
	Sprite::SetTexture(m_pTexture[1]);
	Sprite::Draw();
	for (int i = Digit; i < DIGIT_SCORE; ++i)
	{
		Sprite::SetWorld(mat[0][i]);
		Sprite::SetView(mat[1][0]);
		Sprite::SetProjection(mat[2][0]);
		Sprite::SetSize(DirectX::XMFLOAT2(m_score[i].size.x, -m_score[i].size.y));
		Sprite::SetUVPos(DirectX::XMFLOAT2(m_score[i].posTexCoord.x, m_score[i].posTexCoord.y));
		Sprite::SetUVScale(DirectX::XMFLOAT2(m_score[i].sizeTexCoord.x, m_score[i].sizeTexCoord.y));
		Sprite::SetTexture(m_pTexture[0]);
		Sprite::Draw();
	}
}

void CUI::DrawResult(int resultMoney)
{
	int temp = resultMoney;

	for (int i = DIGIT_SCORE - 1; 0 <= i; --i)
	{
		m_score[i].currentAnimNo = temp % 10;

		m_score[i].posTexCoord.x = m_score[i].sizeTexCoord.x * (m_score[i].currentAnimNo % ANIM_SCORE_SPLIT_X);
		m_score[i].posTexCoord.y = m_score[i].sizeTexCoord.y * (m_score[i].currentAnimNo / ANIM_SCORE_SPLIT_X);

		temp /= 10;
	}

	int Number = resultMoney;
	int Digit = 6;

	if (Number <= 0)
	{
		Digit = 5;
	}
	while (Number != 0)
	{
		Number = Number / 10;
		Digit--;
	}



	DirectX::XMFLOAT4X4 mat[3][DIGIT_SCORE + 1];

	DirectX::XMMATRIX world[DIGIT_SCORE + 1];

	for (int i = 0; i <= DIGIT_SCORE; ++i)
	{
		//ワールド行列はX,Yのみを考慮して作成

		world[i] = DirectX::XMMatrixTranslation(m_score[i].pos.x, m_score[i].pos.y, m_score[i].pos.z);
		DirectX::XMStoreFloat4x4(&mat[0][i], DirectX::XMMatrixTranspose(world[i]));

	}

	//ビュー行列は2dだとカメラの位置があまり関係ないので、単位行列を設定する
	DirectX::XMStoreFloat4x4(&mat[1][0], DirectX::XMMatrixIdentity());

	//プロジェクション行列は2dとして表示するための行列を設定する
	//この行列で2dスクリーンの大きさが決まる
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat[2][0], DirectX::XMMatrixTranspose(proj));

	Sprite::SetWorld(mat[0][6]);
	Sprite::SetView(mat[1][0]);
	Sprite::SetProjection(mat[2][0]);
	Sprite::SetSize(DirectX::XMFLOAT2(m_score[6].size.x * 0.70f, -m_score[6].size.y * 0.70f));
	Sprite::SetUVPos(DirectX::XMFLOAT2(m_score[6].posTexCoord.x, m_score[6].posTexCoord.y));
	Sprite::SetUVScale(DirectX::XMFLOAT2(m_score[6].sizeTexCoord.x, m_score[6].sizeTexCoord.y));
	Sprite::SetTexture(m_pTexture[1]);
	Sprite::Draw();
	for (int i = Digit; i < DIGIT_SCORE; ++i)
	{
		Sprite::SetWorld(mat[0][i]);
		Sprite::SetView(mat[1][0]);
		Sprite::SetProjection(mat[2][0]);
		Sprite::SetSize(DirectX::XMFLOAT2(m_score[i].size.x, -m_score[i].size.y));
		Sprite::SetUVPos(DirectX::XMFLOAT2(m_score[i].posTexCoord.x, m_score[i].posTexCoord.y));
		Sprite::SetUVScale(DirectX::XMFLOAT2(m_score[i].sizeTexCoord.x, m_score[i].sizeTexCoord.y));
		Sprite::SetTexture(m_pTexture[0]);
		Sprite::Draw();
	}
}

void CUI::AddMoney(int num)
{
	m_nAddMoney = num;
	m_nScore += num;

	//上限補正
	if (999999 < m_nScore)
	{
		m_nScore = 999999;
	}
	if (0 > m_nScore)
	{
		m_nScore = 0;
	}

	UpdateScoretexCoord();
	m_bAdd = true;
	m_fAlpha = 1.0f;
}

void CUI::UpdateScoretexCoord()
{


	for (int i = 0; i < DIGIT_SCORE + 1; ++i)
	{
		m_add[i].size = DirectX::XMFLOAT2(m_pTexture[0]->GetWidth() / 6.5f, m_pTexture[0]->GetHeight() / 6.5f);
		m_add[i].pos = DirectX::XMFLOAT3(m_basePosX + i * m_add[i].size.x - (i *30.0f) - 30.0f, m_basePosY + 80.0f, 0.0f);
		m_add[i].posTexCoord = DirectX::XMFLOAT2(0.0f, 0.0f);
		m_add[i].sizeTexCoord = DirectX::XMFLOAT2(1.0f / (float)ANIM_SCORE_SPLIT_X, 1.0f / (float)ANIM_SCORE_SPLIT_Y);

		m_add[i].currentAnimNo = 0;
	}



	int temp = m_nScore;
	int temp2 = m_nAddMoney;
	
	for (int i = DIGIT_SCORE - 1; 0 <= i; --i)
	{
		m_score[i].currentAnimNo = temp % 10;

		m_score[i].posTexCoord.x = m_score[i].sizeTexCoord.x * (m_score[i].currentAnimNo % ANIM_SCORE_SPLIT_X);
		m_score[i].posTexCoord.y = m_score[i].sizeTexCoord.y * (m_score[i].currentAnimNo / ANIM_SCORE_SPLIT_X);

		temp /= 10;
	}

	if (m_nAddMoney < 0)
	{
		m_add[0].currentAnimNo = 11;
		m_add[0].posTexCoord.x = m_add[0].sizeTexCoord.x * (m_add[0].currentAnimNo % ANIM_SCORE_SPLIT_X);
		m_add[0].posTexCoord.y = m_add[0].sizeTexCoord.y * (m_add[0].currentAnimNo / ANIM_SCORE_SPLIT_X);
		temp2 *= -1;
	}
	else
	{
		m_add[0].currentAnimNo = 12;
		m_add[0].posTexCoord.x = m_add[0].sizeTexCoord.x * (m_add[0].currentAnimNo % ANIM_SCORE_SPLIT_X);
		m_add[0].posTexCoord.y = m_add[0].sizeTexCoord.y * (m_add[0].currentAnimNo / ANIM_SCORE_SPLIT_X);
	}
	
	


	for (int i = DIGIT_SCORE; 1 <= i; --i)
	{
		m_add[i].currentAnimNo = temp2 % 10;
		m_add[i].posTexCoord.x = m_add[i].sizeTexCoord.x * (m_add[i].currentAnimNo % ANIM_SCORE_SPLIT_X);
		m_add[i].posTexCoord.y = m_add[i].sizeTexCoord.y * (m_add[i].currentAnimNo / ANIM_SCORE_SPLIT_X);

		temp2 /= 10;

	}
	
}

int CUI::GetMoney()
{
	return m_nScore;
}

void CUI::DrawAdd()
{
	UpdateScoretexCoord();
	m_fAlpha -= 1.0f / 180;
	if (m_fAlpha < 0.0f)
	{
		m_fAlpha = 0.0f;
	}
	m_temp = 0;

	

	for (int i = 1; i <= DIGIT_SCORE; ++i)
	{

		if (m_add[i].currentAnimNo == 0)
		{
			continue;
		}
		else
		{
			if (m_add[0].currentAnimNo == 11)
			{
				m_add[i - 1].currentAnimNo = 11;
				m_add[i - 1].posTexCoord.x = m_add[i - 1].sizeTexCoord.x * (m_add[i - 1].currentAnimNo % ANIM_SCORE_SPLIT_X);
				m_add[i - 1].posTexCoord.y = m_add[i - 1].sizeTexCoord.y * (m_add[i - 1].currentAnimNo / ANIM_SCORE_SPLIT_X);
				m_add[i - 1].pos.x -= 10.0f;
				/*m_add[i - 1].size = DirectX::XMFLOAT2(m_pTexture[0]->GetWidth() / 6.5f, m_pTexture[0]->GetHeight() / 6.5f);
				m_add[i - 1].pos = DirectX::XMFLOAT3(m_basePosX + i * m_add[i].size.x - (i *20.0f) - 60.0f, m_basePosY + 80.0f, 0.0f);*/
			}
			else
			{
				m_add[i - 1].currentAnimNo = 12;
				m_add[i - 1].posTexCoord.x = m_add[i - 1].sizeTexCoord.x * (m_add[i - 1].currentAnimNo % ANIM_SCORE_SPLIT_X);
				m_add[i - 1].posTexCoord.y = m_add[i - 1].sizeTexCoord.y * (m_add[i - 1].currentAnimNo / ANIM_SCORE_SPLIT_X);
				m_add[i - 1].pos.x -= 10.0f;
				/*m_add[i - 1].size = DirectX::XMFLOAT2(m_pTexture[0]->GetWidth() / 6.5f, m_pTexture[0]->GetHeight() / 6.5f);
				m_add[i - 1].pos = DirectX::XMFLOAT3(m_basePosX + (i-1) * m_add[i-1].size.x - ((i - 1) *20.0f), m_basePosY + 80.0f, 0.0f);*/

			}
			
		}
		m_temp = i - 1;
		break;
	}

	if (m_nAddMoney == 0)
	{
		m_add[5].currentAnimNo = 12;
		m_add[5].posTexCoord.x = m_add[5].sizeTexCoord.x * (m_add[5].currentAnimNo % ANIM_SCORE_SPLIT_X);
		m_add[5].posTexCoord.y = m_add[5].sizeTexCoord.y * (m_add[5].currentAnimNo / ANIM_SCORE_SPLIT_X);
		m_temp = 5;
	}


	DirectX::XMFLOAT4X4 mat[3][DIGIT_SCORE + 1];

	DirectX::XMMATRIX world[DIGIT_SCORE + 1];

	for (int i = 0; i <= DIGIT_SCORE; ++i)
	{
		//ワールド行列はX,Yのみを考慮して作成

		world[i] = DirectX::XMMatrixTranslation(m_add[i].pos.x, m_add[i].pos.y, m_add[i].pos.z);
		DirectX::XMStoreFloat4x4(&mat[0][i], DirectX::XMMatrixTranspose(world[i]));

	}

	//ビュー行列は2dだとカメラの位置があまり関係ないので、単位行列を設定する
	DirectX::XMStoreFloat4x4(&mat[1][0], DirectX::XMMatrixIdentity());

	//プロジェクション行列は2dとして表示するための行列を設定する
	//この行列で2dスクリーンの大きさが決まる
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat[2][0], DirectX::XMMatrixTranspose(proj));



	


	//スプライトの設定
		
	
			for (int j = m_temp; j <= DIGIT_SCORE; ++j)
			{
				Sprite::SetWorld(mat[0][j]);
				Sprite::SetView(mat[1][0]);
				Sprite::SetProjection(mat[2][0]);
				Sprite::SetSize(DirectX::XMFLOAT2(m_add[j].size.x, -m_add[j].size.y));
				Sprite::SetUVPos(DirectX::XMFLOAT2(m_add[j].posTexCoord.x, m_add[j].posTexCoord.y));
				Sprite::SetUVScale(DirectX::XMFLOAT2(m_add[j].sizeTexCoord.x, m_add[j].sizeTexCoord.y));
				Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, m_fAlpha));
				Sprite::SetTexture(m_pTexture[0]);
				Sprite::Draw();
			}
			
			
			
		


		/*for (int i = 0; i <= DIGIT_SCORE; ++i)
		{
			Sprite::SetWorld(mat[0][i]);
			Sprite::SetView(mat[1][0]);
			Sprite::SetProjection(mat[2][0]);
			Sprite::SetSize(DirectX::XMFLOAT2(m_add[i].size.x, -m_add[i].size.y));
			Sprite::SetUVPos(DirectX::XMFLOAT2(m_add[i].posTexCoord.x, m_add[i].posTexCoord.y));
			Sprite::SetUVScale(DirectX::XMFLOAT2(m_add[i].sizeTexCoord.x, m_add[i].sizeTexCoord.y));
			Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, m_fAlpha));
			Sprite::SetTexture(m_pTexture[0]);
			Sprite::Draw();
		}*/

	
	
}

void CUI::SetAdd(bool Add)
{
	m_bAdd = Add;
}

bool CUI::GetAdd()
{
	return m_bAdd;
}

CUI::CUI(int money)
	: m_Left(0.0f)
	, m_Right((float)SCREEN_WIDTH)
	, m_Bottom((float)SCREEN_HEIGHT)
	, m_Top(0.0f)
	, m_near(1.0f)
	, m_far(10.0f)
	, m_pTexture{ nullptr, nullptr, nullptr,nullptr,nullptr }
	, m_bAdd(false)
	, m_fAlpha(1.0f)
{
	for (int i = 0; i < MAX_UI; ++i)
	{
		m_pTexture[i] = new Texture();
	}

	if (FAILED(m_pTexture[0]->Create("Assets/Texture/UI_number4.png")))
	{
		MessageBox(NULL, "UI UI_number4.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[1]->Create("Assets/Texture/UI_Money2.png")))
	{
		MessageBox(NULL, "UI UI_Money2.png", "Error", MB_OK);
	}


	m_basePosX = 1050.0f;
	m_basePosY = 70.0f;
	m_nScore = 0;

	//数字
	for (int i = 0; i < DIGIT_SCORE; ++i)
	{
		m_score[i].size = DirectX::XMFLOAT2(m_pTexture[0]->GetWidth() / 6.5f, m_pTexture[0]->GetHeight() / 6.5f);
		m_score[i].pos = DirectX::XMFLOAT3(m_basePosX + i * m_score[i].size.x - (i *30.0f), m_basePosY + 5.0f, 0.0f);
		m_score[i].posTexCoord = DirectX::XMFLOAT2(0.0f, 0.0f);
		m_score[i].sizeTexCoord = DirectX::XMFLOAT2(1.0f / (float)ANIM_SCORE_SPLIT_X, 1.0f / (float)ANIM_SCORE_SPLIT_Y);

		m_score[i].frame = 0;
		m_score[i].currentAnimNo = 0;
	}

	//フレーム
	m_score[DIGIT_SCORE].size = DirectX::XMFLOAT2((float)m_pTexture[1]->GetWidth(), (float)m_pTexture[1]->GetHeight());
	//m_score[DIGIT_SCORE].size = DirectX::XMFLOAT2(330.0f, 150.0f);
	m_score[DIGIT_SCORE].pos = DirectX::XMFLOAT3(m_basePosX + 50.0f, m_basePosY + 5.0f, 0.0f);
	m_score[DIGIT_SCORE].posTexCoord = DirectX::XMFLOAT2(0.0f, 0.0f);
	m_score[DIGIT_SCORE].sizeTexCoord = DirectX::XMFLOAT2(1.0f, 1.0f);

	for (int i = 0; i < DIGIT_SCORE + 1; ++i)
	{
		m_add[i].size = DirectX::XMFLOAT2(m_pTexture[0]->GetWidth() / 6.5f, m_pTexture[0]->GetHeight() / 6.5f);
		m_add[i].pos = DirectX::XMFLOAT3(m_basePosX + i * m_add[i].size.x - (i *30.0f) - 30.0f, m_basePosY + 80.0f, 0.0f);
		m_add[i].posTexCoord = DirectX::XMFLOAT2(0.0f, 0.0f);
		m_add[i].sizeTexCoord = DirectX::XMFLOAT2(1.0f / (float)ANIM_SCORE_SPLIT_X, 1.0f / (float)ANIM_SCORE_SPLIT_Y);

		m_add[i].currentAnimNo = 0;
	}
	m_add[0].size = DirectX::XMFLOAT2(m_pTexture[0]->GetWidth() / 4.0f, m_pTexture[0]->GetHeight() / 4.0f);
	m_add[0].pos = DirectX::XMFLOAT3(m_basePosX - 40.0f, m_basePosY + 80.0f, 0.0f);






	m_nScore = money;
	UpdateScoretexCoord();
}

