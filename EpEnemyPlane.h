#if !defined(AFX_ENEMYPLANE_H__EFDA49CE_F387_4753_B4D3_F150E495252A__INCLUDED_)
#define AFX_ENEMYPLANE_H__EFDA49CE_F387_4753_B4D3_F150E495252A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EpEnemyObj.h"

class EpEnemyPlane : public EpEnemyObj  
{
public:
	EpEnemyPlane();
	virtual ~EpEnemyPlane();

	void	GiveAtt(int iStyle, long x, long y, CDC* backDC, CArray<EpEnemyBullet*, EpEnemyBullet*> *arEB);
	short	CheckAndDraw(POINT mp);

private:
	short	m_iMoveStyle;
	int		m_iShootInterval, m_iLifeMax, m_iLifeNowTime, m_rad;
	long	m_ox, m_oy;
	float	m_ang, m_dang;

	void	Move();
};

#endif
