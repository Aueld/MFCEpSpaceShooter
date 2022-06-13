#include "stdafx.h"
#include "EpShootingGame.h"
#include "EpUnit.h"
#include "EpEnemy.h"
#include "EpBoss.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

EpUnit::EpUnit()
{
	m_bmpECrashed.LoadBitmap(IDB_ECRASHED);
	m_bmpECrashed1.LoadBitmap(IDB_ECRASHED1);
	m_crashedTime = 0;
	m_liveCheck = false;
}

EpUnit::~EpUnit()
{

}

void EpUnit::Draw()
{
	m_backDC->BitBlt(m_point.x, m_point.y, m_objWidth, m_objHeight, &m_memDC, 0, 0, SRCCOPY);
}

short EpUnit::CheckAndDraw(POINT mp)
{
	switch(m_specify)
	{
	case 0:
		return ((EpEnemyPlane *)this)->CheckAndDraw(mp);
	case 1:
		return ((EpBoss *)this)->CheckAndDraw(mp);
	case 2:
		Draw();
		switch(m_crashedTime)
		{
		case 0:
			m_memDC.SelectObject(&m_bmpECrashed);
			break;
		case 7:
			m_memDC.SelectObject(&m_bmpECrashed1);
			break;
		case 15:
			return 1;
		}
		m_crashedTime++;
		return 0;
	case 3:
		Draw();
		switch(m_crashedTime)
		{
		case 0:
			m_memDC.SelectObject(&m_bmpECrashed);
			break;
		case 12:
			m_memDC.SelectObject(&m_bmpECrashed1);
			break;
		case 25:
			return 1;
		}
		m_crashedTime++;
		return 0;
	}
}

short EpUnit::Attacked()
{
	switch(m_specify)
	{
	case 0:
		return 0;
	case 1:
		if(((EpBoss*)this)->CheckHP())
			m_liveCheck = true;

		return ((EpBoss *)this)->Hit();
	case 2:
		return 1;
	}
}