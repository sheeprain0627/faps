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
	DDX_Control(pDX, IDC_COMBO1, myCombo);	
	DDX_Control(pDX, IDC_EDIT3, contrat);
}


BEGIN_MESSAGE_MAP(MyTabTwo, CDialog)
	ON_BN_CLICKED(IDC_RADIO1, &MyTabTwo::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &MyTabTwo::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_BUTTON2, &MyTabTwo::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &MyTabTwo::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON9, &MyTabTwo::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &MyTabTwo::OnBnClickedButton10)
	ON_EN_CHANGE(IDC_EDIT3, &MyTabTwo::OnEnChangeEdit3)
	//ON_EN_CHANGE(IDC_EDIT1, &MyTabTwo::OnEnChangeEdit1)
	//ON_BN_CLICKED(IDC_SPLIT1, &MyTabTwo::OnBnClickedSplit1)
	//ON_CBN_SELCHANGE(IDC_COMBO1, &MyTabTwo::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON8, &MyTabTwo::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_UP, &MyTabTwo::OnBnClickedUp)
	ON_BN_CLICKED(IDC_MoveUp, &MyTabTwo::OnBnClickedMoveup)
	
	ON_BN_CLICKED(IDC_MoveRight, &MyTabTwo::OnBnClickedMoveright)
	ON_BN_CLICKED(IDC_MoveDown, &MyTabTwo::OnBnClickedMovedown)
	ON_BN_CLICKED(IDC_Zoom, &MyTabTwo::OnBnClickedZoom)
	
	
	ON_BN_CLICKED(IDC_BUTTON4, &MyTabTwo::OnBnClickedButton4)
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


void MyTabTwo::OnBnClickedButton3()
{
	reset();// TODO: Add your control notification handler code here
}

void MyTabTwo::OnBnClickedButton9()
{

makeLine();
	// TODO: Add your control notification handler code here
}


void MyTabTwo::OnBnClickedButton10()
{		test();

}




void MyTabTwo::OnEnChangeEdit3()
{

	CString s;
	GetDlgItemText(IDC_EDIT3, s);
	float x = atof( s );
	
	changeContrast(x);
	
}





void MyTabTwo::OnBnClickedSplit1()
{
	// TODO: Add your control notification handler code here
}

/*
void MyTabTwo::OnCbnSelchangeCombo1()
{
	//  CComboBox  m_cbExample;

	  //int nIndex = m_cbExample.GetCurSel();
   // CString strCBText;
   // m_cbExample.GetLBText( nIndex, strCBText);
	
	// TODO: Add your control notification handler code here
}
*/


void MyTabTwo::OnBnClickedButton8()
{
	CString s;
	GetDlgItemText(IDC_EDIT2, s);
	int x = atoi( s );
	markVertex(x);
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









