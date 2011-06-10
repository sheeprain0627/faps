
#if !defined(AFX_TABEXAMPLE1_H__A4E4384B_0BB6_4FC2_A763_711C0F32B290__INCLUDED_)
#define AFX_TABEXAMPLE1_H__A4E4384B_0BB6_4FC2_A763_711C0F32B290__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbol
// cvisionDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "OpenGLControl.h"
#include "MyTabOne.h"
#include "MyTabThree.h"
#include "MyTabTwo.h"
#include "MyFTabCtrl.h"

// CcvisionDlg dialog
class CcvisionDlg : public CDialogEx
{
// Construction
public:
	CcvisionDlg(CWnd* pParent = NULL);	// standard constructor
	


// Dialog Data
	enum { IDD = IDD_CVISION_DIALOG };

	MyTabOne*	m_pDlgPage1;
	MyTabTwo*	m_pDlgPage2;
	MyTabThree*	m_pDlgPage3;
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOpen();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	CStatic m_PicCtrl;
	afx_msg void OnBnClickedOk();
	CButton m_Button1;
//	afx_msg void OnStnClickedpicture();
	afx_msg void OnEnChangeEdit1();
	void swap(int a, int b);
//	CEdit m_textbox;
	

private :
	COpenGLControl m_oglWindow;

public:
	afx_msg void OnBnClickedButton3();
	MyFTabCtrl m_TabCtrl;
};
#endif