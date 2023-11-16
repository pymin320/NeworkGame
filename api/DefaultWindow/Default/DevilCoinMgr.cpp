#include "stdafx.h"
#include "DevilCoinMgr.h"
CDevilCoinMgr* CDevilCoinMgr::m_pInstance = nullptr;

CDevilCoinMgr::CDevilCoinMgr()
{
}


CDevilCoinMgr::~CDevilCoinMgr()
{
	Release();
}

void CDevilCoinMgr::Initialize(void)
{
	INFO tDevilcoinInfo[4] =
	{
	{ 8050 ,100 , 40, 60},
	{ 8150, 100, 40, 60},
	{ 8250, 100, 40, 60},
	{ 21834, 150},
	};


	for (int i = 0; i < 4; ++i)
	{
		m_CoinList.push_back(new CDevilCoin(tDevilcoinInfo[i].fX, tDevilcoinInfo[i].fY));
	}


	for (auto& iter : m_CoinList)
	{
		iter->Initialize();
	}

}

void CDevilCoinMgr::Update(void)
{
	for (auto& iter = m_CoinList.begin(); iter != m_CoinList.end();)
	{
		if ((*iter)->Update() == OBJ_DEAD)
		{
			Safe_Delete<CDevilCoin*>(*iter);
			iter = m_CoinList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void CDevilCoinMgr::Late_Update(void)
{
	for (auto& iter : m_CoinList)
	{
		iter->Late_Update();
	}
}

void CDevilCoinMgr::Render(HDC hDC)
{
	for (auto& iter : m_CoinList)
	{
		iter->Render(hDC);
	}
}

void CDevilCoinMgr::Release(void)
{
	for (auto iter = m_CoinList.begin(); iter != m_CoinList.end();)
	{
		(*iter)->Release();
		Safe_Delete<CDevilCoin*>(*iter);

		iter = m_CoinList.erase(iter);
	}
}
