#pragma once
#include "Obj.h"

class CTile:
	public CObj
{
public:
	CTile();
	virtual ~CTile();


	virtual void			Initialize(void);
	virtual const int&&		Update(void);
	virtual void			Late_Update(void);
	virtual void			Render(HDC _hDC);
	virtual void			Release(void);
};

