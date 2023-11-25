#pragma once
#include "Item.h"
class CDevilCoin :
	public CItem
{
public:
	CDevilCoin();
	CDevilCoin(float _m_fX, float _m_fY);
	~CDevilCoin();

	virtual void			Initialize(void);
	virtual const int&&		Update(void);
	virtual void			Late_Update(void);
	virtual void			Render(HDC hDC);
	virtual void			Release(void);
	virtual void			PlayerColiision(void);
	virtual void			Set_Hp(void);

	void	PetColiision(INFO _Pet);

private:
	int		m_iCoinFrame;
	int		m_iCount;
	bool	m_bCoin;

	float	m_fAngle;
};

