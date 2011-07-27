#pragma once
#include "Tdsloader.h"

// MyTabTwo dialog
#include "resource.h"
#include "afxwin.h"
#include "afxcmn.h"

class MyTabTwo : public CDialog
{
	DECLARE_DYNAMIC(MyTabTwo)

public:
	MyTabTwo(CWnd* pParent = NULL);   // standard constructor
	virtual ~MyTabTwo();

// Dialog Data
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedSplit1();
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox myCombo;
	afx_msg void OnBnClickedButton8();
	CSliderCtrl agebar;
	CEdit contrat;
	afx_msg void OnBnClickedUp();
	afx_msg void OnBnClickedMoveup();
	
	afx_msg void OnBnClickedMoveright();
	afx_msg void OnBnClickedMovedown();
	afx_msg void OnBnClickedZoom();
	
	
	afx_msg void OnBnClickedButton4();
};
