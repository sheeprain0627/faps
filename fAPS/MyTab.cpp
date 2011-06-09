// MyTab.cpp : implementation file
//

#include "stdafx.h"
#include "MyTab.h"


// MyTab

IMPLEMENT_DYNCREATE(MyTab, CWinApp)

MyTab::MyTab()
{
}

MyTab::~MyTab()
{
}

BOOL MyTab::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int MyTab::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinApp::ExitInstance();
}

BEGIN_MESSAGE_MAP(MyTab, CWinApp)
END_MESSAGE_MAP()


// MyTab message handlers
