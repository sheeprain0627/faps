//!  tab 2 controller class
/*!
  control the functionalities of tab2
*/

#include "stdafx.h"
#include "MyTabTwo.h"
#include "afxdialogex.h"
#include "OpenGLControl.h"
#include <sstream>


IMPLEMENT_DYNAMIC(MyTabTwo, CDialog)
/*!
	 constructor of tab2
*/

	MyTabTwo::MyTabTwo(CWnd* pParent /*=NULL*/)
	: CDialog(MyTabTwo::IDD, pParent)
{

}

/*!
	 destructor of tab2
*/

MyTabTwo::~MyTabTwo()
{
}

/*!
	 control handlers
*/
void MyTabTwo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT3, contrat);
}


BEGIN_MESSAGE_MAP(MyTabTwo, CDialog)
	ON_BN_CLICKED(IDC_RADIO1, &MyTabTwo::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &MyTabTwo::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_BUTTON2, &MyTabTwo::OnBnClickedButton2)	
	ON_BN_CLICKED(IDC_MoveUp, &MyTabTwo::OnBnClickedMoveup)
	ON_BN_CLICKED(IDC_MoveRight, &MyTabTwo::OnBnClickedMoveright)
	ON_BN_CLICKED(IDC_MoveDown, &MyTabTwo::OnBnClickedMovedown)
	ON_BN_CLICKED(IDC_Zoom, &MyTabTwo::OnBnClickedZoom)
	ON_BN_CLICKED(IDC_BUTTON4, &MyTabTwo::OnBnClickedButton4)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

/*!
Methodthat chage the 3d model mode to GL_POINTS
*/

void MyTabTwo::OnBnClickedRadio1()
{	
	changeMode(GL_POINTS);
}


/*
* Methodthat chage the 3d model mode to GL_TRIANGLES
*/

void MyTabTwo::OnBnClickedRadio2()
{
	changeMode(GL_TRIANGLES);
}


/*!
use in testing purpose.
*/

void MyTabTwo::OnBnClickedButton2()
{
	CString s;
	GetDlgItemText(IDC_EDIT1, s);
	float x = atof( s );

	CString selectedString;
	int cmbindex=myCombo.GetCurSel();
	myCombo.GetLBText(cmbindex,selectedString);
}

/*!
Method that move the texture up in the 3d model
*/
void MyTabTwo::OnBnClickedMoveup()
{
	move('u');
}

/*!
Method that move the texture right in the 3d model
*/
void MyTabTwo::OnBnClickedMoveright()
{
	move('r');
}

/*!
Method that move the texture down in the 3d model
*/

void MyTabTwo::OnBnClickedMovedown()
{
	move('d');
}

/*!
Method that move the texture left in the 3d model
*/

void MyTabTwo::OnBnClickedButton4()
{
	move('l');
}

/*!
Method that zoom the the 3d model
*/

void MyTabTwo::OnBnClickedZoom()
{
	scaleTex();
}

/*!
to change background color
*/

BOOL MyTabTwo::OnEraseBkgnd(CDC* pDC)
{
	SBitdraw(pDC, IDB_TABBACKGRND, 1);
	return true;
}

/*!
to change background color of each controls
\param pDC as CDC
\param nIDResource contrl ID of the item
\param i as position of the backgrnd
*/

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

