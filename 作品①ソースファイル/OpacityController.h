// 透明度変化クラス

// インクルードガード
#ifndef __OPACITY_H__
#define __OPACITY_H__

// インクルード部
#include "Component.h"

#include "ModelRenderer2D.h"

// クラス定義
class Opacity : public Component
{
public:
	Opacity();
	~Opacity();

	void Execute();		// 更新

	// セット関数
	inline void SetChangeValue(float value)
	{
		m_Value = value;
	}
	inline void SetParam(ModelRenderer2D::Param* param)
	{
		m_Param = param;
	}

private:
	void Blink();		// 透明度変化
private:
	ModelRenderer2D::Param* m_Param;	// パラメータ
	float m_Value;		// 透明度変化量

	float m_Alpha;		// 透明度
	bool m_ClearFlg;	// 透明度フラグ
};

#endif // __OPACITY_H__