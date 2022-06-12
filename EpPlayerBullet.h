#if !defined(AFX_MYBULLET_H__0460B346_4722_498D_BF92_CF0441262CD3__INCLUDED_)
#define AFX_MYBULLET_H__0460B346_4722_498D_BF92_CF0441262CD3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "EpEnemyObj.h"

class EpPlayerBullet  
{
public:
	EpPlayerBullet();
	virtual ~EpPlayerBullet();

	void GiveAtt(POINT p, CDC* backDC, CArray<EpEnemyObj*, EpEnemyObj*> *arE);
	short CheckAndDraw();
	POINT m_point;

private:
	CDC	*m_backDC,m_memDC;
	CBitmap m_bmpB;
	CArray<EpEnemyObj*, EpEnemyObj*> *m_arE;

	void Draw();
	void Move();
};

#endif