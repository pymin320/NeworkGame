#include "stdafx.h"
#include "AirMgr.h"

CAirMgr* CAirMgr::m_pInstance = nullptr;

CAirMgr::CAirMgr()
{
}


CAirMgr::~CAirMgr()
{
}

void CAirMgr::Initialize(void)
{
	INFO tAirInfo[60] =
	{
		{ 18000 , 350 },
		{ 18100 , 300 },
		{ 18200 , 250 },
		{ 18300 , 200 },
		{ 18400 , 150 },


		{ 32000, 100 },
		{ 33000, 100 },
		{ 34000, 250 },


		{ 19932, 500 },
		{ 20700, 500 },
		{ 19932, 100 },
		{ 19932, 110 },
		{ 20700, 100 },
		{ 20700, 110 },
		{ 21618, 500 },
		{ 21618, 450 },
		{ 21618, 400 },


		{ 25500 , 350 },
		{ 25600 , 300 },
		{ 25700 , 250 },
		{ 25800 , 200 },
		{ 25900 , 150 },

		{ 26200 , 350 },
		{ 26200 , 300 },
		{ 26200 , 250 },
		{ 26200 , 200 },
		{ 26200 , 150 },

		{ 26400 , 350 },
		{ 26400 , 300 },
		{ 26400 , 250 },
		{ 26400 , 200 },
		{ 26400 , 150 },

		{ 26600 , 350 },
		{ 26600 , 300 },
		{ 26600 , 250 },
		{ 26600 , 200 },
		{ 26600 , 150 },


		{ 27600 , 450 },
		{ 27600 , 400 },
		{ 27600 , 350 },
		{ 27600 , 300 },
		{ 27600 , 250 },
		{ 27600 , 200 },


		{ 27900 , 450 },
		{ 27900 , 400 },
		{ 27900 , 350 },
		{ 27900 , 300 },
		{ 27900 , 250 },
		{ 27900 , 200 },



		{ 28200 , 450 },
		{ 28200 , 400 },
		{ 28200 , 350 },
		{ 28200 , 300 },
		{ 28200 , 250 },
		{ 28200 , 200 },

	};

	for (int i = 0; i < 60; ++i)
	{
		m_NeedleList.push_back(new CAir(tAirInfo[i].fX, tAirInfo[i].fY));
	}


	for (auto& iter : m_NeedleList)
	{
		iter->Initialize();
	}
}

void CAirMgr::Update(void)
{
	for (auto& iter = m_NeedleList.begin(); iter != m_NeedleList.end();)
	{
		if ((*iter)->Update() == OBJ_DEAD)
		{
			Safe_Delete<CAir*>(*iter);
			iter = m_NeedleList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void CAirMgr::Late_Update(void)
{
	for (auto& iter : m_NeedleList)
	{
		iter->Late_Update();
	}
}

void CAirMgr::Render(HDC hDC)
{
	for (auto& iter : m_NeedleList)
	{
		iter->Render(hDC);
	}
}

void CAirMgr::Release(void)
{
	for (auto iter = m_NeedleList.begin(); iter != m_NeedleList.end();)
	{
		(*iter)->Release();
		Safe_Delete<CAir*>(*iter);

		iter = m_NeedleList.erase(iter);
	}
}
