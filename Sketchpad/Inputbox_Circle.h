#pragma once


// Inputbox_Circle 对话框

class Inputbox_Circle : public CDialogEx
{
	DECLARE_DYNAMIC(Inputbox_Circle)

public:
	Inputbox_Circle(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Inputbox_Circle();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Inputbox_Circle };
#endif

private:
	CWnd* pParent;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString x;
	CString y;
	CString r;
	afx_msg void OnBnClickedCircle();
};
