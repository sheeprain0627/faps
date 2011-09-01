#pragma once
#include "resource.h"
#include "afxcmn.h"
#include "highgui.h"
using namespace cv;

// MyTabThree dialog

class MyTabThree : public CDialog
{
	DECLARE_DYNAMIC(MyTabThree)

	public:
		MyTabThree(CWnd* pParent = NULL);   // standard constructor
		virtual ~MyTabThree();

	// Dialog Data
		enum { IDD = IDD_DIALOG3 };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

		DECLARE_MESSAGE_MAP()
	public:
		afx_msg void OnBnClickedButton1();
		afx_msg void OnBnClickedPick();
		CSliderCtrl agebar;
		afx_msg void OnBnClickedLoadtexture();
		afx_msg void OnNMCustomdrawAgebar(NMHDR *pNMHDR, LRESULT *pResult);
		afx_msg void OnEnChangeEdit1();
		afx_msg void OnBnClickedButton2();
		void show_histogram(char* window_title, IplImage* src, char* channel_name);
		afx_msg void OnBnClickedButton3();
		IplImage* histeq(IplImage* src, IplImage* dst, IplImage* src1, IplImage* dst1);
		afx_msg void OnBnClickedApplyage();
		afx_msg void OnBnClickedsaveface();
		afx_msg void OnBnClickedButton4();
		afx_msg void OnBnClickedNew();
		void MyTabThree::histMatchRGB(Mat& src, const Mat& src_mask, const Mat& dst, const Mat& dst_mask) ;
		void MyTabThree::do1ChnHist(const Mat& _i, const Mat& mask, double* h, double* cdf);
		

		afx_msg void OnBnClickedButton6();
		afx_msg BOOL OnEraseBkgnd(CDC* pDC);
		
		bool SBitdraw(CDC *pDC, UINT nIDResource, int i) ;
};
