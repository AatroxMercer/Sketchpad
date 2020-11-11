#pragma once


// Inputbox_Line 对话框

class Inputbox_Line : public CDialogEx
{
	DECLARE_DYNAMIC(Inputbox_Line)

public:
	Inputbox_Line(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Inputbox_Line();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Inputbox_Line };
#endif

private:
	CWnd* pParent;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString sx;
	CString sy;
	CString ex;
	CString ey;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickeddda();
	afx_msg void OnBnClickedBresenham();
};