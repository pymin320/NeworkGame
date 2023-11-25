#include "Obj.h"
#include "Needle.h"
#include "Fork.h"
#include "Jelly.h"
#include "Coin.h"
#include "Heal.h"
#include "DevilJellies.h"
#include "DevilCoin.h"
#include "Gold.h"
#include "Frog.h"
#include "Air.h"


class CCollision
{
public:
	CCollision();
	~CCollision();

	static void Collision_Player_Needle(CObj& _Obj, list<CNeedle*>& m_Needle_List);
	static void Collision_Player_Frog(CObj& _Obj, list<CFrog*>& m_Needle_List);
	static void Collision_Player_Fork(CObj& _Obj, list<CFork*>& m_Fork_List);
	static void Collision_Player_Air(CObj& _Obj, list<CAir*>& m_Fork_List);
	static void Collision_Player_Jelly(CObj& _Obj, list<CJelly*>& m_Jelly_List);
	static void Collision_Player_Coin(CObj& _Obj, list<CCoin*>& m_Jelly_List);
	static void Collision_Player_Gold(CObj& _Obj, list<CGold*>& m_Coin_List);
	static void Collision_Player_DevilCoin(CObj& _Obj, list<CDevilCoin*>& m_Jelly_List);
	static void Collision_Player_Devil_Jellies(CObj& _Obj, list<DevilJellies*>& m_Jelly_List);
	static void Collision_Player_Item(CObj& _Obj, CObj& _Heal , OBJID eDir = OBJ_END);
	static void Collision_Pet_Jelly(CObj& _Obj, list<CJelly*>& m_Jelly_List);
	static void Collision_Pet_Coin(CObj& _Obj, list<CCoin*>& m_Jelly_List);
	static void Collision_Pet_Gold(CObj& _Obj, list<CGold*>& m_Jelly_List);
};

