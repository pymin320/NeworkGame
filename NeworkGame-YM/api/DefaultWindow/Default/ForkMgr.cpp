#include "stdafx.h"
#include "ForkMgr.h"

CForkMgr* CForkMgr::m_pInstance = nullptr;

CForkMgr::CForkMgr()
{
}


CForkMgr::~CForkMgr()
{
}

void CForkMgr::Initialize(void)
{
	INFO tForkInfo[10] =
	{
		{7400,130},
		{7500,130},
		{14500,130},
		{23500,130},
		{28650,130 },
		{30180,130 },
		{35080,130},
	};

	for (int i = 0; i < 10; ++i)
	{
		m_ForkList.push_back(new CFork(tForkInfo[i].fX, tForkInfo[i].fY));
	}


	for (auto& iter : m_ForkList)
	{
		iter->Initialize();
	}
}

void CForkMgr::Update(void)
{
	for (auto& iter = m_ForkList.begin(); iter != m_ForkList.end();)
	{
		if ((*iter)->Update() == OBJ_DEAD)
		{
			Safe_Delete<CFork*>(*iter);
			iter = m_ForkList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void CForkMgr::Late_Update(void)
{
	for (auto& iter : m_ForkList)
	{
		iter->Late_Update();
	}
}

void CForkMgr::Render(HDC hDC)
{
	for (auto& iter : m_ForkList)
	{
		iter->Render(hDC);
	}
}

void CForkMgr::Release(void)
{
	for (auto iter = m_ForkList.begin(); iter != m_ForkList.end();)
	{
		(*iter)->Release();
		Safe_Delete<CFork*>(*iter);

		iter = m_ForkList.erase(iter);
	}
}
