// MyTabThree.cpp : implementation file
//

#include "stdafx.h"
#include "MyTabThree.h"
#include "afxdialogex.h"
#include "Tdsloader.h"
#include "Ageprogression.h"


// MyTabThree dialog
Ageprogression age;
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
	DDX_Control(pDX, IDC_AgeBar, agebar);
}


BEGIN_MESSAGE_MAP(MyTabThree, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &MyTabThree::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_Pick, &MyTabThree::OnBnClickedPick)
	ON_BN_CLICKED(IDC_LoadTexture, &MyTabThree::OnBnClickedLoadtexture)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_AgeBar, &MyTabThree::OnNMCustomdrawAgebar)
	ON_EN_CHANGE(IDC_EDIT1, &MyTabThree::OnEnChangeEdit1)
END_MESSAGE_MAP()


// MyTabThree message handlers


void MyTabThree::OnBnClickedButton1()
{
float p=age.getSigma();
age.texureEnhancePrototype(p);
}


void MyTabThree::OnBnClickedPick()
{
	drawBox();
	// TODO: Add your control notification handler code here
}


void MyTabThree::OnBnClickedLoadtexture()
{
	this->DragAcceptFiles(true);
	CFileDialog dlg(TRUE, _T("*.bmp"), NULL,
	OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY,
	_T("image files (*.bmp; *.jpg) |*.bmp;*.jpg|All Files (*.*)|*.*||"),NULL);
 
	dlg.m_ofn.lpstrTitle= _T("Open Image");
 
	if (dlg.DoModal() == IDOK) { 
		CString path= dlg.GetPathName();
		LoadImage2(path,255,0,0);		
	}
}


void MyTabThree::OnNMCustomdrawAgebar(NMHDR *pNMHDR, LRESULT *pResult)
{
	
	int curret =agebar.GetPos();
	
	float x=(float)(curret-20)/30;
	changeContrast(x);
	
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void MyTabThree::OnEnChangeEdit1()
{

	CString s;
	GetDlgItemText(IDC_EDIT3, s);
	float p = atof( s );
	age.setSigma(p);
	
}
