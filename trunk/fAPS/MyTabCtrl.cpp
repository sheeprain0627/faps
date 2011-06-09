// MyTabCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "MyTabCtrl.h"


// MyTabCtrl

IMPLEMENT_DYNAMIC(MyTabCtrl, CTabCtrl)

MyTabCtrl::MyTabCtrl()
{
	m_nPageCount	= 0;
}

MyTabCtrl::~MyTabCtrl()
{
}


void MyTabCtrl::AddPage(CWnd *pPageWnd, LPTSTR lpTitle)
{
	TCITEM	itemPage;

	itemPage.mask		= TCIF_TEXT|TCIF_PARAM;
	itemPage.lParam		= LPARAM(pPageWnd);
	itemPage.pszText	= lpTitle;

	InsertItem(m_nPageCount, &itemPage);
	m_nPageCount==0?pPageWnd->ShowWindow(SW_SHOW):pPageWnd->ShowWindow(SW_HIDE);
	m_nPageCount++;
}

void MyTabCtrl::ShowCurPage(UINT nShowState)
{
	int		nCurItem;
	TCITEM	itemCur;

	nCurItem		= GetCurSel();
	itemCur.mask	= TCIF_PARAM;

	GetItem(nCurItem, &itemCur);
	((CWnd*)itemCur.lParam)->ShowWindow(nShowState);
}


BEGIN_MESSAGE_MAP(MyTabCtrl, CTabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, &MyTabCtrl::OnTcnSelchange)
//	ON_NOTIFY_REFLECT(TCN_SELCHANGING, &MyTabCtrl::OnTcnSelchanging)
ON_NOTIFY_REFLECT(TCN_SELCHANGING, &MyTabCtrl::OnTcnSelchanging)
END_MESSAGE_MAP()



// MyTabCtrl message handlers




void MyTabCtrl::OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	ShowCurPage(SW_SHOW);
	*pResult = 0;
}


//void MyTabCtrl::OnTcnSelchanging(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	// TODO: Add your control notification handler code here
//	
//	ShowCurPage(SW_SHOW);
//	*pResult = 0;
//}


void MyTabCtrl::OnTcnSelchanging(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here

	ShowCurPage(SW_HIDE);
	*pResult = 0;
}
