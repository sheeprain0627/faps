#pragma once
#include "resource.h"

// TabThree dialog

class TabThree : public CDialog
{
	DECLARE_DYNAMIC(TabThree)

public:
	TabThree(CWnd* pParent = NULL);   // standard constructor
	virtual ~TabThree();

// Dialog Data
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
