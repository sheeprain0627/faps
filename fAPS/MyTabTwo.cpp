// MyTabTwo.cpp : implementation file
//

#include "stdafx.h"
#include "MyTabTwo.h"
#include "afxdialogex.h"
#include "OpenGLControl.h"
#include <sstream>
//#include "Tdsloader"

//hh
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
	//DDX_Control(pDX, IDC_COMBO1, myCombo);	
	DDX_Control(pDX, IDC_EDIT3, contrat);
}


BEGIN_MESSAGE_MAP(MyTabTwo, CDialog)
	ON_BN_CLICKED(IDC_RADIO1, &MyTabTwo::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &MyTabTwo::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_BUTTON2, &MyTabTwo::OnBnClickedButton2)	
	ON_BN_CLICKED(IDC_UP, &MyTabTwo::OnBnClickedUp)
	ON_BN_CLICKED(IDC_MoveUp, &MyTabTwo::OnBnClickedMoveup)
	ON_BN_CLICKED(IDC_MoveRight, &MyTabTwo::OnBnClickedMoveright)
	ON_BN_CLICKED(IDC_MoveDown, &MyTabTwo::OnBnClickedMovedown)
	ON_BN_CLICKED(IDC_Zoom, &MyTabTwo::OnBnClickedZoom)
	ON_BN_CLICKED(IDC_BUTTON4, &MyTabTwo::OnBnClickedButton4)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// MyTabTwo message handlers


void MyTabTwo::OnBnClickedRadio1()
{
	//MessageBox("Points");
	//modify();
	//display(c);
	//COpenGLControl::m_type=GL_POINTS;
	changeMode(GL_POINTS);
	// TODO: Add your control notification handler code here
}


void MyTabTwo::OnBnClickedRadio2()
{
	//COpenGLControl::m_type=GL_TRIANGLES;
	changeMode(GL_TRIANGLES);

	// TODO: Add your control notification handler code here
}


void MyTabTwo::OnBnClickedButton2()
{
	//IDC_EDIT1 aa;
	//MyTabTwo bb;

	CString s;
	GetDlgItemText(IDC_EDIT1, s);
	float x = atof( s );

	//int nIndex = IDC_COMBO1.GetCurSel();
	CString selectedString;
	// string strText;
	// int  cmbBoxindex=myCombo.GetItemData(IDC_COMBO1);
	int cmbindex=myCombo.GetCurSel();
	myCombo.GetLBText(cmbindex,selectedString);
	//myCombo.getlb
	//m_cmbBox.GetLBText(m_cmbBox.GetCurSel() ,strCBText);
	// GetLBText(IDC_COMBO1,s);
	// m_cbExample.GetLBText( nIndex, strCBText);



	///////////////////////////////////////////////////////////////////////////////////
	/*
	modify(x,selectedString);

	*/
	/////////////////////////////////////////////////////////////////////////////////

	// TODO: Add your control notification handler code here
}


void MyTabTwo::OnBnClickedUp()
{
	// TODO: Add your control notification handler code here
}


void MyTabTwo::OnBnClickedMoveup()
{
	move('u');
}


void MyTabTwo::OnBnClickedMoveright()
{
	move('r');
}


void MyTabTwo::OnBnClickedMovedown()
{
	move('d');
}

void MyTabTwo::OnBnClickedButton4()
{
	move('l');// TODO: Add your control notification handler code here
}

void MyTabTwo::OnBnClickedZoom()
{
	scaleTex();
}


BOOL MyTabTwo::OnEraseBkgnd(CDC* pDC)
{


	SBitdraw(pDC, IDB_TABBACKGRND, 1);
	return true;//CDialog::OnEraseBkgnd(pDC);
}

bool MyTabTwo::SBitdraw(CDC *pDC, UINT nIDResource, int i) 
{
	CBitmap* m_bitmap;
	m_bitmap=new CBitmap();
	m_bitmap->LoadBitmap(nIDResource);
	if(!m_bitmap->m_hObject)
		return true;
	CRect rect;
	GetClientRect(&rect);
	CDC dc;
	dc.CreateCompatibleDC(pDC);    
	dc.SelectObject(m_bitmap);
	int bmw, bmh ;
	BITMAP bmap;
	m_bitmap->GetBitmap(&bmap);
	bmw = bmap.bmWidth;
	bmh = bmap.bmHeight;
	int xo=0, yo=0;
	switch(i){
	case 1:
		pDC->StretchBlt(xo, yo, rect.Width(),
			rect.Height(), &dc,
			0, 0,bmw,bmh, SRCCOPY);
		break;
	case 2:
		if(bmw < rect.Width())
			xo = (rect.Width() - bmw)/2;
		else 
			xo=0;
		if(bmh < rect.Height())
			yo = (rect.Height()-bmh)/2;
		else
			yo=0;
		pDC->BitBlt (xo, yo, rect.Width(),
			rect.Height(), &dc,
			0, 0, SRCCOPY);
		break;
	case 3:
		for (yo = 0; yo < rect.Height(); yo += bmh)
		{
			for (xo = 0; xo < rect.Width(); xo += bmw)
			{
				pDC->BitBlt (xo, yo, rect.Width(),
					rect.Height(), &dc,
					0, 0, SRCCOPY);
			}
		}
	}
	return true;

}

