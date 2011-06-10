// MyTabTwo.cpp : implementation file
//

#include "stdafx.h"
#include "MyTabTwo.h"
#include "afxdialogex.h"


// MyTabTwo dialog

IMPLEMENT_DYNAMIC(MyTabTwo, CDialog)

MyTabTwo::MyTabTwo(CWnd* pParent /*=NULL*/)
	: CDialog(MyTabTwo::IDD, pParent)
{

}

MyTabTwo::~MyTabTwo()
{
}

void MyTabTwo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MyTabTwo, CDialog)
	ON_BN_CLICKED(IDC_RADIO1, &MyTabTwo::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &MyTabTwo::OnBnClickedRadio2)
END_MESSAGE_MAP()


// MyTabTwo message handlers


void MyTabTwo::OnBnClickedRadio1()
{
	display(GL_POINTS);
	// TODO: Add your control notification handler code here
}


void MyTabTwo::OnBnClickedRadio2()
{
	InvalidateRect(NULL,TRUE);
display(GL_TRIANGLES);

	// TODO: Add your control notification handler code here
}
