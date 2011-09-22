// MyFTabCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "MyFTabCtrl.h"


// MyFTabCtrl

IMPLEMENT_DYNAMIC(MyFTabCtrl, CTabCtrl)

/*!
constructor of MyFTabCtrl
*/
	MyFTabCtrl::MyFTabCtrl()
{
	m_nPageCount = 0;
}

/*!
destructor of MyFTabCtrl
*/
MyFTabCtrl::~MyFTabCtrl()
{
}

/*!
to add a page to dialog
\param pPageWnd as CWnd of Dialog
\param lpTitle as LPTSTR of title of tab control
*/
void MyFTabCtrl::AddPage(CWnd *pPageWnd, LPTSTR lpTitle)
{
	TCITEM	itemPage;

	itemPage.mask = TCIF_TEXT|TCIF_PARAM;
	itemPage.lParam	= LPARAM(pPageWnd);
	itemPage.pszText = lpTitle;

	InsertItem(m_nPageCount, &itemPage);
	m_nPageCount == 0?pPageWnd->ShowWindow(SW_SHOW) : pPageWnd->ShowWindow(SW_HIDE);
	m_nPageCount++;
}

/*!
to show current page
\param nShowState as UNIT of control ID
*/

void MyFTabCtrl::ShowCurPage(UINT nShowState)
{
	int		nCurItem;
	TCITEM	itemCur;

	nCurItem		= GetCurSel();
	itemCur.mask	= TCIF_PARAM;

	GetItem(nCurItem, &itemCur);
	((CWnd*)itemCur.lParam)->ShowWindow(nShowState);
}


BEGIN_MESSAGE_MAP(MyFTabCtrl, CTabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGING, &MyFTabCtrl::OnTcnSelchanging)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, &MyFTabCtrl::OnTcnSelchange)
END_MESSAGE_MAP()



// MyFTabCtrl message handlers



/*!
hadling on select changes
*/
void MyFTabCtrl::OnTcnSelchanging(NMHDR *pNMHDR, LRESULT *pResult)
{
	ShowCurPage(SW_HIDE);
	
	*pResult = 0;
}

/*!
hadling on select changes
*/
void MyFTabCtrl::OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult)
{
	ShowCurPage(SW_SHOW);
	
	*pResult = 0;
}
