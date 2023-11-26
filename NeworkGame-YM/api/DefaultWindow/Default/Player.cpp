#include "stdafx.h"
#include "Player.h"
#include "LineMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "Pet.h"
#include "ScoreMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"


CPlayer::CPlayer()
	:m_iColliTime(GetTickCount()), m_iCountColli(GetTickCount())
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo.fX = 140.f;
	m_tInfo.fY = 460.f;

	m_tInfo.fCX = 150.f;
	m_tInfo.fCY = 150.f;

	m_eCurState = WALK;

	m_fJumpPower = 12.f;
	m_fJumpTime = 0.f;


	m_bSlide = false;
	m_bCollision = false;
	m_iColliFrame = 0;

	m_fSpeed = 7.0f;

	m_iCount = 0;

	m_tFrame.iFrameStart = 0;
	m_iJumpFrame = 0;
	m_fHp = 0;

	m_BoostCount = 0;
	m_iDevilJellyCount = 12;

	m_tFontInfo.fCX = 32;
	m_tFontInfo.fCY = 38;

	m_iDevilFrame = 0;
	m_iDevilCount = 0;
	m_iDevilState = 0;

	m_iDevilFrame2 = 0;
	m_iDevilCount2 = 0;
	m_iDevilState2 = 0;

	m_GigaCount = 0;

	m_iDeadCount = 0;
	m_iDeadFrame = 0;
	m_iDeadState = 0;
	m_tFrame2.iFrameStart = 0;

	m_iZombieX = 0;
	m_iZombieX = 0;

	m_iZombieCount = 0;
	m_iZombieFrame = 0;
	m_iZombieState = 0;
	m_EndCount = 0;
	m_iDevilRun = 37800;

	m_iCookieType = COFFEECOOKIE;

	m_bEndgame = false;

	m_bEnd = false;
	m_bCut = false;
	m_fDevilRun = 300;
	m_fRunplus = 0.f;
	m_iRunCount = 0;
	m_iSlideCount = 0;

	m_iUp = 600;

	m_bScrollY = false;
	m_iScrollCount = 0;

	m_iPaCount = 0;
	m_iPaFrame = 0;
	m_iPaCount2 = 0;
	m_fRunaway = 0;
	m_bUp = false;
	m_bQ = false;
	m_bW = false;
	m_bE = false;
	m_iCountQ = 0;
	m_iCountW = 0;
	m_iCountE = 0;

	m_bPa = false;
	m_bPa2 = false;
	m_bWitchSound = false;
	m_bUpSound = false;
	m_bWitchColli = false;

	m_bCutScene2 = false;
	m_bCurbySound = false;
	m_bEnd2 = false;

	m_iEnd2 = 0;

	m_iCookieType = CScoreMgr::Get_Instance()->Get_CookieType();

	if (m_iCookieType == COFFEECOOKIE)
	{
		CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/CoffeeCookie.bmp", L"PlayerC");
		CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/CoffeeGiga.bmp", L"DevilGigaC");
		CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/CoffeeCollision.bmp", L"PlayerCollisionC");
		m_iZombieX = 0;
		m_iZombieY = 0;
		m_iZombieLife = 0;
	}

	else if (m_iCookieType == DEVILCOOKIE)
	{
		CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/DevilCookie.bmp", L"Player");
		CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/DevilCollision.bmp", L"PlayerCollision");
		CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Font_Devil.bmp", L"Font_Devil");

		CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/DevilGiga.bmp", L"DevilGiga");
		CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/DevilGigah.bmp", L"DevilGigah");
		m_iZombieX = 0;
		m_iZombieY = 0;
		m_iZombieLife = 0;
	}
	else if (m_iCookieType == ZOMBIECOOKIE)
	{
		CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/ZombieCookie.bmp", L"PlayerZ");
		CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/ZombieGiga.bmp", L"DevilGigaZ");
		CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/ZombieCollision.bmp", L"PlayerCollisionZ");
		m_iZombieX = -35;
		m_iZombieY = +10;
		m_tInfo.fCX = 195.f;
		m_iZombieLife = 1;
	}

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/DevilCookie.bmp", L"Player");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/CoffeeCookie.bmp", L"PlayerC");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/ZombieCookie.bmp", L"PlayerZ");


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/CoffeeGiga.bmp", L"DevilGigaC");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/ZombieGiga.bmp", L"DevilGigaZ");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/zombieRevive.bmp", L"zombieRevive");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Witch.bmp", L"PWitch");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Devil.bmp", L"Devil");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/DevilRun.bmp", L"DevilRun");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Shotgun2.bmp", L"Shotgun2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/adogen.bmp", L"adogen");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/up.bmp", L"up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/curby.bmp", L"curby");
}

const int&& CPlayer::Update(void)
{
	Key_Input();
	Jumping();
	OffSet();

	m_tInfo.fX += m_fSpeed;


	if (m_eCurState == WITCH)
	{
		if (!m_bWitchSound)
		{
			CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
			CSoundMgr::Get_Instance()->PlaySoundW(L"MAPLE.mp3", SOUND_BGM, g_fSound);
			m_bWitchSound = true;
		}
		m_iDevilRun += m_fSpeed;
		m_fDevilRun += m_fRunplus;
		if (m_fDevilRun <= 00)
			m_fRunplus = 6.f;
		else if (m_fDevilRun >= 450)
			m_fRunplus = -6.f;

		if (m_iRunCount + 10000 == GetTickCount())
		{
			m_fSpeed = -7.0f;
			m_fRunplus = 6.0f;
		}
	}


	if (m_eCurState != WITCH)
	{
		m_fHp -= 0.1f;
	}


	m_tFontInfo.fX = m_tInfo.fX - 30;
	m_tFontInfo.fY = m_tInfo.fY - 120;

	if (m_bCollision == true && m_iPlayertype != BOOST && m_eCurState != DEVIL && m_eCurState != WITCH)
	{
		m_fSpeed = 3.5f;
	}



	if (m_iColliTime + 1500 <= GetTickCount())
	{
		m_bCollision = false;
		m_iColliFrame = 0;
		if (m_fSpeed == 3.5f)
			m_fSpeed += 3.5f;
	}

	// 사망 모션
	if (m_iDeadCount == 0 && m_fHp <= 0)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
		CSoundMgr::Get_Instance()->PlaySoundW(L"SoundEff_GameEnd.mp3", SOUND_PLAYER, g_fSound);
		++m_tFrame2.iFrameStart;
		m_iDeadCount = GetTickCount();
	}
	else if (m_iDeadCount + 400 < GetTickCount() && m_tFrame2.iFrameStart < 5 && m_fHp <= 0)
	{
		++m_tFrame2.iFrameStart;
		m_iDeadCount = GetTickCount();
	}


	// 마녀모드
	if (m_tFrame2.iFrameStart == 5)
	{
		if (m_iDeadCount + 2000 < GetTickCount() && m_iZombieLife != 0)
		{
			if (m_iCookieType == ZOMBIECOOKIE && m_fHp <= 0)		// 좀비 부활
			{
				--m_iZombieLife;
				m_fHp = 50;
				m_iPlayertype = REVIVE;
				m_fSpeed = 6.f;
				m_tFrame2.iFrameStart = 0;
				m_iDeadCount = 0;
			}
		}
		if (m_iDeadCount + 2000 < GetTickCount() && m_iZombieLife == 0 && m_fHp <= 0)
		{
			m_bEndgame = true;
		}
	}



	if (m_iCount == 0)
	{
		++m_tFrame.iFrameStart;
		m_iCount = GetTickCount();
	}
	else if (m_iCount + 70 < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_iCount = GetTickCount();
	}

	if (m_tFrame.iFrameStart == 4)
		m_tFrame.iFrameStart = 0;

	if (m_iPaCount == 0 && m_bPa == true)
	{
		m_iPaCount = GetTickCount();
	}
	else if (m_iPaCount + 10 <= GetTickCount() && m_bPa == true)
	{
		++m_iPaFrame;
		m_iPaCount = GetTickCount();
	}

	if (m_iPaFrame >= 5)
	{
		m_iPaFrame = 5;
	}




	// 악마 모드
	if (m_iDevilCount == 0 && m_eCurState == DEVIL)
	{
		m_iDevilCount = GetTickCount();
		m_iDevilFrame = 0;
	}


	else if (m_iDevilCount + 70 < GetTickCount() && m_eCurState == DEVIL)
	{
		++m_iDevilFrame;
		m_iDevilCount = GetTickCount();
	}


	if (m_iDevilFrame == 17 && 10 >= m_iDevilState)
	{
		++m_iDevilState;
		m_iDevilFrame = 14;
	}

	else if (m_iDevilFrame == 22)
	{
		m_eCurState = WALK;
		m_iDevilFrame = 0;
		m_iDevilCount = 0;
		m_iDevilState = 0;
		m_iDevilJellyCount = 12;
		m_fSpeed = 7.0;
	}



	if (m_iDevilCount2 == 0 && m_eCurState == WITCH)
	{
		m_iDevilCount2 = GetTickCount();
		m_iDevilFrame2 = 0;
	}


	else if (m_iDevilCount2 + 70 < GetTickCount() && m_eCurState == WITCH)
	{
		++m_iDevilFrame2;
		m_iDevilCount2 = GetTickCount();
	}


	if (m_iDevilFrame2 == 4)
	{
		m_iDevilFrame2 = 0;
	}



	if (m_eCurState == DOUBLEJUMP && m_iJumpFrame == 0)
	{
		m_iJumpFrameCount = GetTickCount();
		++m_iJumpFrame;
	}
	else if (m_iJumpFrameCount + 70 < GetTickCount())
	{
		++m_iJumpFrame;
		m_iJumpFrameCount = GetTickCount();
	}

	if (m_eCurState == WALK || m_iJumpFrame == 5)
		m_iJumpFrame = 0;


	if (m_iPlayertype == BOOST && m_BoostCount == 0)
	{
		m_BoostCount = GetTickCount();
	}
	else if (m_iPlayertype == BOOST && m_BoostCount + 5000 < GetTickCount())
	{
		m_iPlayertype = WALK;
		m_fSpeed = 7.0f;
	}


	//거대화
	if (m_iPlayertype == GIGA && m_GigaCount == 0)
	{
		m_GigaCount = GetTickCount();
	}
	else if (m_iPlayertype == GIGA && m_GigaCount + 6000 < GetTickCount())
	{
		m_iPlayertype = STATE_END;
		m_GigaCount = 0;
	}


	if (m_bUp)
	{
		m_iUp -= 20;
		if (!m_bUpSound)
		{
			CSoundMgr::Get_Instance()->PlaySoundW(L"soryuegen.mp3", SOUND_PLAYER, g_fSound);
		}
		m_bUpSound = true;
	}
	if (m_iUp <= -100)
	{
		m_iUp = 600;
		m_bUp = false;
		m_bUpSound = false;
	}



	if (750 <= m_tRect.bottom)
	{
		m_fHp = 0;
		m_fSpeed = 0;
	}

	if (m_fHp <= 1)
	{
		m_iPlayertype = DEAD;
		m_fSpeed = 0;
	}


	if (m_bScrollY == true && m_iScrollCount == 0)
	{
		m_iScrollCount = GetTickCount();
		CSoundMgr::Get_Instance()->PlaySoundW(L"Char_Land_Gigantic.wav", SOUND_PLAYER, g_fSound);

	}

	if (m_iScrollCount + 110 > GetTickCount() && m_iScrollCount + 10 < GetTickCount() && m_bScrollY == true)
	{
		CScrollMgr::Get_Instance()->Set_ScrollY(2);
	}
	else if (m_iScrollCount + 210 > GetTickCount() && m_iScrollCount + 110 < GetTickCount() && m_bScrollY == true)
	{
		CScrollMgr::Get_Instance()->Set_ScrollY(-2);
	}

	else if (m_iScrollCount + 210 < GetTickCount())
	{
		m_bScrollY = false;
		m_iScrollCount = 0;
	}


	if (m_eCurState == WITCH)
	{
		if (GetAsyncKeyState('Q'))
		{
			if (m_bQ == false && m_iCountQ == 0)
			{
				m_fRunaway += 15;
				m_bQ = true;
				m_iCountQ = GetTickCount();
			}
			else if (m_iCountQ + 2000 < GetTickCount() && m_bQ == true)
			{
				m_fRunaway += 15;
				m_bQ = false;
				m_iCountQ = 0;
			}
		}
		else if (GetAsyncKeyState('W'))
		{
			if (m_bW == false && m_iCountW == 0)
			{
				m_fRunaway += 25;
				m_bW = true;
				m_iCountW = GetTickCount();
			}
			else if (m_iCountW + 2000 < GetTickCount() && m_bW == true)
			{
				m_fRunaway += 25;
				m_bW = false;
				m_iCountW = 0;
			}
		}
		else if (GetAsyncKeyState('E'))
		{
			if (m_bE == false && m_iCountE == 0)
			{
				m_fRunaway += 35;
				m_bE = true;
				m_iCountE = GetTickCount();
			}
			else if (m_iCountE + 2000 < GetTickCount() && m_bE == true)
			{
				m_fRunaway += 35;
				m_bE = false;
				m_iCountE = 0;
			}
		}
		else if (GetAsyncKeyState('R'))
		{
			if (m_tRect.left + 30 <= m_iDevilRun + m_fSpeed + m_fRunaway && m_iEnd2 == 0)
			{
				m_iEnd2 = GetTickCount();
				m_bEnd2 = true;
			}
			else
			{
				m_fRunaway += 2;
				if (m_bCurbySound == false)
				{
					CSoundMgr::Get_Instance()->PlaySoundW(L"y2mate (mp3cut.net).mp3", SOUND_PLAYER, g_fSound);
					m_bCurbySound = true;
					m_fRunplus = 0;

				}
				if (m_iEnd2 + 5000 < GetTickCount() && m_tRect.left + 30 <= m_iDevilRun + m_fSpeed + m_fRunaway && m_bEnd2 == true)
				{
					m_bCutScene2 = true;
				}
			}
		}
	}

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	m_tFontRect.left = LONG(m_tFontInfo.fX - (m_tFontInfo.fCX * 0.5f));
	m_tFontRect.top = LONG(m_tFontInfo.fY - (m_tFontInfo.fCY * 0.5f));
	m_tFontRect.right = LONG(m_tFontInfo.fX + (m_tFontInfo.fCX * 0.5f));
	m_tFontRect.bottom = LONG(m_tFontInfo.fY + (m_tFontInfo.fCY * 0.5f));



	Update_Rect();
}

void CPlayer::Collision()
{
	if (!m_bCollision && m_iPlayertype != BOOST && m_eCurState != DEVIL && m_iPlayertype != GIGA && m_eCurState != WITCH)
	{
		m_fHp -= 65;
		m_iColliTime = GetTickCount();
		m_bCollision = true;
		CSoundMgr::Get_Instance()->PlaySoundW(L"SoundEff_CrashWithBody.mp3", SOUND_PLAYER, g_fSound);
	}

	else if (m_eCurState == WITCH)
	{
		//CSoundMgr::Get_Instance()->PlaySoundW(L"SoundEff_CrashWithBody.mp3", SOUND_PLAYER, g_fSound);
		if (!m_bWitchColli)
		{
			CSoundMgr::Get_Instance()->PlaySoundW(L"SoundEff_CrashWithBody.mp3", SOUND_PLAYER, g_fSound);
			m_iWitchColli = GetTickCount();
			m_bWitchColli = true;
		}
		else
		{
			if (m_iWitchColli + 1000 < GetTickCount())
			{
				m_bWitchColli = false;
			}
		}
		m_fRunaway -= 2.0f;
	}
}

void CPlayer::CollisionDevil()
{
	if (m_eCurState != DEVIL)
		--m_iDevilJellyCount;
	if (m_iDevilJellyCount == 0 && m_eCurState != DEVIL)
	{
		m_eCurState = DEVIL;
		m_iDevilJellyCount = 12;
		m_fSpeed += 5;
	}
}

void CPlayer::Get_Itemtype(OBJID _Item)
{
	switch (_Item)
	{
	case OBJ_ITEM_HEAL:
		m_fHp += 100;
		break;
	case OBJ_ITEM_BOOST:
		m_iPlayertype = BOOST;
		m_fSpeed += 10;
		break;
	case OBJ_ITEM_GIGA:
		m_iPlayertype = GIGA;
		m_tInfo.fCY *= 2;
		m_tInfo.fCX *= 2;
		break;
	case OBJ_ITEM_GIGA2:
		m_iPlayertype = GIGA;
		m_tInfo.fCY *= 2;
		m_tInfo.fCX *= 2;
		break;
	case OBJ_ITEM_MAGNET:
		static_cast<CPet*>(OBJMGR->Get_Obj_List(OBJ_PET).front())->Magnet();
		break;
	case OBJ_ITEM_SMALL:
		m_fHp += 30;
		break;
	default:
		break;
	}
}

int CPlayer::Set_State()
{
	if (m_eCurState == JUMP || m_eCurState == DOUBLEJUMP)
		return JUMP;
	else if (m_bSlide == true)
	{
		return SLIDE;
	}
}

void CPlayer::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (CScrollMgr::Get_Instance()->Get_ScrollX() < -37900 && m_bEnd == false)
	{
		m_fSpeed = 0;
		m_EndCount = GetTickCount();
		m_bEnd = true;
	}
	else if ((m_EndCount + 5000 < GetTickCount()) && m_bEnd == true && m_bCut == false)	//마녀모드
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_SCORE);
		m_bCut = true;
		m_eCurState = WITCH;
		m_tInfo.fX = 38700;
		m_tInfo.fY = 300;
		m_tInfo.fCX = 227;
		m_tInfo.fCY = 169;
		m_fSpeed = -0;
		m_iCookieType = WITCHC;
		m_iPlayertype = WITCH;

		m_iRunCount = GetTickCount();
	}


	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Player");
	HDC		hMemDC5 = CBmpMgr::Get_Instance()->Find_Image(L"DevilGiga");
	HDC		hMemDC2 = CBmpMgr::Get_Instance()->Find_Image(L"PlayerCollision");

	if (m_iCookieType == DEVILCOOKIE)
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Player");
		hMemDC5 = CBmpMgr::Get_Instance()->Find_Image(L"DevilGiga");
		hMemDC2 = CBmpMgr::Get_Instance()->Find_Image(L"PlayerCollision");
	}
	else if (m_iCookieType == COFFEECOOKIE)
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"PlayerC");
		hMemDC5 = CBmpMgr::Get_Instance()->Find_Image(L"DevilGigaC");
		hMemDC2 = CBmpMgr::Get_Instance()->Find_Image(L"PlayerCollisionC");
	}
	else if (m_iCookieType == ZOMBIECOOKIE)
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"PlayerZ");
		hMemDC5 = CBmpMgr::Get_Instance()->Find_Image(L"DevilGigaZ");
		hMemDC2 = CBmpMgr::Get_Instance()->Find_Image(L"PlayerCollisionZ");
	}


	HDC		hMemDC3 = CBmpMgr::Get_Instance()->Find_Image(L"Font_Devil");
	HDC		hMemDC4 = CBmpMgr::Get_Instance()->Find_Image(L"Devil");
	HDC		hMemDC6 = CBmpMgr::Get_Instance()->Find_Image(L"DevilGigah");
	HDC		hMemDC7 = CBmpMgr::Get_Instance()->Find_Image(L"zombieRevive");




	// 악마쿠키 악마젤리 갯수
	if (m_iDevilJellyCount <= 9 && m_iCookieType == DEVILCOOKIE)
	{
		GdiTransparentBlt(hDC,
			int(m_tFontRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tFontRect.top + iScrollY),
			int(m_tFontInfo.fCX),
			int(m_tFontInfo.fCY),
			hMemDC3,
			0 + m_iDevilJellyCount * 32,			// 비트맵 출력 시작 좌표, X,Y
			0,
			(int)m_tFontInfo.fCX,		// 복사할 비트맵의 가로, 세로 길이
			(int)m_tFontInfo.fCY,
			RGB(255, 0, 200));
	}
	else if (m_eCurState != WITCH)
	{
		GdiTransparentBlt(hDC,
			int(m_tFontRect.left + iScrollX - 32),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tFontRect.top + iScrollY),
			int(m_tFontInfo.fCX),
			int(m_tFontInfo.fCY),
			hMemDC3,
			(0 + m_iDevilJellyCount / 10 * 32),			// 비트맵 출력 시작 좌표, X,Y
			0,
			(int)m_tFontInfo.fCX,		// 복사할 비트맵의 가로, 세로 길이
			(int)m_tFontInfo.fCY,
			RGB(255, 0, 200));

		GdiTransparentBlt(hDC,
			int(m_tFontRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tFontRect.top + iScrollY),
			int(m_tFontInfo.fCX),
			int(m_tFontInfo.fCY),
			hMemDC3,
			(0 + (m_iDevilJellyCount % 10) * 32),			// 비트맵 출력 시작 좌표, X,Y
			0,
			(int)m_tFontInfo.fCX,		// 복사할 비트맵의 가로, 세로 길이
			(int)m_tFontInfo.fCY,
			RGB(255, 0, 200));
	}



	if (m_eCurState == JUMP && m_iPlayertype != GIGA)
	{
		{
			GdiTransparentBlt(hDC,
				int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tRect.top + iScrollY),
				int(m_tInfo.fCX + 40),
				int(m_tInfo.fCY),
				hMemDC,
				9 * 366 + 100 + m_iZombieX,			// 비트맵 출력 시작 좌표, X,Y
				550 - 366 + m_iZombieY,
				(int)m_tInfo.fCX + 40,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tInfo.fCY,
				RGB(255, 0, 200));
			return;
		}
	}
	else if (m_iPlayertype == GIGA && m_eCurState == JUMP)
	{
		GdiTransparentBlt(hDC,
			int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top + iScrollY),
			int(m_tInfo.fCX),
			int(m_tInfo.fCY),
			hMemDC5,
			220,			// 비트맵 출력 시작 좌표, X,Y
			1800,
			(int)m_tInfo.fCX,		// 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fCY,
			RGB(255, 0, 200));
	}
	else if (m_iPlayertype != GIGA && m_eCurState == DOUBLEJUMP)
	{
		GdiTransparentBlt(hDC,
			int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top + iScrollY),
			int(m_tInfo.fCX + 20),
			int(m_tInfo.fCY),
			hMemDC,
			m_iJumpFrame * 366 + 100,			// 비트맵 출력 시작 좌표, X,Y
			180,
			(int)m_tInfo.fCX + 20,		// 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fCY,
			RGB(255, 0, 200));
	}
	else if (m_iPlayertype == GIGA && m_eCurState == DOUBLEJUMP)
	{
		GdiTransparentBlt(hDC,
			int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top + iScrollY),
			int(m_tInfo.fCX),
			int(m_tInfo.fCY),
			hMemDC5,
			m_iJumpFrame * 720 + 220,			// 비트맵 출력 시작 좌표, X,Y
			360,
			(int)m_tInfo.fCX,		// 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fCY,
			RGB(255, 0, 200));
	}

	else if (m_eCurState == DEVIL && m_iPlayertype != GIGA)
	{
		GdiTransparentBlt(hDC,
			int(m_tRect.left + iScrollX),
			int(m_tRect.top),
			int(360 + 70),
			int(m_tInfo.fCY + 60),
			hMemDC4,
			m_iDevilFrame * 360,
			100,
			(int)360 + 70,
			(int)m_tInfo.fCY + 60,
			RGB(255, 0, 200));
	}
	else if (m_eCurState == DEVIL && m_iPlayertype == GIGA)
	{
		GdiTransparentBlt(hDC,
			int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top),
			int(360 + 140),
			int(m_tInfo.fCY + 80),
			hMemDC6,
			m_iDevilFrame * 720,			// 비트맵 출력 시작 좌표, X,Y
			240,
			(int)720 + 140,		// 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fCY + 80,
			RGB(255, 0, 200));
	}
	else if (m_bSlide)
	{
		GdiTransparentBlt(hDC,
			int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top + 10),
			int(m_tInfo.fCX),
			int(m_tInfo.fCY),
			hMemDC,
			10 * 366 + 70,			// 비트맵 출력 시작 좌표, X,Y
			550 - 366 + 70,
			(int)m_tInfo.fCX,		// 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fCY,
			RGB(255, 0, 200));
	}
	else if (m_iPlayertype == BOOST)
	{
		GdiTransparentBlt(hDC,
			int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top),
			int(m_tInfo.fCX + 100),
			int(m_tInfo.fCY),
			hMemDC,
			m_tFrame.iFrameStart * 366 + 1520,			// 비트맵 출력 시작 좌표, X,Y
			550,
			(int)m_tInfo.fCX + 100,		// 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fCY,
			RGB(255, 0, 200));
	}
	else if (m_iPlayertype == DEAD)
	{
		GdiTransparentBlt(hDC,
			int(m_tRect.left + iScrollX),
			int(m_tRect.top),
			int(m_tInfo.fCX + 50),
			int(m_tInfo.fCY),
			hMemDC,
			m_tFrame2.iFrameStart * 366 + 2304,
			1660,
			(int)m_tInfo.fCX + 50,
			(int)m_tInfo.fCY,
			RGB(255, 0, 200));
	}


	else
	{
		if (m_bCollision && 15 > m_iColliFrame)
		{
			GdiTransparentBlt(hDC,
				int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tRect.top),
				int(m_tInfo.fCX),
				int(m_tInfo.fCY),
				hMemDC2,
				m_iColliFrame * 360 + 80,			// 비트맵 출력 시작 좌표, X,Y
				150,
				(int)m_tInfo.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tInfo.fCY,
				RGB(255, 0, 200));
			if (m_iColliTime + 30 < GetTickCount())
				++m_iColliFrame;
		}
		else if (m_iPlayertype == GIGA)
		{
			GdiTransparentBlt(hDC,
				int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tRect.top + iScrollY),
				int(m_tInfo.fCX),
				int(m_tInfo.fCY),
				hMemDC5,
				m_tFrame.iFrameStart * 720 + 220,			// 비트맵 출력 시작 좌표, X,Y
				1100,
				(int)m_tInfo.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tInfo.fCY,
				RGB(255, 0, 200));
		}
		else  if (m_eCurState != WITCH)
		{
			GdiTransparentBlt(hDC,
				int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tRect.top + iScrollY),
				int(m_tInfo.fCX),
				int(m_tInfo.fCY),
				hMemDC,
				m_tFrame.iFrameStart * 366 + 120 + m_iZombieX,			// 비트맵 출력 시작 좌표, X,Y
				550 + m_iZombieY,
				(int)m_tInfo.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tInfo.fCY,
				RGB(255, 0, 200));
		}
	}

	if (m_eCurState == WITCH)
	{

		if (m_tRect.left + 30 >= m_iDevilRun + m_fSpeed + m_fRunaway)
		{

			HDC		hMemDC9 = CBmpMgr::Get_Instance()->Find_Image(L"DevilRun");
			GdiTransparentBlt(hDC,
				int(m_iDevilRun + iScrollX + m_fSpeed + m_fRunaway),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_fDevilRun),
				int(280),
				int(210),
				hMemDC9,
				m_iDevilFrame2 * 290 + 5,			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)290,		// 복사할 비트맵의 가로, 세로 길이
				(int)280,
				RGB(255, 0, 200));
		}


		if (GetAsyncKeyState('W'))
		{
			m_bPa = true;
			if (!m_bPa2)
			{
				m_iPaCount2 = GetTickCount();
				m_bPa2 = true;
			}
			else
			{
				if (m_iPaCount2 + 1000 < GetTickCount())
				{
					m_bPa2 = false;
				}
			}


			HDC		hMemDC13 = CBmpMgr::Get_Instance()->Find_Image(L"adogen");
			GdiTransparentBlt(hDC,
				int(m_tRect.left + iScrollX),
				int(m_tRect.top + iScrollY),
				int(209),
				int(165),
				hMemDC13,
				1045 - 209 * m_iPaFrame,
				0,
				(int)209,
				(int)165,
				RGB(255, 0, 200));

		}

		else if (GetAsyncKeyState('E'))
		{
			HDC		hMemDC16 = CBmpMgr::Get_Instance()->Find_Image(L"up");
			m_bUp = true;

			GdiTransparentBlt(hDC,
				int(m_iDevilRun + iScrollX + m_fSpeed + m_fRunaway + 30),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_iUp),
				int(272),
				int(392),
				hMemDC16,
				0,			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)272,		// 복사할 비트맵의 가로, 세로 길이
				(int)392,
				RGB(255, 0, 200));
		}

		else if (GetAsyncKeyState('R'))
		{
			HDC		hMemDC19 = CBmpMgr::Get_Instance()->Find_Image(L"curby");
			if (m_tRect.left + 30 >= m_iDevilRun + m_fSpeed + m_fRunaway)
			{
				GdiTransparentBlt(hDC,
					int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tRect.top + iScrollY),
					int(250),
					int(262),
					hMemDC19,
					0,			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)219,		// 복사할 비트맵의 가로, 세로 길이
					(int)262,
					RGB(255, 0, 200));

				//if (m_bCutScene2)
				//{
				//	GdiTransparentBlt(hDC,
				//		int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
				//		int(m_tRect.top + iScrollY + 20),
				//		int(250),
				//		int(262),
				//		hMemDC19,
				//		0,			// 비트맵 출력 시작 좌표, X,Y
				//		0,
				//		(int)219,		// 복사할 비트맵의 가로, 세로 길이
				//		(int)262,
				//		RGB(255, 0, 200));
				//}

			}
			else
			{
				GdiTransparentBlt(hDC,
					int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tRect.top + iScrollY),
					int(250),
					int(262),
					hMemDC19,
					250,			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)219,		// 복사할 비트맵의 가로, 세로 길이
					(int)262,
					RGB(255, 0, 200));
			}
		}


		else
		{
			HDC		hMemDC8 = CBmpMgr::Get_Instance()->Find_Image(L"PWitch");
			GdiTransparentBlt(hDC,
				int(m_tRect.left + iScrollX),
				int(m_tRect.top + iScrollY),
				int(m_tInfo.fCX),
				int(m_tInfo.fCY),
				hMemDC8,
				0,
				0,
				(int)m_tInfo.fCX,
				(int)m_tInfo.fCY,
				RGB(255, 0, 200));


			HDC		hMemDC10 = CBmpMgr::Get_Instance()->Find_Image(L"Shotgun2");
			GdiTransparentBlt(hDC,
				int(m_tRect.left + iScrollX - 50),
				int(m_tRect.top + iScrollY + 110),
				int(136),
				int(43),
				hMemDC10,
				0,
				0,
				(int)136,
				(int)43,
				RGB(255, 0, 200));
		}

	}

}

void CPlayer::Release(void)
{
	//CBmpMgr::Destroy_Instance();
}


void CPlayer::Key_Input(void)
{
	if (GetAsyncKeyState(VK_SPACE))
	{
		if (m_eCurState == WALK)
		{
			m_eCurState = JUMP;
			m_iJumpCount = GetTickCount();
			CSoundMgr::Get_Instance()->PlaySoundW(L"Char_Jump_ch03.wav", SOUND_PLAYER, g_fSound);
		}
		else if (m_eCurState == JUMP && m_iJumpCount + 200 < GetTickCount())
		{
			m_eCurState = DOUBLEJUMP;
			CSoundMgr::Get_Instance()->PlaySoundW(L"Char_Jump_ch03.wav", SOUND_PLAYER, g_fSound);
		}
		else if (m_eCurState == DEVIL)
		{
			m_tRect.top += 5;
		}
		else if (m_eCurState == WITCH)
		{
			m_tRect.top += 5;
		}
	}

	if (GetAsyncKeyState(VK_DOWN) && m_eCurState == WALK && m_iPlayertype != GIGA && m_eCurState != WITCH)
	{
		m_tInfo.fCX = 180;
		m_tInfo.fCY = 100;
		if (m_iSlideCount == 0)
		{
			CSoundMgr::Get_Instance()->PlaySoundW(L"Char_Slide_ch03.wav", SOUND_PLAYER, g_fSound);
			m_iSlideCount = 1;
		}
		m_bSlide = true;
		return;
	}
	else if (m_iPlayertype != GIGA && m_eCurState != WITCH)
	{
		m_tInfo.fCX = 150.f;
		m_tInfo.fCY = 170;
		m_iSlideCount = 0;
		m_bSlide = false;
	}
}

void CPlayer::Jumping(void)
{
	float		fY = 0.f;

	bool		bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY);

	if (m_eCurState == JUMP)
	{
		m_tInfo.fY -= m_fJumpPower * m_fJumpTime - 7.7f * m_fJumpTime * m_fJumpTime * 0.5f;
		m_fJumpTime += 0.1f;

		if (bLineCol && (fY < m_tRect.bottom))
		{
			m_eCurState = WALK;
			m_fJumpTime = 0.f;
			m_tRect.bottom = LONG(fY);

			if (m_iPlayertype == GIGA)
				m_bScrollY = true;
		}
	}
	else if (m_eCurState == DOUBLEJUMP)
	{
		m_tInfo.fY -= m_fJumpPower * m_fJumpTime - 7.7f * m_fJumpTime * m_fJumpTime * 0.5f + 5;
		m_fJumpTime += 0.08f;

		if (m_eCurState == DOUBLEJUMP && (fY < m_tRect.bottom) && bLineCol)
		{
			m_eCurState = WALK;
			m_fJumpTime = 0.f;
			m_tRect.bottom = LONG(fY);
			if (m_iPlayertype == GIGA)
				m_bScrollY = true;
		}
		return;
	}

	else if (m_eCurState == DEVIL)
	{
		if (GetAsyncKeyState(VK_SPACE))
		{
			m_tInfo.fY -= 5;
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			m_tInfo.fY += 5;
		}
	}

	else if (m_eCurState == WITCH)
	{
		if (GetAsyncKeyState(VK_UP))
		{
			m_tInfo.fY -= 5;
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			m_tInfo.fY += 5;
		}
		else if (GetAsyncKeyState(VK_LEFT))
		{
			m_tInfo.fX -= 5;
		}
		else if (GetAsyncKeyState(VK_RIGHT))
		{
			m_tInfo.fX += 5;
		}
	}


	else if (bLineCol)
	{
		m_tInfo.fY = fY - m_tInfo.fCY / 2;
	}

	else if (!bLineCol)
	{
		m_tInfo.fY += 20;
		if (m_tRect.bottom <= 0)
			m_fSpeed = 0;
	}

}



void CPlayer::OffSet(void)
{
	if (CScrollMgr::Get_Instance()->Get_ScrollX() > -37900)
	{
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);
	}
	else if (m_eCurState == WITCH)
	{
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);
	}
}