#pragma once
#include "Bullet.h"

class CBulletMgr
{
public:
	CBulletMgr();
	~CBulletMgr();

public:
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);


	list<CBullet*>	Get_Jelly_List() { return m_JellyList; }

	static		CBulletMgr*&		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CBulletMgr;
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
	static CBulletMgr*	m_pInstance;
	list<CBullet*>	m_JellyList;
};
