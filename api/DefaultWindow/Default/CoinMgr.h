#pragma once
#include "Include.h"
#include "Coin.h"

class CCoinMgr
{
public:
	CCoinMgr();
	~CCoinMgr();
public:
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);


	list<CCoin*>	Get_Coin_List() { return m_CoinList; }

	static		CCoinMgr*&		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CCoinMgr;
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
	static CCoinMgr*	m_pInstance;
	list<CCoin*>	m_CoinList;
};