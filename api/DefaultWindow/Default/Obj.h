#pragma once

#include "Include.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual		void	Initialize(void)		PURE;
	virtual		const int&&		Update(void)	PURE;
	virtual		void	Late_Update(void)		PURE;
	virtual		void	Render(HDC hDC)			PURE;
	virtual		void	Release(void)			PURE;

	void		Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}
	void		Set_Dir(DIRECTION eDir) { m_eDir = eDir; }
	void		Dead() { m_iHp = 0; }

	inline const INFO&	Get_Info(void)	const { return m_tInfo; }
	inline const RECT&	Get_Rect(void)	const { return m_tRect; }

protected:
	void		Update_Rect(void);


protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	FRAME		m_tFrame;
	FRAME		m_tFrame2;


	float		m_fSpeed;
	int			m_eDir;

	int			m_iHp;
};

