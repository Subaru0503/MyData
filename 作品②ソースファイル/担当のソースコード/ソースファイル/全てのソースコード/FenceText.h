//=================================================================
//
//	FenceText.h
//	�t�F���X�Ɋւ���q���g�e�L�X�gBOX
//
//=================================================================

#ifndef __FENCE_TEXT_H__
#define __FENCE_TEXT_H__

// ========== �C���N���[�h�� ==========
#include "PlayerText.h"

// ========== �N���X ==========
class CfenceText : public CPlayerText
{
public:
	CfenceText();
	~CfenceText();
	void Update();
	void Draw();

protected:

private:
};

#endif // !__FENCE_TEXT_H__