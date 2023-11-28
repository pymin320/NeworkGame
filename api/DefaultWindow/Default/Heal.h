#pragma once
#include "Obj.h"


class CHeal :
	public CObj
{
public:
	CHeal();
	virtual ~CHeal();

	virtual void			Initialize(void)  override;
	virtual const int&&		Update(void) override;
	virtual void			Late_Update(void) override;
	virtual void			Render(HDC hDC) override;
	virtual void			Release(void) override;


private:
	int			m_iCount;
};

