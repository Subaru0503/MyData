//=================================================================
//
//	FenceText.h
//	フェンスに関するヒントテキストBOX
//
//=================================================================

#ifndef __FENCE_TEXT_H__
#define __FENCE_TEXT_H__

// ========== インクルード部 ==========
#include "PlayerText.h"

// ========== クラス ==========
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