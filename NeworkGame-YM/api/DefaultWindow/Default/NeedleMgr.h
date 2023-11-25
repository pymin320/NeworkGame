#pragma once
#include "Obj.h"
#include "Needle.h"

class CNeedleMgr
{
public:
	CNeedleMgr();
	~CNeedleMgr();
public:
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);
	list<CNeedle*>	Get_Needle_List() { return m_NeedleList; }

	static		CNeedleMgr*&		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CNeedleMgr;
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
	static CNeedleMgr*	m_pInstance;
	list<CNeedle*>	m_NeedleList;
};

