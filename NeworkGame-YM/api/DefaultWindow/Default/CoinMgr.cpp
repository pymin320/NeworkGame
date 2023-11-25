#include "stdafx.h"
#include "CoinMgr.h"

CCoinMgr* CCoinMgr::m_pInstance = nullptr;

CCoinMgr::CCoinMgr()
{
}


CCoinMgr::~CCoinMgr()
{
	Release();
}

void CCoinMgr::Initialize(void)
{
	INFO tCoinInfo[196] =
	{
	{ 2000,250,40,60 },
	{ 2000,220,40,60 },
	{ 2000,190,40,60 },
	{ 2000,160,40,60 },
	{ 2050,250,40,60 },
	{ 2050,220,40,60 },
	{ 2050,190,40,60 },
	{ 2050,160,40,60 },
	{ 2100,250,40,60 },
	{ 2100,220,40,60 },
	{ 2100,190,40,60 },
	{ 2100,160,40,60 },
	{ 2150,250,40,60 },
	{ 2150,220,40,60 },
	{ 2150,190,40,60 },
	{ 2150,160,40,60 },


	{ 12100,400,40,60},
	{ 12160,300,40,60},
	{ 12200,300,40,60},
	{ 12280,400,40,60},

	{6300,150,40,60},
	{6500,150,40,60},			//22
	{}, {}, {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},//47

	{5400,240},		//하트
	{5460,300},
	{5520,360},
	{5580,420},
	{5610,480},
	{5640,420},
	{5700,360},
	{5760,300},
	{5820,240},
	{5760,180},
	{5700,120},
	{5670,120 },
	{5610,180},
	{5520,120},
	{5580,120},
	{5460,180},			//63
	{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
	{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}, //98
	{},{},{},{},{},{},{},{}, //106
	{},{},{},{},{},{},{},{},{},{}, //118
	{},{},{},{},{},
	{},{},{},{},{},
	{},{},{},{},{},
	{},{},{},{},{},
	{},{},{},{},{},					//143
	{},{},{},						//146
	{},{},{},{},{},{},{},{},{},		//145
	{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}, //160
	{30400,300},
	{30400,180},
	{ 30440,280 },
	{ 30440,200 },
	{ 30360,280 },
	{ 30360,200 },
	{ 30340,240 },
	{ 30460,240 },

	{ 30700,300 },
	{ 30700,180 },
	{ 30740,280 },
	{ 30740,200 },
	{ 30660,280 },
	{ 30660,200 },
	{ 30640,240 },
	{ 30760,240 },
	};


	for (int i = 0; i < 5; ++i)				//사각형
	{
		for (int j = 0; j < 5; j++)
		{
			tCoinInfo[i * 5 + j + 22] = { float(i * 80 + 10160 ) , float(j * 50 + 200), 40.f, 60.f };
		}
	}			

	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; j++)
		{
			tCoinInfo[i * 5 + j + 64] = { float(i * 80 + 9600) , float(j * 50 + 200), 40.f, 60.f };
		}
	}

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 3; j++)
		{
			tCoinInfo[i * 3 + j + 89] = { float(i * 80 + 10560) , float(j * 50 + 250), 40.f, 60.f };
		}
	}


	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 2; j++)
		{
			tCoinInfo[i * 2 + j + 101] = { float(i * 80 + 19400) , float(j * 50 + 250), 40.f, 60.f };
		}
	}

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 2; j++)
		{
			tCoinInfo[i * 2 + j + 110] = { float(i * 80 + 21186) , float(j * 50 + 250), 40.f, 60.f };
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		tCoinInfo[i + 116] = { float(i * 80 + 31400) , 450.f, 40.f, 60.f };		//118
	}

	for (int i = 0; i < 25; ++i)
	{
		tCoinInfo[i + 119] = { float(i * 80 + 24800) , 470.f, 40.f, 60.f };
	}

	for (int i = 0; i < 3; ++i)
	{
		tCoinInfo[i + 143] = { float(i * 80 + 31810) , 450.f, 40.f, 60.f };
	}


	for (int i = 0; i < 3; ++i)
	{
		tCoinInfo[i + 146] = { float(i * 80 + 32810) , 450.f, 40.f, 60.f };
	}

	for (int i = 0; i < 3; ++i)
	{
		tCoinInfo[i + 149] = { float(i * 80 + 33810) , 450.f, 40.f, 60.f };
	}

	for (int i = 0; i < 3; ++i)
	{
		tCoinInfo[i + 152] = { float(i * 80 + 32400) , 450.f, 40.f, 60.f };	
	}

	for (int i = 0; i < 3; ++i)
	{
		tCoinInfo[i + 155] = { float(i * 80 + 33400) , 450.f, 40.f, 60.f };	
	}

	for (int i = 0; i < 2; ++i)
	{
		tCoinInfo[i + 158] = { float(i * 80 + 33650) , 470.f, 40.f, 60.f };
	}



	for (int i = 0; i < 5; ++i)
	{
		tCoinInfo[i + 184] = { float(37280) ,  float(i * 80 + 150), 40.f, 60.f };
	}

	for (int i = 0; i < 5; ++i)
	{
		tCoinInfo[i + 189] = { float(37520) ,  float(i * 80 + 150), 40.f, 60.f };
	}
	
	tCoinInfo[194] = { 37360.f , 270.f, 40.f, 60.f };
	tCoinInfo[195] = { 37450.f , 390.f, 40.f, 60.f };

	for (int i = 0; i < 196; ++i)
	{
		m_CoinList.push_back(new CCoin(tCoinInfo[i].fX, tCoinInfo[i].fY));
	}


	for (auto& iter : m_CoinList)
	{
		iter->Initialize();
	}
}



void CCoinMgr::Update(void)
{
	for (auto& iter = m_CoinList.begin(); iter != m_CoinList.end();)
	{
		if ((*iter)->Update() == OBJ_DEAD)
		{
			Safe_Delete<CCoin*>(*iter);
			iter = m_CoinList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void CCoinMgr::Late_Update(void)
{
	for (auto& iter : m_CoinList)
	{
		iter->Late_Update();
	}
}

void CCoinMgr::Render(HDC hDC)
{
	for (auto& iter : m_CoinList)
	{
		iter->Render(hDC);
	}
}

void CCoinMgr::Release(void)
{
	for (auto iter = m_CoinList.begin(); iter != m_CoinList.end();)
	{
		(*iter)->Release();
		Safe_Delete<CCoin*>(*iter);

		iter = m_CoinList.erase(iter);
	}
}

