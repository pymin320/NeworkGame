#pragma once
#include "Gold.h"

class CGoldMgr
{
public:
	CGoldMgr();
	~CGoldMgr();

public:
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

	list<CGold*>	Get_Coin_List() { return m_CoinList; }

	static		CGoldMgr*&		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CGoldMgr;
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
	static CGoldMgr*	m_pInstance;
	list<CGold*>	m_CoinList;
};

