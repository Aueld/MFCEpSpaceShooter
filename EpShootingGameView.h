#if !defined(AFX_SHOOTINGGAMEVIEW_H__2652D79D_3C2A_49F8_99B1_10F9976A8782__INCLUDED_)
#define AFX_SHOOTINGGAMEVIEW_H__2652D79D_3C2A_49F8_99B1_10F9976A8782__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "EpEnemyObj.h"
#include "EpEnemyPlane.h"
#include "EpPlayer.h"
#include "ScenarioManager.h"
#include "EpPlayerBullet.h"


class EpShootingGameView : public CView
{
protected:
	EpShootingGameView();
	DECLARE_DYNCREATE(EpShootingGameView)
	CScenarioManager m_clSM;
	
	void VTextUI();
	void reStartGame();
	void GameOver();
	void GameEnd();
	
public:
	// player
	EpPlayer m_player;
	CPoint m_oldMousePos;
	CArray<EpPlayerBullet*,EpPlayerBullet*> m_playerBullet;
	
	// enemey
	CArray<EpEnemyObj*, EpEnemyObj*> m_enemyObj;
	CArray<EpEnemyBullet*, EpEnemyBullet*> m_enemyBullet;

	// View
	CDC MemDC,BackDC;
	CBitmap m_bmpM, m_bmpE, m_bmpB, m_bmpEB, m_bmpBackDC, m_bmpBackground;

	BOOL m_MoveFlag, m_RBtnDnFlg, m_bGameOver, bGameOverMsg;
	CRect m_rect;
	CString score, end_text;
	int m_iEnemyGenMode, m_score;
	long m_timeCnt;
	
public:
	EpShootingGameDoc* GetDocument();

	public:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	//}}AFX_VIRTUAL

public:
	virtual ~EpShootingGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CShootingGameView)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG
inline CShootingGameDoc* CShootingGameView::GetDocument()
   { return (CShootingGameDoc*)m_pDocument; }
#endif

#endif
