#pragma once
#include "Obj.h"
class CGiga :
	public CObj
{
public:
	CGiga();
	virtual ~CGiga();


	virtual void			Initialize(void)  override;
	virtual const int&&		Update(void) override;
	virtual void			Late_Update(void) override;
	virtual void			Render(HDC hDC) override;
	virtual void			Release(void) override;
};

