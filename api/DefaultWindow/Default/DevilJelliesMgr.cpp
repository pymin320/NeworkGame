#include "stdafx.h"
#include "DevilJelliesMgr.h"
#include "ScoreMgr.h"

CDevilJelliesMgr* CDevilJelliesMgr::m_pInstance = nullptr;

CDevilJelliesMgr::CDevilJelliesMgr()
{
}


CDevilJelliesMgr::~CDevilJelliesMgr()
{
	Release();
}

void CDevilJelliesMgr::Initialize(void)
{
	INFO tDevilJellyInfo[60];
	srand((unsigned int)time(NULL));


	for (int i = 0; i < 60; ++i)
	{
		tDevilJellyInfo[i] = { 300 + float(i * 500 + rand() % 300), float(rand() % 300 + 100) , 114.f, 79.f };
	}

	
	if (CScoreMgr::Get_Instance()->Get_CookieType() == DEVILCOOKIE)
	{
		for (int i = 0; i < 60; ++i)
		{
			m_DevilJelliesList.push_back(new DevilJellies(tDevilJellyInfo[i].fX, tDevilJellyInfo[i].fY));
		}
	}

	for (auto& iter : m_DevilJelliesList)
	{
		iter->Initialize();
	}
}

void CDevilJelliesMgr::Update(void)
{
	for (auto& iter = m_DevilJelliesList.begin(); iter != m_DevilJelliesList.end();)
	{
		if ((*iter)->Update() == OBJ_DEAD)
		{
			Safe_Delete<DevilJellies*>(*iter);
			iter = m_DevilJelliesList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void CDevilJelliesMgr::Late_Update(void)
{
	for (auto& iter : m_DevilJelliesList)
	{
		iter->Late_Update();
	}
}

void CDevilJelliesMgr::Render(HDC hDC)
{
	for (auto& iter : m_DevilJelliesList)
	{
		iter->Render(hDC);
	}
}

void CDevilJelliesMgr::Release(void)
{
	for (auto iter = m_DevilJelliesList.begin(); iter != m_DevilJelliesList.end();)
	{
		(*iter)->Release();
		Safe_Delete<DevilJellies*>(*iter);

		iter = m_DevilJelliesList.erase(iter);
	}
}
