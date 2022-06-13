#include "stdafx.h"
#include "EpShootingGame.h"

#include "EpShootingGameDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(EpShootingGameDoc, CDocument)

BEGIN_MESSAGE_MAP(EpShootingGameDoc, CDocument)

END_MESSAGE_MAP()


EpShootingGameDoc::EpShootingGameDoc()
{

}

EpShootingGameDoc::~EpShootingGameDoc()
{
}

BOOL EpShootingGameDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}


void EpShootingGameDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{

	}
	else
	{

	}
}


#ifdef _DEBUG
void EpShootingGameDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void EpShootingGameDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif

