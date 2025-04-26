#ifndef _DESTCLOUD_H_
#define _DESTCLOUD_H_

#include "LibEffekseer.h"
#include <list>
#include <vector>
using namespace std;

class CPlayer;
class Object;

class Dust
{
public:
	Dust();
	~Dust();
	void Update();
	void Play();
	void Draw();
	void SetObject(list<Object*>* pObj);
	void SetPlayer(CPlayer* pPlayer);

private:
	Effekseer::EffectRef effect;
	vector<Effekseer::Handle> efkHandle;
	CPlayer* m_pPlayer;
	list<Object*>*m_pObjectlist;
	int efkNum;
	float RadXZ;
};


#endif // !_DESTCLOUD_H_