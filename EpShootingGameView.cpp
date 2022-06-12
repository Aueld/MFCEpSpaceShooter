#include "stdafx.h"
#include "EpShootingGame.h"

#include "EpShootingGameDoc.h"
#include "EpShootingGameView.h"
#include  <math.h>
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(EpShootingGameView, CView)

BEGIN_MESSAGE_MAP(EpShootingGameView, CView)
	//{{AFX_MSG_MAP(CShootingGameView)
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()


EpShootingGameView::EpShootingGameView()
{

}

EpShootingGameView::~EpShootingGameView()
{
}

BOOL EpShootingGameView::PreCreateWindow(CREATESTRUCT& cs)
{

	return CView::PreCreateWindow(cs);
}

void EpShootingGameView::OnDraw(CDC* pDC)
{
	EpShootingGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

BOOL EpShootingGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void EpShootingGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{

}

void EpShootingGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{

}

#ifdef _DEBUG
void EpShootingGameView::AssertValid() const
{
	CView::AssertValid();
}

void EpShootingGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

EpShootingGameDoc* EpShootingGameView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(EpShootingGameDoc)));
	return (EpShootingGameDoc*)m_pDocument;
}
#endif //_DEBUG

void EpShootingGameView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();

	CClientDC dc(this);
	
	GetClientRect(&m_rect);
	
	m_rect.left = 0;
	m_rect.top = 0;
	
	//Load bitmaps
//	m_bmpBackground.LoadBitmap(IDB_BMP_BACKGROUND);

	m_bmpEB.LoadBitmap(IDB_EB_G);
	
	
	//Create compatible DC
	BackDC.CreateCompatibleDC(&dc);
	m_bmpBackDC.CreateCompatibleBitmap(&dc,m_rect.Width(),m_rect.Height());
	BackDC.SelectObject(&m_bmpBackDC);
	
	MemDC.CreateCompatibleDC(&dc);

	//Initialize  플레이어
	m_player.GiveAtt(m_rect.Width() / 2,m_rect.Height() / 2, &BackDC);

	//Initialize 시나리오
	m_clSM.m_arE = &m_enemyObj;
	m_clSM.m_backDC = &BackDC;
	m_clSM.m_arEB = &m_enemyBullet;

	//Initialize 적
	m_enemyObj.RemoveAll();
	m_iEnemyGenMode = 0;

	//Initialize  적 탄환
	m_enemyBullet.RemoveAll();

	//Initialize bullets 
	m_playerBullet.RemoveAll();

	
	//Initialize game parameter
	m_MoveFlag = FALSE;
	m_oldMousePos.x = m_rect.Width() / 2;
	m_oldMousePos.y = m_rect.Height() / 2;
	m_bGameOver = FALSE;
	bGameOverMsg = FALSE;
	m_RBtnDnFlg = FALSE;

	//Set Score
	m_score = 0;

	//Set timer
	m_timeCnt = 0;
	SetTimer(0,30,NULL);
}
/*
void EpShootingGameView::AddEnemy()
{
	CEnemyObj* enemy = new CEnemyObj();
	enemy->GiveLife(m_iEnemyGenMode, &m_rect);
	m_arE.Add(enemy);

	m_iEnemyGenMode++;
	if(m_iEnemyGenMode > MAX_E_SPECIES) 
		m_iEnemyGenMode = 0;
}
*/

// 게임 타이머
void EpShootingGameView::OnTimer(UINT nIDEvent) 
{
	int i;

	CClientDC dc(this);
	GetClientRect(&m_rect);
	
	//Enable copy from background to foreground
	BackDC.SelectObject(&m_bmpBackDC);

	//Clear screen
	CBrush brush(RGB(255, 255, 255));
	BackDC.FillRect(m_rect, &brush );

	VTextUI();

	//플레이어
	m_player.CheckAndDraw(m_oldMousePos);

	MemDC.SelectObject(&m_bmpE);

	for(i = 0; i < m_enemyObj.GetSize(); i++)
	{
		short flg = m_enemyObj[i]->CheckAndDraw(m_player.m_point);
		switch(flg)
		{
		case -1:
			//KillTimer(0);
			m_bGameOver = TRUE;
			break;
		case 1:
			if (m_enemyObj[i]->m_check) {
				GameEnd();
			}

			m_enemyObj[i]->~EpEnemyObj();
			m_enemyObj.RemoveAt(i);
			i--;
			
			if(!m_bGameOver)
				m_score += 10;
			break;
		}
	}

	//플레이어 탄환
	for(i = m_playerBullet.GetSize() - 1; i >=0 ; i--)
	{
		if(m_playerBullet[i]->CheckAndDraw() == 1)
		{
			m_playerBullet[i]->~EpPlayerBullet();
			m_playerBullet.RemoveAt(i);
			i--;

		}
	}

	//적 탄환
	for(i = m_enemyBullet.GetSize() - 1; i >=0 ; i--)
	{
		switch(m_enemyBullet[i]->CheckAndDraw(m_player.m_point))
		{
		case -1:
			//KillTimer(0);
			m_bGameOver = TRUE;
			break;
		case 1:
			m_enemyBullet[i]->~EpEnemyBullet();
			m_enemyBullet.RemoveAt(i);
			i--;

			if (!m_bGameOver)
				m_score += 1;
		}
	}

	//Draw Full Screen
	dc.BitBlt(0,0,m_rect.Width(), m_rect.Height(),&BackDC,0,0,SRCCOPY);
	
	if(m_RBtnDnFlg)
	{
		if(m_playerBullet.GetSize()<MAX_BULLETS)
		{
			EpPlayerBullet *bullet = new EpPlayerBullet();
			POINT pos = m_player.m_point;
			bullet->GiveAtt(pos, &BackDC, &m_enemyObj);
			m_playerBullet.Add(bullet);
		}
	}
	
	//게임 오버시
	if(m_bGameOver)
	{
		m_player.ChgToCrashedStat();
		GameOver();
	}

	m_timeCnt++;
	m_clSM.Unfold(m_timeCnt);
	SetFocus();
	CView::OnTimer(nIDEvent);
}

void EpShootingGameView::VTextUI()
{
	//CFont font;
	//font.CreateFont(400, _T("고딕"));
	//BackDC.SelectObject(&font);

	if (m_timeCnt < 200)
		BackDC.TextOutA(m_rect.Width() / 2 - 200, 400, _T("조작 설명\n 마우스 좌클릭 : 이동 토글, 우클릭 : 자동 발사 토글"));
	if (m_timeCnt > 200 && m_timeCnt < 250)
		BackDC.TextOutA(m_rect.Width() / 2 - 150, 400, _T("재미있게 플레이 해주시면 감사합니다 :)"));



	score.Format(_T("점수 : %d"), m_score);
	//score += (m_score);

	BackDC.TextOutA(1000, 100, score);

}

void EpShootingGameView::reStartGame()
{
	//CBrush brush(RGB(255, 255, 255));
	//BackDC.FillRect(m_rect, &brush);

	m_player.CheckAndDraw(m_oldMousePos);

	m_iEnemyGenMode = 0;

	m_enemyObj.RemoveAll();
	m_enemyBullet.RemoveAll();
	m_playerBullet.RemoveAll();

	m_player.m_check = false;
	m_player.Init();

	m_bGameOver = FALSE;
	m_MoveFlag = FALSE;
	m_oldMousePos.x = m_rect.Width() / 2;
	m_oldMousePos.y = m_rect.Height() / 2;

	bGameOverMsg = FALSE;
	m_RBtnDnFlg = FALSE;

	m_score = 0;
	m_timeCnt = 0;
	m_clSM.Unfold(m_timeCnt);
	SetFocus();
}

void EpShootingGameView::GameOver()
{
	m_RBtnDnFlg = FALSE;

	m_player.m_check = true;

	if (bGameOverMsg)
		return;

	bGameOverMsg = TRUE;

	end_text.Format(_T(" 게임 오버 \n 최종 점수 : %d 점\n 재시작 \"예\", 게임 종료 \"아니오\""), m_score);

	if (AfxMessageBox(end_text, MB_YESNO) == IDYES)
	{
		reStartGame();
	}
	else
	{
		(CMainFrame*)GetParentFrame( )->PostMessage(WM_COMMAND,ID_APP_EXIT);	
	}
}

void EpShootingGameView::GameEnd()
{
	m_RBtnDnFlg = FALSE;

	m_player.m_check = true;

	if (bGameOverMsg)
		return;

	bGameOverMsg = TRUE;

	end_text.Format(_T(" 게임 클리어 \n 최종 점수 : %d 점\n"), m_score);

	if (AfxMessageBox(end_text, MB_YESNO) == IDYES)
	{
		(CMainFrame*)GetParentFrame()->PostMessage(WM_COMMAND, ID_APP_EXIT);
	}
	else
	{
		(CMainFrame*)GetParentFrame()->PostMessage(WM_COMMAND, ID_APP_EXIT);
	}
}


BOOL EpShootingGameView::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN && 
		(pMsg->wParam == VK_RIGHT || pMsg->wParam == VK_LEFT || pMsg->wParam == VK_UP || pMsg->wParam == VK_DOWN))
	{
		SendMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
	}
	if(pMsg->message == WM_KEYDOWN &&  pMsg->wParam == VK_SPACE)
	{
		if(m_playerBullet.GetSize()<MAX_BULLETS)
		{
			EpPlayerBullet *bullet = new EpPlayerBullet();
			POINT pos = m_player.m_point;
			bullet->GiveAtt(pos, &BackDC, &m_enemyObj);
			m_playerBullet.Add(bullet);
		}
	}

	return CView::PreTranslateMessage(pMsg);
}


void EpShootingGameView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// 키보드 조작

	//switch(nChar)
	//{
	//case VK_NUMPAD4:
	//case VK_LEFT:
	//	m_mp.m_MyVelocityX--;
	//	break;
	//case VK_NUMPAD6:
	//case VK_RIGHT:
	//	m_mp.m_MyVelocityX++;
	//	break;
	//case VK_NUMPAD8:
	//case VK_UP:
	//	m_mp.m_MyVelocityY--;
	//	break;
	//case VK_NUMPAD2:
	//case VK_DOWN:
	//	m_mp.m_MyVelocityY++;
	//	break;
	//}	

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void EpShootingGameView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	//m_MoveFlag = TRUE;
	
	CView::OnLButtonDown(nFlags, point);
}

void EpShootingGameView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	//m_MoveFlag = FALSE;

	if (!m_MoveFlag)
		m_MoveFlag = TRUE;
	else if (m_MoveFlag)
		m_MoveFlag = FALSE;
	
	CView::OnLButtonUp(nFlags, point);
}

void EpShootingGameView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(!m_MoveFlag)
		return;
	m_oldMousePos = point;
	
	CView::OnMouseMove(nFlags, point);
}

void EpShootingGameView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	//m_RBtnDnFlg = TRUE;

	CView::OnRButtonDown(nFlags, point);
}

void EpShootingGameView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	//m_RBtnDnFlg = FALSE;

	if (!m_RBtnDnFlg)
		m_RBtnDnFlg = TRUE;
	else if (m_RBtnDnFlg)
		m_RBtnDnFlg = FALSE;
	CView::OnRButtonUp(nFlags, point);
}
