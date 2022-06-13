#if !defined(AFX_SCENARIOMANAGER_H__4A29758D_6AF5_4A39_BEC7_059009D243A9__INCLUDED_)
#define AFX_SCENARIOMANAGER_H__4A29758D_6AF5_4A39_BEC7_059009D243A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "EpUnit.h"
class CScenarioManager  
{
public:
	CScenarioManager();
	virtual ~CScenarioManager();
	void Unfold(long timeCnt);
	CDC	*m_backDC;

	CArray<EpUnit*, EpUnit*> *m_unit;
	CArray<EpEnemyBullet*, EpEnemyBullet*> *m_enemyBullet;

private:
	void AddEnemy(int iStyle, int x, int y);
	void AddBoss(int iStyle, int x, int y);
	void MakeFormation(int iStyle);
};

#endif
