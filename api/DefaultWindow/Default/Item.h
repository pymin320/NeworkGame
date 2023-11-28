#pragma once
#include "Obj.h"
class CItem :
	public CObj
{
public:
	CItem();
	virtual ~CItem();

	virtual void			Initialize(void)			PURE;
	virtual const int&&		Update(void)				PURE;
	virtual void			Late_Update(void)			PURE;
	virtual void			Render(HDC _hDC)			PURE;
	virtual void			Release(void)				PURE;
	virtual void			PlayerColiision(void)		PURE;
	virtual void			Set_Hp(void)				PURE;


	virtual int Itemtype(void) { return m_iItemtype; }



private:
	int  m_iItemtype;

};

