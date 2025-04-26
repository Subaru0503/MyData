#ifndef ___UI_H___
#define ___UI_H___

#include <DirectXMath.h>
#include "Defines.h"
#include "Sprite.h"
#include "Texture.h"

#define MAX_UI (5)
#define DIGIT_SCORE			(6)	//�G�t�F�N�g�̐��i�z��̐��j
#define ANIM_SCORE_FRAME	(2)		//�A�j���[�V������R�}�t���[����
#define ANIM_SCORE_SPLIT_X	(4)		//�摜�������i���j
#define ANIM_SCORE_SPLIT_Y	(4)		//�摜�������i�c�j

class CUI
{

public:
	typedef struct
	{

		DirectX::XMFLOAT3 pos;			//���S���W
		DirectX::XMFLOAT2 size;			//���c�T�C�Y
		DirectX::XMFLOAT2 posTexCoord;	//�e�N�X�`�����W�i����j
		DirectX::XMFLOAT2 sizeTexCoord;	//�e�N�X�`���T�C�Y�i�E���j
		//Float4	color;			//�J���[
		//float	angle;			//��]�p�x
		//bool	use;			//�g�p���t���O
		int		frame;			//�A�j���[�V�����Ǘ��t���[��
		int		currentAnimNo;	//�A�j���[�V�����R�}�ԍ��i���ォ��O�`�j
	}ST_SCORE_PARAM;		//�p�����[�^�̍\����

	typedef struct
	{

		DirectX::XMFLOAT3 pos;			//���S���W
		DirectX::XMFLOAT2 size;			//���c�T�C�Y
		DirectX::XMFLOAT2 posTexCoord;	//�e�N�X�`�����W�i����j
		DirectX::XMFLOAT2 sizeTexCoord;	//�e�N�X�`���T�C�Y�i�E���j
		int		currentAnimNo;	//�A�j���[�V�����R�}�ԍ��i���ォ��O�`�j
	}ST_ADDMANEY_PARAM;		//�p�����[�^�̍\����

public:
	CUI();
	~CUI();
	void Update();
	void Draw();
	void DrawResult(int resultMoney);
	void AddMoney(int num);
	void UpdateScoretexCoord();
	int  GetMoney();
	void DrawAdd();
	void SetAdd(bool Add);
	bool GetAdd();

	CUI(int money);

private:
	ST_SCORE_PARAM m_score[DIGIT_SCORE + 1];
	ST_ADDMANEY_PARAM m_add[DIGIT_SCORE + 1];
	unsigned int m_TextureScore;
	int m_nScore;
	int m_nAddMoney;
	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;
	float m_basePosX, m_basePosY;
	bool m_bAdd;//�\���t���O
	float m_fAlpha;
	Texture* m_pTexture[MAX_UI];

	
	int m_temp;
	int m_temp2;


};


#endif // !___UI_H___