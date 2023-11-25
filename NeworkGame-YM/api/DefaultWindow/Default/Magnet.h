#pragma once
#include "Obj.h"
class CMagnet :
	public CObj
{
public:
	CMagnet();
	virtual ~CMagnet();

	virtual void			Initialize(void)  override;
	virtual const int&&		Update(void) override;
	virtual void			Late_Update(void) override;
	virtual void			Render(HDC hDC) override;
	virtual void			Release(void) override;
};

