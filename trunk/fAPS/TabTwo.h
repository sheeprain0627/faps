#pragma once
#include "resource.h"

// TabTwo dialog

class TabTwo : public CDialog
{
	DECLARE_DYNAMIC(TabTwo)

public:
	TabTwo(CWnd* pParent = NULL);   // standard constructor
	virtual ~TabTwo();

// Dialog Data
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
