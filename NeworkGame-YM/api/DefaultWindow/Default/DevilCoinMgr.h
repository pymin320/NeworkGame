#pragma once
#include "DevilCoin.h"
#include "Include.h"

class CDevilCoinMgr
{
public:
	CDevilCoinMgr();
	~CDevilCoinMgr();

public:
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

	list<CDevilCoin*>	Get_Devil_Coin_List() { return m_CoinList; }

	static		CDevilCoinMgr*&		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CDevilCoinMgr;
		}

		return m_pInstance;
	}

	static	void	Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	static CDevilCoinMgr*	m_pInstance;
	list<CDevilCoin*>	m_CoinList;
};


