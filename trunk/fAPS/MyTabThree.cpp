// MyTabThree.cpp : implementation file
//

#include "stdafx.h"
#include "MyTabThree.h"
#include "afxdialogex.h"
#include "Tdsloader.h"


// MyTabThree dialog

IMPLEMENT_DYNAMIC(MyTabThree, CDialog)

MyTabThree::MyTabThree(CWnd* pParent /*=NULL*/)
	: CDialog(MyTabThree::IDD, pParent)
{

}

MyTabThree::~MyTabThree()
{
}

void MyTabThree::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MyTabThree, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &MyTabThree::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_Pick, &MyTabThree::OnBnClickedPick)
END_MESSAGE_MAP()


// MyTabThree message handlers


void MyTabThree::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
}


void MyTabThree::OnBnClickedPick()
{
	drawBox();
	// TODO: Add your control notification handler code here
}
