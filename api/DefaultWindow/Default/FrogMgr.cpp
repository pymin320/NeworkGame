#include "stdafx.h"
#include "FrogMgr.h"

CFrogMgr* CFrogMgr::m_pInstance = nullptr;


CFrogMgr::CFrogMgr()
{
}


CFrogMgr::~CFrogMgr()
{
}

void CFrogMgr::Initialize(void)
{
	INFO tFrogInfo[5] =
	{
		{14650,130},
		{24000,130},
		{28950,130},
		{ 33700,130},
		{ 35580,130 },
	};

	for (int i = 0; i < 5; ++i)
	{
		m_NeedleList.push_back(new CFrog(tFrogInfo[i].fX, tFrogInfo[i].fY));
	}


	for (auto& iter : m_NeedleList)
	{
		iter->Initialize();
	}
}

void CFrogMgr::Update(void)
{
	for (auto& iter = m_NeedleList.begin(); iter != m_NeedleList.end();)
	{
		if ((*iter)->Update() == OBJ_DEAD)
		{
			Safe_Delete<CFrog*>(*iter);
			iter = m_NeedleList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void CFrogMgr::Late_Update(void)
{
	for (auto& iter : m_NeedleList)
	{
		iter->Late_Update();
	}
}

void CFrogMgr::Render(HDC hDC)
{
	for (auto& iter : m_NeedleList)
	{
		iter->Render(hDC);
	}
}

void CFrogMgr::Release(void)
{
	for (auto iter = m_NeedleList.begin(); iter != m_NeedleList.end();)
	{
		(*iter)->Release();
		Safe_Delete<CFrog*>(*iter);

		iter = m_NeedleList.erase(iter);
	}
}
