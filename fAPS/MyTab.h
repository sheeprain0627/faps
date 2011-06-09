#pragma once



// MyTab

class MyTab : public CWinApp
{
	DECLARE_DYNCREATE(MyTab)

protected:
	MyTab();           // protected constructor used by dynamic creation
	virtual ~MyTab();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


