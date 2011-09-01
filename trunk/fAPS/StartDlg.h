#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "resource.h"

// StartDlg dialog

class StartDlg : public CDialog
{
	DECLARE_DYNAMIC(StartDlg)

public:
	StartDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~StartDlg();
	void CloseDlg();
	void SetPos(int p_iPosition);

// Dialog Data
	enum { IDD = IDD_START_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CEdit editInit;
	CProgressCtrl progressInit;
};
