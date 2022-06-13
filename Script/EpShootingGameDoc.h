#if !defined(AFX_SHOOTINGGAMEDOC_H__F96BD02D_82D7_479F_B2B0_200140381B30__INCLUDED_)
#define AFX_SHOOTINGGAMEDOC_H__F96BD02D_82D7_479F_B2B0_200140381B30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class EpShootingGameDoc : public CDocument
{
protected:
	EpShootingGameDoc();
	DECLARE_DYNCREATE(EpShootingGameDoc);

public:
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

	virtual ~EpShootingGameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	DECLARE_MESSAGE_MAP()
};

#endif