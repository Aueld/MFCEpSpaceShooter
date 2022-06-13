#if !defined(AFX_MYPLANE_H__507BB7A9_4546_44F1_90D1_91C67E89CEE4__INCLUDED_)
#define AFX_MYPLANE_H__507BB7A9_4546_44F1_90D1_91C67E89CEE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>

class EpPlayer  
{
public:
	EpPlayer();
	virtual ~EpPlayer();
	
	POINT m_point;
	float m_MyVelocityX, m_MyVelocityY;
	short m_bombCnt;
	int m_HP;
	bool m_check;

	void GiveAtt(long x, long y, CDC* backDC);
	void CheckAndDraw(POINT mp);
	void ChgToCrashedStat();
	void Init();

private:
	CDC	*m_backDC,m_memDC;
	CBitmap m_bmpM, m_bmpCrashed, m_bmpCrashed1;
	short m_mpWidth, m_mpHeight;
	void Draw();
};

#endif
