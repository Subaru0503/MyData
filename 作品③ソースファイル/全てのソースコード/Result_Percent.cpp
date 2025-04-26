#include "Result_Percent.h"

ResultPer::ResultPer(float PosX, float PosY, float PosZ, float radian, int Per)
	: m_Left(0.0f)
	, m_Right((float)SCREEN_WIDTH)
	, m_Bottom((float)SCREEN_HEIGHT)
	, m_Top(0.0f)
	, m_near(1.0f)
	, m_far(10.0f)
	, m_pTexture(nullptr)
{
	for (int i = 0; i < DIGIT_NUMBER; ++i)
	{
		
		per[i].size = DirectX::XMFLOAT2(60.0f, 60.0f);
		per[i].pos = DirectX::XMFLOAT3(PosX + (i * per[i].size.x) - (i * 15.0f), PosY - (i * 5.0f), PosZ);
		per[i].radian = radian;
		per[i].posTexCoord = DirectX::XMFLOAT2(0.0f, 0.0f);
		per[i].sizeTexCoord = DirectX::XMFLOAT2(1.0f / (float)ANIM_NUMBER_SPLIT_X, 1.0f / (float)ANIM_NUMBER_SPLIT_Y);
		per[i].currentAnimNo = 0;
	}
	per[3].currentAnimNo = 11;
	

	m_pTexture = new Texture();
	if (FAILED(m_pTexture->Create("Assets/texture/UI_ResultNumber.png")))
	{
		MessageBox(NULL, "ResultPer UI_ResultNumber.png", "Error", MB_OK);
	}
}

ResultPer::~ResultPer()
{
	if (m_pTexture)
	{
		delete m_pTexture;
		m_pTexture = nullptr;
	}
}

void ResultPer::Update(int Per)
{
	m_ntemp = Per;

	for (int i = DIGIT_NUMBER - 2; 0 <= i; --i)
	{
		per[i].currentAnimNo = m_ntemp % 10;

		per[i].posTexCoord.x = per[i].sizeTexCoord.x * (per[i].currentAnimNo % ANIM_NUMBER_SPLIT_X);
		per[i].posTexCoord.y = per[i].sizeTexCoord.y * (per[i].currentAnimNo / ANIM_NUMBER_SPLIT_X);

		m_ntemp /= 10;
	}
	per[3].posTexCoord.x = per[3].sizeTexCoord.x * (per[3].currentAnimNo % ANIM_NUMBER_SPLIT_X);
	per[3].posTexCoord.y = per[3].sizeTexCoord.y * (per[3].currentAnimNo / ANIM_NUMBER_SPLIT_X);
}

void ResultPer::Draw()
{
	DirectX::XMFLOAT4X4 mat[3][DIGIT_NUMBER];
	DirectX::XMMATRIX world[DIGIT_NUMBER];
	DirectX::XMMATRIX T[DIGIT_NUMBER];
	DirectX::XMMATRIX R[DIGIT_NUMBER];
	for (int i = 0; i < DIGIT_NUMBER; ++i)
	{
		T[i] = DirectX::XMMatrixTranslation(per[i].pos.x, per[i].pos.y, per[i].pos.z);
		R[i] = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(per[i].radian));
		world[i] = R[i] * T[i];
		DirectX::XMStoreFloat4x4(&mat[0][i], DirectX::XMMatrixTranspose(world[i]));
	}

	//ビュー行列は2dだとカメラの位置があまり関係ないので、単位行列を設定する
	DirectX::XMStoreFloat4x4(&mat[1][0], DirectX::XMMatrixIdentity());

	//プロジェクション行列は2dとして表示するための行列を設定する
	//この行列で2dスクリーンの大きさが決まる
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat[2][0], DirectX::XMMatrixTranspose(proj));

	for (int i = 0; i < DIGIT_NUMBER; ++i)
	{
		if (per[0].currentAnimNo != 0)
		{
			Sprite::SetWorld(mat[0][i]);
			Sprite::SetView(mat[1][0]);
			Sprite::SetProjection(mat[2][0]);
			Sprite::SetSize(DirectX::XMFLOAT2(per[i].size.x, -per[i].size.y));
			Sprite::SetUVPos(DirectX::XMFLOAT2(per[i].posTexCoord.x, per[i].posTexCoord.y));
			Sprite::SetUVScale(DirectX::XMFLOAT2(per[i].sizeTexCoord.x, per[i].sizeTexCoord.y));
			Sprite::SetTexture(m_pTexture);
			Sprite::Draw();
		}
		else
		{
			if (per[1].currentAnimNo != 0)
			{
				Sprite::SetWorld(mat[0][i + 1]);
				Sprite::SetView(mat[1][0]);
				Sprite::SetProjection(mat[2][0]);
				Sprite::SetSize(DirectX::XMFLOAT2(per[i + 1].size.x, -per[i + 1].size.y));
				Sprite::SetUVPos(DirectX::XMFLOAT2(per[i + 1].posTexCoord.x, per[i + 1].posTexCoord.y));
				Sprite::SetUVScale(DirectX::XMFLOAT2(per[i + 1].sizeTexCoord.x, per[i + 1].sizeTexCoord.y));
				Sprite::SetTexture(m_pTexture);
				Sprite::Draw();
			}
			else
			{
				Sprite::SetWorld(mat[0][i + 2]);
				Sprite::SetView(mat[1][0]);
				Sprite::SetProjection(mat[2][0]);
				Sprite::SetSize(DirectX::XMFLOAT2(per[i + 2].size.x, -per[i + 2].size.y));
				Sprite::SetUVPos(DirectX::XMFLOAT2(per[i + 2].posTexCoord.x, per[i + 2].posTexCoord.y));
				Sprite::SetUVScale(DirectX::XMFLOAT2(per[i + 2].sizeTexCoord.x, per[i + 2].sizeTexCoord.y));
				Sprite::SetTexture(m_pTexture);
				Sprite::Draw();


				Sprite::SetWorld(mat[0][i + 3]);
				Sprite::SetView(mat[1][0]);
				Sprite::SetProjection(mat[2][0]);
				Sprite::SetSize(DirectX::XMFLOAT2(per[i + 3].size.x, -per[i + 3].size.y));
				Sprite::SetUVPos(DirectX::XMFLOAT2(per[i + 3].posTexCoord.x, per[i + 3].posTexCoord.y));
				Sprite::SetUVScale(DirectX::XMFLOAT2(per[i + 3].sizeTexCoord.x, per[i + 3].sizeTexCoord.y));
				Sprite::SetTexture(m_pTexture);
				Sprite::Draw();
			}
			
		}

			
		
	
	}
}
