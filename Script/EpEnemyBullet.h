#if !defined(AFX_ENEMYBULLET_H__B523A231_A118_4373_8F2C_A11719DAF4C0__INCLUDED_)
#define AFX_ENEMYBULLET_H__B523A231_A118_4373_8F2C_A11719DAF4C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class EpEnemyBullet  
{
public:
	EpEnemyBullet();
	virtual ~EpEnemyBullet();

	void GiveAtt(short iMoveStyle,POINT mp,POINT p, CDC* backDC);
	short CheckAndDraw(POINT mp);
	POINT m_point, m_speed;

private:
	CDC	*m_backDC,m_memDC;
	CBitmap m_bmpEB;
	
	void Draw();
	void Move();
};

#endif