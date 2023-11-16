#pragma once
#include "Obj.h"

class CFrog :
	public CObj
{
public:
	CFrog();
	CFrog(float _fX, float _fY);
	~CFrog();

public:
	virtual void			Initialize(void);
	virtual const int&&		Update(void);
	virtual void			Late_Update(void);
	virtual void			Render(HDC hDC);
	virtual void			Release(void);

	void Dead() { m_iHp = 0; };

private:
	float		m_fJumpPower;
	float		m_fJumpTime;
	bool		m_bSound;
};

