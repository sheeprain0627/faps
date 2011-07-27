// MyTabThree.cpp : implementation file
//

#include "stdafx.h"
#include "MyTabThree.h"
#include "afxdialogex.h"
#include "Tdsloader.h"
#include "Ageprogression.h"
#include <cxcore.h>
#include "cv.h"



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
	ON_BN_CLICKED(IDC_BUTTON2, &MyTabThree::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &MyTabThree::OnBnClickedButton3)
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


void MyTabThree::OnBnClickedButton2()
{
		IplImage* img11;
		IplImage* img_new;
		
		img_new = cvLoadImage("Ageprogression\\1.bmp");
		cvNamedWindow("Lap",1);
		//img11 = cvCreateImage(cvSize(101,32),8 , 3);
		
		show_histogram("Lap", img_new, "red");
		//cvSetData(img11,l_text ,303);
		//cvShowImage("Lap", img11);	
		
		cvWaitKey();

	
	// TODO: Add your control notification handler code here
}


void MyTabThree::show_histogram(char* window_title, IplImage* src, char* channel_name)
{
  IplImage* img, * canvas;
  int       bins = 256;
  int       hist[256];
  double    scale;
  int       i, j, channel, max = 0;

  CvScalar   colors[] = { CV_RGB(0,0,255), CV_RGB(0,255,0),
                          CV_RGB(255,0,0), CV_RGB(0,0,0) };

  channel = strcmp(channel_name, "blue")  == 0 ? 0
          : strcmp(channel_name, "green") == 0 ? 1
          : strcmp(channel_name, "red")   == 0 ? 2
          : strcmp(channel_name, "gray")  == 0 ? 3 : 0;

  if (src->nChannels == 3 && channel == 3)
  {
    img = cvCreateImage(cvGetSize(src), 8, 1);
    cvCvtColor(src, img, CV_BGR2GRAY);
  }
  else if (channel > src->nChannels)
    return;
  else
    img = cvCloneImage(src);

  canvas = cvCreateImage(cvSize(256, 125), IPL_DEPTH_8U, 3);
  cvSet(canvas, CV_RGB(255,255,255), NULL);

  /* Reset histogram */
  for (j = 0; j < bins-1; hist[j]=0, j++);

  /* Calc histogram of the image */
  for (i = 0; i < img->height; i++)
  {
    uchar* ptr = (uchar*)(img->imageData + i * img->widthStep);
    for (j = 0; j < img->width; j+=img->nChannels)
      hist[ptr[j+(channel == 3 ? 0 : channel)]]++;
  }

  /* Get histogram peak */
  for (i = 0; i < bins-1; i++)
    max = hist[i] > max ? hist[i] : max;

  /* Get scale so the histogram fit the canvas height */
  scale = max > canvas->height ? (double)canvas->height/max : 1.;

  /* Draw histogram */
  for (i = 0; i < bins-1; i++)
  {
    CvPoint pt1 = cvPoint(i, canvas->height - (hist[i] * scale));
    CvPoint pt2 = cvPoint(i, canvas->height);
    cvLine(canvas, pt1, pt2, colors[channel], 1, 8, 0);
  }

  cvShowImage(window_title, canvas);
  cvReleaseImage(&img);
}



void MyTabThree::OnBnClickedButton3()
{
	float p=age.getSigma();
age.applyIbsdt(p);
}
