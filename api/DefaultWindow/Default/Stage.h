#pragma once
#include "Scene.h"
class CStage :
	public CScene
{
public:
	CStage();
	virtual ~CStage();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void		Pause(HDC hDC);



	bool			m_bPause;
	POINT			m_tMouse;
	INFO			m_tMouseInfo;
	RECT			m_tMouseRect;
	
	RECT			m_tStartRect;
	RECT			m_tExitRect;
	RECT			m_tPauseRect;

	RECT			RC;
	int				iNum;
	int				m_iCount;
	int				m_iCount2;

	int				iNum2;
};

