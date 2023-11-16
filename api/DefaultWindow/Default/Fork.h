#pragma once
#include "Obj.h"
class CFork :
	public CObj
{
public:
	CFork();
	CFork(float _m_fX, float _m_fY);
	~CFork();

	virtual void			Initialize(void);
	virtual const int&&		Update(void);
	virtual void			Late_Update(void);
	virtual void			Render(HDC hDC);
	virtual void			Release(void);

	void Dead(void);

private:
	float		m_fJumpPower;
	float		m_fJumpTime;

	bool		m_bSound;
};

