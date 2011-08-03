#pragma once


// MyTabOne dialog
#include "resource.h"
#include "afxwin.h"
class MyTabOne : public CDialog
{
	DECLARE_DYNAMIC(MyTabOne)

public:
	MyTabOne(CWnd* pParent = NULL);   // standard constructor
	virtual ~MyTabOne();

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
	afx_msg void OnBnClickedButton5();
	int getfwidth();
	int getfHeight();
	void resizePic();
	void cropPic();
	void cropPic1();
	void resizePic1();

	void resizePicDB();

	afx_msg void OnBnClickedSetface();
};
