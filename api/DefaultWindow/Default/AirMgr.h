#pragma once
#include "Air.h"

class CAirMgr
{
public:
	CAirMgr();
	~CAirMgr();


public:
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

	list<CAir*>	Get_Needle_List() { return m_NeedleList; }

	static		CAirMgr*&		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CAirMgr;
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
	static CAirMgr*	m_pInstance;
	list<CAir*>	m_NeedleList;
};

