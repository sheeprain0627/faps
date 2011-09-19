#pragma once
#include "afxwin.h"
#include <GL/GL.h>
#include <GL/GLU.H>
//#include "FaceModel.h"
#include "Tdsloader.h"
//#include "MAIN.H"


class COpenGLControl :	public CWnd
{


private :


public:
	void oglInitialize(void);
	void oglDrawScene(void);
	void drewScreen();

	afx_msg void OnDraw(CDC *pDC);
	void oglCreate(CRect rect,CWnd *parent);
	COpenGLControl(void);
	virtual ~COpenGLControl(void);



public:
	/******************/
	/* PUBLIC MEMBERS */
	/******************/
	// Timer
	UINT_PTR m_unpTimer;
	// View information variables
	float	 m_fLastX;
	float	 m_fLastY;
	float	 m_fPosX;
	float	 m_fPosY;
	float	 m_fZoom;
	float	 m_fRotX;
	float	 m_fRotY;
	bool	 m_bIsMaximized;

	//int		m_type;

private:
	/*******************/
	/* PRIVATE MEMBERS */
	/*******************/
	// Window information
	CWnd    *hWnd;
	HDC     hdc;
	HGLRC   hrc;
	int     m_nPixelFormat;
	CRect   m_rect;
	CRect   m_oldWindow;
	CRect   m_originalRect;


public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

