#include "Result_Time.h"

ResultTime::ResultTime(float PosX, float PosY, float PosZ, float radian)
	: m_Left(0.0f)
	, m_Right((float)SCREEN_WIDTH)
	, m_Bottom((float)SCREEN_HEIGHT)
	, m_Top(0.0f)
	, m_near(1.0f)
	, m_far(10.0f)
	, m_pTexture{ nullptr, nullptr }
	, m_ntemp(0.0f)
	, m_nTimeMinutes(0)
	, m_nTimeSeconds(0)
{
	for (int i = 0; i < DIGIT_TIME; ++i)
	{
		time[i].size = DirectX::XMFLOAT2(60.0f, 60.0f);
		time[i].pos = DirectX::XMFLOAT3(PosX + (i * time[i].size.x) - (i * 10.0f), PosY - (i * 5.0f), PosZ);
		time[i].radian = radian;
		time[i].posTexCoord = DirectX::XMFLOAT2(0.0f, 0.0f);
		time[i].sizeTexCoord = DirectX::XMFLOAT2(1.0f / (float)ANIM_TIME_SPLIT_X, 1.0f / (float)ANIM_TIME_SPLIT_Y);
		time[i].currentAnimNo = 0;
	}

	for (int i = 0; i < 2; ++i)
	{
		m_pTexture[i] = new Texture;
	}

	if (FAILED(m_pTexture[0]->Create("Assets/texture/UI_ResultNumber.png")))
	{
		MessageBox(NULL, "ResultTime UI_ResultNumber.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[1]->Create("Assets/texture/UI_hyphen.png")))
	{
		MessageBox(NULL, "ResultTime UI_hyphen.png", "Error", MB_OK);
	}
}

ResultTime::~ResultTime()
{
	for (int i = 0; i < 2; ++i)
	{
		if (m_pTexture[i])
		{
			delete m_pTexture[i];
			m_pTexture[i] = nullptr;
		}
	}
}

void ResultTime::Update(int Time)
{
	int nTime = Time;

	m_nTimeMinutes = nTime / 60;
	m_nTimeSeconds = nTime - (60 * m_nTimeMinutes);
	m_ntemp = m_nTimeSeconds;
	time[0].currentAnimNo = m_nTimeMinutes;
	time[0].posTexCoord.x = time[0].sizeTexCoord.x * (time[0].currentAnimNo % ANIM_TIME_SPLIT_X);
	time[0].posTexCoord.y = time[0].sizeTexCoord.y * (time[0].currentAnimNo / ANIM_TIME_SPLIT_X);


	for (int i = DIGIT_TIME - 1; 2 <= i; --i)
	{
		time[i].currentAnimNo = m_ntemp % 10;

		time[i].posTexCoord.x = time[i].sizeTexCoord.x * (time[i].currentAnimNo % ANIM_TIME_SPLIT_X);
		time[i].posTexCoord.y = time[i].sizeTexCoord.y * (time[i].currentAnimNo / ANIM_TIME_SPLIT_X);

		m_ntemp /= 10;
	}

}

void ResultTime::Draw()
{
	DirectX::XMFLOAT4X4 mat[3][DIGIT_TIME];
	DirectX::XMMATRIX world[DIGIT_TIME];

	DirectX::XMMATRIX T[DIGIT_TIME];
	DirectX::XMMATRIX R[DIGIT_TIME];

	for (int i = 0; i < DIGIT_TIME; ++i)
	{
		T[i] = DirectX::XMMatrixTranslation(time[i].pos.x, time[i].pos.y, time[i].pos.z);
		R[i] = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(time[i].radian));
		world[i] = R[i] * T[i];
		DirectX::XMStoreFloat4x4(&mat[0][i], DirectX::XMMatrixTranspose(world[i]));

	}
	
	//ビュー行列は2dだとカメラの位置があまり関係ないので、単位行列を設定する
	DirectX::XMStoreFloat4x4(&mat[1][0], DirectX::XMMatrixIdentity());

	//プロジェクション行列は2dとして表示するための行列を設定する
	//この行列で2dスクリーンの大きさが決まる
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat[2][0], DirectX::XMMatrixTranspose(proj));

	//分表記
	Sprite::SetWorld(mat[0][0]);
	Sprite::SetView(mat[1][0]);
	Sprite::SetProjection(mat[2][0]);
	Sprite::SetSize(DirectX::XMFLOAT2(time[0].size.x, -time[0].size.y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(time[0].posTexCoord.x, time[0].posTexCoord.y));
	Sprite::SetUVScale(DirectX::XMFLOAT2(time[0].sizeTexCoord.x, time[0].sizeTexCoord.y));
	Sprite::SetTexture(m_pTexture[0]);
	Sprite::Draw();
	//:表記
	Sprite::SetWorld(mat[0][1]);
	Sprite::SetView(mat[1][0]);
	Sprite::SetProjection(mat[2][0]);
	Sprite::SetSize(DirectX::XMFLOAT2(time[1].size.x, -time[1].size.y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.5f, 0.66f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(0.25f, 0.33f));
	Sprite::SetTexture(m_pTexture[0]);
	Sprite::Draw();

	//秒表記
	for (int i = 2; i < DIGIT_TIME; ++i)
	{
		Sprite::SetWorld(mat[0][i]);
		Sprite::SetView(mat[1][0]);
		Sprite::SetProjection(mat[2][0]);
		Sprite::SetSize(DirectX::XMFLOAT2(time[i].size.x, -time[i].size.y));
		Sprite::SetUVPos(DirectX::XMFLOAT2(time[i].posTexCoord.x, time[i].posTexCoord.y));
		Sprite::SetUVScale(DirectX::XMFLOAT2(time[i].sizeTexCoord.x, time[i].sizeTexCoord.y));
		Sprite::SetTexture(m_pTexture[0]);
		Sprite::Draw();
	}
}

void ResultTime::DrawTimeUp()
{
	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMMATRIX world;

	DirectX::XMMATRIX T;
	DirectX::XMMATRIX R;

	T = DirectX::XMMatrixTranslation(time[1].pos.x + 20.0f, time[1].pos.y, time[1].pos.z);
	R = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(time[1].radian));
	world = R * T;
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));

	

	//ビュー行列は2dだとカメラの位置があまり関係ないので、単位行列を設定する
	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());

	//プロジェクション行列は2dとして表示するための行列を設定する
	//この行列で2dスクリーンの大きさが決まる
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));
	
	
	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(200.0f, -200.0f));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[1]);
	Sprite::Draw();
}
