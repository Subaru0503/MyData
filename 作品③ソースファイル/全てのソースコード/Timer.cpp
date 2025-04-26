//Timer.cpp
//=====インクルード部=====
#include "Timer.h"
#include "Startup.h"
#include "Main.h"
#include "Input.h"

//----定数・マクロ定義----
#define TIMER_STRETCH (2)	// 延長時間

//=====コンストラクタ=====
CTimer::CTimer(int TimeLimit)
	: m_Left(0.0f)
	, m_Right((float)SCREEN_WIDTH)
	, m_Bottom((float)SCREEN_HEIGHT)
	, m_Top(0.0f)
	, m_near(1.0f)
	, m_far(10.0f)
	, m_pTexture{ nullptr, nullptr }
	, m_nTime(0)		//経過時間
	, m_nTimeLimit(0)	//制限時間
	, m_nTimeMinutes(3)	//時間（分）
	, m_nTimeSeconds(0)	//時間(秒)
	, m_ftemp(0.0f)
	, m_fRadian(0.0f)
	, m_bResult(true)
	, m_nMaxTime(MAX_TIME)
	, m_nTimer(0)
{
	m_ftemp = (float)m_nTimeLimit;//制限時間を退避


	m_basePosX[0] = 560.0f;
	m_basePosY[0] = 70.0f;
	m_basePosX[1] = 630.0f;
	m_basePosY[1] = 70.0f;


	for (int i = 0; i < 2; ++i)
	{
		m_pTexture[i] = new Texture();
	}

	if (FAILED(m_pTexture[0]->Create("Assets/Texture/UI_number4.png")))
	{
		MessageBox(NULL, "Timer UI_number4.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[1]->Create("Assets/Texture/UI_TimerFrame.png")))
	{
		MessageBox(NULL, "Timer UI_TimerFrame.png", "Error", MB_OK);
	}

	//タイマー数字設定
	for (int i = 0; i < DIGIT_TIME; ++i)
	{
		m_time[i].size = DirectX::XMFLOAT2(m_pTexture[0]->GetWidth() / 6.5f, m_pTexture[0]->GetHeight() / 6.5f);
		m_time[i].pos = DirectX::XMFLOAT3(m_basePosX[0] + i * m_time[i].size.x - (i * 10.0f), m_basePosY[0], 0.0f);
		m_time[i].posTexCoord = DirectX::XMFLOAT2(0.0f, 0.0f);
		m_time[i].sizeTexCoord = DirectX::XMFLOAT2(1.0f / (float)ANIM_TIME_SPLIT_X, 1.0f / (float)ANIM_TIME_SPLIT_Y);

		m_time[i].frame = 0;
		m_time[i].currentAnimNo = 0;
	}

	//タイマーフレーム
	m_timer.size = DirectX::XMFLOAT2((float)(m_pTexture[1]->GetWidth() * 1.2f), (float)(m_pTexture[1]->GetHeight() * 1.2f));
	m_timer.pos = DirectX::XMFLOAT3(m_basePosX[1], m_basePosY[1], 0.0f);


	m_nTimeLimit = TimeLimit;
	m_nMaxTime = TimeLimit;



}

//=====デストラクタ=====
CTimer::~CTimer()
{

	for (int i = 0; i < 2; ++i)
	{
		if (m_pTexture)
		{
			delete m_pTexture[i];
			m_pTexture[i] = nullptr;
		}
	}

}

//=====更新処理=====
void CTimer::Update()
{
	//----アイテムが使用されてたら----
	if (m_nTimer)
	{
		m_nTimeLimit += TIMER_STRETCH * 60;	// 秒に直して格納
		m_nTimeMinutes += TIMER_STRETCH;		// 延長分追加
		m_nTimer = 0;						// フラグ下げ
		m_nMaxTime = m_nTimeLimit;
	}

	m_nTime++;


	int temp = m_nTimeSeconds;
	if (!(m_nTime % 60))
	{
		m_nTimeLimit -= 1;


	}

	//タイマー数字更新
	m_nTimeMinutes = m_nTimeLimit / 60;		//分を取得
	m_nTimeSeconds = m_nTimeLimit - (60 * m_nTimeMinutes);	//秒を取得

	if (m_nTimeLimit <= 0)	//０になったら止める
	{
		//m_nTimeLimit = 0;
		m_nTimeMinutes = 0;
		m_nTimeSeconds = 0;

	}

	//分の更新
	m_time[0].currentAnimNo = m_nTimeMinutes;
	m_time[0].posTexCoord.x = m_time[0].sizeTexCoord.x * (m_time[0].currentAnimNo % ANIM_TIME_SPLIT_X);
	m_time[0].posTexCoord.y = m_time[0].sizeTexCoord.y * (m_time[0].currentAnimNo / ANIM_TIME_SPLIT_X);

	//秒の更新
	for (int i = DIGIT_TIME - 1; 2 <= i; --i)
	{
		m_time[i].currentAnimNo = temp % 10;

		m_time[i].posTexCoord.x = m_time[i].sizeTexCoord.x * (m_time[i].currentAnimNo % ANIM_TIME_SPLIT_X);
		m_time[i].posTexCoord.y = m_time[i].sizeTexCoord.y * (m_time[i].currentAnimNo / ANIM_TIME_SPLIT_X);

		temp /= 10;
	}






}

void CTimer::Draw()
{
	DirectX::XMFLOAT4X4 mat[3][DIGIT_TIME + 1];

	DirectX::XMMATRIX world[DIGIT_TIME + 1];

	for (int i = 0; i < DIGIT_TIME; ++i)
	{
		//ワールド行列はX,Yのみを考慮して作成

		world[i] = DirectX::XMMatrixTranslation(m_time[i].pos.x, m_time[i].pos.y, m_time[i].pos.z);
		DirectX::XMStoreFloat4x4(&mat[0][i], DirectX::XMMatrixTranspose(world[i]));

	}


	world[4] = DirectX::XMMatrixTranslation(m_timer.pos.x, m_timer.pos.y, m_timer.pos.z);
	DirectX::XMStoreFloat4x4(&mat[0][4], DirectX::XMMatrixTranspose(world[4]));



	//ビュー行列は2dだとカメラの位置があまり関係ないので、単位行列を設定する
	DirectX::XMStoreFloat4x4(&mat[1][0], DirectX::XMMatrixIdentity());

	//プロジェクション行列は2dとして表示するための行列を設定する
	//この行列で2dスクリーンの大きさが決まる
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat[2][0], DirectX::XMMatrixTranspose(proj));



	//タイマーフレーム
	Sprite::SetWorld(mat[0][4]);
	Sprite::SetView(mat[1][0]);
	Sprite::SetProjection(mat[2][0]);
	Sprite::SetSize(DirectX::XMFLOAT2(m_timer.size.x, -m_timer.size.y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[1]);
	Sprite::Draw();


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
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.5f, 0.5f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(0.25f, 0.25f));
	Sprite::SetTexture(m_pTexture[0]);
	Sprite::Draw();

	//秒表記
	for (int i = 2; i < DIGIT_TIME; ++i)
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

int CTimer::GetTime()
{
	return m_nTimeLimit;
}

void CTimer::SetItem(int item)
{
	m_nTimer = item;
}

int CTimer::GetMaxTime()
{
	return m_nMaxTime;
}
