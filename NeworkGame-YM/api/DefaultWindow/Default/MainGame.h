#pragma once

#include "Include.h"
#include "Player.h"
#include "Obj.h"

class CMainGame
{
public:				// 持失切, 社瑚切
	CMainGame();
	~CMainGame();
public:
	void	Initialize(void);
	void	Update(void);
	void	Late_Update(void);
	void	Render(void);
	void	Release(void);


private:
	HDC			m_hDC;
	TCHAR		m_szFPS[64];
	int			m_iFPS;
	DWORD		m_dwTime;
	float		m_fTime;
};

