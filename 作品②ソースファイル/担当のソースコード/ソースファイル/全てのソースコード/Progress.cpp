#include "Progress.h"
#include "Main.h"
#include "Input.h"

#define RATIO (0.001f)

CProgress::CProgress(int TotalObjNum, CSoundMng* pSoundMng)
	: m_pSoundMng(pSoundMng)
	, m_Left(0.0f)
	, m_Right((float)SCREEN_WIDTH)
	, m_Bottom((float)SCREEN_HEIGHT)
	, m_Top(0.0f)
	, m_near(1.0f)
	, m_far(10.0f)
	, m_pTexture{ nullptr, nullptr,nullptr, nullptr, nullptr }
	, m_nTime(0)
	, m_bGameEnd(false)
	, m_fsizeTimeUpX(0.0f)
	, m_fsizeTimeUpY(0.0f)
	, m_nMAXRatio(0)
	, m_fRatio(1.0f)
	, numsize(0.0f, 0.0f)
	, numpos{ {0.0f, 0.0f},{0.0f, 0.0f},{0.0f, 0.0f} }
	, m_fsizeStar{ {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f} }
	, m_nMaxtime(0)
{
	m_nSuctionObj = 0;
	m_nTotalObj = TotalObjNum;

	//�m���}�i�S�~�܁j
	m_basePosX[0] = 120.0f;
	m_basePosY[0] = 120.0f;
	m_basePosX[1] = 90.0f;
	m_basePosY[1] = 130.0f;
	m_basePosX[2] = 70.0f;
	m_basePosY[2] = 270.0f;


	for (int i = 0; i < MAX_TEXTURE; ++i)
	{
		m_pTexture[i] = new Texture();
	}
	if (FAILED(m_pTexture[0]->Create("Assets/Texture/UI_Progress.png")))
	{
		MessageBox(NULL, "Progress UI_Progress.png", "Error", MB_OK);
	}

	if (FAILED(m_pTexture[1]->Create("Assets/Texture/num.png")))
	{
		MessageBox(NULL, "Progress num.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[2]->Create("Assets/Texture/UI_star.png")))
	{
		MessageBox(NULL, "Progress UI_Star.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[3]->Create("Assets/Texture/UI_TimeUp.png")))
	{
		MessageBox(NULL, "Progress UI_TimeUp.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[4]->Create("Assets/Texture/UI_Clear.png")))
	{
		MessageBox(NULL, "Progress UI_Clear.png", "Error", MB_OK);
	}




	for (int i = 0; i < DIGIT_PROGRESS; ++i)
	{
		if (i == 0)
		{
			m_progress[i].size = DirectX::XMFLOAT2((m_pTexture[0]->GetWidth() / 3.5f), (m_pTexture[0]->GetHeight() / 3.5f)*2.0f);
		}
		else
		{
			m_progress[i].size = DirectX::XMFLOAT2((m_pTexture[0]->GetWidth() / 5.0f), (m_pTexture[0]->GetHeight() / 5.0f)*2.0f);
		}
		m_progress[i].pos = DirectX::XMFLOAT3(m_basePosX[0], m_basePosY[0], 0.0f);
		m_progress[i].posTexCoord = DirectX::XMFLOAT2(0.0f + (i *0.5f), 0.0f);
		m_progress[i].sizeTexCoord = DirectX::XMFLOAT2(1.0f / (float)ANIM_PROGRESS_SPLIT_X, 1.0f / (float)ANIM_PROGRESS_SPLIT_Y);

	}

	//�m���}�i�����j
	for (int i = 0; i < DIGIT_NUMBER; ++i)
	{
		m_number[i].size = DirectX::XMFLOAT2(50.0f, 50.0f);
		m_number[i].pos = DirectX::XMFLOAT3(m_basePosX[1] - 30.0f + (i * m_number[i].size.x) - (i *20.0f), m_basePosY[1], 0.0f);
		m_number[i].posTexCoord = DirectX::XMFLOAT2(0.0f, 0.0f);
		m_number[i].sizeTexCoord = DirectX::XMFLOAT2(1.0f / (float)ANIM_NUMBER_SPLIT_X, 1.0f / (float)ANIM_NUMBER_SPLIT_Y);

		m_number[i].currentAnimNo = 0;
		numpos[i] = DirectX::XMFLOAT2(m_number[i].pos.x, m_number[i].pos.y);
	}
	numsize.x = m_number[0].size.x;
	numsize.y = m_number[0].size.y;

	//�m���}�i���j

	for (int i = 0; i < DIGIT_STAR; ++i)
	{
		m_star[i].size = DirectX::XMFLOAT2(70.0f, 70.0f);
		m_star[i].pos = DirectX::XMFLOAT3(m_basePosX[2] + (i * m_number[i].size.x), m_basePosY[2], 0.0f);
	}






}

CProgress::~CProgress()
{
	for (int i = 0; i < MAX_TEXTURE; ++i)
	{
		if (m_pTexture)
		{
			delete m_pTexture[i];
			m_pTexture[i] = nullptr;
		}
	}
}

void CProgress::Update(int SuctionObjNum, int time, int maxtime)
{
	m_nMaxtime = maxtime;
	m_nTime = time;
	m_nSuctionObj = SuctionObjNum;
	m_nprogressNum = ((float)m_nSuctionObj / m_nTotalObj) * 100;
	//m_nprogressNum += 100;
	XINPUT_STATE state;
	XInputGetState(0, &state);
	XINPUT_KEYSTROKE stroke;
	XInputGetKeystroke(0, 0, &stroke);



	for (int i = 0; i < DIGIT_NUMBER; ++i)
	{

		m_number[i].size = DirectX::XMFLOAT2(numsize.x + (m_nprogressNum * 0.2f), numsize.x + (m_nprogressNum * 0.2f));



	}

	//�m���}�i�����j
	int temp = m_nprogressNum;

	for (int i = DIGIT_NUMBER - 1; 0 <= i; --i)
	{
		m_number[i].currentAnimNo = temp % 10;

		m_number[i].posTexCoord.x = m_number[i].sizeTexCoord.x * (m_number[i].currentAnimNo % ANIM_NUMBER_SPLIT_X);
		m_number[i].posTexCoord.y = m_number[i].sizeTexCoord.y * (m_number[i].currentAnimNo / ANIM_NUMBER_SPLIT_X);

		temp /= 10;
	}

	if (m_number[0].currentAnimNo != 0)
	{
		m_number[0].pos.x = numpos[2].x - (numsize.x);
		m_number[1].pos.x = numpos[2].x;
		m_number[2].pos.x = numpos[2].x + (numsize.x);
	}
	else if (m_number[1].currentAnimNo != 0)
	{
		m_number[1].pos.x = numpos[2].x - (numsize.x / 2.0f);
		m_number[2].pos.x = numpos[2].x + (numsize.x / 2.0f);
	}

	m_progress[1].size = DirectX::XMFLOAT2(140.0f + m_nprogressNum, 140 + (m_nprogressNum));

	float sizeUPx, sizeUPy;

	if (m_nprogressNum >= 60 && m_nprogressNum < 80)
	{
		m_progress[0].size = DirectX::XMFLOAT2(220.0f, 220.0f);
		if (m_fsizeStar[0].x <= m_star[0].size.x) {
			sizeUPx = m_star[0].size.x / 30.0f;
			sizeUPy = m_star[0].size.y / 30.0f;
			m_fsizeStar[0].x += sizeUPx;
			m_fsizeStar[0].y += sizeUPy;

		}

	}
	else if (m_nprogressNum >= 80)
	{
		m_progress[0].size = DirectX::XMFLOAT2(240.0f, 240.0f);
		if (m_fsizeStar[1].x <= m_star[1].size.x) {
			sizeUPx = m_star[1].size.x / 30.0f;
			sizeUPy = m_star[1].size.y / 30.0f;
			m_fsizeStar[1].x += sizeUPx;
			m_fsizeStar[1].y += sizeUPy;

		}
	}





	if (!m_nMAXRatio)			// �ő�{������Ȃ�������
	{
		m_fRatio += RATIO;		// �{���ݒ�
		if (m_fRatio >= 1.05f)	// �ő�{���𒴂�����
		{
			m_nMAXRatio ^= 1;	// �t���O�グ
		}
	}
	else
	{
		m_fRatio -= RATIO;		// �{���ݒ�
		if (m_fRatio <= 0.95f)	// �ŏ��{����菬�����Ȃ�����
		{
			m_nMAXRatio ^= 1;	// �t���O�グ
		}
	}



	// ----- �Q�[���I������ -----
	if (m_nprogressNum >= 100)		// ���|�����P�O�O���B�����Ă����
	{


		// �G���^�[�Ń��U���g��ʂ�
		//if (IsKeyPress(VK_RETURN) || state.Gamepad.wButtons&XINPUT_GAMEPAD_A&&stroke.Flags == 0x0001) {
		m_bGameEnd = true;	// �Q�[���I���t���O�𗧂Ă�
		m_pSoundMng->playSound(CSoundMng::TimeSE::timeUp2);	// �Q�[���I����
	}
	else if (m_nTime < 0)	// �^�C���A�b�v���Ă����
	{
		//DrawTimeUp();
		m_bGameEnd = true;	// �Q�[���I���t���O�𗧂Ă�
		m_pSoundMng->playSound(CSoundMng::TimeSE::timeUp1);	// �Q�[���I����
	}












}


void CProgress::Draw()
{


	DirectX::XMFLOAT4X4 mat[3][DIGIT_PROGRESS + DIGIT_NUMBER + DIGIT_STAR];
	DirectX::XMMATRIX world[DIGIT_PROGRESS + DIGIT_NUMBER + DIGIT_STAR];
	for (int i = 0; i < DIGIT_PROGRESS; ++i)
	{
		//���[���h�s���X,Y�݂̂��l�����č쐬

		world[i] = DirectX::XMMatrixTranslation(m_progress[i].pos.x, m_progress[i].pos.y, m_progress[i].pos.z);
		DirectX::XMStoreFloat4x4(&mat[0][i], DirectX::XMMatrixTranspose(world[i]));
	}

	for (int i = 0; i < DIGIT_NUMBER; ++i)
	{
		world[i + 2] = DirectX::XMMatrixTranslation(m_number[i].pos.x, m_number[i].pos.y, m_number[i].pos.z);
		DirectX::XMStoreFloat4x4(&mat[0][i + 2], DirectX::XMMatrixTranspose(world[i + 2]));

	}

	for (int i = 0; i < DIGIT_STAR; ++i)
	{
		world[i + 5] = DirectX::XMMatrixTranslation(m_star[i].pos.x, m_star[i].pos.y, m_star[i].pos.z);
		DirectX::XMStoreFloat4x4(&mat[0][i + 5], DirectX::XMMatrixTranspose(world[i + 5]));
	}



	//�r���[�s���2d���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��
	DirectX::XMStoreFloat4x4(&mat[1][0], DirectX::XMMatrixIdentity());

	//�v���W�F�N�V�����s���2d�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
	//���̍s���2d�X�N���[���̑傫�������܂�
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat[2][0], DirectX::XMMatrixTranspose(proj));




	for (int i = 0; i < DIGIT_PROGRESS; ++i)
	{
		Sprite::SetWorld(mat[0][i]);
		Sprite::SetView(mat[1][0]);
		Sprite::SetProjection(mat[2][0]);
		Sprite::SetSize(DirectX::XMFLOAT2(m_progress[i].size.x, -m_progress[i].size.y));
		Sprite::SetUVPos(DirectX::XMFLOAT2(m_progress[i].posTexCoord.x, m_progress[i].posTexCoord.y));
		Sprite::SetUVScale(DirectX::XMFLOAT2(m_progress[i].sizeTexCoord.x, m_progress[i].sizeTexCoord.y));
		Sprite::SetTexture(m_pTexture[0]);
		Sprite::Draw();
	}


	for (int i = 0; i < DIGIT_NUMBER; ++i)
	{
		if (m_number[0].currentAnimNo != 0)
		{
			Sprite::SetWorld(mat[0][i + 2]);
			Sprite::SetView(mat[1][0]);
			Sprite::SetProjection(mat[2][0]);
			Sprite::SetSize(DirectX::XMFLOAT2(m_number[i].size.x * m_fRatio, -m_number[i].size.y* m_fRatio));
			Sprite::SetUVPos(DirectX::XMFLOAT2(m_number[i].posTexCoord.x, m_number[i].posTexCoord.y));
			Sprite::SetUVScale(DirectX::XMFLOAT2(m_number[i].sizeTexCoord.x, m_number[i].sizeTexCoord.y));
			Sprite::SetTexture(m_pTexture[1]);
			Sprite::Draw();
		}
		else
		{
			if (m_number[1].currentAnimNo != 0)
			{
				Sprite::SetWorld(mat[0][i + 3]);
				Sprite::SetView(mat[1][0]);
				Sprite::SetProjection(mat[2][0]);
				Sprite::SetSize(DirectX::XMFLOAT2(m_number[i + 1].size.x* m_fRatio, -m_number[i + 1].size.y* m_fRatio));
				Sprite::SetUVPos(DirectX::XMFLOAT2(m_number[i + 1].posTexCoord.x, m_number[i + 1].posTexCoord.y));
				Sprite::SetUVScale(DirectX::XMFLOAT2(m_number[i + 1].sizeTexCoord.x, m_number[i + 1].sizeTexCoord.y));
				Sprite::SetTexture(m_pTexture[1]);
				Sprite::Draw();
			}
			else
			{
				Sprite::SetWorld(mat[0][i + 4]);
				Sprite::SetView(mat[1][0]);
				Sprite::SetProjection(mat[2][0]);
				Sprite::SetSize(DirectX::XMFLOAT2(m_number[i + 2].size.x* m_fRatio, -m_number[i + 2].size.y* m_fRatio));
				Sprite::SetUVPos(DirectX::XMFLOAT2(m_number[i + 2].posTexCoord.x, m_number[i + 2].posTexCoord.y));
				Sprite::SetUVScale(DirectX::XMFLOAT2(m_number[i + 2].sizeTexCoord.x, m_number[i + 2].sizeTexCoord.y));
				Sprite::SetTexture(m_pTexture[1]);
				Sprite::Draw();
			}

		}



	}



	if (m_nprogressNum >= 60 && m_nprogressNum < 80)
	{
		Sprite::SetWorld(mat[0][5]);
		Sprite::SetView(mat[1][0]);
		Sprite::SetProjection(mat[2][0]);
		Sprite::SetSize(DirectX::XMFLOAT2(m_fsizeStar[0].x * m_fRatio, -m_fsizeStar[0].y* m_fRatio));
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
		Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
		Sprite::SetTexture(m_pTexture[2]);
		Sprite::Draw();

	}
	if (m_nprogressNum >= 80 && m_nprogressNum < 100)
	{
		Sprite::SetWorld(mat[0][5]);
		Sprite::SetView(mat[1][0]);
		Sprite::SetProjection(mat[2][0]);
		Sprite::SetSize(DirectX::XMFLOAT2(m_fsizeStar[0].x * m_fRatio, -m_fsizeStar[0].y * m_fRatio));
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
		Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
		Sprite::SetTexture(m_pTexture[2]);
		Sprite::Draw();

		Sprite::SetWorld(mat[0][6]);
		Sprite::SetView(mat[1][0]);
		Sprite::SetProjection(mat[2][0]);
		Sprite::SetSize(DirectX::XMFLOAT2(m_fsizeStar[1].x * m_fRatio, -m_fsizeStar[1].y * m_fRatio));
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
		Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
		Sprite::SetTexture(m_pTexture[2]);
		Sprite::Draw();
	}
	if (m_nprogressNum >= 100)
	{
		Sprite::SetWorld(mat[0][5]);
		Sprite::SetView(mat[1][0]);
		Sprite::SetProjection(mat[2][0]);
		Sprite::SetSize(DirectX::XMFLOAT2(m_fsizeStar[0].x* m_fRatio, -m_fsizeStar[0].y* m_fRatio));
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
		Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
		Sprite::SetTexture(m_pTexture[2]);
		Sprite::Draw();

		Sprite::SetWorld(mat[0][6]);
		Sprite::SetView(mat[1][0]);
		Sprite::SetProjection(mat[2][0]);
		Sprite::SetSize(DirectX::XMFLOAT2(m_fsizeStar[1].x* m_fRatio, -m_fsizeStar[1].y* m_fRatio));
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
		Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
		Sprite::SetTexture(m_pTexture[2]);
		Sprite::Draw();

		Sprite::SetWorld(mat[0][7]);
		Sprite::SetView(mat[1][0]);
		Sprite::SetProjection(mat[2][0]);
		Sprite::SetSize(DirectX::XMFLOAT2(m_fsizeStar[1].x* m_fRatio, -m_fsizeStar[1].y* m_fRatio));
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
		Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
		Sprite::SetTexture(m_pTexture[2]);
		Sprite::Draw();

	}
}


void CProgress::SetSound(CSoundMng * sound)
{
	m_pSoundMng = sound;
}

bool CProgress::GetEndFlg()
{
	return m_bGameEnd;
}

int CProgress::GetProgressNum()
{
	return m_nprogressNum;
}

int CProgress::GetTime()
{
	return m_nMaxtime - m_nTime;
}

// �����I�ɂU�O���B��������i�f�o�b�O�p�j
void CProgress::SetClear()
{
	m_nprogressNum = 61;
}
