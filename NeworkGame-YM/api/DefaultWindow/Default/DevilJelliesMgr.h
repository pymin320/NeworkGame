#pragma once
#include "DevilJellies.h"

class CDevilJelliesMgr
{
public:
	CDevilJelliesMgr();
	~CDevilJelliesMgr();

	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);


	list<DevilJellies*>	Get_DevilJellies_List() { return m_DevilJelliesList; }

	static		CDevilJelliesMgr*&		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CDevilJelliesMgr;
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
	static CDevilJelliesMgr*	m_pInstance;
	list<DevilJellies*>	m_DevilJelliesList;
};
