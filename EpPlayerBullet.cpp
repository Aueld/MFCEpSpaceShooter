#include "stdafx.h"
#include "ShootingGame.h"
#include "EpPlayerBullet.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

EpPlayerBullet::EpPlayerBullet()
{

}

EpPlayerBullet::~EpPlayerBullet()
{

}

void EpPlayerBullet::GiveAtt(POINT p, CDC *backDC, CArray<EpEnemyObj*, EpEnemyObj*> *arE)
{
	m_point = p;
	m_backDC = backDC;
	m_bmpB.LoadBitmap(IDB_B_G);
	m_memDC.CreateCompatibleDC(backDC);
	m_memDC.SelectObject(&m_bmpB);
	m_arE = arE;
}

short EpPlayerBullet::CheckAndDraw()
{
	Move();
	Draw();
	for(int i = 0; i < m_arE->GetSize(); i++)
	{
		if((m_arE->GetAt(i)->m_point.x >= m_point.x && m_arE->GetAt(i)->m_point.x - m_point.x < 5 
				|| m_arE->GetAt(i)->m_point.x < m_point.x && m_point.x - m_arE->GetAt(i)->m_point.x < m_arE->GetAt(i)->m_objWidth)
			&& (m_arE->GetAt(i)->m_point.y >= m_point.y && m_arE->GetAt(i)->m_point.y - m_point.y < 20 
				|| m_arE->GetAt(i)->m_point.y < m_point.y && m_point.y - m_arE->GetAt(i)->m_point.y < m_arE->GetAt(i)->m_objHeight))
		{

			if(m_arE->GetAt(i)->Attacked() == 0)
			{
				//m_arE->RemoveAt(i);
				m_arE->GetAt(i)->m_specify += 2;
			}
			return 1;
		}

	}

	if(m_point.y < 0) return 1;
	return 0;
}

void EpPlayerBullet::Draw()
{
	m_backDC->BitBlt(m_point.x, m_point.y,5,20,&m_memDC,0,0, SRCCOPY);	
}

void EpPlayerBullet::Move()
{
	m_point.y -=10;
}