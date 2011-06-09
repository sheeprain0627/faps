// MyTabThree.cpp : implementation file
//

#include "stdafx.h"
#include "MyTabThree.h"
#include "afxdialogex.h"


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
END_MESSAGE_MAP()


// MyTabThree message handlers
