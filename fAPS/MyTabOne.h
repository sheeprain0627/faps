#pragma once


/*
* MyTabOne dialog represents tab 1
*/
#include "resource.h"
#include "afxwin.h"
#include "highgui.h"
#include "afxcmn.h"
class MyTabOne : public CDialog
{
	DECLARE_DYNAMIC(MyTabOne)

public:
	MyTabOne(CWnd* pParent = NULL);   
	virtual ~MyTabOne();

	// Dialog Data
	enum { IDD = IDD_DIALOG1 };		/*!< Enum value IDD. */


protected:
	/*!
	 DDX/DDV support
	\param a CDataExchange argument.
	*/
	virtual void DoDataExchange(CDataExchange* pDX);    

	DECLARE_MESSAGE_MAP()

public:
	
	/*!
	 to load the image
	*/
	afx_msg void OnBnClickedButton1();

	/*!
	 histogram matching for Database
	*/
	afx_msg void OnBnClickedButton5();

	/*!
	 getting width
	*/
	int getfwidth();

	/*!
	 getting height
	*/
	int getfHeight();
	void resizePic();
	void cropPic();
	void cropPic1();
	void resizePic1();

	void resizePicDB();

	afx_msg void OnBnClickedSetface();
	IplImage* MyTabOne::findImg(int x,int y);
	void MyTabOne::releaseImg(IplImage *a,int x,int y);
	void MyTabOne::showImage();
	void HistogramEqualization();		
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	IplImage* MyTabOne ::cvOverlayImage(IplImage* src, IplImage* overlay, CvPoint location, CvScalar S, CvScalar D);

	bool SBitdraw(CDC *pDC, UINT nIDResource, int i);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);

	CStatic m_text1;	/*!< CStatic value m_text1. */
	CStatic m_text2;	/*!< CStatic value m_text2. */
	static UINT MyThreadProc(LPVOID pParam);	
	CProgressCtrl warpWait;	/*!< CProgressCtrl value warpWait. */
	CStatic m_PicCtrl;		/*!< CStatic value m_PicCtrl. */
};

int* getXCriticalPoints();
int* getYCriticalPoints();