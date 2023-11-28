#pragma once
#include "Obj.h"

class CGiga2 :
	public CObj
{
public:
	CGiga2();
	virtual ~CGiga2();


	virtual void			Initialize(void)  override;
	virtual const int&&		Update(void) override;
	virtual void			Late_Update(void) override;
	virtual void			Render(HDC hDC) override;
	virtual void			Release(void) override;
};

