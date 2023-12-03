#include "stdafx.h"
#include "ScoreMgr.h"

CScoreMgr* CScoreMgr::m_pInstance = nullptr;
int CScoreMgr::m_iScore(0);
int CScoreMgr::m_iCoin(0);
float CScoreMgr::m_fHp(0);
float CScoreMgr::m_fPosx(0);
float CScoreMgr::m_fPosy(0);

int CScoreMgr::m_iJellyType(BASE);
int CScoreMgr::m_iCookieType(COFFEECOOKIE);
int CScoreMgr::m_iHighScore(1);
int CScoreMgr::m_iMaxCoin(0);


CScoreMgr::CScoreMgr()
{
}


CScoreMgr::~CScoreMgr()
{
	Release();
}

void CScoreMgr::Initialize(void)
{
}

int CScoreMgr::Update(void)
{
	return OBJ_NOEVENT;
}

void CScoreMgr::Release(void)
{
}
