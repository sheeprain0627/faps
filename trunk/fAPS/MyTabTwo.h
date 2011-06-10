#pragma once
#include "Tdsloader.h"

// MyTabTwo dialog
#include "resource.h"

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
};
