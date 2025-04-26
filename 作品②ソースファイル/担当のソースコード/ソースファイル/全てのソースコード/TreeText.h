//=================================================================
//
//	TreeText.h
//	木に関するヒントテキストBOX
//
//=================================================================

#ifndef __TREE_TEXT_H__
#define __TREE_TEXT_H__

// ========== インクルード部 ==========
#include "PlayerText.h"

// ========== クラス ==========
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
