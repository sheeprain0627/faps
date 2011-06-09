#pragma once


// MyTabCtrl

class MyTabCtrl : public CTabCtrl
{
	DECLARE_DYNAMIC(MyTabCtrl)

	int		m_nPageCount;

public:
	MyTabCtrl();
	virtual ~MyTabCtrl();

	void	AddPage(CWnd* pPageWnd, LPTSTR lpTitle);	
	void	ShowCurPage(UINT nShowState);	

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnTcnSelchanging(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchanging(NMHDR *pNMHDR, LRESULT *pResult);
};


