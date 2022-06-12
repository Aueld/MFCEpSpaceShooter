#if !defined(AFX_ENEMYKING_H__9DF59F18_47E1_4A48_8818_463A06447B36__INCLUDED_)
#define AFX_ENEMYKING_H__9DF59F18_47E1_4A48_8818_463A06447B36__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EpEnemyObj.h"

class EpBoss : public EpEnemyObj
{
public:
	EpBoss();
	virtual ~EpBoss();

	void GiveAtt(int iStyle, long x, long y, CDC* backDC, CArray<EpEnemyBullet*, EpEnemyBullet*> *arEB);
	short CheckAndDraw(POINT mp);
	short Hit();
	bool CheckHP();

private:
	short m_iMoveStyle, m_bossHP;
	//int		m_iShootInterval, m_iMissileSpeed, m_iLifeMax, m_iLifeNowTime, m_rad;
	int	m_iShootInterval, m_iMissileSpeed, m_iLifeNowTime, m_rad;
	long m_ox, m_oy;
	float m_ang, m_dang;

	void Move();
};

#endif
