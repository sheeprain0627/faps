// MyTabTwo.cpp : implementation file
//

#include "stdafx.h"
#include "MyTabTwo.h"
#include "afxdialogex.h"
#include "Tdsloader"


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
	ON_BN_CLICKED(IDC_BUTTON2, &MyTabTwo::OnBnClickedButton2)
END_MESSAGE_MAP()


// MyTabTwo message handlers


void MyTabTwo::OnBnClickedRadio1()
{
	//MessageBox("Points");
	//modify();
	//display(GL_POINTS);
	// TODO: Add your control notification handler code here
}


void MyTabTwo::OnBnClickedRadio2()
{
	InvalidateRect(NULL,TRUE);
display(GL_TRIANGLES);

	// TODO: Add your control notification handler code here
}


void MyTabTwo::OnBnClickedButton2()
{
	Tdsloader::
	CString s;
	GetDlgItemText(IDC_EDIT1, s);
	float x = atof( s );
	modify(x);
		
	// TODO: Add your control notification handler code here
}
