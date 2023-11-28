#pragma once
#include "Fork.h"

class CForkMgr
{
public:
	CForkMgr();
	~CForkMgr();


public:
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);
	std::list<CFork*>	Get_Fork_List() { return m_ForkList; }


	static		CForkMgr*&		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CForkMgr;
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
	static CForkMgr*	m_pInstance;
	list<CFork*>	m_ForkList;
};

