// TabTwo.cpp : implementation file
//

#include "stdafx.h"
#include "TabTwo.h"
#include "afxdialogex.h"


// TabTwo dialog

IMPLEMENT_DYNAMIC(TabTwo, CDialog)

TabTwo::TabTwo(CWnd* pParent /*=NULL*/)
	: CDialog(TabTwo::IDD, pParent)
{

}

TabTwo::~TabTwo()
{
}

void TabTwo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TabTwo, CDialog)
END_MESSAGE_MAP()


// TabTwo message handlers
