#pragma once
#include "Pumkin.h"

class CPumkinMgr
{
public:
	CPumkinMgr();
	~CPumkinMgr();

public:
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

	list<CPumkin*>	Get_Needle_List() { return m_NeedleList; }

	static		CPumkinMgr*&		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CPumkinMgr;
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
	static CPumkinMgr*	m_pInstance;
	list<CPumkin*>	m_NeedleList;
};

