//=================================================================
//
//	TreeText.h
//	�؂Ɋւ���q���g�e�L�X�gBOX
//
//=================================================================

#ifndef __TREE_TEXT_H__
#define __TREE_TEXT_H__

// ========== �C���N���[�h�� ==========
#include "PlayerText.h"

// ========== �N���X ==========
class CTreeText : public CPlayerText
{
public:
	CTreeText();
	~CTreeText();
	void Update();
	void Draw();

protected:

private:
};

#endif // !__TREE_TEXT_H__
