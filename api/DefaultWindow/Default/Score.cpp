#include "stdafx.h"
#include "Score.h"
#include "BmpMgr.h"
#include "ScoreMgr.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "SoundMgr.h"


CScore::CScore()
{
}


CScore::~CScore()
{
	Release();
}

void CScore::Initialize(void)
{
	m_tScore.fX = 590;
	m_tScore.fY = 320;
	m_tScore.fCX = 32;
	m_tScore.fCY = 38;

	m_tCoin.fX = 400;
	m_tCoin.fY = 210;
	m_tCoin.fCX = 64;
	m_tCoin.fCY = 64;

	m_bHighScore = false;


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Page_Result2.bmp", L"Page_Result2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/FONT_NUMBER2.bmp", L"FONT_NUMBER2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/FONT_NUMBER2_test.bmp", L"FONT_NUMBER2_test");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/newRecord.bmp", L"newRecord");

	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlaySoundW(L"result_2.wav", SOUND_PLAYER, g_fSound);
}

void CScore::Update(void)
{
	m_iCoin = CScoreMgr::Get_Instance()->Get_Coin();
	m_iScore = CScoreMgr::Get_Instance()->Get_Score();
	m_iHighScore = CScoreMgr::Get_Instance()->Get_HighScore();

	if (m_iScore == m_iHighScore)
		m_bHighScore = true;

	m_tScoreRect.left = LONG(m_tScore.fX - (m_tScore.fCX * 0.5f));
	m_tScoreRect.top = LONG(m_tScore.fY - (m_tScore.fCY * 0.5f));
	m_tScoreRect.right = LONG(m_tScore.fX + (m_tScore.fCX * 0.5f));
	m_tScoreRect.bottom = LONG(m_tScore.fY + (m_tScore.fCY * 0.5f));

	m_tCoinRect.left = LONG(m_tCoin.fX - (m_tCoin.fCX * 0.5f));
	m_tCoinRect.top = LONG(m_tCoin.fY - (m_tCoin.fCY * 0.5f));
	m_tCoinRect.right = LONG(m_tCoin.fX + (m_tCoin.fCX * 0.5f));
	m_tCoinRect.bottom = LONG(m_tCoin.fY + (m_tCoin.fCY * 0.5f));
}

void CScore::Late_Update(void)
{

	if (GetAsyncKeyState(VK_LBUTTON))
		CSceneMgr::Get_Instance()->Scene_Change(SC_Robby);
}

void CScore::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Page_Result2");
	HDC		hMemDC2 = CBmpMgr::Get_Instance()->Find_Image(L"FONT_NUMBER2");
	HDC		hMemDC3 = CBmpMgr::Get_Instance()->Find_Image(L"FONT_NUMBER2_test");
	HDC		hMemDC4 = CBmpMgr::Get_Instance()->Find_Image(L"newRecord");

	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	if (m_bHighScore)
	{
		GdiTransparentBlt(hDC,
			int(70),
			int(70),
			int(174),
			int(90),
			hMemDC4,
			0,
			0,
			174,
			90,
			RGB(255, 0, 200));
	}

	if (m_iCoin < 10)
	{
		GdiTransparentBlt(hDC,
			int(m_tScoreRect.left + 30),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tScoreRect.top),
			int(m_tScore.fCX),
			int(m_tScore.fCY),
			hMemDC2,
			int(m_tScore.fCX * (m_iCoin % 10)),			// 비트맵 출력 시작 좌표, X,Y
			0,
			(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
			(int)m_tScore.fCY,
			RGB(255, 0, 200));
	}

	else if (m_iCoin >= 10 && m_iCoin < 100)
	{
		{
			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC2,
				int(m_tScore.fCX * (m_iCoin / 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 30),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC2,
				int(m_tScore.fCX * (m_iCoin % 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));
		}
	}
	else if (m_iCoin >= 100 && m_iCoin < 1000)
	{
		{
			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC2,
				int(m_tScore.fCX * (m_iCoin / 100)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 30),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC2,
				int(m_tScore.fCX * (m_iCoin % 100 / 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 60),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC2,
				int(m_tScore.fCX * (m_iCoin % 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));
		}
	}
	else if (m_iCoin >= 1000 && m_iCoin < 10000)
	{
		{
			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC2,
				int(m_tScore.fCX * (m_iCoin % 10000 / 1000)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 30),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC2,
				int(m_tScore.fCX * (m_iCoin % 1000 / 100)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 60),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC2,
				int(m_tScore.fCX * (m_iCoin % 100 / 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 90),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC2,
				int(m_tScore.fCX * (m_iCoin % 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));
		}
	}

	else if (m_iCoin >= 10000)
	{
		{
			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC2,
				int(m_tScore.fCX * (m_iCoin / 10000)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 30),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC2,
				int(m_tScore.fCX * (m_iCoin % 10000 / 1000)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 60),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC2,
				int(m_tScore.fCX * (m_iCoin % 1000 / 100)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 90),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC2,
				int(m_tScore.fCX * (m_iCoin % 100 / 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 120),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC2,
				int(m_tScore.fCX * (m_iCoin % 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));
		}
	}

	// 하이스코어
	 if (m_iHighScore >= 0 && m_iHighScore < 100)
	{
		{
			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top + 70),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC2,
				int(m_tScore.fCX * (m_iHighScore / 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 30),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top + 70),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC2,
				int(m_tScore.fCX * (m_iHighScore % 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));
		}
	}
	else if (m_iHighScore >= 100 && m_iHighScore < 1000)
	{
		{
			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top + 70),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC2,
				int(m_tScore.fCX * (m_iHighScore / 100)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 30),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top + 70),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC2,
				int(m_tScore.fCX * (m_iHighScore % 100 / 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 60),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top + 70),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC2,
				int(m_tScore.fCX * (m_iHighScore % 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));
		}
	}
	else if (m_iHighScore >= 1000 && m_iHighScore < 10000)
	{
		{
			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top + 70),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC2,
				int(m_tScore.fCX * (m_iHighScore % 10000 / 1000)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 30),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top + 70),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC2,
				int(m_tScore.fCX * (m_iHighScore % 1000 / 100)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 60),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top + 70),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC2,
				int(m_tScore.fCX * (m_iHighScore % 100 / 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 90),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top + 70),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC2,
				int(m_tScore.fCX * (m_iHighScore % 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));
		}
	}

	else if (m_iHighScore >= 10000 && m_iHighScore < 100000)
	{
		{
			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top + 70),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC2,
				int(m_tScore.fCX * (m_iHighScore / 10000)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 30),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top + 70),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC2,
				int(m_tScore.fCX * (m_iHighScore % 10000 / 1000)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 60),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top + 70),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC2,
				int(m_tScore.fCX * (m_iHighScore % 1000 / 100)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 90),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top + 70),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC2,
				int(m_tScore.fCX * (m_iHighScore % 100 / 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 120),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top + 70),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC2,
				int(m_tScore.fCX * (m_iHighScore % 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));
		}
	}

	else if (m_iHighScore >= 100000 && m_iHighScore < 1000000)
	{
		{
			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top + 70),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC2,
				int(m_tScore.fCX * (m_iHighScore / 100000)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));


			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 30),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top + 70),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC2,
				int(m_tScore.fCX * (m_iHighScore % 100000 / 10000)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 60),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top + 70),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC2,
				int(m_tScore.fCX * (m_iHighScore % 10000 / 1000)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 90),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top + 70),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC2,
				int(m_tScore.fCX * (m_iHighScore % 1000 / 100)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 120),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top + 70),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC2,
				int(m_tScore.fCX * (m_iHighScore % 100 / 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));


			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 150),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top + 70),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC2,
				int(m_tScore.fCX * (m_iHighScore % 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));
		}
	}





	// 현재 점수
	if (m_iScore <= 9)
	{
		GdiTransparentBlt(hDC,
			int(m_tCoinRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tCoinRect.top),
			int(m_tCoin.fCX),
			int(m_tCoin.fCY),
			hMemDC3,
			int(m_tCoin.fCX * m_iScore),			// 비트맵 출력 시작 좌표, X,Y
			0,
			(int)m_tCoin.fCX,		// 복사할 비트맵의 가로, 세로 길이
			(int)m_tCoin.fCY,
			RGB(255, 0, 200));
	}
	else if (m_iScore >= 10 && m_iScore < 100)
	{
		{
			GdiTransparentBlt(hDC,
				int(m_tCoinRect.left - 30),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tCoinRect.top),
				int(m_tCoin.fCX),
				int(m_tCoin.fCY),
				hMemDC3,
				int(m_tCoin.fCX * (m_iScore / 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tCoin.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tCoin.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tCoinRect.left + 30),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tCoinRect.top),
				int(m_tCoin.fCX),
				int(m_tCoin.fCY),
				hMemDC3,
				int(m_tCoin.fCX * (m_iCoin % 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tCoin.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tCoin.fCY,
				RGB(255, 0, 200));
		}
	}
	else if (m_iScore >= 100 && m_iScore < 1000)
	{
		{
			GdiTransparentBlt(hDC,
				int(m_tCoinRect.left - 60),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tCoinRect.top),
				int(m_tCoin.fCX),
				int(m_tCoin.fCY),
				hMemDC3,
				int(m_tCoin.fCX * (m_iScore / 100)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tCoin.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tCoin.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tCoinRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tCoinRect.top),
				int(m_tCoin.fCX),
				int(m_tCoin.fCY),
				hMemDC3,
				int(m_tCoin.fCX * (m_iScore % 100 / 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tCoin.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tCoin.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tCoinRect.left + 60),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tCoinRect.top),
				int(m_tCoin.fCX),
				int(m_tCoin.fCY),
				hMemDC3,
				int(m_tCoin.fCX * (m_iScore % 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tCoin.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tCoin.fCY,
				RGB(255, 0, 200));
		}
	}
	else if (m_iScore >= 1000 && m_iScore < 10000)
	{
		{
			GdiTransparentBlt(hDC,
				int(m_tCoinRect.left - 90),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tCoinRect.top),
				int(m_tCoin.fCX),
				int(m_tCoin.fCY),
				hMemDC3,
				int(m_tCoin.fCX * (m_iScore % 10000 / 1000)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tCoin.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tCoin.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tCoinRect.left - 30),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tCoinRect.top),
				int(m_tCoin.fCX),
				int(m_tCoin.fCY),
				hMemDC3,
				int(m_tCoin.fCX * (m_iScore % 1000 / 100)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tCoin.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tCoin.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tCoinRect.left + 30),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tCoinRect.top),
				int(m_tCoin.fCX),
				int(m_tCoin.fCY),
				hMemDC3,
				int(m_tCoin.fCX * (m_iScore % 100 / 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tCoin.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tCoin.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tCoinRect.left + 90),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tCoinRect.top),
				int(m_tCoin.fCX),
				int(m_tCoin.fCY),
				hMemDC3,
				int(m_tCoin.fCX * (m_iScore % 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tCoin.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tCoin.fCY,
				RGB(255, 0, 200));
		}
	}

	else if (m_iScore >= 10000 && m_iScore < 100000)
	{
		{
			GdiTransparentBlt(hDC,
				int(m_tCoinRect.left - 120),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tCoinRect.top),
				int(m_tCoin.fCX),
				int(m_tCoin.fCY),
				hMemDC3,
				int(m_tCoin.fCX * (m_iScore / 10000)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tCoin.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tCoin.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tCoinRect.left - 60),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tCoinRect.top),
				int(m_tCoin.fCX),
				int(m_tCoin.fCY),
				hMemDC3,
				int(m_tCoin.fCX * (m_iScore % 10000 / 1000)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tCoin.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tCoin.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tCoinRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tCoinRect.top),
				int(m_tCoin.fCX),
				int(m_tCoin.fCY),
				hMemDC3,
				int(m_tCoin.fCX * (m_iScore % 1000 / 100)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tCoin.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tCoin.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tCoinRect.left + 60),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tCoinRect.top),
				int(m_tCoin.fCX),
				int(m_tCoin.fCY),
				hMemDC3,
				int(m_tCoin.fCX * (m_iScore % 100 / 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tCoin.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tCoin.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tCoinRect.left + 120),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tCoinRect.top),
				int(m_tCoin.fCX),
				int(m_tCoin.fCY),
				hMemDC3,
				int(m_tCoin.fCX * (m_iScore % 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tCoin.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tCoin.fCY,
				RGB(255, 0, 200));
		}
	}


	else if (m_iScore >= 100000 && m_iScore < 1000000)
	{
		{
			GdiTransparentBlt(hDC,
				int(m_tCoinRect.left - 150),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tCoinRect.top),
				int(m_tCoin.fCX),
				int(m_tCoin.fCY),
				hMemDC3,
				int(m_tCoin.fCX * (m_iScore / 100000)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tCoin.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tCoin.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tCoinRect.left - 90),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tCoinRect.top),
				int(m_tCoin.fCX),
				int(m_tCoin.fCY),
				hMemDC3,
				int(m_tCoin.fCX * (m_iScore % 100000 / 10000)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tCoin.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tCoin.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tCoinRect.left - 30),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tCoinRect.top),
				int(m_tCoin.fCX),
				int(m_tCoin.fCY),
				hMemDC3,
				int(m_tCoin.fCX * (m_iScore % 10000 / 1000)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tCoin.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tCoin.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tCoinRect.left + 30),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tCoinRect.top),
				int(m_tCoin.fCX),
				int(m_tCoin.fCY),
				hMemDC3,
				int(m_tCoin.fCX * (m_iScore % 1000 / 100)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tCoin.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tCoin.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tCoinRect.left + 90),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tCoinRect.top),
				int(m_tCoin.fCX),
				int(m_tCoin.fCY),
				hMemDC3,
				int(m_tCoin.fCX * (m_iScore % 100 / 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tCoin.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tCoin.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tCoinRect.left + 150),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tCoinRect.top),
				int(m_tCoin.fCX),
				int(m_tCoin.fCY),
				hMemDC3,
				int(m_tCoin.fCX * (m_iScore % 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tCoin.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tCoin.fCY,
				RGB(255, 0, 200));
		}
	}

}

void CScore::Release(void)
{
	OBJMGR->Release();
	CBmpMgr::Get_Instance()->Release();
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Oven.bmp", L"Back");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map2.bmp", L"Ground");
}
