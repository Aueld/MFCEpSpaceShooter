#if !defined(AFX_SHOOTINGGAME_H__6E4710A8_8213_4F19_9EF3_41E5FF56A674__INCLUDED_)
#define AFX_SHOOTINGGAME_H__6E4710A8_8213_4F19_9EF3_41E5FF56A674__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"

class CShootingGameApp : public CWinApp
{
public:
	CShootingGameApp();

	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

#endif
