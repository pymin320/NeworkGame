#pragma once
#include "Obj.h"


class COpp :
	public CObj
{
public:
	COpp();
	virtual ~COpp();

public:
	virtual void Initialize(void) override;
	virtual const int&& Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Late_Update(void) override;

	float		Set_Hp() { return m_fHp; }
	int			Get_Playertype() { return m_iPlayertype; }
	int			Get_Cookietype() { return m_eCurState; }
	int			Set_Cookietype(int _iCookieType) { m_iCookieType = _iCookieType; }
	void		Get_PlayerHp(float _Hp) { m_fHp = _Hp; }
	float		Get_PlayerPosx() { return m_tInfo.fX; }
	float		Get_PlayerPosy() { return m_tInfo.fY; }
	void		Collision();
	void		CollisionDevil();
	void		Get_Itemtype(OBJID _Item);
	int			Set_State();

	bool		Set_Endgame() { return m_bEndgame; }
	bool		Cutscene() { return m_bCut; }

	bool		End() { return m_bCutScene2; }

private:
	void		Key_Input(void);
	void		OffSet(void);
	void		Jumping(void);

	int						m_iPlayertype;


	STATE					m_ePreState;
	STATE					m_eCurState;


	unsigned int			m_iCount;
	unsigned int			m_iCountColli;

	float					m_fJumpPower;
	float					m_fJumpTime;
	unsigned int			m_iJumpCount;
	unsigned int			m_iJumpFrameCount;

	bool					m_bSlide;

	int						m_iJumpFrame;

	float					m_fHp;

	unsigned	int			m_iColliTime;
	int						m_iColliFrame;

	bool					m_bCollision;

	unsigned int			m_BoostCount;

	int						m_iDevilJellyCount;


	int						m_iDevilCount;
	int						m_iDevilFrame;
	int						m_iDevilState;

	int						m_iDevilCount2;
	int						m_iDevilFrame2;
	int						m_iDevilState2;

	int						m_GigaCount;


	INFO					m_tFontInfo;
	RECT					m_tFontRect;

	int						m_iCookieType;

	int						m_iDeadCount;
	int						m_iDeadFrame;
	int						m_iDeadState;

	int						m_iZombieX;
	int						m_iZombieY;

	int						m_iZombieLife;

	bool					m_bEndgame;


	bool					m_bScrollY;
	int						m_iScrollCount;

	int						m_iZombieCount;
	int						m_iZombieFrame;
	int						m_iZombieState;

	int						m_EndCount;
	bool					m_bEnd;
	bool					m_bCut;


	int						m_iDevilRun;
	float					m_fDevilRun;
	float					m_fRunplus;

	int						m_iRunCount;

	int						m_iSlideCount;


	int						m_iPaCount;
	int						m_iPaFrame;
	bool					m_bPa;
	int						m_iPaCount2;
	bool					m_bPa2;
	float					m_fRunaway;


	int						m_iWitchColli;
	bool					m_bWitchColli;

	bool					m_bWitchSound;
	int						m_iUp;
	bool					m_bUp;
	bool					m_bUpSound;

	bool					m_bQ;
	bool					m_bW;
	bool					m_bE;
	int						m_iCountQ;
	int						m_iCountW;
	int						m_iCountE;

	bool					m_bCutScene2;
	bool					m_bCurbySound;

	int						m_iEnd2;
	bool					m_bEnd2;
};