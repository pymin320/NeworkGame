#pragma once
#include "Frog.h"

class CFrogMgr
{
public:
	CFrogMgr();
	~CFrogMgr();

public:
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);
	list<CFrog*>	Get_Needle_List() { return m_NeedleList; }

	static		CFrogMgr*&		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CFrogMgr;
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
	static CFrogMgr*	m_pInstance;
	list<CFrog*>	m_NeedleList;
};

