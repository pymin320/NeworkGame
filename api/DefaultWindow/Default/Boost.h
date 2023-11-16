#pragma once
#include "Obj.h"
class CBoost :
	public CObj
{
public:
	CBoost();
	virtual ~CBoost();

	virtual void			Initialize(void)  override;
	virtual const int&&		Update(void) override;
	virtual void			Late_Update(void) override;
	virtual void			Render(HDC hDC) override;
	virtual void			Release(void) override;
};

