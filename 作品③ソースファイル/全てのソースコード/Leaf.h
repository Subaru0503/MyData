#ifndef LEAF_H
#define	LEAF_H

#include "LibEffekseer.h"
#include <list>
#include <vector>
using namespace std;

class CPlayer;
class Object;

class Leaf
{
public:
	Leaf();
	~Leaf();
	void Play(Object* pObj,int i);
	void Draw();
	void SetObject(list<Object*>* pObj);
	void SetPlayer(CPlayer* pPlayer);

private:
	Effekseer::EffectRef effect;
	Effekseer::Handle efkHandle[1000];
	CPlayer* m_pPlayer;
	list<Object*>*m_pObjectlist;
	int efkNum;
	float RadXZ;
};

#endif // !