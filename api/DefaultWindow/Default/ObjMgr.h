#pragma once

#include "Obj.h"

class CObjMgr
{
private:
	CObjMgr();
	virtual ~CObjMgr();

public:
	CObj*		Get_Player() { 
		if (m_ObjList[OBJ_PLAYER].empty()) {
			return nullptr;
		}
		return m_ObjList[OBJ_PLAYER].front(); 
	}
	CObj*		Get_Target(OBJID eID, CObj* pObj) {};
	list<CObj*>& Get_Obj_List(const OBJID& _ID) { return m_ObjList[_ID]; }
public:
	void		Initialize(void);
	void		Add_Object(OBJID eID, CObj* pObj);
	int			Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

private:
	list<CObj*>	m_ObjList[OBJ_END];


public:
	static		CObjMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CObjMgr;
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
	static CObjMgr*			m_pInstance;

};

