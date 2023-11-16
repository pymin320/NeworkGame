#include "stdafx.h"
#include "GoldMgr.h"

CGoldMgr* CGoldMgr::m_pInstance = nullptr;


CGoldMgr::CGoldMgr()
{
}


CGoldMgr::~CGoldMgr()
{
	Release();
}

void CGoldMgr::Initialize(void)
{
	INFO tCoinInfo[100] =
	{
		{5540, 180},
		{5680, 180},
		{5480, 240},
		{5610, 240},
		{5740, 240},
		{5540, 300},
		{5680, 300},
		{5610, 300},
		{5610, 360},
		{5610, 360},

		{ 6300,100,40,60 },
		{ 6500,100,40,60 },		//12

		{},{},{},{},{},
		{},{},{},{},{},
		{},{},{},{},{},
		{},{},{},{},{},{},		//33
		{11360,120},
		{11360,170},
		{11320,220},
		{11400,220},
		{11200,220},
		{11280,220},
		{11360,220},
		{11440,220},
		{11520,220},
		{11290,270},
		{11360,270},
		{11430,270},
		{11325,320},
		{11395,320},
		{11310,370},
		{ 11410,370 },
		//48
	{},{},{},{},{},{},{},{}, //56
	{},{},{},{},{},{},{},{}, //64
							 //65
	{23630 , 330 }, {23710, 330 }, { 23790 , 330 },
	{ 28650, 460 },
	{ 28950, 460 },
	{27500,250},
	{ 27800,250 },
	{ 28100,250 },
	{ 28400,250 },

	{ 30550,370 },
	{ 30550,250 },
	{ 30590,350 },
	{ 30590,270 },
	{ 30510,350 },
	{ 30510,270 },
	{ 30490,310 },
	{ 30610,310 },

	{ 30850,370 },
	{ 30850,250 },
	{ 30890,350 },
	{ 30890,270 },
	{ 30810,350 },
	{ 30810,270 },
	{ 30790,310 },
	{ 30910,310 },

	};


	for (int j = 0; j < 5; j++)
	{
		tCoinInfo[j + 13] = { float(10480) , float(j * 50 + 200), 40.f, 60.f };
	}

	for (int j = 0; j < 5; j++)
	{
		tCoinInfo[j + 18] = { float(10860) , float(j * 50 + 200), 40.f, 60.f };
	}
	for (int j = 0; j < 5; j++)
	{
		tCoinInfo[j + 23] = { float(10480 + j * 80) , float(200), 40.f, 60.f };
	}
	for (int j = 0; j < 5; j++)
	{
		tCoinInfo[j + 28] = { float(10480 + j * 80) , float(400), 40.f, 60.f };
	}

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 2; j++)
		{
			tCoinInfo[i * 2 + j + 49] = { float(i * 80 + 20168) , float(j * 50 + 250), 40.f, 60.f };
		}
	}

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 2; j++)
		{
			tCoinInfo[i * 2 + j + 57] = { float(i * 80 + 22204) , float(j * 50 + 250), 40.f, 60.f };
		}
	}


	for (int j = 0; j < 5; j++)
	{
		tCoinInfo[90 + j] = { float(37660) , float(j * 80 + 150), 40.f, 60.f };
	}

	tCoinInfo[95] = { 37740.f , 190.f, 40.f, 60.f };
	tCoinInfo[96] = { 37740.f , 430.f, 40.f, 60.f };
	tCoinInfo[97] = { 37820.f , 230.f, 40.f, 60.f };
	tCoinInfo[98] = { 37820.f , 310.f, 40.f, 60.f };
	tCoinInfo[99] = { 37820.f , 390.f, 40.f, 60.f };




	for (int i = 0; i < 100; ++i)
	{
		m_CoinList.push_back(new CGold(tCoinInfo[i].fX, tCoinInfo[i].fY));
	}


	for (auto& iter : m_CoinList)
	{
		iter->Initialize();
	}
}

void CGoldMgr::Update(void)
{
	for (auto& iter = m_CoinList.begin(); iter != m_CoinList.end();)
	{
		if ((*iter)->Update() == OBJ_DEAD)
		{
			Safe_Delete<CGold*>(*iter);
			iter = m_CoinList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void CGoldMgr::Late_Update(void)
{
	for (auto& iter : m_CoinList)
	{
		iter->Late_Update();
	}
}

void CGoldMgr::Render(HDC hDC)
{
	for (auto& iter : m_CoinList)
	{
		iter->Render(hDC);
	}
}

void CGoldMgr::Release(void)
{
	for (auto iter = m_CoinList.begin(); iter != m_CoinList.end();)
	{
		(*iter)->Release();
		Safe_Delete<CGold*>(*iter);

		iter = m_CoinList.erase(iter);
	}
}
