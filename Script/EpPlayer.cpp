#include "stdafx.h"
#include "EpShootingGame.h"
#include "EpPlayer.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

EpPlayer::EpPlayer()
{
	// 비행기 이미지 크기
	m_mpWidth = 32;
	m_mpHeight = 32;

	m_HP = 1;
	m_check = false;
}

EpPlayer::~EpPlayer()
{

}

void EpPlayer::GiveAtt(long x, long y, CDC *backDC)
{
	m_point.x = x;
	m_point.y = y;
	m_backDC = backDC;
	m_bmpM.LoadBitmap(IDB_M_G);
	m_bmpCrashed.LoadBitmap(IDB_CRASHED);
	m_bmpCrashed1.LoadBitmap(IDB_CRASHED1);
	m_memDC.CreateCompatibleDC(backDC);
	m_memDC.SelectObject(&m_bmpM);

	m_MyVelocityX = m_MyVelocityY = 0;
	m_bombCnt = 3;
	m_HP = 1;
}

void EpPlayer::CheckAndDraw(POINT mp)
{

	m_point.x +=m_MyVelocityX;
	m_point.y +=m_MyVelocityY;
	m_MyVelocityX = (mp.x - m_point.x) / 3 - (m_mpWidth / 6);
	m_MyVelocityY = (mp.y - m_point.y) / 3 - (m_mpHeight / 6);
		
	Draw();
}

void EpPlayer::Draw()
{
	m_backDC->BitBlt(m_point.x, m_point.y,m_mpWidth, m_mpHeight,&m_memDC,0,0, SRCCOPY);	
}

void EpPlayer::ChgToCrashedStat()
{
	static short sFlipFlg;
	
	if (m_check) {
		sFlipFlg++;
	}

	if (sFlipFlg > 19)
		sFlipFlg = 0;
	
	if (sFlipFlg < 9)
		m_memDC.SelectObject(&m_bmpCrashed);
	else
		m_memDC.SelectObject(&m_bmpCrashed1);

}

void EpPlayer::Init()
{
	m_memDC.SelectObject(&m_bmpM);
}