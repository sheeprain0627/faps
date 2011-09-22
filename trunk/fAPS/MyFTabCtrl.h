#pragma once


/*
* the controller for the tab
*/

class MyFTabCtrl : public CTabCtrl
{
	DECLARE_DYNAMIC(MyFTabCtrl)
	int		m_nPageCount;	/*!< int value m_nPageCount of no of pages. */

public:
	MyFTabCtrl();
	virtual ~MyFTabCtrl();
	void	AddPage(CWnd* pPageWnd, LPTSTR lpTitle);	
	void	ShowCurPage(UINT nShowState);	

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnTcnSelchanging(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);
};


