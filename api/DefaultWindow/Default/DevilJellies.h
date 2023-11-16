#pragma once
#include "Obj.h"
class DevilJellies :
	public CObj
{
public:
	DevilJellies();
	DevilJellies(float _m_fX, float _m_fY);
	virtual ~DevilJellies();

	virtual void			Initialize(void)  override;
	virtual const int&&		Update(void) override;
	virtual void			Late_Update(void) override;
	virtual void			Render(HDC hDC) override;
	virtual void			Release(void) override;

private:
	int		m_iJellyX;
	int		m_iCount;
	bool	m_bJelly;
};

