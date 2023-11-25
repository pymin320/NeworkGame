#pragma once
#include "Obj.h"
class CSmall :
	public CObj
{
public:
	CSmall();
	virtual ~CSmall();

	virtual void			Initialize(void)  override;
	virtual const int&&		Update(void) override;
	virtual void			Late_Update(void) override;
	virtual void			Render(HDC hDC) override;
	virtual void			Release(void) override;


};

