#include "stdafx.h"
#include "ObjMgr.h"
#include "JellyMgr.h"
#include "ForkMgr.h"
#include "NeedleMgr.h"
#include "Collision.h"
#include "CAbstractFactory.h"
#include "Player.h"
#include "Background.h"
#include "LineMgr.h"
#include "Tilemgr.h"
#include "CoinMgr.h"
#include "DevilJelliesMgr.h"
#include "DevilCoinMgr.h"
#include "GoldMgr.h"
#include "PumkinMgr.h"
#include "AirMgr.h"
#include "FrogMgr.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}


void CObjMgr::Initialize(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Initialize();
	}
	CJellyMgr::Get_Instance()->Initialize();
	CForkMgr::Get_Instance()->Initialize();
	CNeedleMgr::Get_Instance()->Initialize();
	CCoinMgr::Get_Instance()->Initialize();
	CDevilJelliesMgr::Get_Instance()->Initialize();
	CDevilCoinMgr::Get_Instance()->Initialize();
	CGoldMgr::Get_Instance()->Initialize();
	CPumkinMgr::Get_Instance()->Initialize();
	CAirMgr::Get_Instance()->Initialize();
	CFrogMgr::Get_Instance()->Initialize();
}

void CObjMgr::Add_Object(OBJID eID, CObj * pObj)
{
	if ((eID >= OBJ_END) || (nullptr == pObj))
		return;

	m_ObjList[eID].push_back(pObj);
}

int CObjMgr::Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}
	CJellyMgr::Get_Instance()->Update();
	CForkMgr::Get_Instance()->Update();
	CNeedleMgr::Get_Instance()->Update();
	CCoinMgr::Get_Instance()->Update();
	CDevilJelliesMgr::Get_Instance()->Update();
	CDevilCoinMgr::Get_Instance()->Update();
	CGoldMgr::Get_Instance()->Update();
	CPumkinMgr::Get_Instance()->Update();
	CAirMgr::Get_Instance()->Update();
	CFrogMgr::Get_Instance()->Update();


	return OBJ_NOEVENT;
}

void CObjMgr::Late_Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Late_Update();
	}
	CJellyMgr::Get_Instance()->Late_Update();
	CForkMgr::Get_Instance()->Late_Update();
	CNeedleMgr::Get_Instance()->Late_Update();
	CCoinMgr::Get_Instance()->Late_Update();
	CDevilJelliesMgr::Get_Instance()->Late_Update();
	CDevilCoinMgr::Get_Instance()->Late_Update();
	CGoldMgr::Get_Instance()->Late_Update();
	CPumkinMgr::Get_Instance()->Late_Update();
	CAirMgr::Get_Instance()->Late_Update();
	CFrogMgr::Get_Instance()->Late_Update();

	CCollision::Collision_Player_Needle(*OBJMGR->Get_Obj_List(OBJ_PLAYER).front(), CNeedleMgr::Get_Instance()->Get_Needle_List());
	CCollision::Collision_Player_Fork(*OBJMGR->Get_Obj_List(OBJ_PLAYER).front(), CForkMgr::Get_Instance()->Get_Fork_List());
	CCollision::Collision_Player_Frog(*OBJMGR->Get_Obj_List(OBJ_PLAYER).front(), CFrogMgr::Get_Instance()->Get_Needle_List());
	CCollision::Collision_Player_Air(*OBJMGR->Get_Obj_List(OBJ_PLAYER).front(), CAirMgr::Get_Instance()->Get_Needle_List());
	CCollision::Collision_Player_Jelly(*OBJMGR->Get_Obj_List(OBJ_PLAYER).front(), CJellyMgr::Get_Instance()->Get_Jelly_List());
	CCollision::Collision_Player_Coin(*OBJMGR->Get_Obj_List(OBJ_PLAYER).front(), CCoinMgr::Get_Instance()->Get_Coin_List());
	CCollision::Collision_Player_Gold(*OBJMGR->Get_Obj_List(OBJ_PLAYER).front(), CGoldMgr::Get_Instance()->Get_Coin_List());
	CCollision::Collision_Player_DevilCoin(*OBJMGR->Get_Obj_List(OBJ_PLAYER).front(), CDevilCoinMgr::Get_Instance()->Get_Devil_Coin_List());
	CCollision::Collision_Player_Devil_Jellies(*OBJMGR->Get_Obj_List(OBJ_PLAYER).front(), CDevilJelliesMgr::Get_Instance()->Get_DevilJellies_List());
	CCollision::Collision_Pet_Jelly(*OBJMGR->Get_Obj_List(OBJ_PET).front(), CJellyMgr::Get_Instance()->Get_Jelly_List());
	CCollision::Collision_Pet_Coin(*OBJMGR->Get_Obj_List(OBJ_PET).front(), CCoinMgr::Get_Instance()->Get_Coin_List());
	CCollision::Collision_Pet_Gold(*OBJMGR->Get_Obj_List(OBJ_PET).front(), CGoldMgr::Get_Instance()->Get_Coin_List());

	if(!OBJMGR->Get_Obj_List(OBJ_ITEM_HEAL).empty())
		CCollision::Collision_Player_Item(*OBJMGR->Get_Obj_List(OBJ_PLAYER).front(), *OBJMGR->Get_Obj_List(OBJ_ITEM_HEAL).front(), OBJ_ITEM_HEAL);
	if (!OBJMGR->Get_Obj_List(OBJ_ITEM_BOOST).empty())
		CCollision::Collision_Player_Item(*OBJMGR->Get_Obj_List(OBJ_PLAYER).front(), *OBJMGR->Get_Obj_List(OBJ_ITEM_BOOST).front(), OBJ_ITEM_BOOST);
	if (!OBJMGR->Get_Obj_List(OBJ_ITEM_GIGA).empty())
		CCollision::Collision_Player_Item(*OBJMGR->Get_Obj_List(OBJ_PLAYER).front(), *OBJMGR->Get_Obj_List(OBJ_ITEM_GIGA).front(), OBJ_ITEM_GIGA);
	if (!OBJMGR->Get_Obj_List(OBJ_ITEM_GIGA2).empty())
		CCollision::Collision_Player_Item(*OBJMGR->Get_Obj_List(OBJ_PLAYER).front(), *OBJMGR->Get_Obj_List(OBJ_ITEM_GIGA2).front(), OBJ_ITEM_GIGA2);
	if (!OBJMGR->Get_Obj_List(OBJ_ITEM_MAGNET).empty())
		CCollision::Collision_Player_Item(*OBJMGR->Get_Obj_List(OBJ_PLAYER).front(), *OBJMGR->Get_Obj_List(OBJ_ITEM_MAGNET).front(), OBJ_ITEM_MAGNET);
	if (!OBJMGR->Get_Obj_List(OBJ_ITEM_MAGNET).empty())
		CCollision::Collision_Player_Item(*OBJMGR->Get_Obj_List(OBJ_PLAYER).front(), *OBJMGR->Get_Obj_List(OBJ_ITEM_MAGNET).front(), OBJ_ITEM_MAGNET);
	if (!OBJMGR->Get_Obj_List(OBJ_ITEM_SMALL).empty())
		CCollision::Collision_Player_Item(*OBJMGR->Get_Obj_List(OBJ_PLAYER).front(), *OBJMGR->Get_Obj_List(OBJ_ITEM_SMALL).front(), OBJ_ITEM_SMALL);

}

void CObjMgr::Render(HDC hDC)
{
	for (auto& iter : m_ObjList[0])
		iter->Render(hDC);
	CJellyMgr::Get_Instance()->Render(hDC);
	CForkMgr::Get_Instance()->Render(hDC);
	CNeedleMgr::Get_Instance()->Render(hDC);
	CCoinMgr::Get_Instance()->Render(hDC);
	CDevilJelliesMgr::Get_Instance()->Render(hDC);
	CDevilCoinMgr::Get_Instance()->Render(hDC);
	CGoldMgr::Get_Instance()->Render(hDC);
	CPumkinMgr::Get_Instance()->Render(hDC);
	CAirMgr::Get_Instance()->Render(hDC);
	CFrogMgr::Get_Instance()->Render(hDC);

	for (int i = 1; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Render(hDC);
	}

}

void CObjMgr::Release(void)
{

	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			Safe_Delete<CObj*>(iter);

		m_ObjList[i].clear();
	}
	CJellyMgr::Get_Instance()->Release();
	CForkMgr::Get_Instance()->Release();
	CNeedleMgr::Get_Instance()->Release();
	CCoinMgr::Get_Instance()->Release();
	CDevilJelliesMgr::Get_Instance()->Release();
	CDevilCoinMgr::Get_Instance()->Release();
	CTileMgr::Get_Instance()->Release();
	CLineMgr::Get_Instance()->Release();
	CGoldMgr::Get_Instance()->Release();
	CPumkinMgr::Get_Instance()->Release();
	CAirMgr::Get_Instance()->Release();
	CFrogMgr::Get_Instance()->Release();
}
