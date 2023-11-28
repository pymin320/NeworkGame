#pragma once
#include "Item.h"

class CJelly :
	public CItem
{
public:
	CJelly();
	CJelly(float _m_fX, float _m_fY);
	virtual ~CJelly();

	virtual void			Initialize(void);
	virtual const int&&		Update(void);
	virtual void			Late_Update(void);
	virtual void			Render(HDC hDC);
	virtual void			Release(void);
	virtual void			PlayerColiision(void);
	virtual void			Set_Hp(void);

	void			PetColiision(INFO _Pet);

private:
	INFO	m_tEffect;
	RECT	m_tEffectR;

	bool	m_bScore;
	float	m_fAngle;

	int		m_iJellyType;
	int		m_JellyCount;
	bool	m_bJellyDead;

	int		m_iJellyScore;
};

