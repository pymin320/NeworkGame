#pragma once
#include "Ui.h"

class CUiMgr
{
public:
	CUiMgr();
	~CUiMgr();

public:
	void		Initialize();
	void		Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();
	list<CObj*>	Get_Ui_List() { return m_listUi; }

public:
	static		CUiMgr* Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CUiMgr;
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
	static CUiMgr* m_pInstance;
	list<CObj*>				m_listUi;
};