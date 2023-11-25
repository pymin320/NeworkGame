#include "stdafx.h"
#include "Collision.h"
#include "Player.h"
#include "Pet.h"


CCollision::CCollision()
{
}


CCollision::~CCollision()
{
}

void CCollision::Collision_Player_Needle(CObj& _Obj, list<CNeedle*>& m_Needle_List)
{
	CPlayer* player = static_cast<CPlayer*>(&_Obj);
	RECT Player_Rc = _Obj.Get_Rect();
	INFO _Player_Info = _Obj.Get_Info();

	INFO Needle_Info;
	RECT Collision = { 0,0,0,0 };

	for (auto& _Needle : m_Needle_List)
	{
		Needle_Info = _Needle->Get_Info();
		if (IntersectRect(&Collision, &player->Get_Rect(), &_Needle->Get_Rect()))
		{
			player->Collision();
			if (player->Get_Playertype() == BOOST || player->Get_Playertype() == GIGA)
				_Needle->Dead();
		}
	}
}

void CCollision::Collision_Player_Frog(CObj & _Obj, list<CFrog*>& m_Needle_List)
{
	CPlayer* player = static_cast<CPlayer*>(&_Obj);
	RECT Player_Rc = _Obj.Get_Rect();
	INFO _Player_Info = _Obj.Get_Info();

	INFO Needle_Info;
	RECT Collision = { 0,0,0,0 };

	for (auto& _Fork : m_Needle_List)
	{
		Needle_Info = _Fork->Get_Info();
		if (IntersectRect(&Collision, &player->Get_Rect(), &_Fork->Get_Rect()))
		{
			player->Collision();
			if (player->Get_Playertype() == BOOST || player->Get_Playertype() == GIGA)
				_Fork->Dead();
		}
	}
}

void  CCollision::Collision_Player_Fork(CObj& _Obj, std::list<CFork*>& m_Fork_List)
{
	CPlayer* player = static_cast<CPlayer*>(&_Obj);
	RECT Player_Rc = _Obj.Get_Rect();
	INFO _Player_Info = _Obj.Get_Info();

	INFO Needle_Info;
	RECT Collision = { 0,0,0,0 };

	for (auto& _Fork : m_Fork_List)
	{
		Needle_Info = _Fork->Get_Info();
		if (IntersectRect(&Collision, &player->Get_Rect(), &_Fork->Get_Rect()))
		{
			player->Collision();
			if (player->Get_Playertype() == BOOST || player->Get_Playertype() == GIGA)
				_Fork->Dead();
		}
	}
}

void CCollision::Collision_Player_Air(CObj & _Obj, list<CAir*>& m_Fork_List)
{
	CPlayer* player = static_cast<CPlayer*>(&_Obj);
	RECT Player_Rc = _Obj.Get_Rect();
	INFO _Player_Info = _Obj.Get_Info();

	INFO Needle_Info;
	RECT Collision = { 0,0,0,0 };

	for (auto& _Fork : m_Fork_List)
	{
		Needle_Info = _Fork->Get_Info();
		if (IntersectRect(&Collision, &player->Get_Rect(), &_Fork->Get_Rect()))
		{
			player->Collision();
			if (player->Get_Playertype() == BOOST || player->Get_Playertype() == GIGA)
				_Fork->Dead();
		}
	}
}

void CCollision::Collision_Player_Jelly(CObj & _Obj, std::list<CJelly*>& m_Jelly_List)
{
	CPlayer* player = static_cast<CPlayer*>(&_Obj);
	RECT Player_Rc = _Obj.Get_Rect();
	INFO _Player_Info = _Obj.Get_Info();

	INFO Needle_Info;
	RECT Collision = { 0,0,0,0 };

	for (auto& _Jelly : m_Jelly_List)
	{
		Needle_Info = _Jelly->Get_Info();
		if (IntersectRect(&Collision, &player->Get_Rect(), &_Jelly->Get_Rect()))
		{
			_Jelly->PlayerColiision();
		}
	}
}
void CCollision::Collision_Player_Item(CObj& _Obj, CObj& _Item, OBJID eDir)
{
	CPlayer* player = static_cast<CPlayer*>(&_Obj);

	RECT Collision = { 0,0,0,0 };

	if (IntersectRect(&Collision, &player->Get_Rect(), &_Item.Get_Rect()))
	{
		player->Get_Itemtype(eDir);
		_Item.Dead();
	}
}

void CCollision::Collision_Pet_Jelly(CObj & _Obj, list<CJelly*>& m_Jelly_List)
{
	CPet* Pet = static_cast<CPet*>(&_Obj);

	RECT RC = { 0,0,0,0 };
	INFO Needle_Info;

	for (auto& _Jelly : m_Jelly_List)
	{
		Needle_Info = _Jelly->Get_Info();
		if ((IntersectRect(&RC, &Pet->Get_MagnetRect(), &_Jelly->Get_Rect())) && (Pet->ReturnMagnet()))
		{
			_Jelly->PetColiision(Pet->Get_Info());
		}
	}
}

void CCollision::Collision_Pet_Coin(CObj & _Obj, list<CCoin*>& m_Jelly_List)
{
	CPet* Pet = static_cast<CPet*>(&_Obj);

	RECT RC = { 0,0,0,0 };
	INFO Needle_Info;

	for (auto& _Jelly : m_Jelly_List)
	{
		Needle_Info = _Jelly->Get_Info();
		if ((IntersectRect(&RC, &Pet->Get_MagnetRect(), &_Jelly->Get_Rect())) && (Pet->ReturnMagnet()))
		{
			_Jelly->PetColiision(Pet->Get_Info());
		}
	}
}

void CCollision::Collision_Pet_Gold(CObj & _Obj, list<CGold*>& m_Jelly_List)
{
	CPet* Pet = static_cast<CPet*>(&_Obj);

	RECT RC = { 0,0,0,0 };
	INFO Needle_Info;

	for (auto& _Jelly : m_Jelly_List)
	{
		Needle_Info = _Jelly->Get_Info();
		if ((IntersectRect(&RC, &Pet->Get_MagnetRect(), &_Jelly->Get_Rect())) && (Pet->ReturnMagnet()))
		{
			_Jelly->PetColiision(Pet->Get_Info());
		}
	}
}



void CCollision::Collision_Player_Coin(CObj & _Obj, std::list<CCoin*>& m_Coin_List)
{
	CPlayer* player = static_cast<CPlayer*>(&_Obj);
	RECT Player_Rc = _Obj.Get_Rect();
	INFO _Player_Info = _Obj.Get_Info();

	INFO Coin_Info;
	RECT Collision = { 0,0,0,0 };

	for (auto& _Coin : m_Coin_List)
	{
		Coin_Info = _Coin->Get_Info();
		if (IntersectRect(&Collision, &player->Get_Rect(), &_Coin->Get_Rect()))
		{
			_Coin->PlayerColiision();
		}
	}
}

void CCollision::Collision_Player_Gold(CObj & _Obj, list<CGold*>& m_Coin_List)
{
	CPlayer* player = static_cast<CPlayer*>(&_Obj);
	RECT Player_Rc = _Obj.Get_Rect();
	INFO _Player_Info = _Obj.Get_Info();

	INFO Coin_Info;
	RECT Collision = { 0,0,0,0 };

	for (auto& _Coin : m_Coin_List)
	{
		Coin_Info = _Coin->Get_Info();
		if (IntersectRect(&Collision, &player->Get_Rect(), &_Coin->Get_Rect()))
		{
			_Coin->PlayerColiision();
		}
	}
}

void CCollision::Collision_Player_DevilCoin(CObj & _Obj, list<CDevilCoin*>& m_Jelly_List)
{
	CPlayer* player = static_cast<CPlayer*>(&_Obj);
	RECT Player_Rc = _Obj.Get_Rect();
	INFO _Player_Info = _Obj.Get_Info();

	INFO Coin_Info;
	RECT Collision = { 0,0,0,0 };

	for (auto& _Coin : m_Jelly_List)
	{
		Coin_Info = _Coin->Get_Info();
		if (IntersectRect(&Collision, &player->Get_Rect(), &_Coin->Get_Rect()))
		{
			_Coin->PlayerColiision();
		}
	}
}



void CCollision::Collision_Player_Devil_Jellies(CObj & _Obj, std::list<DevilJellies*>& m_DevilJelly_List)
{
	CPlayer* player = static_cast<CPlayer*>(&_Obj);
	RECT Player_Rc = _Obj.Get_Rect();
	INFO _Player_Info = _Obj.Get_Info();

	INFO Needle_Info;
	RECT Collision = { 0,0,0,0 };

	for (auto& _DevilJelly : m_DevilJelly_List)
	{
		Needle_Info = _DevilJelly->Get_Info();
		if (IntersectRect(&Collision, &player->Get_Rect(), &_DevilJelly->Get_Rect()))
		{
			_DevilJelly->Dead();
			player->CollisionDevil();
		}
	}
}
