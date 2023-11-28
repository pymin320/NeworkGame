#pragma once
#include "Obj.h"

class CUi
	:public CObj
{
public:
	CUi();
	~CUi();

public:
	virtual void			Initialize(void);
	virtual const int&&		Update(void);
	virtual void			Late_Update(void);
	virtual void			Render(HDC hDC);
	virtual void			Release(void);



	void	Get_Hp(float _Hp) { m_fPlayerHp = _Hp; }
	void	Reset_1st() { m_bHighScore = false; }
	void	Get_Player();



private:
	float		m_fPlayerHp;
	INFO		m_tHP;
	RECT		m_tHPrect;

	float		m_fOppHp;
	float		m_fOppOriginHp;
	INFO		m_tOppHP;
	RECT		m_tOppHPrect;

	INFO		m_tBonus;
	RECT		m_tBonusRect;

	INFO		m_tScore;
	RECT		m_tScoreRect;
	int			m_iScore;

	int			m_iCoin;
	INFO		m_tCoin;
	RECT		m_tCoinRect;

	INFO		m_tJump;
	RECT		m_tJumpRect;

	INFO		m_tSlide;
	RECT		m_tSlideRect;
	
	float		m_fPlayerBar;

	int			m_iPlayer;


	bool		m_bHp;
	bool		m_bHighScore;
};

