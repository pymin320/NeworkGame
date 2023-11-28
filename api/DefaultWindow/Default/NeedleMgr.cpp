#include "stdafx.h"
#include "NeedleMgr.h"

CNeedleMgr* CNeedleMgr::m_pInstance = nullptr;

CNeedleMgr::CNeedleMgr()
{
}


CNeedleMgr::~CNeedleMgr()
{
}

void CNeedleMgr::Initialize(void)
{
	INFO tForkInfo[11] =
	{
		{ 1500,415 },
		{ 3900,415},
		{ 4000,415 },
		{ 4100,415 },
		{ 4200,415 },
		{ 4300,415 },
		{14000,415 },

		{ 24650,415 },
		{ 28500,415 },
		{ 28800,415 },
		{ 29100,415 },
	};

	for (int i = 0; i < 11; ++i)
	{
		m_NeedleList.push_back(new CNeedle(tForkInfo[i].fX, tForkInfo[i].fY));
	}


	for (auto& iter : m_NeedleList)
	{
		iter->Initialize();
	}
}

void CNeedleMgr::Update(void)
{
	for (auto& iter = m_NeedleList.begin(); iter != m_NeedleList.end();)
	{
		if ((*iter)->Update() == OBJ_DEAD)
		{
			Safe_Delete<CNeedle*>(*iter);
			iter = m_NeedleList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void CNeedleMgr::Late_Update(void)
{
	for (auto& iter : m_NeedleList)
	{
		iter->Late_Update();
	}
}

void CNeedleMgr::Render(HDC hDC)
{
	for (auto& iter : m_NeedleList)
	{
		iter->Render(hDC);
	}
}

void CNeedleMgr::Release(void)
{
	for (auto iter = m_NeedleList.begin(); iter != m_NeedleList.end();)
	{
		(*iter)->Release();
		Safe_Delete<CNeedle*>(*iter);

		iter = m_NeedleList.erase(iter);
	}
}
