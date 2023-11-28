#include "stdafx.h"
#include "PumkinMgr.h"

CPumkinMgr* CPumkinMgr::m_pInstance = nullptr;

CPumkinMgr::CPumkinMgr()
{
}


CPumkinMgr::~CPumkinMgr()
{
}

void CPumkinMgr::Initialize(void)
{
	INFO tPumkinInfo[5] =
	{
	{ 17000 , 450},
	{ 17050 , 450},
	{ 22400, 450},
	{ 31700, 450 },
	{ 32700, 450 },
	};

	for (int i = 0; i < 5; ++i)
	{
		m_NeedleList.push_back(new CPumkin(tPumkinInfo[i].fX, tPumkinInfo[i].fY));
	}


	for (auto& iter : m_NeedleList)
	{
		iter->Initialize();
	}
}

void CPumkinMgr::Update(void)
{

	for (auto& iter = m_NeedleList.begin(); iter != m_NeedleList.end();)
	{
		if ((*iter)->Update() == OBJ_DEAD)
		{
			Safe_Delete<CPumkin*>(*iter);
			iter = m_NeedleList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void CPumkinMgr::Late_Update(void)
{
	for (auto& iter : m_NeedleList)
	{
		iter->Late_Update();
	}
}

void CPumkinMgr::Render(HDC hDC)
{
	for (auto& iter : m_NeedleList)
	{
		iter->Render(hDC);
	}
}
void CPumkinMgr::Release(void)
{
	for (auto iter = m_NeedleList.begin(); iter != m_NeedleList.end();)
	{
		(*iter)->Release();
		Safe_Delete<CPumkin*>(*iter);

		iter = m_NeedleList.erase(iter);
	}
}
