// StartDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StartDlg.h"
#include "afxdialogex.h"
#include "resource.h"


// StartDlg dialog

IMPLEMENT_DYNAMIC(StartDlg, CDialog)

StartDlg::StartDlg(CWnd* pParent /*=NULL*/)
	: CDialog(StartDlg::IDD, pParent)
{

}

StartDlg::~StartDlg()
{
}

void StartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_INIT, editInit);
	DDX_Control(pDX, IDC_PROGRESS_BAR, progressInit);
}


BEGIN_MESSAGE_MAP(StartDlg, CDialog)
END_MESSAGE_MAP()


// StartDlg.cpp : implementation file
BOOL StartDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	SetDlgItemText(IDC_EDIT_INIT,"Initializing...");
	progressInit.SetRange(0,100);
	progressInit.ShowWindow(TRUE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void StartDlg::CloseDlg()
{
	Sleep(1000);
	CDialog::OnOK();
}


void StartDlg::SetPos(int p_iPosition)
{
	progressInit.SetPos(p_iPosition);
}
// StartDlg message handlers
