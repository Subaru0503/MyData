#pragma once
#include "LibEffekseer.h"
#include <list>
#include <vector>
using namespace std;

class Object;
class CPlayer;

class EBag
{
public:
	EBag();
	~EBag();
	void Play(Object* pObj);
	void Draw();
	void SetObject(list<Object*>* pObj);
	void SetPlayer(CPlayer* pPlayer);
private:
	Effekseer::EffectRef effect;
	Effekseer::Handle efkHandle;
	list<Object*>*m_pObjectlist;
	CPlayer* m_pPlayer;
};
