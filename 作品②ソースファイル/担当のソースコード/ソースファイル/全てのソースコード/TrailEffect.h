#ifndef ___TRAIL_EFFECT_H___
#define ___TRAIL_EFFECT_H___


#include "Polyline.h"

class Object;
//プレイヤーの後を追いかけるエフェクト
class TrailEffect : public Polyline
{
public:
	TrailEffect(Object* pObject);
	~TrailEffect();
	void Init();
	void SetOldPos(DirectX::XMFLOAT3 oldPos);
protected:
	//ポリラインの制御点を更新
	void UpdateControlPoints(
		LineID id, ControlPoints& controlPoints) final;

private:
	Object* m_pObject;
	DirectX::XMFLOAT3 m_oldPos;
};

#include "Object.h"
#endif // !___TRAIL_EFFECT_H___

