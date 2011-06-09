#pragma once
#include "resource.h"
#include "afxwin.h"

// TabOne dialog

class TabOne : public CDialog
{
	DECLARE_DYNAMIC(TabOne)

public:
	TabOne(CWnd* pParent = NULL);   // standard constructor
	virtual ~TabOne();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	CStatic m_PicCtrl;
};
