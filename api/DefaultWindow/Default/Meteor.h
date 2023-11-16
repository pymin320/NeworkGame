#pragma once
#include "Obj.h"
class CMeteor :
	public CObj
{
public:
	CMeteor();
	virtual ~CMeteor();


	virtual void			Initialize(void);
	virtual const int&&		Update(void);
	virtual void			Late_Update(void);
	virtual void			Render(HDC hDC);
	virtual void			Release(void);
	virtual void			PlayerColiision(void);
	virtual void			Set_Hp(void);


private:
	bool		m_bBullet;
	int			m_iCount;
};

