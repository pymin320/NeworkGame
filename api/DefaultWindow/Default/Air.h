#pragma once
#include "Obj.h"
class CAir :
	public CObj
{
public:
	CAir();
	CAir(float _fX, float _fY);
	~CAir();

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
	int			m_iAirspeed;

	float		m_fTop;
	bool		m_bSound;
};

