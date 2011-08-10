#pragma once


// MyFTabCtrl

class MyFTabCtrl : public CTabCtrl
{
	DECLARE_DYNAMIC(MyFTabCtrl)
	int		m_nPageCount;

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


