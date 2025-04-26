#include "Select_Score.h"

SelectScore::SelectScore()
	: m_Left(0.0f)
	, m_Right((float)SCREEN_WIDTH)
	, m_Bottom((float)SCREEN_HEIGHT)
	, m_Top(0.0f)
	, m_near(1.0f)
	, m_far(10.0f)
	, m_pTexture{ nullptr, nullptr, nullptr , nullptr}
	, m_cleartime(0)
	, m_starNum(0)
	, m_nper(0)
	, m_hyphenPos(0.0f, 0.0f)
	, m_hyphenSize(0.0f, 0.0f)
{
	//テクスチャ
	for (int i = 0; i < 4; ++i)
	{
		m_pTexture[i] = new Texture;
	}
	if (FAILED(m_pTexture[0]->Create("Assets/texture/UI_ResultNumber.png")))
	{
		MessageBox(NULL, "ResultTime UI_ResultNumber.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[1]->Create("Assets/texture/UI_star.png")))
	{
		MessageBox(NULL, "ResultTime UI_star.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[2]->Create("Assets/texture/UI_ResultNumber.png")))
	{
		MessageBox(NULL, "ResultTime UI_ResultNumber.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[3]->Create("Assets/Texture/UI_hyphen.png")))
	{
		MessageBox(NULL, "Select UI_hyphen.png", "Error", MB_OK);
	}

	//クリアタイム
	for (int i = 0; i < 4; ++i)
	{
		m_time[i].size = DirectX::XMFLOAT2(50.0f, 50.0f);
		m_time[i].pos = DirectX::XMFLOAT3(1000.0f + (i * m_time[i].size.x) - (i * 10.0f), 270.0f, 0.0f);
		m_time[i].posTexCoord = DirectX::XMFLOAT2(0.0f, 0.0f);
		m_time[i].sizeTexCoord = DirectX::XMFLOAT2(1.0f / (float)ANIM_TIME_SPLIT_X, 1.0f / (float)ANIM_TIME_SPLIT_Y);
		m_time[i].currentAnimNo = 0;
	}

	//星
	for (int i = 0; i < 3; ++i)
	{
		m_starSize[i] = DirectX::XMFLOAT2(110.0f, 110.0f);
		m_starPos[i] = DirectX::XMFLOAT3(900.0f + i * 100.0f, 100.0f, 0.0f);
	}

	m_starPos[0] = DirectX::XMFLOAT3(890.0f, 110.0f, 0.0f);
	m_starPos[2] = DirectX::XMFLOAT3(1110.0f, 110.0f, 0.0f);

	//パーセント
	for (int i = 0; i < 3; ++i)
	{
		m_per[i].size = DirectX::XMFLOAT2(50.0f, 50.0f);
		m_per[i].pos = DirectX::XMFLOAT3(990.0f + (i * m_per[i].size.x) - (i * 10.0f), 200.0f, 0.0f);
		m_per[i].posTexCoord = DirectX::XMFLOAT2(0.0f, 0.0f);
		m_per[i].sizeTexCoord = DirectX::XMFLOAT2(1.0f / (float)ANIM_TIME_SPLIT_X, 1.0f / (float)ANIM_TIME_SPLIT_Y);
		m_per[i].currentAnimNo = 0;
	}

	m_hyphenPos = DirectX::XMFLOAT2(1000.0f, 270.0f);
	m_hyphenSize = DirectX::XMFLOAT2(m_pTexture[3]->GetWidth() * 0.1f, m_pTexture[3]->GetHeight()*0.1f);
	
}

SelectScore::~SelectScore()
{
	for (int i = 0; i < 4; ++i)
	{
		if (m_pTexture[i])
		{
			delete m_pTexture[i];
			m_pTexture[i] = nullptr;
		}
	}
}

void SelectScore::Update(int * score, int * time, int select)
{
	

	if (select == 0)
	{
		if (time[0] != 999)
		{
			
			m_cleartime = time[0];
			
		}
		else
		{
			m_cleartime = 0;
		}

		if (score[0] >= 60 && score[0] < 80)
		{
			m_starNum = 1;
		}
		else if(score[0] >= 80 && score[0] < 100)
		{
			m_starNum = 2;
		}
		else if(score[0] == 100)
		{
			m_starNum = 3;
		}
		else if (score[0] < 60)
		{
			m_starNum = 0;
		}

		m_nper = score[0];
	}
	else if (select == 1)
	{
		if (time[1] != 999)
		{
			m_cleartime = time[1];
		}
		else
		{
			m_cleartime = 0;
		}

		if (score[1] >= 60 && score[1] < 80)
		{
			m_starNum = 1;
		}
		else if (score[1] >= 80 && score[1] < 100)
		{
			m_starNum = 2;
		}
		else if (score[1] == 100)
		{
			m_starNum = 3;
		}
		else if (score[1] < 60)
		{
			m_starNum = 0;
		}

		m_nper = score[1];
	}
	else if(select == 2)
	{
		if (time[2] != 999)
		{
			m_cleartime = time[2];
		}
		else
		{
			m_cleartime = 0;
		}

		if (score[2] >= 60 && score[2] < 80)
		{
			m_starNum = 1;
		}
		else if (score[2] >= 80 && score[2] < 100)
		{
			m_starNum = 2;
		}
		else if (score[2] == 100)
		{
			m_starNum = 3;
		}
		else if (score[2] < 60)
		{
			m_starNum = 0;
		}

		m_nper = score[2];
	}

	

	m_nTimeMinutes = m_cleartime / 60;
	m_nTimeSeconds = m_cleartime - (60 * m_nTimeMinutes);
	m_time[0].currentAnimNo = m_nTimeMinutes;
	m_time[0].posTexCoord.x = m_time[0].sizeTexCoord.x * (m_time[0].currentAnimNo % ANIM_TIME_SPLIT_X);
	m_time[0].posTexCoord.y = m_time[0].sizeTexCoord.y * (m_time[0].currentAnimNo / ANIM_TIME_SPLIT_X);
	int temp = m_nTimeSeconds;

	for (int i = 3; 2 <= i; --i)
	{
		
		m_time[i].currentAnimNo = temp % 10;
		m_time[i].posTexCoord.x = m_time[i].sizeTexCoord.x * (m_time[i].currentAnimNo % ANIM_TIME_SPLIT_X);
		m_time[i].posTexCoord.y = m_time[i].sizeTexCoord.y * (m_time[i].currentAnimNo / ANIM_TIME_SPLIT_X);
		temp /= 10;
	}

	//パーセント
	
	for (int i = 2; 0 <= i; --i)
	{
		m_per[i].currentAnimNo = m_nper % 10;

		m_per[i].posTexCoord.x = m_per[i].sizeTexCoord.x * (m_per[i].currentAnimNo % ANIM_TIME_SPLIT_X);
		m_per[i].posTexCoord.y = m_per[i].sizeTexCoord.y * (m_per[i].currentAnimNo / ANIM_TIME_SPLIT_X);

		m_nper /= 10;
	}
	


}

void SelectScore::Draw()
{
	DirectX::XMFLOAT4X4 mat[3][4];
	DirectX::XMMATRIX world[4];

	for (int i = 0; i < 4; ++i)
	{
		
		
		world[i] = DirectX::XMMatrixTranslation(m_time[i].pos.x, m_time[i].pos.y, m_time[i].pos.z);
		DirectX::XMStoreFloat4x4(&mat[0][i], DirectX::XMMatrixTranspose(world[i]));

	}

	//ビュー行列は2dだとカメラの位置があまり関係ないので、単位行列を設定する
	DirectX::XMStoreFloat4x4(&mat[1][0], DirectX::XMMatrixIdentity());

	//プロジェクション行列は2dとして表示するための行列を設定する
	//この行列で2dスクリーンの大きさが決まる
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat[2][0], DirectX::XMMatrixTranspose(proj));

	if (m_cleartime != 0 && m_starNum >= 3)
	{
		//分表記
		Sprite::SetWorld(mat[0][0]);
		Sprite::SetView(mat[1][0]);
		Sprite::SetProjection(mat[2][0]);
		Sprite::SetSize(DirectX::XMFLOAT2(m_time[0].size.x, -m_time[0].size.y));
		Sprite::SetUVPos(DirectX::XMFLOAT2(m_time[0].posTexCoord.x, m_time[0].posTexCoord.y));
		Sprite::SetUVScale(DirectX::XMFLOAT2(m_time[0].sizeTexCoord.x, m_time[0].sizeTexCoord.y));
		Sprite::SetTexture(m_pTexture[0]);
		Sprite::Draw();
		//:表記
		Sprite::SetWorld(mat[0][1]);
		Sprite::SetView(mat[1][0]);
		Sprite::SetProjection(mat[2][0]);
		Sprite::SetSize(DirectX::XMFLOAT2(m_time[1].size.x, -m_time[1].size.y));
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.5f, 0.66f));
		Sprite::SetUVScale(DirectX::XMFLOAT2(0.25f, 0.33f));
		Sprite::SetTexture(m_pTexture[0]);
		Sprite::Draw();

		//秒表記
		for (int i = 2; i < 4; ++i)
		{
			Sprite::SetWorld(mat[0][i]);
			Sprite::SetView(mat[1][0]);
			Sprite::SetProjection(mat[2][0]);
			Sprite::SetSize(DirectX::XMFLOAT2(m_time[i].size.x, -m_time[i].size.y));
			Sprite::SetUVPos(DirectX::XMFLOAT2(m_time[i].posTexCoord.x, m_time[i].posTexCoord.y));
			Sprite::SetUVScale(DirectX::XMFLOAT2(m_time[i].sizeTexCoord.x, m_time[i].sizeTexCoord.y));
			Sprite::SetTexture(m_pTexture[0]);
			Sprite::Draw();
		}
	}
	else
	{
		//ハイフン
		Sprite::SetWorld(mat[0][2]);
		Sprite::SetView(mat[1][0]);
		Sprite::SetProjection(mat[2][0]);
		Sprite::SetSize(DirectX::XMFLOAT2(m_hyphenSize.x, -m_hyphenSize.y));
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
		Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
		Sprite::SetTexture(m_pTexture[3]);
		Sprite::Draw();
	}



	//星
	DirectX::XMFLOAT4X4 mat2[3][3];
	DirectX::XMMATRIX world2[3];

	

	for (int i = 0; i < 3; ++i)
	{
		DirectX::XMMATRIX T  = DirectX::XMMatrixTranslation(m_starPos[i].x, m_starPos[i].y, m_starPos[i].z);
		DirectX::XMMATRIX R = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(355.0f + i * 5.0f));
		world2[i] = R * T;
		DirectX::XMStoreFloat4x4(&mat2[0][i], DirectX::XMMatrixTranspose(world2[i]));

	}

	//ビュー行列は2dだとカメラの位置があまり関係ないので、単位行列を設定する
	DirectX::XMStoreFloat4x4(&mat2[1][0], DirectX::XMMatrixIdentity());

	//プロジェクション行列は2dとして表示するための行列を設定する
	//この行列で2dスクリーンの大きさが決まる
	//DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat2[2][0], DirectX::XMMatrixTranspose(proj));

	for (int i = 0; i < m_starNum; ++i)
	{
		Sprite::SetWorld(mat2[0][i]);
		Sprite::SetView(mat2[1][0]);
		Sprite::SetProjection(mat2[2][0]);
		Sprite::SetSize(DirectX::XMFLOAT2(m_starSize[i].x, -m_starSize[i].y));
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
		Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
		Sprite::SetTexture(m_pTexture[1]);
		Sprite::Draw();
	}

	//パーセント
	DirectX::XMFLOAT4X4 mat3[3][3];
	DirectX::XMMATRIX world3[3];



	for (int i = 0; i < 3; ++i)
	{
		world3[i] = DirectX::XMMatrixTranslation(m_per[i].pos.x, m_per[i].pos.y, 0.0f);
		DirectX::XMStoreFloat4x4(&mat3[0][i], DirectX::XMMatrixTranspose(world3[i]));

	}

	//ビュー行列は2dだとカメラの位置があまり関係ないので、単位行列を設定する
	DirectX::XMStoreFloat4x4(&mat3[1][0], DirectX::XMMatrixIdentity());

	//プロジェクション行列は2dとして表示するための行列を設定する
	//この行列で2dスクリーンの大きさが決まる
	//DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat3[2][0], DirectX::XMMatrixTranspose(proj));

	for (int i = 0; i < 3; ++i)
	{
		if (m_per[0].currentAnimNo != 0)
		{
			Sprite::SetWorld(mat3[0][i]);
			Sprite::SetView(mat3[1][0]);
			Sprite::SetProjection(mat3[2][0]);
			Sprite::SetSize(DirectX::XMFLOAT2(m_per[i].size.x, -m_per[i].size.y));
			Sprite::SetUVPos(DirectX::XMFLOAT2(m_per[i].posTexCoord.x, m_per[i].posTexCoord.y));
			Sprite::SetUVScale(DirectX::XMFLOAT2(m_per[i].sizeTexCoord.x, m_per[i].sizeTexCoord.y));
			Sprite::SetTexture(m_pTexture[2]);
			Sprite::Draw();
		}
		else
		{
			if (m_per[1].currentAnimNo != 0)
			{
				Sprite::SetWorld(mat3[0][i + 1]);
				Sprite::SetView(mat3[1][0]);
				Sprite::SetProjection(mat3[2][0]);
				Sprite::SetSize(DirectX::XMFLOAT2(m_per[i + 1].size.x, -m_per[i + 1].size.y));
				Sprite::SetUVPos(DirectX::XMFLOAT2(m_per[i + 1].posTexCoord.x, m_per[i + 1].posTexCoord.y));
				Sprite::SetUVScale(DirectX::XMFLOAT2(m_per[i + 1].sizeTexCoord.x, m_per[i + 1].sizeTexCoord.y));
				Sprite::SetTexture(m_pTexture[2]);
				Sprite::Draw();
			}
			else
			{
				Sprite::SetWorld(mat3[0][i + 2]);
				Sprite::SetView(mat3[1][0]);
				Sprite::SetProjection(mat3[2][0]);
				Sprite::SetSize(DirectX::XMFLOAT2(m_per[i + 2].size.x, -m_per[i + 2].size.y));
				Sprite::SetUVPos(DirectX::XMFLOAT2(m_per[i + 2].posTexCoord.x, m_per[i + 2].posTexCoord.y));
				Sprite::SetUVScale(DirectX::XMFLOAT2(m_per[i + 2].sizeTexCoord.x, m_per[i + 2].sizeTexCoord.y));
				Sprite::SetTexture(m_pTexture[2]);
				Sprite::Draw();
			}
		}
	}

}
